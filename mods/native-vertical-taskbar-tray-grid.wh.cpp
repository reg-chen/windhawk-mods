// ==WindhawkMod==
// @id              native-vertical-taskbar-tray-grid
// @name            Native vertical taskbar tray grid
// @description     Arrange notification area icons into a compact grid on the native Windows 11 vertical taskbar without replacing ItemsPanel.
// @version         0.2
// @author          reg-chen
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -lversion
// ==/WindhawkMod==

// Uses the SystemTray/taskbar discovery approach from m417z's
// "Taskbar tray icon spacing and grid" mod, but intentionally does not replace
// NotificationAreaIcons.ItemsPanel and does not touch any other tray group.

// ==WindhawkModReadme==
/*
# Native vertical taskbar tray grid

Windows 11 native vertical-taskbar patch for:

    SystemTray.NotificationAreaIcons

The native side taskbar uses a vertical StackPanel. This mod changes that
existing panel's local Orientation value to Horizontal and arranges the
existing ContentPresenter children into a two-column 32x24 grid.

No ItemsPanel replacement is used.

Version 0.2 also scans the already-created taskbar XAML tree when the mod is
loaded. This matters because Windhawk can inject the mod after the tray icons
have already fired their Loaded events.
*/
// ==/WindhawkModReadme==

#include <windhawk_utils.h>

#include <atomic>
#include <functional>
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


// -----------------------------------------------------------------------------
// XAML helpers
// -----------------------------------------------------------------------------

FrameworkElement EnumChildElements(
    FrameworkElement element,
    std::function<bool(FrameworkElement)> enumCallback) {

    int childrenCount =
        Media::VisualTreeHelper::GetChildrenCount(element);

    for (int i = 0; i < childrenCount; i++) {
        auto child =
            Media::VisualTreeHelper::GetChild(element, i)
                .try_as<FrameworkElement>();

        if (!child) {
            continue;
        }

        if (enumCallback(child)) {
            return child;
        }
    }

    return nullptr;
}


FrameworkElement FindChildByName(
    FrameworkElement element,
    PCWSTR name) {

    return EnumChildElements(
        element,
        [name](FrameworkElement child) {
            return child.Name() == name;
        });
}


FrameworkElement FindDescendantByClassName(
    FrameworkElement element,
    PCWSTR className) {

    int childrenCount =
        Media::VisualTreeHelper::GetChildrenCount(element);

    for (int i = 0; i < childrenCount; i++) {
        auto child =
            Media::VisualTreeHelper::GetChild(element, i)
                .try_as<FrameworkElement>();

        if (!child) {
            continue;
        }

        if (winrt::get_class_name(child) == className) {
            return child;
        }

        if (auto found =
                FindDescendantByClassName(child, className)) {
            return found;
        }
    }

    return nullptr;
}


bool IsChildOfElementByName(
    FrameworkElement element,
    PCWSTR name) {

    auto parent = element;

    while (true) {
        parent =
            Media::VisualTreeHelper::GetParent(parent)
                .try_as<FrameworkElement>();

        if (!parent) {
            return false;
        }

        if (parent.Name() == name) {
            return true;
        }
    }
}


bool IsChildOfElementByClassName(
    FrameworkElement element,
    PCWSTR className) {

    auto parent = element;

    while (true) {
        parent =
            Media::VisualTreeHelper::GetParent(parent)
                .try_as<FrameworkElement>();

        if (!parent) {
            return false;
        }

        if (winrt::get_class_name(parent) == className) {
            return true;
        }
    }
}


// -----------------------------------------------------------------------------
// NotificationAreaIcons layout
// -----------------------------------------------------------------------------

void ApplyNotificationAreaGrid(
    FrameworkElement stackPanelElement) {

    if (g_unloading || !stackPanelElement) {
        return;
    }

    auto stackPanel =
        stackPanelElement.try_as<Controls::StackPanel>();

    if (!stackPanel) {
        return;
    }

    if (!IsChildOfElementByName(
            stackPanelElement,
            L"NotificationAreaIcons")) {
        return;
    }

    int childCount =
        Media::VisualTreeHelper::GetChildrenCount(stackPanel);

    if (childCount <= 0) {
        return;
    }

    //
    // Fail closed if Microsoft changes the verified structure.
    //
    for (int i = 0; i < childCount; i++) {
        auto child =
            Media::VisualTreeHelper::GetChild(stackPanel, i)
                .try_as<FrameworkElement>();

        if (!child ||
            winrt::get_class_name(child) !=
                L"Windows.UI.Xaml.Controls.ContentPresenter") {

            Wh_Log(
                L"Unexpected NotificationAreaIcons child at index %d",
                i);

            return;
        }
    }

    int rows =
        (childCount + kColumns - 1) / kColumns;

    //
    // Local property values.
    //
    // UWPSpy proved that assigning Orientation directly works on the native
    // vertical taskbar, whereas Taskbar Styler's Style setter doesn't win.
    //
    stackPanel.Orientation(
        Controls::Orientation::Horizontal);

    stackPanel.Spacing(0);

    stackPanel.Width(
        kItemWidth * kColumns);

    stackPanel.Height(
        kItemHeight * rows);

    stackPanel.HorizontalAlignment(
        HorizontalAlignment::Center);


    for (int index = 0;
         index < childCount;
         index++) {

        auto child =
            Media::VisualTreeHelper::GetChild(
                stackPanel,
                index)
                .as<FrameworkElement>();

        child.Width(kItemWidth);
        child.Height(kItemHeight);

        child.HorizontalAlignment(
            HorizontalAlignment::Left);

        child.VerticalAlignment(
            VerticalAlignment::Top);


        int col =
            index % kColumns;

        int row =
            index / kColumns;


        //
        // Horizontal StackPanel naturally places each element at:
        //
        //     x = index * 32
        //
        // Pull it back into a 2-column layout:
        //
        //     0  1
        //     2  3
        //
        //
        Media::TranslateTransform transform;

        transform.X(
            kItemWidth * (col - index));

        transform.Y(
            kItemHeight * row);

        child.RenderTransform(transform);
    }


    g_notificationAreaIconsStackPanel =
        stackPanelElement;


    Wh_Log(
        L"Applied NotificationAreaIcons grid: icons=%d rows=%d",
        childCount,
        rows);
}


void RestoreNotificationAreaGrid(
    FrameworkElement stackPanelElement) {

    if (!stackPanelElement) {
        return;
    }

    auto stackPanel =
        stackPanelElement.try_as<Controls::StackPanel>();

    if (!stackPanel) {
        return;
    }


    int childCount =
        Media::VisualTreeHelper::GetChildrenCount(
            stackPanel);


    for (int i = 0;
         i < childCount;
         i++) {

        auto child =
            Media::VisualTreeHelper::GetChild(
                stackPanel,
                i)
                .try_as<FrameworkElement>();

        if (!child) {
            continue;
        }

        auto childDp =
            child.as<DependencyObject>();

        childDp.ClearValue(
            FrameworkElement::WidthProperty());

        childDp.ClearValue(
            FrameworkElement::HeightProperty());

        childDp.ClearValue(
            UIElement::RenderTransformProperty());
    }


    auto panelDp =
        stackPanel.as<DependencyObject>();

    panelDp.ClearValue(
        FrameworkElement::WidthProperty());

    panelDp.ClearValue(
        FrameworkElement::HeightProperty());


    //
    // Target configuration is specifically native vertical taskbar.
    //
    stackPanel.Orientation(
        Controls::Orientation::Vertical);
}


void ApplyNotificationAreaGridOfIcon(
    FrameworkElement notifyIconViewElement) {

    auto contentPresenter =
        Media::VisualTreeHelper::GetParent(
            notifyIconViewElement)
            .try_as<FrameworkElement>();

    if (!contentPresenter ||
        winrt::get_class_name(contentPresenter) !=
            L"Windows.UI.Xaml.Controls.ContentPresenter") {

        return;
    }


    auto stackPanel =
        Media::VisualTreeHelper::GetParent(
            contentPresenter)
            .try_as<FrameworkElement>();

    if (!stackPanel ||
        winrt::get_class_name(stackPanel) !=
            L"Windows.UI.Xaml.Controls.StackPanel") {

        return;
    }


    ApplyNotificationAreaGrid(
        stackPanel);
}


// -----------------------------------------------------------------------------
// Existing XAML tree scan
// -----------------------------------------------------------------------------

bool ApplyExistingTaskbarTree(
    XamlRoot xamlRoot) {

    auto root =
        xamlRoot.Content()
            .try_as<FrameworkElement>();

    if (!root) {
        return false;
    }


    auto systemTrayFrame =
        FindDescendantByClassName(
            root,
            L"SystemTray.SystemTrayFrame");

    if (!systemTrayFrame) {
        Wh_Log(
            L"SystemTrayFrame not found");

        return false;
    }


    auto systemTrayFrameGrid =
        FindChildByName(
            systemTrayFrame,
            L"SystemTrayFrameGrid");

    if (!systemTrayFrameGrid) {

        //
        // Fallback in case Microsoft inserts another wrapper.
        //
        systemTrayFrameGrid =
            FindDescendantByClassName(
                systemTrayFrame,
                L"Windows.UI.Xaml.Controls.Grid");
    }


    if (!systemTrayFrameGrid) {
        Wh_Log(
            L"SystemTrayFrameGrid not found");

        return false;
    }


    auto notificationAreaIcons =
        FindChildByName(
            systemTrayFrameGrid,
            L"NotificationAreaIcons");


    if (!notificationAreaIcons) {

        notificationAreaIcons =
            FindDescendantByClassName(
                systemTrayFrameGrid,
                L"SystemTray.NotificationAreaIcons");
    }


    if (!notificationAreaIcons) {
        Wh_Log(
            L"NotificationAreaIcons not found");

        return false;
    }


    //
    // Verified native vertical tree:
    //
    // NotificationAreaIcons
    // └─ ItemsPresenter
    //    └─ ContentControl
    //       └─ StackPanel
    //
    //
    auto stackPanel =
        FindDescendantByClassName(
            notificationAreaIcons,
            L"Windows.UI.Xaml.Controls.StackPanel");


    if (!stackPanel) {
        Wh_Log(
            L"NotificationAreaIcons StackPanel not found");

        return false;
    }


    ApplyNotificationAreaGrid(
        stackPanel);

    return true;
}


// -----------------------------------------------------------------------------
// SystemTray hooks
// -----------------------------------------------------------------------------

using IconView_IconView_t =
    void*(WINAPI*)(void* pThis);

IconView_IconView_t
    IconView_IconView_Original;


void* WINAPI IconView_IconView_Hook(
    void* pThis) {

    void* ret =
        IconView_IconView_Original(
            pThis);


    FrameworkElement iconView = nullptr;

    ((IUnknown**)pThis)[1]->QueryInterface(
        winrt::guid_of<FrameworkElement>(),
        winrt::put_abi(iconView));


    if (!iconView) {
        return ret;
    }


    g_autoRevokerList.emplace_back();

    auto autoRevokerIt =
        g_autoRevokerList.end();

    --autoRevokerIt;


    *autoRevokerIt =
        iconView.Loaded(

            winrt::auto_revoke_t{},

            [autoRevokerIt](
                winrt::Windows::Foundation::IInspectable const& sender,
                RoutedEventArgs const&) {

                g_autoRevokerList.erase(
                    autoRevokerIt);

                if (g_unloading) {
                    return;
                }


                auto iconView =
                    sender.try_as<FrameworkElement>();

                if (!iconView) {
                    return;
                }

                if (winrt::get_class_name(iconView) !=
                    L"SystemTray.NotifyIconView") {
                    return;
                }

                //
                // Never touch overflow flyout.
                //
                if (IsChildOfElementByClassName(
                        iconView,
                        L"SystemTray.NotificationAreaOverflow")) {
                    return;
                }


                if (!IsChildOfElementByName(
                        iconView,
                        L"NotificationAreaIcons")) {

                    return;
                }

                ApplyNotificationAreaGridOfIcon(
                    iconView);
            });


    return ret;
}


using StackViewModel_UpdateIconIndexes_t =
    void(WINAPI*)(void* pThis);

StackViewModel_UpdateIconIndexes_t
    StackViewModel_UpdateIconIndexes_Original;


void WINAPI StackViewModel_UpdateIconIndexes_Hook(
    void* pThis) {

    StackViewModel_UpdateIconIndexes_Original(
        pThis);


    if (g_unloading) {
        return;
    }


    //
    // Icon count/order changed. Recalculate the geometry.
    //
    if (auto stackPanel =
            g_notificationAreaIconsStackPanel.get()) {

        ApplyNotificationAreaGrid(
            stackPanel);
    }
}


bool HookSystemTraySymbols(
    HMODULE module) {

    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {

        {
            {
                LR"(public: __cdecl winrt::SystemTray::implementation::IconView::IconView(void))"
            },
            &IconView_IconView_Original,
            IconView_IconView_Hook,
        },

        {
            {
                LR"(private: void __cdecl winrt::SystemTray::implementation::StackViewModel::UpdateIconIndexes(void))"
            },
            &StackViewModel_UpdateIconIndexes_Original,
            StackViewModel_UpdateIconIndexes_Hook,
        },
    };


    if (!HookSymbols(
            module,
            symbolHooks,
            ARRAYSIZE(symbolHooks))) {

        Wh_Log(
            L"HookSystemTraySymbols failed");

        return false;
    }


    return true;
}


// -----------------------------------------------------------------------------
// Find SystemTray.dll / Taskbar.View.dll
// -----------------------------------------------------------------------------

VS_FIXEDFILEINFO* GetModuleVersionInfo(
    HMODULE hModule,
    UINT* puPtrLen) {

    void* pFixedFileInfo =
        nullptr;

    UINT uPtrLen =
        0;


    HRSRC hResource =
        FindResource(
            hModule,
            MAKEINTRESOURCE(VS_VERSION_INFO),
            RT_VERSION);


    if (hResource) {

        HGLOBAL hGlobal =
            LoadResource(
                hModule,
                hResource);


        if (hGlobal) {

            void* pData =
                LockResource(
                    hGlobal);


            if (pData) {

                if (!VerQueryValue(
                        pData,
                        L"\\",
                        &pFixedFileInfo,
                        &uPtrLen) ||
                    uPtrLen == 0) {

                    pFixedFileInfo =
                        nullptr;

                    uPtrLen =
                        0;
                }
            }
        }
    }


    if (puPtrLen) {
        *puPtrLen =
            uPtrLen;
    }


    return
        (VS_FIXEDFILEINFO*)
            pFixedFileInfo;
}


HMODULE GetSystemTrayModuleHandle() {

    HMODULE module =
        GetModuleHandle(
            L"SystemTray.dll");


    if (!module) {

        module =
            GetModuleHandle(
                L"Taskbar.View.dll");


        if (module) {

            VS_FIXEDFILEINFO* fixedFileInfo =
                GetModuleVersionInfo(
                    module,
                    nullptr);


            WORD moduleMajor =
                fixedFileInfo
                    ? HIWORD(
                          fixedFileInfo->dwFileVersionMS)
                    : 0;


            //
            // New builds moved SystemTray into SystemTray.dll.
            //
            if (!moduleMajor ||
                moduleMajor >= 2604) {

                module =
                    nullptr;
            }
        }
    }


    return module;
}


void HandleLoadedModuleIfSystemTray(
    HMODULE module,
    LPCWSTR lpLibFileName) {

    if (!g_systemTrayModuleHooked &&
        GetSystemTrayModuleHandle() == module &&
        !g_systemTrayModuleHooked.exchange(true)) {

        Wh_Log(
            L"Loaded %s",
            lpLibFileName);


        if (HookSystemTraySymbols(
                module)) {

            Wh_ApplyHookOperations();
        }
    }
}


using LoadLibraryExW_t =
    decltype(&LoadLibraryExW);

LoadLibraryExW_t
    LoadLibraryExW_Original;


HMODULE WINAPI LoadLibraryExW_Hook(
    LPCWSTR lpLibFileName,
    HANDLE hFile,
    DWORD dwFlags) {

    HMODULE module =
        LoadLibraryExW_Original(
            lpLibFileName,
            hFile,
            dwFlags);


    if (module) {

        HandleLoadedModuleIfSystemTray(
            module,
            lpLibFileName);
    }


    return module;
}


// -----------------------------------------------------------------------------
// Existing taskbar XAML root access
//
// Adapted from the original tray icon spacing mod.
// -----------------------------------------------------------------------------

HWND FindCurrentProcessTaskbarWnd() {

    HWND hTaskbarWnd =
        nullptr;


    EnumWindows(

        [](
            HWND hWnd,
            LPARAM lParam) -> BOOL {

            DWORD processId;

            WCHAR className[32];


            if (GetWindowThreadProcessId(
                    hWnd,
                    &processId) &&

                processId ==
                    GetCurrentProcessId() &&

                GetClassName(
                    hWnd,
                    className,
                    ARRAYSIZE(className)) &&

                _wcsicmp(
                    className,
                    L"Shell_TrayWnd") == 0) {

                *reinterpret_cast<HWND*>(
                    lParam) =
                    hWnd;

                return FALSE;
            }


            return TRUE;
        },

        reinterpret_cast<LPARAM>(
            &hTaskbarWnd));


    return hTaskbarWnd;
}


void*
    CTaskBand_ITaskListWndSite_vftable;


using CTaskBand_GetTaskbarHost_t =
    void*(WINAPI*)(
        void* pThis,
        void** result);

CTaskBand_GetTaskbarHost_t
    CTaskBand_GetTaskbarHost_Original;


void*
    TaskbarHost_FrameHeight_Original;


using std__Ref_count_base__Decref_t =
    void(WINAPI*)(
        void* pThis);

std__Ref_count_base__Decref_t
    std__Ref_count_base__Decref_Original;


XamlRoot GetTaskbarXamlRoot(
    HWND hTaskbarWnd) {

    HWND hTaskSwWnd =
        (HWND)GetProp(
            hTaskbarWnd,
            L"TaskbandHWND");


    if (!hTaskSwWnd) {
        return nullptr;
    }


    void* taskBand =
        (void*)GetWindowLongPtr(
            hTaskSwWnd,
            0);


    void* taskBandForTaskListWndSite =
        taskBand;


    for (
        int i = 0;

        *(void**)taskBandForTaskListWndSite !=
            CTaskBand_ITaskListWndSite_vftable;

        i++) {

        if (i == 20) {
            return nullptr;
        }


        taskBandForTaskListWndSite =
            (void**)
                taskBandForTaskListWndSite +
            1;
    }


    void* taskbarHostSharedPtr[2]{};


    CTaskBand_GetTaskbarHost_Original(
        taskBandForTaskListWndSite,
        taskbarHostSharedPtr);


    if (!taskbarHostSharedPtr[0] &&
        !taskbarHostSharedPtr[1]) {

        return nullptr;
    }


    size_t taskbarElementIUnknownOffset =
        0x48;


#if defined(_M_X64)

    {
        //
        // 48:83EC 28 | sub rsp,28
        // 48:83C1 48 | add rcx,48
        //
        const BYTE* b =
            (const BYTE*)
                TaskbarHost_FrameHeight_Original;


        if (
            b[0] == 0x48 &&
            b[1] == 0x83 &&
            b[2] == 0xEC &&
            b[4] == 0x48 &&
            b[5] == 0x83 &&
            b[6] == 0xC1 &&
            b[7] <= 0x7F) {

            taskbarElementIUnknownOffset =
                b[7];

        } else {

            Wh_Log(
                L"Unsupported TaskbarHost::FrameHeight; using 0x48");
        }
    }

#else

#error "Unsupported architecture"

#endif


    auto* taskbarElementIUnknown =

        *(IUnknown**)(
            (BYTE*)
                taskbarHostSharedPtr[0] +

            taskbarElementIUnknownOffset);


    FrameworkElement taskbarElement =
        nullptr;


    taskbarElementIUnknown->QueryInterface(
        winrt::guid_of<FrameworkElement>(),
        winrt::put_abi(taskbarElement));


    auto result =
        taskbarElement
            ? taskbarElement.XamlRoot()
            : nullptr;


    std__Ref_count_base__Decref_Original(
        taskbarHostSharedPtr[1]);


    return result;
}


// -----------------------------------------------------------------------------
// Run code on taskbar UI thread
// -----------------------------------------------------------------------------

using RunFromWindowThreadProc_t =
    void(WINAPI*)(
        void* parameter);


bool RunFromWindowThread(
    HWND hWnd,
    RunFromWindowThreadProc_t proc,
    void* procParam) {

    static const UINT registeredMsg =
        RegisterWindowMessage(
            L"Windhawk_RunFromWindowThread_"
            WH_MOD_ID);


    struct PARAM {
        RunFromWindowThreadProc_t proc;
        void* procParam;
    };


    DWORD threadId =
        GetWindowThreadProcessId(
            hWnd,
            nullptr);


    if (!threadId) {
        return false;
    }


    if (threadId ==
        GetCurrentThreadId()) {

        proc(
            procParam);

        return true;
    }


    HHOOK hook =
        SetWindowsHookEx(

            WH_CALLWNDPROC,

            [](
                int nCode,
                WPARAM wParam,
                LPARAM lParam) -> LRESULT {

                if (nCode ==
                    HC_ACTION) {

                    const CWPSTRUCT* cwp =
                        (const CWPSTRUCT*)
                            lParam;


                    if (cwp->message ==
                        registeredMsg) {

                        auto* param =
                            (PARAM*)
                                cwp->lParam;


                        param->proc(
                            param->procParam);
                    }
                }


                return CallNextHookEx(
                    nullptr,
                    nCode,
                    wParam,
                    lParam);
            },

            nullptr,
            threadId);


    if (!hook) {
        return false;
    }


    PARAM param{
        proc,
        procParam
    };


    SendMessage(
        hWnd,
        registeredMsg,
        0,
        (LPARAM)&param);


    UnhookWindowsHookEx(
        hook);


    return true;
}


// -----------------------------------------------------------------------------
// Apply to already-created taskbar
// -----------------------------------------------------------------------------

void ApplyToExistingTaskbar() {

    HWND taskbarWnd =
        FindCurrentProcessTaskbarWnd();


    if (!taskbarWnd) {

        Wh_Log(
            L"Shell_TrayWnd not found");

        return;
    }


    RunFromWindowThread(

        taskbarWnd,

        [](
            void* pParam) {

            HWND taskbarWnd =
                (HWND)pParam;


            auto xamlRoot =
                GetTaskbarXamlRoot(
                    taskbarWnd);


            if (!xamlRoot) {

                Wh_Log(
                    L"GetTaskbarXamlRoot failed");

                return;
            }


            if (!ApplyExistingTaskbarTree(
                    xamlRoot)) {

                Wh_Log(
                    L"ApplyExistingTaskbarTree failed");
            }
        },

        taskbarWnd);
}


// -----------------------------------------------------------------------------
// taskbar.dll symbols
// -----------------------------------------------------------------------------

bool HookTaskbarDllSymbols() {

    HMODULE module =
        LoadLibraryEx(
            L"taskbar.dll",
            nullptr,
            LOAD_LIBRARY_SEARCH_SYSTEM32);


    if (!module) {

        Wh_Log(
            L"Failed to load taskbar.dll");

        return false;
    }


    WindhawkUtils::SYMBOL_HOOK hooks[] = {

        {
            {
                LR"(const CTaskBand::`vftable'{for `ITaskListWndSite'})"
            },
            &CTaskBand_ITaskListWndSite_vftable,
        },

        {
            {
                LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CTaskBand::GetTaskbarHost(void)const )"
            },
            &CTaskBand_GetTaskbarHost_Original,
        },

        {
            {
                LR"(public: int __cdecl TaskbarHost::FrameHeight(void)const )"
            },
            &TaskbarHost_FrameHeight_Original,
        },

        {
            {
                LR"(public: void __cdecl std::_Ref_count_base::_Decref(void))"
            },
            &std__Ref_count_base__Decref_Original,
        },
    };


    return HookSymbols(
        module,
        hooks,
        ARRAYSIZE(hooks));
}


} // namespace


// -----------------------------------------------------------------------------
// Windhawk entry points
// -----------------------------------------------------------------------------

BOOL Wh_ModInit() {

    Wh_Log(L">");


    if (HMODULE systemTrayModule =
            GetSystemTrayModuleHandle()) {

        g_systemTrayModuleHooked =
            true;


        if (!HookSystemTraySymbols(
                systemTrayModule)) {

            return FALSE;
        }

    } else {

        Wh_Log(
            L"System tray module not loaded yet");


        HMODULE kernelBaseModule =
            GetModuleHandle(
                L"kernelbase.dll");


        auto pKernelBaseLoadLibraryExW =

            (decltype(&LoadLibraryExW))
                GetProcAddress(
                    kernelBaseModule,
                    "LoadLibraryExW");


        WindhawkUtils::Wh_SetFunctionHookT(
            pKernelBaseLoadLibraryExW,
            LoadLibraryExW_Hook,
            &LoadLibraryExW_Original);
    }


    //
    // Needed for grabbing the already-created taskbar XAML root.
    //
    if (!HookTaskbarDllSymbols()) {
        return FALSE;
    }


    return TRUE;
}


void Wh_ModAfterInit() {

    Wh_Log(L">");


    if (!g_systemTrayModuleHooked) {

        if (HMODULE systemTrayModule =
                GetSystemTrayModuleHandle()) {

            if (!g_systemTrayModuleHooked.exchange(
                    true)) {

                Wh_Log(
                    L"Got system tray module");


                if (HookSystemTraySymbols(
                        systemTrayModule)) {

                    Wh_ApplyHookOperations();
                }
            }
        }
    }


    //
    // Important difference from v0.1:
    //
    // The tray can already exist before the mod gets loaded, meaning the
    // NotifyIconView.Loaded handlers will never run for existing icons.
    //
    // Explicitly scan the current XAML tree here.
    //
    ApplyToExistingTaskbar();
}


void Wh_ModBeforeUninit() {

    Wh_Log(L">");

    g_unloading =
        true;

    g_autoRevokerList.clear();


    if (auto stackPanel =
            g_notificationAreaIconsStackPanel.get()) {

        RestoreNotificationAreaGrid(
            stackPanel);
    }
}


void Wh_ModUninit() {

    Wh_Log(L">");
}
