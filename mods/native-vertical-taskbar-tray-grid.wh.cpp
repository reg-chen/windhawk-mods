// ==WindhawkMod==
// @id              native-vertical-taskbar-tray-grid
// @name            Native vertical taskbar tray grid
// @description     Arrange notification area icons into a compact grid on the native Windows 11 vertical taskbar without replacing ItemsPanel.
// @version         0.1
// @author          reg-chen
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -lversion
// ==/WindhawkMod==

// Based on the SystemTray discovery/hooking approach used by m417z's
// "Taskbar tray icon spacing and grid" mod. This fork-specific mod deliberately
// does NOT replace NotificationAreaIcons.ItemsPanel. Instead, it changes the
// existing StackPanel's local properties and arranges its ContentPresenter
// children directly, which avoids the Explorer startup crash observed when
// replacing the ItemsPanel on the native vertical taskbar.

// ==WindhawkModReadme==
/*
# Native vertical taskbar tray grid

A small Windows 11 native vertical-taskbar patch for the notification area.

The native vertical taskbar uses a vertical `StackPanel` for
`SystemTray.NotificationAreaIcons`. Taskbar Styler can't reliably override the
panel's local `Orientation` value, while replacing `ItemsPanel` can crash
Explorer during startup on affected builds.

This mod waits until `SystemTray.NotifyIconView` elements are loaded, finds the
existing notification-area `StackPanel`, changes its local orientation to
horizontal, and arranges the existing `ContentPresenter` children as a 2-column
32x24 grid.

It intentionally does not modify the overflow popup, language indicator,
Control Center, or any other tray group.
*/
// ==/WindhawkModReadme==

#include <windhawk_utils.h>

#include <atomic>
#include <list>

#undef GetCurrentTime

#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>

using namespace winrt::Windows::UI::Xaml;

namespace {

constexpr int kColumns = 2;
constexpr double kItemWidth = 32.0;
constexpr double kItemHeight = 24.0;

std::atomic<bool> g_systemTrayModuleHooked;
std::atomic<bool> g_unloading;

using FrameworkElementLoadedEventRevoker = winrt::impl::event_revoker<
    IFrameworkElement,
    &winrt::impl::abi<IFrameworkElement>::type::remove_Loaded>;

std::list<FrameworkElementLoadedEventRevoker> g_autoRevokerList;
winrt::weak_ref<FrameworkElement> g_notificationAreaIconsStackPanel;

bool IsChildOfElementByName(FrameworkElement element, PCWSTR name) {
    auto parent = element;
    while (true) {
        parent = Media::VisualTreeHelper::GetParent(parent)
                     .try_as<FrameworkElement>();
        if (!parent) {
            return false;
        }

        if (parent.Name() == name) {
            return true;
        }
    }
}

bool IsChildOfElementByClassName(FrameworkElement element, PCWSTR className) {
    auto parent = element;
    while (true) {
        parent = Media::VisualTreeHelper::GetParent(parent)
                     .try_as<FrameworkElement>();
        if (!parent) {
            return false;
        }

        if (winrt::get_class_name(parent) == className) {
            return true;
        }
    }
}

void ApplyNotificationAreaGrid(FrameworkElement stackPanelElement) {
    if (g_unloading || !stackPanelElement) {
        return;
    }

    auto stackPanel = stackPanelElement.try_as<Controls::StackPanel>();
    if (!stackPanel) {
        return;
    }

    if (!IsChildOfElementByName(stackPanelElement, L"NotificationAreaIcons")) {
        return;
    }

    int childCount = Media::VisualTreeHelper::GetChildrenCount(stackPanel);
    if (childCount <= 0) {
        return;
    }

    // Only touch the exact structure that was verified with UWPSpy. If a
    // Windows update inserts another element here, fail closed instead of
    // applying transforms against the wrong indexes.
    for (int i = 0; i < childCount; i++) {
        auto child = Media::VisualTreeHelper::GetChild(stackPanel, i)
                         .try_as<FrameworkElement>();
        if (!child || winrt::get_class_name(child) !=
                          L"Windows.UI.Xaml.Controls.ContentPresenter") {
            Wh_Log(L"Unexpected notification-area child at index %d", i);
            return;
        }
    }

    int rows = (childCount + kColumns - 1) / kColumns;

    // Set local values. This is intentional: the native vertical taskbar sets
    // Orientation locally, so a Taskbar Styler style setter loses precedence.
    stackPanel.Orientation(Controls::Orientation::Horizontal);
    stackPanel.Spacing(0);
    stackPanel.Width(kItemWidth * kColumns);
    stackPanel.Height(kItemHeight * rows);
    stackPanel.HorizontalAlignment(HorizontalAlignment::Center);

    for (int index = 0; index < childCount; index++) {
        auto child = Media::VisualTreeHelper::GetChild(stackPanel, index)
                         .as<FrameworkElement>();

        child.Width(kItemWidth);
        child.Height(kItemHeight);
        child.HorizontalAlignment(HorizontalAlignment::Left);
        child.VerticalAlignment(VerticalAlignment::Top);

        int col = index % kColumns;
        int row = index / kColumns;

        // A horizontal StackPanel initially lays the children out at
        // x = index * kItemWidth. Translate each child back into its intended
        // two-column cell, then move later rows downward.
        Media::TranslateTransform transform;
        transform.X(kItemWidth * (col - index));
        transform.Y(kItemHeight * row);
        child.RenderTransform(transform);
    }

    g_notificationAreaIconsStackPanel = stackPanelElement;

    Wh_Log(L"Applied notification-area grid: %d icons, %d rows", childCount,
           rows);
}

void ApplyNotificationAreaGridOfIcon(FrameworkElement notifyIconViewElement) {
    auto contentPresenter =
        Media::VisualTreeHelper::GetParent(notifyIconViewElement)
            .try_as<FrameworkElement>();
    if (!contentPresenter || winrt::get_class_name(contentPresenter) !=
                                 L"Windows.UI.Xaml.Controls.ContentPresenter") {
        return;
    }

    auto stackPanel = Media::VisualTreeHelper::GetParent(contentPresenter)
                          .try_as<FrameworkElement>();
    if (!stackPanel || winrt::get_class_name(stackPanel) !=
                           L"Windows.UI.Xaml.Controls.StackPanel") {
        return;
    }

    ApplyNotificationAreaGrid(stackPanel);
}

using IconView_IconView_t = void*(WINAPI*)(void* pThis);
IconView_IconView_t IconView_IconView_Original;

void* WINAPI IconView_IconView_Hook(void* pThis) {
    void* ret = IconView_IconView_Original(pThis);

    FrameworkElement iconView = nullptr;
    ((IUnknown**)pThis)[1]->QueryInterface(winrt::guid_of<FrameworkElement>(),
                                           winrt::put_abi(iconView));
    if (!iconView) {
        return ret;
    }

    g_autoRevokerList.emplace_back();
    auto autoRevokerIt = g_autoRevokerList.end();
    --autoRevokerIt;

    *autoRevokerIt = iconView.Loaded(
        winrt::auto_revoke_t{},
        [autoRevokerIt](winrt::Windows::Foundation::IInspectable const& sender,
                        RoutedEventArgs const&) {
            g_autoRevokerList.erase(autoRevokerIt);

            if (g_unloading) {
                return;
            }

            auto iconView = sender.try_as<FrameworkElement>();
            if (!iconView) {
                return;
            }

            if (winrt::get_class_name(iconView) !=
                L"SystemTray.NotifyIconView") {
                return;
            }

            if (IsChildOfElementByClassName(
                    iconView, L"SystemTray.NotificationAreaOverflow")) {
                return;
            }

            if (!IsChildOfElementByName(iconView, L"NotificationAreaIcons")) {
                return;
            }

            ApplyNotificationAreaGridOfIcon(iconView);
        });

    return ret;
}

using StackViewModel_UpdateIconIndexes_t = void(WINAPI*)(void* pThis);
StackViewModel_UpdateIconIndexes_t StackViewModel_UpdateIconIndexes_Original;

void WINAPI StackViewModel_UpdateIconIndexes_Hook(void* pThis) {
    StackViewModel_UpdateIconIndexes_Original(pThis);

    if (g_unloading) {
        return;
    }

    if (auto stackPanel = g_notificationAreaIconsStackPanel.get()) {
        ApplyNotificationAreaGrid(stackPanel);
    }
}

bool HookSystemTraySymbols(HMODULE module) {
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {LR"(public: __cdecl winrt::SystemTray::implementation::IconView::IconView(void))"},
            &IconView_IconView_Original,
            IconView_IconView_Hook,
        },
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::StackViewModel::UpdateIconIndexes(void))"},
            &StackViewModel_UpdateIconIndexes_Original,
            StackViewModel_UpdateIconIndexes_Hook,
        },
    };

    if (!HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }

    return true;
}

VS_FIXEDFILEINFO* GetModuleVersionInfo(HMODULE hModule, UINT* puPtrLen) {
    void* pFixedFileInfo = nullptr;
    UINT uPtrLen = 0;

    HRSRC hResource =
        FindResource(hModule, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    if (hResource) {
        HGLOBAL hGlobal = LoadResource(hModule, hResource);
        if (hGlobal) {
            void* pData = LockResource(hGlobal);
            if (pData) {
                if (!VerQueryValue(pData, L"\\", &pFixedFileInfo, &uPtrLen) ||
                    uPtrLen == 0) {
                    pFixedFileInfo = nullptr;
                    uPtrLen = 0;
                }
            }
        }
    }

    if (puPtrLen) {
        *puPtrLen = uPtrLen;
    }

    return (VS_FIXEDFILEINFO*)pFixedFileInfo;
}

HMODULE GetSystemTrayModuleHandle() {
    HMODULE module = GetModuleHandle(L"SystemTray.dll");
    if (!module) {
        module = GetModuleHandle(L"Taskbar.View.dll");
        if (module) {
            VS_FIXEDFILEINFO* fixedFileInfo =
                GetModuleVersionInfo(module, nullptr);
            WORD moduleMajor =
                fixedFileInfo ? HIWORD(fixedFileInfo->dwFileVersionMS) : 0;
            if (!moduleMajor || moduleMajor >= 2604) {
                module = nullptr;
            }
        }
    }

    return module;
}

void HandleLoadedModuleIfSystemTray(HMODULE module, LPCWSTR lpLibFileName) {
    if (!g_systemTrayModuleHooked && GetSystemTrayModuleHandle() == module &&
        !g_systemTrayModuleHooked.exchange(true)) {
        Wh_Log(L"Loaded %s", lpLibFileName);

        if (HookSystemTraySymbols(module)) {
            Wh_ApplyHookOperations();
        }
    }
}

using LoadLibraryExW_t = decltype(&LoadLibraryExW);
LoadLibraryExW_t LoadLibraryExW_Original;

HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR lpLibFileName,
                                   HANDLE hFile,
                                   DWORD dwFlags) {
    HMODULE module = LoadLibraryExW_Original(lpLibFileName, hFile, dwFlags);
    if (module) {
        HandleLoadedModuleIfSystemTray(module, lpLibFileName);
    }

    return module;
}

}  // namespace

BOOL Wh_ModInit() {
    Wh_Log(L">");

    if (HMODULE systemTrayModule = GetSystemTrayModuleHandle()) {
        g_systemTrayModuleHooked = true;
        if (!HookSystemTraySymbols(systemTrayModule)) {
            return FALSE;
        }
    } else {
        Wh_Log(L"System tray module not loaded yet");

        HMODULE kernelBaseModule = GetModuleHandle(L"kernelbase.dll");
        auto pKernelBaseLoadLibraryExW =
            (decltype(&LoadLibraryExW))GetProcAddress(kernelBaseModule,
                                                      "LoadLibraryExW");
        WindhawkUtils::Wh_SetFunctionHookT(pKernelBaseLoadLibraryExW,
                                           LoadLibraryExW_Hook,
                                           &LoadLibraryExW_Original);
    }

    return TRUE;
}

void Wh_ModAfterInit() {
    Wh_Log(L">");

    if (!g_systemTrayModuleHooked) {
        if (HMODULE systemTrayModule = GetSystemTrayModuleHandle()) {
            if (!g_systemTrayModuleHooked.exchange(true)) {
                Wh_Log(L"Got system tray module");

                if (HookSystemTraySymbols(systemTrayModule)) {
                    Wh_ApplyHookOperations();
                }
            }
        }
    }
}

void Wh_ModBeforeUninit() {
    Wh_Log(L">");
    g_unloading = true;
    g_autoRevokerList.clear();
}

void Wh_ModUninit() {
    Wh_Log(L">");
}
