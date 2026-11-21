// ==WindhawkMod==
// @id              fluent-osd-xaml
// @name            Fluent OSD (XAML Experimental)
// @description     Customizable Windows 11 OSDs for volume, brightness, media, and system events.
// @description:zh-TW 自訂 Windows 11 音量、亮度、媒體及系統事件提示介面。
// @version         1.0.24
// @author          Reg Chen
// @github          https://github.com/reg-chen
// @include         explorer.exe
// @include         Twinkle Tray.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lgdiplus -lshcore -ladvapi32 -lole32 -luuid -lshell32 -lsetupapi -liphlpapi -loleaut32 -lruntimeobject -lwindowsapp -ldwmapi
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Fluent OSD

Customizable Fluent-style on-screen displays for Windows 11. Keep the
Windows indicators you want, replace individual ones, or show both.

## XAML migration experiment (v1.0.24)

The test build uses its own Windhawk ID (`fluent-osd-xaml`) and its
own receiver-window class / WM_COPYDATA tag. It can be installed
separately from the production `fluent-osd`, but do not enable both
simultaneously because their Windows OSD hooks still target the same
Explorer functions. Restore the official `@id fluent-osd` only when
merging the renderer back into the production branch.

Branch-only native XAML Island renderer for migrated categories:
**system volume, native brightness, per-target DDC/CI brightness, lock-key status, USB/Bluetooth/network details, native system status, and clipboard text/file/image notices**.
The existing XAML toggle selects the migrated renderer (no GDI+ fallback).
Opacity inherits the original background-opacity setting; Native XAML pointer gestures
relay clicks/drags/wheels to the existing audio and brightness
workers. DDC targets have independent XAML hosts and their original
monitor identity. Caps/Num/Scroll/Insert now use a shared XAML status card.
Both single-item and aggregated USB/Bluetooth/network notices now use native
XAML with click-to-expand details and ScrollViewer. Keyboard backlight,
airplane mode, camera/access, microphone, virtual desktop and system text
events use the same XAML status card. Clipboard text/file notices reuse that
status card; bounded image previews use a native WriteableBitmap, without
passing GDI handles to the XAML thread. Remaining GDI+ UI paths for media
and mixer are transitional and will be deleted as migration finishes.

## Features

- **Volume and brightness:** Horizontal or vertical OSDs, direct slider and
  wheel adjustment, internal-display brightness and external DDC/CI.
- **Audio mixer:** Master and per-app volume/mute controls, plus a dropdown
  to switch the Windows default playback device (Console/Multimedia).
- **Media controls:** Album art, track information, playback/seek controls,
  and shuffle/repeat when available through Windows SMTC.
- **System events:** Optional keyboard lock, clipboard, USB, paired Bluetooth
  Classic/LE, and network indicators.
- **Customization:** Light/dark/system themes, colors, dimensions, spacing,
  placement, duration, per-monitor routing and Traditional Chinese/English UI.

## Setup

1. Use **Native OSD visibility** to choose which Windows flyouts to hide.
2. Enable the matching **Custom OSD** switches for the indicators you want.
3. Adjust appearance, placement and timing independently. Custom indicators
   are disabled by default, so installing the mod won't replace them all.

## Compatibility and limitations

- Windows 11 x64; includes Explorer and Twinkle Tray for supported DDC hooks.
  DDC/CI requires compatible monitors and a supported brightness-write path.
- The mixer output selector changes the default **Console** and **Multimedia**
  endpoints, not the separate **Communications** endpoint. Switching uses the
  undocumented Windows `IPolicyConfig` interface and may be version-sensitive.
- Device and media notifications depend on events exposed by Windows and
  drivers. Bluetooth polling/GATT scanning is not performed; some disconnect
  transitions may be unavailable.
- All-monitor OSD mirrors are view-only; the primary popup is interactive.
  Some Shell hook symbols can change after Windows updates.

## Credits and license

Copyright (c) Reg Chen. Licensed under **GPL-3.0**. Works with supported
**Taskbar Scroll Actions** and **Twinkle Tray** workflows. No third-party
UI assets are bundled; third-party names/trademarks belong to their owners.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- displayLanguage: auto
  $name: Display language
  $name:zh-TW: 顯示語言
  $description: Choose the language used in custom OSD text. Auto follows Windows UI language (English fallback for other languages). System-provided names are unchanged.
  $description:zh-TW: 選擇自訂 OSD 的文字語言。自動會依 Windows 介面語言選擇（其他語系回退英文）；系統提供的名稱不受影響。
  $options:
    - auto: Auto (Windows language)
    - en: English
    - zh-TW: Traditional Chinese
  $options:zh-TW:
    - auto: 自動（隨系統）
    - en: English
    - zh-TW: 繁體中文
- NativeHide:
    - hideAllNativeOsd: false
      $name: Hide all supported Windows native OSDs
      $name:zh-TW: 隱藏所有支援的 Windows 原生 OSD
      $description: Master override for all eight native OSD categories below. Custom Show switches remain independent; disabling this restores individual Hide choices.
      $description:zh-TW: 優先控制下方八種 Windows 原生 OSD 的隱藏狀態。自訂顯示開關仍各自獨立；停用總開關後會恢復依個別隱藏設定判斷。
    - hideNativeVolume: false
      $name: Hide Windows volume OSD
      $name:zh-TW: 隱藏 Windows 音量 OSD
    - hideNativeBrightness: false
      $name: Hide Windows native brightness OSD
      $name:zh-TW: 隱藏 Windows 原生亮度 OSD
    - hideNativeKeyboardBrightness: false
      $name: Hide keyboard brightness OSD
      $name:zh-TW: 隱藏鍵盤背光 OSD
    - hideNativeAirplane: false
      $name: Hide airplane mode OSD
      $name:zh-TW: 隱藏飛航模式 OSD
    - hideNativeCamera: false
      $name: Hide camera OSD
      $name:zh-TW: 隱藏相機 OSD
    - hideNativeMicrophone: false
      $name: Hide microphone OSD
      $name:zh-TW: 隱藏麥克風 OSD
    - hideNativeText: false
      $name: Hide miscellaneous text OSD
      $name:zh-TW: 隱藏其他系統文字 OSD
    - hideNativeVirtualDesktop: false
      $name: Hide virtual desktop name OSD
      $name:zh-TW: 隱藏虛擬桌面名稱 OSD
  $name: 1. Windows native OSD — Hide switches
  $name:zh-TW: 1. Windows 原生 OSD — 隱藏開關
  $description: All native Hide switches default to off. The master switch hides all supported native OSDs; individual switches apply independently when the master is off. Show custom switches never affect native visibility.
  $description:zh-TW: 原生 OSD 隱藏開關預設全部關閉。總開關可隱藏所有支援類別；總開關關閉後，各項隱藏設定獨立生效。自訂 OSD 顯示開關不影響原生顯示。
- CustomOSD:
    - Switches:
        - showCustomVolume: false
          $name: Show custom Windows volume OSD
          $name:zh-TW: 顯示自訂 Windows 音量 OSD
          $description: The only switch that enables the custom Windows volume indicator. Media card, mixer arrow, and vertical layout only customize it and never enable it implicitly.
          $description:zh-TW: 只有此開關會啟用自訂 Windows 音量提示。媒體卡片、混音器箭頭及垂直版面只調整外觀，不會間接啟用音量 OSD。
        - experimentalXamlVolume: false
          $name: Experimental XAML renderer for migrated OSDs (no fallback)
          $name:zh-TW: XAML 已遷移提示渲染開關（不回退）
          $description: Enables native XAML for migrated volume, brightness, lock keys, native system status, USB/Bluetooth/network, and clipboard previews. No GDI+ fallback. Media and mixer still use the original renderer during migration.
          $description:zh-TW: 已遷移的音量、亮度、鎖定鍵、原生事件、USB／藍牙／網路及剪貼簿預覽均使用 XAML，不回退 GDI+。尚未遷移的媒體及混音器仍使用舊渲染器。
        - showCustomBrightness: false
          $name: Show custom Windows brightness OSD
          $name:zh-TW: 顯示自訂 Windows 亮度 OSD
          $description: Enabled only by this switch; vertical layout changes appearance without enabling it implicitly.
          $description:zh-TW: 只有此開關會啟用自訂 Windows 亮度提示；垂直版面僅改變呈現方式，不會間接啟用。
        - showCustomKeyboardBrightness: false
          $name: Show custom keyboard backlight OSD
          $name:zh-TW: 顯示自訂鍵盤背光 OSD
        - showCustomAirplane: false
          $name: Show custom airplane mode OSD
          $name:zh-TW: 顯示自訂飛航模式 OSD
        - showCustomCamera: false
          $name: Show custom camera OSD
          $name:zh-TW: 顯示自訂相機 OSD
          $description: Includes camera use and camera access state; labels distinguish the two.
          $description:zh-TW: 包含相機使用狀態與相機存取權限，兩種情況會顯示不同文字。
        - showCustomMicrophone: false
          $name: Show custom microphone mute OSD
          $name:zh-TW: 顯示自訂麥克風靜音 OSD
        - showCustomText: false
          $name: Show custom miscellaneous text OSD
          $name:zh-TW: 顯示自訂其他系統文字 OSD
        - showCustomVirtualDesktop: false
          $name: Show custom virtual desktop name OSD
          $name:zh-TW: 顯示自訂虛擬桌面名稱 OSD
          $description: Shows the text provided by Windows when available; desktop routing is best effort and depends on shell symbols.
          $description:zh-TW: 可用時顯示 Windows 提供的文字；虛擬桌面事件的對應屬盡力支援，取決於 Shell 內部符號。
        - showDdcBrightness: false
          $name: Show custom DDC/CI brightness OSD
          $name:zh-TW: 顯示自訂 DDC/CI 亮度 OSD
          $description: Independent of Windows native brightness Hide. Disabled by default; enable this switch to show DDC/CI brightness changes.
          $description:zh-TW: 與隱藏 Windows 原生亮度 OSD 相互獨立。預設關閉；啟用後才顯示 DDC/CI 亮度變更提示。
        - showSmtcOnVolume: false
          $name: Show SMTC media card on volume change
          $name:zh-TW: 音量變更時顯示 SMTC 媒體卡片
          $description: Show playing media title, artist, artwork and controls beside the volume OSD, if the player provides SMTC data.
          $description:zh-TW: 若播放器有提供 SMTC 資料，音量 OSD 旁會顯示歌曲名稱、演出者、專輯圖片與播放控制。
        - showVolumeMixerArrow: false
          $name: Show per-app volume mixer expand arrow
          $name:zh-TW: 顯示各程式音量混音器展開箭頭
          $description: Click the arrow to adjust Core Audio session volumes in an interactive popup.
          $description:zh-TW: 點擊箭頭以展開互動式面板，調整個別 Core Audio 工作階段音量。
        - LockKeys:
            - showCapsLockOsd: false
              $name: Show custom Caps Lock OSD
              $name:zh-TW: 顯示自訂 Caps Lock OSD
            - showNumLockOsd: false
              $name: Show custom Num Lock OSD
              $name:zh-TW: 顯示自訂 Num Lock OSD
            - showScrollLockOsd: false
              $name: Show custom Scroll Lock OSD
              $name:zh-TW: 顯示自訂 Scroll Lock OSD
            - showInsertOsd: false
              $name: Show custom Insert OSD
              $name:zh-TW: 顯示自訂 Insert OSD
              $description: Insert state is not a system-wide toggle on every application; this indicator tracks its key presses only.
              $description:zh-TW: 並非所有應用程式都將 Insert 視為全系統切換狀態；此提示僅追蹤按鍵動作。
          $name: Lock key OSDs
          $name:zh-TW: 鍵盤鎖定鍵提示
        - showClipboardOsd: false
          $name: Show clipboard OSD (opt-in)
          $name:zh-TW: 顯示剪貼簿 OSD（需自行啟用）
          $description: Disabled by default for privacy. Only processes clipboard updates after you enable it.
          $description:zh-TW: 考量隱私，預設關閉。只有啟用後才會處理剪貼簿更新。
        - showUsbEvents: false
          $name: Show USB connection/disconnection OSD
          $name:zh-TW: 顯示 USB 連接／移除 OSD
          $description: USB device-interface arrivals/removals; multiple interfaces from one physical device are coalesced.
          $description:zh-TW: 監聽 USB 裝置介面新增與移除事件；同一實體裝置的多個介面事件會合併。
        - showBluetoothEvents: false
          $name: Show Bluetooth connection OSD (Classic + LE)
          $name:zh-TW: 顯示藍牙連線 OSD（傳統藍牙及 BLE）
          $description: Monitors paired Bluetooth Classic and LE devices through Windows association-endpoint IsConnected changes. Device/driver support varies.
          $description:zh-TW: 透過 Windows 配對裝置端點的 IsConnected 狀態監聽傳統藍牙與 BLE；實際通知取決於裝置及驅動程式。
        - showNetworkEvents: false
          $name: Show network connectivity OSD
          $name:zh-TW: 顯示網路連線狀態 OSD
          $description: Windows aggregate connectivity hints, not ping or per-VPN connectivity verification.
          $description:zh-TW: 顯示 Windows 彙總網路連線提示，不執行 Ping，也不個別驗證 VPN 連線。
      $name: Individual OSD switches
      $name:zh-TW: 各項 OSD 開關
    - AudioAndMedia:
        - showMediaArtwork: true
          $name: Show SMTC thumbnail
          $name:zh-TW: 顯示 SMTC 專輯縮圖
        - showMediaControls: true
          $name: Show previous / play-pause / next buttons
          $name:zh-TW: 顯示上一首／播放暫停／下一首按鈕
        - mediaControlSizePercent: 100
          $name: SMTC playback button size (%)
          $name:zh-TW: SMTC 播放控制按鈕大小（%）
          $description: Scales both the button circles and their icons, default 100%. Mouse hit regions follow the drawn buttons.
          $description:zh-TW: 同步縮放按鈕圓形與圖示，預設 100%；滑鼠點擊範圍隨顯示大小調整。
          #! $min: 90
          #! $max: 135
          #! $format: slider
        - mixerMaxRows: 6
          $name: Visible mixer rows
          $name:zh-TW: 混音器可見列數
          #! $min: 3
          #! $max: 16
          #! $format: slider
      $name: Media and audio mixer
      $name:zh-TW: 媒體與音量混音器
    - ClipboardAndDevices:
        - clipboardTextPreview: false
          $name: Show copied text excerpt
          $name:zh-TW: 顯示複製文字摘要
          $description: May expose passwords and private text on screen. Disabled by default.
          $description:zh-TW: 可能在畫面上顯露密碼及私人文字，預設關閉。
        - clipboardImagePreview: true
          $name: Show copied image thumbnail
          $name:zh-TW: 顯示複製圖片縮圖
          $description: Displays a larger image-first preview fitted to available space without distortion; currently requires a usable bitmap clipboard format.
          $description:zh-TW: 將圖片依可用空間等比縮放為較大的預覽，不會拉伸變形；目前需有可用的位圖剪貼簿格式。
        - clipboardMaxChars: 48
          $name: Maximum copied-text preview characters
          $name:zh-TW: 複製文字預覽的最大字數
          #! $min: 12
          #! $max: 100
      $name: Clipboard and device event details
      $name:zh-TW: 剪貼簿與裝置事件詳情
    - BrightnessSources:
        - ddcFromExplorer: true
          $name: Monitor Taskbar Scroll Actions (explorer.exe)
          $name:zh-TW: 監聽 Taskbar Scroll Actions（explorer.exe）
        - ddcFromTwinkle: true
          $name: Monitor Twinkle Tray
          $name:zh-TW: 監聽 Twinkle Tray
        - ddcVcpCode: 16
          $name: Brightness VCP code (decimal; default 16 = 0x10)
          $name:zh-TW: 亮度 VCP 代碼（十進位；預設 16 = 0x10）
      $name: DDC/CI sources
      $name:zh-TW: DDC/CI 事件來源
    - Appearance:
        - ddcTheme: system
          $name: Custom OSD theme
          $name:zh-TW: 自訂 OSD 主題
          $options:
          - system: Follow Windows app theme
          - light: Light
          - dark: Dark
          $options:zh-TW:
          - system: 跟隨 Windows 應用程式主題
          - light: 淺色
          - dark: 深色
        - ddcBorderless: true
          $name: Borderless DDC/CI OSD (no outline or shadow)
          $name:zh-TW: 無邊框 DDC/CI OSD（無外框或陰影）
          $description: Matches the border/shadow behavior of Notification Center Styler's Borderless theme. Only this custom OSD is affected; no automatic cross-mod theme sync.
          $description:zh-TW: 外框／陰影行為參考 Notification Center Styler 的 Borderless 主題。只影響此自訂 OSD，不會自動與其他 Mod 同步主題。
        - ddcAccentMode: system
          $name: Progress bar color source
          $name:zh-TW: 進度條顏色來源
          $options:
          - system: Windows system accent color (automatic)
          - custom: Custom color
          $options:zh-TW:
          - system: Windows 系統強調色（自動）
          - custom: 自訂顏色
        - ddcCustomAccent: "#B97DFF"
          $name: Custom progress color (#RRGGBB)
          $name:zh-TW: 自訂進度顏色（#RRGGBB）
          $description: Used only when Progress bar color source = Custom. Invalid hex falls back to system accent.
          $description:zh-TW: 只有進度條顏色來源設為自訂時才使用。無效的十六進位色碼會回退至系統強調色。
          #! $showIf: {ddcAccentMode: custom}
          #! $format: colorRgb
        - ddcBackgroundMode: system
          $name: Background color source
          $name:zh-TW: 背景顏色來源
          $options:
          - system: Follow light/dark theme
          - custom: Custom color
          $options:zh-TW:
          - system: 跟隨淺色／深色主題
          - custom: 自訂顏色
        - ddcCustomBackground: "#28282C"
          $name: Custom background color (#RRGGBB)
          $name:zh-TW: 自訂背景顏色（#RRGGBB）
          #! $showIf: {ddcBackgroundMode: custom}
          #! $format: colorRgb
        - ddcTextMode: system
          $name: Text and icon color (Light theme defaults to dark text)
          $name:zh-TW: 文字及圖示顏色（淺色主題預設使用深色文字）
          $options:
          - system: Follow light/dark theme
          - custom: Custom color
          $options:zh-TW:
          - system: 跟隨淺色／深色主題
          - custom: 自訂顏色
        - ddcCustomText: "#FAFAFA"
          $name: Custom text and icon color (#RRGGBB)
          $name:zh-TW: 自訂文字及圖示顏色（#RRGGBB）
          #! $showIf: {ddcTextMode: custom}
          #! $format: colorRgb
        - ddcTrackMode: system
          $name: Progress track color
          $name:zh-TW: 進度軌道顏色
          $options:
          - system: Follow light/dark theme
          - custom: Custom color
          $options:zh-TW:
          - system: 跟隨淺色／深色主題
          - custom: 自訂顏色
        - ddcCustomTrack: "#5A5A60"
          $name: Custom track color (#RRGGBB)
          $name:zh-TW: 自訂軌道顏色（#RRGGBB）
          #! $showIf: {ddcTrackMode: custom}
          #! $format: colorRgb
        - ddcBackgroundOpacity: 96
          $name: Background opacity (%)
          $name:zh-TW: 背景不透明度（%）
          #! $min: 0
          #! $max: 100
          #! $format: slider
        - ddcCornerRadius: 17
          $name: Card corner radius (logical px)
          $name:zh-TW: 卡片圓角半徑（邏輯像素）
          #! $min: 0
          #! $max: 34
          #! $format: slider
        - controlButtonShape: circle
          $name: Control button shape
          $name:zh-TW: 控制按鈕形狀
          $description: Applies to SMTC controls, mixer expand button and audio-output dropdown. Circle preserves the existing look.
          $description:zh-TW: 套用至 SMTC 控制鍵、混音器展開鍵與音訊輸出下拉鍵；圓形沿用原本外觀。
          $options:
          - circle: Circle
          - square: Square / rounded square
          $options:zh-TW:
          - circle: 圓形
          - square: 方形（可調圓角）
        - controlButtonCornerRadius: 6
          $name: Square button corner radius (logical px)
          $name:zh-TW: 方形按鈕圓角半徑（邏輯像素）
          $description: Only applies to square buttons. Zero gives sharp corners; the radius is clamped to each button's half-size.
          $description:zh-TW: 僅在選擇方形時套用；0 為直角，實際圓角不超過按鈕半邊長。
          #! $showIf: {controlButtonShape: square}
          #! $min: 0
          #! $max: 16
          #! $format: slider
        - ddcBarThickness: 8
          $name: Bar thickness (logical px)
          $name:zh-TW: 進度條厚度（邏輯像素）
          #! $min: 2
          #! $max: 18
          #! $format: slider
        - ddcThumbDiameter: 11
          $name: Thumb diameter (0 = hidden)
          $name:zh-TW: 滑塊直徑（0 = 隱藏）
          #! $min: 0
          #! $max: 20
          #! $format: slider
        - ddcFontSize: 15
          $name: Value font size (logical px)
          $name:zh-TW: 數值字體大小（邏輯像素）
          #! $min: 10
          #! $max: 24
          #! $format: slider
        - ddcIconSize: 16
          $name: Vertical OSD icon size (logical px)
          $name:zh-TW: 垂直 OSD 圖示大小（邏輯像素）
          $description: Same bounding box for the speaker and sun icons. Defaults to a compact 16px before DPI and overall size scaling.
          $description:zh-TW: 喇叭與太陽圖示共用相同的邊界尺寸；預設為套用 DPI 與整體縮放前的 16 像素。
          #! $min: 10
          #! $max: 24
          #! $format: slider
        - ddcIconStrokeWidth: 2
          $name: Vertical OSD icon stroke width (logical px)
          $name:zh-TW: 垂直 OSD 圖示線條粗細（邏輯像素）
          $description: One stroke width is shared by both icon types, independent of speaker volume level.
          $description:zh-TW: 兩類圖示共用線條粗細設定，不受喇叭音量大小影響。
          #! $min: 1
          #! $max: 3
          #! $format: slider
        - ddcShowSun: true
          $name: Show sun icon
          $name:zh-TW: 顯示太陽圖示
        - ddcShowValue: true
          $name: Show brightness value
          $name:zh-TW: 顯示亮度數值
        - ddcInnerPadding: 14
          $name: Vertical OSD interior padding (logical px)
          $name:zh-TW: 垂直 OSD 內容內距（邏輯像素）
          #! $min: 6
          #! $max: 22
          #! $format: slider
      $name: Fluent appearance
      $name:zh-TW: Fluent 外觀
    - Timing:
        - globalDurationMs: 3000
          $name: Global OSD visibility (ms)
          $name:zh-TW: 全域 OSD 顯示時間（毫秒）
          $description: Shared by every custom OSD, unless individual durations are enabled. The fade animation is configured separately.
          $description:zh-TW: 除非啟用個別顯示時間，否則所有自訂 OSD 共用此值。淡入淡出動畫時間另行設定。
          #! $min: 500
          #! $max: 20000
        - individualDurations: false
          $name: Override individual OSD durations
          $name:zh-TW: 個別設定各 OSD 顯示時間
          $description: Disabled by default. Turn on to configure the categories below; otherwise every category inherits the global duration.
          $description:zh-TW: 預設停用。啟用後可分別設定下方各類別的時間；否則都沿用全域時間。
        - volumeDurationMs: 1250
          $name: Volume without SMTC (ms)
          $name:zh-TW: 無 SMTC 的音量 OSD（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - mediaDurationMs: 4000
          $name: Volume with SMTC media (ms)
          $name:zh-TW: 包含 SMTC 媒體的音量 OSD（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - nativeBrightnessDurationMs: 1250
          $name: Windows brightness (ms)
          $name:zh-TW: Windows 亮度（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - ddcBrightnessDurationMs: 1250
          $name: DDC/CI brightness (ms)
          $name:zh-TW: DDC/CI 亮度（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - nativeEventDurationMs: 1250
          $name: Other Windows native OSD replacements (ms)
          $name:zh-TW: 其他 Windows 原生 OSD 替代提示（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - lockDurationMs: 1250
          $name: Caps / Num / Scroll / Insert (ms)
          $name:zh-TW: Caps／Num／Scroll／Insert（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - clipboardDurationMs: 2100
          $name: Clipboard notification (ms)
          $name:zh-TW: 剪貼簿通知（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - deviceDurationMs: 2100
          $name: USB and Bluetooth notifications (ms)
          $name:zh-TW: USB 與藍牙通知（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - networkDurationMs: 2100
          $name: Network notification (ms)
          $name:zh-TW: 網路通知（毫秒）
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - interactiveDurationMs: 8000
          $name: Expanded Mixer / media / details (ms)
          $name:zh-TW: 展開的混音器／媒體／詳情（毫秒）
          $description: Inactivity timeout after an interactive action. While hovering an interactive panel, auto-hide is paused and restarts on mouse leave.
          $description:zh-TW: 互動後的閒置逾時。滑鼠停留在互動面板上會暫停自動隱藏，移出後重新計時。
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
      $name: OSD timing
      $name:zh-TW: OSD 顯示時間
    - MainOSDSize:
            - horizontalOsdWidth: 380
              $name: Horizontal OSD width (logical px)
              $name:zh-TW: 水平 OSD 寬度（邏輯像素）
              $description: Main volume and brightness OSD canvas width. SMTC and Mixer inherit this width in horizontal layout.
              $description:zh-TW: 主音量及亮度 OSD 的畫布寬度；在水平版面中，SMTC 與混音器繼承此寬度。
              #! $min: 300
              #! $max: 650
            - horizontalOsdHeight: 72
              $name: Horizontal OSD height (logical px)
              $name:zh-TW: 水平 OSD 高度（邏輯像素）
              $description: Main volume and brightness OSD canvas height. SMTC and Mixer use an independently adjustable expanded height.
              $description:zh-TW: 主音量及亮度 OSD 的畫布高度；SMTC 與混音器使用獨立可調的展開高度。
              #! $min: 80
              #! $max: 220
            - verticalOsdWidth: 72
              $name: Vertical OSD width (logical px)
              $name:zh-TW: 垂直 OSD 寬度（邏輯像素）
              $description: Main volume and brightness OSD canvas width. Expanded SMTC and Mixer use an independent width.
              $description:zh-TW: 主音量及亮度 OSD 的畫布寬度；垂直版面的 SMTC 與混音器使用獨立寬度。
              #! $min: 72
              #! $max: 180
            - verticalOsdHeight: 200
              $name: Vertical OSD height (logical px)
              $name:zh-TW: 垂直 OSD 高度（邏輯像素）
              $description: Main volume and brightness OSD canvas height. SMTC and Mixer inherit this height in vertical layout.
              $description:zh-TW: 主音量及亮度 OSD 的畫布高度；垂直版面的 SMTC 與混音器繼承此高度。
              #! $min: 160
              #! $max: 430
      $name: Main OSD dimensions
      $name:zh-TW: 主 OSD 尺寸
    - ExpandedPanelSize:
            - horizontalSmtcHeight: 200
              $name: Horizontal SMTC height (logical px)
              $name:zh-TW: 水平 SMTC 高度（邏輯像素）
              $description: SMTC width inherits horizontal main OSD width; only its height is independent.
              $description:zh-TW: SMTC 繼承水平主 OSD 寬度，只有高度獨立設定。
              #! $min: 176
              #! $max: 480
            - horizontalMixerHeight: 200
              $name: Horizontal Mixer height (logical px)
              $name:zh-TW: 水平混音器高度（邏輯像素）
              $description: Mixer width inherits horizontal main OSD width; only its height is independent.
              $description:zh-TW: 混音器繼承水平主 OSD 寬度，只有高度獨立設定。
              #! $min: 176
              #! $max: 480
            - verticalSmtcWidth: 380
              $name: Vertical SMTC width (logical px)
              $name:zh-TW: 垂直 SMTC 寬度（邏輯像素）
              $description: SMTC height inherits vertical main OSD height; only its width is independent.
              $description:zh-TW: SMTC 繼承垂直主 OSD 高度，只有寬度獨立設定。
              #! $min: 300
              #! $max: 650
            - verticalMixerWidth: 380
              $name: Vertical Mixer width (logical px)
              $name:zh-TW: 垂直混音器寬度（邏輯像素）
              $description: Mixer height inherits vertical main OSD height; only its width is independent.
              $description:zh-TW: 混音器繼承垂直主 OSD 高度，只有寬度獨立設定。
              #! $min: 300
              #! $max: 650
      $name: SMTC / Mixer dimensions
      $name:zh-TW: SMTC／混音器尺寸
    - Layout:
        - verticalVolumeBrightness: true
          $name: Use vertical volume and brightness layout
          $name:zh-TW: 使用垂直音量與亮度版面
          $description: Layout only; it does not enable Windows custom volume or brightness OSDs. Other native-event replacements retain compact icon-and-state cards.
          $description:zh-TW: 此選項只改變版面，不會啟用自訂 Windows 音量或亮度 OSD。其他原生事件的自訂提示仍維持精簡圖示及狀態卡片。
        - fadeOsd: true
          $name: Enable custom OSD fade animation
          $name:zh-TW: 啟用自訂 OSD 淡入淡出動畫
        - ddcSizePercent: 75
          $name: Custom OSD size (%)
          $name:zh-TW: 自訂 OSD 大小（%）
          $description: Overall uniform scale applied after the configurable logical width/height and monitor DPI. Does not change the aspect ratio of either layout.
          $description:zh-TW: 在可設定的邏輯寬高及螢幕 DPI 之後套用整體等比縮放，不會改變任何版面的長寬比例。
        - displayOutputMode: source
          $name: OSD display output
          $name:zh-TW: OSD 顯示螢幕
          $description: DDC/CI target monitor (primary for other events), primary only, selected monitor, or all monitors. DDC brightness always follows its target even in all-monitor mode; other events mirror to all screens. Mirror controls are view-only.
          $description:zh-TW: 可選 DDC/CI 事件目標螢幕（其他事件使用主螢幕）、僅主螢幕、指定螢幕或所有螢幕。即使選擇所有螢幕，DDC 亮度仍依各自目標顯示，不複製別台的數值；其他 OSD 則同步顯示。副本僅供觀看。
          $options:
          - source: Event target monitor (default)
          - primary: Primary monitor
          - selected: Selected monitor
          - all: All monitors (synchronized)
          $options:zh-TW:
          - source: 事件目標螢幕（預設）
          - primary: 主螢幕
          - selected: 指定螢幕
          - all: 所有螢幕同步顯示
        - displayOutputNumber: 1
          $name: Windows display number
          $name:zh-TW: Windows 顯示器編號
          $description: Uses the Windows device ID DISPLAY1, DISPLAY2, etc. Only used in Selected monitor mode. Falls back to the primary display if missing.
          $description:zh-TW: 對應 Windows 的 DISPLAY1、DISPLAY2 等裝置名稱；只在指定螢幕模式使用，找不到則回退主螢幕。
          #! $showIf: {displayOutputMode: selected}
          #! $min: 1
          #! $max: 16
        - ddcPosition: topLeft
          $name: OSD position
          $name:zh-TW: OSD 位置
          $options:
          - topLeft: Top left (default)
          - topCenter: Top center
          - topRight: Top right
          - centerLeft: Center left
          - center: Center
          - centerRight: Center right
          - bottomLeft: Bottom left
          - bottomCenter: Bottom center
          - bottomRight: Bottom right
          $options:zh-TW:
          - topLeft: 左上（預設）
          - topCenter: 上方中央
          - topRight: 右上
          - centerLeft: 左側中央
          - center: 中央
          - centerRight: 右側中央
          - bottomLeft: 左下
          - bottomCenter: 下方中央
          - bottomRight: 右下
        - ddcOffsetX: 0
          $name: Horizontal offset (logical px, right positive)
          $name:zh-TW: 水平位移（邏輯像素；向右為正）
          #! $min: -500
          #! $max: 500
        - ddcOffsetY: 0
          $name: Vertical offset (logical px, down positive)
          $name:zh-TW: 垂直位移（邏輯像素；向下為正）
          #! $min: -500
          #! $max: 500
        - fadeDurationMs: 160
          $name: Fade duration (ms)
          $name:zh-TW: 淡入淡出時間（毫秒）
          #! $min: 60
          #! $max: 450
      $name: Position and size
      $name:zh-TW: 位置與大小
  $name: 2. Custom OSD
  $name:zh-TW: 2. 自訂 OSD
  $description: A Show switch controls only its own custom flyout. Native visibility is controlled exclusively by the native Hide switches above; when Hide is off and Show is on, both native and custom OSDs will appear.
  $description:zh-TW: 每個顯示開關只控制對應的自訂提示；原生提示則完全由上方的隱藏開關管理。隱藏關閉、顯示開啟時，原生與自訂提示會同時出現。
*/
// ==/WindhawkModSettings==

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <dbt.h>
#include <setupapi.h>
#include <iphlpapi.h>
#include <shellapi.h>
#include <windhawk_utils.h>
#include <highlevelmonitorconfigurationapi.h>
#include <lowlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <atomic>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cwchar>
#include <cstring>
#include <cmath>
#include <gdiplus.h>
#include <dwmapi.h>
#include <shellscalingapi.h>
#include <cstdint>
#include <cstddef>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <windowsx.h>
#include <wbemidl.h>
#include <audiopolicy.h>
#include <propidl.h>
#include <new>
#include <wrl/client.h>
#include <winrt/base.h>
#undef GetCurrentTime
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.h>
// PointerRoutedEventArgs::GetCurrentPoint returns Windows.UI.Input.PointerPoint.
// Its Position/Properties members require the full projection, not just XAML.Input.
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.Media.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <array>
#include <mutex>
#include <winrt/Windows.Storage.Streams.h>
#include <vector>
#include <memory>
#include <limits>
#include <cstdlib>
#include <utility>
#include <string>

namespace {

// Presentation-independent input arithmetic. Both the legacy GDI+
// controls and migrated XAML controls use these same normalized units.
namespace osd_input {
int TrackPercent(double pointer, double origin, double span, bool reverse) {
    if (!std::isfinite(pointer) || !std::isfinite(origin) ||
        !std::isfinite(span) || span <= 0.0) return 0;
    const double ratio = reverse
        ? (origin + span - pointer) / span
        : (pointer - origin) / span;
    return std::clamp(static_cast<int>(std::lround(
        std::clamp(ratio, 0.0, 1.0) * 100.0)), 0, 100);
}

int ConsumeWheelSteps(int delta, int& remainder) {
    remainder += delta;
    const int steps = remainder / WHEEL_DELTA;
    remainder %= WHEEL_DELTA;
    return steps;
}

DWORD PercentToRaw(DWORD minimum, DWORD maximum, int percent) {
    if (maximum <= minimum) return minimum;
    const double fraction = std::clamp(percent, 0, 100) / 100.0;
    return minimum + static_cast<DWORD>(std::lround(
        static_cast<double>(maximum - minimum) * fraction));
}
} // namespace osd_input

// Optional native XAML volume renderer. WinRT and HWND ownership stay entirely
// on a dedicated STA. The existing Hook/UI threads exchange only value data.
namespace xaml_osd {
namespace wx = winrt::Windows::UI::Xaml;
namespace controls = winrt::Windows::UI::Xaml::Controls;
namespace xinput = winrt::Windows::UI::Xaml::Input;
namespace media = winrt::Windows::UI::Xaml::Media;
namespace imaging = winrt::Windows::UI::Xaml::Media::Imaging;
namespace shapes = winrt::Windows::UI::Xaml::Shapes;
namespace hosting = winrt::Windows::UI::Xaml::Hosting;
using Microsoft::WRL::ComPtr;

struct IDesktopWindowXamlSourceNative : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE AttachToWindow(HWND) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_WindowHandle(HWND*) = 0;
};
// WinRT PixelBuffer exposes IBufferByteAccess for bounded BGRA writes.
struct IBufferByteAccess : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE Buffer(BYTE**) = 0;
};
constexpr GUID kBufferByteAccessIID = {0x905a0fef, 0xbc53, 0x11df,
    {0x8c, 0x49, 0x00, 0x1e, 0x4f, 0xc6, 0x86, 0xda}};
constexpr GUID kInteropIID = {
    0x3cbcf1bf, 0x2f76, 0x4e9c,
    {0x96, 0xab, 0xe8, 0x4b, 0x37, 0x97, 0x25, 0x54}};
// Microsoft IXamlSourceTransparency: Windows.UI.Xaml.Window.Current QI.
struct IXamlSourceTransparency : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE get_IsBackgroundTransparent(BYTE*) = 0;
    virtual HRESULT STDMETHODCALLTYPE put_IsBackgroundTransparent(BYTE) = 0;
};
constexpr GUID kTransparencyIID = {
    0x06636c29, 0x5a17, 0x458d,
    {0x8e, 0xa2, 0x24, 0x22, 0xd9, 0x97, 0xa9, 0x22}};
constexpr wchar_t kClass[] = L"Windhawk.FluentOSD.XamlMigration.Host";
constexpr UINT kShowMessage = WM_APP + 680;
constexpr UINT kHideMessage = WM_APP + 681;
constexpr UINT kInputMessage = WM_APP + 690; // To existing Explorer UI receiver.
constexpr UINT_PTR kHideTimer = 683;
constexpr UINT_PTR kFadeTimer = 684;
constexpr UINT_PTR kStatusLineTimer = 685;
constexpr double kOffLineRatio = .35;
constexpr DWORD kStatusLineAnimationMs = 220;
constexpr int kWidth = 354, kHeight = 49; // Default horizontal card pixels.

std::atomic<HWND> g_ready{nullptr};
std::atomic<DWORD> g_threadId{0};
std::atomic<bool> g_stopping{false};
std::atomic<bool> g_failed{false};
std::mutex g_startLock;
SRWLOCK g_snapshotLock = SRWLOCK_INIT;
HANDLE g_thread = nullptr;

enum class LevelKind { Volume, NativeBrightness, DdcBrightness, LockStatus, NoticeStatus, NativeEvent, ClipboardImage };
struct Snapshot {
    LevelKind kind = LevelKind::Volume;
    std::wstring key;       // Nonempty for a physical DDC display/window.
    HWND receiver = nullptr;
    WCHAR device[CCHDEVICENAME]{};
    DWORD physicalIndex = 0, minimum = 0, maximum = 0;
    int percent = 0;
    int rawValue = 0;
    bool valueKnown = true;
    bool muted = false;
    bool statusActive = false;
    bool statusFontIcon = false;
    std::wstring statusTitle, statusDetail, statusGlyph;
    std::wstring noticeDetailsHeading;
    std::vector<std::wstring> noticeDetails;
    DWORD noticeInteractiveDurationMs = 8000;
    uint32_t clipboardWidth = 0, clipboardHeight = 0;
    std::vector<uint8_t> clipboardPixels; // Bounded 32-bit BGRA, no HBITMAP on STA.
    bool brightness = false;
    bool showIcon = true;
    BYTE backgroundAlpha = 255;
    bool borderless = true, fadeEnabled = false;
    int cornerRadius = 17;
    DWORD fadeDurationMs = 160;
    DWORD durationMs = 3000;
    RECT anchor{};          // Existing placement canvas in physical pixels.
    float scale = 1.0f;     // Monitor DPI * user-defined size.
    bool vertical = false;
    bool showValue = true;
    int innerPadding = 14;
    int iconSize = 16, fontSize = 15, barThickness = 8, thumbDiameter = 11;
    DWORD background = 0x232327, text = 0xf8f8fc;
    DWORD accent = 0x67acff, track = 0x56565c;
};
std::vector<Snapshot> g_pending; // Batched, atomic DDC update across monitors.

enum class InputAction { SetPercent, Wheel, ToggleMute };
struct InputCommand {
    LevelKind kind = LevelKind::Volume;
    InputAction action = InputAction::SetPercent;
    int value = 0;
    WCHAR device[CCHDEVICENAME]{};
    DWORD physicalIndex = 0, minimum = 0, maximum = 0;
};
SRWLOCK g_inputLock = SRWLOCK_INIT;
std::vector<InputCommand> g_inputQueue;

std::vector<InputCommand> TakeInputs() {
    std::vector<InputCommand> result;
    AcquireSRWLockExclusive(&g_inputLock);
    result.swap(g_inputQueue);
    ReleaseSRWLockExclusive(&g_inputLock);
    return result;
}

struct State {
    HWND host = nullptr, island = nullptr;
    bool dragging = false, iconPressed = false, pointerActive = false;
    uint32_t activePointerId = 0;
    bool fading = false, fadeOut = false;
    ULONGLONG fadeStart = 0;
    int wheelRemainder = 0;
    double trackX = 0, trackY = 0, trackW = 0, trackH = 0;
    double iconX = 0, iconY = 0, iconW = 0, iconH = 0;
    double scale = 1.0;
    Snapshot current;
    std::unordered_map<std::wstring, std::unique_ptr<State>> peers;
    hosting::WindowsXamlManager manager{nullptr};
    hosting::DesktopWindowXamlSource source{nullptr};
    controls::Border card{nullptr};
    controls::Canvas canvas{nullptr};
    controls::Viewbox viewbox{nullptr};
    controls::TextBlock icon{nullptr};
    controls::TextBlock value{nullptr};
    shapes::Rectangle track{nullptr};
    shapes::Rectangle fill{nullptr};
    media::RectangleGeometry fillClip{nullptr};
    shapes::Ellipse thumb{nullptr};
    // Shared status-card visual tree for Caps/Num/Scroll/Insert.
    controls::Border statusTile{nullptr};
    controls::TextBlock statusGlyph{nullptr}, statusTitle{nullptr},
                        statusDetail{nullptr};
    shapes::Rectangle statusUnderline{nullptr};
    controls::TextBlock noticeChevron{nullptr}, noticeHeading{nullptr};
    controls::ScrollViewer noticeScroll{nullptr};
    controls::StackPanel noticeRows{nullptr};
    controls::Border clipboardFrame{nullptr};
    controls::Image clipboardImage{nullptr};
    controls::TextBlock clipboardCaption{nullptr};
    bool noticeExpanded = false;
    double noticeHeaderH = 0;
    DWORD noticeNormalDurationMs = 3000;
    // Width is a ratio of the current text column; its center stays fixed.
    // The previous interpolated ratio is retained for interruption/reversal.
    bool statusLineAnimating = false;
    ULONGLONG statusLineStart = 0;
    double statusLineFrom = 1.0, statusLineTo = 1.0;
    double statusLineRatio = 1.0, statusLineTextW = 0.0;
    double statusLineCenterX = 0.0;

    // Intrinsic size of *all possible* speaker and volume-value states.
    // These change only with the corresponding font size; neither text
    // changes nor mute/volume events may change progress-track geometry.
    int measuredIconFontSize = -1;
    int measuredValueFontSize = -1;
    double iconSlotWidth = 0.0, iconSlotHeight = 0.0;
    double valueSlotWidth = 0.0, valueSlotHeight = 0.0;
    double rawSlotWidth = 0.0, rawSlotHeight = 0.0;
};
media::SolidColorBrush Brush(DWORD rgb, BYTE alpha = 255) {
    return media::SolidColorBrush(winrt::Windows::UI::Color{
        alpha, static_cast<BYTE>(rgb >> 16), static_cast<BYTE>(rgb >> 8),
        static_cast<BYTE>(rgb)});
}

void DrawSnapshot(State&, const Snapshot&);
void DrawStatusSnapshot(State&, const Snapshot&);
void DrawClipboardImageSnapshot(State&, const Snapshot&);
void ToggleNoticeDetails(State&);

// All audio/WMI/DDC writes stay on the original Explorer OSD UI thread.
// The STA handles pointer geometry and sends only bounded POD commands.
void SendInput(State& state, InputAction action, int value) {
    if (g_stopping.load() || !state.current.receiver) return;
    InputCommand command;
    command.kind = state.current.kind;
    command.action = action;
    command.value = value;
    wcscpy_s(command.device, state.current.device);
    command.physicalIndex = state.current.physicalIndex;
    command.minimum = state.current.minimum;
    command.maximum = state.current.maximum;
    AcquireSRWLockExclusive(&g_inputLock);
    if (g_inputQueue.size() >= 64) g_inputQueue.erase(g_inputQueue.begin());
    g_inputQueue.push_back(command);
    ReleaseSRWLockExclusive(&g_inputLock);
    if (!PostMessageW(state.current.receiver, kInputMessage, 0, 0)) {
        Wh_Log(L"XAML v1.0.24: input post failed (%lu)", GetLastError());
    }
}

void HideSurface(State& state) {
    if (state.host) {
        KillTimer(state.host, kHideTimer);
        KillTimer(state.host, kFadeTimer);
        KillTimer(state.host, kStatusLineTimer);
    }
    state.statusLineAnimating = false;
    state.noticeExpanded = false;
    // Clipboard image bytes must not persist after the flyout disappears.
    if (state.clipboardImage) state.clipboardImage.Source(nullptr);
    state.current.clipboardPixels.clear();
    state.current.clipboardPixels.shrink_to_fit();
    if (state.canvas) state.canvas.ReleasePointerCaptures();
    // CaptureLost may invoke the shared interaction callback and restart
    // the inactivity timer. Cancel once more before hiding the HWND.
    if (state.host) KillTimer(state.host, kHideTimer);
    state.dragging = state.iconPressed = state.pointerActive = false;
    state.fading = state.fadeOut = false;
    if (state.host) ShowWindow(state.host, SW_HIDE);
}

void HideAll(State& root) {
    HideSurface(root);
    for (auto& peer : root.peers) HideSurface(*peer.second);
}

// XAML itself owns hit testing and pointer capture. No detached topmost
// HWND can cover the Island (or another physical monitor's Island).
void ArmInteractionTimer(State& state, bool active) {
    if (!state.host) return;
    KillTimer(state.host, kHideTimer);
    if (active && state.fadeOut) {
        KillTimer(state.host, kFadeTimer);
        state.fading = state.fadeOut = false;
        if (state.card) state.card.Opacity(1.0);
    }
    if (!active)
        SetTimer(state.host, kHideTimer,
            std::clamp(state.current.durationMs, DWORD(500), DWORD(20000)),
            nullptr);
}

// Interactive XAML details remain visible while the pointer is over their
// native host. The normal configured timeout resumes when it leaves.
bool PointerInsideHost(const State& state) {
    if (!state.host) return false;
    POINT point{};
    RECT area{};
    return GetCursorPos(&point) && GetWindowRect(state.host, &area) &&
        PtInRect(&area, point) != FALSE;
}

bool InHitRegion(double x, double y, double left, double top,
                 double width, double height, double halo) {
    return width > 0.0 && height > 0.0 &&
        x >= left - halo && x <= left + width + halo &&
        y >= top - halo && y <= top + height + halo;
}

void DragTrack(State& state, double x, double y) {
    if (!state.current.valueKnown || state.trackW <= 0.0 ||
        state.trackH <= 0.0) return;
    const bool vertical = state.current.vertical;
    const int percent = osd_input::TrackPercent(
        vertical ? y : x,
        vertical ? state.trackY : state.trackX,
        vertical ? state.trackH : state.trackW,
        vertical);
    if (percent == state.current.percent) return;
    state.current.percent = percent;
    if (state.current.kind == LevelKind::DdcBrightness)
        state.current.rawValue = static_cast<int>(
            osd_input::PercentToRaw(state.current.minimum,
                state.current.maximum, percent));
    else state.current.rawValue = percent;
    SendInput(state, InputAction::SetPercent, percent);
    const Snapshot updated = state.current;
    DrawSnapshot(state, updated); // Preview, independent of hardware latency.
    ArmInteractionTimer(state, true);
}

void PointerPressed(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.canvas || !state.host ||
        (state.current.kind == LevelKind::LockStatus ||
         state.current.kind == LevelKind::NativeEvent)) return;
    const auto point = args.GetCurrentPoint(state.canvas);
    if (!point.Properties().IsLeftButtonPressed()) return;
    const auto pos = point.Position();
    if (state.current.kind == LevelKind::NoticeStatus) {
        if (state.current.noticeDetails.size() <= 1 ||
            pos.Y < 0 || pos.Y >= state.noticeHeaderH) return;
        state.pointerActive = true;
        state.activePointerId = args.Pointer().PointerId();
        state.canvas.CapturePointer(args.Pointer());
        ArmInteractionTimer(state, true);
        args.Handled(true);
        return;
    }
    const double halo = std::max(6.0,
        static_cast<double>(state.current.thumbDiameter) / 2.0 + 3.0);
    const bool icon = state.current.kind == LevelKind::Volume &&
        state.current.showIcon &&
        InHitRegion(pos.X, pos.Y, state.iconX, state.iconY,
                    state.iconW, state.iconH, halo);
    const bool bar = state.current.valueKnown &&
        InHitRegion(pos.X, pos.Y, state.trackX, state.trackY,
                    state.trackW, state.trackH, halo);
    if (!icon && !bar) return;
    state.pointerActive = true;
    state.activePointerId = args.Pointer().PointerId();
    state.iconPressed = icon;
    state.dragging = !icon && bar;
    state.canvas.CapturePointer(args.Pointer());
    ArmInteractionTimer(state, true);
    if (state.dragging) DragTrack(state, pos.X, pos.Y);
    args.Handled(true);
}

void PointerMoved(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.pointerActive || !state.dragging || !state.canvas ||
        args.Pointer().PointerId() != state.activePointerId) return;
    const auto pos = args.GetCurrentPoint(state.canvas).Position();
    DragTrack(state, pos.X, pos.Y);
    args.Handled(true);
}

void PointerReleased(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.pointerActive || !state.canvas ||
        args.Pointer().PointerId() != state.activePointerId) return;
    const auto pos = args.GetCurrentPoint(state.canvas).Position();
    if (state.current.kind == LevelKind::NoticeStatus) {
        const bool activate = pos.Y >= 0 && pos.Y < state.noticeHeaderH;
        state.pointerActive = false;
        state.canvas.ReleasePointerCapture(args.Pointer());
        if (activate) {
            try { ToggleNoticeDetails(state); }
            catch (const winrt::hresult_error& ex) {
                Wh_Log(L"XAML notice details HRESULT 0x%08lX",
                    static_cast<unsigned long>(ex.code()));
            } catch (...) {
                Wh_Log(L"XAML notice details unexpected exception");
            }
        }
        ArmInteractionTimer(state, PointerInsideHost(state));
        args.Handled(true);
        return;
    }
    const bool click = state.iconPressed &&
        InHitRegion(pos.X, pos.Y, state.iconX, state.iconY,
                    state.iconW, state.iconH, 0.0);
    if (state.dragging) DragTrack(state, pos.X, pos.Y);
    state.pointerActive = state.dragging = state.iconPressed = false;
    state.canvas.ReleasePointerCapture(args.Pointer());
    if (click) SendInput(state, InputAction::ToggleMute, 0);
    ArmInteractionTimer(state, false);
    args.Handled(true);
}

void PointerCancelled(State& state) {
    state.pointerActive = state.dragging = state.iconPressed = false;
    ArmInteractionTimer(state, false);
}

void PointerWheel(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.current.valueKnown ||
        state.current.kind == LevelKind::LockStatus ||
        state.current.kind == LevelKind::NoticeStatus ||
        state.current.kind == LevelKind::NativeEvent) return;
    const int delta = args.GetCurrentPoint(state.canvas)
        .Properties().MouseWheelDelta();
    const int steps = osd_input::ConsumeWheelSteps(delta, state.wheelRemainder);
    if (steps) SendInput(state, InputAction::Wheel, steps * WHEEL_DELTA);
    ArmInteractionTimer(state, false);
    args.Handled(true);
}

// Dynamic-font measurement, but stable across all runtime values.
// Use the actual visible XAML controls to guarantee matching typography.
// Only recalculate when a font-size setting changes; otherwise changing
// 98% to 100% (or toggling mute) must never shorten the track.
void UpdateTextSlots(State& state, int iconFontSize, int valueFontSize) {
    const winrt::Windows::Foundation::Size unconstrained{
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity()};
    const double autoWidth = std::numeric_limits<double>::quiet_NaN();

    if (state.measuredIconFontSize != iconFontSize) {
        const winrt::hstring current = state.icon.Text();
        state.icon.Width(autoWidth);
        state.iconSlotWidth = 0.0;
        state.iconSlotHeight = 0.0;
        // Both volume/mute glyphs affect intrinsic TextBlock dimensions.
        // Fixed slot across speaker, mute and the verified brightness glyph.
        constexpr const wchar_t* kSpeakerGlyphs[] = {
            L"\uE74F", L"\uE767", L"\uE706"};
        for (const auto glyph : kSpeakerGlyphs) {
            state.icon.Text(glyph);
            state.icon.Measure(unconstrained);
            const auto desired = state.icon.DesiredSize();
            state.iconSlotWidth = std::max(
                state.iconSlotWidth, static_cast<double>(desired.Width));
            state.iconSlotHeight = std::max(
                state.iconSlotHeight, static_cast<double>(desired.Height));
        }
        state.icon.Text(current);
        state.measuredIconFontSize = iconFontSize;
    }

    if (state.measuredValueFontSize != valueFontSize) {
        const winrt::hstring current = state.value.Text();
        state.value.Width(autoWidth);
        state.valueSlotWidth = 0.0;
        state.valueSlotHeight = 0.0;
        state.rawSlotWidth = 0.0;
        state.rawSlotHeight = 0.0;
        // Actual maximum over *all* possible labels, not an arbitrary
        // text-box width or an assumption that "100%" is widest.
        for (int percent = 0; percent <= 100; ++percent) {
            state.value.Text(winrt::hstring(
                std::to_wstring(percent) + L"%"));
            state.value.Measure(unconstrained);
            const auto desired = state.value.DesiredSize();
            state.valueSlotWidth = std::max(
                state.valueSlotWidth, static_cast<double>(desired.Width));
            state.valueSlotHeight = std::max(
                state.valueSlotHeight, static_cast<double>(desired.Height));
        }
        state.value.Text(L"65535");
        state.value.Measure(unconstrained);
        const auto raw = state.value.DesiredSize();
        state.rawSlotWidth = raw.Width;
        state.rawSlotHeight = raw.Height;
        state.value.Text(current);
        state.measuredValueFontSize = valueFontSize;
    }
}

// XAML host placement and fade lifecycle is shared by levels and status cards.
// The input geometry remains in logical DIPs on the same Canvas.
void ShowPositionedSurface(State& state, const Snapshot& value,
                           double insetX, double insetY,
                           double bodyW, double bodyH) {
    const float scale = std::clamp(value.scale, 0.5f, 6.0f);
    const int hostW = std::max(28, static_cast<int>(std::lround(bodyW * scale)));
    const int hostH = std::max(28, static_cast<int>(std::lround(bodyH * scale)));
    const int x = value.anchor.left +
        static_cast<int>(std::lround(insetX * scale));
    int y = value.anchor.top +
        static_cast<int>(std::lround(insetY * scale));
    if (value.kind == LevelKind::NoticeStatus && bodyH >
        static_cast<double>(value.anchor.bottom - value.anchor.top) / scale -
            2.0 * insetY + .5) {
        MONITORINFO mi{sizeof(mi)};
        if (GetMonitorInfoW(MonitorFromRect(&value.anchor,
                MONITOR_DEFAULTTONEAREST), &mi)) {
            const int top = static_cast<int>(mi.rcWork.top);
            const int bottom = static_cast<int>(mi.rcWork.bottom);
            y = std::clamp(y, top, std::max(top, bottom - hostH));
        }
    }
    const bool wasVisible = IsWindowVisible(state.host) != FALSE;
    if (!wasVisible)
        state.card.Opacity(value.fadeEnabled ? 0.0 : 1.0);
    else if (state.fadeOut) {
        KillTimer(state.host, kFadeTimer);
        state.fading = state.fadeOut = false;
        state.card.Opacity(1.0);
    }
    if (!SetWindowPos(state.host, HWND_TOPMOST, x, y, hostW, hostH,
                      SWP_NOACTIVATE | SWP_SHOWWINDOW)) {
        Wh_Log(L"XAML v1.0.24: show failed (%lu)", GetLastError());
        return;
    }
    if (!wasVisible) {
        state.fading = value.fadeEnabled;
        state.fadeOut = false;
        state.fadeStart = GetTickCount64();
        if (state.fading) SetTimer(state.host, kFadeTimer, 16, nullptr);
    } else if (!value.fadeEnabled && state.fading) {
        state.fading = false;
        KillTimer(state.host, kFadeTimer);
        state.card.Opacity(1.0);
    }
    ArmInteractionTimer(state, state.dragging || state.iconPressed);
}


// Native XAML status underline: animate a dimensionless width ratio instead
// of pixel positions. The underline stays centered through custom size/DPI
// changes, and a second key event reverses from its current visible width.
void PaintStatusUnderline(State& state) {
    if (!state.statusUnderline) return;
    const double width = state.statusLineTextW * state.statusLineRatio;
    state.statusUnderline.Width(width);
    controls::Canvas::SetLeft(state.statusUnderline,
        state.statusLineCenterX - width / 2.0);
    // Interpolate visual emphasis with the same eased width transition.
    const double activeBlend = std::clamp(
        (state.statusLineRatio - kOffLineRatio) /
            (1.0 - kOffLineRatio), 0.0, 1.0);
    state.statusUnderline.Opacity(.57 + .43 * activeBlend);
}

void AdvanceStatusUnderline(State& state, ULONGLONG now) {
    if (!state.statusLineAnimating) return;
    const double fraction = std::clamp(
        static_cast<double>(now - state.statusLineStart) /
            kStatusLineAnimationMs, 0.0, 1.0);
    // Cubic ease-in/out: gentle start and stop, symmetrical on reversal.
    const double ease = fraction * fraction * (3.0 - 2.0 * fraction);
    state.statusLineRatio = state.statusLineFrom +
        (state.statusLineTo - state.statusLineFrom) * ease;
    PaintStatusUnderline(state);
    if (fraction >= 1.0) {
        state.statusLineAnimating = false;
        if (state.host) KillTimer(state.host, kStatusLineTimer);
    }
}

void TransitionStatusUnderline(State& state, bool sameVisibleStatus,
                               bool active, double textX, double textW) {
    const ULONGLONG now = GetTickCount64();
    // Capture the exact interpolated value before an interrupted transition.
    AdvanceStatusUnderline(state, now);
    const double target = active ? 1.0 : kOffLineRatio;
    const bool sameTarget = sameVisibleStatus &&
        state.current.statusActive == active;
    if (!sameVisibleStatus) {
        // A fresh card also animates, even when the prior popup expired.
        // The alternate state provides a visible expansion/contraction.
        state.statusLineRatio = active ? kOffLineRatio : 1.0;
        state.statusLineAnimating = false;
        if (state.host) KillTimer(state.host, kStatusLineTimer);
    } else if (sameTarget && !state.statusLineAnimating) {
        state.statusLineRatio = target;
    }
    state.statusLineTextW = textW;
    state.statusLineCenterX = textX + textW / 2.0;
    PaintStatusUnderline(state);

    // Identical repeat events do not restart an in-flight animation.
    if (sameTarget && state.statusLineAnimating) return;
    if (std::abs(state.statusLineRatio - target) < 0.0001) {
        state.statusLineRatio = target;
        state.statusLineAnimating = false;
        PaintStatusUnderline(state);
        if (state.host) KillTimer(state.host, kStatusLineTimer);
        return;
    }
    state.statusLineFrom = state.statusLineRatio;
    state.statusLineTo = target;
    state.statusLineStart = now;
    state.statusLineAnimating = true;
    if (!SetTimer(state.host, kStatusLineTimer, 16, nullptr)) {
        state.statusLineAnimating = false;
        state.statusLineRatio = target;
        PaintStatusUnderline(state);
    }
}


void UpdateNoticeDetails(State& state, const Snapshot& value,
                         double bodyW, double headerH, double pad,
                         double insetY, double& totalBodyH) {
    const bool clickable = value.kind == LevelKind::NoticeStatus &&
        value.noticeDetails.size() > 1;
    state.noticeHeaderH = headerH;
    state.noticeChevron.Visibility(clickable
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    state.noticeChevron.Text(state.noticeExpanded ? L"\u2303" : L"\u2304");
    state.noticeChevron.Foreground(Brush(value.accent));
    state.noticeChevron.FontSize(std::clamp(value.fontSize + 4, 14, 26));
    const double arrowW = std::max(15.0, pad * 1.7);
    state.noticeChevron.Width(arrowW);
    controls::Canvas::SetLeft(state.noticeChevron,
        std::max(0.0, bodyW - pad - arrowW));
    controls::Canvas::SetTop(state.noticeChevron,
        std::max(0.0, (headerH - value.fontSize * 1.45) / 2.0));
    const bool expanded = clickable && state.noticeExpanded;
    state.noticeHeading.Visibility(expanded
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    state.noticeScroll.Visibility(expanded
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    if (!expanded) {
        totalBodyH = headerH;
        return;
    }
    const double rowH = std::max(26.0, value.fontSize * 1.8);
    const double headingH = std::max(20.0, value.fontSize * 1.5);
    const double scale = std::clamp(
        static_cast<double>(value.scale), 0.5, 6.0);
    MONITORINFO mi{sizeof(mi)};
    const HMONITOR monitor = MonitorFromRect(&value.anchor,
                                            MONITOR_DEFAULTTONEAREST);
    const double screenH = GetMonitorInfoW(monitor, &mi)
        ? (mi.rcWork.bottom - mi.rcWork.top) / scale : 640.0;
    const double maxExtra = std::max(rowH,
        screenH - headerH - 2.0 * insetY - 3.0 * pad);
    const double viewportH = std::min({
        static_cast<double>(value.noticeDetails.size()) * rowH,
        6.0 * rowH,
        std::max(rowH, maxExtra - headingH - 2.0 * pad)});
    totalBodyH = headerH + headingH + viewportH + 2.0 * pad;
    state.noticeHeading.Text(winrt::hstring(value.noticeDetailsHeading));
    state.noticeHeading.FontSize(std::clamp(value.fontSize, 11, 22));
    state.noticeHeading.Foreground(Brush(value.text));
    state.noticeHeading.Width(std::max(1.0, bodyW - 2.0 * pad));
    controls::Canvas::SetLeft(state.noticeHeading, pad);
    controls::Canvas::SetTop(state.noticeHeading, headerH + pad * .5);
    state.noticeScroll.Width(std::max(1.0, bodyW - 2.0 * pad));
    state.noticeScroll.Height(viewportH);
    controls::Canvas::SetLeft(state.noticeScroll, pad);
    controls::Canvas::SetTop(state.noticeScroll,
        headerH + pad + headingH);
    state.noticeRows.Children().Clear();
    for (const auto& name : value.noticeDetails) {
        controls::TextBlock row;
        row.Text(winrt::hstring(name));
        row.Width(std::max(1.0, bodyW - 3.0 * pad));
        row.Height(rowH);
        row.FontSize(std::clamp(value.fontSize - 2, 10, 18));
        row.Foreground(Brush(value.text));
        row.TextTrimming(wx::TextTrimming::CharacterEllipsis);
        state.noticeRows.Children().Append(row);
    }
}

void ToggleNoticeDetails(State& state) {
    if (state.current.kind != LevelKind::NoticeStatus ||
        state.current.noticeDetails.size() <= 1) return;
    state.noticeExpanded = !state.noticeExpanded;
    const Snapshot snapshot = state.current;
    DrawStatusSnapshot(state, snapshot);
}

void DrawStatusSnapshot(State& state, const Snapshot& value) {
    if (!state.host || !state.card || !state.canvas ||
        !state.statusTile || !state.statusTitle || !state.statusGlyph ||
        !state.statusDetail || !state.statusUnderline ||
        !state.noticeScroll || !state.noticeRows ||
        !state.noticeHeading || !state.noticeChevron) return;
    if (state.pointerActive && state.canvas)
        state.canvas.ReleasePointerCaptures();
    // Sample previous value before overwriting the key and toggle state.
    const bool visible = IsWindowVisible(state.host) != FALSE;
    const bool sameVisibleStatus =
        visible && state.current.kind == LevelKind::LockStatus &&
        state.current.statusTitle == value.statusTitle;
    const bool sameNotice =
        visible && state.current.kind == LevelKind::NoticeStatus &&
        value.kind == LevelKind::NoticeStatus &&
        state.current.statusTitle == value.statusTitle &&
        state.current.noticeDetails == value.noticeDetails;
    if (!sameNotice) {
        state.noticeExpanded = false;
        state.noticeNormalDurationMs = value.durationMs;
    }
    state.wheelRemainder = 0;
    state.dragging = state.iconPressed = state.pointerActive = false;
    state.scale = std::clamp(static_cast<double>(value.scale), 0.5, 6.0);

    // Same host canvas as other status notices: 296x92 by default. The
    // card inset is proportional to the source status canvas, while actual
    // card size and content columns are derived from the active bounds.
    const double logicalW = std::max(32.0,
        static_cast<double>(value.anchor.right - value.anchor.left) / state.scale);
    const double logicalH = std::max(32.0,
        static_cast<double>(value.anchor.bottom - value.anchor.top) / state.scale);
    const double insetX = std::min(logicalW * (8.0 / 296.0), logicalW / 8.0);
    const double insetY = std::min(logicalH * (7.0 / 92.0), logicalH / 8.0);
    const double bodyW = std::max(28.0, logicalW - 2.0 * insetX);
    const double bodyH = std::max(28.0, logicalH - 2.0 * insetY);
    const double pad = std::clamp(
        static_cast<double>(value.innerPadding), 6.0, 22.0) * .68;
    const double tileSize = std::max(18.0,
        std::min(bodyH - 2.0 * pad, bodyH * .69));
    const double tileX = pad, tileY = (bodyH - tileSize) / 2.0;
    const double textX = tileX + tileSize + pad;
    const bool clickableNotice =
        value.kind == LevelKind::NoticeStatus &&
        value.noticeDetails.size() > 1;
    const double arrowSpace = clickableNotice
        ? std::max(15.0, pad * 1.7) : 0.0;
    const double textW = std::max(1.0,
        bodyW - textX - pad - arrowSpace);

    state.canvas.IsHitTestVisible(clickableNotice);
    state.canvas.Width(bodyW);
    state.card.Background(Brush(value.background, value.backgroundAlpha));
    const double radius = static_cast<double>(
        std::clamp(value.cornerRadius, 0, 34));
    state.card.CornerRadius(wx::CornerRadius{radius, radius, radius, radius});
    state.card.BorderBrush(Brush(value.track));
    const double border = value.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{border, border, border, border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);
    state.thumb.Visibility(wx::Visibility::Collapsed);

    state.statusTile.Visibility(wx::Visibility::Visible);
    state.statusGlyph.Visibility(wx::Visibility::Visible);
    state.statusTitle.Visibility(wx::Visibility::Visible);
    state.statusDetail.Visibility(wx::Visibility::Visible);
    const bool lock = value.kind == LevelKind::LockStatus;
    state.statusUnderline.Visibility(lock
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    if (!lock) {
        if (state.statusLineAnimating && state.host)
            KillTimer(state.host, kStatusLineTimer);
        state.statusLineAnimating = false;
    }

    state.statusTile.Width(tileSize);
    state.statusTile.Height(tileSize);
    state.statusGlyph.Width(tileSize);
    const double tileRadius = std::min(tileSize * .19, radius);
    state.statusTile.CornerRadius(wx::CornerRadius{
        tileRadius, tileRadius, tileRadius, tileRadius});
    state.statusTile.Background(Brush(value.track, 120));
    controls::Canvas::SetLeft(state.statusTile, tileX);
    controls::Canvas::SetTop(state.statusTile, tileY);

    state.statusGlyph.FontFamily(media::FontFamily{
        value.statusFontIcon ? L"Segoe Fluent Icons" : L"Segoe UI"});
    state.statusGlyph.Text(winrt::hstring(value.statusGlyph));
    state.statusGlyph.FontSize(value.statusFontIcon
        ? std::clamp(tileSize * .53, 15.0, 32.0)
        : static_cast<double>(value.statusGlyph.size() > 1
            ? std::clamp(value.fontSize, 12, 24)
            : std::clamp(value.iconSize + 7, 16, 32)));
    state.statusGlyph.Foreground(Brush(
        value.statusFontIcon || value.statusActive ? value.accent : value.text,
        value.statusFontIcon || value.statusActive ? 255 : 195));
    state.statusTitle.Text(winrt::hstring(value.statusTitle));
    state.statusDetail.Text(winrt::hstring(value.statusDetail));
    const int titleFont = std::clamp(value.fontSize, 10, 24);
    const int detailFont = std::max(10, titleFont - 3);
    state.statusTitle.FontSize(titleFont);
    state.statusDetail.FontSize(detailFont);
    state.statusTitle.Foreground(Brush(value.text));
    state.statusDetail.Foreground(Brush(value.text, 195));
    state.statusTitle.Width(textW);
    state.statusDetail.Width(textW);
    state.statusTitle.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    state.statusDetail.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    const double lineGap = std::clamp(bodyH * .045, 2.0, 6.0);
    const double textBlockH = titleFont * 1.43 + detailFont * 1.43 + lineGap;
    const double lineHeight = std::max(2.0, bodyH * .04);
    // Reserve enough bottom clearance for the card's rounded corners.
    // Keep the underline within the unrounded interior instead of
    // anchoring it against the very bottom edge.
    const double bottomInset = std::max(pad, radius * .65);
    const double underlineTop = std::max(0.0,
        bodyH - bottomInset - lineHeight);
    const double centeredTextTop = std::max(0.0,
        (bodyH - textBlockH) / 2.0 - 2.0);
    // On short/high-radius cards, shift the text block upward to preserve
    // its gap to the underline rather than overlapping either element.
    const double availableTextTop = std::max(0.0,
        underlineTop - lineGap - textBlockH);
    const double top = lock ? std::min(centeredTextTop, availableTextTop)
                            : centeredTextTop;
    controls::Canvas::SetLeft(state.statusTitle, textX);
    controls::Canvas::SetTop(state.statusTitle, top);
    controls::Canvas::SetLeft(state.statusDetail, textX);
    controls::Canvas::SetTop(state.statusDetail, top + titleFont * 1.43 + lineGap);
    // ON expands to the full text column; OFF contracts to 35%.
    // Animate both while keeping the underline centered below the text.
    state.statusUnderline.Height(lineHeight);
    state.statusUnderline.RadiusX(lineHeight / 2.0);
    state.statusUnderline.RadiusY(lineHeight / 2.0);
    state.statusUnderline.Fill(Brush(value.accent));
    controls::Canvas::SetTop(state.statusUnderline, underlineTop);
    if (lock)
        TransitionStatusUnderline(state, sameVisibleStatus,
                                  value.statusActive, textX, textW);
    double totalBodyH = bodyH;
    UpdateNoticeDetails(state, value, bodyW, bodyH, pad,
                        insetY, totalBodyH);
    state.canvas.Height(totalBodyH);
    state.current = value;
    if (clickableNotice && state.noticeExpanded)
        state.current.durationMs = value.noticeInteractiveDurationMs;
    else if (value.kind == LevelKind::NoticeStatus)
        state.current.durationMs = state.noticeNormalDurationMs;
    ShowPositionedSurface(state, state.current, insetX, insetY,
                          bodyW, totalBodyH);
}


void DrawClipboardImageSnapshot(State& state, const Snapshot& data) {
    if (!state.host || !state.card || !state.canvas ||
        !state.clipboardFrame || !state.clipboardImage ||
        !state.clipboardCaption) return;
    state.scale = std::clamp(static_cast<double>(data.scale), 0.5, 6.0);
    const double logicalW = std::max(32.0,
        static_cast<double>(data.anchor.right - data.anchor.left) / state.scale);
    const double logicalH = std::max(32.0,
        static_cast<double>(data.anchor.bottom - data.anchor.top) / state.scale);
    const double insetX = std::min(logicalW * (8.0 / 264.0), logicalW / 8.0);
    const double insetY = std::min(logicalH * (7.0 / 224.0), logicalH / 8.0);
    const double bodyW = std::max(28.0, logicalW - 2.0 * insetX);
    const double bodyH = std::max(28.0, logicalH - 2.0 * insetY);
    const double inset = std::clamp(
        static_cast<double>(data.innerPadding), 6.0, 22.0) * .68;
    const double captionFont = std::clamp(data.fontSize - 2, 10, 18);
    const double captionHeight = captionFont * 1.5;
    const double frameW = std::max(1.0, bodyW - 2.0 * inset);
    const double frameH = std::max(1.0,
        bodyH - 3.0 * inset - captionHeight);
    const double radius = static_cast<double>(
        std::clamp(data.cornerRadius, 0, 34));
    state.canvas.IsHitTestVisible(false);
    state.canvas.Width(bodyW);
    state.canvas.Height(bodyH);
    state.card.Background(Brush(data.background, data.backgroundAlpha));
    state.card.CornerRadius(wx::CornerRadius{radius, radius, radius, radius});
    state.card.BorderBrush(Brush(data.track));
    const double border = data.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{border, border, border, border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);
    state.thumb.Visibility(wx::Visibility::Collapsed);
    state.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.noticeScroll.Visibility(wx::Visibility::Collapsed);
    if (state.statusLineAnimating) KillTimer(state.host, kStatusLineTimer);
    state.statusLineAnimating = false;
    state.noticeExpanded = false;

    // Do not retain an old image when a new snapshot is malformed.
    state.clipboardImage.Source(nullptr);
    state.clipboardFrame.Visibility(wx::Visibility::Visible);
    state.clipboardCaption.Visibility(wx::Visibility::Visible);
    state.clipboardFrame.Background(Brush(data.track, 72));
    const double previewRadius = std::min(radius, frameH * .14);
    state.clipboardFrame.CornerRadius(wx::CornerRadius{
        previewRadius, previewRadius, previewRadius, previewRadius});
    state.clipboardFrame.Width(frameW);
    state.clipboardFrame.Height(frameH);
    controls::Canvas::SetLeft(state.clipboardFrame, inset);
    controls::Canvas::SetTop(state.clipboardFrame, inset);
    state.clipboardImage.Width(frameW);
    state.clipboardImage.Height(frameH);
    state.clipboardCaption.Text(winrt::hstring(data.statusTitle));
    state.clipboardCaption.Width(frameW);
    state.clipboardCaption.FontSize(captionFont);
    state.clipboardCaption.Foreground(Brush(data.text));
    state.clipboardCaption.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    controls::Canvas::SetLeft(state.clipboardCaption, inset);
    controls::Canvas::SetTop(state.clipboardCaption,
        inset * 2.0 + frameH);

    // Construct WriteableBitmap only on the Island's STA. The original
    // Explorer UI thread transferred copied bytes, never an HBITMAP/HDC.
    const size_t bytes = static_cast<size_t>(data.clipboardWidth) *
        data.clipboardHeight * 4;
    if (data.clipboardWidth && data.clipboardHeight &&
        data.clipboardWidth <= 224 && data.clipboardHeight <= 164 &&
        bytes == data.clipboardPixels.size()) {
        imaging::WriteableBitmap bitmap{
            static_cast<int32_t>(data.clipboardWidth),
            static_cast<int32_t>(data.clipboardHeight)};
        const auto buffer = bitmap.PixelBuffer();
        if (buffer.Length() >= bytes) {
            ComPtr<IBufferByteAccess> access;
            winrt::check_hresult(winrt::get_unknown(buffer)->QueryInterface(
                kBufferByteAccessIID,
                reinterpret_cast<void**>(access.GetAddressOf())));
            BYTE* output = nullptr;
            winrt::check_hresult(access->Buffer(&output));
            if (output) {
                memcpy(output, data.clipboardPixels.data(), bytes);
                bitmap.Invalidate();
                state.clipboardImage.Source(bitmap);
            }
        }
    }
    state.current = data;
    ShowPositionedSurface(state, data, insetX, insetY, bodyW, bodyH);
}

void DrawSnapshot(State& state, const Snapshot& value) {
    if (value.kind == LevelKind::ClipboardImage) {
        DrawClipboardImageSnapshot(state, value);
        return;
    }
    if (state.clipboardImage) state.clipboardImage.Source(nullptr);
    if (state.clipboardFrame)
        state.clipboardFrame.Visibility(wx::Visibility::Collapsed);
    if (state.clipboardCaption)
        state.clipboardCaption.Visibility(wx::Visibility::Collapsed);
    if (value.kind == LevelKind::LockStatus ||
        value.kind == LevelKind::NoticeStatus ||
        value.kind == LevelKind::NativeEvent) {
        DrawStatusSnapshot(state, value);
        return;
    }
    if (!state.host || !state.card || !state.canvas ||
        !state.icon || !state.value || !state.track || !state.fill ||
        !state.fillClip || !state.thumb || !state.statusTile) return;
    if (state.current.kind != value.kind) state.wheelRemainder = 0;
    state.current = value;
    state.scale = std::clamp(static_cast<double>(value.scale), 0.5, 6.0);
    state.canvas.IsHitTestVisible(true);
    if (state.statusLineAnimating && state.host)
        KillTimer(state.host, kStatusLineTimer);
    state.statusLineAnimating = false;
    state.noticeExpanded = false;
    state.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.noticeScroll.Visibility(wx::Visibility::Collapsed);
    state.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Visible);
    state.fill.Visibility(wx::Visibility::Visible);

    const float scale = std::clamp(value.scale, 0.5f, 6.0f);
    const double logicalW = static_cast<double>(
        value.anchor.right - value.anchor.left) / scale;
    const double logicalH = static_cast<double>(
        value.anchor.bottom - value.anchor.top) / scale;
    const double insetX = value.vertical ? 7.0 : 13.0;
    const double insetY = value.vertical ? 6.0 : 10.0;
    const double bodyW = std::max(28.0, logicalW - insetX * 2.0);
    const double bodyH = std::max(28.0, logicalH -
        (value.vertical ? 12.0 : 23.0));
    state.canvas.Width(bodyW);
    state.canvas.Height(bodyH);
    state.card.Background(Brush(value.background, value.backgroundAlpha));
    const double radius = static_cast<double>(
        std::clamp(value.cornerRadius, 0, 34));
    state.card.CornerRadius(wx::CornerRadius{
        radius, radius, radius, radius});
    state.card.BorderBrush(Brush(value.track));
    const double border = value.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{
        border, border, border, border});
    state.icon.Foreground(Brush(value.text));
    state.value.Foreground(Brush(value.text));
    state.track.Fill(Brush(value.track));
    state.fill.Fill(Brush(value.accent));
    state.thumb.Fill(Brush(value.accent));

    const int percent = std::clamp(value.percent, 0, 100);
    // Segoe Fluent Icons is provided by Windows; no external font assets.
    state.icon.Text(value.brightness ? L"\uE706" :
        (value.muted || percent == 0 ? L"\uE74F" : L"\uE767"));
    const int iconFontSize = std::clamp(value.iconSize, 10, 24);
    const int numberFontSize = std::clamp(value.fontSize, 10, 24);
    state.icon.FontSize(iconFontSize);
    state.value.Text(winrt::hstring(value.valueKnown
        ? std::to_wstring(percent) + L"%"
        : std::to_wstring(value.rawValue)));
    state.value.FontSize(numberFontSize);
    // Measure visible text even if the previous event hid the label/icon.
    state.icon.Visibility(wx::Visibility::Visible);
    state.value.Visibility(wx::Visibility::Visible);

    const double trackThickness =
        static_cast<double>(std::clamp(value.barThickness, 2, 18));
    const int fillPercent = value.valueKnown ? percent : 0;
    const double wantedThumb =
        static_cast<double>(std::clamp(value.thumbDiameter, 0, 20));

    // Measure the intrinsic maximum among possible glyphs and labels.
    // Do not base the available track width on the *current* percentage.
    UpdateTextSlots(state, iconFontSize, numberFontSize);
    // Choose a *separate* cached raw-number slot for non-normalized
    // native brightness. It must not permanently widen volume labels.
    const bool rawLabel = value.brightness && !value.valueKnown;
    state.icon.Visibility(value.showIcon
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    state.value.Visibility(value.showValue
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    const double iconW = value.showIcon ? state.iconSlotWidth : 0.0;
    const double iconH = value.showIcon ? state.iconSlotHeight : 0.0;
    const double labelW = !value.showValue ? 0.0 :
        rawLabel ? std::max(state.valueSlotWidth, state.rawSlotWidth) :
                   state.valueSlotWidth;
    const double labelH = !value.showValue ? 0.0 :
        rawLabel ? std::max(state.valueSlotHeight, state.rawSlotHeight) :
                   state.valueSlotHeight;
    // A measured icon slot keeps speaker, mute and brightness aligned.
    state.icon.Width(state.iconSlotWidth);
    state.icon.TextAlignment(wx::TextAlignment::Center);
    const double inner = std::max(0.0, static_cast<double>(value.innerPadding));

    if (value.vertical) {
        // Center both texts using their measured bounds. Stack the label,
        // an expanding progress region, and speaker from top to bottom.
        // The inset uses the user's inner padding; space compresses when
        // a custom height cannot accommodate all three elements.
        const double freeHeight = std::max(0.0, bodyH -
            iconH - labelH - std::max(trackThickness, wantedThumb));
        const double pad = std::min(inner / 2.0,
            freeHeight / (value.showValue ? 4.0 : 3.0));
        const double gap = std::min(
            std::max(trackThickness, wantedThumb),
            std::max(0.0, (freeHeight - 2.0 * pad) /
                (value.showValue ? 2.0 : 1.0)));
        const double iconTop = bodyH - pad - iconH;
        const double trackTop = value.showValue ? pad + labelH + gap : pad;
        const double trackBottom = std::max(trackTop, iconTop - gap);
        const double length = trackBottom - trackTop;
        const double filled = length * fillPercent / 100.0;
        const double centerX = bodyW / 2.0;
        const double thumbSize = std::min(wantedThumb, length);

        state.track.Width(trackThickness);
        state.track.Height(length);
        state.track.RadiusX(trackThickness / 2.0);
        state.track.RadiusY(trackThickness / 2.0);
        controls::Canvas::SetLeft(state.track,
            centerX - trackThickness / 2.0);
        controls::Canvas::SetTop(state.track, trackTop);
        state.fill.Width(trackThickness);
        state.fill.Height(length);
        state.fill.RadiusX(trackThickness / 2.0);
        state.fill.RadiusY(trackThickness / 2.0);
        controls::Canvas::SetLeft(state.fill,
            centerX - trackThickness / 2.0);
        controls::Canvas::SetTop(state.fill, trackTop);
        state.fillClip.Rect(winrt::Windows::Foundation::Rect{
            0.0f, static_cast<float>(length - filled),
            static_cast<float>(trackThickness), static_cast<float>(filled)});

        state.thumb.Width(thumbSize);
        state.thumb.Height(thumbSize);
        state.thumb.Visibility(thumbSize > 0.0 && value.valueKnown
            ? wx::Visibility::Visible : wx::Visibility::Collapsed);
        const double thumbHalf = thumbSize / 2.0;
        const double thumbY = std::clamp(trackBottom - filled,
            trackTop + thumbHalf,
            std::max(trackTop + thumbHalf, trackBottom - thumbHalf));
        controls::Canvas::SetLeft(state.thumb, centerX - thumbHalf);
        controls::Canvas::SetTop(state.thumb, thumbY - thumbHalf);
        controls::Canvas::SetLeft(state.icon,
            std::max(0.0, (bodyW - iconW) / 2.0));
        controls::Canvas::SetTop(state.icon, iconTop);
        state.value.Width(bodyW);
        state.value.TextAlignment(wx::TextAlignment::Center);
        controls::Canvas::SetLeft(state.value, 0.0);
        controls::Canvas::SetTop(state.value, pad);
        state.trackX = centerX - trackThickness / 2.0;
        state.trackY = trackTop;
        state.trackW = trackThickness;
        state.trackH = length;
        state.iconX = (bodyW - iconW) / 2.0;
        state.iconY = iconTop;
        state.iconW = iconW;
        state.iconH = iconH;
    } else {
        // One shared axis for outer padding and one shared gap on BOTH
        // sides of the bar. This makes extra custom width flow into the
        // progress track rather than into a hard-coded empty gutter.
        // The outer inset follows the original painted-card cutout and
        // the user's configurable inner padding.
        const double minTrack = std::max(trackThickness, wantedThumb);
        const double freeWidth = std::max(0.0,
            bodyW - iconW - labelW - minTrack);
        const double pad = std::min(inner + insetX,
            freeWidth / (value.showValue ? 4.0 : 3.0));
        const double gap = std::min(std::max(iconH, labelH),
            std::max(0.0,
                (freeWidth - 2.0 * pad) /
                (value.showValue ? 2.0 : 1.0)));
        const double iconX = pad;
        const double valueX = bodyW - pad - labelW;
        const double trackX = iconX + iconW + gap;
        const double trackRight = value.showValue
            ? valueX - gap : bodyW - pad;
        const double trackW = std::max(0.0, trackRight - trackX);
        const double filled = trackW * fillPercent / 100.0;
        const double midY = bodyH / 2.0;
        const double thumbSize = std::min(wantedThumb, trackW);

        state.track.Width(trackW);
        state.track.Height(trackThickness);
        state.track.RadiusX(trackThickness / 2.0);
        state.track.RadiusY(trackThickness / 2.0);
        controls::Canvas::SetLeft(state.track, trackX);
        controls::Canvas::SetTop(state.track,
            midY - trackThickness / 2.0);
        state.fill.Width(trackW);
        state.fill.Height(trackThickness);
        state.fill.RadiusX(trackThickness / 2.0);
        state.fill.RadiusY(trackThickness / 2.0);
        controls::Canvas::SetLeft(state.fill, trackX);
        controls::Canvas::SetTop(state.fill,
            midY - trackThickness / 2.0);
        state.fillClip.Rect(winrt::Windows::Foundation::Rect{
            0.0f, 0.0f,
            static_cast<float>(filled), static_cast<float>(trackThickness)});

        state.thumb.Width(thumbSize);
        state.thumb.Height(thumbSize);
        state.thumb.Visibility(thumbSize > 0.0 && value.valueKnown
            ? wx::Visibility::Visible : wx::Visibility::Collapsed);
        const double thumbHalf = thumbSize / 2.0;
        const double thumbX = std::clamp(filled, thumbHalf,
            std::max(thumbHalf, trackW - thumbHalf));
        controls::Canvas::SetLeft(state.thumb, trackX + thumbX - thumbHalf);
        controls::Canvas::SetTop(state.thumb, midY - thumbHalf);
        controls::Canvas::SetLeft(state.icon, iconX);
        controls::Canvas::SetTop(state.icon,
            std::max(0.0, (bodyH - iconH) / 2.0));
        state.value.Width(labelW);
        state.value.TextAlignment(wx::TextAlignment::Right);
        controls::Canvas::SetLeft(state.value,
            std::max(0.0, valueX));
        controls::Canvas::SetTop(state.value,
            std::max(0.0, (bodyH - labelH) / 2.0));
        state.trackX = trackX;
        state.trackY = midY - trackThickness / 2.0;
        state.trackW = trackW;
        state.trackH = trackThickness;
        state.iconX = iconX;
        state.iconY = std::max(0.0, (bodyH - iconH) / 2.0);
        state.iconW = iconW;
        state.iconH = iconH;
    }

    ShowPositionedSurface(state, value, insetX, insetY, bodyW, bodyH);
}
void DeliverPending(State& root); // Defined after native/XAML host creation.
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
        return TRUE;
    }
    auto* state = reinterpret_cast<State*>(
        GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    switch (msg) {
        case kShowMessage:
            if (state) {
                try { DeliverPending(*state); }
                catch (const winrt::hresult_error& ex) {
                    Wh_Log(L"XAML v1.0.24: draw exception 0x%08lX; disabling renderer",
                           static_cast<unsigned long>(ex.code()));
                    g_failed.store(true);
                    g_ready.store(nullptr, std::memory_order_release);
                    HideAll(*state);
                } catch (...) {
                    Wh_Log(L"XAML v1.0.24: unexpected draw exception; disabling renderer");
                    g_failed.store(true);
                    g_ready.store(nullptr, std::memory_order_release);
                    HideAll(*state);
                }
            }
            return 0;
        case kHideMessage:
            if (state) HideAll(*state);
            return 0;
        case WM_SIZE:
            // Resize only the Island belonging to this XAML host.
            if (state && hwnd == state->host &&
                state->island && wp != SIZE_MINIMIZED)
                SetWindowPos(state->island, nullptr, 0, 0,
                    LOWORD(lp), HIWORD(lp),
                    SWP_NOZORDER | SWP_NOACTIVATE);
            return 0;
        case WM_TIMER:
            if (state && hwnd == state->host) {
                if (wp == kHideTimer) {
                    KillTimer(hwnd, kHideTimer);
                    if (state->current.fadeEnabled && state->card) {
                        state->fading = state->fadeOut = true;
                        state->fadeStart = GetTickCount64();
                        SetTimer(hwnd, kFadeTimer, 16, nullptr);
                    } else HideSurface(*state);
                } else if (wp == kStatusLineTimer) {
                    AdvanceStatusUnderline(*state, GetTickCount64());
                } else if (wp == kFadeTimer && state->fading && state->card) {
                    const auto elapsed = GetTickCount64() - state->fadeStart;
                    const double duration = static_cast<double>(
                        std::max<DWORD>(1, state->current.fadeDurationMs));
                    const double t = std::clamp(
                        static_cast<double>(elapsed) / duration, 0.0, 1.0);
                    const double ease = t * t * (3.0 - 2.0 * t);
                    state->card.Opacity(state->fadeOut ? 1.0 - ease : ease);
                    if (t >= 1.0) {
                        KillTimer(hwnd, kFadeTimer);
                        state->fading = false;
                        if (state->fadeOut) HideSurface(*state);
                    }
                }
            }
            return 0;
        case WM_ERASEBKGND: return TRUE;
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
        case WM_CLOSE:
            // DDC peer cleanup must not terminate the root STA.
            if (state && hwnd != state->host) {
                ShowWindow(hwnd, SW_HIDE);
                return 0;
            }
            if (state && !state->current.key.empty()) {
                HideSurface(*state);
                return 0;
            }
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}
void CreateContent(State& state) {
    // The XAML Border owns the user-configured radius and alpha.
    // DWM rounding is disabled on the host to avoid conflicting clips.
    controls::Border card;
    card.CornerRadius(wx::CornerRadius{0.0, 0.0, 0.0, 0.0});
    card.Padding(wx::Thickness{0.0, 0.0, 0.0, 0.0});
    card.Background(Brush(0x232327));

    controls::Canvas canvas;
    // A transparent background still participates in XAML hit testing.
    canvas.Background(Brush(0, 0));
    canvas.Width(354.0);
    canvas.Height(49.0);

    controls::TextBlock icon;
    icon.FontFamily(media::FontFamily{L"Segoe Fluent Icons"});
    icon.Text(L"\uE767");
    icon.FontSize(16.0);
    icon.Foreground(Brush(0xf8f8fc));
    canvas.Children().Append(icon);

    shapes::Rectangle track;
    track.Height(8.0);
    track.Width(211.0);
    track.RadiusX(4.0);
    track.RadiusY(4.0);
    track.Fill(Brush(0x56565c));
    canvas.Children().Append(track);
    shapes::Rectangle fill;
    fill.Height(8.0);
    fill.Width(0.0);
    fill.RadiusX(4.0);
    fill.RadiusY(4.0);
    fill.Fill(Brush(0x67acff));
    // Reuse a single rectangle geometry per STA for both orientations.
    media::RectangleGeometry fillClip;
    fill.Clip(fillClip);
    canvas.Children().Append(fill);
    shapes::Ellipse thumb;
    thumb.Width(11.0);
    thumb.Height(11.0);
    thumb.Fill(Brush(0x67acff));
    canvas.Children().Append(thumb);

    controls::TextBlock value;
    value.Text(L"0%");
    value.FontSize(15.0);
    value.Foreground(Brush(0xf8f8fc));
    canvas.Children().Append(value);

    // Noninteractive lock-key cards share this Canvas and stay hidden in
    // level-indicator mode. The status renderer derives its layout from bounds.
    controls::Border statusTile;
    statusTile.Visibility(wx::Visibility::Collapsed);
    controls::TextBlock statusGlyph;
    statusGlyph.FontFamily(media::FontFamily{L"Segoe UI"});
    statusGlyph.TextAlignment(wx::TextAlignment::Center);
    statusGlyph.VerticalAlignment(wx::VerticalAlignment::Center);
    statusTile.Child(statusGlyph);
    canvas.Children().Append(statusTile);

    controls::TextBlock statusTitle;
    statusTitle.Visibility(wx::Visibility::Collapsed);
    canvas.Children().Append(statusTitle);
    controls::TextBlock statusDetail;
    statusDetail.Visibility(wx::Visibility::Collapsed);
    canvas.Children().Append(statusDetail);
    shapes::Rectangle statusUnderline;
    statusUnderline.Visibility(wx::Visibility::Collapsed);
    canvas.Children().Append(statusUnderline);

    controls::TextBlock noticeChevron;
    noticeChevron.Visibility(wx::Visibility::Collapsed);
    noticeChevron.TextAlignment(wx::TextAlignment::Center);
    canvas.Children().Append(noticeChevron);
    controls::TextBlock noticeHeading;
    noticeHeading.Visibility(wx::Visibility::Collapsed);
    canvas.Children().Append(noticeHeading);
    controls::StackPanel noticeRows;
    controls::ScrollViewer noticeScroll;
    noticeScroll.Visibility(wx::Visibility::Collapsed);
    noticeScroll.VerticalScrollBarVisibility(
        controls::ScrollBarVisibility::Auto);
    noticeScroll.HorizontalScrollBarVisibility(
        controls::ScrollBarVisibility::Disabled);
    noticeScroll.Content(noticeRows);
    canvas.Children().Append(noticeScroll);


    controls::Border clipboardFrame;
    clipboardFrame.Visibility(wx::Visibility::Collapsed);
    controls::Image clipboardImage;
    clipboardImage.Stretch(media::Stretch::Uniform);
    clipboardFrame.Child(clipboardImage);
    canvas.Children().Append(clipboardFrame);
    controls::TextBlock clipboardCaption;
    clipboardCaption.Visibility(wx::Visibility::Collapsed);
    canvas.Children().Append(clipboardCaption);

    controls::Viewbox viewbox;
    viewbox.Stretch(media::Stretch::Fill);
    viewbox.Child(canvas);
    card.Child(viewbox);
    state.source.Content(card);
    state.card = card;
    state.canvas = canvas;
    state.viewbox = viewbox;
    state.icon = icon;
    state.track = track;
    state.fill = fill;
    state.fillClip = fillClip;
    state.thumb = thumb;
    state.value = value;
    state.statusTile = statusTile;
    state.statusGlyph = statusGlyph;
    state.statusTitle = statusTitle;
    state.statusDetail = statusDetail;
    state.statusUnderline = statusUnderline;
    state.noticeChevron = noticeChevron;
    state.noticeHeading = noticeHeading;
    state.noticeRows = noticeRows;
    state.noticeScroll = noticeScroll;
    state.clipboardFrame = clipboardFrame;
    state.clipboardImage = clipboardImage;
    state.clipboardCaption = clipboardCaption;
    canvas.PointerPressed([&state](auto const&, const xinput::PointerRoutedEventArgs& e) {
        PointerPressed(state, e);
    });
    canvas.PointerMoved([&state](auto const&, const xinput::PointerRoutedEventArgs& e) {
        PointerMoved(state, e);
    });
    canvas.PointerReleased([&state](auto const&, const xinput::PointerRoutedEventArgs& e) {
        PointerReleased(state, e);
    });
    canvas.PointerCanceled([&state](auto const&, auto const&) {
        PointerCancelled(state);
    });
    canvas.PointerCaptureLost([&state](auto const&, auto const&) {
        PointerCancelled(state);
    });
    canvas.PointerWheelChanged([&state](auto const&, const xinput::PointerRoutedEventArgs& e) {
        PointerWheel(state, e);
    });
    canvas.PointerEntered([&state](auto const&, auto const&) {
        ArmInteractionTimer(state, true);
    });
    canvas.PointerExited([&state](auto const&, auto const&) {
        if (!state.pointerActive) ArmInteractionTimer(state, false);
    });
}
void CreateSurface(State& state, HINSTANCE instance) {
    state.host = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        kClass, L"", WS_POPUP, 0, 0, kWidth, kHeight,
        nullptr, nullptr, instance, &state);
    if (!state.host)
        winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));

    // XAML Border owns configurable corner radius; avoid double-clipping.
    const DWM_WINDOW_CORNER_PREFERENCE corner = DWMWCP_DONOTROUND;
    const COLORREF noBorder = DWMWA_COLOR_NONE;
    const HRESULT rounded = DwmSetWindowAttribute(
        state.host, DWMWA_WINDOW_CORNER_PREFERENCE,
        &corner, sizeof(corner));
    const HRESULT border = DwmSetWindowAttribute(
        state.host, DWMWA_BORDER_COLOR, &noBorder, sizeof(noBorder));
    // The non-layered Win32 host extends glass behind the transparent
    // Island; the XAML Border provides the only visible card background.
    const MARGINS glass{-1, -1, -1, -1};
    const HRESULT frame = DwmExtendFrameIntoClientArea(state.host, &glass);
    Wh_Log(L"XAML v1.0.24: rounded=0x%08lX border=0x%08lX frame=0x%08lX",
        static_cast<unsigned long>(rounded),
        static_cast<unsigned long>(border),
        static_cast<unsigned long>(frame));

    state.source = hosting::DesktopWindowXamlSource{};
    ComPtr<IDesktopWindowXamlSourceNative> interop;
    winrt::check_hresult(winrt::get_unknown(state.source)->
        QueryInterface(kInteropIID,
            reinterpret_cast<void**>(interop.GetAddressOf())));
    winrt::check_hresult(interop->AttachToWindow(state.host));
    winrt::check_hresult(interop->get_WindowHandle(&state.island));
    if (!state.island) winrt::throw_hresult(E_POINTER);
    if (!SetWindowPos(state.island, nullptr, 0, 0, kWidth, kHeight,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_SHOWWINDOW))
        winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));
    CreateContent(state);
}

void CloseSurface(State& state) {
    HideSurface(state);
    state.clipboardCaption = nullptr;
    state.clipboardImage = nullptr;
    state.clipboardFrame = nullptr;
    state.noticeScroll = nullptr;
    state.noticeRows = nullptr;
    state.noticeHeading = nullptr;
    state.noticeChevron = nullptr;
    state.statusUnderline = nullptr;
    state.statusDetail = nullptr;
    state.statusTitle = nullptr;
    state.statusGlyph = nullptr;
    state.statusTile = nullptr;
    state.thumb = nullptr;
    state.fillClip = nullptr;
    state.fill = nullptr;
    state.track = nullptr;
    state.value = nullptr;
    state.icon = nullptr;
    state.canvas = nullptr;
    state.viewbox = nullptr;
    state.card = nullptr;
    if (state.source) {
        try { state.source.Content(nullptr); state.source.Close(); }
        catch (...) { Wh_Log(L"XAML v1.0.24: island close failed"); }
        state.source = nullptr;
    }
    state.island = nullptr;
    if (state.host) DestroyWindow(state.host);
    state.host = nullptr;
}

// The primary STA HWND is the dispatcher. DDC uses one HWND and Island
// per *physical* target. Every update is a complete snapshot batch,
// so removed/unresolved targets do not retain stale visible windows.
void DeliverPending(State& root) {
    std::vector<Snapshot> batch;
    AcquireSRWLockExclusive(&g_snapshotLock);
    batch.swap(g_pending);
    ReleaseSRWLockExclusive(&g_snapshotLock);
    if (batch.empty()) return;

    const bool ddc = batch.front().kind == LevelKind::DdcBrightness;
    if (!ddc) {
        for (auto& peer : root.peers) HideSurface(*peer.second);
        DrawSnapshot(root, batch.back());
        return;
    }
    HideSurface(root);
    std::unordered_set<std::wstring> requested;
    for (const auto& snap : batch) {
        if (snap.key.empty()) continue;
        requested.insert(snap.key);
        auto found = root.peers.find(snap.key);
        if (found == root.peers.end()) {
            auto fresh = std::make_unique<State>();
            try {
                CreateSurface(*fresh, GetModuleHandleW(nullptr));
            } catch (const winrt::hresult_error& ex) {
                Wh_Log(L"XAML v1.0.24: DDC target create failed 0x%08lX",
                    static_cast<unsigned long>(ex.code()));
                CloseSurface(*fresh);
                continue;
            }
            found = root.peers.emplace(snap.key, std::move(fresh)).first;
        }
        DrawSnapshot(*found->second, snap);
    }
    // Reclaim no-longer-active DDC Island resources instead of keeping
    // every monitor ever attached alive for Explorer's entire lifetime.
    for (auto it = root.peers.begin(); it != root.peers.end();) {
        if (requested.find(it->first) == requested.end()) {
            CloseSurface(*it->second);
            it = root.peers.erase(it);
        } else ++it;
    }
}

void TryEnableIslandTransparency() {
    // Official IXamlSourceTransparency applies to every Island on the
    // current XAML STA. Log QI failure; do not silently claim opacity works.
    try {
        auto currentWindow = wx::Window::Current();
        if (!currentWindow) {
            Wh_Log(L"XAML v1.0.24: Window.Current unavailable for transparency");
            return;
        }
        ComPtr<IXamlSourceTransparency> transparency;
        HRESULT hr = winrt::get_unknown(currentWindow)->QueryInterface(
            kTransparencyIID,
            reinterpret_cast<void**>(transparency.GetAddressOf()));
        if (SUCCEEDED(hr) && transparency)
            hr = transparency->put_IsBackgroundTransparent(1);
        Wh_Log(L"XAML v1.0.24: Island transparency HRESULT=0x%08lX",
            static_cast<unsigned long>(hr));
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"XAML v1.0.24: transparency initialization exception 0x%08lX",
            static_cast<unsigned long>(ex.code()));
    }
}

DWORD WINAPI ThreadProc(void*) {
    State root;
    MSG msg{};
    bool apartment = false, registered = false;
    const HINSTANCE instance = GetModuleHandleW(nullptr);
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    g_threadId.store(GetCurrentThreadId(), std::memory_order_release);
    try {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
        apartment = true;
        if (!g_stopping.load()) {
            WNDCLASSEXW wc{sizeof(wc)};
            wc.lpfnWndProc = WndProc;
            wc.hInstance = instance;
            wc.hbrBackground = nullptr; // Don't paint opaque host behind XAML.
            wc.lpszClassName = kClass;
            registered = RegisterClassExW(&wc) != 0;
            if (!registered)
                winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));

            root.manager =
                hosting::WindowsXamlManager::InitializeForCurrentThread();
            if (!g_stopping.load()) {
                CreateSurface(root, instance);
                // Window.Current is available once the first Island has
                // been created; the interface applies to the entire STA.
                TryEnableIslandTransparency();
                g_ready.store(root.host, std::memory_order_release);
                Wh_Log(L"XAML v1.0.24: renderer ready (per-display DDC)");
                while (!g_stopping.load() &&
                       GetMessageW(&msg, nullptr, 0, 0) > 0) {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
            }
        }
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"XAML v1.0.24: startup failed 0x%08lX (%s)",
               static_cast<unsigned long>(ex.code()), ex.message().c_str());
        g_failed.store(true);
    } catch (...) {
        Wh_Log(L"XAML v1.0.24: unexpected startup exception");
        g_failed.store(true);
    }
    g_ready.store(nullptr, std::memory_order_release);
    for (auto& peer : root.peers) CloseSurface(*peer.second);
    root.peers.clear(); // Release peer WinRT refs while STA is still alive.
    CloseSurface(root);
    if (root.manager) {
        try { root.manager.Close(); }
        catch (...) { Wh_Log(L"XAML v1.0.24: manager close failed"); }
        root.manager = nullptr;
    }
    if (registered) UnregisterClassW(kClass, instance);
    if (apartment) winrt::uninit_apartment();
    g_threadId.store(0, std::memory_order_release);
    return 0;
}
void Start() {
    std::lock_guard<std::mutex> guard(g_startLock);
    if (g_thread || g_stopping.load() || g_failed.load()) return;
    g_thread = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
    if (!g_thread) {
        g_failed.store(true);
        Wh_Log(L"XAML v1.0.24: STA creation failed (%lu)", GetLastError());
    }
}
bool ShowBatch(const std::vector<Snapshot>& snapshots) {
    const HWND hwnd = g_ready.load(std::memory_order_acquire);
    if (!hwnd || g_stopping.load() || g_failed.load() ||
        snapshots.empty()) return false;
    AcquireSRWLockExclusive(&g_snapshotLock);
    g_pending = snapshots;
    ReleaseSRWLockExclusive(&g_snapshotLock);
    return PostMessageW(hwnd, kShowMessage, 0, 0) != FALSE;
}
bool Show(const Snapshot& snapshot) {
    return ShowBatch(std::vector<Snapshot>{snapshot});
}

void Hide() {
    const HWND hwnd = g_ready.load(std::memory_order_acquire);
    if (hwnd) PostMessageW(hwnd, kHideMessage, 0, 0);
}
void Stop() {
    std::lock_guard<std::mutex> guard(g_startLock);
    g_stopping.store(true);
    const HWND hwnd = g_ready.exchange(nullptr);
    if (hwnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    const DWORD id = g_threadId.load(std::memory_order_acquire);
    if (id) PostThreadMessageW(id, WM_QUIT, 0, 0);
    if (g_thread) {
        // Do not unload executing code. Shutdown of legacy XAML may block.
        WaitForSingleObject(g_thread, INFINITE);
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
}
} // namespace xaml_osd

constexpr WCHAR kWindowClass[] = L"WH.FluentOSD.XamlTest.01E7AFB2";
constexpr ULONG_PTR kCopyDataTag = 0x1E7AFB3;
constexpr UINT_PTR kHideTimer = 320;
constexpr UINT_PTR kFadeTimer = 321;
constexpr UINT_PTR kEventBatchTimer = 322;
constexpr UINT_PTR kDdcBatchTimer = 324;
constexpr UINT kDdcBatchDelayMs = 90;
constexpr UINT_PTR kMediaAnimationTimer = 323;
constexpr UINT kMediaAnimationIntervalMs = 100;
constexpr ULONGLONG kMediaFeedbackMs = 240;
constexpr ULONGLONG kMediaRefreshIntervalMs = 3000;
constexpr UINT kBrightnessWheelResultMessage = WM_APP + 326;
constexpr UINT kBluetoothQueueMessage = WM_APP + 327;
constexpr UINT kBluetoothConfigMessage = WM_APP + 328;
constexpr int kMaxMixerOutputDevices = 64;
constexpr float kOutputPickerTop = 10.0f;
constexpr float kOutputPickerHeight = 28.0f;
constexpr float kOutputPickerMenuTop = 42.0f;
constexpr float kOutputPickerRowHeight = 30.0f;
constexpr int kOutputPickerMaxRows = 4;
constexpr int kWheelStepPercent = 5;  // One standard notch; leave high-res deltas accumulated.
constexpr UINT kNativeOsdMessage = WM_APP + 320;
constexpr UINT kMediaUpdateMessage = WM_APP + 321;
constexpr UINT kLockToggleMessage = WM_APP + 322;
constexpr UINT kAudioRefreshMessage = WM_APP + 323;
constexpr UINT kNetworkNoticeMessage = WM_APP + 324;
constexpr UINT kNativeExtraMessage = WM_APP + 325;
constexpr DWORD kEventMagic = 0x54434444; // 'DDCT', private wire format

enum class Kind : int {
    Volume, Brightness, Keyboard, Airplane, Camera, Microphone,
    Text, Desktop, Count
};

enum class DurationKind : int {
    Volume, Media, NativeBrightness, DdcBrightness, NativeEvents, LockKeys,
    Clipboard, Devices, Network, Interactive, Count
};
enum class NoticeCategory { Usb, Bluetooth, Network };
enum class NoticeIcon { Clipboard, Usb, Bluetooth, Network };
enum class NoticeAction { Connected, Disconnected, Removed, NetworkChanged };
enum class PanelMode { None, Media, Mixer, Details };
enum class PopupKind { DdcBrightness, NativeBrightness, NativeVolume, NativeEvent, LockStatus, Notification };
enum class FlyoutDirection { Left, Right, Up, Down };

// Documented signatures of the widely used *undocumented* Windows
// IPolicyConfig ABI. Do not share this with ordinary Core Audio code.
// The vtable order is important and must be checked on Windows updates.
struct IPolicyConfigEndpointSwitch : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetMixFormat(PCWSTR, WAVEFORMATEX**) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetDeviceFormat(PCWSTR, INT, WAVEFORMATEX**) = 0;
    virtual HRESULT STDMETHODCALLTYPE ResetDeviceFormat(PCWSTR) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetDeviceFormat(PCWSTR, WAVEFORMATEX*, WAVEFORMATEX*) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetProcessingPeriod(PCWSTR, INT, PINT64, PINT64) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetProcessingPeriod(PCWSTR, PINT64) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetShareMode(PCWSTR, void*) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetShareMode(PCWSTR, void*) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetPropertyValue(PCWSTR, const PROPERTYKEY&, PROPVARIANT*) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetPropertyValue(PCWSTR, const PROPERTYKEY&, PROPVARIANT*) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetDefaultEndpoint(PCWSTR, ERole) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetEndpointVisibility(PCWSTR, INT) = 0;
};

// --- Immutable IDs, limits and drawing geometry ---
constexpr GUID kIUiSettings3 = {
    0x03021be4, 0x5254, 0x4781,
    {0x81, 0x94, 0x51, 0x68, 0xf7, 0xd0, 0x6d, 0x7b}
};
constexpr GUID kUsbDeviceInterface = {0xa5dcbf10,0x6530,0x11d2,
    {0x90,0x1f,0x00,0xc0,0x4f,0xb9,0x51,0xed}};
constexpr WCHAR kUiSettingsRuntimeClass[] = L"Windows.UI.ViewManagement.UISettings";
// Undocumented PolicyConfig: isolated to the explicit user-requested
// Windows default playback endpoint switch, never used while enumerating.
constexpr GUID kPolicyConfigClsid = {0x870af99c, 0x171d, 0x4f9e,
    {0xaf,0x0d,0xe6,0x3d,0xf4,0x0c,0x2b,0xc9}};
constexpr GUID kPolicyConfigIid = {0xf8679f50, 0x850a, 0x41cf,
    {0x9c,0x72,0x43,0x0f,0x29,0x02,0x90,0xc8}};
constexpr PROPERTYKEY kAudioDeviceFriendlyName = {{0xa45c254e,0xdf1c,0x4efd,
    {0x80,0x20,0x67,0xd1,0x46,0xa8,0x50,0xe0}}, 14};
constexpr GUID kWmiLocatorClsid = {0x4590f811, 0x1d3a, 0x11d0,
    {0x89, 0x1f, 0x00, 0xaa, 0x00, 0x4b, 0x2e, 0x24}};
constexpr GUID kWmiLocatorIid = {0xdc12a687, 0x737f, 0x11cf,
    {0x88, 0x4d, 0x00, 0xaa, 0x00, 0x4b, 0x2e, 0x24}};
constexpr size_t kMaxMirrorOutputs = 7; // At most 8 displays including master.
constexpr size_t kMaxDdcTargets = 16;
constexpr wchar_t kConnectedProperty[] = L"System.Devices.Aep.IsConnected";
constexpr size_t kMaxQueuedEvents = 128;
constexpr size_t kMaxKnownDevices = 256;
constexpr size_t kMaxMediaTextChars = 4096;
constexpr INT64 kMaxMediaLag100ns = INT64(24) * 60 * 60 * 10000000;
constexpr uint32_t kMaxArtworkBytes = 1024u * 1024u;
constexpr size_t kMaxMediaSessions = 32; // Bound the UI-only GSMTC selector.
constexpr DWORD kMaxVcpValue = 0xFFFF;
// Unified logical canvas for status-only OSDs: lock keys, native events,
// USB, Bluetooth, network and text-only clipboard notices.
constexpr float kStatusNoticeWidth = 296.0f;
constexpr float kStatusNoticeHeight = 92.0f;
constexpr float kStatusIconX = 18.0f;
constexpr float kStatusIconY = 19.0f;
constexpr float kStatusIconSize = 52.0f;
constexpr float kStatusTextX = 84.0f;
constexpr float kClipboardImageCanvasW = 264.0f;
constexpr float kClipboardImageCanvasH = 224.0f;
constexpr float kClipboardImageMaxW = 224.0f;
constexpr float kClipboardImageMaxH = 164.0f;
constexpr float kMixerRowStep = 30.0f;
constexpr float kMixerFirstRowY = 45.0f;
constexpr float kMixerTrackStart = 62.0f;
constexpr float kMixerTrackLength = 216.0f;
constexpr float kMixerTrackHeight = 7.0f;
constexpr int kLockVk[4] = {VK_CAPITAL, VK_NUMLOCK, VK_SCROLL, VK_INSERT};
constexpr int kLogicalWidth = 380;
constexpr int kLogicalHeight = 72;
constexpr float kHorizontalArrowRadius = 12.5f;
constexpr float kVerticalArrowRadius = 11.5f;
constexpr float kArrowHitDiameter = 30.0f;
// Minimum clear gaps between SMTC transport and auxiliary button surfaces.
constexpr float kMediaExtraGroupGap = 10.0f;
constexpr float kMediaExtraStackGap = 8.0f;
constexpr float kTau = 6.28318530718f;

// --- Stable setting key tables (same ordinal as their state arrays) ---
constexpr PCWSTR kNativeHideSettingKeys[] = {
    L"NativeHide.hideNativeVolume", L"NativeHide.hideNativeBrightness", L"NativeHide.hideNativeKeyboardBrightness",
    L"NativeHide.hideNativeAirplane", L"NativeHide.hideNativeCamera", L"NativeHide.hideNativeMicrophone",
    L"NativeHide.hideNativeText", L"NativeHide.hideNativeVirtualDesktop"
};
constexpr PCWSTR kCustomNativeSettingKeys[] = {
    L"CustomOSD.Switches.showCustomVolume",
    L"CustomOSD.Switches.showCustomBrightness",
    L"CustomOSD.Switches.showCustomKeyboardBrightness",
    L"CustomOSD.Switches.showCustomAirplane",
    L"CustomOSD.Switches.showCustomCamera",
    L"CustomOSD.Switches.showCustomMicrophone",
    L"CustomOSD.Switches.showCustomText",
    L"CustomOSD.Switches.showCustomVirtualDesktop"
};
constexpr PCWSTR kDurationSettingKeys[] = {
    L"volumeDurationMs", L"mediaDurationMs",
    L"nativeBrightnessDurationMs", L"ddcBrightnessDurationMs",
    L"nativeEventDurationMs", L"lockDurationMs", L"clipboardDurationMs",
    L"deviceDurationMs", L"networkDurationMs",
    L"interactiveDurationMs"
};
constexpr PCWSTR kLockSettingKeys[] = {
    L"CustomOSD.Switches.LockKeys.showCapsLockOsd", L"CustomOSD.Switches.LockKeys.showNumLockOsd",
    L"CustomOSD.Switches.LockKeys.showScrollLockOsd", L"CustomOSD.Switches.LockKeys.showInsertOsd"
};

static_assert(ARRAYSIZE(kNativeHideSettingKeys) == static_cast<size_t>(Kind::Count));
static_assert(ARRAYSIZE(kCustomNativeSettingKeys) == static_cast<size_t>(Kind::Count));
static_assert(ARRAYSIZE(kDurationSettingKeys) == static_cast<size_t>(DurationKind::Count));
static_assert(ARRAYSIZE(kLockSettingKeys) == 4);

// --- Input glyphs and labels (custom string table follows) ---
constexpr PCWSTR kLockDisplayNames[] = {L"Caps Lock", L"Num Lock", L"Scroll Lock", L"Insert"};
constexpr PCWSTR kLockGlyphs[] = {L"A", L"1", L"↕", L"Ins"};

// Localized custom OSD strings. Event identities do not depend on UI text.
enum class OsdText : size_t {
    KeyboardBacklight,
    Level,
    AirplaneMode,
    Enabled,
    Disabled,
    CameraAccess,
    Camera,
    Allowed,
    Blocked,
    Microphone,
    Unmuted,
    Muted,
    StatusChanged,
    VirtualDesktop,
    DesktopSwitched,
    SystemNotice,
    SystemStatus,
    Device,
    CountUnit,
    ViewDetails,
    Clipboard,
    ContentCopied,
    ImageCopied,
    ClipboardImage,
    TextCopied,
    ClipboardText,
    EmptyText,
    FilesCopied,
    ClipboardFiles,
    UsbDevice,
    Bluetooth,
    BluetoothDevice,
    NetworkInterface,
    Network,
    Connected,
    Disconnected,
    Removed,
    NetworkChanged,
    WindowsNetwork,
    EventDetails,
    VolumeMixer,
    MediaPlayback,
    SystemSounds,
    ProcessPrefix,
    On,
    Off,
    AudioOutput,
    AudioSwitchFailed,
    NoAudioOutputs,
    Count
};
struct LocalizedText { PCWSTR en; PCWSTR zhTw; };
constexpr LocalizedText kLocalizedText[] = {
    {L"Keyboard backlight", L"鍵盤背光"}, // KeyboardBacklight
    {L"Level ", L"等級 "}, // Level
    {L"Airplane mode", L"飛航模式"}, // AirplaneMode
    {L"Enabled", L"已開啟"}, // Enabled
    {L"Disabled", L"已關閉"}, // Disabled
    {L"Camera access", L"相機存取權限"}, // CameraAccess
    {L"Camera", L"相機"}, // Camera
    {L"Allowed", L"已允許"}, // Allowed
    {L"Blocked", L"已封鎖"}, // Blocked
    {L"Microphone", L"麥克風"}, // Microphone
    {L"Unmuted", L"已解除靜音"}, // Unmuted
    {L"Muted", L"已靜音"}, // Muted
    {L"Status changed", L"狀態已變更"}, // StatusChanged
    {L"Virtual desktop", L"虛擬桌面"}, // VirtualDesktop
    {L"Desktop switched", L"桌面已切換"}, // DesktopSwitched
    {L"System notice", L"系統提示"}, // SystemNotice
    {L"System status", L"系統狀態"}, // SystemStatus
    {L"device", L"裝置"}, // Device
    {L"events", L"個"}, // CountUnit
    {L"Click to view details", L"點擊查看詳細資訊"}, // ViewDetails
    {L"Clipboard", L"剪貼簿"}, // Clipboard
    {L"Content copied", L"內容已複製"}, // ContentCopied
    {L"Image copied", L"已複製圖片"}, // ImageCopied
    {L"Clipboard image", L"剪貼簿圖片"}, // ClipboardImage
    {L"Text copied", L"已複製文字"}, // TextCopied
    {L"Clipboard text", L"剪貼簿文字"}, // ClipboardText
    {L"Empty text", L"空白文字"}, // EmptyText
    {L"Files copied", L"已複製檔案"}, // FilesCopied
    {L"Clipboard file selection", L"剪貼簿檔案選取"}, // ClipboardFiles
    {L"USB device", L"USB 裝置"}, // UsbDevice
    {L"Bluetooth", L"藍牙"}, // Bluetooth
    {L"Bluetooth device", L"藍牙裝置"}, // BluetoothDevice
    {L"Network interface", L"網路介面"}, // NetworkInterface
    {L"Network", L"網路"}, // Network
    {L"Connected", L"已連接"}, // Connected
    {L"Disconnected", L"已中斷"}, // Disconnected
    {L"Removed", L"已移除"}, // Removed
    {L"Connectivity changed", L"連線狀態已變更"}, // NetworkChanged
    {L"Windows network connection", L"Windows 網路連線"}, // WindowsNetwork
    {L"Event details", L"事件詳細資訊"}, // EventDetails
    {L"Volume mixer", L"音量混音器"}, // VolumeMixer
    {L"Media playback", L"媒體播放"}, // MediaPlayback
    {L"System sounds", L"系統音效"}, // SystemSounds
    {L"Process ", L"處理程序 "}, // ProcessPrefix
    {L"On", L"開啟"}, // On
    {L"Off", L"關閉"}, // Off
    {L"Output", L"輸出裝置"}, // AudioOutput
    {L"Switch failed", L"切換失敗"}, // AudioSwitchFailed
    {L"No playback devices", L"沒有可用的播放裝置"}, // NoAudioOutputs
};
static_assert(ARRAYSIZE(kLocalizedText) == static_cast<size_t>(OsdText::Count));
// ============================================================
// Shared declarations: payload types, API facades and states
// ============================================================
// A transient native OSD event is not the underlying hardware state.
struct NativeEventInfo {
    Kind kind = Kind::Keyboard;
    int value = 0;
    int variant = 0; // 1 = camera access (not camera activity)
    std::wstring text;
};

struct PhysicalInfo {
    WCHAR device[CCHDEVICENAME]{}; // GDI display, e.g. \\.\DISPLAY2
    DWORD physicalIndex = 0;
    DWORD minimum = 0;
    DWORD maximum = 0; // 0 = unknown, do not pretend raw=percent
};

// Wire format: no process-local HANDLE or pointer crosses WM_COPYDATA.
struct BrightnessEvent {
    DWORD magic;
    WCHAR device[CCHDEVICENAME];
    DWORD physicalIndex;
    DWORD value;
    DWORD minimum;
    DWORD maximum;
    DWORD producerPid;
};
static_assert(sizeof(BrightnessEvent) < 512);
// Twinkle Tray emits an independent write for each physical monitor.
// Keep a per-target batch: a single "latest" slot silently discards other
// monitors' values, and a mirrored image duplicates the wrong percentage.
struct DdcTargetState {
    BrightnessEvent event{};
    ULONGLONG expiresAt = 0;
};

struct BrightnessWheelTask {
    bool native = false;
    DWORD generation = 0;
    int value = 0;                // Native: 0..100; DDC: device raw value
    BrightnessEvent monitor{};   // Only display ID/physical index, no handles
};

// UISettings3 GetColorValue is read-only; the IID matches WinRT metadata.
struct UiColor {
    BYTE a, r, g, b;
};
struct IUiSettings3Raw : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetIids(ULONG*, GUID**) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetRuntimeClassName(void**) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetTrustLevel(int*) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetColorValue(int, UiColor*) = 0;
};
using RoInitialize_t = HRESULT(WINAPI*)(int);
using RoUninitialize_t = void(WINAPI*)();
using WindowsCreateString_t = HRESULT(WINAPI*)(PCWSTR, UINT, void**);
using WindowsDeleteString_t = HRESULT(WINAPI*)(void*);
using RoActivateInstance_t = HRESULT(WINAPI*)(void*, IUnknown**);

// --- Settings / UI / device state ---
std::atomic<int> g_displayLanguage{0}; // 0=Auto, 1=English, 2=zh-TW
std::atomic<bool> g_hideAllNativeOsd{false};
std::atomic<bool> g_hide[static_cast<int>(Kind::Count)]{};
std::atomic<bool> g_showCustomNative[static_cast<int>(Kind::Count)]{};
std::atomic<bool> g_xamlForMigrated{false};
std::atomic<bool> g_showDdcBrightness{false};
std::atomic<bool> g_verticalVolumeBrightness{true};
std::atomic<bool> g_fromExplorer{true};
std::atomic<bool> g_fromTwinkle{true};
std::atomic<int> g_vcpCode{16};

std::atomic<int> g_globalDurationMs{3000};
std::atomic<bool> g_individualDurations{false};
std::atomic<int> g_durationOverrides[static_cast<int>(DurationKind::Count)]{};
// Only the dedicated OSD UI thread reads/writes this current category.
DurationKind g_activeDurationKind = DurationKind::Volume;

std::atomic<int> g_ddcTheme{0};
std::atomic<int> g_ddcSizePercent{75};
// Independent logical dimensions; global DPI and size % are applied later.
std::atomic<int> g_horizontalOsdWidth{380};
std::atomic<int> g_horizontalOsdHeight{72};
std::atomic<int> g_verticalOsdWidth{72};
std::atomic<int> g_verticalOsdHeight{200};
std::atomic<int> g_horizontalSmtcHeight{200};
std::atomic<int> g_horizontalMixerHeight{200};
std::atomic<int> g_verticalSmtcWidth{380};
std::atomic<int> g_verticalMixerWidth{380};
std::atomic<bool> g_ddcBorderless{true};
std::atomic<bool> g_showSmtcOnVolume{false};
std::atomic<bool> g_showMediaArtwork{true};
std::atomic<bool> g_showMediaControls{true};
std::atomic<int> g_mediaControlSizePercent{100};
std::atomic<bool> g_controlButtonSquare{false};
std::atomic<int> g_controlButtonCornerRadius{6};
std::atomic<bool> g_showMixerArrow{false};
std::atomic<int> g_mixerMaxRows{6};
std::atomic<bool> g_showLockKeys[4]{};
std::atomic<int> g_innerPadding{14};
std::atomic<bool> g_showClipboardOsd{false};
std::atomic<bool> g_clipboardTextPreview{false};
std::atomic<bool> g_clipboardImagePreview{true};
std::atomic<int> g_clipboardChars{48};
std::atomic<bool> g_showUsbEvents{false};
std::atomic<bool> g_showBluetoothEvents{false};
std::atomic<bool> g_showNetworkEvents{false};
std::atomic<bool> g_fadeEnabled{true};
std::atomic<int> g_fadeDuration{160};
// Layout and palette options. Values are atomic because settings can be
// reloaded outside the Explorer OSD UI thread.
std::atomic<int> g_accentMode{0};
std::atomic<DWORD> g_customAccent{0};
std::atomic<bool> g_validCustomAccent{false};
std::atomic<int> g_backgroundMode{0};
std::atomic<DWORD> g_customBackground{0};
std::atomic<bool> g_validCustomBackground{false};
std::atomic<int> g_textMode{0};
std::atomic<DWORD> g_customText{0};
std::atomic<bool> g_validCustomText{false};
std::atomic<int> g_trackMode{0};
std::atomic<DWORD> g_customTrack{0};
std::atomic<bool> g_validCustomTrack{false};
std::atomic<int> g_backgroundOpacity{96};
std::atomic<int> g_cornerRadius{17};
std::atomic<int> g_barThickness{8};
std::atomic<int> g_thumbDiameter{11};
std::atomic<int> g_fontSize{15};
std::atomic<int> g_iconSize{16};
std::atomic<int> g_iconStrokeWidth{2};
std::atomic<bool> g_showSun{true};
std::atomic<bool> g_showValue{true};
// 0=source, 1=primary, 2=selected DISPLAYn, 3=all screens
std::atomic<int> g_displayOutputMode{0};
std::atomic<int> g_displayOutputNumber{1};
std::atomic<int> g_position{5};
std::atomic<int> g_offsetX{0};
std::atomic<int> g_offsetY{0};

bool g_isExplorer = false;
HMODULE g_ddcDll = nullptr;
HMODULE g_confirmatorDll = nullptr;
std::atomic<bool> g_loggedUnmapped{false};
HANDLE g_uiThread = nullptr;
HANDLE g_uiReady = nullptr;
DWORD g_uiThreadId = 0;
HWND g_receiveWnd = nullptr;
HWND g_popupWnd = nullptr;
struct MirrorOutput {
    HWND popup = nullptr;
    HWND panel = nullptr;
    HMONITOR monitor = nullptr;
    RECT work{}, monitorBounds{}, popupBounds{};
    float scale = 1.0f;
};
std::vector<MirrorOutput> g_mirrorOutputs; // UI thread only
HWND g_panelWnd = nullptr;
HWND g_arrowWnd = nullptr;
// Hover and press state belong to the Explorer UI thread, like the flyouts.
bool g_arrowHovered = false;
bool g_arrowPressed = false;
HWND g_speakerHitWnd = nullptr; // Hit target above the main-volume speaker.
bool g_speakerPressed = false;  // Dedicated OSD UI thread only.
HWND g_barWheelWnd = nullptr; // Minimal hit surface over the main OSD's bar.
// Owned by the UI thread. The same small surface now supports wheel,
// click-to-position and continuous dragging, without making the OSD opaque.
bool g_mainBarDragging = false;
int g_mainBarDragKind = -1; // static_cast<int>(PopupKind) on mouse-down
// Only the UI thread mutates confirmed/optimistic values.
DWORD g_wheelWriteGeneration = 0;
int g_lastConfirmedNativeBrightness = -1;
DWORD g_lastConfirmedDdcBrightness = 0;
bool g_clipboardListener = false;
HDEVNOTIFY g_usbNotification = nullptr;
HMODULE g_networkDll = nullptr;
HANDLE g_networkNotification = nullptr;
std::atomic<int> g_networkPreviousLevel{-1};
std::atomic<HWND> g_networkReceiver{nullptr};
bool g_fadeActive = false;
bool g_fadeOut = false;
DWORD g_fadeStart = 0;
int g_fadeFrom = 255;
int g_fadeTo = 255;
int g_fadeAlpha = 255;
std::atomic<bool> g_closing{false};
std::wstring g_noticeTitle;
std::wstring g_noticeBody;
NoticeIcon g_noticeIcon = NoticeIcon::Clipboard; // UI thread only.
struct NoticeBatch {
    NoticeCategory category = NoticeCategory::Usb;
    NoticeAction action = NoticeAction::Connected;
    std::vector<std::wstring> names;
    std::unordered_set<std::wstring> identities;
    bool pending = false;
};
NoticeBatch g_noticeBatch;
std::vector<std::wstring> g_noticeDetails;
int g_noticeScroll = 0;
bool g_noticeClickable = false;
std::unordered_map<std::wstring, std::wstring> g_usbNames;
struct NetInterfaceState { std::wstring name; bool connected = false; };
std::unordered_map<std::string, NetInterfaceState> g_networkInterfaces;

// Owned thumbnail, created only when the user enables clipboard previews.
// Its dimensions are bounded before display; never store clipboard data.
HBITMAP g_clipboardThumbnail = nullptr;
DWORD g_usbLastEvent = 0;
WPARAM g_usbLastEventType = 0;

// The SMTC worker never touches HWND/GDI+/CoreAudio objects directly.
struct MediaSnapshot {
    bool available = false;
    bool playing = false;
    uint32_t sessionCount = 0;
    uint32_t selectionSerial = 0; // Distinguish same-app sessions after cycling.
    std::wstring sourceId; // Used only to detect source changes on the UI thread.
    bool canPrevious = false;
    bool canToggle = false;
    bool canNext = false;
    // Standard GSMTC capabilities, independent of player brand.
    bool canShuffle = false, shuffleKnown = false, shuffleActive = false;
    bool canRepeat = false;
    int repeatMode = -1; // Windows MediaPlaybackAutoRepeatMode: 0=None, 1=Track, 2=List
    std::wstring title;
    std::wstring artist;
    std::vector<BYTE> artwork;
    bool hasTimeline = false;
    bool canSeek = false;
    // Media TimeSpan units are 100 ns; Position is reported as of
    // LastUpdatedTime, then converted to the local monotonic tick clock.
    INT64 timelineStart = 0;
    INT64 timelineEnd = 0;
    INT64 timelinePosition = 0;
    ULONGLONG timelineObservedTick = 0;
};
SRWLOCK g_mediaLock = SRWLOCK_INIT;
MediaSnapshot g_mediaPending;
MediaSnapshot g_mediaCurrent;             // Explorer UI thread only
// Keep decoded artwork alive (together with its backing IStream), rather
// than decoding the album cover on every progress-animation frame.
std::vector<BYTE> g_cachedArtworkBytes;
[[clang::no_destroy]] Microsoft::WRL::ComPtr<IStream> g_cachedArtworkStream;
[[clang::no_destroy]] std::unique_ptr<Gdiplus::Bitmap> g_cachedArtwork;
// All media positioning and dragging is owned by Explorer's OSD UI thread.
bool g_mediaSeeking = false;
INT64 g_mediaPreviewPosition = 0;
ULONGLONG g_mediaSeekHoldUntil = 0;
int g_mediaPressedIndex = -1;
bool g_mediaPressedInside = false;
bool g_mediaCyclePressed = false; // Album-cover session selector, UI thread.
bool g_mediaCycleInside = false;
int g_extraPressedAction = 0; // UI thread only, 5=shuffle, 6=repeat
bool g_extraPressedInside = false;
int g_mediaFeedbackIndex = -1;
ULONGLONG g_mediaFeedbackTick = 0;
ULONGLONG g_mediaLastRefreshTick = 0;
HANDLE g_mediaWake = nullptr;
HANDLE g_mediaThread = nullptr;
std::atomic<bool> g_mediaStop{false};
SRWLOCK g_mediaCommandLock = SRWLOCK_INIT;
struct MediaCommand {
    int action = 0;  // 1-3=transport; 4=seek; 5-6=shuffle/repeat; 7=next SMTC session
    INT64 position = 0; // SMTC 100-ns ticks for action 4
};
std::vector<MediaCommand> g_mediaCommands; // Bounded, worker-owned after swap.

PanelMode g_panelMode = PanelMode::None;  // Explorer UI thread only
float g_scale = 1.0f;
int g_panelWidth = 0;
int g_panelHeight = 0;
int g_mixerScroll = 0;
bool g_mixerDrag = false;
int g_mixerMutePressedIndex = -1; // clicked icon; validate again on mouse-up
int g_mixerDragIndex = -1;
struct MixerEntry {
    std::wstring title;
    HICON appIcon = nullptr; // owned; released before clear
    Microsoft::WRL::ComPtr<ISimpleAudioVolume> volume;
    float scalar = 0;
    bool muted = false;
};
[[clang::no_destroy]] std::vector<MixerEntry> g_mixerEntries;    // Explorer UI thread only
[[clang::no_destroy]] Microsoft::WRL::ComPtr<IAudioEndpointVolume> g_mixerMaster;
int g_mixerWheelRemainder = 0;
int g_mixerWheelIndex = -1;
int g_barWheelRemainder = 0;
int g_barWheelKind = -1;
float g_mixerMasterLevel = 0;
bool g_mixerMasterMuted = false;
struct AudioOutputOption { std::wstring id; std::wstring name; };
[[clang::no_destroy]] std::vector<AudioOutputOption> g_mixerOutputOptions; // UI thread only
[[clang::no_destroy]] std::wstring g_mixerOutputId;
bool g_mixerOutputExpanded = false;
bool g_mixerOutputSwitchFailed = false;
int g_mixerOutputScroll = 0;
int g_mixerOutputHoveredRow = -1; // UI thread; index in device list
bool g_mixerOutputHeaderHovered = false;
// Endpoint listener is registered only while the interactive mixer is open.
class MixerOutputNotifications final : public IMMNotificationClient {
    std::atomic<ULONG> refs_{1};
    std::atomic<HWND> target_;
    std::atomic<bool> pending_{false};
    void Notify() {
        HWND hwnd = target_.load(std::memory_order_acquire);
        if (!hwnd || pending_.exchange(true, std::memory_order_acq_rel)) return;
        if (!PostMessageW(hwnd, kAudioRefreshMessage, 0, 0))
            pending_.store(false, std::memory_order_release);
    }
public:
    explicit MixerOutputNotifications(HWND hwnd) : target_(hwnd) {}
    void Stop() { target_.store(nullptr, std::memory_order_release); }
    void ClearPending() { pending_.store(false, std::memory_order_release); }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** object) override {
        if (!object) return E_POINTER;
        *object = nullptr;
        if (IsEqualIID(iid, IID_IUnknown) ||
            IsEqualIID(iid, __uuidof(IMMNotificationClient))) {
            *object = static_cast<IMMNotificationClient*>(this);
            AddRef();
            return S_OK;
        }
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() override { return refs_.fetch_add(1) + 1; }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG left = refs_.fetch_sub(1) - 1;
        if (!left) delete this;
        return left;
    }
    HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role,
                                                     LPCWSTR) override {
        if (flow == eRender && (role == eConsole || role == eMultimedia)) Notify();
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR) override { Notify(); return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR) override { Notify(); return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR, DWORD) override {
        Notify(); return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR,
                                                     const PROPERTYKEY) override {
        return S_OK;
    }
};
[[clang::no_destroy]] Microsoft::WRL::ComPtr<IMMDeviceEnumerator> g_mixerNotifyEnumerator;
[[clang::no_destroy]] Microsoft::WRL::ComPtr<MixerOutputNotifications> g_mixerNotify;
// Hook callback and UI message loop share the same dedicated UI thread.
HHOOK g_lockHook = nullptr;
bool g_lockPressed[4]{};
bool g_lockToggle[4]{};
int g_lastLock = 0;
bool g_lastLockValue = false;

// --- Event state and worker coordination ---
SRWLOCK g_nativeEventLock = SRWLOCK_INIT;
NativeEventInfo g_nativeEventPending;
bool g_nativeEventPosted = false;

SRWLOCK g_handleLock = SRWLOCK_INIT;
std::unordered_map<ULONG_PTR, PhysicalInfo> g_handles;

std::vector<BrightnessEvent> g_ddcBatchEvents;  // UI thread only
std::vector<DdcTargetState> g_ddcTargets;      // UI thread only
bool g_ddcBatchPending = false;
WCHAR g_ddcLastUnresolved[CCHDEVICENAME]{}; // UI thread, log only changed failures
WCHAR g_ddcLastTarget[CCHDEVICENAME]{}; // UI thread, log target transitions

SRWLOCK g_wheelWriteLock = SRWLOCK_INIT;
std::vector<BrightnessWheelTask> g_wheelWritePending; // At most one latest write per physical display.
HANDLE g_wheelWriteWake = nullptr;
HANDLE g_wheelWriteThread = nullptr;
std::atomic<bool> g_wheelWriteStop{false};

HMODULE g_combase = nullptr;               // UI thread only
RoUninitialize_t g_roUninitialize = nullptr;
bool g_roInitialized = false;
IUiSettings3Raw* g_uiSettings = nullptr;    // UI thread only

// --- Active master flyout state (dedicated UI thread) ---
BrightnessEvent g_visible{};  // UI thread only
PopupKind g_popupKind = PopupKind::DdcBrightness; // UI thread only
NativeEventInfo g_nativeEventCurrent;         // UI thread only
int g_nativePercent = 0;                        // UI thread only
bool g_nativePercentKnown = false;              // UI thread only
bool g_nativeMuted = false;                     // UI thread only
int g_width = kLogicalWidth;
int g_height = kLogicalHeight;
ULONG_PTR g_gdiplusToken = 0;

// ============================================================
// Shared helpers: localization, settings, UI state and geometry
// ============================================================

bool UseTraditionalChinese() {
    const int selected = g_displayLanguage.load(std::memory_order_relaxed);
    if (selected == 2) return true;
    if (selected == 1) return false;
    const LANGID lang = GetUserDefaultUILanguage();
    if (PRIMARYLANGID(lang) != LANG_CHINESE) return false;
    const WORD sublanguage = SUBLANGID(lang);
    return sublanguage == SUBLANG_CHINESE_TRADITIONAL ||
           sublanguage == SUBLANG_CHINESE_HONGKONG ||
           sublanguage == SUBLANG_CHINESE_MACAU;
}
PCWSTR Tr(OsdText id) {
    const size_t index = static_cast<size_t>(id);
    if (index >= ARRAYSIZE(kLocalizedText)) return L"";
    return UseTraditionalChinese() ? kLocalizedText[index].zhTw
                                   : kLocalizedText[index].en;
}
UINT OsdDuration(DurationKind kind) {
    if (!g_individualDurations.load(std::memory_order_relaxed))
        return static_cast<UINT>(g_globalDurationMs.load(std::memory_order_relaxed));
    return static_cast<UINT>(g_durationOverrides[static_cast<int>(kind)]
        .load(std::memory_order_relaxed));
}
bool ParseRgbHex(PCWSTR str, DWORD& rgb) {
    if (!str) return false;
    if (*str == L'#') ++str;
    if (wcslen(str) != 6) return false;
    DWORD value = 0;
    for (int i = 0; i < 6; ++i) {
        wchar_t c = str[i];
        int nibble = (c >= L'0' && c <= L'9') ? c - L'0' :
                     (c >= L'a' && c <= L'f') ? c - L'a' + 10 :
                     (c >= L'A' && c <= L'F') ? c - L'A' + 10 : -1;
        if (nibble < 0) return false;
        value = (value << 4) | static_cast<DWORD>(nibble);
    }
    rgb = value;
    return true;
}

void LoadHexSetting(PCWSTR setting, std::atomic<DWORD>& rgb,
                    std::atomic<bool>& valid) {
    PCWSTR input = Wh_GetStringSetting(setting);
    DWORD parsed = 0;
    bool ok = ParseRgbHex(input, parsed);
    Wh_FreeStringSetting(input);
    rgb.store(parsed, std::memory_order_relaxed);
    valid.store(ok, std::memory_order_relaxed);
}
PCWSTR NoticeCategoryLabel(NoticeCategory category) {
    switch (category) {
        case NoticeCategory::Usb: return L"USB";
        case NoticeCategory::Bluetooth: return Tr(OsdText::Bluetooth);
        case NoticeCategory::Network: return Tr(OsdText::Network);
    }
    return L"";
}
PCWSTR NoticeActionLabel(NoticeAction action) {
    switch (action) {
        case NoticeAction::Connected: return Tr(OsdText::Connected);
        case NoticeAction::Disconnected: return Tr(OsdText::Disconnected);
        case NoticeAction::Removed: return Tr(OsdText::Removed);
        case NoticeAction::NetworkChanged: return Tr(OsdText::NetworkChanged);
    }
    return L"";
}
float MixerTrackLength() {
    if (g_panelWidth <= 0 || g_scale <= 0.0f) return kMixerTrackLength;
    const float w = g_panelWidth / g_scale;
    // Keep room at the right for the volume number and scrollbar.
    return std::max(110.0f, w -
        (g_verticalVolumeBrightness.load() ? 124.0f : 120.0f));
}
int MixerVisibleRows() {
    if (g_panelHeight <= 0) return 1;
    const float h = g_panelHeight / g_scale;
    const int byHeight = std::max(1, static_cast<int>((h - 50.0f) / kMixerRowStep));
    return std::min(g_mixerMaxRows.load(), byHeight);
}
int MixerMaximumScroll() {
    return std::max(0, static_cast<int>(g_mixerEntries.size()) + 1 - MixerVisibleRows());
}
void ClampMixerScroll() {
    g_mixerScroll = std::clamp(g_mixerScroll, 0, MixerMaximumScroll());
}
bool IsCustomMode(PCWSTR name) {
    PCWSTR value = Wh_GetStringSetting(name);
    const bool custom = value && _wcsicmp(value, L"custom") == 0;
    Wh_FreeStringSetting(value);
    return custom;
}

int ReadPositionSetting() {
    PCWSTR value = Wh_GetStringSetting(L"CustomOSD.Layout.ddcPosition");
    int result = 5; // topLeft (fallback on missing/unknown setting)
    if (value) {
        if (_wcsicmp(value, L"bottomCenter") == 0) result = 0;
        else if (_wcsicmp(value, L"bottomLeft") == 0) result = 1;
        else if (_wcsicmp(value, L"bottomRight") == 0) result = 2;
        else if (_wcsicmp(value, L"topCenter") == 0) result = 3;
        else if (_wcsicmp(value, L"center") == 0) result = 4;
        else if (_wcsicmp(value, L"topLeft") == 0) result = 5;
        else if (_wcsicmp(value, L"topRight") == 0) result = 6;
        else if (_wcsicmp(value, L"centerLeft") == 0) result = 7;
        else if (_wcsicmp(value, L"centerRight") == 0) result = 8;
    }
    Wh_FreeStringSetting(value);
    return result;
}

template <size_t N>
void LoadBoolSettings(std::atomic<bool> (&target)[N],
                      PCWSTR const (&keys)[N]) {
    for (size_t i = 0; i < N; ++i)
        target[i].store(Wh_GetIntSetting(keys[i]) != 0);
}

// Preserve 32-bit top-down BI_RGB backing storage for premultiplied BGRA.
HBITMAP CreateArgbDib(HDC screen, int width, int height, void** pixels) {
    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    return CreateDIBSection(screen, &bitmapInfo, DIB_RGB_COLORS,
                            pixels, nullptr, 0);
}

BYTE OsdBackgroundAlpha() {
    return static_cast<BYTE>((g_backgroundOpacity.load() * 255 + 50) / 100);
}

// A single direction and anchor rule drives panel placement and chevrons.
// --- Common placement, sizing and monitor identity ---
float MainLogicalWidth() {
    return static_cast<float>(g_verticalVolumeBrightness.load()
        ? g_verticalOsdWidth.load() : g_horizontalOsdWidth.load());
}
float MainLogicalHeight() {
    return static_cast<float>(g_verticalVolumeBrightness.load()
        ? g_verticalOsdHeight.load() : g_horizontalOsdHeight.load());
}
float MainCenterY() { return MainLogicalHeight() / 2.0f - 2.0f; }
float HorizontalChevronX() { return MainLogicalWidth() - 33.0f; }
float HorizontalChevronY() { return MainCenterY(); }
float VerticalChevronX() { return MainLogicalWidth() / 2.0f; }
float VerticalChevronY() { return MainLogicalHeight() - 25.0f; }
FlyoutDirection InverseDirection(FlyoutDirection dir) {
    switch (dir) {
        case FlyoutDirection::Left: return FlyoutDirection::Right;
        case FlyoutDirection::Right: return FlyoutDirection::Left;
        case FlyoutDirection::Up: return FlyoutDirection::Down;
        case FlyoutDirection::Down: return FlyoutDirection::Up;
    }
    return FlyoutDirection::Right;
}
bool PositionIsTop(int pos) {
    return pos == 3 || pos == 5 || pos == 6;
}
bool PositionIsBottom(int pos) {
    return pos == 0 || pos == 1 || pos == 2;
}
bool PositionIsLeft(int pos) {
    return pos == 1 || pos == 5 || pos == 7;
}
bool PositionIsRight(int pos) {
    return pos == 2 || pos == 6 || pos == 8;
}
// Use physical display center on centered axes; work area is reserved for
// edge-anchored axes so a side/top taskbar cannot skew the visual midpoint.
bool PositionCentersX(int pos) {
    return pos == 0 || pos == 3 || pos == 4; // bottom/top center, center
}
bool PositionCentersY(int pos) {
    return pos == 4 || pos == 7 || pos == 8; // center, center left/right
}
int ClampPopupAxis(int coordinate, int size, const RECT& limits,
                   bool horizontal) {
    const int low = horizontal ? limits.left : limits.top;
    const int high = horizontal ? limits.right : limits.bottom;
    return std::clamp(coordinate, low, std::max(low, high - size));
}

// Use the SAME direction and panel attachment for actual UI placement and
// centered composite placement, rather than centering the narrow main OSD
// and letting an attached panel shift the perceived center.
FlyoutDirection DirectionForPopup(const RECT& main, const RECT& work,
                                  int pos, bool vertical) {
    if (vertical) {
        if (PositionIsLeft(pos)) return FlyoutDirection::Right;
        if (PositionIsRight(pos)) return FlyoutDirection::Left;
        const int freeRight = work.right - main.right;
        const int freeLeft = main.left - work.left;
        return freeRight >= freeLeft ? FlyoutDirection::Right
                                     : FlyoutDirection::Left;
    }
    if (PositionIsTop(pos)) return FlyoutDirection::Down;
    if (PositionIsBottom(pos)) return FlyoutDirection::Up;
    const int freeDown = work.bottom - main.bottom;
    const int freeUp = main.top - work.top;
    return freeDown >= freeUp ? FlyoutDirection::Down
                              : FlyoutDirection::Up;
}

struct PanelAttachment { int x = 0, y = 0; };
PanelAttachment GetPanelAttachment(bool vertical, FlyoutDirection direction,
                                   float scale, int mainWidth, int mainHeight,
                                   int panelWidth, int panelHeight) {
    const int gap = static_cast<int>(std::lround(7.0f * scale));
    const int inset = static_cast<int>(std::lround(4.0f * scale));
    if (vertical) {
        const int side = static_cast<int>(std::lround(7.0f * scale));
        return {direction == FlyoutDirection::Left
                    ? side - gap + inset - panelWidth
                    : mainWidth - side + gap - inset, 0};
    }
    const int top = static_cast<int>(std::lround(10.0f * scale));
    const int bottom = static_cast<int>(std::lround(13.0f * scale));
    return {0, direction == FlyoutDirection::Up
                   ? top - gap + bottom - panelHeight
                   : mainHeight - bottom + gap - top};
}

bool IsExpandedVolumePanel() {
    return g_popupKind == PopupKind::NativeVolume &&
           (g_panelMode == PanelMode::Media || g_panelMode == PanelMode::Mixer);
}
bool NeedsCompositeCentering() {
    if (!IsExpandedVolumePanel()) return false;
    const int position = g_position.load(std::memory_order_relaxed);
    return g_verticalVolumeBrightness.load(std::memory_order_relaxed)
        ? PositionCentersX(position) : PositionCentersY(position);
}

FlyoutDirection GetFlyoutDirection() {
    const bool vertical = g_verticalVolumeBrightness.load(
        std::memory_order_relaxed);
    RECT main{};
    MONITORINFO mi{sizeof(mi)};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &main) ||
        !GetMonitorInfoW(MonitorFromWindow(g_popupWnd,
                                         MONITOR_DEFAULTTONEAREST), &mi))
        return vertical ? FlyoutDirection::Right : FlyoutDirection::Down;
    return DirectionForPopup(main, mi.rcWork,
        g_position.load(std::memory_order_relaxed), vertical);
}
struct FindDisplay {
    WCHAR name[CCHDEVICENAME]{};
    HMONITOR monitor = nullptr;
};
BOOL CALLBACK FindDisplayCallback(HMONITOR m, HDC, LPRECT, LPARAM context) {
    auto* f = reinterpret_cast<FindDisplay*>(context);
    MONITORINFOEXW mi{sizeof(mi)};
    if (GetMonitorInfoW(m, &mi) &&
        _wcsicmp(mi.szDevice, f->name) == 0) {
        f->monitor = m;
        return FALSE;
    }
    return TRUE;
}
// One GDI-name lookup for DDC events, selected DISPLAYn and popup routing.
// Unknown identities stay unresolved, rather than silently identifying
// the primary monitor as the event target.
HMONITOR FindMonitorByDeviceName(PCWSTR device) {
    if (!device || !device[0]) return nullptr;
    FindDisplay result{};
    wcscpy_s(result.name, device);
    EnumDisplayMonitors(nullptr, nullptr, FindDisplayCallback,
                        reinterpret_cast<LPARAM>(&result));
    return result.monitor;
}

bool PublishArgbLayer(HWND window, HDC screen, HDC memory,
                      int width, int height) {
    SIZE size{width, height};
    POINT origin{0, 0};
    BLENDFUNCTION blend{AC_SRC_OVER, 0,
                        static_cast<BYTE>(g_fadeAlpha), AC_SRC_ALPHA};
    return UpdateLayeredWindow(window, screen, nullptr, &size,
                               memory, &origin, 0, &blend, ULW_ALPHA) != FALSE;
}

// ============================================================
// Forward declarations: cross-feature callbacks and UI entrypoints
// ============================================================
void DrawText(Gdiplus::Graphics&, const std::wstring&, float, float, float,
              float, float, Gdiplus::Color, bool = false, bool = false);
void DrawHorizontalVolume(Gdiplus::Graphics&);
void DrawLockStatus(Gdiplus::Graphics&);
void DrawNotification(Gdiplus::Graphics&);
void DrawExpandChevron(Gdiplus::Graphics&, float, float, Gdiplus::Color);
void ShowPopupAnimated();
void RenderPopup();
void RenderPanel();
void RenderMirroredFrame(HDC, void*, int, int, bool);
void RenderDdcTargetPeers();
void MovePopupToDisplay(const BrightnessEvent&);
void SetPopupInteractive(bool);
void ResetHideTimer(UINT);
void ResetHideTimerFor(DurationKind);
void ClosePanel();
void HideMirroredWindows(bool);
void DestroyMirroredWindows();
void UpdateArrowHitWindow();
void UpdateSpeakerHitWindow();
void FlushNoticeBatch();
void ShowPanel();
void ShowNotice(std::wstring, std::wstring, DurationKind, NoticeIcon);
void ShowMigratedXamlDeviceNotice(DurationKind);
void ShowMigratedXamlClipboardNotice();
std::vector<std::pair<std::string, NetInterfaceState>> GetNetworkSnapshot();
namespace bt_monitor {
    void Start();
    void Stop();
    void Drain();
} // namespace bt_monitor

void LoadSettings() {
    PCWSTR selectedLanguage = Wh_GetStringSetting(L"displayLanguage");
    const int chosen = selectedLanguage &&
        _wcsicmp(selectedLanguage, L"zh-TW") == 0 ? 2 :
        selectedLanguage && _wcsicmp(selectedLanguage, L"en") == 0 ? 1 : 0;
    g_displayLanguage.store(chosen, std::memory_order_relaxed);
    Wh_FreeStringSetting(selectedLanguage);
    g_hideAllNativeOsd.store(
        Wh_GetIntSetting(L"NativeHide.hideAllNativeOsd") != 0);
    LoadBoolSettings(g_hide, kNativeHideSettingKeys);
    LoadBoolSettings(g_showCustomNative, kCustomNativeSettingKeys);
    g_xamlForMigrated.store(
        Wh_GetIntSetting(L"CustomOSD.Switches.experimentalXamlVolume") != 0);
    g_showDdcBrightness.store(Wh_GetIntSetting(L"CustomOSD.Switches.showDdcBrightness") != 0);
    g_verticalVolumeBrightness.store(Wh_GetIntSetting(L"CustomOSD.Layout.verticalVolumeBrightness") != 0);
    g_fromExplorer.store(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcFromExplorer") != 0);
    g_fromTwinkle.store(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcFromTwinkle") != 0);
    g_vcpCode.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcVcpCode"), 0, 255));
    g_globalDurationMs.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Timing.globalDurationMs"), 500, 20000));
    g_individualDurations.store(
        Wh_GetIntSetting(L"CustomOSD.Timing.individualDurations") != 0);
    for (int i = 0; i < static_cast<int>(DurationKind::Count); ++i) {
        std::wstring path = L"CustomOSD.Timing.";
        path += kDurationSettingKeys[i];
        g_durationOverrides[i].store(std::clamp(
            Wh_GetIntSetting(path.c_str()), 500, 20000));
    }
    PCWSTR selectedTheme = Wh_GetStringSetting(L"CustomOSD.Appearance.ddcTheme");
    const int selectedMode = selectedTheme &&
        (_wcsicmp(selectedTheme, L"light") == 0 || wcscmp(selectedTheme, L"1") == 0)
        ? 1 : selectedTheme &&
        (_wcsicmp(selectedTheme, L"dark") == 0 || wcscmp(selectedTheme, L"2") == 0)
        ? 2 : 0;
    g_ddcTheme.store(selectedMode);
    Wh_FreeStringSetting(selectedTheme);
    g_ddcSizePercent.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcSizePercent"), 55, 120));
    g_horizontalOsdWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.horizontalOsdWidth"), 300, 650));
    g_horizontalOsdHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.horizontalOsdHeight"), 72, 220));
    g_verticalOsdWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.verticalOsdWidth"), 72, 180));
    g_verticalOsdHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.verticalOsdHeight"), 160, 430));
    g_horizontalSmtcHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.horizontalSmtcHeight"), 176, 480));
    g_horizontalMixerHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.horizontalMixerHeight"), 176, 480));
    g_verticalSmtcWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.verticalSmtcWidth"), 300, 650));
    g_verticalMixerWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.verticalMixerWidth"), 300, 650));
    g_ddcBorderless.store(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcBorderless") != 0);
    g_showSmtcOnVolume.store(Wh_GetIntSetting(L"CustomOSD.Switches.showSmtcOnVolume") != 0);
    g_showMediaArtwork.store(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.showMediaArtwork") != 0);
    g_showMediaControls.store(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.showMediaControls") != 0);
    g_mediaControlSizePercent.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.mediaControlSizePercent"), 90, 135));
    {
        PCWSTR shape = Wh_GetStringSetting(L"CustomOSD.Appearance.controlButtonShape");
        g_controlButtonSquare.store(shape && _wcsicmp(shape, L"square") == 0);
        Wh_FreeStringSetting(shape);
    }
    g_controlButtonCornerRadius.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Appearance.controlButtonCornerRadius"), 0, 16));
    g_showMixerArrow.store(Wh_GetIntSetting(L"CustomOSD.Switches.showVolumeMixerArrow") != 0);
    g_mixerMaxRows.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.mixerMaxRows"), 3, 16));
    LoadBoolSettings(g_showLockKeys, kLockSettingKeys);
    g_innerPadding.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcInnerPadding"), 6, 22));
    g_showClipboardOsd.store(Wh_GetIntSetting(L"CustomOSD.Switches.showClipboardOsd") != 0);
    g_clipboardTextPreview.store(Wh_GetIntSetting(L"CustomOSD.ClipboardAndDevices.clipboardTextPreview") != 0);
    g_clipboardImagePreview.store(Wh_GetIntSetting(L"CustomOSD.ClipboardAndDevices.clipboardImagePreview") != 0);
    g_clipboardChars.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ClipboardAndDevices.clipboardMaxChars"), 12, 100));
    g_showUsbEvents.store(Wh_GetIntSetting(L"CustomOSD.Switches.showUsbEvents") != 0);
    g_showBluetoothEvents.store(Wh_GetIntSetting(L"CustomOSD.Switches.showBluetoothEvents") != 0);
    g_showNetworkEvents.store(Wh_GetIntSetting(L"CustomOSD.Switches.showNetworkEvents") != 0);
    g_fadeEnabled.store(Wh_GetIntSetting(L"CustomOSD.Layout.fadeOsd") != 0);
    g_fadeDuration.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.fadeDurationMs"), 60, 450));
    g_accentMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcAccentMode"));
    g_backgroundMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcBackgroundMode"));
    g_textMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcTextMode"));
    g_trackMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcTrackMode"));
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomAccent", g_customAccent, g_validCustomAccent);
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomBackground", g_customBackground, g_validCustomBackground);
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomText", g_customText, g_validCustomText);
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomTrack", g_customTrack, g_validCustomTrack);
    g_backgroundOpacity.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcBackgroundOpacity"), 0, 100));
    g_cornerRadius.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcCornerRadius"), 0, 34));
    g_barThickness.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcBarThickness"), 2, 18));
    g_thumbDiameter.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcThumbDiameter"), 0, 20));
    g_fontSize.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcFontSize"), 10, 24));
    g_iconSize.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcIconSize"), 10, 24));
    g_iconStrokeWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcIconStrokeWidth"), 1, 3));
    g_showSun.store(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcShowSun") != 0);
    g_showValue.store(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcShowValue") != 0);
    PCWSTR outputMode = Wh_GetStringSetting(L"CustomOSD.Layout.displayOutputMode");
    const int displayMode = outputMode && _wcsicmp(outputMode, L"all") == 0 ? 3 :
        outputMode && _wcsicmp(outputMode, L"selected") == 0 ? 2 :
        outputMode && _wcsicmp(outputMode, L"primary") == 0 ? 1 : 0;
    g_displayOutputMode.store(displayMode);
    Wh_FreeStringSetting(outputMode);
    g_displayOutputNumber.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Layout.displayOutputNumber"), 1, 16));
    g_position.store(ReadPositionSetting());
    g_offsetX.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcOffsetX"), -500, 500));
    g_offsetY.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcOffsetY"), -500, 500));
}

// ============================================================
// Native shell hooks and event routing
// ============================================================
bool Hidden(Kind k) {
    // Hide never changes whether the custom OSD is displayed. A master
    // override hides all native categories, even if their local Hide is off.
    return g_hideAllNativeOsd.load(std::memory_order_relaxed) ||
           g_hide[static_cast<int>(k)].load(std::memory_order_relaxed);
}

bool ShowCustomNative(Kind kind) {
    return g_showCustomNative[static_cast<int>(kind)].load(
        std::memory_order_relaxed);
}

// Do not retain an HSTRING handle across the asynchronous hand-off: its
// lifetime belongs to the caller. Copy a bounded string while inside the hook.
std::wstring ReadNativeDisplayText(void* value) {
    if (!value) return {};
    HMODULE base = GetModuleHandleW(L"combase.dll");
    if (!base) return {};
    using RawText = PCWSTR(WINAPI*)(void*, UINT*);
    auto getText = reinterpret_cast<RawText>(
        GetProcAddress(base, "WindowsGetStringRawBuffer"));
    if (!getText) return {};
    UINT length = 0;
    PCWSTR buffer = getText(value, &length);
    if (!buffer || !length) return {};
    std::wstring cleaned;
    cleaned.reserve(std::min<UINT>(length, 128));
    for (UINT i = 0; i < length && cleaned.size() < 128; ++i) {
        WCHAR ch = buffer[i];
        if (ch == L'\r' || ch == L'\n' || ch == L'\t') ch = L' ';
        if (ch >= 32 && ch != 0x7f) cleaned.push_back(ch);
    }
    return cleaned;
}

bool RouteNativeExtra(Kind kind, int value, int variant = 0,
                      std::wstring text = {}) {
    if (!ShowCustomNative(kind)) return false;
    HWND receiver = FindWindowExW(HWND_MESSAGE, nullptr, kWindowClass, nullptr);
    if (!receiver) return false;
    bool mustPost = false;
    AcquireSRWLockExclusive(&g_nativeEventLock);
    g_nativeEventPending = NativeEventInfo{kind, value, variant, std::move(text)};
    if (!g_nativeEventPosted) {
        g_nativeEventPosted = true;
        mustPost = true;
    }
    ReleaseSRWLockExclusive(&g_nativeEventLock);
    if (!mustPost) return true;
    if (PostMessageW(receiver, kNativeExtraMessage, 0, 0)) return true;
    AcquireSRWLockExclusive(&g_nativeEventLock);
    g_nativeEventPosted = false;
    ReleaseSRWLockExclusive(&g_nativeEventLock);
    return false;
}

bool DdcAllowed() {
    return g_showDdcBrightness.load(std::memory_order_relaxed) &&
        (g_isExplorer ? g_fromExplorer.load(std::memory_order_relaxed)
                      : g_fromTwinkle.load(std::memory_order_relaxed));
}

// Display routing is independent of native visibility. Show controls whether
// the custom UI is enqueued; Hide alone decides whether to call the native
// implementation. Media, mixer and layout options are only subfeatures.
bool RouteNativeVolumeBrightness(Kind kind, int reportedValue) {
    if ((kind != Kind::Volume && kind != Kind::Brightness) ||
        !ShowCustomNative(kind))
        return false;
    HWND receiver = FindWindowExW(HWND_MESSAGE, nullptr,
                                  kWindowClass, nullptr);
    return receiver && PostMessageW(receiver, kNativeOsdMessage,
        static_cast<WPARAM>(kind), static_cast<LPARAM>(reportedValue));
}

// --- Windows 11 native HardwareConfirmator OSD switches ---
// ABI public thunks: int(this, value).
#define OSD_THUNK(name, kind, argtype)                          \
    using name##_t = int(WINAPI*)(void*, argtype);              \
    name##_t name##_Original = nullptr;                        \
    int WINAPI name##_Hook(void* self, argtype value) {        \
        if (Kind::kind == Kind::Volume || Kind::kind == Kind::Brightness) \
            RouteNativeVolumeBrightness(Kind::kind, static_cast<int>(value)); \
        else RouteNativeExtra(Kind::kind, static_cast<int>(value)); \
        if (Hidden(Kind::kind)) return S_OK;                     \
        return name##_Original(self, value);                    \
    }

OSD_THUNK(VolumeThunk, Volume, int)
OSD_THUNK(BrightnessThunk, Brightness, int)
OSD_THUNK(KeyboardThunk, Keyboard, int)
OSD_THUNK(AirplaneThunk, Airplane, bool)
OSD_THUNK(CameraThunk, Camera, bool)
using CameraAccessThunk_t = int(WINAPI*)(void*, bool);
CameraAccessThunk_t CameraAccessThunk_Original = nullptr;
int WINAPI CameraAccessThunk_Hook(void* self, bool enabled) {
    RouteNativeExtra(Kind::Camera, enabled ? 1 : 0, 1);
    if (Hidden(Kind::Camera)) return S_OK;
    return CameraAccessThunk_Original(self, enabled);
}
#undef OSD_THUNK

// C++/WinRT fire_and_forget uses a hidden return pointer on x64.
#define OSD_ASYNC(name, kind, argtype)                            \
    using name##_t = void*(WINAPI*)(void*, void*, argtype);      \
    name##_t name##_Original = nullptr;                          \
    void* WINAPI name##_Hook(void* self, void* ret, argtype v) {  \
        if (Kind::kind == Kind::Volume || Kind::kind == Kind::Brightness) \
            RouteNativeVolumeBrightness(Kind::kind, static_cast<int>(v)); \
        else RouteNativeExtra(Kind::kind, static_cast<int>(v)); \
        if (Hidden(Kind::kind)) return ret;                     \
        return name##_Original(self, ret, v);                   \
    }
OSD_ASYNC(VolumeAsync, Volume, int)
OSD_ASYNC(BrightnessAsync, Brightness, int)
OSD_ASYNC(KeyboardAsync, Keyboard, int)
OSD_ASYNC(AirplaneAsync, Airplane, bool)
OSD_ASYNC(CameraAsync, Camera, bool)
using CameraAccessAsync_t = void*(WINAPI*)(void*, void*, bool);
CameraAccessAsync_t CameraAccessAsync_Original = nullptr;
void* WINAPI CameraAccessAsync_Hook(void* self, void* ret, bool enabled) {
    RouteNativeExtra(Kind::Camera, enabled ? 1 : 0, 1);
    if (Hidden(Kind::Camera)) return ret;
    return CameraAccessAsync_Original(self, ret, enabled);
}
#undef OSD_ASYNC

// Do not skip the private coroutine for hstring parameters, since that
// would bypass the coroutine's responsibility for destroying the hstring.
using Microphone_t = int(WINAPI*)(void*, int, void*);
Microphone_t MicrophoneOriginal = nullptr;
int WINAPI MicrophoneHook(void* self, int state, void* text) {
    RouteNativeExtra(Kind::Microphone, state);
    if (Hidden(Kind::Microphone)) return S_OK;
    return MicrophoneOriginal(self, state, text);
}

using Text_t = int(WINAPI*)(void*, void*, bool);
Text_t TextOriginal = nullptr;
bool IsTwinuiReturnAddress(void* address) {
    HMODULE caller = nullptr;
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                             GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                             reinterpret_cast<PCWSTR>(address), &caller))
        return false;
    return caller && caller == GetModuleHandleW(L"twinui.dll");
}
int WINAPI TextHook(void* self, void* text, bool value) {
    auto kind = IsTwinuiReturnAddress(__builtin_return_address(0))
                    ? Kind::Desktop : Kind::Text;
    if (ShowCustomNative(kind))
        RouteNativeExtra(kind, value ? 1 : 0, 0, ReadNativeDisplayText(text));
    if (Hidden(kind)) return S_OK;
    return TextOriginal(self, text, value);
}

void HookNativeOsd() {
    g_confirmatorDll = LoadLibraryExW(
        L"Windows.Internal.HardwareConfirmator.dll", nullptr,
        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!g_confirmatorDll) {
        Wh_Log(L"Windows HardwareConfirmator DLL not available");
        return;
    }
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowVolume(int))"}, &VolumeThunk_Original, VolumeThunk_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowBrightness(int))"}, &BrightnessThunk_Original, BrightnessThunk_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowKeyboardBrightness(int))"}, &KeyboardThunk_Original, KeyboardThunk_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowAirplaneModeOn(bool))"}, &AirplaneThunk_Original, AirplaneThunk_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowCameraOn(bool))"}, &CameraThunk_Original, CameraThunk_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowCameraAccessEnabled(bool))"}, &CameraAccessThunk_Original, CameraAccessThunk_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowMicrophoneMuted(int,void *))",
          LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowMicrophoneMuted(int))"}, &MicrophoneOriginal, MicrophoneHook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost,struct winrt::Windows::Internal::HardwareConfirmator::IHardwareConfirmatorHost>::ShowText(void *,bool))"}, &TextOriginal, TextHook, true},
        {{LR"(private: struct winrt::fire_and_forget __cdecl winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost::ShowVolumeAsync(int))"}, &VolumeAsync_Original, VolumeAsync_Hook, true},
        {{LR"(private: struct winrt::fire_and_forget __cdecl winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost::ShowBrightnessAsync(int))"}, &BrightnessAsync_Original, BrightnessAsync_Hook, true},
        {{LR"(private: struct winrt::fire_and_forget __cdecl winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost::ShowKeyboardBrightnessAsync(int))"}, &KeyboardAsync_Original, KeyboardAsync_Hook, true},
        {{LR"(private: struct winrt::fire_and_forget __cdecl winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost::ShowAirplaneModeOnAsync(bool))"}, &AirplaneAsync_Original, AirplaneAsync_Hook, true},
        {{LR"(private: struct winrt::fire_and_forget __cdecl winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost::ShowCameraOnAsync(bool))"}, &CameraAsync_Original, CameraAsync_Hook, true},
        {{LR"(private: struct winrt::fire_and_forget __cdecl winrt::Windows::Internal::HardwareConfirmator::implementation::HardwareConfirmatorHost::ShowCameraAccessEnabledAsync(bool))"}, &CameraAccessAsync_Original, CameraAccessAsync_Hook, true},
    };
    if (!WindhawkUtils::HookSymbols(g_confirmatorDll, hooks, ARRAYSIZE(hooks)))
        Wh_Log(L"HardwareConfirmator HookSymbols failed");
    Wh_Log(L"Native OSD hooks: volume=%d brightness=%d microphone=%d text=%d",
           VolumeThunk_Original || VolumeAsync_Original,
           BrightnessThunk_Original || BrightnessAsync_Original,
           MicrophoneOriginal != nullptr, TextOriginal != nullptr);
}

// ============================================================
// DDC source hooks, target cache and cross-process events
// ============================================================
// --- DDC hooks and per-process HANDLE -> display identity / range cache ---
PhysicalInfo GetPhysicalInfo(HANDLE handle) {
    AcquireSRWLockShared(&g_handleLock);
    auto it = g_handles.find(reinterpret_cast<ULONG_PTR>(handle));
    PhysicalInfo copy = it == g_handles.end() ? PhysicalInfo{} : it->second;
    ReleaseSRWLockShared(&g_handleLock);
    return copy;
}

void UpdateRange(HANDLE handle, DWORD low, DWORD high) {
    if (high <= low) return;
    AcquireSRWLockExclusive(&g_handleLock);
    auto it = g_handles.find(reinterpret_cast<ULONG_PTR>(handle));
    if (it != g_handles.end()) {
        it->second.minimum = low;
        it->second.maximum = high;
    }
    ReleaseSRWLockExclusive(&g_handleLock);
}

using GetPhysical_t = BOOL(WINAPI*)(HMONITOR, DWORD, LPPHYSICAL_MONITOR);
GetPhysical_t GetPhysicalOriginal = nullptr;
BOOL WINAPI GetPhysicalHook(HMONITOR display, DWORD count,
                            LPPHYSICAL_MONITOR items) {
    BOOL ok = GetPhysicalOriginal(display, count, items);
    if (!ok || !items || !count || count > 32) return ok;
    MONITORINFOEXW mi{sizeof(mi)};
    if (!GetMonitorInfoW(display, &mi)) return ok;
    AcquireSRWLockExclusive(&g_handleLock);
    for (DWORD i = 0; i < count; ++i) {
        PhysicalInfo p{};
        wcscpy_s(p.device, mi.szDevice);
        p.physicalIndex = i;
        g_handles[reinterpret_cast<ULONG_PTR>(items[i].hPhysicalMonitor)] = p;
    }
    ReleaseSRWLockExclusive(&g_handleLock);
    return ok;
}

using DestroyPhysical_t = BOOL(WINAPI*)(HANDLE);
DestroyPhysical_t DestroyPhysicalOriginal = nullptr;
BOOL WINAPI DestroyPhysicalHook(HANDLE handle) {
    AcquireSRWLockExclusive(&g_handleLock);
    g_handles.erase(reinterpret_cast<ULONG_PTR>(handle));
    ReleaseSRWLockExclusive(&g_handleLock);
    return DestroyPhysicalOriginal(handle);
}

using DestroyPhysicalArray_t = BOOL(WINAPI*)(DWORD, LPPHYSICAL_MONITOR);
DestroyPhysicalArray_t DestroyPhysicalArrayOriginal = nullptr;
BOOL WINAPI DestroyPhysicalArrayHook(DWORD count, LPPHYSICAL_MONITOR items) {
    if (items && count <= 32) {
        AcquireSRWLockExclusive(&g_handleLock);
        for (DWORD i = 0; i < count; ++i)
            g_handles.erase(reinterpret_cast<ULONG_PTR>(items[i].hPhysicalMonitor));
        ReleaseSRWLockExclusive(&g_handleLock);
    }
    return DestroyPhysicalArrayOriginal(count, items);
}

using GetBrightness_t = BOOL(WINAPI*)(HANDLE, LPDWORD, LPDWORD, LPDWORD);
GetBrightness_t GetBrightnessOriginal = nullptr;
BOOL WINAPI GetBrightnessHook(HANDLE handle, LPDWORD low, LPDWORD current,
                              LPDWORD high) {
    BOOL ok = GetBrightnessOriginal(handle, low, current, high);
    if (ok && low && high) UpdateRange(handle, *low, *high);
    return ok;
}

using GetVcp_t = BOOL(WINAPI*)(HANDLE, BYTE, LPMC_VCP_CODE_TYPE,
                               LPDWORD, LPDWORD);
GetVcp_t GetVcpOriginal = nullptr;
BOOL WINAPI GetVcpHook(HANDLE handle, BYTE code, LPMC_VCP_CODE_TYPE type,
                       LPDWORD current, LPDWORD maximum) {
    BOOL ok = GetVcpOriginal(handle, code, type, current, maximum);
    if (ok && maximum && code == static_cast<BYTE>(g_vcpCode.load()))
        UpdateRange(handle, 0, *maximum);
    return ok;
}

void QueueBrightnessWheelTask(const BrightnessWheelTask& task) {
    if (!g_wheelWriteWake || g_wheelWriteStop.load()) return;
    AcquireSRWLockExclusive(&g_wheelWriteLock);
    auto sameTarget = [&](const BrightnessWheelTask& pending) {
        return pending.native == task.native &&
            (task.native ||
             (pending.monitor.physicalIndex == task.monitor.physicalIndex &&
              _wcsicmp(pending.monitor.device, task.monitor.device) == 0));
    };
    const auto found = std::find_if(g_wheelWritePending.begin(),
                                   g_wheelWritePending.end(), sameTarget);
    if (found != g_wheelWritePending.end()) {
        *found = task; // Coalesce only within the same physical target.
    } else if (g_wheelWritePending.size() < kMaxDdcTargets + 1) {
        g_wheelWritePending.push_back(task);
    } else {
        // Hard bound against malformed/rapid producer floods.
        g_wheelWritePending.erase(g_wheelWritePending.begin());
        g_wheelWritePending.push_back(task);
    }
    ReleaseSRWLockExclusive(&g_wheelWriteLock);
    SetEvent(g_wheelWriteWake);
}

void Publish(HANDLE handle, DWORD value) {
    if (!DdcAllowed()) return;
    PhysicalInfo info = GetPhysicalInfo(handle);
    if (!info.device[0]) {
        if (!g_loggedUnmapped.exchange(true))
            Wh_Log(L"DDC target monitor unknown: handle was not observed in "
                   L"GetPhysicalMonitorsFromHMONITOR. Fully quit/restart "
                   L"Twinkle Tray to rebuild its physical-monitor handle map.");
        // The Event target monitor mode must not silently move an unknown
        // target to DISPLAY1. Other output modes are location-independent.
        if (g_displayOutputMode.load(std::memory_order_relaxed) == 0)
            return;
    }
    BrightnessEvent ev{};
    ev.magic = kEventMagic;
    wcscpy_s(ev.device, info.device);
    ev.physicalIndex = info.physicalIndex;
    ev.value = value;
    ev.minimum = info.minimum;
    ev.maximum = info.maximum;
    ev.producerPid = GetCurrentProcessId();

    // The receiver is a message-only window in Explorer's dedicated UI
    // thread. WM_COPYDATA safely copies our stack payload across processes.
    HWND target = FindWindowExW(HWND_MESSAGE, nullptr, kWindowClass, nullptr);
    if (!target) return;
    COPYDATASTRUCT payload{kCopyDataTag, sizeof(ev), &ev};
    DWORD_PTR result = 0;
    SendMessageTimeoutW(target, WM_COPYDATA, 0,
                        reinterpret_cast<LPARAM>(&payload),
                        SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, &result);
}

using SetBrightness_t = BOOL(WINAPI*)(HANDLE, DWORD);
SetBrightness_t SetBrightnessOriginal = nullptr;
thread_local bool g_insideHighLevelSet = false;
BOOL WINAPI SetBrightnessHook(HANDLE handle, DWORD value) {
    bool prior = g_insideHighLevelSet;
    g_insideHighLevelSet = true;
    BOOL ok = SetBrightnessOriginal(handle, value);
    DWORD lastError = GetLastError();
    g_insideHighLevelSet = prior;
    if (ok && !prior) Publish(handle, value);
    SetLastError(lastError);
    return ok;
}

using SetVcp_t = BOOL(WINAPI*)(HANDLE, BYTE, DWORD);
SetVcp_t SetVcpOriginal = nullptr;
BOOL WINAPI SetVcpHook(HANDLE handle, BYTE code, DWORD value) {
    BOOL ok = SetVcpOriginal(handle, code, value);
    DWORD lastError = GetLastError();
    if (ok && !g_insideHighLevelSet &&
        code == static_cast<BYTE>(g_vcpCode.load()))
        Publish(handle, value);
    SetLastError(lastError);
    return ok;
}

void HookDdc() {
    g_ddcDll = LoadLibraryExW(L"dxva2.dll", nullptr,
                              LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!g_ddcDll) {
        Wh_Log(L"Cannot load dxva2.dll");
        return;
    }
    struct HookEntry { const char* name; void* detour; void** original; };
    HookEntry entries[] = {
        {"GetPhysicalMonitorsFromHMONITOR", reinterpret_cast<void*>(GetPhysicalHook), reinterpret_cast<void**>(&GetPhysicalOriginal)},
        {"DestroyPhysicalMonitor", reinterpret_cast<void*>(DestroyPhysicalHook), reinterpret_cast<void**>(&DestroyPhysicalOriginal)},
        {"DestroyPhysicalMonitors", reinterpret_cast<void*>(DestroyPhysicalArrayHook), reinterpret_cast<void**>(&DestroyPhysicalArrayOriginal)},
        {"GetMonitorBrightness", reinterpret_cast<void*>(GetBrightnessHook), reinterpret_cast<void**>(&GetBrightnessOriginal)},
        {"GetVCPFeatureAndVCPFeatureReply", reinterpret_cast<void*>(GetVcpHook), reinterpret_cast<void**>(&GetVcpOriginal)},
        {"SetMonitorBrightness", reinterpret_cast<void*>(SetBrightnessHook), reinterpret_cast<void**>(&SetBrightnessOriginal)},
        {"SetVCPFeature", reinterpret_cast<void*>(SetVcpHook), reinterpret_cast<void**>(&SetVcpOriginal)},
    };
    for (auto& e : entries) {
        void* address = reinterpret_cast<void*>(GetProcAddress(g_ddcDll, e.name));
        if (!address || !Wh_SetFunctionHook(address, e.detour, e.original))
            Wh_Log(L"DDC Hook failed: %hs", e.name);
    }
}

// ============================================================
// Windows accent/theme helpers
// ============================================================
void InitWindowsAccentProvider() {
    g_combase = LoadLibraryExW(L"combase.dll", nullptr,
                               LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!g_combase) return;
    auto roInit = reinterpret_cast<RoInitialize_t>(
        GetProcAddress(g_combase, "RoInitialize"));
    auto activate = reinterpret_cast<RoActivateInstance_t>(
        GetProcAddress(g_combase, "RoActivateInstance"));
    auto createString = reinterpret_cast<WindowsCreateString_t>(
        GetProcAddress(g_combase, "WindowsCreateString"));
    auto deleteString = reinterpret_cast<WindowsDeleteString_t>(
        GetProcAddress(g_combase, "WindowsDeleteString"));
    g_roUninitialize = reinterpret_cast<RoUninitialize_t>(
        GetProcAddress(g_combase, "RoUninitialize"));
    if (!roInit || !activate || !createString || !deleteString ||
        !g_roUninitialize) return;

    // Dedicated UI thread: initialize WinRT on this same thread.
    HRESULT hr = roInit(1); // RO_INIT_MULTITHREADED
    if (FAILED(hr)) return;
    g_roInitialized = true;
    void* classId = nullptr;
    if (FAILED(createString(kUiSettingsRuntimeClass, ARRAYSIZE(kUiSettingsRuntimeClass) - 1, &classId)))
        return;
    IUnknown* object = nullptr;
    hr = activate(classId, &object);
    deleteString(classId);
    if (SUCCEEDED(hr) && object) {
        hr = object->QueryInterface(kIUiSettings3,
                                    reinterpret_cast<void**>(&g_uiSettings));
        object->Release();
    }
    if (FAILED(hr))
        Wh_Log(L"UISettings unavailable (HRESULT=0x%08lX); using accent fallbacks",
               static_cast<unsigned long>(hr));
}

void ReleaseWindowsAccentProvider() {
    if (g_uiSettings) {
        g_uiSettings->Release();
        g_uiSettings = nullptr;
    }
    if (g_roInitialized && g_roUninitialize)
        g_roUninitialize();
    g_roInitialized = false;
    g_roUninitialize = nullptr;
    if (g_combase) FreeLibrary(g_combase);
    g_combase = nullptr;
}

DWORD SystemAccentRgb() {
    // Reading UISettings for each actual render supports changes to the
    // Windows accent without a timer, additional thread, or injected hook.
    if (g_uiSettings) {
        UiColor c{};
        if (SUCCEEDED(g_uiSettings->GetColorValue(5, &c))) // UIColorType.Accent
            return (DWORD(c.r) << 16) | (DWORD(c.g) << 8) | DWORD(c.b);
    }
    DWORD value = 0, bytes = sizeof(value);
    if (RegGetValueW(HKEY_CURRENT_USER,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Accent",
            L"AccentColorMenu", RRF_RT_REG_DWORD, nullptr,
            &value, &bytes) == ERROR_SUCCESS) {
        // AccentColorMenu is 0xAABBGGRR, unlike WinRT's Color{A,R,G,B}.
        return ((value & 0xff) << 16) | (value & 0xff00) |
               ((value >> 16) & 0xff);
    }
    HMODULE dwm = LoadLibraryExW(L"dwmapi.dll", nullptr,
                                LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (dwm) {
        using GetDwmColor_t = HRESULT(WINAPI*)(DWORD*, BOOL*);
        auto getDwmColor = reinterpret_cast<GetDwmColor_t>(
            GetProcAddress(dwm, "DwmGetColorizationColor"));
        BOOL opaque = FALSE;
        if (getDwmColor && SUCCEEDED(getDwmColor(&value, &opaque))) {
            FreeLibrary(dwm);
            return value & 0x00ffffff;  // DWM uses 0xAARRGGBB.
        }
        FreeLibrary(dwm);
    }
    COLORREF fallback = GetSysColor(COLOR_HIGHLIGHT);
    return (DWORD(GetRValue(fallback)) << 16) |
           (DWORD(GetGValue(fallback)) << 8) | DWORD(GetBValue(fallback));
}

Gdiplus::Color ToGdiColor(DWORD rgb, BYTE alpha = 255) {
    return Gdiplus::Color(alpha, (rgb >> 16) & 255,
                          (rgb >> 8) & 255, rgb & 255);
}

bool IsLightTheme() {
    const int setting = g_ddcTheme.load(std::memory_order_relaxed);
    if (setting == 1) return true;
    if (setting == 2) return false;
    DWORD light = 0;
    DWORD bytes = sizeof(light);
    const LSTATUS status = RegGetValueW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &light, &bytes);
    return status == ERROR_SUCCESS ? light != 0 : false;
}

// Shared color resolution across native, DDC, media, mixer and notices.
// Query the system accent only when no valid custom accent is configured.
DWORD ConfiguredOsdRgb(const std::atomic<int>& mode,
                        const std::atomic<bool>& valid,
                        const std::atomic<DWORD>& rgb, DWORD fallback) {
    return mode.load() && valid.load() ? rgb.load() : fallback;
}
DWORD OsdBackgroundRgb(bool light) {
    return ConfiguredOsdRgb(g_backgroundMode, g_validCustomBackground,
                            g_customBackground, light ? 0xFAFAFC : 0x26262A);
}
DWORD OsdTextRgb(bool light) {
    return ConfiguredOsdRgb(g_textMode, g_validCustomText,
                            g_customText, light ? 0x1C1C20 : 0xFAFAFB);
}
DWORD OsdTrackRgb(bool light, bool mixer = false) {
    return ConfiguredOsdRgb(g_trackMode, g_validCustomTrack,
                            g_customTrack, mixer
                                ? (light ? 0xE0E1E7 : 0x5E5E65)
                                : (light ? 0xDEDFE3 : 0x595A60));
}
DWORD OsdAccentRgb() {
    return g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
}

void AddRoundedRect(Gdiplus::GraphicsPath& path, float x, float y,
                    float width, float height, float radius) {
    radius = std::clamp(radius, 0.0f,
                        std::min(width, height) / 2.0f);
    if (radius <= 0.0f) {
        path.AddRectangle(Gdiplus::RectF(x, y, width, height));
        return;
    }
    const float d = radius * 2.0f;
    path.AddArc(x, y, d, d, 180.0f, 90.0f);
    path.AddArc(x + width - d, y, d, d, 270.0f, 90.0f);
    path.AddArc(x + width - d, y + height - d, d, d, 0.0f, 90.0f);
    path.AddArc(x, y + height - d, d, d, 90.0f, 90.0f);
    path.CloseFigure();
}

void DrawTrackThumb(Gdiplus::Graphics& gfx, float x, float centerY,
                    Gdiplus::Color accent, bool light) {
    const float diameter = static_cast<float>(g_thumbDiameter.load());
    if (diameter <= 0.0f) return;
    const float radius = diameter / 2.0f;
    Gdiplus::SolidBrush fill(light
        ? Gdiplus::Color(255, 255, 255, 255)
        : Gdiplus::Color(255, 27, 27, 31));
    Gdiplus::Pen outline(accent, 2.0f);
    gfx.FillEllipse(&fill, x - radius, centerY - radius,
                    diameter, diameter);
    gfx.DrawEllipse(&outline, x - radius, centerY - radius,
                    diameter, diameter);
}

int BrightnessPercent(const BrightnessEvent& brightness, bool* known) {
    *known = brightness.maximum > brightness.minimum;
    if (!*known) return 0;
    const DWORD current = std::clamp(brightness.value,
                                     brightness.minimum, brightness.maximum);
    const unsigned long long range = brightness.maximum - brightness.minimum;
    return static_cast<int>((
        static_cast<unsigned long long>(current - brightness.minimum) * 100ULL +
        range / 2ULL) / range);
}
int BrightnessPercent(bool* known) {
    return BrightnessPercent(g_visible, known);
}

// Shared endpoint acquisition for read, wheel, track drag and mute.
// WRL::ComPtr already ships with Windhawk's compiler; it avoids repeating
// manual COM Release paths and preserves multimedia -> console fallback.
bool OpenDefaultAudioEndpointVolume(
    Microsoft::WRL::ComPtr<IAudioEndpointVolume>& volume) {
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        reinterpret_cast<void**>(enumerator.GetAddressOf()));
    if (FAILED(hr) || !enumerator) return false;
    Microsoft::WRL::ComPtr<IMMDevice> device;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia,
                                              device.GetAddressOf());
    if (FAILED(hr) || !device) {
        device.Reset();
        hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole,
                                                  device.GetAddressOf());
    }
    if (FAILED(hr) || !device) return false;
    volume.Reset();
    hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL,
        nullptr, reinterpret_cast<void**>(volume.GetAddressOf()));
    return SUCCEEDED(hr) && volume.Get() != nullptr;
}

// Called ONLY on the Explorer OSD UI thread when Windows requests its
// native volume indicator. We do not query continuously or alter the volume.
bool ReadDefaultAudioVolume(int& percent, bool& muted) {
    Microsoft::WRL::ComPtr<IAudioEndpointVolume> volume;
    if (!OpenDefaultAudioEndpointVolume(volume)) return false;
    float scalar = 0.0f;
    BOOL isMuted = FALSE;
    const bool ok = SUCCEEDED(volume->GetMasterVolumeLevelScalar(&scalar)) &&
                    SUCCEEDED(volume->GetMute(&isMuted));
    if (ok) {
        percent = static_cast<int>(std::lround(
            std::clamp(scalar, 0.0f, 1.0f) * 100.0f));
        muted = isMuted != FALSE;
    }
    return ok;
}

bool AdjustDefaultAudioWheel(int steps) {
    if (!steps) return false;
    Microsoft::WRL::ComPtr<IAudioEndpointVolume> volume;
    if (!OpenDefaultAudioEndpointVolume(volume)) return false;
    float level = 0;
    BOOL muted = FALSE;
    bool ok = SUCCEEDED(volume->GetMasterVolumeLevelScalar(&level));
    if (ok) {
        const float next = std::clamp(level +
            steps * (kWheelStepPercent / 100.0f), 0.0f, 1.0f);
        ok = SUCCEEDED(volume->SetMasterVolumeLevelScalar(next, nullptr));
        if (ok) {
            volume->GetMasterVolumeLevelScalar(&level);
            volume->GetMute(&muted);
        }
    }
    if (ok) {
        g_nativePercent = static_cast<int>(std::lround(level * 100.0f));
        g_nativeMuted = muted != FALSE;
        g_nativePercentKnown = true;
        RenderPopup();
        ResetHideTimerFor(DurationKind::Volume);
    }
    return ok;
}

// Absolute set for click/drag of the main volume track. Do not unmute: mute
// is a separate user state, and moving the track should not silently clear it.
bool SetDefaultAudioBarPercent(int percent) {
    percent = std::clamp(percent, 0, 100);
    if (g_popupKind != PopupKind::NativeVolume || !g_nativePercentKnown)
        return false;
    if (percent == g_nativePercent) return true;
    Microsoft::WRL::ComPtr<IAudioEndpointVolume> volume;
    if (!OpenDefaultAudioEndpointVolume(volume)) return false;
    HRESULT hr = volume->SetMasterVolumeLevelScalar(percent / 100.0f, nullptr);
    float actual = percent / 100.0f;
    BOOL muted = FALSE;
    if (SUCCEEDED(hr)) {
        volume->GetMasterVolumeLevelScalar(&actual);
        volume->GetMute(&muted);
    }
    if (FAILED(hr)) return false;
    g_nativePercent = static_cast<int>(std::lround(
        std::clamp(actual, 0.0f, 1.0f) * 100.0f));
    g_nativeMuted = muted != FALSE;
    RenderPopup();
    return true;
}

// Toggle the default endpoint's mute without changing its stored volume.
bool ToggleDefaultAudioMute() {
    if (g_popupKind != PopupKind::NativeVolume || g_closing.load())
        return false;
    Microsoft::WRL::ComPtr<IAudioEndpointVolume> volume;
    if (!OpenDefaultAudioEndpointVolume(volume)) return false;
    BOOL current = FALSE;
    if (FAILED(volume->GetMute(&current))) return false;
    const BOOL wanted = current ? FALSE : TRUE;
    if (FAILED(volume->SetMute(wanted, nullptr))) return false;
    BOOL actual = wanted;
    (void)volume->GetMute(&actual);
    float scalar = 0.0f;
    if (SUCCEEDED(volume->GetMasterVolumeLevelScalar(&scalar))) {
        g_nativePercent = static_cast<int>(std::lround(
            std::clamp(scalar, 0.0f, 1.0f) * 100.0f));
        g_nativePercentKnown = true;
    }
    g_nativeMuted = actual != FALSE;
    if (g_panelMode == PanelMode::Mixer) {
        g_mixerMasterMuted = g_nativeMuted;
        RenderPanel();
    }
    RenderPopup();
    ResetHideTimerFor(g_activeDurationKind);
    return true;
}

// Draws independently constructed Fluent-style outline symbols in one shared
// 20 x 20 coordinate space. Both symbols use the same size, stroke width and
// visual anchor. Speaker detail follows the current volume level; both
// symbols are locally drawn vector paths, with no external glyph assets.
// ============================================================
// Shared vector drawing and main OSD painters
// ============================================================
void DrawUniformStatusIcon(Gdiplus::Graphics& gfx,
                           Gdiplus::Color color,
                           float centerX, float centerY,
                           PopupKind kind, int percent, bool muted) {
    const float size = static_cast<float>(g_iconSize.load());
    const float unit = size / 20.0f;
    const float left = centerX - size / 2.0f;
    const float top = centerY - size / 2.0f;
    const auto X = [left, unit](float x) { return left + x * unit; };
    const auto Y = [top, unit](float y) { return top + y * unit; };
    Gdiplus::Pen pen(color,
        static_cast<float>(g_iconStrokeWidth.load()));
    pen.SetStartCap(Gdiplus::LineCapRound);
    pen.SetEndCap(Gdiplus::LineCapRound);
    pen.SetLineJoin(Gdiplus::LineJoinRound);

    if (kind == PopupKind::NativeVolume) {
        Gdiplus::PointF points[] = {
            {X(2.2f), Y(8.0f)}, {X(5.7f), Y(8.0f)},
            {X(10.0f), Y(4.7f)}, {X(10.0f), Y(15.3f)},
            {X(5.7f), Y(12.0f)}, {X(2.2f), Y(12.0f)}
        };
        Gdiplus::GraphicsPath speaker;
        speaker.AddLines(points, ARRAYSIZE(points));
        speaker.CloseFigure();
        gfx.DrawPath(&pen, &speaker);
        if (muted || percent == 0) {
            gfx.DrawLine(&pen, X(13.0f), Y(7.7f),
                           X(17.3f), Y(12.3f));
            gfx.DrawLine(&pen, X(17.3f), Y(7.7f),
                           X(13.0f), Y(12.3f));
        } else {
            // Medium and high volume are differentiated, but never enlarge
            // the speaker icon; its maximum envelope matches the sun icon.
            gfx.DrawArc(&pen, X(10.5f), Y(6.5f),
                        4.3f * unit, 7.0f * unit, -65.0f, 130.0f);
            if (percent >= 50)
                gfx.DrawArc(&pen, X(9.5f), Y(3.4f),
                            8.2f * unit, 13.2f * unit, -62.0f, 124.0f);
        }
    } else {
        gfx.DrawEllipse(&pen, X(7.1f), Y(7.1f),
                        5.8f * unit, 5.8f * unit);
        for (int i = 0; i < 8; ++i) {
            const float angle = kTau * static_cast<float>(i) / 8.0f;
            const float dx = std::cos(angle), dy = std::sin(angle);
            gfx.DrawLine(&pen,
                X(10.0f + dx * 6.0f), Y(10.0f + dy * 6.0f),
                X(10.0f + dx * 8.0f), Y(10.0f + dy * 8.0f));
        }
    }
}

// One renderer is shared by volume, native brightness and DDC/CI brightness.
// This is an upright bar (bottom-to-top), not a rotated bitmap. It deliberately
// does not add taskbar widgets or depend on a separate UI framework.
void DrawExpandChevron(Gdiplus::Graphics& gfx, float x, float y,
                       Gdiplus::Color color);
// Shared painted icon and hit-target anchor, including vertical size settings.
void MainVolumeIconCenter(float& x, float& y) {
    if (g_verticalVolumeBrightness.load()) {
        const float logicalH = MainLogicalHeight();
        const float glyph = static_cast<float>(g_iconSize.load());
        x = MainLogicalWidth() / 2.0f;
        y = g_showMixerArrow.load() ?
            logicalH - 42.0f - glyph / 2.0f :
            logicalH - 6.0f - static_cast<float>(g_innerPadding.load()) -
                glyph / 2.0f;
    } else {
        x = 49.0f;
        y = MainCenterY();
    }
}

void DrawVerticalPopup(Gdiplus::Graphics& gfx, const BrightnessEvent& brightness) {
    const bool light = IsLightTheme();
    const DWORD backgroundRgb = OsdBackgroundRgb(light);
    const DWORD textRgb = OsdTextRgb(light);
    const DWORD trackRgb = OsdTrackRgb(light);
    const DWORD accentRgb = OsdAccentRgb();
    const BYTE opacity = OsdBackgroundAlpha();
    const Gdiplus::Color foreground = ToGdiColor(textRgb);
    const Gdiplus::Color accent = ToGdiColor(accentRgb);
    const Gdiplus::Color trackColor = ToGdiColor(trackRgb);
    const bool borderless = g_ddcBorderless.load();
    const float corner = static_cast<float>(g_cornerRadius.load());

    // Configurable vertical canvas; keep 7px side / 6px top/bottom margins.
    const float logicalW = MainLogicalWidth();
    const float logicalH = MainLogicalHeight();
    const float edge = static_cast<float>(g_innerPadding.load());
    const float cardHeight = logicalH - 12.0f;
    const float cardWidth = logicalW - 14.0f;
    const float centerX = logicalW / 2.0f;
    if (!borderless) {
        for (int layer = 5; layer >= 1; --layer) {
            const float grow = static_cast<float>(layer);
            Gdiplus::GraphicsPath shadow;
            AddRoundedRect(shadow, 7.0f - grow * 0.35f,
                           6.0f + grow * 0.45f,
                           cardWidth + grow * 0.7f,
                           cardHeight + grow * 0.55f,
                           corner + grow * 0.25f);
            Gdiplus::SolidBrush sb(Gdiplus::Color(
                static_cast<BYTE>(light ? 6 : 12), 0, 0, 0));
            gfx.FillPath(&sb, &shadow);
        }
    }
    Gdiplus::GraphicsPath body;
    AddRoundedRect(body, 7.0f, 6.0f, cardWidth, cardHeight, corner);
    Gdiplus::SolidBrush bg(ToGdiColor(backgroundRgb, opacity));
    gfx.FillPath(&bg, &body);
    if (!borderless) {
        Gdiplus::Pen outline(light
            ? Gdiplus::Color(255, 213, 215, 220)
            : Gdiplus::Color(255, 81, 82, 87), 0.8f);
        gfx.DrawPath(&outline, &body);
    }

    const bool showIcon = (g_popupKind == PopupKind::NativeVolume) ||
                          g_showSun.load();
    const bool showValue = g_showValue.load();
    bool known = false;
    int percent = 0;
    DWORD raw = 0;
    if (g_popupKind == PopupKind::DdcBrightness) {
        percent = BrightnessPercent(brightness, &known);
        raw = brightness.value;
    } else {
        known = g_nativePercentKnown;
        percent = g_nativePercent;
        raw = static_cast<DWORD>(std::max(g_nativePercent, 0));
    }
    percent = std::clamp(percent, 0, 100);

    if (showValue) {
        WCHAR number[48]{};
        if (known) swprintf_s(number, L"%d%%", percent);
        else swprintf_s(number, L"%lu", raw);
        Gdiplus::Font font(L"Segoe UI Variable Text",
            static_cast<float>(g_fontSize.load()),
            Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::Font fallback(L"Segoe UI",
            static_cast<float>(g_fontSize.load()),
            Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::SolidBrush textBrush(foreground);
        Gdiplus::StringFormat format;
        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
        gfx.DrawString(number, -1,
            font.GetLastStatus() == Gdiplus::Ok ? &font : &fallback,
            Gdiplus::RectF(8.0f, 6.0f + edge, logicalW - 16.0f, 22.0f),
            &format, &textBrush);
    }

    const float thick = static_cast<float>(g_barThickness.load());
    const float y = showValue ? 34.0f + edge : 9.0f + edge;
    const bool hasChevron =
        g_popupKind == PopupKind::NativeVolume && g_showMixerArrow.load();
    // Preserve the gap above the expand button at any custom main height.
    const float iconBottom = hasChevron ? logicalH - 42.0f : logicalH - 27.0f;
    const float glyphSize = static_cast<float>(g_iconSize.load());
    const float thumbRadius = static_cast<float>(g_thumbDiameter.load()) / 2.0f;
    const float bottom = hasChevron
        ? std::min(logicalH - 57.0f, iconBottom - glyphSize -
                           std::max(8.0f, thumbRadius + 4.0f))
        : (showIcon ? logicalH - 34.0f - edge : logicalH - 9.0f - edge);
    const float height = std::max(1.0f, bottom - y);
    const float x = centerX - thick / 2.0f;
    Gdiplus::GraphicsPath track;
    AddRoundedRect(track, x, y, thick, height, thick / 2.0f);
    Gdiplus::SolidBrush trackBrush(trackColor);
    gfx.FillPath(&trackBrush, &track);
    if (known && percent > 0) {
        const float filled = height * percent / 100.0f;
        // Clip the full track to keep both ends curved.
        Gdiplus::GraphicsPath fill;
        AddRoundedRect(fill, x, y, thick, height, thick / 2.0f);
        Gdiplus::GraphicsState previousClip = gfx.Save();
        gfx.SetClip(Gdiplus::RectF(x, bottom - filled, thick, filled));
        Gdiplus::SolidBrush accentBrush(accent);
        gfx.FillPath(&accentBrush, &fill);
        gfx.Restore(previousClip);
    }
    // Preserve the user-selected thumb diameter. Users who prefer a clean,
    // Fluent-style progress track can still set it to 0 in Windhawk settings.
    if (known)
        DrawTrackThumb(gfx, centerX,
                       bottom - height * percent / 100.0f, accent, light);

    if (showIcon) {
        // Put the volume icon ABOVE its dedicated bottom chevron, while
        // retaining the same size and stroke as the brightness icon.
        float iconX = centerX;
        float iconY = hasChevron
            ? (iconBottom - glyphSize / 2.0f)
            : (logicalH - 6.0f - edge - glyphSize / 2.0f);
        if (g_popupKind == PopupKind::NativeVolume)
            MainVolumeIconCenter(iconX, iconY);
        DrawUniformStatusIcon(gfx, foreground, iconX, iconY,
                              g_popupKind, percent, g_nativeMuted);
    }
    if (hasChevron)
        DrawExpandChevron(gfx, VerticalChevronX(),
                          VerticalChevronY(), foreground);
}

// --- Event notifications & shared animation state ---
void ClearClipboardThumbnail() {
    if (g_clipboardThumbnail) {
        DeleteObject(g_clipboardThumbnail);
        g_clipboardThumbnail = nullptr;
    }
}

// All text/status notifications share exactly the same canvas and card/tile
// geometry. A separate, image-first clipboard layout intentionally uses its
// own canvas so image previews can preserve their aspect ratio.
void DrawStatusNoticeChrome(Gdiplus::Graphics& gfx, bool light) {
    Gdiplus::GraphicsPath card;
    AddRoundedRect(card, 8.0f, 7.0f,
                   kStatusNoticeWidth - 16.0f, kStatusNoticeHeight - 15.0f,
                   static_cast<float>(g_cornerRadius.load()));
    Gdiplus::SolidBrush background(ToGdiColor(
        OsdBackgroundRgb(light), OsdBackgroundAlpha()));
    gfx.FillPath(&background, &card);
    Gdiplus::GraphicsPath tile;
    AddRoundedRect(tile, kStatusIconX, kStatusIconY,
                   kStatusIconSize, kStatusIconSize, 10.0f);
    Gdiplus::SolidBrush tileBrush(light
        ? Gdiplus::Color(255, 234, 236, 240)
        : Gdiplus::Color(255, 66, 68, 72));
    gfx.FillPath(&tileBrush, &tile);
}

// Keep typography and text insets identical across event sources.
void DrawStatusNoticeLabels(Gdiplus::Graphics& gfx,
                            const std::wstring& title,
                            const std::wstring& detail,
                            Gdiplus::Color fg,
                            bool hasAction = false) {
    const Gdiplus::Color quiet(195, fg.GetR(), fg.GetG(), fg.GetB());
    DrawText(gfx, title, kStatusTextX, 22.0f,
             hasAction ? 177.0f : 188.0f, 25.0f, 15.0f, fg, false);
    DrawText(gfx, detail, kStatusTextX, 48.0f,
             188.0f, 23.0f, 12.0f, quiet, false);
}

// Compact icon-and-state OSD for HardwareConfirmator categories that do not
// have a meaningful volume/brightness slider. Values come from the native
// display request itself, not from polling device state.
void DrawNativeEvent(Gdiplus::Graphics& gfx) {
    const bool light = IsLightTheme();
    const Gdiplus::Color fg = ToGdiColor(OsdTextRgb(light));
    DrawStatusNoticeChrome(gfx, light);
    Gdiplus::Pen symbol(ToGdiColor(OsdAccentRgb()), 2.0f);
    symbol.SetStartCap(Gdiplus::LineCapRound);
    symbol.SetEndCap(Gdiplus::LineCapRound);
    const NativeEventInfo& ev = g_nativeEventCurrent;
    std::wstring title, detail;
    switch (ev.kind) {
        case Kind::Keyboard: {
            title = Tr(OsdText::KeyboardBacklight);
            detail = ev.value >= 0 && ev.value <= 100
                ? std::to_wstring(ev.value) + L"%" :
                  std::wstring(Tr(OsdText::Level)) + std::to_wstring(ev.value);
            Gdiplus::GraphicsPath kb;
            AddRoundedRect(kb, 28.0f, 33.0f, 32.0f, 23.0f, 4.0f);
            gfx.DrawPath(&symbol, &kb);
            for (int row = 0; row < 2; ++row)
                for (int col = 0; col < 4; ++col)
                    gfx.DrawLine(&symbol, 33.0f + col * 7.0f,
                                 40.0f + row * 7.0f,
                                 36.0f + col * 7.0f,
                                 40.0f + row * 7.0f);
            break;
        }
        case Kind::Airplane:
            title = Tr(OsdText::AirplaneMode);
            detail = ev.value ? Tr(OsdText::Enabled) : Tr(OsdText::Disabled);
            gfx.DrawLine(&symbol, 30.0f, 55.0f, 57.0f, 31.0f);
            gfx.DrawLine(&symbol, 44.0f, 42.0f, 28.0f, 37.0f);
            gfx.DrawLine(&symbol, 44.0f, 42.0f, 54.0f, 58.0f);
            gfx.DrawLine(&symbol, 34.0f, 49.0f, 33.0f, 56.0f);
            break;
        case Kind::Camera: {
            const bool access = ev.variant == 1;
            title = access ? Tr(OsdText::CameraAccess) : Tr(OsdText::Camera);
            detail = access ? (ev.value ? Tr(OsdText::Allowed) : Tr(OsdText::Blocked))
                            : (ev.value ? Tr(OsdText::Enabled) : Tr(OsdText::Disabled));
            Gdiplus::GraphicsPath camera;
            AddRoundedRect(camera, 28.0f, 35.0f, 32.0f, 22.0f, 4.0f);
            gfx.DrawPath(&symbol, &camera);
            gfx.DrawEllipse(&symbol, 40.0f, 40.0f, 11.0f, 11.0f);
            break;
        }
        case Kind::Microphone: {
            title = Tr(OsdText::Microphone);
            // The non-public API uses an integer state; do not invent device
            // state semantics for values other than conventional 0/1.
            detail = ev.value == 0 ? Tr(OsdText::Unmuted) :
                     ev.value == 1 ? Tr(OsdText::Muted) : Tr(OsdText::StatusChanged);
            Gdiplus::GraphicsPath capsule;
            AddRoundedRect(capsule, 38.0f, 30.0f, 13.0f, 23.0f, 6.5f);
            gfx.DrawPath(&symbol, &capsule);
            gfx.DrawArc(&symbol, 33.0f, 38.0f, 23.0f, 20.0f, 0.0f, 180.0f);
            gfx.DrawLine(&symbol, 44.0f, 58.0f, 44.0f, 62.0f);
            gfx.DrawLine(&symbol, 38.0f, 62.0f, 50.0f, 62.0f);
            if (ev.value == 1)
                gfx.DrawLine(&symbol, 32.0f, 59.0f, 56.0f, 33.0f);
            break;
        }
        case Kind::Desktop: {
            title = Tr(OsdText::VirtualDesktop);
            detail = ev.text.empty() ? Tr(OsdText::DesktopSwitched) : ev.text;
            Gdiplus::GraphicsPath desktop;
            AddRoundedRect(desktop, 27.0f, 33.0f, 34.0f, 24.0f, 3.0f);
            gfx.DrawPath(&symbol, &desktop);
            gfx.DrawLine(&symbol, 44.0f, 58.0f, 44.0f, 62.0f);
            gfx.DrawLine(&symbol, 37.0f, 62.0f, 51.0f, 62.0f);
            break;
        }
        case Kind::Text:
            title = Tr(OsdText::SystemNotice);
            detail = ev.text.empty() ? Tr(OsdText::StatusChanged) : ev.text;
            gfx.DrawLine(&symbol, 31.0f, 34.0f, 57.0f, 34.0f);
            gfx.DrawLine(&symbol, 44.0f, 34.0f, 44.0f, 59.0f);
            gfx.DrawLine(&symbol, 37.0f, 59.0f, 51.0f, 59.0f);
            break;
        default:
            title = Tr(OsdText::SystemStatus);
            detail = Tr(OsdText::StatusChanged);
            break;
    }
    DrawStatusNoticeLabels(gfx, title, detail, fg);
}

// The notice category is explicit state, not inferred from localized titles
// or device names. Keep all symbols within the shared 52x52 status tile.
void DrawNoticeCategoryIcon(Gdiplus::Graphics& gfx, NoticeIcon icon) {
    const Gdiplus::Color accent = ToGdiColor(OsdAccentRgb());
    Gdiplus::Pen stroke(accent, 2.2f);
    stroke.SetStartCap(Gdiplus::LineCapRound);
    stroke.SetEndCap(Gdiplus::LineCapRound);
    stroke.SetLineJoin(Gdiplus::LineJoinRound);
    Gdiplus::SolidBrush solid(accent);
    switch (icon) {
        case NoticeIcon::Bluetooth:
            // Standard Bluetooth angular rune: upper and lower forks.
            gfx.DrawLine(&stroke, 44.0f, 29.0f, 44.0f, 61.0f);
            gfx.DrawLine(&stroke, 44.0f, 29.0f, 55.0f, 38.0f);
            gfx.DrawLine(&stroke, 55.0f, 38.0f, 34.0f, 54.0f);
            gfx.DrawLine(&stroke, 34.0f, 36.0f, 55.0f, 52.0f);
            gfx.DrawLine(&stroke, 55.0f, 52.0f, 44.0f, 61.0f);
            break;
        case NoticeIcon::Usb: {
            // USB trident: triangular head, branch terminal and dot.
            gfx.DrawLine(&stroke, 44.0f, 36.0f, 44.0f, 59.0f);
            gfx.DrawLine(&stroke, 44.0f, 49.0f, 34.0f, 49.0f);
            gfx.DrawLine(&stroke, 34.0f, 49.0f, 34.0f, 55.0f);
            gfx.DrawLine(&stroke, 44.0f, 42.0f, 54.0f, 42.0f);
            gfx.DrawLine(&stroke, 54.0f, 42.0f, 54.0f, 35.0f);
            Gdiplus::PointF triangle[] = {
                {44.0f, 28.0f}, {39.5f, 36.0f}, {48.5f, 36.0f}
            };
            gfx.DrawPolygon(&stroke, triangle, 3);
            gfx.DrawEllipse(&stroke, 31.0f, 55.0f, 6.0f, 6.0f);
            gfx.DrawRectangle(&stroke, 51.0f, 29.0f, 6.0f, 6.0f);
            gfx.FillEllipse(&solid, 41.0f, 57.0f, 6.0f, 6.0f);
            break;
        }
        case NoticeIcon::Network:
            // Interface/network topology, not a globe implying Internet
            // availability (which connectivity-hint events cannot prove).
            gfx.DrawLine(&stroke, 44.0f, 37.0f, 44.0f, 46.0f);
            gfx.DrawLine(&stroke, 44.0f, 46.0f, 33.0f, 55.0f);
            gfx.DrawLine(&stroke, 44.0f, 46.0f, 55.0f, 55.0f);
            gfx.FillEllipse(&solid, 40.0f, 29.0f, 8.0f, 8.0f);
            gfx.FillEllipse(&solid, 40.0f, 42.0f, 8.0f, 8.0f);
            gfx.FillEllipse(&solid, 29.0f, 53.0f, 8.0f, 8.0f);
            gfx.FillEllipse(&solid, 51.0f, 53.0f, 8.0f, 8.0f);
            break;
        case NoticeIcon::Clipboard: {
            // Replace the generic dot with a clipboard; image previews
            // continue using their separate full-image layout.
            Gdiplus::GraphicsPath board;
            AddRoundedRect(board, 33.0f, 33.0f, 22.0f, 29.0f, 3.0f);
            gfx.DrawPath(&stroke, &board);
            Gdiplus::GraphicsPath clip;
            AddRoundedRect(clip, 39.0f, 29.0f, 10.0f, 7.0f, 2.0f);
            gfx.FillPath(&solid, &clip);
            gfx.DrawLine(&stroke, 38.0f, 46.0f, 50.0f, 46.0f);
            gfx.DrawLine(&stroke, 38.0f, 52.0f, 48.0f, 52.0f);
            break;
        }
    }
}

void DrawNotification(Gdiplus::Graphics& gfx) {
    // OSD text is ephemeral and never written to disk or Windhawk logs.
    const bool light = IsLightTheme();
    const DWORD bg = OsdBackgroundRgb(light);
    const DWORD fgRgb = OsdTextRgb(light);
    const Gdiplus::Color fg = ToGdiColor(fgRgb);
    // Image-first clipboard notice: the image occupies nearly the whole
    // canvas. Do not crop or distort portrait/panoramic clipboard images.
    if (g_clipboardThumbnail) {
        Gdiplus::GraphicsPath card;
        AddRoundedRect(card, 8.0f, 7.0f,
                       kClipboardImageCanvasW - 16.0f,
                       kClipboardImageCanvasH - 14.0f,
                       static_cast<float>(g_cornerRadius.load()));
        Gdiplus::SolidBrush background(ToGdiColor(bg,
            OsdBackgroundAlpha()));
        gfx.FillPath(&background, &card);

        constexpr float left = 20.0f;
        constexpr float top = 18.0f;
        const float previewW = kClipboardImageMaxW;
        const float previewH = kClipboardImageMaxH;
        Gdiplus::GraphicsPath preview;
        AddRoundedRect(preview, left, top, previewW, previewH, 9.0f);
        Gdiplus::SolidBrush placeholder(light
            ? Gdiplus::Color(255, 235, 236, 240)
            : Gdiplus::Color(255, 55, 56, 61));
        gfx.FillPath(&placeholder, &preview);

        Gdiplus::Bitmap bitmap(g_clipboardThumbnail, nullptr);
        if (bitmap.GetLastStatus() == Gdiplus::Ok &&
            bitmap.GetWidth() && bitmap.GetHeight()) {
            const float imageScale = std::min(
                previewW / bitmap.GetWidth(),
                previewH / bitmap.GetHeight());
            const float imageW = bitmap.GetWidth() * imageScale;
            const float imageH = bitmap.GetHeight() * imageScale;
            const float x = left + (previewW - imageW) * 0.5f;
            const float y = top + (previewH - imageH) * 0.5f;
            const auto state = gfx.Save();
            gfx.SetClip(&preview);
            gfx.DrawImage(&bitmap, x, y, imageW, imageH);
            gfx.Restore(state);
        }
        // Only a small caption remains; the picture is the primary UI.
        DrawText(gfx, g_noticeTitle, 20.0f, 190.0f,
                 224.0f, 18.0f, 12.0f, fg, true);
        return;
    }
    DrawStatusNoticeChrome(gfx, light);
    DrawNoticeCategoryIcon(gfx, g_noticeIcon);
    DrawStatusNoticeLabels(gfx, g_noticeTitle, g_noticeBody,
                           fg, g_noticeClickable);
    if (g_noticeClickable) DrawText(gfx, L"›", 269, 34, 17, 20, 20, fg, true);
}

// Windows 11 layered GDI+ windows use UpdateLayeredWindow (premultiplied
// alpha). NEVER mix SetLayeredWindowAttributes on the popup/panel: doing so
// would break subsequent UpdateLayeredWindow calls.
// ============================================================
// Popup lifetime, hide/fade and input geometry
// ============================================================
void FinishPopupHide() {
    HideMirroredWindows(false);
    g_ddcTargets.clear(); // Release per-monitor values after visibility ends.
    g_fadeActive = false;
    g_fadeAlpha = 255;
    if (g_popupWnd) ShowWindow(g_popupWnd, SW_HIDE);
    if (g_arrowWnd) ShowWindow(g_arrowWnd, SW_HIDE);
    g_arrowHovered = false;
    g_arrowPressed = false;
    if (g_arrowWnd && GetCapture() == g_arrowWnd) ReleaseCapture();
    if (g_barWheelWnd) ShowWindow(g_barWheelWnd, SW_HIDE);
    if (g_speakerHitWnd) ShowWindow(g_speakerHitWnd, SW_HIDE);
    g_speakerPressed = false;
    if (g_speakerHitWnd && GetCapture() == g_speakerHitWnd) ReleaseCapture();
    g_mainBarDragging = false;
    g_mainBarDragKind = -1;
    if (g_barWheelWnd && GetCapture() == g_barWheelWnd) ReleaseCapture();
    ClosePanel();
    ClearClipboardThumbnail();
    g_noticeTitle.clear();
    g_noticeBody.clear();
    g_noticeIcon = NoticeIcon::Clipboard;
    g_noticeClickable = false;
    g_noticeDetails.clear();
    g_noticeScroll = 0;
    // Revert to a passthrough OSD after any interactive event notification.
    SetWindowLongPtrW(g_popupWnd, GWL_EXSTYLE,
        GetWindowLongPtrW(g_popupWnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT);
}

void BeginFade(bool out) {
    if (!g_popupWnd) return;
    KillTimer(g_popupWnd, kFadeTimer);
    g_fadeActive = false;
    if (!g_fadeEnabled.load()) {
        g_fadeAlpha = out ? 0 : 255;
        if (out) FinishPopupHide();
        else { RenderPopup(); if (g_panelMode != PanelMode::None) RenderPanel(); }
        return;
    }
    g_fadeOut = out;
    g_fadeFrom = g_fadeAlpha;
    g_fadeTo = out ? 0 : 255;
    if (g_fadeFrom == g_fadeTo) {
        if (out) FinishPopupHide();
        return;
    }
    g_fadeStart = GetTickCount();
    g_fadeActive = true;
    if (!SetTimer(g_popupWnd, kFadeTimer, 16, nullptr)) {
        g_fadeActive = false;
        g_fadeAlpha = g_fadeTo;
        if (out) FinishPopupHide();
    }
}

// The painted track (not the hit halo) defines the 0..100% mapping.
// This matches DrawVerticalPopup, DrawHorizontalVolume, and the horizontal
// brightness renderer, including user-defined OSD canvas dimensions.
struct MainBarRect { float x, y, w, h; };
bool MainBarTrackGeometry(MainBarRect& bar) {
    if (g_popupKind != PopupKind::NativeVolume &&
        g_popupKind != PopupKind::NativeBrightness &&
        g_popupKind != PopupKind::DdcBrightness) return false;
    if (g_popupKind == PopupKind::DdcBrightness &&
        g_visible.maximum <= g_visible.minimum) return false;
    if (g_popupKind != PopupKind::DdcBrightness &&
        !g_nativePercentKnown) return false;
    const float thick = static_cast<float>(g_barThickness.load());
    if (g_verticalVolumeBrightness.load()) {
        const float edge = static_cast<float>(g_innerPadding.load());
        const float glyph = static_cast<float>(g_iconSize.load());
        const float thumb = static_cast<float>(g_thumbDiameter.load()) / 2.0f;
        const bool showIcon = g_popupKind == PopupKind::NativeVolume ||
                              g_showSun.load();
        const bool chevron = g_popupKind == PopupKind::NativeVolume &&
                             g_showMixerArrow.load();
        const float top = g_showValue.load() ? 34.0f + edge : 9.0f + edge;
        const float logicalH = MainLogicalHeight();
        const float bottom = chevron ?
            std::min(logicalH - 57.0f, logicalH - 42.0f - glyph -
                           std::max(8.0f, thumb + 4.0f))
            : (showIcon ? logicalH - 34.0f - edge : logicalH - 9.0f - edge);
        if (bottom <= top) return false;
        bar = {MainLogicalWidth() / 2.0f - thick / 2.0f,
               top, thick, bottom - top};
    } else if (g_popupKind == PopupKind::NativeVolume) {
        const float width = MainLogicalWidth() -
            (g_showMixerArrow.load() ? 191.0f : 169.0f);
        // Horizontal volume uses a fixed 8px track, not barThickness.
        bar = {76.0f, MainCenterY() - 4.0f, width, 8.0f};
    } else {
        const float left = g_showSun.load() ? 80.0f : 38.0f;
        const float right = MainLogicalWidth() -
            (g_showValue.load() ? 79.0f : 30.0f);
        bar = {left, MainCenterY() - thick / 2.0f,
               right - left, thick};
    }
    return bar.w > 0.0f && bar.h > 0.0f;
}

// Keep the existing small, invisible input surface: unrelated parts of the
// layered OSD remain fully mouse-transparent.
bool MainBarWheelGeometry(MainBarRect& bar) {
    MainBarRect track{};
    if (!MainBarTrackGeometry(track)) return false;
    if (g_verticalVolumeBrightness.load()) {
        const float haloWidth = std::max(24.0f, track.w + 14.0f);
        bar = {track.x + track.w / 2.0f - haloWidth / 2.0f,
               track.y - 9.0f, haloWidth, track.h + 18.0f};
    } else {
        bar = {track.x - 7.0f, track.y + track.h / 2.0f - 12.0f,
               track.w + 14.0f, 24.0f};
    }
    return true;
}
void UpdateBarWheelWindow() {
    if (!g_barWheelWnd || !g_popupWnd || !IsWindowVisible(g_popupWnd)) {
        if (g_barWheelWnd) ShowWindow(g_barWheelWnd, SW_HIDE);
        return;
    }
    MainBarRect b{};
    if (!MainBarWheelGeometry(b) || g_scale <= 0.0f) {
        ShowWindow(g_barWheelWnd, SW_HIDE);
        return;
    }
    RECT main{};
    if (!GetWindowRect(g_popupWnd, &main)) return;
    const int x = main.left + static_cast<int>(std::lround(b.x * g_scale));
    const int y = main.top + static_cast<int>(std::lround(b.y * g_scale));
    const int width = std::max(8, static_cast<int>(std::lround(b.w * g_scale)));
    const int height = std::max(8, static_cast<int>(std::lround(b.h * g_scale)));
    SetWindowPos(g_barWheelWnd, HWND_TOPMOST, x, y, width, height,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

void ShowPopupAnimated() {
    // Never leave a previous XAML volume popup over a GDI+ event.
    xaml_osd::Hide();
    if (!g_popupWnd) return;
    const bool wasVisible = IsWindowVisible(g_popupWnd) != FALSE;
    const bool reversingFade = g_fadeActive && g_fadeOut;
    if (!wasVisible) g_fadeAlpha = g_fadeEnabled.load() ? 0 : 255;
    if (!g_fadeEnabled.load()) g_fadeAlpha = 255;
    ShowWindow(g_popupWnd, SW_SHOWNOACTIVATE);
    if (!wasVisible || reversingFade) BeginFade(false);
    // Repeated volume-key events must not perpetually restart fade-in.
    RenderPopup();
    UpdateBarWheelWindow();
    UpdateSpeakerHitWindow();
}

void SetNoticeHitTesting(bool enabled) {
    if (!g_popupWnd) return;
    LONG_PTR flags = GetWindowLongPtrW(g_popupWnd, GWL_EXSTYLE);
    const LONG_PTR wanted = enabled ? (flags & ~WS_EX_TRANSPARENT)
                                       : (flags | WS_EX_TRANSPARENT);
    if (flags != wanted) {
        SetWindowLongPtrW(g_popupWnd, GWL_EXSTYLE, wanted);
        SetWindowPos(g_popupWnd, nullptr, 0, 0, 0, 0,
            SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }
}

// Input is a single event group, not a new connection check or repeated poll.
void AddNoticeEvent(NoticeCategory category, NoticeAction action,
                    std::wstring identity, std::wstring label) {
    if (!g_receiveWnd || g_closing.load()) return;
    if (identity.empty()) identity = label;
    if (label.empty()) label = std::wstring(NoticeCategoryLabel(category)) +
        L" " + Tr(OsdText::Device);
    if (g_noticeBatch.pending &&
        (g_noticeBatch.category != category || g_noticeBatch.action != action))
        FlushNoticeBatch();
    if (!g_noticeBatch.pending) {
        g_noticeBatch = NoticeBatch{};
        g_noticeBatch.pending = true;
        g_noticeBatch.category = std::move(category);
        g_noticeBatch.action = std::move(action);
    }
    if (label.size() > 120) label.resize(120);
    if (identity.size() > 2048) identity.resize(2048);
    if (g_noticeBatch.identities.insert(identity).second &&
        g_noticeBatch.names.size() < 64)
        g_noticeBatch.names.push_back(std::move(label));
    // 320 ms debounce; repeated device-interface announcements coalesce.
    SetTimer(g_receiveWnd, kEventBatchTimer, 320, nullptr);
}

void FlushNoticeBatch() {
    if (g_receiveWnd) KillTimer(g_receiveWnd, kEventBatchTimer);
    if (!g_noticeBatch.pending) return;
    NoticeBatch batch = std::move(g_noticeBatch);
    g_noticeBatch = NoticeBatch{};
    if (batch.names.empty()) return;
    g_noticeDetails = batch.names;
    g_noticeScroll = 0;
    g_noticeClickable = batch.names.size() > 1;
    std::wstring title;
    std::wstring body;
    if (batch.names.size() == 1) {
        title = batch.names[0];
        body = NoticeActionLabel(batch.action);
    } else {
        title = std::wstring(NoticeCategoryLabel(batch.category)) + L" (" +
                std::to_wstring(batch.names.size()) + L" " + Tr(OsdText::CountUnit) +
                L") " + NoticeActionLabel(batch.action);
        body = Tr(OsdText::ViewDetails);
    }
    const NoticeIcon icon = batch.category == NoticeCategory::Bluetooth
        ? NoticeIcon::Bluetooth : batch.category == NoticeCategory::Network
        ? NoticeIcon::Network : NoticeIcon::Usb;
    ShowNotice(std::move(title), std::move(body),
        batch.category == NoticeCategory::Network ? DurationKind::Network : DurationKind::Devices,
        icon);
}

void ShowNotice(std::wstring title, std::wstring body, DurationKind kind,
                NoticeIcon icon) {
    if (g_closing || !g_popupWnd) return;
    if (kind != DurationKind::Clipboard) ClearClipboardThumbnail();
    ClosePanel();
    g_popupKind = PopupKind::Notification;
    g_noticeTitle = std::move(title);
    g_noticeBody = std::move(body);
    g_noticeIcon = icon;
    BrightnessEvent ev{};
    MovePopupToDisplay(ev);
    // Every USB/Bluetooth/network notice, including a multi-device batch,
    // is now native XAML when selected. Never revert interactive details
    // to GDI+ because a notice has multiple device names.
    if (g_xamlForMigrated.load()) {
        if (icon == NoticeIcon::Clipboard) {
            ShowMigratedXamlClipboardNotice();
            return;
        }
        if (icon == NoticeIcon::Usb || icon == NoticeIcon::Bluetooth ||
            icon == NoticeIcon::Network) {
            ShowMigratedXamlDeviceNotice(kind);
            return;
        }
    }
    SetNoticeHitTesting(g_noticeClickable);
    ShowPopupAnimated();
    UpdateArrowHitWindow();
    ResetHideTimerFor(kind);
}

// ============================================================
// Clipboard event processing
// ============================================================
void ProcessClipboard() {
    if (!g_showClipboardOsd.load()) return;
    if (!OpenClipboard(g_receiveWnd)) return;
    std::wstring title = Tr(OsdText::Clipboard), body = Tr(OsdText::ContentCopied);
    HBITMAP newThumbnail = nullptr;
    if (IsClipboardFormatAvailable(CF_BITMAP) ||
        IsClipboardFormatAvailable(CF_DIB) ||
        IsClipboardFormatAvailable(CF_DIBV5)) {
        title = Tr(OsdText::ImageCopied);
        body = Tr(OsdText::ClipboardImage);
        if (g_clipboardImagePreview.load()) {
            HBITMAP source = static_cast<HBITMAP>(GetClipboardData(CF_BITMAP));
            BITMAP bm{};
            if (source && GetObjectW(source, sizeof(bm), &bm) == sizeof(bm) &&
                bm.bmWidth > 0 && bm.bmHeight > 0 &&
                bm.bmWidth <= 16384 && bm.bmHeight <= 16384) {
                // Bound the copied bitmap and preserve aspect ratio. We only
                // retain this preview, never the full clipboard image.
                const double scale = std::min(
                    static_cast<double>(kClipboardImageMaxW) / bm.bmWidth,
                    static_cast<double>(kClipboardImageMaxH) / bm.bmHeight);
                const int width = std::clamp(
                    static_cast<int>(std::lround(bm.bmWidth * scale)),
                    1, static_cast<int>(kClipboardImageMaxW));
                const int height = std::clamp(
                    static_cast<int>(std::lround(bm.bmHeight * scale)),
                    1, static_cast<int>(kClipboardImageMaxH));
                newThumbnail = static_cast<HBITMAP>(CopyImage(
                    source, IMAGE_BITMAP, width, height, LR_CREATEDIBSECTION));
            }
        }
    } else if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
        title = Tr(OsdText::TextCopied);
        body = Tr(OsdText::ClipboardText);
        if (g_clipboardTextPreview.load()) {
            HANDLE handle = GetClipboardData(CF_UNICODETEXT);
            SIZE_T cb = handle ? GlobalSize(handle) : 0;
            if (handle && cb >= sizeof(wchar_t)) {
                const wchar_t* text = static_cast<const wchar_t*>(GlobalLock(handle));
                if (text) {
                    const size_t bound = std::min<size_t>(cb / sizeof(wchar_t),
                            static_cast<size_t>(g_clipboardChars.load()) + 1);
                    body.clear();
                    for (size_t i = 0; i < bound && text[i]; ++i) {
                        const wchar_t ch = text[i];
                        body.push_back(ch < 0x20 || ch == 0x7f ? L' ' : ch);
                    }
                    if (cb / sizeof(wchar_t) > body.size() &&
                        body.size() >= static_cast<size_t>(g_clipboardChars.load()))
                        body += L"…";
                    GlobalUnlock(handle);
                }
            }
            if (body.empty()) body = Tr(OsdText::EmptyText);
        }
    } else if (IsClipboardFormatAvailable(CF_HDROP)) {
        title = Tr(OsdText::FilesCopied);
        body = Tr(OsdText::ClipboardFiles);
    }
    CloseClipboard();
    ClearClipboardThumbnail();
    g_noticeClickable = false;
    g_noticeDetails.clear();
    g_noticeScroll = 0;
    g_clipboardThumbnail = newThumbnail;
    ShowNotice(std::move(title), std::move(body), DurationKind::Clipboard,
               NoticeIcon::Clipboard);
}

// ============================================================
// USB, network and Bluetooth device event handlers
// ============================================================
// Event-based USB interface notifications and OS connectivity hints.
// Bluetooth uses typed Windows DeviceWatcher projections below.

// The network APIs were introduced in Windows 10 2004. Win32 ABI avoids
// depending on newer MinGW header definitions on an older Windhawk compiler.
struct NetworkHintAbi {
    LONG connectivityLevel;
    LONG connectivityCost;
    BOOLEAN approachingLimit;
    BOOLEAN overLimit;
    BOOLEAN roaming;
};
static_assert(sizeof(NetworkHintAbi) == 12);
using NetworkCallback = void (WINAPI*)(void*, NetworkHintAbi);
using RegisterNetworkHint = DWORD (WINAPI*)(NetworkCallback, void*, BOOLEAN, HANDLE*);
using GetNetworkHint = DWORD (WINAPI*)(NetworkHintAbi*);
using CancelNetworkHint = DWORD (WINAPI*)(HANDLE);

void WINAPI NetworkChanged(void*, NetworkHintAbi hint) {
    const int prior = g_networkPreviousLevel.exchange(hint.connectivityLevel);
    if (!g_showNetworkEvents.load() || g_closing ||
        prior == hint.connectivityLevel || prior < 0) return;
    HWND receiver = g_networkReceiver.load(std::memory_order_relaxed);
    if (receiver) PostMessageW(receiver, kNetworkNoticeMessage,
                               static_cast<WPARAM>(hint.connectivityLevel), 0);
}

void CaptureNetworkBaseline() {
    g_networkInterfaces.clear();
    for (auto& item : GetNetworkSnapshot())
        g_networkInterfaces.emplace(item.first, std::move(item.second));
}
void InitNetworkEvents() {
    g_networkDll = LoadLibraryExW(L"iphlpapi.dll", nullptr,
                                  LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!g_networkDll) return;
    const auto getHint = reinterpret_cast<GetNetworkHint>(
        GetProcAddress(g_networkDll, "GetNetworkConnectivityHint"));
    const auto subscribe = reinterpret_cast<RegisterNetworkHint>(
        GetProcAddress(g_networkDll, "NotifyNetworkConnectivityHintChange"));
    if (!getHint || !subscribe) return;
    CaptureNetworkBaseline();
    NetworkHintAbi state{};
    if (getHint(&state) == NO_ERROR)
        g_networkPreviousLevel.store(state.connectivityLevel);
    if (subscribe(NetworkChanged, nullptr, FALSE, &g_networkNotification) != NO_ERROR)
        g_networkNotification = nullptr;
}

void InitDeviceEvents() {
    DEV_BROADCAST_DEVICEINTERFACE_W usb{};
    usb.dbcc_size = sizeof(usb);
    usb.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    usb.dbcc_classguid = kUsbDeviceInterface;
    g_usbNotification = RegisterDeviceNotificationW(
        g_receiveWnd, &usb, DEVICE_NOTIFY_WINDOW_HANDLE);
    bt_monitor::Start(); // No-op unless opt-in is enabled.
}

void StopDeviceEvents() {
    // Revoke WinRT callbacks before destroying the UI receiver or COM MTA.
    bt_monitor::Stop();
    if (g_usbNotification) UnregisterDeviceNotification(g_usbNotification);
    g_usbNotification = nullptr;
    if (g_networkNotification && g_networkDll) {
        const auto cancel = reinterpret_cast<CancelNetworkHint>(
            GetProcAddress(g_networkDll, "CancelMibChangeNotify2"));
        if (cancel) cancel(g_networkNotification);
    }
    g_networkNotification = nullptr;
    if (g_networkDll) FreeLibrary(g_networkDll);
    g_networkDll = nullptr;
}

// This may fail for removed devices; the arrival-side path cache is
// preferred on removal. Interface descriptions are not physical-device IDs.
std::wstring UsbDeviceLabel(const std::wstring& path) {
    HDEVINFO devices = SetupDiCreateDeviceInfoList(nullptr, nullptr);
    if (devices == INVALID_HANDLE_VALUE) return Tr(OsdText::UsbDevice);
    SP_DEVICE_INTERFACE_DATA iface{};
    iface.cbSize = sizeof(iface);
    std::wstring label = Tr(OsdText::UsbDevice);
    if (SetupDiOpenDeviceInterfaceW(devices, path.c_str(), 0, &iface)) {
        SP_DEVINFO_DATA info{};
        info.cbSize = sizeof(info);
        DWORD required = 0;
        SetupDiGetDeviceInterfaceDetailW(devices, &iface, nullptr, 0, &required, &info);
        WCHAR value[256]{};
        DWORD type = 0;
        if (SetupDiGetDeviceRegistryPropertyW(devices, &info, SPDRP_FRIENDLYNAME,
                &type, reinterpret_cast<PBYTE>(value), sizeof(value), &required) ||
            SetupDiGetDeviceRegistryPropertyW(devices, &info, SPDRP_DEVICEDESC,
                &type, reinterpret_cast<PBYTE>(value), sizeof(value), &required)) {
            if (value[0]) label.assign(value, std::min<size_t>(wcslen(value), 80));
        }
    }
    SetupDiDestroyDeviceInfoList(devices);
    return label;
}

// Capture interface transitions on network-hint events. A connectivity hint
// alone does not expose an SSID or a VPN connection's authenticated status.
std::vector<std::pair<std::string, NetInterfaceState>> GetNetworkSnapshot() {
    std::vector<std::pair<std::string, NetInterfaceState>> out;
    ULONG size = 16 * 1024;
    std::vector<BYTE> buffer(size);
    ULONG err = GetAdaptersAddresses(AF_UNSPEC,
        GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
        GAA_FLAG_SKIP_DNS_SERVER, nullptr,
        reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &size);
    if (err == ERROR_BUFFER_OVERFLOW && size <= 256 * 1024) {
        buffer.resize(size);
        err = GetAdaptersAddresses(AF_UNSPEC,
            GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
            GAA_FLAG_SKIP_DNS_SERVER, nullptr,
            reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &size);
    }
    if (err != NO_ERROR) return out;
    const auto* adapter = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());
    for (int count = 0; adapter && count < 128;
         adapter = adapter->Next, ++count) {
        if (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
        NetInterfaceState state;
        state.connected = adapter->OperStatus == IfOperStatusUp;
        state.name = adapter->FriendlyName ? adapter->FriendlyName : Tr(OsdText::NetworkInterface);
        if (state.name.size() > 80) state.name.resize(80);
        out.emplace_back(adapter->AdapterName ? adapter->AdapterName : "",
                         std::move(state));
    }
    return out;
}

bool CaptureNetworkEvents() {
    auto current = GetNetworkSnapshot();
    if (current.empty()) return false;
    bool changed = false;
    for (const auto& item : current) {
        auto previous = g_networkInterfaces.find(item.first);
        if (previous != g_networkInterfaces.end() &&
            previous->second.connected != item.second.connected) {
            AddNoticeEvent(NoticeCategory::Network, item.second.connected ?
                NoticeAction::Connected : NoticeAction::Disconnected,
                std::wstring(item.first.begin(), item.first.end()), item.second.name);
            changed = true;
        }
    }
    g_networkInterfaces.clear();
    for (auto& item : current) g_networkInterfaces.emplace(item.first, std::move(item.second));
    return changed;
}

bool HandleDeviceChange(WPARAM type, LPARAM value) {
    if (!value) return false;
    const auto* header = reinterpret_cast<const DEV_BROADCAST_HDR*>(value);
    if (header->dbch_size < sizeof(DEV_BROADCAST_HDR)) return false;
    if (header->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE &&
        (type == DBT_DEVICEARRIVAL || type == DBT_DEVICEREMOVECOMPLETE)) {
        if (header->dbch_size < sizeof(DEV_BROADCAST_DEVICEINTERFACE_W) - sizeof(WCHAR))
            return false;
        const auto* dev = reinterpret_cast<const DEV_BROADCAST_DEVICEINTERFACE_W*>(value);
        if (!IsEqualGUID(dev->dbcc_classguid, kUsbDeviceInterface)) return false;
        if (!g_showUsbEvents.load()) return true;
        const size_t pathMax = (header->dbch_size -
            offsetof(DEV_BROADCAST_DEVICEINTERFACE_W, dbcc_name)) / sizeof(WCHAR);
        if (pathMax == 0) return true;
        const size_t maxChars = std::min<size_t>(pathMax, 2048);
        size_t pathChars = 0;
        while (pathChars < maxChars && dev->dbcc_name[pathChars]) ++pathChars;
        const std::wstring path(dev->dbcc_name, pathChars);
        if (path.empty()) return true;
        std::wstring label;
        auto known = g_usbNames.find(path);
        if (known != g_usbNames.end()) label = known->second;
        else label = UsbDeviceLabel(path);
        if (type == DBT_DEVICEARRIVAL) {
            if (g_usbNames.size() >= 256) g_usbNames.clear();
            g_usbNames[path] = label;
        } else {
            g_usbNames.erase(path);
        }
        AddNoticeEvent(NoticeCategory::Usb, type == DBT_DEVICEARRIVAL ?
            NoticeAction::Connected : NoticeAction::Removed,
                       path, label);
        return true;
    }
    return false;
}

// --- Bluetooth AEP watcher (Classic + LE), UI-thread-owned WinRT objects. ---
// The old v1.7.6 crash experiment built its own IInspectable delegates and
// guessed vtable slots. Here the Windows projection owns all COM ABI details.
// Callbacks NEVER touch HWND/GDI+, native Bluetooth handles or notification UI.
namespace bt_monitor {
namespace de = winrt::Windows::Devices::Enumeration;
namespace db = winrt::Windows::Devices::Bluetooth;
namespace fc = winrt::Windows::Foundation::Collections;


enum class Change : uint8_t { Added, Updated, Removed, Completed };
struct Event {
    int transport = 0; // 0=Bluetooth Classic, 1=Bluetooth LE.
    Change change = Change::Added;
    std::wstring id, name;
    bool connectionPresent = false, connected = false;
};
struct DeviceState {
    std::wstring name;
    bool connectionKnown = false, connected = false;
};
struct CallbackGate {
    std::atomic<bool> enabled{true};
    std::atomic<unsigned> inFlight{0};
};
struct Watcher {
    de::DeviceWatcher value{nullptr};
    winrt::event_token added{}, updated{}, removed{}, enumerated{};
    std::shared_ptr<CallbackGate> gate;
};

// The receive window owns all device states. Callback threads only append to
// this short, bounded queue, then post a zero-payload message to the OSD UI.
[[clang::no_destroy]] std::mutex queueMutex;
[[clang::no_destroy]] std::vector<Event> queue;
[[clang::no_destroy]] std::unordered_map<std::wstring, DeviceState> known;
[[clang::no_destroy]] std::array<std::unique_ptr<Watcher>, 2> watchers;
std::array<bool, 2> enumerationComplete{};
std::atomic<HWND> receiver{nullptr};
std::atomic<bool> accepting{false};

std::wstring Limited(winrt::hstring const& input, size_t maxChars) {
    return {input.c_str(), std::min<size_t>(input.size(), maxChars)};
}

bool TryConnected(fc::IMapView<winrt::hstring, winrt::Windows::Foundation::IInspectable>
                  const& properties, bool& connected) {
    if (!properties || !properties.HasKey(kConnectedProperty)) return false;
    auto value = properties.Lookup(kConnectedProperty);
    if (!value) return false;
    connected = winrt::unbox_value<bool>(value);
    return true;
}

void Post(Event&& event) {
    if (!accepting.load(std::memory_order_acquire) ||
        g_closing.load(std::memory_order_relaxed)) return;
    HWND target = receiver.load(std::memory_order_acquire);
    if (!target) return;
    bool queued = false;
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        queued = accepting.load(std::memory_order_relaxed) &&
                 queue.size() < kMaxQueuedEvents;
        if (queued) queue.emplace_back(std::move(event));
    }
    // A failed PostMessage leaves the event in the queue. Any later callback
    // will retry; there is no heap pointer stranded in a destroyed HWND.
    if (queued) (void)PostMessageW(target, kBluetoothQueueMessage, 0, 0);
}

template <typename Fn>
void WithGate(std::weak_ptr<CallbackGate> const& weak, Fn&& action) noexcept {
    auto gate = weak.lock();
    if (!gate) return;
    gate->inFlight.fetch_add(1, std::memory_order_acq_rel);
    if (gate->enabled.load(std::memory_order_acquire)) {
        try { action(); } catch (...) {
            // A broken device property is not allowed to cross WinRT's ABI.
        }
    }
    gate->inFlight.fetch_sub(1, std::memory_order_acq_rel);
}

void Stop() {
    accepting.store(false, std::memory_order_release);
    receiver.store(nullptr, std::memory_order_release);
    for (auto& watcher : watchers) {
        if (!watcher) continue;
        watcher->gate->enabled.store(false, std::memory_order_release);
        try {
            // Revoke every callback before Stop, especially during mod unload.
            if (watcher->added.value) watcher->value.Added(watcher->added);
            if (watcher->updated.value) watcher->value.Updated(watcher->updated);
            if (watcher->removed.value) watcher->value.Removed(watcher->removed);
            if (watcher->enumerated.value)
                watcher->value.EnumerationCompleted(watcher->enumerated);
            auto status = watcher->value.Status();
            if (status == de::DeviceWatcherStatus::Started ||
                status == de::DeviceWatcherStatus::EnumerationCompleted)
                watcher->value.Stop();
        } catch (...) {
            // Release the projection objects regardless of device removal.
        }
    }
    for (auto& watcher : watchers) {
        if (!watcher) continue;
        // All callbacks are bounded to a property read and a queue append.
        // They cannot call user callbacks or wait for the OSD message loop.
        while (watcher->gate->inFlight.load(std::memory_order_acquire))
            Sleep(1);
        watcher.reset();
    }
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        queue.clear();
    }
    known.clear();
    enumerationComplete = {false, false};
}

void StartOne(int transport, winrt::hstring const& selector) {
    auto item = std::make_unique<Watcher>();
    item->gate = std::make_shared<CallbackGate>();
    auto weak = std::weak_ptr<CallbackGate>(item->gate);
    auto properties = winrt::single_threaded_vector<winrt::hstring>(
        std::vector<winrt::hstring>{kConnectedProperty});
    item->value = de::DeviceInformation::CreateWatcher(
        selector, properties, de::DeviceInformationKind::AssociationEndpoint);

    item->added = item->value.Added([weak, transport](
        de::DeviceWatcher const&, de::DeviceInformation const& info) {
        WithGate(weak, [&] {
            Event event;
            event.transport = transport;
            event.change = Change::Added;
            event.id = Limited(info.Id(), 512);
            if (event.id.empty()) return;
            event.name = Limited(info.Name(), 80);
            event.connectionPresent = TryConnected(info.Properties(), event.connected);
            Post(std::move(event));
        });
    });
    item->updated = item->value.Updated([weak, transport](
        de::DeviceWatcher const&, de::DeviceInformationUpdate const& info) {
        WithGate(weak, [&] {
            Event event;
            event.transport = transport;
            event.change = Change::Updated;
            event.id = Limited(info.Id(), 512);
            if (event.id.empty()) return;
            // Updated is a partial property bag: missing IsConnected must
            // never be interpreted as a disconnection.
            event.connectionPresent = TryConnected(info.Properties(), event.connected);
            if (event.connectionPresent) Post(std::move(event));
        });
    });
    item->removed = item->value.Removed([weak, transport](
        de::DeviceWatcher const&, de::DeviceInformationUpdate const& info) {
        WithGate(weak, [&] {
            Event event;
            event.transport = transport;
            event.change = Change::Removed;
            event.id = Limited(info.Id(), 512);
            if (!event.id.empty()) Post(std::move(event));
        });
    });
    item->enumerated = item->value.EnumerationCompleted([weak, transport](
        de::DeviceWatcher const&, winrt::Windows::Foundation::IInspectable const&) {
        WithGate(weak, [&] {
            Event event;
            event.transport = transport;
            event.change = Change::Completed;
            Post(std::move(event));
        });
    });
    // Ownership precedes Start; an early callback can only enqueue a message.
    watchers[transport] = std::move(item);
    watchers[transport]->value.Start();
}

void Start() {
    if (!g_receiveWnd || g_closing.load() ||
        !g_showBluetoothEvents.load()) return;
    if (watchers[0] || watchers[1]) return;
    receiver.store(g_receiveWnd, std::memory_order_release);
    accepting.store(true, std::memory_order_release);
    try {
        // Paired-only selectors do not trigger scans for arbitrary unpaired
        // nearby BLE devices. Classic and LE are both tracked as AEPs.
        StartOne(0, db::BluetoothDevice::GetDeviceSelectorFromPairingState(true));
    } catch (winrt::hresult_error const& error) {
        Wh_Log(L"Bluetooth Classic watcher failed: 0x%08lX",
               static_cast<unsigned long>(error.code().value));
    } catch (...) { Wh_Log(L"Bluetooth Classic watcher failed"); }
    try {
        StartOne(1, db::BluetoothLEDevice::GetDeviceSelectorFromPairingState(true));
    } catch (winrt::hresult_error const& error) {
        Wh_Log(L"Bluetooth LE watcher failed: 0x%08lX",
               static_cast<unsigned long>(error.code().value));
    } catch (...) { Wh_Log(L"Bluetooth LE watcher failed"); }
    if (!watchers[0] && !watchers[1]) Stop();
}

void Drain() {
    std::vector<Event> events;
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        events.swap(queue);
    }
    if (!accepting.load(std::memory_order_acquire)) return;

    for (auto& event : events) {
        if (event.transport < 0 || event.transport > 1) continue;
        const size_t transport = static_cast<size_t>(event.transport);
        if (event.change == Change::Completed) {
            enumerationComplete[transport] = true; // Initial scan is silent.
            continue;
        }
        if (event.id.empty()) continue;
        const std::wstring id = (transport ? L"ble:" : L"classic:") + event.id;
        auto previous = known.find(id);
        if (event.change == Change::Removed) {
            if (previous != known.end()) {
                if (enumerationComplete[transport] &&
                    previous->second.connectionKnown && previous->second.connected &&
                    g_showBluetoothEvents.load())
                    AddNoticeEvent(NoticeCategory::Bluetooth,
                        NoticeAction::Disconnected, id,
                        previous->second.name.empty() ? Tr(OsdText::BluetoothDevice)
                                                      : previous->second.name);
                known.erase(previous);
            }
            continue;
        }
        if (previous == known.end()) {
            if (known.size() >= kMaxKnownDevices) continue;
            previous = known.emplace(id, DeviceState{}).first;
        }
        auto& current = previous->second;
        if (!event.name.empty()) current.name = std::move(event.name);
        if (!event.connectionPresent) continue;
        const bool changed = !current.connectionKnown ||
                             current.connected != event.connected;
        // A first Updated state may be a late initial snapshot. Report only
        // known-state changes, or a newly Added connected device after scan.
        // A first false observation is never a disconnection transition.
        const bool shouldNotify = enumerationComplete[transport] && changed &&
                                  (current.connectionKnown ||
                                   (event.change == Change::Added && event.connected));
        current.connected = event.connected;
        current.connectionKnown = true;
        if (shouldNotify && g_showBluetoothEvents.load())
            AddNoticeEvent(NoticeCategory::Bluetooth,
                event.connected ? NoticeAction::Connected : NoticeAction::Disconnected,
                id, current.name.empty() ? Tr(OsdText::BluetoothDevice)
                                         : current.name);
    }
}
} // namespace bt_monitor

// ============================================================
// Master and multi-display rendering
// ============================================================
// No DDC or monitor I/O, timers or extra worker threads in this renderer.
// Draw to premultiplied BGRA pixels before publishing a layered surface.
struct PopupFrame {
    HWND window = nullptr;
    int width = 0, height = 0;
    float scale = 1.0f;
    BrightnessEvent brightness{};
};
// One GDI+ painter is shared by the master popup and all DDC-target peers.
// A peer never mutates the global HWND, brightness snapshot or DPI state.
bool RenderPopupFrame(const PopupFrame& frame, bool publishMirrors) {
    if (!frame.window || !g_gdiplusToken || frame.width <= 0 ||
        frame.height <= 0 || frame.width > 4096 || frame.height > 4096 ||
        static_cast<uint64_t>(frame.width) * frame.height > 8388608ULL)
        return false;
    HDC screen = GetDC(nullptr);
    if (!screen) return false;
    HDC memory = CreateCompatibleDC(screen);
    if (!memory) { ReleaseDC(nullptr, screen); return false; }
    bool published = false;

    void* pixels = nullptr;
    HBITMAP bitmap = CreateArgbDib(screen, frame.width, frame.height, &pixels);
    if (bitmap && pixels) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        {
            Gdiplus::Bitmap surface(frame.width, frame.height, frame.width * 4,
                                    PixelFormat32bppPARGB,
                                    static_cast<BYTE*>(pixels));
            Gdiplus::Graphics gfx(&surface);
            gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
            gfx.Clear(Gdiplus::Color(0, 0, 0, 0));
            gfx.ScaleTransform(frame.scale, frame.scale);
            if (g_popupKind == PopupKind::LockStatus) {
                DrawLockStatus(gfx);
            } else if (g_popupKind == PopupKind::Notification) {
                DrawNotification(gfx);
            } else if (g_popupKind == PopupKind::NativeEvent) {
                DrawNativeEvent(gfx);
            } else if (g_verticalVolumeBrightness.load(std::memory_order_relaxed)) {
                DrawVerticalPopup(gfx, frame.brightness);
            } else if (g_popupKind == PopupKind::NativeVolume) {
                DrawHorizontalVolume(gfx);
            } else {

            const bool light = IsLightTheme();
            const DWORD backgroundRgb =
                OsdBackgroundRgb(light);
            const DWORD textRgb =
                OsdTextRgb(light);
            const DWORD trackRgb =
                OsdTrackRgb(light);
            const DWORD accentRgb =
                OsdAccentRgb();
            const BYTE backgroundAlpha = OsdBackgroundAlpha();
            const Gdiplus::Color card =
                ToGdiColor(backgroundRgb, backgroundAlpha);
            const Gdiplus::Color foreground = ToGdiColor(textRgb);
            const Gdiplus::Color accent = ToGdiColor(accentRgb);
            const Gdiplus::Color trackColor = ToGdiColor(trackRgb);
            const float corner = static_cast<float>(g_cornerRadius.load());
            const float logicalW = MainLogicalWidth();
            const float logicalH = MainLogicalHeight();
            const float centerY = MainCenterY();

            // Notification Center Styler's Borderless theme suppresses
            // XAML border thickness and shadows. Our popup is independent
            // GDI+, so replicate just these two appearance choices without
            // interfering with that mod or its settings.
            const bool borderless =
                g_ddcBorderless.load(std::memory_order_relaxed);
            if (!borderless) {
                // Legacy Fluent-style soft shadow.
                for (int layer = 5; layer >= 1; --layer) {
                    Gdiplus::GraphicsPath shadow;
                    const float grow = static_cast<float>(layer);
                    AddRoundedRect(shadow, 13.0f - grow * 0.4f,
                                   10.0f + grow * 0.5f,
                                   (logicalW - 26.0f) + grow * 0.8f,
                                   (logicalH - 23.0f) + grow * 0.8f,
                                   corner + grow * 0.25f);
                    Gdiplus::SolidBrush brush(Gdiplus::Color(
                        static_cast<BYTE>(light ? 6 : 12), 0, 0, 0));
                    gfx.FillPath(&brush, &shadow);
                }
            }
            Gdiplus::GraphicsPath body;
            AddRoundedRect(body, 13.0f, 10.0f, logicalW - 26.0f, logicalH - 23.0f, corner);
            Gdiplus::SolidBrush background(card);
            gfx.FillPath(&background, &body);
            if (!borderless) {
                Gdiplus::Pen outline(light
                    ? Gdiplus::Color(255, 213, 215, 220)
                    : Gdiplus::Color(255, 81, 82, 87), 0.8f);
                gfx.DrawPath(&outline, &body);
            }

            // Fluent-like sun icon; geometry is independent of installed
            // symbol fonts, so it stays consistent across Windows builds.
            if (g_showSun.load(std::memory_order_relaxed)) {
            Gdiplus::Pen sunPen(foreground, 1.85f);
            sunPen.SetStartCap(Gdiplus::LineCapRound);
            sunPen.SetEndCap(Gdiplus::LineCapRound);
            gfx.DrawEllipse(&sunPen, 44.5f, centerY - 6.0f, 12.0f, 12.0f);
            for (int i = 0; i < 8; ++i) {
                const float a = kTau * i / 8.0f;
                const float sx = std::cos(a), sy = std::sin(a);
                gfx.DrawLine(&sunPen, 50.5f + sx * 9.6f,
                             centerY + sy * 9.6f,
                             50.5f + sx * 12.0f,
                             centerY + sy * 12.0f);
            }

            }
            bool known = false;
            int percent = 0;
            DWORD rawBrightness = frame.brightness.value;
            if (g_popupKind == PopupKind::NativeBrightness) {
                known = g_nativePercentKnown;
                percent = std::clamp(g_nativePercent, 0, 100);
                rawBrightness = static_cast<DWORD>(std::max(g_nativePercent, 0));
            } else {
                percent = BrightnessPercent(frame.brightness, &known);
            }
            const bool showValue = g_showValue.load();
            const float barX = g_showSun.load() ? 80.0f : 38.0f;
            const float barRight = logicalW - (showValue ? 79.0f : 30.0f);
            const float barW = barRight - barX;
            const float barH = static_cast<float>(g_barThickness.load());
            const float barMid = centerY;
            const float barY = barMid - barH / 2.0f;
            Gdiplus::GraphicsPath track;
            AddRoundedRect(track, barX, barY, barW, barH, barH / 2.0f);
            Gdiplus::SolidBrush trackBrush(trackColor);
            gfx.FillPath(&trackBrush, &track);
            if (known && percent > 0) {
                const float filled = barW * percent / 100.0f;
                // A real clipped rounded bar prevents rectangular ends.
                Gdiplus::GraphicsPath fill;
                AddRoundedRect(fill, barX, barY,
                               std::max(barH, filled), barH, barH / 2.0f);
                gfx.SetClip(Gdiplus::RectF(barX, barY, filled, barH));
                Gdiplus::SolidBrush accentBrush(accent);
                gfx.FillPath(&accentBrush, &fill);
                gfx.ResetClip();
            }
            if (known)
                DrawTrackThumb(gfx, barX + barW * percent / 100.0f,
                               barMid, accent, light);

            if (showValue) {
            WCHAR number[48]{};
            if (known) swprintf_s(number, L"%d%%", percent);
            else swprintf_s(number, L"%lu", rawBrightness);
            Gdiplus::Font font(L"Segoe UI Variable Text",
                               static_cast<float>(g_fontSize.load()),
                               Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
            if (font.GetLastStatus() != Gdiplus::Ok) {
                Gdiplus::Font fallback(L"Segoe UI",
                                       static_cast<float>(g_fontSize.load()),
                                       Gdiplus::FontStyleBold,
                                       Gdiplus::UnitPixel);
                Gdiplus::SolidBrush textBrush(foreground);
                Gdiplus::StringFormat format;
                format.SetAlignment(Gdiplus::StringAlignmentFar);
                format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                gfx.DrawString(number, -1, &fallback,
                               Gdiplus::RectF(logicalW - 72.0f, centerY - 17.5f, 42.0f, 36.0f),
                               &format, &textBrush);
            } else {
                Gdiplus::SolidBrush textBrush(foreground);
                Gdiplus::StringFormat format;
                format.SetAlignment(Gdiplus::StringAlignmentFar);
                format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                gfx.DrawString(number, -1, &font,
                               Gdiplus::RectF(logicalW - 72.0f, centerY - 17.5f, 42.0f, 36.0f),
                               &format, &textBrush);
            }
            } // g_showValue
            } // horizontal renderer
        }
        if (!PublishArgbLayer(frame.window, screen, memory,
                              frame.width, frame.height)) {
            Wh_Log(L"UpdateLayeredWindow failed: %lu", GetLastError());
        } else {
            published = true;
        }
        if (publishMirrors && published &&
            g_displayOutputMode.load(std::memory_order_relaxed) == 3 &&
            g_popupKind != PopupKind::DdcBrightness)
            RenderMirroredFrame(screen, pixels, frame.width, frame.height, false);
        SelectObject(memory, previous);
        DeleteObject(bitmap);
    }
    DeleteDC(memory);
    ReleaseDC(nullptr, screen);
    return published;
}
void RenderPopup() {
    PopupFrame master{g_popupWnd, g_width, g_height, g_scale, g_visible};
    if (!RenderPopupFrame(master, true)) return;
    if (g_popupKind == PopupKind::DdcBrightness) {
        const int mode = g_displayOutputMode.load(std::memory_order_relaxed);
        if (mode == 0 || mode == 3) RenderDdcTargetPeers();
    }
}

struct PopupPlacement {
    float scale = 1.0f;
    int width = 0, height = 0;
    RECT work{}, monitorBounds{}, bounds{};
};
bool CalculatePopupPlacement(HMONITOR monitor, PopupPlacement& p) {
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(monitor, &mi)) return false;
    UINT dpiX = 96, dpiY = 96;
    if (GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY) != S_OK)
        dpiX = 96;
    // Apply an independent user-selected size factor after monitor DPI.
    // The renderer keeps the same Win11-inspired vector geometry.
    const float dpiScale = std::clamp(dpiX / 96.0f, 0.75f, 3.0f);
    const float sizeScale =
        g_ddcSizePercent.load(std::memory_order_relaxed) / 100.0f;
    p.scale = dpiScale * sizeScale;
    const bool vertical = g_verticalVolumeBrightness.load(
        std::memory_order_relaxed);
    const bool statusNotice = g_popupKind == PopupKind::LockStatus ||
        g_popupKind == PopupKind::NativeEvent ||
        g_popupKind == PopupKind::Notification;
    const bool imageNotice = g_popupKind == PopupKind::Notification &&
        g_clipboardThumbnail;
    const float logicalWidth = imageNotice ? kClipboardImageCanvasW :
        statusNotice ? kStatusNoticeWidth : MainLogicalWidth();
    const float logicalHeight = imageNotice ? kClipboardImageCanvasH :
        statusNotice ? kStatusNoticeHeight : MainLogicalHeight();
    p.width = static_cast<int>(std::lround(logicalWidth * p.scale));
    p.height = static_cast<int>(std::lround(logicalHeight * p.scale));
    const RECT& work = mi.rcWork;
    const RECT& display = mi.rcMonitor;
    const int margin = static_cast<int>(std::lround(24.0f * dpiScale));
    // Center always means the actual screen center, regardless of taskbar
    // placement. Edge positions still avoid the taskbar via rcWork.
    const int centerX = display.left +
        ((display.right - display.left) - p.width) / 2;
    const int centerY = display.top +
        ((display.bottom - display.top) - p.height) / 2;
    const int leftX = work.left + margin;
    const int rightX = work.right - p.width - margin;
    const int topY = work.top + margin;
    const int bottomY = work.bottom - p.height - margin;
    int x = centerX;
    int y = bottomY;
    // Stable mapping retains positions chosen in v1.4.1.
    // bottom center, bottom left/right, top center, center,
    // top left/right, center left/right.
    switch (g_position.load(std::memory_order_relaxed)) {
        case 1: x = leftX; break;                      // bottom-left
        case 2: x = rightX; break;                     // bottom-right
        case 3: y = topY; break;                       // top-center
        case 4: y = centerY; break;                    // center
        case 5: x = leftX; y = topY; break;            // top-left
        case 6: x = rightX; y = topY; break;           // top-right
        case 7: x = leftX; y = centerY; break;         // center-left
        case 8: x = rightX; y = centerY; break;        // center-right
        default: break;                               // bottom-center
    }
    x += static_cast<int>(std::lround(g_offsetX.load() * dpiScale));
    y += static_cast<int>(std::lround(g_offsetY.load() * dpiScale));
    // A visible SMTC/Mixer panel is a separate HWND. For the central anchors,
    // center the union of both HWND bounds, not the main OSD alone. The same
    // per-monitor calculation also positions DDC/all-screen mirror surfaces.
    const int position = g_position.load(std::memory_order_relaxed);
    bool centerGroupX = false, centerGroupY = false;
    int groupMinX = 0, groupMaxX = p.width;
    int groupMinY = 0, groupMaxY = p.height;
    if (IsExpandedVolumePanel()) {
        const int panelWidth = vertical ? static_cast<int>(std::lround(
            (g_panelMode == PanelMode::Media ? g_verticalSmtcWidth.load() :
                                               g_verticalMixerWidth.load()) * p.scale))
                                        : p.width;
        const int panelHeight = vertical ? p.height : static_cast<int>(std::lround(
            (g_panelMode == PanelMode::Media ? g_horizontalSmtcHeight.load() :
                                               g_horizontalMixerHeight.load()) * p.scale));
        const RECT unshifted{x, y, x + p.width, y + p.height};
        const auto direction = DirectionForPopup(unshifted, work, position, vertical);
        const auto attached = GetPanelAttachment(vertical, direction, p.scale,
            p.width, p.height, panelWidth, panelHeight);
        if (vertical && PositionCentersX(position)) {
            centerGroupX = true;
            groupMinX = std::min(0, attached.x);
            groupMaxX = std::max(p.width, attached.x + panelWidth);
            x += (p.width - groupMinX - groupMaxX) / 2;
        } else if (!vertical && PositionCentersY(position)) {
            centerGroupY = true;
            groupMinY = std::min(0, attached.y);
            groupMaxY = std::max(p.height, attached.y + panelHeight);
            y += (p.height - groupMinY - groupMaxY) / 2;
        }
    }
    // Clamp the entire centered pair where possible, not just its main HWND.
    // Anchored axes still use rcWork for taskbar avoidance.
    if (centerGroupX) {
        const int minX = static_cast<int>(display.left) - groupMinX;
        const int maxX = static_cast<int>(display.right) - groupMaxX;
        x = std::clamp(x, minX, std::max(minX, maxX));
    }
    else
        x = ClampPopupAxis(x, p.width,
            PositionCentersX(position) ? display : work, true);
    if (centerGroupY) {
        const int minY = static_cast<int>(display.top) - groupMinY;
        const int maxY = static_cast<int>(display.bottom) - groupMaxY;
        y = std::clamp(y, minY, std::max(minY, maxY));
    }
    else
        y = ClampPopupAxis(y, p.height,
            PositionCentersY(position) ? display : work, false);
    p.work = work;
    p.monitorBounds = display;
    p.bounds = RECT{x, y, x + p.width, y + p.height};
    return true;
}
struct MirrorScan { HMONITOR master = nullptr; std::vector<HMONITOR> peers; };
BOOL CALLBACK FindMirrorCallback(HMONITOR monitor, HDC, LPRECT, LPARAM data) {
    auto* scan = reinterpret_cast<MirrorScan*>(data);
    if (monitor != scan->master && scan->peers.size() < kMaxMirrorOutputs)
        scan->peers.push_back(monitor);
    return TRUE;
}
void HideMirroredWindows(bool onlyPanel) {
    for (auto& display : g_mirrorOutputs) {
        if (display.panel) ShowWindow(display.panel, SW_HIDE);
        if (!onlyPanel && display.popup) ShowWindow(display.popup, SW_HIDE);
    }
}
void DestroyMirroredWindows() {
    for (auto& display : g_mirrorOutputs) {
        if (display.panel) DestroyWindow(display.panel);
        if (display.popup) DestroyWindow(display.popup);
    }
    g_mirrorOutputs.clear();
}
HWND CreateMirrorSurface() {
    return CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE |
        WS_EX_LAYERED | WS_EX_TRANSPARENT,
        kWindowClass, L"", WS_POPUP, 0, 0, 1, 1,
        nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
}
void RefreshMirrorOutputs(HMONITOR master) {
    // XAML creates its own per-monitor DDC hosts. Never start the legacy
    // GDI+ replicas while the migrated DDC renderer is selected.
    if (g_xamlForMigrated.load() &&
        g_popupKind == PopupKind::DdcBrightness) {
        DestroyMirroredWindows();
        return;
    }
    const int mode = g_displayOutputMode.load(std::memory_order_relaxed);
    const bool targetDisplayMode = mode == 0 &&
        g_popupKind == PopupKind::DdcBrightness && !g_ddcTargets.empty();
    if (mode != 3 && !targetDisplayMode) {
        DestroyMirroredWindows();
        return;
    }
    MirrorScan scan{master, {}};
    EnumDisplayMonitors(nullptr, nullptr, FindMirrorCallback,
                        reinterpret_cast<LPARAM>(&scan));
    while (g_mirrorOutputs.size() < scan.peers.size()) {
        MirrorOutput display{};
        display.popup = CreateMirrorSurface();
        display.panel = CreateMirrorSurface();
        if (!display.popup || !display.panel) {
            if (display.popup) DestroyWindow(display.popup);
            if (display.panel) DestroyWindow(display.panel);
            Wh_Log(L"OSD mirror creation failed: %lu", GetLastError());
            break;
        }
        g_mirrorOutputs.push_back(display);
    }
    for (size_t i = 0; i < g_mirrorOutputs.size(); ++i) {
        MirrorOutput& display = g_mirrorOutputs[i];
        if (i >= scan.peers.size()) {
            if (display.popup) ShowWindow(display.popup, SW_HIDE);
            if (display.panel) ShowWindow(display.panel, SW_HIDE);
            display.monitor = nullptr;
            continue;
        }
        PopupPlacement place{};
        if (!CalculatePopupPlacement(scan.peers[i], place)) {
            display.monitor = nullptr;
            if (display.popup) ShowWindow(display.popup, SW_HIDE);
            if (display.panel) ShowWindow(display.panel, SW_HIDE);
            continue;
        }
        // A visible replica may still contain the *previous* monitor's
        // bitmap. Hide it before moving to another physical display.
        if (display.monitor != scan.peers[i] &&
            IsWindowVisible(display.popup))
            ShowWindow(display.popup, SW_HIDE);
        display.monitor = scan.peers[i];
        display.work = place.work;
        display.monitorBounds = place.monitorBounds;
        display.popupBounds = place.bounds;
        display.scale = place.scale;
        SetWindowPos(display.popup, HWND_TOPMOST,
            place.bounds.left, place.bounds.top,
            place.width, place.height, SWP_NOACTIVATE);
    }
}

void MovePopupToDisplay(const BrightnessEvent& ev) {
    WCHAR device[CCHDEVICENAME]{};
    const int outputMode = g_displayOutputMode.load(std::memory_order_relaxed);
    if ((outputMode == 0 ||
         (outputMode == 3 && g_popupKind == PopupKind::DdcBrightness)) &&
        ev.device[0]) {
        wcscpy_s(device, ev.device);
    } else if (outputMode == 2) {
        swprintf_s(device, L"\\\\.\\DISPLAY%d",
                   g_displayOutputNumber.load(std::memory_order_relaxed));
    }
    HMONITOR monitor = FindMonitorByDeviceName(device);
    if (!monitor)
        monitor = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    PopupPlacement place{};
    if (!CalculatePopupPlacement(monitor, place)) return;
    g_scale = place.scale;
    g_width = place.width;
    g_height = place.height;
    SetWindowPos(g_popupWnd, HWND_TOPMOST, place.bounds.left,
        place.bounds.top, place.width, place.height, SWP_NOACTIVATE);
    RefreshMirrorOutputs(monitor);
}

// Reapply anchor placement only when opening/closing a panel changes the
// expected composite bounds. This also keeps the bar/chevron/speaker input
// windows aligned with the relocated main popup.
void RefreshCompositePlacementIfChanged() {
    if (!g_popupWnd || !IsWindowVisible(g_popupWnd) || g_closing.load())
        return;
    RECT current{};
    if (!GetWindowRect(g_popupWnd, &current)) return;
    PopupPlacement expected{};
    if (!CalculatePopupPlacement(
            MonitorFromWindow(g_popupWnd, MONITOR_DEFAULTTONEAREST), expected))
        return;
    if (EqualRect(&current, &expected.bounds)) return;
    BrightnessEvent none{};
    MovePopupToDisplay(none);
    RenderPopup();
    UpdateBarWheelWindow();
    UpdateArrowHitWindow();
    UpdateSpeakerHitWindow();
}

// Paint each target's actual DDC value on its own screen. This method uses
// the existing renderer but temporarily swaps ONLY paint state on the same
// Explorer UI thread; it never repositions the master or changes controls.
// The guard prevents nested rendering from recursively rendering more peers.
void RenderDdcTargetPeers() {
    if (g_mirrorOutputs.empty()) return;
    const ULONGLONG now = GetTickCount64();
    for (auto& output : g_mirrorOutputs) {
        if (!output.monitor || !output.popup) continue;
        MONITORINFOEXW info{sizeof(info)};
        if (!GetMonitorInfoW(output.monitor, &info)) {
            ShowWindow(output.popup, SW_HIDE);
            continue;
        }
        const auto item = std::find_if(g_ddcTargets.begin(),
            g_ddcTargets.end(), [&](const DdcTargetState& target) {
                return target.expiresAt > now &&
                       _wcsicmp(target.event.device, info.szDevice) == 0;
            });
        if (item == g_ddcTargets.end()) {
            // Never mirror another display's DDC percentage to this one.
            ShowWindow(output.popup, SW_HIDE);
            continue;
        }
        const int width = output.popupBounds.right -
                          output.popupBounds.left;
        const int height = output.popupBounds.bottom -
                           output.popupBounds.top;
        if (width <= 0 || height <= 0 || width > 4096 ||
            height > 4096 || output.scale <= 0.0f) {
            ShowWindow(output.popup, SW_HIDE);
            continue;
        }
        PopupFrame frame{output.popup, width, height, output.scale,
                         item->event};
        if (RenderPopupFrame(frame, false))
            ShowWindow(output.popup, SW_SHOWNOACTIVATE);
        else
            ShowWindow(output.popup, SW_HIDE);
    }
}

// All replica HWNDs are view-only. The master premultiplied-alpha DIB is
// scaled to each monitor's independent effective DPI on the same UI thread.
// No new media/DDC worker, hooks, animation timers or network requests.
void RenderMirroredFrame(HDC screen, void* pixels, int sourceWidth,
                         int sourceHeight, bool panel) {
    if (!screen || !pixels || sourceWidth <= 0 || sourceHeight <= 0 ||
        g_scale <= 0.0f) return;
    Gdiplus::Bitmap source(sourceWidth, sourceHeight, sourceWidth * 4,
                          PixelFormat32bppPARGB, static_cast<BYTE*>(pixels));
    if (source.GetLastStatus() != Gdiplus::Ok) return;
    RECT mainPopup{}, mainPanel{};
    if (!GetWindowRect(g_popupWnd, &mainPopup)) return;
    if (panel && (!g_panelWnd || g_panelMode == PanelMode::None ||
                  !GetWindowRect(g_panelWnd, &mainPanel))) return;
    for (auto& output : g_mirrorOutputs) {
        if (!output.monitor) continue;
        HWND mirror = panel ? output.panel : output.popup;
        if (!mirror) continue;
        const float ratio = output.scale / g_scale;
        if (ratio <= 0.0f || ratio > 4.0f) continue;
        const int width = std::max(1, static_cast<int>(
            std::lround(sourceWidth * ratio)));
        const int height = std::max(1, static_cast<int>(
            std::lround(sourceHeight * ratio)));
        // Bound per-frame allocations inside explorer.exe.
        if (width > 4096 || height > 4096 ||
            static_cast<uint64_t>(width) * height > 8388608ULL) continue;
        if (panel) {
            int x = output.popupBounds.left + static_cast<int>(std::lround(
                (mainPanel.left - mainPopup.left) * ratio));
            int y = output.popupBounds.top + static_cast<int>(std::lround(
                (mainPanel.top - mainPopup.top) * ratio));
            const int position = g_position.load(std::memory_order_relaxed);
            const bool vertical = g_verticalVolumeBrightness.load();
            if (IsExpandedVolumePanel()) {
                // A peer display can have a taskbar on the opposite edge.
                // Resolve its own flyout side instead of copying the master
                // panel offset, which would break composite centering there.
                const auto direction = DirectionForPopup(
                    output.popupBounds, output.work, position, vertical);
                const auto attached = GetPanelAttachment(vertical, direction,
                    output.scale,
                    output.popupBounds.right - output.popupBounds.left,
                    output.popupBounds.bottom - output.popupBounds.top,
                    width, height);
                x = output.popupBounds.left + attached.x;
                y = output.popupBounds.top + attached.y;
            }
            // Preserve centered-axis alignment of the mirrored popup/panel.
            x = ClampPopupAxis(x, width,
                vertical || !PositionCentersX(position)
                    ? output.work : output.monitorBounds, true);
            y = ClampPopupAxis(y, height,
                !vertical || !PositionCentersY(position)
                    ? output.work : output.monitorBounds, false);
            SetWindowPos(mirror, HWND_TOPMOST, x, y, width, height,
                         SWP_NOACTIVATE);
        }
        HDC targetDC = CreateCompatibleDC(screen);
        if (!targetDC) continue;
        void* targetPixels = nullptr;
        HBITMAP bitmap = CreateArgbDib(screen, width, height, &targetPixels);
        if (bitmap && targetPixels) {
            HGDIOBJ previous = SelectObject(targetDC, bitmap);
            {
                Gdiplus::Bitmap dst(width, height, width * 4,
                    PixelFormat32bppPARGB, static_cast<BYTE*>(targetPixels));
                Gdiplus::Graphics graphics(&dst);
                graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
                graphics.SetInterpolationMode(
                    Gdiplus::InterpolationModeHighQualityBicubic);
                graphics.DrawImage(&source, Gdiplus::Rect(0, 0, width, height));
            }
            if (PublishArgbLayer(mirror, screen, targetDC,
                                 width, height))
                ShowWindow(mirror, SW_SHOWNOACTIVATE);
            SelectObject(targetDC, previous);
            DeleteObject(bitmap);
        } else if (bitmap) {
            DeleteObject(bitmap);
        }
        DeleteDC(targetDC);
    }
}

// Shared properties of all migrated XAML level indicators; the source
// value, event identity and monitor placement remain category-specific.
xaml_osd::Snapshot MakeXamlSnapshot(
        PopupKind kind, const RECT& anchor, float scale) {
    xaml_osd::Snapshot data;
    data.kind = kind == PopupKind::NativeVolume
        ? xaml_osd::LevelKind::Volume
        : kind == PopupKind::DdcBrightness
        ? xaml_osd::LevelKind::DdcBrightness
        : xaml_osd::LevelKind::NativeBrightness;
    data.brightness = kind != PopupKind::NativeVolume;
    data.receiver = g_receiveWnd;
    data.showIcon = !data.brightness || g_showSun.load();
    data.percent = g_nativePercent;
    data.rawValue = g_nativePercent;
    data.valueKnown = g_nativePercentKnown;
    data.muted = !data.brightness && g_nativeMuted;
    data.durationMs = OsdDuration(kind == PopupKind::DdcBrightness
        ? DurationKind::DdcBrightness
        : kind == PopupKind::NativeBrightness
        ? DurationKind::NativeBrightness : DurationKind::Volume);
    data.anchor = anchor;
    data.scale = scale;
    data.vertical = g_verticalVolumeBrightness.load();
    data.showValue = g_showValue.load();
    data.innerPadding = g_innerPadding.load();
    data.iconSize = g_iconSize.load();
    data.fontSize = g_fontSize.load();
    data.barThickness = g_barThickness.load();
    data.thumbDiameter = g_thumbDiameter.load();
    const bool light = IsLightTheme();
    data.background = OsdBackgroundRgb(light);
    data.backgroundAlpha = OsdBackgroundAlpha();
    data.borderless = g_ddcBorderless.load();
    data.cornerRadius = g_cornerRadius.load();
    data.fadeEnabled = g_fadeEnabled.load();
    data.fadeDurationMs = static_cast<DWORD>(g_fadeDuration.load());
    data.text = OsdTextRgb(light);
    data.accent = OsdAccentRgb();
    data.track = OsdTrackRgb(light);
    return data;
}

// All compact XAML categories share one rendering snapshot contract.
// Device/native notices and lock keys differ only in content and behavior;
// the background/theme/placement lifecycle is inherited from MakeXamlSnapshot.
xaml_osd::Snapshot MakeXamlStatusSnapshot(
        xaml_osd::LevelKind category, const RECT& anchor,
        DurationKind duration, bool fluentIcon = false) {
    auto data = MakeXamlSnapshot(
        PopupKind::NativeBrightness, anchor, g_scale);
    data.kind = category;
    data.brightness = false;
    data.valueKnown = false;
    data.showValue = false;
    data.statusFontIcon = fluentIcon;
    data.durationMs = OsdDuration(duration);
    return data;
}

void HideGdiLevelForXaml() {
    if (g_popupWnd) {
        KillTimer(g_popupWnd, kHideTimer);
        KillTimer(g_popupWnd, kFadeTimer);
        KillTimer(g_popupWnd, kMediaAnimationTimer);
        g_fadeActive = false;
        ShowWindow(g_popupWnd, SW_HIDE);
    }
    HideMirroredWindows(false);
    ClosePanel();
    if (g_barWheelWnd) ShowWindow(g_barWheelWnd, SW_HIDE);
    UpdateArrowHitWindow();
    UpdateSpeakerHitWindow();
}

// All valid DDC targets can render simultaneously on their actual displays.
// Fixed-output modes preserve the previous single-output behavior instead.
bool ShowXamlDdcTargets(const BrightnessEvent& master) {
    const int mode = g_displayOutputMode.load(std::memory_order_relaxed);
    std::vector<xaml_osd::Snapshot> batch;
    const ULONGLONG now = GetTickCount64();
    auto push = [&](const BrightnessEvent& ev,
                    const RECT& anchor, float scale) {
        auto snapshot = MakeXamlSnapshot(
            PopupKind::DdcBrightness, anchor, scale);
        snapshot.key = std::wstring(L"ddc:") + ev.device + L":" +
            std::to_wstring(ev.physicalIndex);
        wcscpy_s(snapshot.device, ev.device);
        snapshot.physicalIndex = ev.physicalIndex;
        snapshot.minimum = ev.minimum;
        snapshot.maximum = ev.maximum;
        snapshot.rawValue = static_cast<int>(ev.value);
        snapshot.percent = BrightnessPercent(ev, &snapshot.valueKnown);
        batch.push_back(std::move(snapshot));
    };

    if (mode == 0 || mode == 3) {
        for (const auto& target : g_ddcTargets) {
            if (target.expiresAt <= now) continue;
            HMONITOR monitor =
                FindMonitorByDeviceName(target.event.device);
            PopupPlacement placement{};
            if (!monitor || !CalculatePopupPlacement(monitor, placement)) {
                Wh_Log(L"XAML v1.0.24: unresolved DDC display '%s'",
                       target.event.device);
                continue;
            }
            push(target.event, placement.bounds, placement.scale);
        }
    } else {
        // Primary/selected output remains one card with the chosen event.
        RECT anchor{};
        if (g_popupWnd && GetWindowRect(g_popupWnd, &anchor))
            push(master, anchor, g_scale);
    }
    if (batch.empty()) {
        Wh_Log(L"XAML v1.0.24: no resolvable DDC snapshots");
        xaml_osd::Hide();
        return false;
    }
    const bool ok = xaml_osd::ShowBatch(batch);
    if (!ok)
        Wh_Log(L"XAML v1.0.24: DDC batch not delivered; NO GDI+ fallback");
    return ok;
}

// Coalesce writes per physical display, not across all displays. Each
// target's raw value and range survive the burst for independent painting.
void DisplayDdcBatch() {
    if (!g_ddcBatchPending) return;
    g_ddcBatchPending = false;
    std::vector<BrightnessEvent> events = std::move(g_ddcBatchEvents);
    g_ddcBatchEvents.clear();
    if (g_closing.load() || !g_showDdcBrightness.load() || events.empty())
        return;

    const ULONGLONG now = GetTickCount64();
    const int mode = g_displayOutputMode.load(std::memory_order_relaxed);
    const ULONGLONG expiry = now + static_cast<ULONGLONG>(
        OsdDuration(DurationKind::DdcBrightness));
    // The cache lasts only for the active OSD period, never indefinitely.
    g_ddcTargets.erase(std::remove_if(g_ddcTargets.begin(),
        g_ddcTargets.end(), [now](const DdcTargetState& item) {
            return item.expiresAt <= now;
        }), g_ddcTargets.end());

    BrightnessEvent master{};
    bool masterChosen = false;
    // If both displays update in the same burst, keep the already-visible
    // target as master. The other target still receives its own peer frame.
    // This prevents the master window bouncing when write order varies.
    bool pinnedMaster = false;
    if ((mode == 0 || mode == 3) &&
        g_popupKind == PopupKind::DdcBrightness && g_popupWnd &&
        IsWindowVisible(g_popupWnd) && g_visible.device[0]) {
        auto current = std::find_if(events.begin(), events.end(),
            [&](const BrightnessEvent& event) {
                return event.physicalIndex == g_visible.physicalIndex &&
                       _wcsicmp(event.device, g_visible.device) == 0;
            });
        if (current != events.end()) {
            master = *current;
            masterChosen = true;
            pinnedMaster = true;
        }
    }
    WCHAR preferredDevice[CCHDEVICENAME]{};
    if (mode == 1 || mode == 2) {
        HMONITOR preferredMonitor = nullptr;
        if (mode == 2) {
            WCHAR device[CCHDEVICENAME]{};
            swprintf_s(device, L"\\\\.\\DISPLAY%d",
                g_displayOutputNumber.load(std::memory_order_relaxed));
            preferredMonitor = FindMonitorByDeviceName(device);
        }
        if (!preferredMonitor)
            preferredMonitor = MonitorFromPoint(
                POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
        MONITORINFOEXW monitorInfo{sizeof(monitorInfo)};
        if (GetMonitorInfoW(preferredMonitor, &monitorInfo))
            wcscpy_s(preferredDevice, monitorInfo.szDevice);
    }

    for (const BrightnessEvent& ev : events) {
        const HMONITOR target = FindMonitorByDeviceName(ev.device);
        if (!target && (mode == 0 || mode == 3)) {
            if (_wcsicmp(g_ddcLastUnresolved, ev.device) != 0 ||
                !g_ddcLastUnresolved[0]) {
                wcscpy_s(g_ddcLastUnresolved, ev.device);
                Wh_Log(L"DDC event target unresolved: device='%s', "
                       L"physicalIndex=%lu, senderPID=%lu; skipping "
                       L"unknown target.", ev.device, ev.physicalIndex,
                       ev.producerPid);
            }
            continue;
        }
        if (target) {
            if (_wcsicmp(g_ddcLastTarget, ev.device) != 0) {
                wcscpy_s(g_ddcLastTarget, ev.device);
                Wh_Log(L"DDC target resolved: '%s' (physicalIndex=%lu)",
                       ev.device, ev.physicalIndex);
            }
            g_ddcLastUnresolved[0] = L'\0';
            const auto sameDevice = [&](const DdcTargetState& state) {
                return state.event.physicalIndex == ev.physicalIndex &&
                       _wcsicmp(state.event.device, ev.device) == 0;
            };
            auto it = std::find_if(g_ddcTargets.begin(),
                                   g_ddcTargets.end(), sameDevice);
            if (it != g_ddcTargets.end()) {
                it->event = ev;
                it->expiresAt = expiry;
            } else if (g_ddcTargets.size() < kMaxDdcTargets) {
                g_ddcTargets.push_back({ev, expiry});
            }
        }
        // Source mode puts the latest event on its own monitor. For fixed
        // output/mirror modes prefer that screen's value if it was updated.
        if (!masterChosen ||
            ((mode == 0 || mode == 3) && !pinnedMaster) ||
            (preferredDevice[0] &&
             _wcsicmp(preferredDevice, ev.device) == 0)) {
            master = ev;
            masterChosen = true;
        }
    }
    if (!masterChosen) return;

    ClosePanel();
    g_visible = master;
    g_lastConfirmedDdcBrightness = master.value;
    g_popupKind = PopupKind::DdcBrightness;
    MovePopupToDisplay(master);
    if (g_xamlForMigrated.load()) {
        HideGdiLevelForXaml();
        (void)ShowXamlDdcTargets(master);
        return;
    }
    SetPopupInteractive(false);
    ShowPopupAnimated();
    UpdateArrowHitWindow();
    ResetHideTimerFor(DurationKind::DdcBrightness);
}

// ============================================================
// Brightness writer worker and bar interaction
// ============================================================
// Brightness writes never execute on the OSD UI thread. Firmware DDC/CI
// can be slow, so a single sleeping worker coalesces wheel updates. This
// worker does not poll monitors and starts only in explorer.exe.
struct ScopedBstr {
    BSTR value = nullptr;
    explicit ScopedBstr(PCWSTR text) : value(SysAllocString(text)) {}
    ~ScopedBstr() { if (value) SysFreeString(value); }
    operator BSTR() const { return value; }
};

bool WriteNativeBrightnessWmi(BYTE percent) {
    // Standard Windows internal-panel provider; absent on many external panels.
    // IWbemServices calls run on the separate worker with its own MTA.
    IWbemLocator* locator = nullptr;
    // Inline COM GUIDs avoid requiring wbemuuid.lib in Windhawk/MinGW.
    if (FAILED(CoCreateInstance(kWmiLocatorClsid, nullptr, CLSCTX_INPROC_SERVER,
            kWmiLocatorIid, reinterpret_cast<void**>(&locator))) || !locator)
        return false;
    ScopedBstr ns(L"ROOT\\WMI");
    IWbemServices* service = nullptr;
    HRESULT hr = locator->ConnectServer(ns, nullptr, nullptr, nullptr, 0,
                                        nullptr, nullptr, &service);
    locator->Release();
    if (FAILED(hr) || !service) return false;
    (void)CoSetProxyBlanket(service, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE,
        nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr, EOAC_NONE);
    ScopedBstr wql(L"WQL");
    ScopedBstr query(L"SELECT * FROM WmiMonitorBrightnessMethods");
    IEnumWbemClassObject* items = nullptr;
    hr = service->ExecQuery(wql, query,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr, &items);
    if (FAILED(hr) || !items) { service->Release(); return false; }
    IWbemClassObject* instance = nullptr;
    ULONG fetched = 0;
    hr = items->Next(1200, 1, &instance, &fetched);
    items->Release();
    if (FAILED(hr) || fetched != 1 || !instance) {
        service->Release(); return false;
    }
    VARIANT path{};
    VariantInit(&path);
    hr = instance->Get(L"__PATH", 0, &path, nullptr, nullptr);
    instance->Release();
    if (FAILED(hr) || path.vt != VT_BSTR || !path.bstrVal) {
        VariantClear(&path); service->Release(); return false;
    }
    IWbemClassObject* cls = nullptr;
    ScopedBstr clsName(L"WmiMonitorBrightnessMethods");
    hr = service->GetObject(clsName, 0, nullptr, &cls, nullptr);
    IWbemClassObject* inSig = nullptr;
    IWbemClassObject* inParams = nullptr;
    ScopedBstr method(L"WmiSetBrightness");
    if (SUCCEEDED(hr) && cls) hr = cls->GetMethod(method, 0, &inSig, nullptr);
    if (SUCCEEDED(hr) && inSig) hr = inSig->SpawnInstance(0, &inParams);
    if (SUCCEEDED(hr) && inParams) {
        VARIANT brightness{};
        VariantInit(&brightness);
        brightness.vt = VT_UI1;
        brightness.bVal = percent;
        hr = inParams->Put(L"Brightness", 0, &brightness, 0);
        if (SUCCEEDED(hr)) {
            VARIANT timeout{};
            VariantInit(&timeout);
            timeout.vt = VT_UI4;
            timeout.ulVal = 0; // WmiSetBrightness Timeout is uint32 seconds.
            hr = inParams->Put(L"Timeout", 0, &timeout, 0);
        }
        if (SUCCEEDED(hr)) {
            IWbemClassObject* output = nullptr;
            hr = service->ExecMethod(path.bstrVal, method, 0, nullptr,
                                     inParams, &output, nullptr);
            if (SUCCEEDED(hr) && output) {
                VARIANT result{};
                VariantInit(&result);
                hr = output->Get(L"ReturnValue", 0, &result, nullptr, nullptr);
                if (SUCCEEDED(hr)) {
                    if (result.vt == VT_I4) hr = result.lVal == 0 ? S_OK : E_FAIL;
                    else if (result.vt == VT_UI4)
                        hr = result.ulVal == 0 ? S_OK : E_FAIL;
                    else hr = E_FAIL;
                }
                VariantClear(&result);
            } else if (SUCCEEDED(hr)) hr = E_FAIL;
            if (output) output->Release();
        }
    }
    if (inParams) inParams->Release();
    if (inSig) inSig->Release();
    if (cls) cls->Release();
    VariantClear(&path);
    service->Release();
    return SUCCEEDED(hr);
}

bool WriteExternalBrightnessDdc(const BrightnessWheelTask& task) {
    if (!task.monitor.device[0]) return false; // Never guess the monitor.
    FindDisplay display{};
    wcscpy_s(display.name, task.monitor.device);
    EnumDisplayMonitors(nullptr, nullptr, FindDisplayCallback,
                        reinterpret_cast<LPARAM>(&display));
    if (!display.monitor) return false;
    HMODULE lib = LoadLibraryExW(L"Dxva2.dll", nullptr,
                                LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!lib) return false;
    using GetCount = BOOL(WINAPI*)(HMONITOR, LPDWORD);
    using GetMonitors = BOOL(WINAPI*)(HMONITOR, DWORD, LPPHYSICAL_MONITOR);
    using DestroyMonitors = BOOL(WINAPI*)(DWORD, LPPHYSICAL_MONITOR);
    using SetVcp = BOOL(WINAPI*)(HANDLE, BYTE, DWORD);
    using SetBrightness = BOOL(WINAPI*)(HANDLE, DWORD);
    auto count = reinterpret_cast<GetCount>(GetProcAddress(lib,
        "GetNumberOfPhysicalMonitorsFromHMONITOR"));
    auto get = reinterpret_cast<GetMonitors>(GetProcAddress(lib,
        "GetPhysicalMonitorsFromHMONITOR"));
    auto destroy = reinterpret_cast<DestroyMonitors>(GetProcAddress(lib,
        "DestroyPhysicalMonitors"));
    auto setVcp = reinterpret_cast<SetVcp>(GetProcAddress(lib,
        "SetVCPFeature"));
    auto setBrightness = reinterpret_cast<SetBrightness>(GetProcAddress(lib,
        "SetMonitorBrightness"));
    DWORD n = 0;
    bool ok = false;
    if (count && get && destroy && setVcp &&
        count(display.monitor, &n) && n && n <= 16 &&
        task.monitor.physicalIndex < n) {
        std::vector<PHYSICAL_MONITOR> monitors(n);
        if (get(display.monitor, n, monitors.data())) {
            HANDLE monitor = monitors[task.monitor.physicalIndex].hPhysicalMonitor;
            UpdateRange(monitor, task.monitor.minimum, task.monitor.maximum);
            const int vcp = g_vcpCode.load();
            ok = setVcp(monitor, static_cast<BYTE>(vcp),
                        static_cast<DWORD>(task.value)) != FALSE;
            if (!ok && vcp == 16 && setBrightness)
                ok = setBrightness(monitor, static_cast<DWORD>(task.value)) != FALSE;
            destroy(n, monitors.data());
        }
    }
    FreeLibrary(lib);
    return ok;
}

DWORD WINAPI BrightnessWheelThreadProc(void*) {
    const HRESULT init = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    const bool comReady = SUCCEEDED(init);
    while (WaitForSingleObject(g_wheelWriteWake, INFINITE) == WAIT_OBJECT_0) {
        if (g_wheelWriteStop.load()) break;
        std::vector<BrightnessWheelTask> tasks;
        AcquireSRWLockExclusive(&g_wheelWriteLock);
        tasks.swap(g_wheelWritePending);
        ReleaseSRWLockExclusive(&g_wheelWriteLock);
        for (const auto& task : tasks) {
            if (g_wheelWriteStop.load()) break;
            // Skip a snapshot superseded while another DDC command ran.
            AcquireSRWLockShared(&g_wheelWriteLock);
            const bool superseded = std::any_of(
                g_wheelWritePending.begin(), g_wheelWritePending.end(),
                [&](const BrightnessWheelTask& newer) {
                    return newer.generation > task.generation &&
                        newer.native == task.native &&
                        (task.native ||
                         (newer.monitor.physicalIndex ==
                              task.monitor.physicalIndex &&
                          _wcsicmp(newer.monitor.device,
                                  task.monitor.device) == 0));
                });
            ReleaseSRWLockShared(&g_wheelWriteLock);
            if (superseded) continue;
            const bool success = task.native ?
                (comReady && WriteNativeBrightnessWmi(
                    static_cast<BYTE>(std::clamp(task.value, 0, 100))))
                : WriteExternalBrightnessDdc(task);
            const HWND receiver = g_receiveWnd;
            if (receiver && !g_closing.load())
                PostMessageW(receiver, kBrightnessWheelResultMessage,
                    static_cast<WPARAM>(task.generation),
                    static_cast<LPARAM>((success ? 1 : 0) |
                                        (task.native ? 2 : 0)));
        }
    }
    if (comReady) CoUninitialize();
    return 0;
}

void AdjustBrightnessWheel(int steps) {
    if (!steps || !g_wheelWriteWake) return;
    BrightnessWheelTask task{};
    task.generation = ++g_wheelWriteGeneration;
    if (g_popupKind == PopupKind::NativeBrightness) {
        if (!g_nativePercentKnown) return;
        if (g_lastConfirmedNativeBrightness < 0)
            g_lastConfirmedNativeBrightness = g_nativePercent;
        task.native = true;
        task.value = std::clamp(g_nativePercent +
            steps * kWheelStepPercent, 0, 100);
        g_nativePercent = task.value; // Temporary preview; reverted on failure.
        ResetHideTimerFor(DurationKind::NativeBrightness);
    } else if (g_popupKind == PopupKind::DdcBrightness) {
        if (g_visible.maximum <= g_visible.minimum) return;
        task.monitor = g_visible;
        const DWORD range = g_visible.maximum - g_visible.minimum;
        const DWORD singleStep = std::max<DWORD>(1,
            static_cast<DWORD>(std::lround(range *
            (kWheelStepPercent / 100.0))));
        const INT64 next = static_cast<INT64>(g_visible.value) +
            static_cast<INT64>(steps) * singleStep;
        if (!g_lastConfirmedDdcBrightness)
            g_lastConfirmedDdcBrightness = g_visible.value;
        task.value = static_cast<int>(std::clamp<INT64>(next,
            g_visible.minimum, g_visible.maximum));
        g_visible.value = static_cast<DWORD>(task.value);
        ResetHideTimerFor(DurationKind::DdcBrightness);
    } else return;
    QueueBrightnessWheelTask(task);
    RenderPopup();
}

// Absolute brightness from the main track. The UI thread only updates an
// optimistic preview; the worker performs WMI/DDC writes and posts results.
void SetBrightnessBarPercent(int percent) {
    if (!g_wheelWriteWake) return;
    percent = std::clamp(percent, 0, 100);
    BrightnessWheelTask task{};
    if (g_popupKind == PopupKind::NativeBrightness) {
        if (!g_nativePercentKnown || percent == g_nativePercent) return;
        if (g_lastConfirmedNativeBrightness < 0)
            g_lastConfirmedNativeBrightness = g_nativePercent;
        task.native = true;
        task.value = percent;
        g_nativePercent = percent;
    } else if (g_popupKind == PopupKind::DdcBrightness) {
        if (g_visible.maximum <= g_visible.minimum) return;
        const DWORD range = g_visible.maximum - g_visible.minimum;
        const DWORD next = osd_input::PercentToRaw(
            g_visible.minimum, g_visible.maximum, percent);
        if (next == g_visible.value) return;
        if (!g_lastConfirmedDdcBrightness)
            g_lastConfirmedDdcBrightness = g_visible.value;
        task.monitor = g_visible;
        task.value = static_cast<int>(next);
        g_visible.value = next;
    } else return;
    task.generation = ++g_wheelWriteGeneration;
    QueueBrightnessWheelTask(task);
    RenderPopup();
}

// Convert hit-window client coordinates to the actual painted bar in main
// popup logical coordinates, not to the expanded 24px mouse-hit halo.
void SetMainBarFromPointer(HWND hwnd, LPARAM lp) {
    if (!g_popupWnd || !g_barWheelWnd || hwnd != g_barWheelWnd ||
        !IsWindowVisible(g_popupWnd) || g_scale <= 0.0f) return;
    MainBarRect track{};
    if (!MainBarTrackGeometry(track)) return;
    POINT screenPoint{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
    if (!ClientToScreen(hwnd, &screenPoint)) return;
    RECT popup{};
    if (!GetWindowRect(g_popupWnd, &popup)) return;
    const float x = (screenPoint.x - popup.left) / g_scale;
    const float y = (screenPoint.y - popup.top) / g_scale;
    const bool vertical = g_verticalVolumeBrightness.load();
    const int percent = osd_input::TrackPercent(
        vertical ? y : x,
        vertical ? track.y : track.x,
        vertical ? track.h : track.w,
        vertical);
    if (g_popupKind == PopupKind::NativeVolume)
        SetDefaultAudioBarPercent(percent);
    else
        SetBrightnessBarPercent(percent);
}

void HandleMainBarWheel(int delta) {
    if (!delta || g_scale <= 0.0f) return;
    if (g_barWheelKind != static_cast<int>(g_popupKind)) {
        g_barWheelKind = static_cast<int>(g_popupKind);
        g_barWheelRemainder = 0;
    }
    const int steps = osd_input::ConsumeWheelSteps(
        delta, g_barWheelRemainder);
    if (!steps) return;
    if (g_popupKind == PopupKind::NativeVolume)
        AdjustDefaultAudioWheel(steps);
    else if (g_popupKind == PopupKind::NativeBrightness ||
             g_popupKind == PopupKind::DdcBrightness)
        AdjustBrightnessWheel(steps);
}

// -- SMTC: C++/WinRT projections. Restricted to the private MTA worker.
// No synchronous WinRT waits or media metadata calls run on Explorer's UI
// thread. Poll async completion with a bounded wait so Windhawk unload joins
// cannot be held indefinitely by media-player or broker operations.
// ============================================================
// SMTC WinRT projection and media worker
// ============================================================
namespace smtc_projection {
namespace wf = winrt::Windows::Foundation;
namespace mc = winrt::Windows::Media::Control;
namespace wm = winrt::Windows::Media;
namespace streams = winrt::Windows::Storage::Streams;
using Session = mc::GlobalSystemMediaTransportControlsSession;
using Manager = mc::GlobalSystemMediaTransportControlsSessionManager;

template <typename Operation>
bool AwaitReady(Operation const& operation, DWORD timeoutMs = 1800) {
    if (!operation) return false;
    auto info = operation.template as<wf::IAsyncInfo>();
    const ULONGLONG start = GetTickCount64();
    for (;;) {
        const auto state = info.Status();
        if (state == wf::AsyncStatus::Completed) return true;
        if (state == wf::AsyncStatus::Error ||
            state == wf::AsyncStatus::Canceled) return false;
        if (g_mediaStop.load(std::memory_order_relaxed) ||
            GetTickCount64() - start >= timeoutMs) return false;
        Sleep(15);
    }
}

bool ResultOf(wf::IAsyncOperation<bool> const& task) {
    return AwaitReady(task) && task.get();
}

// Media metadata is untrusted. Cap UTF-16 size, keeping surrogate pairs intact.
std::wstring MediaText(winrt::hstring const& value) {
    size_t count = std::min<size_t>(value.size(), kMaxMediaTextChars);
    const wchar_t* ptr = value.c_str();
    if (count < value.size() && count &&
        ptr[count - 1] >= 0xD800 && ptr[count - 1] <= 0xDBFF)
        --count;
    return std::wstring(ptr, count);
}

void RequestMediaAction(Session const& session, MediaCommand const& command) {
    if (command.action == 5 || command.action == 6) {
        auto info = session.GetPlaybackInfo();
        if (!info) return;
        auto controls = info.Controls();
        if (!controls) return;
        if (command.action == 5) {
            if (!controls.IsShuffleEnabled()) return;
            auto active = info.IsShuffleActive();
            if (!active) return;
            (void)ResultOf(session.TryChangeShuffleActiveAsync(!active.Value()));
        } else {
            if (!controls.IsRepeatEnabled()) return;
            auto current = info.AutoRepeatMode();
            if (!current) return;
            using Mode = wm::MediaPlaybackAutoRepeatMode;
            const Mode mode = current.Value();
            // None -> List -> Track -> None, matching the existing OSD.
            const Mode next = mode == Mode::None ? Mode::List :
                              mode == Mode::List ? Mode::Track : Mode::None;
            (void)ResultOf(session.TryChangeAutoRepeatModeAsync(next));
        }
        return;
    }
    if (command.action == 4) {
        auto info = session.GetPlaybackInfo();
        if (!info || !info.Controls() ||
            !info.Controls().IsPlaybackPositionEnabled()) return;
        // GSMTC takes an Int64 Windows tick count, not a Foundation TimeSpan.
        (void)ResultOf(session.TryChangePlaybackPositionAsync(command.position));
        return;
    }
    if (command.action == 1) {
        (void)ResultOf(session.TrySkipPreviousAsync());
    } else if (command.action == 3) {
        (void)ResultOf(session.TrySkipNextAsync());
    } else if (command.action == 2) {
        auto info = session.GetPlaybackInfo();
        mc::GlobalSystemMediaTransportControlsSessionPlaybackControls controls{nullptr};
        if (info) controls = info.Controls();
        if (controls && !controls.IsPlayPauseToggleEnabled()) {
            const bool playing = info.PlaybackStatus() ==
                mc::GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;
            (void)ResultOf(playing ? session.TryPauseAsync()
                                   : session.TryPlayAsync());
        } else {
            (void)ResultOf(session.TryTogglePlayPauseAsync());
        }
    }
}

void ReadTimeline(Session const& session, MediaSnapshot& snapshot) {
    auto timeline = session.GetTimelineProperties();
    if (!timeline) return;
    const INT64 start = timeline.StartTime().count();
    const INT64 end = timeline.EndTime().count();
    INT64 position = timeline.Position().count();
    if (end <= start) return; // Live streams and unknown duration.
    position = std::clamp(position, start, end);
    const INT64 updated = timeline.LastUpdatedTime().time_since_epoch().count();
    if (snapshot.playing && updated > 0) {
        FILETIME now{};
        GetSystemTimeAsFileTime(&now);
        ULARGE_INTEGER absolute{};
        absolute.LowPart = now.dwLowDateTime;
        absolute.HighPart = now.dwHighDateTime;
        const INT64 now100ns = static_cast<INT64>(absolute.QuadPart);
        if (now100ns >= updated && now100ns - updated <= kMaxMediaLag100ns)
            position += std::min(end - position, now100ns - updated);
    }
    snapshot.hasTimeline = true;
    snapshot.timelineStart = start;
    snapshot.timelineEnd = end;
    snapshot.timelinePosition = position;
    snapshot.timelineObservedTick = GetTickCount64();
}

void ReadArtwork(streams::IRandomAccessStreamReference const& thumbnail,
                 std::vector<BYTE>& output) {
    if (!thumbnail || !g_showMediaArtwork.load(std::memory_order_relaxed))
        return;
    auto open = thumbnail.OpenReadAsync();
    if (!AwaitReady(open)) return;
    auto stream = open.get();
    if (!stream) return;
    const uint64_t size = stream.Size();
    if (!size || size > kMaxArtworkBytes) return;
    const auto count = static_cast<uint32_t>(size);
    streams::Buffer buffer(count);
    auto read = stream.ReadAsync(buffer, count, streams::InputStreamOptions::None);
    if (!AwaitReady(read)) return;
    auto bytes = read.get();
    if (!bytes || !bytes.Length() || bytes.Length() > kMaxArtworkBytes) return;
    output.resize(bytes.Length());
    auto reader = streams::DataReader::FromBuffer(bytes);
    reader.ReadBytes(winrt::array_view<uint8_t>(
        output.data(), output.data() + output.size()));
}

void FillSnapshot(Session const& session, MediaSnapshot const& previous,
                  MediaSnapshot& snapshot) {
    snapshot.available = true;
    auto info = session.GetPlaybackInfo();
    if (info) {
        snapshot.playing = info.PlaybackStatus() ==
            mc::GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;
        auto controls = info.Controls();
        if (controls) {
            snapshot.canPrevious = controls.IsPreviousEnabled();
            snapshot.canNext = controls.IsNextEnabled();
            snapshot.canToggle = controls.IsPlayPauseToggleEnabled() ||
                                 controls.IsPlayEnabled() ||
                                 controls.IsPauseEnabled();
            snapshot.canSeek = controls.IsPlaybackPositionEnabled();
            snapshot.canShuffle = controls.IsShuffleEnabled();
            snapshot.canRepeat = controls.IsRepeatEnabled();
        }
        if (snapshot.canShuffle) {
            auto active = info.IsShuffleActive();
            if (active) {
                snapshot.shuffleKnown = true;
                snapshot.shuffleActive = active.Value();
            }
        }
        if (snapshot.canRepeat) {
            auto mode = info.AutoRepeatMode();
            if (mode) snapshot.repeatMode = static_cast<int>(mode.Value());
        }
    }
    auto propsAsync = session.TryGetMediaPropertiesAsync();
    if (AwaitReady(propsAsync)) {
        auto props = propsAsync.get();
        if (props) {
            snapshot.title = MediaText(props.Title());
            snapshot.artist = MediaText(props.Artist());
            if (g_showMediaArtwork.load(std::memory_order_relaxed)) {
                if (snapshot.sourceId == previous.sourceId &&
                    snapshot.selectionSerial == previous.selectionSerial &&
                    snapshot.title == previous.title &&
                    snapshot.artist == previous.artist &&
                    !previous.artwork.empty()) {
                    snapshot.artwork = previous.artwork;
                } else {
                    try {
                        ReadArtwork(props.Thumbnail(), snapshot.artwork);
                    } catch (winrt::hresult_error const&) {
                        // Missing artwork must not discard valid metadata.
                    }
                }
            }
        }
    }
    ReadTimeline(session, snapshot);
}
} // namespace smtc_projection

void RequestMedia(int command = 0, INT64 position = 0) {
    if (!g_mediaWake || g_mediaStop.load()) return;
    if (command) {
        AcquireSRWLockExclusive(&g_mediaCommandLock);
        if (command == 4) {
            // Dragging generates many positions; keep only the latest seek.
            g_mediaCommands.erase(std::remove_if(g_mediaCommands.begin(),
                g_mediaCommands.end(), [](const MediaCommand& entry) {
                    return entry.action == 4;
                }), g_mediaCommands.end());
        }
        if (g_mediaCommands.size() < 32)
            g_mediaCommands.push_back(MediaCommand{command, position});
        ReleaseSRWLockExclusive(&g_mediaCommandLock);
    }
    SetEvent(g_mediaWake);
}

DWORD WINAPI MediaThreadProc(void*) {
    namespace mc = winrt::Windows::Media::Control;
    try {
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
    } catch (winrt::hresult_error const& e) {
        Wh_Log(L"SMTC apartment initialization failed: 0x%08lX",
               static_cast<unsigned long>(e.code().value));
        return 0;
    }
    struct ScopedApartment {
        ~ScopedApartment() { winrt::uninit_apartment(); }
    } apartment;
    try {
        auto initial = mc::GlobalSystemMediaTransportControlsSessionManager::RequestAsync();
        if (!smtc_projection::AwaitReady(initial)) {
            Wh_Log(L"SMTC manager initialization timed out or failed");
            return 0;
        }
        auto manager = initial.get();
        if (!manager) return 0;
        MediaSnapshot lastSnapshot;
        // Selection is private to this MTA worker. Do not change Windows'
        // global current-session preference or pass WinRT objects to the UI.
        bool manuallySelected = false;
        uint32_t selectionSerial = 0;
        std::wstring selectedSource;
        size_t selectedOrdinal = 0;
        while (WaitForSingleObject(g_mediaWake, INFINITE) == WAIT_OBJECT_0) {
            if (g_mediaStop.load()) break;
            try {
                std::vector<smtc_projection::Session> sessions;
                // GetSessions is a passive enumeration; no GATT/network polling.
                try {
                    auto found = manager.GetSessions();
                    for (auto const& item : found) {
                        if (item && sessions.size() < kMaxMediaSessions)
                            sessions.push_back(item);
                        if (sessions.size() >= kMaxMediaSessions) break;
                    }
                } catch (winrt::hresult_error const&) {
                    // A broker failure must not break the default SMTC card.
                    sessions.clear();
                }
                auto current = manager.GetCurrentSession();
                auto sourceOf = [](const smtc_projection::Session& session) {
                    const auto id = session.SourceAppUserModelId();
                    return std::wstring(id.c_str(), id.size());
                };
                size_t index = sessions.size();
                if (manuallySelected) {
                    // Prefer the previous position when multiple browser tabs
                    // report the same AUMID; fall back to the matching source.
                    if (selectedOrdinal < sessions.size() &&
                        sourceOf(sessions[selectedOrdinal]) == selectedSource) {
                        index = selectedOrdinal;
                    } else {
                        for (size_t i = 0; i < sessions.size(); ++i) {
                            if (sourceOf(sessions[i]) == selectedSource) {
                                index = i;
                                break;
                            }
                        }
                    }
                    if (index == sessions.size()) {
                        manuallySelected = false; // Session disappeared.
                        selectedSource.clear();
                        ++selectionSerial;
                    }
                }
                if (!manuallySelected && current) {
                    const auto currentId = sourceOf(current);
                    for (size_t i = 0; i < sessions.size(); ++i) {
                        if (sourceOf(sessions[i]) == currentId) {
                            index = i;
                            break;
                        }
                    }
                }
                if (index >= sessions.size() && !sessions.empty()) index = 0;
                std::vector<MediaCommand> commands;
                AcquireSRWLockExclusive(&g_mediaCommandLock);
                commands.swap(g_mediaCommands);
                ReleaseSRWLockExclusive(&g_mediaCommandLock);
                smtc_projection::Session session{nullptr};
                if (index < sessions.size()) session = sessions[index];
                else if (current) session = current;
                // Preserve FIFO semantics when cycling and transport commands
                // arrive in the same wake cycle.
                for (auto const& command : commands) {
                    if (command.action == 7) {
                        if (sessions.size() > 1) {
                            index = (index < sessions.size() ? index + 1 : 0) % sessions.size();
                            session = sessions[index];
                            manuallySelected = true;
                            selectedOrdinal = index;
                            selectedSource = sourceOf(session);
                            ++selectionSerial;
                        }
                        continue;
                    }
                    if (!session) continue;
                    try {
                        smtc_projection::RequestMediaAction(session, command);
                    } catch (winrt::hresult_error const& e) {
                        Wh_Log(L"SMTC media command failed: 0x%08lX",
                               static_cast<unsigned long>(e.code().value));
                    }
                }
                MediaSnapshot snapshot;
                snapshot.sessionCount = static_cast<uint32_t>(sessions.size());
                snapshot.selectionSerial = selectionSerial;
                if (session) {
                    try {
                        snapshot.sourceId = sourceOf(session);
                        smtc_projection::FillSnapshot(session, lastSnapshot, snapshot);
                    } catch (winrt::hresult_error const& e) {
                        Wh_Log(L"SMTC metadata read failed: 0x%08lX",
                               static_cast<unsigned long>(e.code().value));
                    }
                }
                lastSnapshot = snapshot;
                AcquireSRWLockExclusive(&g_mediaLock);
                g_mediaPending = std::move(snapshot);
                ReleaseSRWLockExclusive(&g_mediaLock);
                HWND receiver = FindWindowExW(HWND_MESSAGE, nullptr, kWindowClass, nullptr);
                if (receiver) PostMessageW(receiver, kMediaUpdateMessage, 0, 0);
            } catch (winrt::hresult_error const& e) {
                Wh_Log(L"SMTC worker cycle failed: 0x%08lX",
                       static_cast<unsigned long>(e.code().value));
            }
        }
    } catch (winrt::hresult_error const& e) {
        Wh_Log(L"SMTC projection unavailable: 0x%08lX",
               static_cast<unsigned long>(e.code().value));
    } catch (...) {
        Wh_Log(L"SMTC projection worker encountered an unexpected exception");
    }
    return 0;
}

// -- Interactive Core Audio session mixer, created/refreshed only on demand.
// ============================================================
// Audio mixer and per-session controls
// ============================================================
std::wstring ProcessTitle(DWORD pid) {
    if (!pid) return Tr(OsdText::SystemSounds);
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) return std::wstring(Tr(OsdText::ProcessPrefix)) + std::to_wstring(pid);
    WCHAR path[MAX_PATH]{};
    DWORD length = ARRAYSIZE(path);
    bool ok = QueryFullProcessImageNameW(process, 0, path, &length) != FALSE;
    CloseHandle(process);
    if (!ok) return std::wstring(Tr(OsdText::ProcessPrefix)) + std::to_wstring(pid);
    std::wstring result(path);
    size_t slash = result.find_last_of(L"\\/");
    if (slash != std::wstring::npos) result = result.substr(slash + 1);
    if (result.size() > 4 && _wcsicmp(result.c_str() + result.size() - 4, L".exe") == 0)
        result.resize(result.size() - 4);
    return result;
}

void CleanupMixerIcons() {
    for (auto& entry : g_mixerEntries) {
        if (entry.appIcon) DestroyIcon(entry.appIcon);
        entry.appIcon = nullptr;
    }
}

HICON ProcessIcon(DWORD pid) {
    if (!pid) return nullptr;
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) return nullptr;
    WCHAR path[32768]{};
    DWORD size = ARRAYSIZE(path);
    const bool ok = QueryFullProcessImageNameW(process, 0, path, &size) != FALSE;
    CloseHandle(process);
    if (!ok) return nullptr;
    SHFILEINFOW result{};
    if (!SHGetFileInfoW(path, FILE_ATTRIBUTE_NORMAL, &result, sizeof(result),
                        SHGFI_ICON | SHGFI_SMALLICON)) return nullptr;
    return result.hIcon; // caller owns and must destroy
}

void StopMixerOutputNotifications() {
    if (g_mixerNotify) g_mixerNotify->Stop();
    if (g_mixerNotify && g_mixerNotifyEnumerator) {
        (void)g_mixerNotifyEnumerator->UnregisterEndpointNotificationCallback(
            g_mixerNotify.Get());
    }
    g_mixerNotify.Reset();
    g_mixerNotifyEnumerator.Reset();
}

void StartMixerOutputNotifications() {
    if (g_mixerNotify || !g_receiveWnd) return;
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(enumerator.GetAddressOf()));
    if (FAILED(hr)) return;
    auto* callback = new (std::nothrow) MixerOutputNotifications(g_receiveWnd);
    if (!callback) return;
    hr = enumerator->RegisterEndpointNotificationCallback(callback);
    if (SUCCEEDED(hr)) {
        g_mixerNotify.Attach(callback); // callback's construction reference
        g_mixerNotifyEnumerator = std::move(enumerator);
    } else {
        callback->Stop();
        callback->Release();
        Wh_Log(L"Mixer output listener registration failed: 0x%08lX",
               static_cast<unsigned long>(hr));
    }
}

std::wstring AudioOutputFriendlyName(IMMDevice* device) {
    Microsoft::WRL::ComPtr<IPropertyStore> store;
    if (FAILED(device->OpenPropertyStore(STGM_READ, store.GetAddressOf())))
        return Tr(OsdText::AudioOutput);
    PROPVARIANT value;
    PropVariantInit(&value);
    std::wstring name;
    if (SUCCEEDED(store->GetValue(kAudioDeviceFriendlyName, &value)) &&
        value.vt == VT_LPWSTR && value.pwszVal) {
        size_t length = 0;
        while (length < 512 && value.pwszVal[length]) ++length;
        name.assign(value.pwszVal, length);
    }
    PropVariantClear(&value);
    return name.empty() ? std::wstring(Tr(OsdText::AudioOutput)) : name;
}

void ReadMixerOutputDevices(IMMDeviceEnumerator* enumerator) {
    g_mixerOutputOptions.clear();
    g_mixerOutputId.clear();
    Microsoft::WRL::ComPtr<IMMDevice> current;
    if (SUCCEEDED(enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia,
                                                    current.GetAddressOf()))) {
        LPWSTR id = nullptr;
        if (SUCCEEDED(current->GetId(&id)) && id) {
            g_mixerOutputId.assign(id);
            CoTaskMemFree(id);
        }
    }
    Microsoft::WRL::ComPtr<IMMDeviceCollection> collection;
    if (FAILED(enumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE,
                                              collection.GetAddressOf())))
        return;
    UINT count = 0;
    if (FAILED(collection->GetCount(&count))) return;
    for (UINT i = 0; i < count && g_mixerOutputOptions.size() <
            static_cast<size_t>(kMaxMixerOutputDevices); ++i) {
        Microsoft::WRL::ComPtr<IMMDevice> device;
        if (FAILED(collection->Item(i, device.GetAddressOf()))) continue;
        LPWSTR id = nullptr;
        if (FAILED(device->GetId(&id)) || !id) continue;
        AudioOutputOption output{id, AudioOutputFriendlyName(device.Get())};
        CoTaskMemFree(id);
        if (output.id == g_mixerOutputId)
            g_mixerOutputOptions.insert(g_mixerOutputOptions.begin(), std::move(output));
        else
            g_mixerOutputOptions.push_back(std::move(output));
    }
    const int maximum = std::max(0, static_cast<int>(g_mixerOutputOptions.size()) -
                                   kOutputPickerMaxRows);
    g_mixerOutputScroll = std::clamp(g_mixerOutputScroll, 0, maximum);
}

// Deliberately only changes console/multimedia output. An independently
// configured communications endpoint must not be silently overwritten.
HRESULT SetWindowsDefaultPlaybackEndpoint(const std::wstring& id,
                                          const std::wstring& previous) {
    if (id.empty()) return E_INVALIDARG;
    Microsoft::WRL::ComPtr<IPolicyConfigEndpointSwitch> policy;
    HRESULT hr = CoCreateInstance(kPolicyConfigClsid, nullptr,
        CLSCTX_ALL, kPolicyConfigIid,
        reinterpret_cast<void**>(policy.GetAddressOf()));
    if (FAILED(hr)) return hr;
    hr = policy->SetDefaultEndpoint(id.c_str(), eConsole);
    if (FAILED(hr)) return hr;
    hr = policy->SetDefaultEndpoint(id.c_str(), eMultimedia);
    if (FAILED(hr) && !previous.empty())
        (void)policy->SetDefaultEndpoint(previous.c_str(), eConsole);
    return hr;
}

void RefreshMixer() {
    CleanupMixerIcons();
    g_mixerEntries.clear();
    g_mixerMaster.Reset();
    g_mixerMasterLevel = 0;
    g_mixerMasterMuted = false;
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_ALL, IID_PPV_ARGS(enumerator.GetAddressOf()));
    if (FAILED(hr) || !enumerator) {
        g_mixerOutputOptions.clear();
        g_mixerOutputId.clear();
        return;
    }
    ReadMixerOutputDevices(enumerator.Get());
    IMMDevice* device = nullptr;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (FAILED(hr) || !device) return;
    device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL,
        nullptr, reinterpret_cast<void**>(g_mixerMaster.GetAddressOf()));
    if (g_mixerMaster) {
        g_mixerMaster->GetMasterVolumeLevelScalar(&g_mixerMasterLevel);
        BOOL muted = FALSE;
        if (SUCCEEDED(g_mixerMaster->GetMute(&muted)))
            g_mixerMasterMuted = muted != FALSE;
    }
    IAudioSessionManager2* manager = nullptr;
    hr = device->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL,
        nullptr, reinterpret_cast<void**>(&manager));
    device->Release();
    if (FAILED(hr) || !manager) return;
    IAudioSessionEnumerator* sessions = nullptr;
    hr = manager->GetSessionEnumerator(&sessions);
    manager->Release();
    if (FAILED(hr) || !sessions) return;
    int count = 0;
    sessions->GetCount(&count);
    for (int i = 0; i < count && i < 128; ++i) {
        IAudioSessionControl* control = nullptr;
        if (FAILED(sessions->GetSession(i, &control)) || !control) continue;
        AudioSessionState state = AudioSessionStateExpired;
        control->GetState(&state);
        if (state == AudioSessionStateExpired) { control->Release(); continue; }
        ISimpleAudioVolume* volume = nullptr;
        if (FAILED(control->QueryInterface(__uuidof(ISimpleAudioVolume),
                                          reinterpret_cast<void**>(&volume))) || !volume) {
            control->Release();
            continue;
        }
        MixerEntry entry;
        entry.volume.Attach(volume);
        entry.volume->GetMasterVolume(&entry.scalar);
        BOOL muted = FALSE;
        entry.volume->GetMute(&muted);
        entry.muted = muted != FALSE;
        LPWSTR displayName = nullptr;
        control->GetDisplayName(&displayName);
        if (displayName && displayName[0]) entry.title = displayName;
        if (displayName) CoTaskMemFree(displayName);
        IAudioSessionControl2* info = nullptr;
        if (SUCCEEDED(control->QueryInterface(
                __uuidof(IAudioSessionControl2),
                reinterpret_cast<void**>(&info))) && info) {
            DWORD pid = 0;
            if (SUCCEEDED(info->GetProcessId(&pid))) {
                if (entry.title.empty()) entry.title = ProcessTitle(pid);
                entry.appIcon = ProcessIcon(pid);
            }
            info->Release();
        }
        if (entry.title.empty()) entry.title = L"Application";
        control->Release();
        g_mixerEntries.emplace_back(std::move(entry));
    }
    sessions->Release();
    ClampMixerScroll();
}

Gdiplus::RectF MixerOutputHeader() {
    const float w = g_panelWidth / std::max(0.01f, g_scale);
    const float left = std::max(132.0f, w * 0.43f);
    return Gdiplus::RectF(left, kOutputPickerTop,
                          std::max(60.0f, w - left - 22.0f),
                          kOutputPickerHeight);
}

int MixerOutputRows() {
    const float h = g_panelHeight / std::max(0.01f, g_scale);
    const int fit = std::max(0, static_cast<int>(
        (h - kOutputPickerMenuTop - 12.0f) / kOutputPickerRowHeight));
    return std::min({kOutputPickerMaxRows, fit,
                     static_cast<int>(g_mixerOutputOptions.size())});
}

Gdiplus::RectF MixerOutputMenuRect() {
    const auto header = MixerOutputHeader();
    return Gdiplus::RectF(header.X, kOutputPickerMenuTop, header.Width,
                          MixerOutputRows() * kOutputPickerRowHeight + 6.0f);
}

Gdiplus::RectF MixerOutputRowRect(int row) {
    const auto menu = MixerOutputMenuRect();
    return Gdiplus::RectF(menu.X + 3.0f,
                          menu.Y + 3.0f + row * kOutputPickerRowHeight,
                          menu.Width - 6.0f, kOutputPickerRowHeight);
}

bool MixerOutputHeaderHit(float x, float y) {
    auto r = MixerOutputHeader();
    return x >= r.X && x < r.X + r.Width &&
           y >= r.Y && y < r.Y + r.Height;
}

int MixerOutputRowHit(float x, float y) {
    if (!g_mixerOutputExpanded) return -1;
    const int count = MixerOutputRows();
    for (int row = 0; row < count; ++row) {
        const auto bounds = MixerOutputRowRect(row);
        if (x >= bounds.X && x < bounds.X + bounds.Width &&
            y >= bounds.Y && y < bounds.Y + bounds.Height)
            return row + g_mixerOutputScroll;
    }
    return -1;
}

bool UpdateMixerOutputHover(float x, float y) {
    const bool header = MixerOutputHeaderHit(x, y);
    const int row = MixerOutputRowHit(x, y);
    const bool changed = header != g_mixerOutputHeaderHovered ||
                         row != g_mixerOutputHoveredRow;
    g_mixerOutputHeaderHovered = header;
    g_mixerOutputHoveredRow = row;
    return changed;
}

void SelectMixerOutput(int index) {
    if (index < 0 || index >= static_cast<int>(g_mixerOutputOptions.size()))
        return;
    const std::wstring target = g_mixerOutputOptions[index].id;
    g_mixerOutputExpanded = false;
    g_mixerOutputHoveredRow = -1;
    g_mixerOutputSwitchFailed = false;
    if (target != g_mixerOutputId) {
        const HRESULT hr = SetWindowsDefaultPlaybackEndpoint(target,
                                                             g_mixerOutputId);
        if (FAILED(hr)) {
            g_mixerOutputSwitchFailed = true;
            Wh_Log(L"Mixer default output switch failed: 0x%08lX",
                   static_cast<unsigned long>(hr));
        } else {
            // Drop stale Core Audio endpoint/session references immediately.
            // Endpoint notifications also catch asynchronous Windows changes.
            RefreshMixer();
        }
    }
    RenderPanel();
    ResetHideTimerFor(DurationKind::Interactive);
}

void SetMixerSlider(float x, float /* y */) {
    // Lock the target audio session for the whole drag. Crossing rows can
    // never accidentally modify a different app's volume.
    int index = g_mixerDragIndex;
    if (index < 0 || index > static_cast<int>(g_mixerEntries.size())) return;
    float value = std::clamp((x - kMixerTrackStart) / MixerTrackLength(),
                             0.0f, 1.0f);
    if (!index) {
        if (g_mixerMaster && SUCCEEDED(g_mixerMaster->SetMasterVolumeLevelScalar(value, nullptr)))
            g_mixerMasterLevel = value;
    } else {
        auto& item = g_mixerEntries[index - 1];
        if (item.volume && SUCCEEDED(item.volume->SetMasterVolume(value, nullptr)))
            item.scalar = value;
    }
}

// The per-session wheel targets the same full-width track used by dragging.
// Wheel events elsewhere continue to scroll the mixer list.
int MixerTrackHitTest(float x, float y) {
    if (x < kMixerTrackStart - 8.0f ||
        x > kMixerTrackStart + MixerTrackLength() + 8.0f) return -1;
    const int total = static_cast<int>(g_mixerEntries.size()) + 1;
    for (int row = 0; row < MixerVisibleRows(); ++row) {
        const int index = row + g_mixerScroll;
        if (index >= total) break;
        const float centerY = kMixerFirstRowY + row * kMixerRowStep +
                              1.0f + kMixerTrackHeight / 2.0f;
        if (std::fabs(y - centerY) <= 11.0f) return index;
    }
    return -1;
}

bool AdjustMixerVolumeWheel(int index, int steps) {
    if (!steps || index < 0 ||
        index > static_cast<int>(g_mixerEntries.size())) return false;
    const float change = steps * (kWheelStepPercent / 100.0f);
    if (!index) {
        if (!g_mixerMaster) return false;
        float current = 0;
        if (FAILED(g_mixerMaster->GetMasterVolumeLevelScalar(&current)))
            return false;
        const float wanted = std::clamp(current + change, 0.0f, 1.0f);
        if (FAILED(g_mixerMaster->SetMasterVolumeLevelScalar(wanted, nullptr)))
            return false;
        g_mixerMaster->GetMasterVolumeLevelScalar(&g_mixerMasterLevel);
    } else {
        auto& entry = g_mixerEntries[index - 1];
        if (!entry.volume) return false;
        float current = 0;
        if (FAILED(entry.volume->GetMasterVolume(&current))) return false;
        const float wanted = std::clamp(current + change, 0.0f, 1.0f);
        if (FAILED(entry.volume->SetMasterVolume(wanted, nullptr))) return false;
        entry.volume->GetMasterVolume(&entry.scalar);
    }
    RenderPanel();
    ResetHideTimerFor(DurationKind::Interactive);
    return true;
}

// Icon click targets match the painted icons, not the track. Scroll offsets
// are resolved on every event; the same target must be pressed and released.
int MixerIconHitTest(float x, float y) {
    const float iconX = !g_verticalVolumeBrightness.load() ? 28.0f : 25.0f;
    if (x < iconX - 4.0f || x > iconX + 24.0f) return -1;
    const int total = static_cast<int>(g_mixerEntries.size()) + 1;
    for (int row = 0; row < MixerVisibleRows(); ++row) {
        const int index = row + g_mixerScroll;
        if (index >= total) break;
        const float centerY = kMixerFirstRowY + row * kMixerRowStep + 1.5f;
        if (std::fabs(y - centerY) <= 12.5f) return index;
    }
    return -1;
}

void ToggleMixerMute(int index) {
    if (index < 0 || index > static_cast<int>(g_mixerEntries.size())) return;
    if (index == 0) {
        if (!g_mixerMaster) return;
        BOOL current = FALSE;
        if (FAILED(g_mixerMaster->GetMute(&current))) return;
        const BOOL requested = current ? FALSE : TRUE;
        if (SUCCEEDED(g_mixerMaster->SetMute(requested, nullptr))) {
            BOOL actual = requested;
            g_mixerMaster->GetMute(&actual);
            g_mixerMasterMuted = actual != FALSE;
        }
    } else {
        auto& entry = g_mixerEntries[index - 1];
        if (!entry.volume) return;
        BOOL current = FALSE;
        if (FAILED(entry.volume->GetMute(&current))) return;
        const BOOL requested = current ? FALSE : TRUE;
        if (SUCCEEDED(entry.volume->SetMute(requested, nullptr))) {
            BOOL actual = requested;
            entry.volume->GetMute(&actual);
            entry.muted = actual != FALSE;
        }
    }
    RenderPanel();
    ResetHideTimerFor(DurationKind::Interactive);
}

// ============================================================
// Expanded media/mixer/details panel rendering
// ============================================================
void DrawText(Gdiplus::Graphics& gfx, const std::wstring& str,
              float x, float y, float w, float h, float size,
              Gdiplus::Color color, bool centered,
              bool rightAligned) {
    Gdiplus::Font font(L"Segoe UI Variable Text", size,
        Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font fallback(L"Segoe UI", size,
        Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::StringFormat format;
    format.SetAlignment(rightAligned ? Gdiplus::StringAlignmentFar :
                        centered ? Gdiplus::StringAlignmentCenter :
                                   Gdiplus::StringAlignmentNear);
    format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    format.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
    format.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
    Gdiplus::SolidBrush brush(color);
    gfx.DrawString(str.c_str(), -1,
        font.GetLastStatus() == Gdiplus::Ok ? &font : &fallback,
        Gdiplus::RectF(x, y, w, h), &format, &brush);
}

// Shared SMTC-style button appearance for media controls and expanders.
// Controls may differ in radius to fit their host without changing the palette.
Gdiplus::Color ControlButtonFill(bool light, bool pressed = false,
                                 bool active = false, bool hovered = false) {
    if (pressed) return ToGdiColor(OsdAccentRgb(), 96);
    if (active) return ToGdiColor(OsdAccentRgb(), 65);
    if (hovered) return ToGdiColor(OsdAccentRgb(), 40);
    return light ? Gdiplus::Color(255, 233, 234, 238)
                 : Gdiplus::Color(255, 67, 68, 74);
}

// Draw every button from the same geometry, including pressed/feedback states.
// In square mode the radius is specified in logical px and capped by size.
void FillControlButtonShape(Gdiplus::Graphics& gfx, float x, float y,
                            float radius, Gdiplus::Color color) {
    Gdiplus::SolidBrush fill(color);
    if (!g_controlButtonSquare.load()) {
        gfx.FillEllipse(&fill, x - radius, y - radius,
                        radius * 2.0f, radius * 2.0f);
    } else {
        Gdiplus::GraphicsPath path;
        const float corner = std::min(radius,
            static_cast<float>(g_controlButtonCornerRadius.load()));
        AddRoundedRect(path, x - radius, y - radius,
                       radius * 2.0f, radius * 2.0f, corner);
        gfx.FillPath(&fill, &path);
    }
}

void DrawControlButtonOutline(Gdiplus::Graphics& gfx, float x, float y,
                              float radius, Gdiplus::Pen& pen) {
    if (!g_controlButtonSquare.load()) {
        gfx.DrawEllipse(&pen, x - radius, y - radius,
                        radius * 2.0f, radius * 2.0f);
    } else {
        Gdiplus::GraphicsPath path;
        const float corner = std::min(radius,
            static_cast<float>(g_controlButtonCornerRadius.load()));
        AddRoundedRect(path, x - radius, y - radius,
                       radius * 2.0f, radius * 2.0f, corner);
        gfx.DrawPath(&pen, &path);
    }
}

void DrawControlButtonSurface(Gdiplus::Graphics& gfx, float x, float y,
                              float radius, bool light, bool pressed = false,
                              bool active = false, bool hovered = false) {
    FillControlButtonShape(gfx, x, y, radius,
                           ControlButtonFill(light, pressed, active, hovered));
}

void DrawControlChevron(Gdiplus::Graphics& gfx, float x, float y,
                        Gdiplus::Color color, FlyoutDirection direction,
                        float extent = 4.5f) {
    Gdiplus::Pen pen(color, 1.8f);
    pen.SetStartCap(Gdiplus::LineCapRound);
    pen.SetEndCap(Gdiplus::LineCapRound);
    pen.SetLineJoin(Gdiplus::LineJoinRound);
    switch (direction) {
        case FlyoutDirection::Up:
            gfx.DrawLine(&pen, x - extent, y + extent / 2.0f,
                         x, y - extent / 2.0f);
            gfx.DrawLine(&pen, x, y - extent / 2.0f,
                         x + extent, y + extent / 2.0f);
            break;
        case FlyoutDirection::Down:
            gfx.DrawLine(&pen, x - extent, y - extent / 2.0f,
                         x, y + extent / 2.0f);
            gfx.DrawLine(&pen, x, y + extent / 2.0f,
                         x + extent, y - extent / 2.0f);
            break;
        case FlyoutDirection::Left:
            gfx.DrawLine(&pen, x + extent / 2.0f, y - extent,
                         x - extent / 2.0f, y);
            gfx.DrawLine(&pen, x - extent / 2.0f, y,
                         x + extent / 2.0f, y + extent);
            break;
        case FlyoutDirection::Right:
            gfx.DrawLine(&pen, x - extent / 2.0f, y - extent,
                         x + extent / 2.0f, y);
            gfx.DrawLine(&pen, x + extent / 2.0f, y,
                         x - extent / 2.0f, y + extent);
            break;
    }
}

// Draw tiny Fluent-like transport controls at one fixed visual scale.
// Glyphs use the exact same user scale as the button's hit box.
// At the default 100%, circles are 32px logical and symbols ~13px.
void DrawMediaControl(Gdiplus::Graphics& gfx, float cx, float cy,
                      int action, bool playing, Gdiplus::Color color,
                      float pressScale = 1.0f) {
    const float scale = g_mediaControlSizePercent.load() / 100.0f * pressScale;
    Gdiplus::SolidBrush brush(color);
    Gdiplus::Pen pen(color, 1.8f * scale);
    pen.SetStartCap(Gdiplus::LineCapRound);
    pen.SetEndCap(Gdiplus::LineCapRound);
    pen.SetLineJoin(Gdiplus::LineJoinRound);
    if (action == 2 && playing) {
        gfx.FillRectangle(&brush, cx - 5.3f * scale, cy - 6.1f * scale,
                          3.1f * scale, 12.2f * scale);
        gfx.FillRectangle(&brush, cx + 2.2f * scale, cy - 6.1f * scale,
                          3.1f * scale, 12.2f * scale);
    } else {
        const float d = action == 1 ? -1.0f : 1.0f;
        Gdiplus::PointF pts[] = {
            {cx - d * 5.4f * scale, cy - 6.0f * scale},
            {cx + d * 5.0f * scale, cy},
            {cx - d * 5.4f * scale, cy + 6.0f * scale}
        };
        gfx.FillPolygon(&brush, pts, 3);
        if (action != 2)
            gfx.DrawLine(&pen, cx + d * 6.0f * scale,
                          cy - 6.0f * scale,
                          cx + d * 6.0f * scale,
                          cy + 6.0f * scale);
    }
}

Gdiplus::Color PanelBorderColor(bool light) {
    return light ? Gdiplus::Color(170, 190, 190, 195)
                 : Gdiplus::Color(170, 90, 90, 97);
}

void DrawPanelCard(Gdiplus::Graphics& gfx, float width, float height,
                   bool alignToMainVolume = false) {
    bool light = IsLightTheme();
    DWORD bg = OsdBackgroundRgb(light);
    BYTE alpha = OsdBackgroundAlpha();
    const bool vertical = g_verticalVolumeBrightness.load();
    const float topInset = vertical ? 6.0f : 10.0f;
    const float bottomInset = vertical ? 6.0f : 13.0f;
    // The horizontal main volume card uses 13px side insets at every width.
    // Match painted edges, not merely the window bounds.
    const float sideInset = alignToMainVolume && !vertical ? 13.0f : 4.0f;
    Gdiplus::GraphicsPath path;
    AddRoundedRect(path, sideInset, topInset, width - sideInset * 2.0f,
                   height - topInset - bottomInset,
                   static_cast<float>(g_cornerRadius.load()));
    Gdiplus::SolidBrush brush(ToGdiColor(bg, alpha));
    gfx.FillPath(&brush, &path);
    if (!g_ddcBorderless.load()) {
        Gdiplus::Pen border(PanelBorderColor(light), .8f);
        gfx.DrawPath(&border, &path);
    }
}

// Panels are drawn in their own focus-free layered window, independently of the
// tiny vertically laid out main OSD. This keeps vertical bar dimensions stable.

// SMTC painting, seeking and transport button hit-tests must use the exact
// same geometry. All visible content is inside the card's common 14px inset.
// The cover grows with panel height rather than stopping at a hard-coded
// 132px cap. Where the panel is too narrow for a square cover at full height
// AND a readable transport column, center the entire cover/control group
// vertically instead of clipping or distorting the artwork.
bool MediaExtraControlsVisible() {
    return g_showMediaControls.load() &&
        ((g_mediaCurrent.canShuffle && g_mediaCurrent.shuffleKnown) ||
         (g_mediaCurrent.canRepeat && g_mediaCurrent.repeatMode >= 0));
}
struct MediaLayout {
    float artX, artY, artSize;
    float textX, textWidth, titleY, artistY;
    float controlsY, controlsX[3], buttonRadius;
    float timelineY, timeY, timelineWidth;
    float contentScale;  // Same scale for typography and transport glyphs.
};
MediaLayout ComputeMediaLayout(float h, float w) {
    constexpr float inset = 14.0f;
    const bool vertical = g_verticalVolumeBrightness.load();
    // DrawPanelCard(..., alignToMainVolume=true) uses precisely these insets.
    const float cardLeft = vertical ? 4.0f : 13.0f;
    const float cardTop = vertical ? 6.0f : 10.0f;
    const float cardBottom = vertical ? 6.0f : 13.0f;
    const float contentLeft = cardLeft + inset;
    const float contentRight = w - cardLeft - inset;
    const float contentTop = cardTop + inset;
    const float contentBottom = h - cardBottom - inset;
    const float contentHeight = std::max(1.0f, contentBottom - contentTop);
    const float artGap = vertical ? 16.0f : 12.0f;
    const float usableWidth = contentRight - contentLeft - artGap;
    const float baseRadius = 16.0f *
        (g_mediaControlSizePercent.load() / 100.0f);

    // Reserve an additional half-size column immediately before Previous.
    // The three main controls remain on one baseline without a bottom row.
    const bool hasExtra = MediaExtraControlsVisible();
    auto controlScale = [](float art) {
        return std::clamp(art / 125.0f, 0.78f, 1.45f);
    };
    auto fits = [&](float art) {
        const float radius = baseRadius * controlScale(art);
        // Three main buttons need 4px between adjacent surfaces. Reserve
        // another 3px from the text boundary and a 10px auxiliary gap.
        const float required = hasExtra
            ? 7.0f * radius + kMediaExtraGroupGap + 11.0f
            : 6.0f * radius + 8.0f;
        return art + std::max(86.0f, required) <= usableWidth;
    };
    float lo = 1.0f;
    float hi = contentHeight;
    for (int i = 0; i < 18; ++i) {
        const float candidate = (lo + hi) * 0.5f;
        if (fits(candidate)) lo = candidate;
        else hi = candidate;
    }
    const float artSize = std::max(1.0f, std::min(contentHeight, lo));
    const float artX = contentLeft;
    // At normal aspect ratios, artSize==contentHeight, so the cover has
    // exactly inset pixels above, below and to its left. At constrained
    // ratios, center the cover and the entire right-side group together.
    const float artY = contentTop + (contentHeight - artSize) / 2.0f;
    const float textX = artX + artSize + artGap;
    const float textWidth = std::max(1.0f, contentRight - textX);
    const float scale = controlScale(artSize);
    const float radius = std::min(baseRadius * scale,
        std::max(1.0f, hasExtra
            ? (textWidth - kMediaExtraGroupGap - 11.0f) / 7.0f
            : (textWidth - 8.0f) / 6.0f));
    const float extraColumnWidth = hasExtra
        ? radius + kMediaExtraGroupGap + 3.0f : 0.0f;
    const float leftButtonX = textX + extraColumnWidth + radius;
    const float rightButtonX = contentRight - radius;
    // All vertical geometry is tied to the same artwork box, not to an
    // unrelated 176px reference panel height or a second center offset.
    return {
        artX, artY, artSize,
        textX, textWidth,
        artY + artSize * 0.024f,
        artY + artSize * 0.240f,
        artY + artSize - radius,
        {leftButtonX, (leftButtonX + rightButtonX) / 2.0f,
         rightButtonX}, radius,
        artY + artSize * 0.448f,
        artY + artSize * 0.512f,
        textWidth, scale
    };
}

// The GDI+ stream backing an image must outlive the decoded bitmap.
// Refresh this cache only after SMTC publishes a new artwork payload.
void UpdateMediaArtworkCache() {
    if (g_cachedArtworkBytes == g_mediaCurrent.artwork) return;
    g_cachedArtwork.reset();
    g_cachedArtworkStream.Reset();
    g_cachedArtworkBytes = g_mediaCurrent.artwork;
    if (g_cachedArtworkBytes.empty()) return;
    HGLOBAL allocation = GlobalAlloc(GMEM_MOVEABLE, g_cachedArtworkBytes.size());
    if (!allocation) return;
    void* memory = GlobalLock(allocation);
    if (!memory) { GlobalFree(allocation); return; }
    memcpy(memory, g_cachedArtworkBytes.data(), g_cachedArtworkBytes.size());
    GlobalUnlock(allocation);
    IStream* stream = nullptr;
    if (FAILED(CreateStreamOnHGlobal(allocation, TRUE, &stream))) {
        GlobalFree(allocation);
        return;
    }
    // The stream now owns the HGLOBAL; keep the stream until bitmap deletion.
    g_cachedArtworkStream.Attach(stream);
    g_cachedArtwork.reset(new Gdiplus::Bitmap(stream));
    // Encoded bytes are limited in ReadArtwork, but a small compressed
    // image can still describe a huge decoded bitmap.
    const UINT artworkWidth = g_cachedArtwork->GetWidth();
    const UINT artworkHeight = g_cachedArtwork->GetHeight();
    if (g_cachedArtwork->GetLastStatus() != Gdiplus::Ok ||
        !artworkWidth || !artworkHeight ||
        artworkWidth > 4096 || artworkHeight > 4096 ||
        static_cast<uint64_t>(artworkWidth) * artworkHeight > 8388608ULL) {
        g_cachedArtwork.reset();
        g_cachedArtworkStream.Reset();
    }
}

void ClearMediaArtworkCache() {
    g_cachedArtwork.reset();
    g_cachedArtworkStream.Reset();
    g_cachedArtworkBytes.clear();
}

// Extrapolation occurs only between SMTC snapshots while the player reports
// Playing. Use a monotonic clock so UI animation is independent of clock
// corrections. Never extrapolate beyond the SMTC-reported track bounds.
INT64 MediaDisplayedPosition100ns(const MediaSnapshot& m,
                                  ULONGLONG nowTick) {
    if (!m.hasTimeline || m.timelineEnd <= m.timelineStart) return 0;
    if (g_mediaSeeking || (g_mediaSeekHoldUntil &&
        nowTick < g_mediaSeekHoldUntil))
        return std::clamp(g_mediaPreviewPosition,
                          m.timelineStart, m.timelineEnd);
    INT64 pos = m.timelinePosition;
    if (m.playing && nowTick >= m.timelineObservedTick) {
        const ULONGLONG elapsed = std::min<ULONGLONG>(
            nowTick - m.timelineObservedTick,
            static_cast<ULONGLONG>((m.timelineEnd - pos) / 10000));
        pos += static_cast<INT64>(elapsed * 10000);
    }
    return std::clamp(pos, m.timelineStart, m.timelineEnd);
}

std::wstring FormatMediaTime(INT64 span100ns) {
    const UINT64 seconds = static_cast<UINT64>(std::max<INT64>(0, span100ns)) /
        10000000ULL;
    const std::wstring sec = (seconds % 60 < 10 ? L"0" : L"") +
        std::to_wstring(seconds % 60);
    if (seconds >= 3600) {
        const UINT64 minute = (seconds / 60) % 60;
        return std::to_wstring(seconds / 3600) + L":" +
            (minute < 10 ? L"0" : L"") + std::to_wstring(minute) +
            L":" + sec;
    }
    return std::to_wstring(seconds / 60) + L":" + sec;
}

// Two half-size buttons in a vertical column directly left of Previous.
// Both paint and hit test use these same coordinates.
struct MediaExtraLayout { float x, y[2], radius; };
bool GetMediaExtraLayout(MediaExtraLayout& extra) {
    if (!MediaExtraControlsVisible() || g_panelMode != PanelMode::Media ||
        g_scale <= 0.0f) return false;
    const MediaLayout layout = ComputeMediaLayout(
        g_panelHeight / g_scale, g_panelWidth / g_scale);
    extra.radius = layout.buttonRadius * 0.5f;
    extra.x = layout.controlsX[0] - layout.buttonRadius -
              extra.radius - kMediaExtraGroupGap;
    const bool both = g_mediaCurrent.canShuffle &&
                      g_mediaCurrent.shuffleKnown &&
                      g_mediaCurrent.canRepeat &&
                      g_mediaCurrent.repeatMode >= 0;
    const float offset = both
        ? extra.radius + kMediaExtraStackGap / 2.0f : 0.0f;
    extra.y[0] = layout.controlsY - offset; // Shuffle above
    extra.y[1] = layout.controlsY + offset; // Repeat below
    return true;
}
bool ControlButtonHit(float dx, float dy, float radius) {
    if (!g_controlButtonSquare.load()) return dx * dx + dy * dy <= radius * radius;
    const float ax = std::abs(dx), ay = std::abs(dy);
    if (ax > radius || ay > radius) return false;
    const float corner = std::min(radius,
        static_cast<float>(g_controlButtonCornerRadius.load()));
    if (corner <= 0.0f) return true;
    const float straight = radius - corner;
    if (ax <= straight || ay <= straight) return true;
    const float x = ax - straight, y = ay - straight;
    return x * x + y * y <= corner * corner;
}

// Album-cover overlay: appears only when more than one SMTC session exists.
// Independent of the SMTC transport-button size setting.
bool MediaCycleGeometry(float& cx, float& cy, float& radius) {
    if (g_panelMode != PanelMode::Media || g_scale <= 0.0f ||
        g_mediaCurrent.sessionCount <= 1) return false;
    const MediaLayout layout = ComputeMediaLayout(
        g_panelHeight / g_scale, g_panelWidth / g_scale);
    radius = std::clamp(layout.artSize * 0.10f, 10.0f, 14.0f);
    constexpr float inset = 5.0f;
    cx = layout.artX + layout.artSize - radius - inset;
    cy = layout.artY + radius + inset;
    return layout.artSize >= 2.0f * (radius + inset);
}

bool MediaCycleHitTest(float x, float y) {
    float cx = 0.0f, cy = 0.0f, radius = 0.0f;
    return MediaCycleGeometry(cx, cy, radius) &&
        ControlButtonHit(x - cx, y - cy, radius);
}

int MediaExtraHitTest(float x, float y) {
    MediaExtraLayout extra{};
    if (!GetMediaExtraLayout(extra)) return 0;
    const bool allowed[2] = {
        g_mediaCurrent.canShuffle && g_mediaCurrent.shuffleKnown,
        g_mediaCurrent.canRepeat && g_mediaCurrent.repeatMode >= 0
    };
    for (int i = 0; i < 2; ++i) {
        const float dx = x - extra.x;
        const float dy = y - extra.y[i];
        if (allowed[i] && ControlButtonHit(dx, dy, extra.radius))
            return i == 0 ? 5 : 6;
    }
    return 0;
}
int MediaButtonHitTest(float x, float y) {
    if (g_panelMode != PanelMode::Media || !g_showMediaControls.load() ||
        g_scale <= 0) return -1;
    const MediaLayout layout = ComputeMediaLayout(
        g_panelHeight / g_scale, g_panelWidth / g_scale);
    const bool enabled[3]{g_mediaCurrent.canPrevious,
        g_mediaCurrent.canToggle, g_mediaCurrent.canNext};
    for (int i = 0; i < 3; ++i) {
        const float dx = x - layout.controlsX[i];
        const float dy = y - layout.controlsY;
        if (enabled[i] && ControlButtonHit(dx, dy, layout.buttonRadius))
            return i;
    }
    return -1;
}

bool MediaTimelineHitTest(float x, float y) {
    if (g_panelMode != PanelMode::Media || !g_mediaCurrent.hasTimeline ||
        !g_mediaCurrent.canSeek ||
        g_mediaCurrent.timelineEnd <= g_mediaCurrent.timelineStart ||
        g_scale <= 0.0f) return false;
    const MediaLayout l = ComputeMediaLayout(
        g_panelHeight / g_scale, g_panelWidth / g_scale);
    // 5px drawn line, 19px accessible pointer target; clamp at endpoints.
    return x >= l.textX - 8.0f &&
           x <= l.textX + l.timelineWidth + 8.0f &&
           std::fabs(y - (l.timelineY + 2.5f)) <= 9.5f;
}

void PreviewMediaSeek(float x) {
    if (!g_mediaCurrent.hasTimeline || !g_mediaCurrent.canSeek ||
        g_mediaCurrent.timelineEnd <= g_mediaCurrent.timelineStart ||
        g_scale <= 0.0f) return;
    const MediaLayout l = ComputeMediaLayout(
        g_panelHeight / g_scale, g_panelWidth / g_scale);
    const double fraction = std::clamp(
        static_cast<double>((x - l.textX) / l.timelineWidth), 0.0, 1.0);
    const INT64 span = g_mediaCurrent.timelineEnd -
                       g_mediaCurrent.timelineStart;
    g_mediaPreviewPosition = g_mediaCurrent.timelineStart +
        static_cast<INT64>(std::llround(fraction * static_cast<double>(span)));
    g_mediaPreviewPosition = std::clamp(g_mediaPreviewPosition,
        g_mediaCurrent.timelineStart, g_mediaCurrent.timelineEnd);
    RenderPanel();
}

void DrawMediaPanel(Gdiplus::Graphics& gfx) {
    const float w = g_panelWidth / g_scale;
    const float h = g_panelHeight / g_scale;
    DrawPanelCard(gfx, w, h, true);
    const MediaLayout layout = ComputeMediaLayout(h, w);
    const bool light = IsLightTheme();
    const DWORD rgb = OsdTextRgb(light);
    const Gdiplus::Color fg = ToGdiColor(rgb);
    const Gdiplus::Color quiet(190, fg.GetR(), fg.GetG(), fg.GetB());
    const float imgW = layout.artSize;
    const float imgX = layout.artX, imgY = layout.artY;
    bool renderedArt = false;
    if (g_showMediaArtwork.load() && g_cachedArtwork &&
        g_cachedArtwork->GetLastStatus() == Gdiplus::Ok) {
        Gdiplus::GraphicsPath clip;
        AddRoundedRect(clip, imgX, imgY, imgW, imgW,
                       std::clamp(imgW * 0.056f, 5.0f, 14.0f));
        const auto saved = gfx.Save();
        gfx.SetClip(&clip);
        // Center-crop a non-square source instead of stretching cover art.
        const float srcW = static_cast<float>(g_cachedArtwork->GetWidth());
        const float srcH = static_cast<float>(g_cachedArtwork->GetHeight());
        const float srcSide = std::min(srcW, srcH);
        gfx.DrawImage(g_cachedArtwork.get(),
                      Gdiplus::RectF(imgX, imgY, imgW, imgW),
                      (srcW - srcSide) * 0.5f, (srcH - srcSide) * 0.5f,
                      srcSide, srcSide, Gdiplus::UnitPixel);
        gfx.Restore(saved);
        renderedArt = true;
    }
    if (!renderedArt) {
        Gdiplus::GraphicsPath placeholder;
        AddRoundedRect(placeholder, imgX, imgY, imgW, imgW,
                       std::clamp(imgW * 0.056f, 5.0f, 14.0f));
        Gdiplus::SolidBrush fill(light ? Gdiplus::Color(255, 228,230,235)
                                       : Gdiplus::Color(255,64,65,70));
        gfx.FillPath(&fill, &placeholder);
        DrawText(gfx, L"♫", imgX, imgY, imgW, imgW,
                 32.0f * std::min(layout.contentScale, 1.35f), quiet, true);
    }
    // Semi-transparent Fluent-style chevron over the album's top-right.
    // It switches the session shown by this card, not the Windows default.
    float cycleX = 0.0f, cycleY = 0.0f, cycleRadius = 0.0f;
    if (MediaCycleGeometry(cycleX, cycleY, cycleRadius)) {
        const bool pressed = g_mediaCyclePressed && g_mediaCycleInside;
        FillControlButtonShape(gfx, cycleX, cycleY, cycleRadius,
            pressed ? Gdiplus::Color(188, 67, 91, 130)
                    : Gdiplus::Color(166, 24, 27, 34));
        DrawControlChevron(gfx, cycleX, cycleY,
            Gdiplus::Color(250, 255, 255, 255), FlyoutDirection::Right,
            cycleRadius * 0.34f);
    }
    DrawText(gfx, g_mediaCurrent.title.empty() ? Tr(OsdText::MediaPlayback) :
             g_mediaCurrent.title, layout.textX, layout.titleY, layout.textWidth,
             27.0f * layout.contentScale,
             16.0f * std::min(layout.contentScale, 1.35f), fg);
    DrawText(gfx, g_mediaCurrent.artist, layout.textX,
             layout.artistY, layout.textWidth,
             19.0f * layout.contentScale,
             12.0f * std::min(layout.contentScale, 1.35f), quiet);
    if (g_mediaCurrent.hasTimeline &&
        g_mediaCurrent.timelineEnd > g_mediaCurrent.timelineStart) {
        const DWORD trackRgb = OsdTrackRgb(light);
        const DWORD accentRgb = OsdAccentRgb();
        Gdiplus::GraphicsPath track;
        AddRoundedRect(track, layout.textX, layout.timelineY,
                       layout.timelineWidth, 5.0f, 2.5f);
        Gdiplus::SolidBrush trackBrush(ToGdiColor(trackRgb));
        gfx.FillPath(&trackBrush, &track);
        const INT64 position = MediaDisplayedPosition100ns(
            g_mediaCurrent, GetTickCount64());
        const double fraction = static_cast<double>(
            position - g_mediaCurrent.timelineStart) /
            static_cast<double>(g_mediaCurrent.timelineEnd -
                g_mediaCurrent.timelineStart);
        const float fillWidth = static_cast<float>(
            std::clamp(fraction, 0.0, 1.0) * layout.timelineWidth);
        if (fillWidth >= 1.0f) {
            Gdiplus::GraphicsPath progress;
            AddRoundedRect(progress, layout.textX, layout.timelineY,
                           fillWidth, 5.0f, std::min(2.5f, fillWidth / 2.0f));
            Gdiplus::SolidBrush accent(ToGdiColor(accentRgb));
            gfx.FillPath(&accent, &progress);
        }
        // The progress thumb uses the same geometry as the main OSD thumb.
        // Its center is on the bar; the setting can disable thumbs globally.
        DrawTrackThumb(gfx, layout.textX + fillWidth,
                       layout.timelineY + 2.5f,
                       ToGdiColor(accentRgb), light);
        const float timeWidth = std::min(73.0f,
                                         layout.timelineWidth * 0.48f);
        const float timeHeight = 15.0f * layout.contentScale;
        const float timeFont = 10.0f *
            std::min(layout.contentScale, 1.35f);
        DrawText(gfx, FormatMediaTime(position - g_mediaCurrent.timelineStart),
                 layout.textX, layout.timeY, timeWidth, timeHeight,
                 timeFont, quiet);
        // End time shares the right-hand content boundary with the progress
        // track and controls, regardless of expanded-panel width.
        DrawText(gfx, FormatMediaTime(g_mediaCurrent.timelineEnd -
                     g_mediaCurrent.timelineStart),
                 layout.textX + layout.timelineWidth - timeWidth,
                 layout.timeY, timeWidth, timeHeight,
                 timeFont, quiet, false, true);
    }
    if (!g_showMediaControls.load()) return;
    const bool allowed[3] = {g_mediaCurrent.canPrevious,
                             g_mediaCurrent.canToggle, g_mediaCurrent.canNext};
    const ULONGLONG now = GetTickCount64();
    const bool feedback = g_mediaFeedbackIndex >= 0 &&
        now >= g_mediaFeedbackTick &&
        now - g_mediaFeedbackTick < kMediaFeedbackMs;
    for (int i = 0; i < 3; ++i) {
        const bool pressed = i == g_mediaPressedIndex && g_mediaPressedInside;
        const bool tapped = feedback && i == g_mediaFeedbackIndex;
        const float radius = layout.buttonRadius * (pressed ? 0.94f : 1.0f);
        const DWORD accentRgb = OsdAccentRgb();
        const Gdiplus::Color fill = pressed || tapped
            ? ToGdiColor(accentRgb, pressed ? 96 : static_cast<BYTE>(
                (kMediaFeedbackMs - (now - g_mediaFeedbackTick)) * 85 /
                 kMediaFeedbackMs))
            : ControlButtonFill(light);
        FillControlButtonShape(gfx, layout.controlsX[i], layout.controlsY,
                               radius, fill);
        if (tapped) {
            const float t = static_cast<float>(now - g_mediaFeedbackTick) /
                static_cast<float>(kMediaFeedbackMs);
            Gdiplus::Pen ring(ToGdiColor(accentRgb, static_cast<BYTE>(
                (1.0f - t) * 145.0f)), 1.6f);
            DrawControlButtonOutline(gfx, layout.controlsX[i],
                layout.controlsY, radius * (0.75f + 0.3f*t), ring);
        }
        DrawMediaControl(gfx, layout.controlsX[i], layout.controlsY,
                         i + 1, g_mediaCurrent.playing,
                         allowed[i] ? fg : quiet,
                         layout.contentScale * (pressed ? 0.90f : 1.0f));
    }
    MediaExtraLayout extra{};
    if (GetMediaExtraLayout(extra)) {
        const bool enabled[2] = {
            g_mediaCurrent.canShuffle && g_mediaCurrent.shuffleKnown,
            g_mediaCurrent.canRepeat && g_mediaCurrent.repeatMode >= 0
        };
        const bool active[2] = {g_mediaCurrent.shuffleActive,
                                g_mediaCurrent.repeatMode > 0};
        const DWORD accentRgb = OsdAccentRgb();
        for (int i = 0; i < 2; ++i) {
            if (!enabled[i]) continue;
            const int action = 5 + i;
            const bool pressed = g_extraPressedAction == action &&
                                 g_extraPressedInside;
            const bool tapped = feedback && g_mediaFeedbackIndex == action - 2;
            const float radius = extra.radius * (pressed ? 0.95f : 1.0f);
            const Gdiplus::Color background = pressed || tapped ?
                ToGdiColor(accentRgb, 96) : active[i] ?
                ToGdiColor(accentRgb, 65) :
                ControlButtonFill(light);
            FillControlButtonShape(gfx, extra.x, extra.y[i], radius, background);
            Gdiplus::Pen pen(active[i] ? ToGdiColor(accentRgb) : fg, 1.6f);
            pen.SetStartCap(Gdiplus::LineCapRound);
            pen.SetEndCap(Gdiplus::LineCapRound);
            // Both the circle and its symbol scale with Previous.
            const Gdiplus::GraphicsState saved = gfx.Save();
            gfx.TranslateTransform(extra.x, extra.y[i]);
            gfx.ScaleTransform(extra.radius / 16.0f, extra.radius / 16.0f);
            const float x = 0.0f, y = 0.0f;
            if (i == 0) { // Shuffle: crossing paths with directional heads.
                gfx.DrawLine(&pen, x - 6.0f, y - 4.5f, x - 2.0f, y - 4.5f);
                gfx.DrawLine(&pen, x - 2.0f, y - 4.5f, x + 3.0f, y + 4.5f);
                gfx.DrawLine(&pen, x + 3.0f, y + 4.5f, x + 6.0f, y + 4.5f);
                gfx.DrawLine(&pen, x - 6.0f, y + 4.5f, x - 2.0f, y + 4.5f);
                gfx.DrawLine(&pen, x - 2.0f, y + 4.5f, x + 3.0f, y - 4.5f);
                gfx.DrawLine(&pen, x + 3.0f, y - 4.5f, x + 6.0f, y - 4.5f);
                gfx.DrawLine(&pen, x + 3.5f, y - 7.0f, x + 6.0f, y - 4.5f);
                gfx.DrawLine(&pen, x + 3.5f, y - 2.0f, x + 6.0f, y - 4.5f);
                gfx.DrawLine(&pen, x + 3.5f, y + 2.0f, x + 6.0f, y + 4.5f);
                gfx.DrawLine(&pen, x + 3.5f, y + 7.0f, x + 6.0f, y + 4.5f);
            } else { // Repeat list / track, with "1" in track mode.
                gfx.DrawLine(&pen, x - 6.0f, y - 4.5f, x + 5.0f, y - 4.5f);
                gfx.DrawLine(&pen, x + 5.0f, y - 4.5f, x + 2.8f, y - 6.5f);
                gfx.DrawLine(&pen, x + 5.0f, y - 4.5f, x + 2.8f, y - 2.5f);
                gfx.DrawLine(&pen, x + 6.0f, y + 4.5f, x - 5.0f, y + 4.5f);
                gfx.DrawLine(&pen, x - 5.0f, y + 4.5f, x - 2.8f, y + 6.5f);
                gfx.DrawLine(&pen, x - 5.0f, y + 4.5f, x - 2.8f, y + 2.5f);
                if (g_mediaCurrent.repeatMode == 1)
                    DrawText(gfx, L"1", x - 4.0f, y - 4.0f,
                             8.0f, 8.0f, 7.0f, fg, true);
            }
            gfx.Restore(saved);
        }
    }
}

int NoticeVisibleRows() {
    if (g_panelHeight <= 0) return 1;
    return std::max(1, static_cast<int>((g_panelHeight / g_scale - 47.0f) / 28.0f));
}
void DrawNoticeDetails(Gdiplus::Graphics& gfx) {
    const float h = g_panelHeight / g_scale;
    DrawPanelCard(gfx, 340.0f, h);
    const bool light = IsLightTheme();
    const Gdiplus::Color fg = ToGdiColor(
        OsdTextRgb(light));
    DrawText(gfx, Tr(OsdText::EventDetails), 16, 10, 290, 24, 15, fg);
    const int visible = NoticeVisibleRows();
    const int maxStart = std::max<int>(0, static_cast<int>(g_noticeDetails.size()) - visible);
    g_noticeScroll = std::clamp(g_noticeScroll, 0, maxStart);
    for (int i = 0; i < visible && i + g_noticeScroll < static_cast<int>(g_noticeDetails.size()); ++i)
        DrawText(gfx, g_noticeDetails[i + g_noticeScroll], 18,
                 42.0f + i * 28.0f, 304, 25, 13, fg);
    if (maxStart > 0) {
        const DWORD accent = OsdAccentRgb();
        Gdiplus::SolidBrush b(ToGdiColor(accent));
        const float travel = std::max(12.0f, h - 52.0f);
        const float thumb = std::max(12.0f, travel * visible / g_noticeDetails.size());
        const float offset = (travel - thumb) * g_noticeScroll / maxStart;
        gfx.FillRectangle(&b, 332.0f, 41.0f + offset, 3.0f, thumb);
    }
}

void DrawMixerOutputPicker(Gdiplus::Graphics& gfx, float width, float height,
                           Gdiplus::Color fg, bool light, DWORD accentRgb) {
    (void)width;
    const auto header = MixerOutputHeader();
    const float corner = std::clamp(
        static_cast<float>(g_cornerRadius.load()), 0.0f, 12.0f);
    // The header remains minimal until hovered/expanded, matching OSD controls.
    if (g_mixerOutputHeaderHovered || g_mixerOutputExpanded) {
        Gdiplus::GraphicsPath backdrop;
        AddRoundedRect(backdrop, header.X, header.Y, header.Width,
                       header.Height, corner);
        Gdiplus::SolidBrush fill(ToGdiColor(accentRgb,
            g_mixerOutputExpanded ? 36 : 22));
        gfx.FillPath(&fill, &backdrop);
    }
    std::wstring selected = Tr(OsdText::NoAudioOutputs);
    if (g_mixerOutputSwitchFailed) selected = Tr(OsdText::AudioSwitchFailed);
    else for (const auto& output : g_mixerOutputOptions) {
        if (output.id == g_mixerOutputId) {
            selected = output.name;
            break;
        }
    }
    DrawText(gfx, selected, header.X + 7.0f, header.Y + 1.0f,
             header.Width - 42.0f, header.Height - 2.0f, 11.5f, fg);
    const float cx = header.X + header.Width - 14.0f;
    const float cy = header.Y + header.Height / 2.0f;
    DrawControlButtonSurface(gfx, cx, cy, 12.5f, light, false,
                             g_mixerOutputExpanded, g_mixerOutputHeaderHovered);
    DrawControlChevron(gfx, cx, cy, fg,
                       g_mixerOutputExpanded ? FlyoutDirection::Up
                                             : FlyoutDirection::Down, 4.2f);
    if (!g_mixerOutputExpanded) return;
    const int rows = MixerOutputRows();
    if (!rows) return;
    const auto bounds = MixerOutputMenuRect();
    if (bounds.Y + bounds.Height > height) return;
    Gdiplus::GraphicsPath menu;
    AddRoundedRect(menu, bounds.X, bounds.Y, bounds.Width,
                   bounds.Height, corner);
    // Opaque over the underlying sliders, but honor the custom OSD background.
    Gdiplus::SolidBrush panel(ToGdiColor(OsdBackgroundRgb(light)));
    gfx.FillPath(&panel, &menu);
    if (!g_ddcBorderless.load()) {
        Gdiplus::Pen border(PanelBorderColor(light), .8f);
        gfx.DrawPath(&border, &menu);
    }
    for (int row = 0; row < rows; ++row) {
        const int index = row + g_mixerOutputScroll;
        const auto& item = g_mixerOutputOptions[index];
        const auto itemBounds = MixerOutputRowRect(row);
        const bool current = item.id == g_mixerOutputId;
        const bool hovered = index == g_mixerOutputHoveredRow;
        if (current || hovered) {
            Gdiplus::GraphicsPath tile;
            AddRoundedRect(tile, itemBounds.X, itemBounds.Y,
                           itemBounds.Width, itemBounds.Height,
                           std::min(6.0f, corner));
            Gdiplus::SolidBrush highlight(ToGdiColor(accentRgb,
                current ? (light ? 34 : 60) : (light ? 20 : 34)));
            gfx.FillPath(&highlight, &tile);
        }
        if (current)
            DrawText(gfx, L"✓", itemBounds.X + 4.0f, itemBounds.Y, 16.0f,
                     itemBounds.Height, 12.0f, ToGdiColor(accentRgb));
        DrawText(gfx, item.name, itemBounds.X + 24.0f, itemBounds.Y,
                 itemBounds.Width - 34.0f, itemBounds.Height, 11.5f, fg);
    }
    if (static_cast<int>(g_mixerOutputOptions.size()) > rows) {
        Gdiplus::SolidBrush scroll(ToGdiColor(accentRgb, 160));
        const float travel = bounds.Height - 10.0f;
        const float thumb = std::max(8.0f, travel * rows /
            static_cast<float>(g_mixerOutputOptions.size()));
        const int maxOffset = static_cast<int>(g_mixerOutputOptions.size()) - rows;
        const float y = bounds.Y + 5.0f +
            (travel - thumb) * g_mixerOutputScroll / std::max(1, maxOffset);
        gfx.FillRectangle(&scroll, bounds.X + bounds.Width - 4.0f,
                          y, 2.0f, thumb);
    }
}

void DrawMixerPanel(Gdiplus::Graphics& gfx) {
    const float width = g_panelWidth / g_scale;
    const float h = g_panelHeight / g_scale;
    DrawPanelCard(gfx, width, h, true);
    const bool horizontal = !g_verticalVolumeBrightness.load();
    const bool light = IsLightTheme();
    const DWORD textRgb = OsdTextRgb(light);
    const DWORD accentRgb = OsdAccentRgb();
    const DWORD trackRgb = OsdTrackRgb(light, true);
    const Gdiplus::Color fg = ToGdiColor(textRgb);
    Gdiplus::SolidBrush track(ToGdiColor(trackRgb));
    Gdiplus::SolidBrush active(ToGdiColor(accentRgb));
    DrawText(gfx, Tr(OsdText::VolumeMixer), horizontal ? 27.0f : 17.0f,
             10.0f, MixerOutputHeader().X - (horizontal ? 31.0f : 21.0f),
             30.0f, 15.0f, fg);
    const int rows = MixerVisibleRows();
    const int total = static_cast<int>(g_mixerEntries.size()) + 1;
    ClampMixerScroll();
    for (int row = 0; row < rows; ++row) {
        const int index = row + g_mixerScroll;
        if (index >= total) break;
        const float value = index == 0 ? g_mixerMasterLevel :
                            g_mixerEntries[index - 1].scalar;
        const bool muted = index == 0 ? g_mixerMasterMuted :
                           g_mixerEntries[index - 1].muted;
        const float y = kMixerFirstRowY + row * kMixerRowStep;
        // Stretch tracks with the independently configured panel width.
        // Hittest/drag share MixerTrackLength(), preventing control drift.
        const float iconX = horizontal ? 28.0f : 25.0f;
        if (index > 0 && g_mixerEntries[index - 1].appIcon) {
            Gdiplus::Bitmap bmp(g_mixerEntries[index - 1].appIcon);
            if (bmp.GetLastStatus() == Gdiplus::Ok)
                gfx.DrawImage(&bmp, iconX, y - 8.0f, 19.0f, 19.0f);
        } else if (index == 0) {
            DrawUniformStatusIcon(gfx, fg, iconX + 9.0f, y + 2.0f,
                PopupKind::NativeVolume, static_cast<int>(value * 100), muted);
        } else {
            DrawText(gfx, L"◉", iconX - 2.0f, y - 9.0f,
                     28.0f, 23.0f, 14.0f, fg, true);
        }
        // Muted app: preserve the recognizable process icon beneath a
        // translucent tile and a compact diagonal mute mark.
        if (muted && index > 0) {
            Gdiplus::GraphicsPath overlay;
            AddRoundedRect(overlay, iconX, y - 8.0f,
                           19.0f, 19.0f, 4.0f);
            Gdiplus::SolidBrush shade(light
                ? Gdiplus::Color(165, 250, 250, 252)
                : Gdiplus::Color(165, 22, 22, 26));
            gfx.FillPath(&shade, &overlay);
            Gdiplus::Pen slash(fg, 2.0f);
            slash.SetStartCap(Gdiplus::LineCapRound);
            slash.SetEndCap(Gdiplus::LineCapRound);
            gfx.DrawLine(&slash, iconX + 4.5f, y + 7.0f,
                         iconX + 14.5f, y - 4.5f);
        }
        Gdiplus::GraphicsPath back;
        AddRoundedRect(back, kMixerTrackStart, y + 1.0f,
                       MixerTrackLength(), kMixerTrackHeight,
                       kMixerTrackHeight / 2.0f);
        gfx.FillPath(&track, &back);
        const float filled = MixerTrackLength() *
            std::clamp(value, 0.0f, 1.0f);
        if (filled > 0) {
            auto state = gfx.Save();
            gfx.SetClip(Gdiplus::RectF(kMixerTrackStart,
                                      y + 1.0f, filled, kMixerTrackHeight));
            gfx.FillPath(&active, &back);
            gfx.Restore(state);
        }
        DrawTrackThumb(gfx, kMixerTrackStart + filled,
                       y + 1.0f + kMixerTrackHeight / 2.0f,
                       ToGdiColor(accentRgb), light);
        DrawText(gfx, std::to_wstring(static_cast<int>(std::lround(value * 100))) + L"%",
                 kMixerTrackStart + MixerTrackLength() + 11.0f,
                 y - 7.0f, horizontal ? 34.0f : 41.0f,
                 23.0f, 11.0f, fg);
    }
    if (total > rows) {
        // A small scroll thumb rather than a footer that consumes a row.
        Gdiplus::SolidBrush scrollbar(ToGdiColor(accentRgb, 190));
        const float travel = std::max(4.0f, h - 55.0f);
        const float thumb = std::max(12.0f, travel * rows / total);
        const float offset = MixerMaximumScroll() > 0
            ? (travel - thumb) * g_mixerScroll / MixerMaximumScroll() : 0;
        gfx.FillRectangle(&scrollbar, width - (horizontal ? 21.0f : 10.0f),
                          42.0f + offset, 3.0f, thumb);
    }
    // Draw last so the dropdown visually overlays the mixer tracks.
    DrawMixerOutputPicker(gfx, width, h, fg, light, accentRgb);
}

void RenderPanel() {
    if (!g_panelWnd || !g_gdiplusToken || g_panelMode == PanelMode::None) return;
    const int w = g_panelWidth, h = g_panelHeight;
    if (w <= 0 || h <= 0) return;
    HDC screen = GetDC(nullptr);
    if (!screen) return;
    HDC memory = CreateCompatibleDC(screen);
    if (!memory) { ReleaseDC(nullptr, screen); return; }
    void* pixels = nullptr;
    HBITMAP bmp = CreateArgbDib(screen, w, h, &pixels);
    if (bmp && pixels) {
        HGDIOBJ old = SelectObject(memory, bmp);
        {
            Gdiplus::Bitmap surface(w, h, w * 4,
                PixelFormat32bppPARGB, static_cast<BYTE*>(pixels));
            Gdiplus::Graphics gfx(&surface);
            gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
            gfx.Clear(Gdiplus::Color(0,0,0,0));
            gfx.ScaleTransform(g_scale, g_scale);
            if (g_panelMode == PanelMode::Media) DrawMediaPanel(gfx);
            else if (g_panelMode == PanelMode::Mixer) DrawMixerPanel(gfx);
            else DrawNoticeDetails(gfx);
        }
        (void)PublishArgbLayer(g_panelWnd, screen, memory, w, h);
        if (g_displayOutputMode.load(std::memory_order_relaxed) == 3)
            RenderMirroredFrame(screen, pixels, w, h, true);
        SelectObject(memory, old);
        DeleteObject(bmp);
    }
    DeleteDC(memory);
    ReleaseDC(nullptr, screen);
}

void ClosePanel() {
    const bool hadCenteredPair = NeedsCompositeCentering();
    StopMixerOutputNotifications();
    g_mixerOutputExpanded = false;
    g_mixerOutputHoveredRow = -1;
    g_mixerOutputHeaderHovered = false;
    g_mixerOutputSwitchFailed = false;
    g_mixerOutputScroll = 0;
    g_mixerOutputOptions.clear();
    g_mixerOutputId.clear();
    HideMirroredWindows(true);
    if (g_popupWnd) KillTimer(g_popupWnd, kMediaAnimationTimer);
    const bool heldCapture = g_mediaPressedIndex >= 0 ||
        g_extraPressedAction != 0 || g_mediaCyclePressed ||
        g_mixerDrag || g_mixerMutePressedIndex >= 0;
    g_mediaPressedIndex = -1;
    g_mediaPressedInside = false;
    g_mediaCyclePressed = false;
    g_mediaCycleInside = false;
    g_extraPressedAction = 0;
    g_extraPressedInside = false;
    g_mediaSeeking = false;
    g_mediaSeekHoldUntil = 0;
    g_mediaFeedbackIndex = -1;
    if (heldCapture && g_panelWnd && GetCapture() == g_panelWnd)
        ReleaseCapture();
    g_mixerMutePressedIndex = -1;
    if (g_panelWnd) ShowWindow(g_panelWnd, SW_HIDE);
    g_panelMode = PanelMode::None;
    CleanupMixerIcons();
    g_mixerEntries.clear();
    g_mixerMaster.Reset();
    g_mixerDrag = false;
    g_mixerDragIndex = -1;
    if (hadCenteredPair) RefreshCompositePlacementIfChanged();
}


void ShowPanel() {
    if (!g_panelWnd || !g_popupWnd || g_panelMode == PanelMode::None) return;
    const bool vertical = g_verticalVolumeBrightness.load();
    const bool volumePanel = g_panelMode == PanelMode::Media ||
                             g_panelMode == PanelMode::Mixer;
    // Reposition first: monitor DPI may change the scale used for the panel.
    if (NeedsCompositeCentering()) RefreshCompositePlacementIfChanged();
    if (volumePanel) {
        // Exact physical dimension inheritance avoids 1px rounding drift.
        const bool media = g_panelMode == PanelMode::Media;
        g_panelWidth = vertical ? static_cast<int>(std::lround(
            (media ? g_verticalSmtcWidth.load() :
                     g_verticalMixerWidth.load()) * g_scale)) : g_width;
        g_panelHeight = vertical ? g_height : static_cast<int>(std::lround(
            (media ? g_horizontalSmtcHeight.load() :
                     g_horizontalMixerHeight.load()) * g_scale));
    } else {
        g_panelWidth = static_cast<int>(std::lround(340.0f * g_scale));
        g_panelHeight = std::max(g_height,
            static_cast<int>(std::lround(220.0f * g_scale)));
    }
    // SMTC/Mixer each inherit horizontal WIDTH or vertical HEIGHT, with
    // independent heights/widths for the other axis. Details keep legacy.
    ClampMixerScroll();
    RECT main{};
    if (!GetWindowRect(g_popupWnd, &main)) return;
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(MonitorFromWindow(g_popupWnd, MONITOR_DEFAULTTONEAREST), &mi))
        return;
    const RECT& work = mi.rcWork;
    const int panelInset = static_cast<int>(std::lround(4.0f * g_scale));
    const int sideInset = static_cast<int>(std::lround(
        (vertical ? 7.0f : 13.0f) * g_scale));
    const FlyoutDirection direction = GetFlyoutDirection();
    const int position = g_position.load();
    int x = main.left, y = main.top;
    if (volumePanel) {
        const auto attached = GetPanelAttachment(vertical, direction, g_scale,
            main.right - main.left, main.bottom - main.top,
            g_panelWidth, g_panelHeight);
        x += attached.x;
        y += attached.y;
    } else if (vertical) {
        // Preserve the legacy positioning of non-volume detail panels.
        const int gap = static_cast<int>(std::lround(7.0f * g_scale));
        x = direction == FlyoutDirection::Left
            ? main.left + sideInset - gap + panelInset - g_panelWidth
            : main.right - sideInset + gap - panelInset;
    } else {
        const int gap = static_cast<int>(std::lround(7.0f * g_scale));
        const int topInset = static_cast<int>(std::lround(10.0f * g_scale));
        const int bottomInset = static_cast<int>(std::lround(13.0f * g_scale));
        y = direction == FlyoutDirection::Up
            ? main.top + topInset - gap + bottomInset - g_panelHeight
            : main.bottom - bottomInset + gap - topInset;
        if (PositionIsLeft(position))
            x = main.left + sideInset - panelInset;
        else if (PositionIsRight(position))
            x = main.right - sideInset + panelInset - g_panelWidth;
        else
            x = main.left + ((main.right - main.left) - g_panelWidth) / 2;
    }
    x = ClampPopupAxis(x, g_panelWidth,
        !vertical && PositionCentersX(position) ? mi.rcMonitor : work, true);
    y = ClampPopupAxis(y, g_panelHeight,
        vertical && PositionCentersY(position) ? mi.rcMonitor : work, false);
    SetWindowPos(g_panelWnd, HWND_TOPMOST, x, y, g_panelWidth, g_panelHeight,
                 SWP_NOACTIVATE | SWP_NOREDRAW);
    RenderPanel();
    ShowWindow(g_panelWnd, SW_SHOWNOACTIVATE);
    if (g_popupWnd) {
        if (g_panelMode == PanelMode::Media)
            SetTimer(g_popupWnd, kMediaAnimationTimer,
                     kMediaAnimationIntervalMs, nullptr);
        else
            KillTimer(g_popupWnd, kMediaAnimationTimer);
    }
}

void ShowVolumePanelIfReady() {
    if (g_panelMode == PanelMode::Mixer) return;
    if (g_showSmtcOnVolume.load() && g_mediaCurrent.available) {
        g_panelMode = PanelMode::Media;
        ShowPanel();
    } else ClosePanel();
}

// Expand/collapse is a real, padded circular button. The painted button,
// transparent hit target and direction use one set of constants; it never
// depends on the native Hide switch or enables a custom volume popup itself.
void DrawExpandChevron(Gdiplus::Graphics& gfx, float x, float y,
                       Gdiplus::Color color) {
    const bool vertical = g_verticalVolumeBrightness.load();
    const bool expanded = g_panelMode == PanelMode::Mixer;
    const bool pressed = g_arrowPressed;
    const float radius = vertical ? kVerticalArrowRadius
                                  : kHorizontalArrowRadius;
    DrawControlButtonSurface(gfx, x, y, radius, IsLightTheme(), pressed,
                             expanded, g_arrowHovered);
    // Mirror the direction when the mixer is open, preserving flyout routing.
    const FlyoutDirection dir = expanded
        ? InverseDirection(GetFlyoutDirection()) : GetFlyoutDirection();
    DrawControlChevron(gfx, x, y + (pressed ? 0.35f : 0.0f), color, dir);
}

void DrawHorizontalVolume(Gdiplus::Graphics& gfx) {
    const float logicalW = MainLogicalWidth();
    const float logicalH = MainLogicalHeight();
    const float centerY = MainCenterY();
    bool light = IsLightTheme();
    DWORD bg = OsdBackgroundRgb(light);
    DWORD fgRgb = OsdTextRgb(light);
    DWORD accentRgb = OsdAccentRgb();
    DWORD trackRgb = OsdTrackRgb(light);
    Gdiplus::GraphicsPath body;
    AddRoundedRect(body, 13.0f, 10.0f, logicalW - 26.0f,
                   logicalH - 23.0f, static_cast<float>(g_cornerRadius.load()));
    Gdiplus::SolidBrush base(ToGdiColor(bg,
        OsdBackgroundAlpha()));
    gfx.FillPath(&base, &body);
    Gdiplus::Color fg = ToGdiColor(fgRgb);
    float speakerX = 0.0f, speakerY = 0.0f;
    MainVolumeIconCenter(speakerX, speakerY);
    DrawUniformStatusIcon(gfx, fg, speakerX, speakerY, PopupKind::NativeVolume,
                          g_nativePercent, g_nativeMuted);
    const float trackW = logicalW - (g_showMixerArrow.load() ? 191.0f : 169.0f);
    Gdiplus::GraphicsPath track;
    AddRoundedRect(track, 76.0f, centerY - 4.0f, trackW, 8.0f, 4.0f);
    Gdiplus::SolidBrush tb(ToGdiColor(trackRgb));
    gfx.FillPath(&tb, &track);
    int percent = std::clamp(g_nativePercent, 0, 100);
    if (g_nativePercentKnown && percent > 0) {
        float fill = trackW * percent / 100.0f;
        auto state = gfx.Save();
        gfx.SetClip(Gdiplus::RectF(76.0f, centerY - 4.0f, fill, 8.0f));
        Gdiplus::SolidBrush sb(ToGdiColor(accentRgb));
        gfx.FillPath(&sb, &track);
        gfx.Restore(state);
    }
    if (g_nativePercentKnown)
        DrawTrackThumb(gfx, 76.0f + trackW * percent / 100.0f,
                       centerY, ToGdiColor(accentRgb), light);
    if (g_showValue.load()) {
        // Without the chevron, move the number right along with the track;
        // the 167px default track must not overlap the value label.
        const float valueX = logicalW -
            (g_showMixerArrow.load() ? 108.0f : 84.0f);
        DrawText(gfx, std::to_wstring(percent) + L"%",
                 valueX, centerY - 16.0f, 54.0f, 32.0f,
                 15, fg, true);
    }
    if (g_showMixerArrow.load())
        DrawExpandChevron(gfx, HorizontalChevronX(), HorizontalChevronY(), fg);
}


// Lock-key notices use the same 296x92 status surface as native, device and
// network notices. Keep a compact state underline as an extra visual cue.
void DrawLockStatus(Gdiplus::Graphics& gfx) {
    const bool light = IsLightTheme();
    DrawStatusNoticeChrome(gfx, light);
    const Gdiplus::Color fg = ToGdiColor(OsdTextRgb(light));
    const Gdiplus::Color quiet(195, fg.GetR(), fg.GetG(), fg.GetB());
    const int key = std::clamp(g_lastLock, 0, 3);
    const Gdiplus::Color active = ToGdiColor(OsdAccentRgb());
    const Gdiplus::Color inactive(145, active.GetR(), active.GetG(), active.GetB());
    DrawText(gfx, kLockGlyphs[key], kStatusIconX + 2.0f,
             kStatusIconY + 3.0f, kStatusIconSize - 4.0f,
             kStatusIconSize - 6.0f, key == 3 ? 16.0f : 23.0f,
             g_lastLockValue ? active : quiet, true);
    DrawStatusNoticeLabels(gfx, kLockDisplayNames[key],
                           g_lastLockValue ? Tr(OsdText::On) : Tr(OsdText::Off),
                           fg);
    Gdiplus::GraphicsPath line;
    AddRoundedRect(line, kStatusTextX, 74.0f, 188.0f, 3.0f, 1.5f);
    Gdiplus::SolidBrush lineBrush(g_lastLockValue ? active : inactive);
    gfx.FillPath(&lineBrush, &line);
}

// Low-level keyboard hook: event-driven and no keyboard polling. Toggle state
// is tracked on first key down (not repeated autorepeat key-down messages).
// ============================================================
// Input hit surfaces, UI event dispatch and thread
// ============================================================
LRESULT CALLBACK LockKeyProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && lp) {
        const auto* event = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lp);
        for (int i = 0; i < 4; ++i) {
            if (event->vkCode != static_cast<DWORD>(kLockVk[i])) continue;
            bool down = wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN;
            bool up = wp == WM_KEYUP || wp == WM_SYSKEYUP;
            if (down && !g_lockPressed[i]) {
                g_lockPressed[i] = true;
                g_lockToggle[i] = !g_lockToggle[i];
                if (g_showLockKeys[i].load() && g_receiveWnd)
                    PostMessageW(g_receiveWnd, kLockToggleMessage,
                                 static_cast<WPARAM>(i),
                                 static_cast<LPARAM>(g_lockToggle[i]));
            } else if (up) g_lockPressed[i] = false;
            break;
        }
    }
    return CallNextHookEx(g_lockHook, code, wp, lp);
}

// The main layered OSD remains mouse-transparent. A dedicated, nearly
// invisible hit window covers only the visible mixer button, keeping the
// rest of the popup click-through and free of focus changes.
void SetPopupInteractive(bool interactive) {
    if (!g_popupWnd) return;
    LONG_PTR flags = GetWindowLongPtrW(g_popupWnd, GWL_EXSTYLE);
    if ((!interactive && !(flags & WS_EX_TRANSPARENT)) ||
        (interactive && (flags & WS_EX_TRANSPARENT))) {
        SetWindowLongPtrW(g_popupWnd, GWL_EXSTYLE,
            interactive ? (flags & ~WS_EX_TRANSPARENT) : (flags | WS_EX_TRANSPARENT));
        SetWindowPos(g_popupWnd, nullptr, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE |
            SWP_FRAMECHANGED);
    }
}

void UpdateArrowHitWindow() {
    if (!g_arrowWnd) return;
    if (g_popupKind != PopupKind::NativeVolume || !g_showMixerArrow.load() ||
        !g_popupWnd || !IsWindowVisible(g_popupWnd)) {
        g_arrowHovered = false;
        g_arrowPressed = false;
        if (GetCapture() == g_arrowWnd) ReleaseCapture();
        ShowWindow(g_arrowWnd, SW_HIDE);
        return;
    }
    RECT main{};
    GetWindowRect(g_popupWnd, &main);
    const bool vertical = g_verticalVolumeBrightness.load();
    const float arrowX = vertical ? VerticalChevronX() : HorizontalChevronX();
    const float arrowY = vertical ? VerticalChevronY() : HorizontalChevronY();
    const float targetLogicalSize = kArrowHitDiameter;
    const int targetW = std::max(16, static_cast<int>(
        std::lround(targetLogicalSize * g_scale)));
    const int targetH = targetW;
    const int x = main.left + static_cast<int>(std::lround(arrowX * g_scale)) - targetW / 2;
    const int y = main.top + static_cast<int>(std::lround(arrowY * g_scale)) - targetH / 2;
    SetWindowPos(g_arrowWnd, HWND_TOPMOST, x, y, targetW, targetH,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

// An almost invisible, non-activating mouse surface. The remaining main OSD
// stays click-through, preserving track dragging and mixer-arrow hit targets.
void UpdateSpeakerHitWindow() {
    if (!g_speakerHitWnd) return;
    if (g_popupKind != PopupKind::NativeVolume || !g_popupWnd ||
        !IsWindowVisible(g_popupWnd) || g_closing.load()) {
        g_speakerPressed = false;
        if (GetCapture() == g_speakerHitWnd) ReleaseCapture();
        ShowWindow(g_speakerHitWnd, SW_HIDE);
        return;
    }
    RECT popup{};
    if (!GetWindowRect(g_popupWnd, &popup) || g_scale <= 0.0f) {
        ShowWindow(g_speakerHitWnd, SW_HIDE);
        return;
    }
    float cx = 0.0f, cy = 0.0f;
    MainVolumeIconCenter(cx, cy);
    const float hitSize = std::max(26.0f,
        static_cast<float>(g_iconSize.load()) + 8.0f);
    const int size = std::max(16, static_cast<int>(std::lround(hitSize * g_scale)));
    const int x = popup.left + static_cast<int>(std::lround(cx * g_scale)) - size / 2;
    const int y = popup.top + static_cast<int>(std::lround(cy * g_scale)) - size / 2;
    SetWindowPos(g_speakerHitWnd, HWND_TOPMOST, x, y, size, size,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

void ResetHideTimer(UINT ms) {
    if (g_popupWnd)
        SetTimer(g_popupWnd, kHideTimer, ms, nullptr);
}

void ResetHideTimerFor(DurationKind kind) {
    g_activeDurationKind = kind;
    ResetHideTimer(OsdDuration(kind));
}

// Shared routing for every category completed in the experimental XAML
// renderer. The original GDI+ event handler remains ONLY behind an explicit
// XAML-off setting; failure/initialization never silently paints the old UI.
void ShowMigratedXamlLevel(PopupKind kind) {
    const bool brightness = kind == PopupKind::NativeBrightness;
    HideGdiLevelForXaml();
    RECT target{};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &target)) {
        Wh_Log(L"Fluent OSD v1.0.24: XAML %s missing anchor",
               brightness ? L"brightness" : L"volume");
        return;
    }
    const auto snapshot = MakeXamlSnapshot(kind, target, g_scale);
    static bool routeLogged[2]{};
    static bool unavailableLogged[2]{};
    const int index = brightness ? 1 : 0;
    if (xaml_osd::Show(snapshot)) {
        if (!routeLogged[index]) {
            Wh_Log(L"Fluent OSD v1.0.24: native %s -> XAML only",
                   brightness ? L"brightness" : L"volume");
            routeLogged[index] = true;
        }
        unavailableLogged[index] = false;
    } else if (!unavailableLogged[index]) {
        Wh_Log(L"Fluent OSD v1.0.24: XAML %s unavailable; NO GDI+ fallback",
               brightness ? L"brightness" : L"volume");
        unavailableLogged[index] = true;
    }
}


// Lock-key OSD is the first compact, noninteractive XAML status category.
// Retain the keyboard hook, localization, placement and duration engine.
void ShowMigratedXamlLockStatus() {
    HideGdiLevelForXaml();
    RECT target{};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &target)) {
        Wh_Log(L"XAML v1.0.24: lock status missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::LockStatus, target, DurationKind::LockKeys);
    snapshot.statusTitle = kLockDisplayNames[std::clamp(g_lastLock, 0, 3)];
    snapshot.statusGlyph = kLockGlyphs[std::clamp(g_lastLock, 0, 3)];
    snapshot.statusDetail = g_lastLockValue
        ? Tr(OsdText::On) : Tr(OsdText::Off);
    snapshot.statusActive = g_lastLockValue;
    if (!xaml_osd::Show(snapshot))
        Wh_Log(L"XAML v1.0.24: lock status unavailable; NO GDI+ fallback");
}

// Entire USB/Bluetooth/network category: single-item notifications and
// aggregated, clickable device lists share the same XAML Island renderer.
// Event identity and debounce stay in the existing event engine; the
// XAML snapshot owns the names and uses installed Segoe Fluent Icons.
void ShowMigratedXamlDeviceNotice(DurationKind duration) {
    HideGdiLevelForXaml();
    RECT target{};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &target)) {
        Wh_Log(L"XAML v1.0.24: device notice missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::NoticeStatus, target, duration, true);
    snapshot.statusTitle = g_noticeTitle;
    snapshot.statusDetail = g_noticeBody;
    snapshot.noticeDetails = g_noticeDetails;
    snapshot.noticeDetailsHeading = Tr(OsdText::EventDetails);
    snapshot.noticeInteractiveDurationMs =
        OsdDuration(DurationKind::Interactive);
    switch (g_noticeIcon) {
        case NoticeIcon::Bluetooth: snapshot.statusGlyph = L"\uE702"; break;
        case NoticeIcon::Usb:       snapshot.statusGlyph = L"\uE88E"; break;
        case NoticeIcon::Network:   snapshot.statusGlyph = L"\uE968"; break;
        default: return;
    }
    if (!xaml_osd::Show(snapshot))
        Wh_Log(L"XAML v1.0.24: device notice unavailable; NO GDI+ fallback");
}

// A native system event already has one immutable display payload; use
// the existing XAML status card, not another GDI+ painter or Win32 hit HWND.
// Glyph identifiers are Microsoft Segoe Fluent Icons (Windows 11).
void ShowMigratedXamlNativeEvent() {
    HideGdiLevelForXaml();
    RECT target{};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &target)) {
        Wh_Log(L"XAML v1.0.24: native event missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::NativeEvent, target,
        DurationKind::NativeEvents, true);

    const NativeEventInfo& event = g_nativeEventCurrent;
    switch (event.kind) {
        case Kind::Keyboard:
            snapshot.statusTitle = Tr(OsdText::KeyboardBacklight);
            snapshot.statusDetail = event.value >= 0 && event.value <= 100
                ? std::to_wstring(event.value) + L"%"
                : std::wstring(Tr(OsdText::Level)) +
                  std::to_wstring(event.value);
            snapshot.statusGlyph = L"\uE765"; // KeyboardClassic
            break;
        case Kind::Airplane:
            snapshot.statusTitle = Tr(OsdText::AirplaneMode);
            snapshot.statusDetail = event.value
                ? Tr(OsdText::Enabled) : Tr(OsdText::Disabled);
            snapshot.statusGlyph = L"\uE709"; // Airplane
            break;
        case Kind::Camera: {
            const bool access = event.variant == 1;
            snapshot.statusTitle = access
                ? Tr(OsdText::CameraAccess) : Tr(OsdText::Camera);
            snapshot.statusDetail = access
                ? (event.value ? Tr(OsdText::Allowed) : Tr(OsdText::Blocked))
                : (event.value ? Tr(OsdText::Enabled) : Tr(OsdText::Disabled));
            snapshot.statusGlyph = L"\uE722"; // Camera (not Video E714)
            break;
        }
        case Kind::Microphone:
            snapshot.statusTitle = Tr(OsdText::Microphone);
            // 0/1 are the only recognized states of this non-public event.
            snapshot.statusDetail = event.value == 0 ? Tr(OsdText::Unmuted)
                : event.value == 1 ? Tr(OsdText::Muted)
                : Tr(OsdText::StatusChanged);
            snapshot.statusGlyph = L"\uE720"; // Microphone
            break;
        case Kind::Desktop:
            snapshot.statusTitle = Tr(OsdText::VirtualDesktop);
            snapshot.statusDetail = event.text.empty()
                ? Tr(OsdText::DesktopSwitched) : event.text;
            snapshot.statusGlyph = L"\uE7C4"; // TaskView
            break;
        case Kind::Text:
            snapshot.statusTitle = Tr(OsdText::SystemNotice);
            snapshot.statusDetail = event.text.empty()
                ? Tr(OsdText::StatusChanged) : event.text;
            snapshot.statusGlyph = L"\uE7C3"; // Page
            break;
        default:
            // Do not turn unknown payload kinds into invented status UI.
            return;
    }
    if (!xaml_osd::Show(snapshot))
        Wh_Log(L"XAML v1.0.24: native event unavailable; NO GDI+ fallback");
}

// Convert the already-downscaled clipboard HBITMAP into a private, bounded
// byte buffer on the Explorer UI thread. A GDI handle never crosses to XAML.
bool CopyClipboardThumbnailPixels(HBITMAP bitmap,
                                  xaml_osd::Snapshot& snapshot) {
    if (!bitmap) return false;
    BITMAP info{};
    if (GetObjectW(bitmap, sizeof(info), &info) != sizeof(info) ||
        info.bmWidth <= 0 || info.bmHeight <= 0 ||
        info.bmWidth > 224 || info.bmHeight > 164)
        return false;
    const auto width = static_cast<uint32_t>(info.bmWidth);
    const auto height = static_cast<uint32_t>(info.bmHeight);
    const size_t bytes = static_cast<size_t>(width) * height * 4;
    if (!bytes || bytes > 224u * 164u * 4u) return false;
    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = info.bmWidth;
    bmi.bmiHeader.biHeight = -info.bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    std::vector<uint8_t> pixels(bytes);
    HDC dc = GetDC(nullptr);
    if (!dc) return false;
    const int copied = GetDIBits(dc, bitmap, 0, height, pixels.data(),
                                &bmi, DIB_RGB_COLORS);
    ReleaseDC(nullptr, dc);
    if (copied != static_cast<int>(height)) return false;
    // Win32 CF_BITMAP alpha is unspecified: match the original opaque
    // preview instead of accidentally displaying entirely transparent pixels.
    for (size_t offset = 3; offset < bytes; offset += 4)
        pixels[offset] = 255;
    snapshot.clipboardWidth = width;
    snapshot.clipboardHeight = height;
    snapshot.clipboardPixels = std::move(pixels);
    return true;
}

// Text/file notices use the same compact XAML card. If the original capture
// produced a bounded thumbnail, use the native XAML image-first layout.
void ShowMigratedXamlClipboardNotice() {
    HideGdiLevelForXaml();
    RECT target{};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &target)) {
        ClearClipboardThumbnail();
        Wh_Log(L"XAML v1.0.24: clipboard notice missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::NoticeStatus, target,
        DurationKind::Clipboard, true);
    snapshot.statusTitle = g_noticeTitle;
    snapshot.statusDetail = g_noticeBody;
    snapshot.statusGlyph = L"\uE8C8"; // Segoe Fluent Icons Copy
    const bool image = CopyClipboardThumbnailPixels(
        g_clipboardThumbnail, snapshot);
    if (image)
        snapshot.kind = xaml_osd::LevelKind::ClipboardImage;
    // XAML owns pixel bytes now. Release the transient GDI thumbnail
    // regardless of whether posting the XAML snapshot succeeds.
    ClearClipboardThumbnail();
    if (!image) {
        // Image placement was selected before conversion. Recalculate
        // compact status-card bounds after a conversion failure.
        BrightnessEvent empty{};
        MovePopupToDisplay(empty);
        if (!GetWindowRect(g_popupWnd, &snapshot.anchor)) return;
        snapshot.scale = g_scale;
    }
    if (!xaml_osd::Show(snapshot))
        Wh_Log(L"XAML v1.0.24: clipboard notice unavailable; NO GDI+ fallback");
}

void ShowNativeVolumePopup() {
    BrightnessEvent ev{};
    MovePopupToDisplay(ev);
    if (g_xamlForMigrated.load()) {
        ShowMigratedXamlLevel(PopupKind::NativeVolume);
        return;
    }
    // Original volume GDI+ renderer is used ONLY when XAML was disabled.
    SetPopupInteractive(false);
    ShowPopupAnimated();
    UpdateArrowHitWindow();
    RequestMedia();
    ShowVolumePanelIfReady();
    ResetHideTimerFor(g_panelMode == PanelMode::Mixer
        ? DurationKind::Interactive
        : (g_showSmtcOnVolume.load() ? DurationKind::Media
                                      : DurationKind::Volume));
}

void ActivateMixer() {
    if (g_panelMode == PanelMode::Mixer) {
        ClosePanel();
        ShowVolumePanelIfReady();
    } else {
        ClosePanel();
        g_panelMode = PanelMode::Mixer;
        g_mixerScroll = 0;
        RefreshMixer();
        StartMixerOutputNotifications();
        ShowPanel();
    }
    RenderPopup();  // The chevron reverses only while the mixer is expanded.
    ResetHideTimerFor(DurationKind::Interactive);
}


void HandleMixerDrag(LPARAM lp) {
    float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
    float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
    SetMixerSlider(x, y);
    RenderPanel();
    ResetHideTimerFor(DurationKind::Interactive);
}

// XAML interaction commands reach this original UI thread without
// cross-apartment WinRT calls. Physical DDC identity is carried on each
// command, not inferred from whichever monitor happened to be last active.
struct XamlPendingDdcWrite {
    BrightnessEvent event{};
    DWORD previousValue = 0, generation = 0;
};
std::vector<XamlPendingDdcWrite> g_xamlPendingDdcWrites; // UI thread only.

void ProcessXamlInputs() {
    auto inputs = xaml_osd::TakeInputs();
    if (g_closing.load() || !g_xamlForMigrated.load()) return;
    for (const auto& cmd : inputs) {
        if (cmd.kind == xaml_osd::LevelKind::Volume) {
            if (g_popupKind != PopupKind::NativeVolume) continue;
            bool ok = false;
            if (cmd.action == xaml_osd::InputAction::ToggleMute)
                ok = ToggleDefaultAudioMute();
            else if (cmd.action == xaml_osd::InputAction::Wheel) {
                const int steps = cmd.value / WHEEL_DELTA;
                ok = steps != 0 && AdjustDefaultAudioWheel(steps);
            } else ok = SetDefaultAudioBarPercent(cmd.value);
            if (ok) ShowMigratedXamlLevel(PopupKind::NativeVolume);
            continue;
        }
        if (!g_wheelWriteWake) continue;

        if (cmd.kind == xaml_osd::LevelKind::NativeBrightness) {
            if (g_popupKind != PopupKind::NativeBrightness ||
                !g_nativePercentKnown) continue;
            if (cmd.action == xaml_osd::InputAction::ToggleMute) continue;
            const int requested = cmd.action == xaml_osd::InputAction::Wheel
                ? g_nativePercent + (cmd.value / WHEEL_DELTA) * kWheelStepPercent
                : cmd.value;
            const int percent = std::clamp(requested, 0, 100);
            if (percent == g_nativePercent) continue;
            BrightnessWheelTask task{};
            task.native = true;
            task.value = percent;
            task.generation = ++g_wheelWriteGeneration;
            if (g_lastConfirmedNativeBrightness < 0)
                g_lastConfirmedNativeBrightness = g_nativePercent;
            g_nativePercent = percent;
            QueueBrightnessWheelTask(task);
            ShowMigratedXamlLevel(PopupKind::NativeBrightness);
            continue;
        }

        if (cmd.kind != xaml_osd::LevelKind::DdcBrightness ||
            g_popupKind != PopupKind::DdcBrightness ||
            cmd.action == xaml_osd::InputAction::ToggleMute) continue;
        const auto selected = std::find_if(
            g_ddcTargets.begin(), g_ddcTargets.end(),
            [&](const DdcTargetState& target) {
                return target.event.physicalIndex == cmd.physicalIndex &&
                    _wcsicmp(target.event.device, cmd.device) == 0;
            });
        if (selected == g_ddcTargets.end()) continue;
        auto& event = selected->event;
        if (event.maximum <= event.minimum) continue; // Unknown range.
        // Keep the actively edited physical target in the XAML batch.
        selected->expiresAt = GetTickCount64() +
            OsdDuration(DurationKind::DdcBrightness);
        const DWORD range = event.maximum - event.minimum;
        int percent = 0;
        if (cmd.action == xaml_osd::InputAction::Wheel) {
            bool known = false;
            percent = BrightnessPercent(event, &known) +
                (cmd.value / WHEEL_DELTA) * kWheelStepPercent;
        } else percent = cmd.value;
        percent = std::clamp(percent, 0, 100);
        const DWORD raw = osd_input::PercentToRaw(
            event.minimum, event.maximum, percent);
        if (raw == event.value) continue;

        BrightnessWheelTask task{};
        task.monitor = event;  // Exact display + physical index.
        task.value = static_cast<int>(raw);
        task.generation = ++g_wheelWriteGeneration;
        auto pending = std::find_if(
            g_xamlPendingDdcWrites.begin(), g_xamlPendingDdcWrites.end(),
            [&](const XamlPendingDdcWrite& item) {
                return item.event.physicalIndex == event.physicalIndex &&
                    _wcsicmp(item.event.device, event.device) == 0;
            });
        if (pending == g_xamlPendingDdcWrites.end()) {
            if (g_xamlPendingDdcWrites.size() >= kMaxDdcTargets)
                g_xamlPendingDdcWrites.erase(g_xamlPendingDdcWrites.begin());
            g_xamlPendingDdcWrites.push_back(
                {event, event.value, task.generation});
        } else pending->generation = task.generation;
        event.value = raw;
        if (g_visible.physicalIndex == event.physicalIndex &&
            _wcsicmp(g_visible.device, event.device) == 0)
            g_visible.value = raw;
        QueueBrightnessWheelTask(task);
        (void)ShowXamlDdcTargets(g_visible);
    }
}

LRESULT CALLBACK UiWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (hwnd == g_receiveWnd && msg == xaml_osd::kInputMessage) {
        ProcessXamlInputs();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == WM_TIMER && wp == kEventBatchTimer) {
        FlushNoticeBatch();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == WM_TIMER && wp == kDdcBatchTimer) {
        KillTimer(hwnd, kDdcBatchTimer);
        DisplayDdcBatch();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == WM_CLIPBOARDUPDATE) {
        ProcessClipboard();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == WM_DEVICECHANGE) {
        if (HandleDeviceChange(wp, lp)) return TRUE;
    }
    if (hwnd == g_receiveWnd && msg == kBluetoothQueueMessage) {
        bt_monitor::Drain();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == kBluetoothConfigMessage) {
        if (g_showBluetoothEvents.load()) bt_monitor::Start();
        else bt_monitor::Stop();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == kNetworkNoticeMessage) {
        if (g_showNetworkEvents.load()) {
            const bool changed = CaptureNetworkEvents();
            // An aggregate connectivity hint is not proof of which SSID or VPN
            // changed. Use a generic notice only when no NIC transition was found.
            if (!changed) {
                const int level = static_cast<int>(wp);
                const bool online = level >= 2;
                AddNoticeEvent(NoticeCategory::Network, online ?
                               NoticeAction::NetworkChanged : NoticeAction::Disconnected,
                               L"aggregate-connectivity", Tr(OsdText::WindowsNetwork));
            }
        }
        return 0;
    }
    if (msg == kNativeExtraMessage && hwnd == g_receiveWnd) {
        NativeEventInfo received;
        AcquireSRWLockExclusive(&g_nativeEventLock);
        received = std::move(g_nativeEventPending);
        g_nativeEventPending = NativeEventInfo{};
        g_nativeEventPosted = false;
        ReleaseSRWLockExclusive(&g_nativeEventLock);
        if (!ShowCustomNative(received.kind)) return 0;
        ClosePanel();
        g_nativeEventCurrent = std::move(received);
        g_popupKind = PopupKind::NativeEvent;
        BrightnessEvent ev{};
        MovePopupToDisplay(ev);
        if (g_xamlForMigrated.load()) {
            ShowMigratedXamlNativeEvent();
        } else {
            SetPopupInteractive(false);
            ShowPopupAnimated();
            UpdateArrowHitWindow();
            ResetHideTimerFor(DurationKind::NativeEvents);
        }
        return 0;
    }
    if (msg == kNativeOsdMessage && hwnd == g_receiveWnd) {
        const Kind kind = static_cast<Kind>(wp);
        if (kind != Kind::Volume && kind != Kind::Brightness)
            return 0;
        if (!ShowCustomNative(kind)) return 0;
        g_popupKind = kind == Kind::Volume ?
            PopupKind::NativeVolume : PopupKind::NativeBrightness;
        g_nativePercent = static_cast<int>(lp);
        if (kind == Kind::Brightness)
            g_lastConfirmedNativeBrightness = g_nativePercent;
        g_nativePercentKnown = g_nativePercent >= 0 && g_nativePercent <= 100;
        g_nativeMuted = false;
        if (kind == Kind::Volume) {
            int actual = 0;
            bool mute = false;
            if (ReadDefaultAudioVolume(actual, mute)) {
                g_nativePercent = actual;
                g_nativePercentKnown = true;
                g_nativeMuted = mute;
            }
            ShowNativeVolumePopup();
        } else {
            // Brightness has joined volume in the migrated XAML categories.
            // The XAML switch directly controls it, without any fallback.
            if (g_xamlForMigrated.load()) {
                BrightnessEvent ev{};
                MovePopupToDisplay(ev);
                ShowMigratedXamlLevel(PopupKind::NativeBrightness);
            } else {
                ClosePanel();
                BrightnessEvent ev{};
                MovePopupToDisplay(ev);
                SetPopupInteractive(false);
                ShowPopupAnimated();
                UpdateArrowHitWindow();
                ResetHideTimerFor(DurationKind::NativeBrightness);
            }
        }
        return 0;
    }
    if (msg == kAudioRefreshMessage && hwnd == g_receiveWnd) {
        if (g_mixerNotify) g_mixerNotify->ClearPending();
        if (g_panelMode == PanelMode::Mixer && !g_closing.load()) {
            RefreshMixer();
            RenderPanel();
        }
        return 0;
    }
    if (msg == kMediaUpdateMessage && hwnd == g_receiveWnd) {
        const std::wstring previousSource = g_mediaCurrent.sourceId;
        const uint32_t previousSelection = g_mediaCurrent.selectionSerial;
        AcquireSRWLockShared(&g_mediaLock);
        g_mediaCurrent = g_mediaPending;
        ReleaseSRWLockShared(&g_mediaLock);
        if (previousSource != g_mediaCurrent.sourceId ||
            previousSelection != g_mediaCurrent.selectionSerial) {
            g_mediaSeeking = false;
            g_mediaSeekHoldUntil = 0;
            g_mediaFeedbackIndex = -1;
        }
        g_mediaLastRefreshTick = GetTickCount64();
        if (!g_mediaSeeking && g_mediaSeekHoldUntil &&
            g_mediaCurrent.hasTimeline &&
            std::llabs(g_mediaCurrent.timelinePosition -
                       g_mediaPreviewPosition) < 15000000LL)
            g_mediaSeekHoldUntil = 0;
        UpdateMediaArtworkCache();
        if (g_panelMode == PanelMode::Media && g_panelWnd &&
            IsWindowVisible(g_panelWnd)) RenderPanel();
        if (g_popupKind == PopupKind::NativeVolume &&
            g_popupWnd && IsWindowVisible(g_popupWnd))
            ShowVolumePanelIfReady();
        return 0;
    }
    if (msg == kLockToggleMessage && hwnd == g_receiveWnd) {
        int index = static_cast<int>(wp);
        if (index < 0 || index >= 4 || !g_showLockKeys[index].load()) return 0;
        ClosePanel();
        g_lastLock = index;
        g_lastLockValue = lp != 0;
        g_popupKind = PopupKind::LockStatus;
        BrightnessEvent ev{};
        MovePopupToDisplay(ev);
        if (g_xamlForMigrated.load()) {
            ShowMigratedXamlLockStatus();
        } else {
            SetPopupInteractive(false);
            ShowPopupAnimated();
            UpdateArrowHitWindow();
            ResetHideTimerFor(DurationKind::LockKeys);
        }
        return 0;
    }
    if (msg == kBrightnessWheelResultMessage && hwnd == g_receiveWnd) {
        const DWORD generation = static_cast<DWORD>(wp);
        const bool success = (lp & 1) != 0;
        const bool native = (lp & 2) != 0;
        if (!native && g_xamlForMigrated.load()) {
            const auto pending = std::find_if(
                g_xamlPendingDdcWrites.begin(),
                g_xamlPendingDdcWrites.end(),
                [generation](const XamlPendingDdcWrite& item) {
                    return item.generation == generation;
                });
            if (pending == g_xamlPendingDdcWrites.end())
                return 0; // Superseded DDC write: never roll back its target.
            const XamlPendingDdcWrite write = *pending;
            g_xamlPendingDdcWrites.erase(pending);
            const auto target = std::find_if(
                g_ddcTargets.begin(), g_ddcTargets.end(),
                [&](const DdcTargetState& item) {
                    return item.event.physicalIndex ==
                            write.event.physicalIndex &&
                        _wcsicmp(item.event.device,
                                write.event.device) == 0;
                });
            const bool master = g_visible.physicalIndex ==
                    write.event.physicalIndex &&
                _wcsicmp(g_visible.device, write.event.device) == 0;
            if (!success) {
                if (target != g_ddcTargets.end())
                    target->event.value = write.previousValue;
                if (master) g_visible.value = write.previousValue;
                Wh_Log(L"XAML v1.0.24: DDC write failed for '%s' index %lu",
                    write.event.device, write.event.physicalIndex);
                if (g_popupKind == PopupKind::DdcBrightness)
                    (void)ShowXamlDdcTargets(g_visible);
            } else if (master && target != g_ddcTargets.end()) {
                g_lastConfirmedDdcBrightness = target->event.value;
            }
            return 0;
        }
        if (generation != g_wheelWriteGeneration) return 0;
        if (native) {
            if (success) g_lastConfirmedNativeBrightness = g_nativePercent;
            else if (g_lastConfirmedNativeBrightness >= 0) {
                g_nativePercent = g_lastConfirmedNativeBrightness;
                if (g_xamlForMigrated.load() &&
                    g_popupKind == PopupKind::NativeBrightness)
                    ShowMigratedXamlLevel(PopupKind::NativeBrightness);
                else RenderPopup();
                Wh_Log(L"Native brightness wheel write failed; restored value");
            }
        } else if (!g_xamlForMigrated.load()) {
            if (success) g_lastConfirmedDdcBrightness = g_visible.value;
            else {
                g_visible.value = g_lastConfirmedDdcBrightness;
                RenderPopup();
                Wh_Log(L"DDC brightness wheel write failed; restored value");
            }
        }
        return 0;
    }
    if (msg == WM_COPYDATA && hwnd == g_receiveWnd) {
        auto* cds = reinterpret_cast<const COPYDATASTRUCT*>(lp);
        if (!cds || cds->dwData != kCopyDataTag ||
            cds->cbData != sizeof(BrightnessEvent) || !cds->lpData)
            return FALSE;
        BrightnessEvent ev{};
        memcpy(&ev, cds->lpData, sizeof(ev));
        if (ev.magic != kEventMagic) return FALSE;
        bool terminator = false;
        for (WCHAR ch : ev.device) {
            if (!ch) { terminator = true; break; }
        }
        if (!terminator || g_closing.load()) return FALSE;
        // DDC/CI VCP values are 16-bit. Reject malformed cross-process
        // notices before their values can influence slider geometry.
        if (ev.physicalIndex >= 32 ||
            ev.value > kMaxVcpValue || ev.minimum > kMaxVcpValue ||
            ev.maximum > kMaxVcpValue ||
            (ev.maximum == 0 && ev.minimum != 0) ||
            (ev.maximum != 0 && (ev.maximum <= ev.minimum ||
                                  ev.value < ev.minimum || ev.value > ev.maximum)))
            return FALSE;
        // producerPid is descriptive metadata, not sender authentication.
        if (!g_showDdcBrightness.load()) return TRUE;
        const bool firstInBatch = !g_ddcBatchPending;
        // Keep one latest write per GDI target and physical index. Updates
        // for display 1 must never overwrite display 2's brightness value.
        auto sameTarget = [&](const BrightnessEvent& existing) {
            return existing.physicalIndex == ev.physicalIndex &&
                   _wcsicmp(existing.device, ev.device) == 0;
        };
        auto same = std::find_if(g_ddcBatchEvents.begin(),
                                 g_ddcBatchEvents.end(), sameTarget);
        if (same != g_ddcBatchEvents.end()) {
            // Move a refreshed target to the end so the order reflects
            // real writes: DISPLAY1 -> DISPLAY2 -> DISPLAY1 ends on DISPLAY1.
            g_ddcBatchEvents.erase(same);
            g_ddcBatchEvents.push_back(ev);
        } else if (g_ddcBatchEvents.size() < kMaxDdcTargets) {
            g_ddcBatchEvents.push_back(ev);
        }
        if (g_ddcBatchEvents.empty()) return TRUE;
        g_ddcBatchPending = true;
        if (firstInBatch &&
            !SetTimer(g_receiveWnd, kDdcBatchTimer, kDdcBatchDelayMs, nullptr))
            DisplayDdcBatch(); // Timer allocation failure must not lose updates.
        return TRUE;
    }
    if (msg == WM_TIMER && hwnd == g_popupWnd && wp == kHideTimer) {
        if (g_mixerDrag || g_mainBarDragging || g_mixerOutputExpanded) return 0;
        KillTimer(hwnd, kHideTimer);
        BeginFade(true);
        return 0;
    }
    if (msg == WM_TIMER && hwnd == g_popupWnd &&
        wp == kMediaAnimationTimer) {
        if (g_panelMode != PanelMode::Media || !g_panelWnd ||
            !IsWindowVisible(g_panelWnd)) {
            KillTimer(hwnd, kMediaAnimationTimer);
            return 0;
        }
        const ULONGLONG now = GetTickCount64();
        const bool feedbackActive = g_mediaFeedbackIndex >= 0 &&
            now >= g_mediaFeedbackTick &&
            now - g_mediaFeedbackTick < kMediaFeedbackMs;
        if (!feedbackActive) g_mediaFeedbackIndex = -1;
        const bool seekPreviewExpired = g_mediaSeekHoldUntil &&
            now >= g_mediaSeekHoldUntil;
        if (seekPreviewExpired) g_mediaSeekHoldUntil = 0;
        if ((g_mediaCurrent.hasTimeline && g_mediaCurrent.playing) ||
            feedbackActive || g_mediaPressedIndex >= 0 || g_mediaSeeking ||
            g_mediaSeekHoldUntil || seekPreviewExpired)
            RenderPanel();
        // Refresh the SMTC snapshot only while its card is open. No
        // always-on media polling and no WinRT call on the UI thread.
        if (now - g_mediaLastRefreshTick >= kMediaRefreshIntervalMs) {
            g_mediaLastRefreshTick = now;
            RequestMedia();
        }
        return 0;
    }
    if (msg == WM_TIMER && hwnd == g_popupWnd && wp == kFadeTimer) {
        if (!g_fadeActive) { KillTimer(hwnd, kFadeTimer); return 0; }
        const DWORD elapsed = GetTickCount() - g_fadeStart;
        const DWORD duration = static_cast<DWORD>(g_fadeDuration.load());
        const float amount = std::min(1.0f,
            static_cast<float>(elapsed) / std::max<DWORD>(duration, 1));
        const float eased = amount * amount * (3.0f - 2.0f * amount);
        g_fadeAlpha = std::clamp(static_cast<int>(std::lround(
            g_fadeFrom + (g_fadeTo - g_fadeFrom) * eased)), 0, 255);
        if (amount >= 1.0f) {
            g_fadeActive = false;
            KillTimer(hwnd, kFadeTimer);
            if (g_fadeOut) { FinishPopupHide(); return 0; }
        }
        RenderPopup();
        if (g_panelMode != PanelMode::None) RenderPanel();
        return 0;
    }
    // An interactive control should not vanish beneath a stationary
    // pointer. WM_MOUSELEAVE re-arms its category's selected duration.
    // This is event-driven; it adds no polling timer.
    const bool hoverSurface = hwnd == g_panelWnd || hwnd == g_arrowWnd ||
        hwnd == g_barWheelWnd || hwnd == g_speakerHitWnd ||
        (hwnd == g_popupWnd && g_popupKind == PopupKind::Notification &&
         g_noticeClickable);
    if (msg == WM_MOUSEMOVE && hoverSurface) {
        TRACKMOUSEEVENT tracking{sizeof(tracking), TME_LEAVE, hwnd, 0};
        TrackMouseEvent(&tracking);
        if (g_popupWnd) KillTimer(g_popupWnd, kHideTimer);
        if (hwnd == g_arrowWnd && !g_arrowHovered) {
            g_arrowHovered = true;
            RenderPopup();
        }
    }
    if (msg == WM_MOUSELEAVE && hoverSurface) {
        if (hwnd == g_panelWnd && g_panelMode == PanelMode::Mixer) {
            const bool changed = g_mixerOutputExpanded ||
                g_mixerOutputHoveredRow >= 0 || g_mixerOutputHeaderHovered;
            g_mixerOutputExpanded = false;
            g_mixerOutputHoveredRow = -1;
            g_mixerOutputHeaderHovered = false;
            if (changed) RenderPanel();
        }
        if (hwnd == g_arrowWnd && g_arrowHovered) {
            g_arrowHovered = false;
            if (!g_arrowPressed) RenderPopup();
        }
        if (!g_mainBarDragging && g_popupWnd && IsWindowVisible(g_popupWnd))
            ResetHideTimerFor(g_activeDurationKind);
        return 0;
    }
    if (msg == WM_MOUSEMOVE && hwnd == g_panelWnd &&
        g_panelMode == PanelMode::Mixer && !g_mixerDrag && g_scale > 0.0f) {
        const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
        const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
        if (UpdateMixerOutputHover(x, y))
            RenderPanel(); // Only on hover transition; no per-pixel repaint.
    }
    if (msg == WM_NCHITTEST) {
        if (hwnd == g_popupWnd) return g_popupKind == PopupKind::Notification && g_noticeClickable ? HTCLIENT : HTTRANSPARENT;
        if (hwnd == g_panelWnd || hwnd == g_arrowWnd ||
            hwnd == g_barWheelWnd || hwnd == g_speakerHitWnd) return HTCLIENT;
    }
    if (msg == WM_SETCURSOR && hwnd == g_popupWnd &&
        g_popupKind == PopupKind::Notification && g_noticeClickable) {
        SetCursor(LoadCursorW(nullptr, IDC_HAND));
        return TRUE;
    }
    if (msg == WM_SETCURSOR &&
        (hwnd == g_panelWnd || hwnd == g_arrowWnd ||
         hwnd == g_barWheelWnd || hwnd == g_speakerHitWnd)) {
        bool overClickableIcon = hwnd == g_arrowWnd ||
            hwnd == g_barWheelWnd || hwnd == g_speakerHitWnd;
        if (hwnd == g_panelWnd && g_scale > 0) {
            POINT point{};
            if (GetCursorPos(&point) && ScreenToClient(hwnd, &point)) {
                const float x = point.x / g_scale, y = point.y / g_scale;
                if (g_panelMode == PanelMode::Mixer)
                    overClickableIcon = MixerOutputHeaderHit(x, y) ||
                        MixerOutputRowHit(x, y) >= 0 ||
                        (!g_mixerOutputExpanded && MixerIconHitTest(x, y) >= 0);
                else if (g_panelMode == PanelMode::Media)
                    overClickableIcon = MediaCycleHitTest(x, y) ||
                        MediaButtonHitTest(x, y) >= 0 ||
                        MediaTimelineHitTest(x, y) ||
                        MediaExtraHitTest(x, y) != 0;
            }
        }
        SetCursor(LoadCursorW(nullptr,
            overClickableIcon ? IDC_HAND : IDC_ARROW));
        return TRUE;
    }
    if (msg == WM_MOUSEACTIVATE &&
        (hwnd == g_popupWnd || hwnd == g_panelWnd ||
         hwnd == g_arrowWnd || hwnd == g_barWheelWnd ||
         hwnd == g_speakerHitWnd))
        return MA_NOACTIVATE;
    if (msg == WM_LBUTTONUP && hwnd == g_popupWnd &&
        g_popupKind == PopupKind::Notification && g_noticeClickable) {
        if (g_panelMode == PanelMode::Details) ClosePanel();
        else { g_panelMode = PanelMode::Details; g_noticeScroll = 0; ShowPanel(); }
        ResetHideTimerFor(DurationKind::Interactive);
        return 0;
    }
    if (hwnd == g_speakerHitWnd) {
        if (msg == WM_LBUTTONDOWN) {
            if (g_popupKind == PopupKind::NativeVolume && g_popupWnd &&
                IsWindowVisible(g_popupWnd) && !g_closing.load()) {
                g_speakerPressed = true;
                SetCapture(hwnd);
                KillTimer(g_popupWnd, kHideTimer);
            }
            return 0;
        }
        if (msg == WM_LBUTTONUP) {
            RECT area{};
            GetClientRect(hwnd, &area);
            const POINT pointer{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            const bool activate = g_speakerPressed &&
                g_popupKind == PopupKind::NativeVolume &&
                !g_closing.load() && PtInRect(&area, pointer);
            g_speakerPressed = false;
            if (GetCapture() == hwnd) ReleaseCapture();
            if (activate) ToggleDefaultAudioMute();
            else if (g_popupWnd && IsWindowVisible(g_popupWnd))
                ResetHideTimerFor(g_activeDurationKind);
            return 0;
        }
        if (msg == WM_CAPTURECHANGED || msg == WM_CANCELMODE) {
            g_speakerPressed = false;
            if (g_popupWnd && IsWindowVisible(g_popupWnd))
                ResetHideTimerFor(g_activeDurationKind);
            return 0;
        }
    }
    if (msg == WM_MOUSEWHEEL && hwnd == g_barWheelWnd) {
        HandleMainBarWheel(GET_WHEEL_DELTA_WPARAM(wp));
        return 0;
    }
    if (hwnd == g_barWheelWnd) {
        if (msg == WM_LBUTTONDOWN) {
            MainBarRect track{};
            if (MainBarTrackGeometry(track) && g_scale > 0.0f) {
                g_mainBarDragging = true;
                g_mainBarDragKind = static_cast<int>(g_popupKind);
                SetCapture(hwnd);
                if (g_popupWnd) KillTimer(g_popupWnd, kHideTimer);
                SetMainBarFromPointer(hwnd, lp); // Click-to-position.
            }
            return 0;
        }
        if (msg == WM_MOUSEMOVE && g_mainBarDragging) {
            if (g_mainBarDragKind == static_cast<int>(g_popupKind))
                SetMainBarFromPointer(hwnd, lp);
            return 0;
        }
        if (msg == WM_LBUTTONUP) {
            if (g_mainBarDragging &&
                g_mainBarDragKind == static_cast<int>(g_popupKind))
                SetMainBarFromPointer(hwnd, lp);
            g_mainBarDragging = false;
            g_mainBarDragKind = -1;
            if (GetCapture() == hwnd) ReleaseCapture();
            if (g_popupWnd && IsWindowVisible(g_popupWnd))
                ResetHideTimerFor(g_activeDurationKind);
            return 0;
        }
        if (msg == WM_CAPTURECHANGED || msg == WM_CANCELMODE) {
            if (g_mainBarDragging) {
                g_mainBarDragging = false;
                g_mainBarDragKind = -1;
                if (g_popupWnd && IsWindowVisible(g_popupWnd))
                    ResetHideTimerFor(g_activeDurationKind);
            }
            return 0;
        }
    }
    if (hwnd == g_arrowWnd) {
        if (msg == WM_LBUTTONDOWN) {
            if (g_popupKind == PopupKind::NativeVolume &&
                g_showMixerArrow.load()) {
                g_arrowPressed = true;
                SetCapture(hwnd);
                RenderPopup();
            }
            return 0;
        }
        if (msg == WM_LBUTTONUP) {
            const bool activate = g_arrowPressed &&
                g_popupKind == PopupKind::NativeVolume &&
                g_showMixerArrow.load();
            RECT area{};
            GetClientRect(hwnd, &area);
            POINT pointer{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            const bool inside = PtInRect(&area, pointer) != FALSE;
            g_arrowPressed = false;
            if (GetCapture() == hwnd) ReleaseCapture();
            if (activate && inside) ActivateMixer();
            else RenderPopup();
            return 0;
        }
        if (msg == WM_CAPTURECHANGED || msg == WM_CANCELMODE) {
            if (g_arrowPressed) {
                g_arrowPressed = false;
                RenderPopup();
            }
            return 0;
        }
    }
    if (hwnd == g_panelWnd && g_panelMode == PanelMode::Media) {
        if (msg == WM_LBUTTONDOWN) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
            if (MediaCycleHitTest(x, y)) {
                g_mediaCyclePressed = true;
                g_mediaCycleInside = true;
                SetCapture(hwnd);
                RenderPanel();
                return 0;
            }
            if (MediaTimelineHitTest(x, y)) {
                g_mediaSeeking = true;
                g_mediaSeekHoldUntil = 0;
                SetCapture(hwnd);
                PreviewMediaSeek(x);
                return 0;
            }
            g_extraPressedAction = MediaExtraHitTest(x, y);
            g_extraPressedInside = g_extraPressedAction != 0;
            if (g_extraPressedAction) {
                SetCapture(hwnd);
                RenderPanel();
                return 0;
            }
            g_mediaPressedIndex = MediaButtonHitTest(x, y);
            g_mediaPressedInside = g_mediaPressedIndex >= 0;
            if (g_mediaPressedIndex >= 0) {
                SetCapture(hwnd);
                RenderPanel();
            }
            return 0;
        }
        if (msg == WM_MOUSEMOVE && g_mediaCyclePressed) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
            const bool inside = MediaCycleHitTest(x, y);
            if (inside != g_mediaCycleInside) {
                g_mediaCycleInside = inside;
                RenderPanel();
            }
            return 0;
        }
        if (msg == WM_MOUSEMOVE && g_mediaSeeking) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            PreviewMediaSeek(x);
            return 0;
        }
        if (msg == WM_MOUSEMOVE && g_extraPressedAction) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
            const bool inside = MediaExtraHitTest(x, y) == g_extraPressedAction;
            if (inside != g_extraPressedInside) {
                g_extraPressedInside = inside;
                RenderPanel();
            }
            return 0;
        }
        if (msg == WM_MOUSEMOVE && g_mediaPressedIndex >= 0) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
            const bool inside = MediaButtonHitTest(x, y) == g_mediaPressedIndex;
            if (inside != g_mediaPressedInside) {
                g_mediaPressedInside = inside;
                RenderPanel();
            }
            return 0;
        }
        if (msg == WM_LBUTTONUP) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
            if (g_mediaCyclePressed) {
                const bool activated = MediaCycleHitTest(x, y);
                g_mediaCyclePressed = false;
                g_mediaCycleInside = false;
                if (GetCapture() == hwnd) ReleaseCapture();
                if (activated) RequestMedia(7);
                RenderPanel();
                ResetHideTimerFor(DurationKind::Interactive);
                return 0;
            }
            if (g_mediaSeeking) {
                PreviewMediaSeek(x);
                g_mediaSeeking = false;
                g_mediaSeekHoldUntil = GetTickCount64() + 2000;
                if (GetCapture() == hwnd) ReleaseCapture();
                RequestMedia(4, g_mediaPreviewPosition);
                RenderPanel();
                ResetHideTimerFor(DurationKind::Interactive);
                return 0;
            }
            if (g_extraPressedAction) {
                const int action = g_extraPressedAction;
                const bool activated = MediaExtraHitTest(x, y) == action;
                g_extraPressedAction = 0;
                g_extraPressedInside = false;
                if (GetCapture() == hwnd) ReleaseCapture();
                if (activated) {
                    g_mediaFeedbackIndex = action - 2; // 3=shuffle, 4=repeat
                    g_mediaFeedbackTick = GetTickCount64();
                    RequestMedia(action);
                }
                RenderPanel();
                ResetHideTimerFor(DurationKind::Interactive);
                return 0;
            }
            const int pressed = g_mediaPressedIndex;
            const bool activated = pressed >= 0 &&
                MediaButtonHitTest(x, y) == pressed;
            g_mediaPressedIndex = -1;
            g_mediaPressedInside = false;
            if (GetCapture() == hwnd) ReleaseCapture();
            if (activated) {
                g_mediaFeedbackIndex = pressed;
                g_mediaFeedbackTick = GetTickCount64();
                RequestMedia(pressed + 1);
            }
            RenderPanel();
            ResetHideTimerFor(DurationKind::Interactive);
            return 0;
        }
    }
    if (msg == WM_LBUTTONDOWN && hwnd == g_panelWnd &&
        g_panelMode == PanelMode::Mixer) {
        float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
        float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
        if (MixerOutputHeaderHit(x, y)) {
            if (!g_mixerOutputExpanded) {
                RefreshMixer(); // snapshot current devices before showing list
                g_mixerOutputScroll = 0;
                g_mixerOutputSwitchFailed = false;
            }
            g_mixerOutputExpanded = !g_mixerOutputExpanded &&
                MixerOutputRows() > 0;
            g_mixerOutputHoveredRow = -1;
            RenderPanel();
            ResetHideTimerFor(DurationKind::Interactive);
            return 0;
        }
        if (g_mixerOutputExpanded) {
            const int selection = MixerOutputRowHit(x, y);
            if (selection >= 0) SelectMixerOutput(selection);
            else {
                g_mixerOutputExpanded = false;
                RenderPanel();
                ResetHideTimerFor(DurationKind::Interactive);
            }
            return 0; // never pass a menu click through to a volume slider
        }
        const int muteIndex = MixerIconHitTest(x, y);
        if (muteIndex >= 0) {
            g_mixerMutePressedIndex = muteIndex;
            SetCapture(hwnd);
            return 0;
        }
        int row = static_cast<int>(std::floor((y - kMixerFirstRowY + 10.0f) / kMixerRowStep));
        int index = row + g_mixerScroll;
        if (x >= kMixerTrackStart - 3.0f &&
            x <= kMixerTrackStart + MixerTrackLength() + 3.0f &&
            row >= 0 &&
            row < MixerVisibleRows() && index >= 0 &&
            index <= static_cast<int>(g_mixerEntries.size())) {
            g_mixerDragIndex = index;
            g_mixerDrag = true;
            SetCapture(hwnd);
            HandleMixerDrag(lp);
        }
        return 0;
    }
    if (msg == WM_CAPTURECHANGED && hwnd == g_panelWnd) {
        if (g_mediaSeeking) {
            g_mediaSeeking = false;
            g_mediaSeekHoldUntil = 0;
            if (g_panelMode == PanelMode::Media) RenderPanel();
        }
        if (g_mediaPressedIndex >= 0 || g_extraPressedAction ||
            g_mediaCyclePressed) {
            g_mediaPressedIndex = -1;
            g_mediaPressedInside = false;
            g_mediaCyclePressed = false;
            g_mediaCycleInside = false;
            g_extraPressedAction = 0;
            g_extraPressedInside = false;
            if (g_panelMode == PanelMode::Media) RenderPanel();
        }
        g_mixerMutePressedIndex = -1;
        g_mixerDrag = false;
        g_mixerDragIndex = -1;
        return 0;
    }
    if (msg == WM_MOUSEMOVE && hwnd == g_panelWnd &&
        g_panelMode == PanelMode::Mixer && g_mixerDrag) {
        HandleMixerDrag(lp);
        return 0;
    }
    if (msg == WM_LBUTTONUP && hwnd == g_panelWnd &&
        g_panelMode == PanelMode::Mixer) {
        if (g_mixerMutePressedIndex >= 0) {
            const int pressed = g_mixerMutePressedIndex;
            g_mixerMutePressedIndex = -1;
            if (GetCapture() == hwnd) ReleaseCapture();
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            const float y = static_cast<float>(GET_Y_LPARAM(lp)) / g_scale;
            if (MixerIconHitTest(x, y) == pressed)
                ToggleMixerMute(pressed);
            return 0;
        }
        if (g_mixerDrag) {
            HandleMixerDrag(lp);
            g_mixerDrag = false;
            g_mixerDragIndex = -1;
            ReleaseCapture();
        }
        ResetHideTimerFor(DurationKind::Interactive);
        return 0;
    }
    if (msg == WM_MOUSEWHEEL && hwnd == g_panelWnd &&
        g_panelMode == PanelMode::Details) {
        const int d = GET_WHEEL_DELTA_WPARAM(wp);
        const int maxScroll = std::max<int>(0, static_cast<int>(g_noticeDetails.size()) - NoticeVisibleRows());
        g_noticeScroll = std::clamp(g_noticeScroll + (d > 0 ? -1 : 1), 0, maxScroll);
        RenderPanel();
        ResetHideTimerFor(DurationKind::Interactive);
        return 0;
    }
    if (msg == WM_MOUSEWHEEL && hwnd == g_panelWnd &&
        g_panelMode == PanelMode::Mixer) {
        if (g_mixerOutputExpanded) {
            const int rows = MixerOutputRows();
            const int maxScroll = std::max(0,
                static_cast<int>(g_mixerOutputOptions.size()) - rows);
            if (maxScroll && GET_WHEEL_DELTA_WPARAM(wp)) {
                g_mixerOutputScroll = std::clamp(g_mixerOutputScroll +
                    (GET_WHEEL_DELTA_WPARAM(wp) > 0 ? -1 : 1), 0, maxScroll);
                POINT cursor{};
                if (g_scale > 0.0f && GetCursorPos(&cursor) &&
                    ScreenToClient(hwnd, &cursor))
                    UpdateMixerOutputHover(cursor.x / g_scale,
                                           cursor.y / g_scale);
                else
                    g_mixerOutputHoveredRow = -1;
                RenderPanel();
            }
            ResetHideTimerFor(DurationKind::Interactive);
            return 0;
        }
        POINT cursor{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
        if (ScreenToClient(hwnd, &cursor) && g_scale > 0.0f) {
            const int index = MixerTrackHitTest(cursor.x / g_scale,
                                                 cursor.y / g_scale);
            if (index >= 0 && !g_mixerDrag) {
                if (index != g_mixerWheelIndex) {
                    g_mixerWheelIndex = index;
                    g_mixerWheelRemainder = 0;
                }
                g_mixerWheelRemainder += GET_WHEEL_DELTA_WPARAM(wp);
                const int steps = g_mixerWheelRemainder / WHEEL_DELTA;
                g_mixerWheelRemainder %= WHEEL_DELTA;
                AdjustMixerVolumeWheel(index, steps);
                return 0;
            }
        }
        g_mixerWheelIndex = -1;
        g_mixerWheelRemainder = 0;
        const int delta = GET_WHEEL_DELTA_WPARAM(wp);
        if (delta) {
            const int maxScroll = MixerMaximumScroll();
            g_mixerScroll = std::clamp(g_mixerScroll + (delta > 0 ? -1 : 1),
                                       0, maxScroll);
            RenderPanel();
            ResetHideTimerFor(DurationKind::Interactive);
        }
        return 0;
    }
    if (msg == WM_ERASEBKGND) return TRUE;
    return DefWindowProcW(hwnd, msg, wp, lp);
}

DWORD WINAPI UiThreadProc(void*) {
    // A dedicated message loop avoids performing UI work on Explorer's shell
    // thread. It performs no DDC/CI calls and no periodic brightness reads.
    // Keep the GDI+ helper window on this dedicated, pumping UI thread.
    // The default GDI+ background thread may own a helper window whose
    // unresponsive shutdown message is reported as "GDI+ Window".
    Gdiplus::GdiplusStartupInput gdiplusInput;
    gdiplusInput.SuppressBackgroundThread = TRUE;
    Gdiplus::GdiplusStartupOutput gdiplusOutput{};
    if (Gdiplus::GdiplusStartup(&g_gdiplusToken, &gdiplusInput,
                                &gdiplusOutput) != Gdiplus::Ok) {
        Wh_Log(L"GDI+ startup failed");
        if (g_uiReady) SetEvent(g_uiReady);
        return 0;
    }
    const HRESULT coInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    const bool coInitialized = SUCCEEDED(coInit);
    InitWindowsAccentProvider();
    ULONG_PTR gdiplusHookToken = 0;
    const bool gdiplusHooked = gdiplusOutput.NotificationHook &&
        gdiplusOutput.NotificationUnhook &&
        gdiplusOutput.NotificationHook(&gdiplusHookToken) == Gdiplus::Ok;
    if (!gdiplusHooked) {
        Wh_Log(L"GDI+ notification hook failed; not creating OSD windows");
        ReleaseWindowsAccentProvider();
        if (coInitialized) CoUninitialize();
        Gdiplus::GdiplusShutdown(g_gdiplusToken);
        g_gdiplusToken = 0;
        if (g_uiReady) SetEvent(g_uiReady);
        return 0;
    }
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = UiWndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kWindowClass;
    // Ensure the queue exists before the unload callback posts WM_QUIT.
    MSG dummy{};
    PeekMessageW(&dummy, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"OSD window class registration failed: %lu", GetLastError());
        if (g_uiReady) SetEvent(g_uiReady);
        // The notification hook must be removed on the same UI thread.
        gdiplusOutput.NotificationUnhook(gdiplusHookToken);
        Gdiplus::GdiplusShutdown(g_gdiplusToken);
        g_gdiplusToken = 0;
        ReleaseWindowsAccentProvider();
        if (coInitialized) CoUninitialize();
        return 0;
    }
    g_receiveWnd = CreateWindowExW(0, kWindowClass, L"", 0,
                                    0, 0, 0, 0, HWND_MESSAGE, nullptr,
                                    wc.hInstance, nullptr);
    if (g_receiveWnd) {
        g_networkReceiver.store(g_receiveWnd);
        g_clipboardListener = AddClipboardFormatListener(g_receiveWnd) != FALSE;
        InitDeviceEvents();
        InitNetworkEvents();
    }
    g_popupWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE |
            WS_EX_LAYERED | WS_EX_TRANSPARENT,
        kWindowClass, L"", WS_POPUP, 0, 0, g_width, g_height,
        nullptr, nullptr, wc.hInstance, nullptr);
    g_panelWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
        kWindowClass, L"", WS_POPUP, 0, 0, 340, 144,
        nullptr, nullptr, wc.hInstance, nullptr);
    g_arrowWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
        kWindowClass, L"", WS_POPUP, 0, 0, 26, 26,
        nullptr, nullptr, wc.hInstance, nullptr);
    if (g_arrowWnd)
        SetLayeredWindowAttributes(g_arrowWnd, 0, 1, LWA_ALPHA);
    g_speakerHitWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
        kWindowClass, L"", WS_POPUP, 0, 0, 32, 32,
        nullptr, nullptr, wc.hInstance, nullptr);
    if (g_speakerHitWnd)
        SetLayeredWindowAttributes(g_speakerHitWnd, 0, 1, LWA_ALPHA);
    g_barWheelWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
        kWindowClass, L"", WS_POPUP, 0, 0, 32, 32,
        nullptr, nullptr, wc.hInstance, nullptr);
    if (g_barWheelWnd)
        SetLayeredWindowAttributes(g_barWheelWnd, 0, 1, LWA_ALPHA);
    for (int i = 0; i < 4; ++i)
        g_lockToggle[i] = (GetKeyState(kLockVk[i]) & 1) != 0;
    HMODULE mod = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                       GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<PCWSTR>(reinterpret_cast<void*>(LockKeyProc)),
                       &mod);
    g_lockHook = SetWindowsHookExW(WH_KEYBOARD_LL, LockKeyProc, mod, 0);
    if (!g_lockHook) Wh_Log(L"Lock-key keyboard hook unavailable: %lu", GetLastError());
    if (!g_receiveWnd || !g_popupWnd)
        Wh_Log(L"OSD window creation failed: %lu", GetLastError());
    if (g_uiReady) SetEvent(g_uiReady);
    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    g_closing.store(true);
    g_networkReceiver.store(nullptr);
    if (g_clipboardListener) RemoveClipboardFormatListener(g_receiveWnd);
    g_clipboardListener = false;
    if (g_receiveWnd) {
        KillTimer(g_receiveWnd, kEventBatchTimer);
        KillTimer(g_receiveWnd, kDdcBatchTimer);
    }
    g_ddcBatchPending = false;
    g_ddcBatchEvents.clear();
    g_ddcTargets.clear();
    g_noticeBatch = NoticeBatch{};
    g_usbNames.clear();
    g_networkInterfaces.clear();
    StopDeviceEvents();
    ClearClipboardThumbnail();
    if (g_popupWnd) {
        KillTimer(g_popupWnd, kHideTimer);
        KillTimer(g_popupWnd, kFadeTimer);
        KillTimer(g_popupWnd, kMediaAnimationTimer);
    }
    if (g_lockHook) { UnhookWindowsHookEx(g_lockHook); g_lockHook = nullptr; }
    ClosePanel();
    ClearMediaArtworkCache();  // Must precede GDI+ shutdown.
    DestroyMirroredWindows();
    if (g_speakerHitWnd) DestroyWindow(g_speakerHitWnd);
    if (g_barWheelWnd) DestroyWindow(g_barWheelWnd);
    if (g_arrowWnd) DestroyWindow(g_arrowWnd);
    if (g_panelWnd) DestroyWindow(g_panelWnd);
    if (g_popupWnd) DestroyWindow(g_popupWnd);
    if (g_receiveWnd) DestroyWindow(g_receiveWnd);
    g_speakerHitWnd = nullptr;
    g_speakerPressed = false;
    g_barWheelWnd = nullptr;
    g_arrowWnd = nullptr;
    g_panelWnd = nullptr;
    g_popupWnd = nullptr;
    g_receiveWnd = nullptr;
    UnregisterClassW(kWindowClass, wc.hInstance);
    // Unhook only after the message loop exits and all UI artwork is freed.
    gdiplusOutput.NotificationUnhook(gdiplusHookToken);
    Gdiplus::GdiplusShutdown(g_gdiplusToken);
    g_gdiplusToken = 0;
    ReleaseWindowsAccentProvider();
    if (coInitialized) CoUninitialize();
    return 0;
}

} // namespace

// ============================================================
// Windhawk module entrypoints and shutdown lifecycle
// ============================================================
BOOL Wh_ModInit() {
    WCHAR exe[MAX_PATH]{};
    if (!GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe))) return FALSE;
    PCWSTR name = wcsrchr(exe, L'\\');
    name = name ? name + 1 : exe;
    g_isExplorer = _wcsicmp(name, L"explorer.exe") == 0;
    const bool isTwinkle = _wcsicmp(name, L"Twinkle Tray.exe") == 0;
    if (!g_isExplorer && !isTwinkle) return FALSE;
    LoadSettings();
    if (g_isExplorer) HookNativeOsd();
    HookDdc();
    Wh_Log(L"Fluent OSD v1.0.24 (XAML experimental, no fallback) initialized (%s)", name);
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isExplorer) return;
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_uiReady) {
        Wh_Log(L"Cannot create UI ready event: %lu", GetLastError());
        return;
    }
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0,
                              &g_uiThreadId);
    if (!g_uiThread) {
        Wh_Log(L"Cannot start OSD UI thread: %lu", GetLastError());
        CloseHandle(g_uiReady);
        g_uiReady = nullptr;
        return;
    }
    if (WaitForSingleObject(g_uiReady, 1500) != WAIT_OBJECT_0)
        Wh_Log(L"OSD UI initialization did not signal readiness");
    g_wheelWriteStop.store(false);
    g_wheelWriteWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (g_wheelWriteWake) {
        g_wheelWriteThread = CreateThread(nullptr, 0,
            BrightnessWheelThreadProc, nullptr, 0, nullptr);
        if (!g_wheelWriteThread) {
            CloseHandle(g_wheelWriteWake);
            g_wheelWriteWake = nullptr;
        }
    }
    g_mediaStop.store(false);
    g_mediaWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (g_mediaWake) {
        g_mediaThread = CreateThread(nullptr, 0, MediaThreadProc, nullptr,
                                    0, nullptr);
        if (!g_mediaThread) {
            CloseHandle(g_mediaWake);
            g_mediaWake = nullptr;
        }
    }
    if (g_xamlForMigrated.load())
        xaml_osd::Start();
}

void Wh_ModSettingsChanged() {
    LoadSettings();
    if (g_isExplorer && !g_closing.load()) {
        if (g_xamlForMigrated.load())
            xaml_osd::Start();
        else
            xaml_osd::Hide();
    }
    // Windhawk's settings callback is not the OSD UI thread.
    HWND target = g_networkReceiver.load(std::memory_order_acquire);
    if (g_isExplorer && target && !g_closing.load())
        (void)PostMessageW(target, kBluetoothConfigMessage, 0, 0);
    // Refresh the next OSD using the newly selected theme. Settings never
    // force an unexpected brightness write or background monitor read.
}

void Wh_ModBeforeUninit() {
    // Prevent callbacks from posting into a receiver that is going away.
    g_closing.store(true);
    g_networkReceiver.store(nullptr);
    // WinRT/XAML is STA-owned and must exit before the module unloads.
    xaml_osd::Stop();
    // Stop all worker threads before the UI windows or DLL can be unloaded.
    g_wheelWriteStop.store(true);
    if (g_wheelWriteWake) SetEvent(g_wheelWriteWake);
    if (g_wheelWriteThread) {
        WaitForSingleObject(g_wheelWriteThread, INFINITE);
        CloseHandle(g_wheelWriteThread);
        g_wheelWriteThread = nullptr;
    }
    if (g_wheelWriteWake) {
        CloseHandle(g_wheelWriteWake);
        g_wheelWriteWake = nullptr;
    }
    g_mediaStop.store(true);
    if (g_mediaWake) SetEvent(g_mediaWake);
    if (g_mediaThread) {
        // Await completion to guarantee there is no executing code in the
        // Windhawk DLL after unload. The WinRT worker is independent of Explorer.
        WaitForSingleObject(g_mediaThread, INFINITE);
        CloseHandle(g_mediaThread);
        g_mediaThread = nullptr;
    }
    if (g_mediaWake) { CloseHandle(g_mediaWake); g_mediaWake = nullptr; }
    if (g_uiThread) {
        // Waiting with a 2.5-second timeout and then unloading could leave
        // this DLL executing on a live UI thread. Join before the unload.
        PostThreadMessageW(g_uiThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_uiThread, INFINITE);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    if (g_uiReady) {
        CloseHandle(g_uiReady);
        g_uiReady = nullptr;
    }
}

void Wh_ModUninit() {
    if (g_confirmatorDll) {
        FreeLibrary(g_confirmatorDll);
        g_confirmatorDll = nullptr;
    }
    if (g_ddcDll) {
        FreeLibrary(g_ddcDll);
        g_ddcDll = nullptr;
    }
}