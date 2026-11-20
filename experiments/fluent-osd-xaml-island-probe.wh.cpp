// ==WindhawkMod==
// @id              fluent-osd-xaml-island-probe
// @name            Fluent OSD XAML Island Probe (Experimental)
// @description     Isolated native XAML Island volume-preview host for testing a future Fluent OSD renderer.
// @description:zh-TW 獨立測試原生 XAML Island 的音量預覽，供 Fluent OSD 未來渲染架構研究。
// @version         0.1.1
// @author          Reg Chen
// @github          https://github.com/reg-chen
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -luser32 -lole32 -luuid -lruntimeobject -lwindowsapp
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Fluent OSD XAML Island Probe

**Experimental, not a replacement for Fluent OSD 1.0.1.**
Test with Ctrl+Alt+Shift+O. The popup renders with Windows.UI.Xaml
(Border, TextBlock, ProgressBar), not GDI+ or HTML/WebView2.

This mod has its own ID. Do not use it as a production OSD yet.
It never hides the Windows native OSD or installs Shell hooks.
If the host cannot initialize it logs a failure and leaves Explorer UI alone.

The XAML runtime is confined to a dedicated STA thread and its own HWND.
This intentionally does not reuse Fluent OSD's MTA/GDI+ UI thread.

Source: https://github.com/reg-chen/windhawk-mods/tree/fluent-osd-xaml
Copyright (c) Reg Chen. GPL-3.0.
*/
// ==/WindhawkModReadme==

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <wrl/client.h>
#include <atomic>
#include <string>
#include <algorithm>
#include <cmath>
#include <winrt/base.h>
// Windows headers define this macro; C++/WinRT's projection uses the name.
#undef GetCurrentTime
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Media.h>

// Declare the documented Win32 interop COM interface locally: some Windhawk
// SDK configurations omit windows.ui.xaml.hosting.desktopwindowxamlsource.h.
struct IDesktopWindowXamlSourceNative : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE AttachToWindow(HWND parentWnd) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_WindowHandle(HWND* child) = 0;
};

// Windhawk Clang maps __declspec to GNU attributes and ignores uuid.
// QueryInterface must use the explicit IID instead of __uuidof(local type).
constexpr GUID kDesktopWindowXamlSourceNativeIID = {
    0x3cbcf1bf, 0x2f76, 0x4e9c, {0x96, 0xab, 0xe8, 0x4b,
                                   0x37, 0x97, 0x25, 0x54}};

namespace wx = winrt::Windows::UI::Xaml;
namespace controls = winrt::Windows::UI::Xaml::Controls;
namespace media = winrt::Windows::UI::Xaml::Media;
namespace hosting = winrt::Windows::UI::Xaml::Hosting;
using Microsoft::WRL::ComPtr;

namespace {
constexpr wchar_t kHostClass[] = L"Windhawk.FluentOSD.XamlProbe.Host";
constexpr UINT kHotkeyId = 320;
constexpr UINT_PTR kHideTimer = 321;
constexpr UINT_PTR kStartupPreviewTimer = 322;
constexpr UINT kStartupPreviewDelayMs = 750;
constexpr UINT kVisibleMs = 12000; // Diagnostic preview, intentionally conspicuous.
constexpr int kProbeWidth = 344;  // Physical px, first-stage hosting check.
constexpr int kProbeHeight = 124;

std::atomic<HWND> g_host{nullptr};
std::atomic<DWORD> g_threadId{0};
std::atomic<bool> g_stopping{false};
HANDLE g_thread = nullptr;

struct ProbeState {
    HWND host = nullptr;
    HWND island = nullptr;
    hosting::WindowsXamlManager manager{nullptr};
    hosting::DesktopWindowXamlSource source{nullptr};
    controls::TextBlock volumeText{nullptr};
    controls::ProgressBar volumeBar{nullptr};
    bool registeredHotkey = false;
};

bool ReadDefaultVolume(int& percent, bool& muted) {
    ComPtr<IMMDeviceEnumerator> devices;
    if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(devices.GetAddressOf())))) return false;
    ComPtr<IMMDevice> device;
    if (FAILED(devices->GetDefaultAudioEndpoint(eRender, eMultimedia,
                                               device.GetAddressOf()))) return false;
    ComPtr<IAudioEndpointVolume> volume;
    if (FAILED(device->Activate(__uuidof(IAudioEndpointVolume),
        CLSCTX_INPROC_SERVER, nullptr,
        reinterpret_cast<void**>(volume.GetAddressOf())))) return false;
    float level = 0.0f;
    BOOL off = FALSE;
    if (FAILED(volume->GetMasterVolumeLevelScalar(&level)) ||
        FAILED(volume->GetMute(&off))) return false;
    percent = std::clamp(static_cast<int>(std::lround(level * 100.0f)), 0, 100);
    muted = off != FALSE;
    return true;
}

void ShowPreview(ProbeState& state) {
    if (g_stopping.load() || !state.host || !state.volumeText || !state.volumeBar)
        return;
    int percent = 0;
    bool muted = false;
    const bool available = ReadDefaultVolume(percent, muted);
    state.volumeText.Text(available
        ? winrt::hstring((muted ? L"靜音  " : L"音量  ") +
                         std::to_wstring(percent) + L"%")
        : winrt::hstring(L"無法讀取音訊輸出"));
    state.volumeBar.Value(available ? percent : 0);
    state.volumeBar.IsEnabled(available);

    POINT cursor{};
    HMONITOR monitor = GetCursorPos(&cursor)
        ? MonitorFromPoint(cursor, MONITOR_DEFAULTTOPRIMARY)
        : MonitorFromWindow(state.host, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(monitor, &mi)) {
        Wh_Log(L"XAML probe: GetMonitorInfo failed: %lu", GetLastError());
        return;
    }
    // Center the first-stage diagnostic instead of hiding it near a screen edge.
    const int x = mi.rcWork.left +
        (mi.rcWork.right - mi.rcWork.left - kProbeWidth) / 2;
    const int y = mi.rcWork.top +
        (mi.rcWork.bottom - mi.rcWork.top - kProbeHeight) / 2;
    if (!SetWindowPos(state.host, HWND_TOPMOST, x, y,
        kProbeWidth, kProbeHeight, SWP_NOACTIVATE | SWP_SHOWWINDOW)) {
        Wh_Log(L"XAML probe: SetWindowPos(show) failed: %lu", GetLastError());
        return;
    }
    UpdateWindow(state.host);
    Wh_Log(L"XAML probe: preview at (%d,%d), hostVisible=%d islandVisible=%d",
        x, y, static_cast<int>(IsWindowVisible(state.host)),
        static_cast<int>(state.island && IsWindowVisible(state.island)));
    if (!SetTimer(state.host, kHideTimer, kVisibleMs, nullptr))
        Wh_Log(L"XAML probe: hide timer failed: %lu", GetLastError());
}

void TryShowPreview(ProbeState& state, PCWSTR reason) {
    Wh_Log(L"XAML probe: preview requested (%s)", reason);
    try {
        ShowPreview(state);
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"XAML probe: preview failed: HRESULT 0x%08lX (%s)",
            static_cast<unsigned long>(ex.code()), ex.message().c_str());
    } catch (...) {
        Wh_Log(L"XAML probe: preview failed with unexpected exception");
    }
}

LRESULT CALLBACK ProbeWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
        return TRUE;
    }
    auto* state = reinterpret_cast<ProbeState*>(
        GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    switch (msg) {
        case WM_HOTKEY:
            if (wp == kHotkeyId && state) TryShowPreview(*state, L"hotkey");
            return 0;
        case WM_SIZE:
            if (state && state->island)
                SetWindowPos(state->island, nullptr, 0, 0,
                    LOWORD(lp), HIWORD(lp),
                    SWP_NOZORDER | SWP_NOACTIVATE);
            return 0;
        case WM_TIMER:
            if (wp == kStartupPreviewTimer) {
                KillTimer(hwnd, kStartupPreviewTimer);
                if (state) TryShowPreview(*state, L"startup");
            } else if (wp == kHideTimer) {
                KillTimer(hwnd, kHideTimer);
                ShowWindow(hwnd, SW_HIDE);
                Wh_Log(L"XAML probe: preview hidden");
            }
            return 0;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_CLOSE:
            // Do not destroy the parent before the island has been closed.
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

void CreateXamlContent(ProbeState& state) {
    // Directly build an actual Windows.UI.Xaml visual tree, not GDI+ drawing.
    controls::Border card;
    card.CornerRadius(wx::CornerRadius{14.0, 14.0, 14.0, 14.0});
    card.Padding(wx::Thickness{20.0, 14.0, 20.0, 14.0});
    card.Background(media::SolidColorBrush{
        winrt::Windows::UI::Color{255, 35, 35, 39}});

    controls::StackPanel content;
    content.Orientation(controls::Orientation::Vertical);
    controls::TextBlock title;
    title.Text(L"FLUENT OSD  /  XAML");
    title.FontSize(12.0);
    title.Foreground(media::SolidColorBrush{
        winrt::Windows::UI::Color{255, 168, 182, 208}});
    content.Children().Append(title);

    controls::TextBlock volume;
    volume.Text(L"音量");
    volume.FontSize(21.0);
    volume.Margin(wx::Thickness{0.0, 6.0, 0.0, 0.0});
    volume.Foreground(media::SolidColorBrush{
        winrt::Windows::UI::Color{255, 248, 248, 252}});
    content.Children().Append(volume);

    controls::ProgressBar bar;
    bar.Minimum(0);
    bar.Maximum(100);
    bar.Value(0);
    bar.Height(8.0);
    bar.Margin(wx::Thickness{0.0, 9.0, 0.0, 0.0});
    bar.Foreground(media::SolidColorBrush{
        winrt::Windows::UI::Color{255, 103, 172, 255}});
    content.Children().Append(bar);

    card.Child(content);
    state.source.Content(card);
    state.volumeText = volume;
    state.volumeBar = bar;
}

DWORD WINAPI ProbeThreadProc(void*) {
    ProbeState state;
    bool apartmentReady = false;
    bool classRegistered = false;
    HINSTANCE instance = GetModuleHandleW(nullptr);
    MSG message{};
    // Create a message queue before exposing the thread ID to the unloader.
    PeekMessageW(&message, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    g_threadId.store(GetCurrentThreadId());
    Wh_Log(L"XAML probe: STA worker starting tid=%lu", GetCurrentThreadId());
    try {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
        apartmentReady = true;
        Wh_Log(L"XAML probe: STA initialized");
        if (!g_stopping.load()) {
            WNDCLASSEXW wc{sizeof(wc)};
            wc.lpfnWndProc = ProbeWindowProc;
            wc.hInstance = instance;
            wc.lpszClassName = kHostClass;
            // An ordinary redirected host gives a visible fallback surface
            // if its child XAML composition fails to present.
            wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
            classRegistered = RegisterClassExW(&wc) != 0;
            if (!classRegistered)
                winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));

            // Test a conventional redirected host first. The previous
            // WS_EX_NOREDIRECTIONBITMAP path may hide fallback rendering.
            // Neither path uses WebView2 or HTML.
            state.host = CreateWindowExW(
                WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
                kHostClass, L"", WS_POPUP,
                0, 0, kProbeWidth, kProbeHeight,
                nullptr, nullptr, instance, &state);
            if (!state.host)
                winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));
            g_host.store(state.host);
            Wh_Log(L"XAML probe: Win32 host created hwnd=%p", state.host);
            if (!g_stopping.load()) {
                Wh_Log(L"XAML probe: initializing WindowsXamlManager");
                state.manager = hosting::WindowsXamlManager::InitializeForCurrentThread();
                Wh_Log(L"XAML probe: manager initialized; creating island");
                state.source = hosting::DesktopWindowXamlSource{};
                ComPtr<IDesktopWindowXamlSourceNative> interop;
                // Use the documented COM IID explicitly. No dependency on
                // C++/WinRT projection metadata for this native interface.
                auto* unknown = winrt::get_unknown(state.source);
                winrt::check_hresult(unknown->QueryInterface(
                    kDesktopWindowXamlSourceNativeIID,
                    reinterpret_cast<void**>(interop.GetAddressOf())));
                winrt::check_hresult(interop->AttachToWindow(state.host));
                winrt::check_hresult(interop->get_WindowHandle(&state.island));
                if (!state.island)
                    winrt::throw_hresult(E_POINTER);
                Wh_Log(L"XAML probe: island attached hwnd=%p", state.island);
                if (!SetWindowPos(state.island, nullptr, 0, 0,
                    kProbeWidth, kProbeHeight,
                    SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW))
                    winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));
                CreateXamlContent(state);
                Wh_Log(L"XAML probe: XAML controls created");
                state.registeredHotkey = RegisterHotKey(state.host, kHotkeyId,
                    MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,
                    'O') != FALSE;
                if (!state.registeredHotkey)
                    Wh_Log(L"XAML probe: hotkey registration failed (%lu)",
                           GetLastError());
                else
                    Wh_Log(L"XAML probe v0.1.1 ready: Ctrl+Alt+Shift+O");
                if (!SetTimer(state.host, kStartupPreviewTimer,
                              kStartupPreviewDelayMs, nullptr))
                    TryShowPreview(state, L"startup timer unavailable");
                else
                    Wh_Log(L"XAML probe: startup auto-preview scheduled");
                while (!g_stopping.load() && GetMessageW(&message, nullptr, 0, 0) > 0) {
                    TranslateMessage(&message);
                    DispatchMessageW(&message);
                }
            }
        }
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"XAML probe startup failed: 0x%08lX %s",
            static_cast<unsigned long>(ex.code()), ex.message().c_str());
    } catch (...) {
        Wh_Log(L"XAML probe unexpected exception");
    }
    // Close island, release the framework, then destroy the parent HWND.
    if (state.registeredHotkey && state.host)
        UnregisterHotKey(state.host, kHotkeyId);
    if (state.host) {
        KillTimer(state.host, kHideTimer);
        KillTimer(state.host, kStartupPreviewTimer);
    }
    state.volumeBar = nullptr;
    state.volumeText = nullptr;
    if (state.source) {
        try {
            state.source.Content(nullptr);
            state.source.Close();
        } catch (const winrt::hresult_error& ex) {
            Wh_Log(L"XAML probe: island close failed: 0x%08lX",
                static_cast<unsigned long>(ex.code()));
        }
        state.source = nullptr;
    }
    state.island = nullptr;
    if (state.manager) {
        try {
            state.manager.Close();
        } catch (const winrt::hresult_error& ex) {
            Wh_Log(L"XAML probe: manager close failed: 0x%08lX",
                static_cast<unsigned long>(ex.code()));
        }
        state.manager = nullptr;
    }
    g_host.store(nullptr);
    if (state.host) DestroyWindow(state.host);
    if (classRegistered) UnregisterClassW(kHostClass, instance);
    // The legacy UWP XAML manager's shutdown is asynchronous. Drain only
    // messages already queued; never pump an open-ended secondary loop.
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
        if (message.message != WM_QUIT) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
    if (apartmentReady) winrt::uninit_apartment();
    g_threadId.store(0);
    return 0;
}
} // namespace

BOOL Wh_ModInit() {
    g_stopping.store(false);
    Wh_Log(L"XAML probe v0.1.1: mod init in pid=%lu", GetCurrentProcessId());
    // Standalone opt-in diagnostic mod: no hooks or native OSD suppression.
    g_thread = CreateThread(nullptr, 0, ProbeThreadProc, nullptr, 0, nullptr);
    if (!g_thread) {
        Wh_Log(L"XAML probe: UI thread creation failed (%lu)", GetLastError());
        return FALSE;
    }
    return TRUE;
}

void Wh_ModBeforeUninit() {
    g_stopping.store(true);
    const HWND hwnd = g_host.load();
    if (hwnd && IsWindow(hwnd)) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    const DWORD threadId = g_threadId.load();
    if (threadId) PostThreadMessageW(threadId, WM_QUIT, 0, 0);
    if (g_thread) {
        // Never let Windhawk unload this module while our thread may still
        // execute its code. A stuck XAML shutdown can consequently block
        // removal: this is a pilot, not an enabled-by-default renderer.
        const DWORD result = WaitForSingleObject(g_thread, 6000);
        if (result == WAIT_TIMEOUT) {
            Wh_Log(L"XAML probe: STA exit exceeded 6s; waiting for safe unload");
            WaitForSingleObject(g_thread, INFINITE);
        } else if (result == WAIT_FAILED) {
            Wh_Log(L"XAML probe: thread wait failed: %lu", GetLastError());
        }
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
}
