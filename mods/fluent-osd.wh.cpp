// ==WindhawkMod==
// @id              fluent-osd
// @name            Fluent OSD
// @description     Native XAML on-screen displays for volume, brightness, media, mixer and Windows system events.
// @description:zh-TW 以原生 XAML 顯示音量、亮度、媒體、混音器及 Windows 系統事件提示。
// @version         1.1.5
// @author          Reg Chen
// @github          https://github.com/reg-chen
// @include         explorer.exe
// @include         Twinkle Tray.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshcore -ladvapi32 -lole32 -luuid -lshell32 -lsetupapi -liphlpapi -loleaut32 -lruntimeobject -lwindowsapp -ldwmapi -DWIN32_LEAN_AND_MEAN
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Fluent OSD

Customizable XAML on-screen displays for Windows 11. Choose which native
Windows indicators to hide and which custom OSDs to show.

## Features

- **Volume and brightness:** Horizontal or vertical layouts, interactive
  sliders, mouse-wheel control and optional per-monitor DDC/CI brightness.
- **Media:** Album art, track details, playback controls, timeline,
  shuffle and repeat (subject to media-session support).
- **Audio mixer:** Master and per-app volume/mute controls and playback
  device selection.
- **System events:** Lock keys, keyboard backlight, airplane mode,
  camera, microphone, virtual desktop and other Windows indicators.
- **Notifications:** Clipboard, USB, Bluetooth and network events.
- **Appearance:** Themes, colors, custom background brushes, window
  corner radius, button shapes, sizing, placement, multi-monitor display
  and visibility timing. English and Traditional Chinese are supported.

## Screenshots

Actual Windows 11 captures, cropped to consistent dimensions.

### Volume and mixer

| Horizontal volume + media | Vertical volume + media |
| :---: | :---: |
| ![Horizontal volume + media](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/volume/horizontal_media.png) | ![Vertical volume + media](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/volume/vertical_media.png) |

| Horizontal volume + mixer | Vertical volume + mixer |
| :---: | :---: |
| ![Horizontal volume + mixer](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/volume/horizontal_mixer.png?v=1.1.4-1aca9f1) | ![Vertical volume + mixer](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/volume/vertical_mixer.png?v=1.1.4-1aca9f1) |

### Brightness

| Horizontal brightness | Vertical brightness |
| :---: | :---: |
| ![Horizontal brightness](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/brightness/horizontal.png) | ![Vertical brightness](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/brightness/vertical.png) |

### Clipboard

| Copied image preview | Copied text | Copied files |
| :---: | :---: | :---: |
| ![Copied image preview](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/clipboard/image_preview.png) | ![Copied text](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/clipboard/text.png) | ![Copied files](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/clipboard/files.png) |

### Network

Wi-Fi radio power and connection to a Wi-Fi profile are separate events.
Other network interfaces retain their own connection notices.

| Connected Wi-Fi profile | Disconnected network interface |
| :---: | :---: |
| ![Connected Wi-Fi profile](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/network/wifi_connected.png) | ![Disconnected network interface (name redacted)](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/network/interface_disconnected.png) |

### Bluetooth

| Keyboard connected | Mouse connected |
| :---: | :---: |
| ![Bluetooth keyboard](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/bluetooth/keyboard.png) | ![Bluetooth mouse](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/bluetooth/mouse.png) |

### System

| Caps Lock | Insert |
| :---: | :---: |
| ![Caps Lock](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/system/caps_lock.png) | ![Insert](https://raw.githubusercontent.com/reg-chen/windhawk-mods-assets/main/fluent-osd/screenshots/system/insert.png) |

See the [complete screenshot gallery](https://github.com/reg-chen/windhawk-mods-assets#fluent-osd-screenshots) for all examples.

## Getting started

1. Configure **Windows native OSD — Hide switches** for indicators you
   want to suppress.
2. Enable the corresponding **Custom OSD** switches to display Fluent OSD.
   Hide and Show are independent; custom displays are off by default.
3. Adjust appearance, layout and timing to your preference.

## Custom background brushes

Under **Fluent appearance > Background effect**, choose **Transparency**
for the original solid background, or **Brush layers** for one to five
custom brushes. The same renderer handles a single enabled layer and a
stack of multiple brushes; the separate single-brush setting is removed.
Windhawk's Add item, Remove, and reorder commands manage the layer list.
Each layer accepts one single-line brush definition (without `Fill:=`),
an Enabled flag, and an independent layer opacity (0–100%).
Layers are painted bottom to top. Empty or invalid stacks use solid fallback.
More than one Acrylic or WindhawkBlur can increase GPU memory use.

| Brush | Example |
| --- | --- |
| `SolidColorBrush` | `<SolidColorBrush Color="$mainColor" Opacity="0.8" />` |
| `AcrylicBrush` | `<AcrylicBrush BackgroundSource="Backdrop" TintColor="$mainColor" TintOpacity="0.3" TintLuminosityOpacity="0.6" />` |
| `LinearGradientBrush` | `<LinearGradientBrush StartPoint="0,0" EndPoint="1,1"><GradientStop Color="$mainColor" Offset="0" /><GradientStop Color="#80000000" Offset="1" /></LinearGradientBrush>` |
| `ImageBrush` | `<ImageBrush ImageSource="C:\Pictures\osd.png" Stretch="UniformToFill" Opacity="0.8" />` |
| `WindhawkBlur` | `<WindhawkBlur BlurAmount="18" TintColor="$mainColor" TintOpacity="0.3" NoiseOpacity="0.02" />` |

Supported color values include `#RRGGBB`, `#AARRGGBB`,
`$mainColor`, `$accentColor`, `$textColor`, `$trackColor`, and
a bounded set of named colors (including `Transparent`, `White`,
`Red`, `Yellow`, `Blue` and `LimeGreen`).

- **ImageBrush:** Local absolute paths only, files up to 16 MiB;
  images are decoded to at most 1024 pixels per side. Supports native
  Stretch, AlignmentX and AlignmentY.
- **LinearGradientBrush:** 2–12 gradient stops; bounded coordinates,
  MappingMode, SpreadMethod and ColorInterpolationMode are supported.
  Gradient offsets may extend to 4 as in existing Styler examples.
- **SolidColorBrush:** Native Color and Opacity, unchanged.
- **WindhawkBlur:** Supports tint, opacity, blur and noise options.
- Arbitrary XAML, bindings and unsupported brush attributes are not
  accepted. Invalid definitions fall back to a solid background.
  Arbitrary XAML/XamlReader is not enabled in Explorer.

## Blur brush tips

- Put `AcrylicBrush` or `WindhawkBlur` in the first (bottom) layer.
  Keep its layer opacity at **100%** for the best blur appearance.
- Add gradients, images, or highlights above it and adjust their opacity
  as desired. Change glass color/strength using the brush's own settings.
- Native `AcrylicBrush` supports `BackgroundSource="Backdrop"` only;
  `HostBackdrop` is not supported. Blur of content outside the OSD
  window is not guaranteed.

## Compatibility and limitations

- Windows 11 x64. DDC/CI brightness requires a compatible monitor and
  works with supported Taskbar Scroll Actions and Twinkle Tray input.
- Audio output selection changes the default **Console** and
  **Multimedia** devices, not the **Communications** device.
- Media and device notifications depend on the information provided by
  Windows and connected hardware; Bluetooth disconnect notifications
  may not always be available.
- Network notifications distinguish Wi-Fi radio enable/disable from
  association/disconnection of a particular WLAN profile. Radio changes use
  the Native Wi-Fi PHY state; profile names are obtained from the active
  Windows Wi-Fi connection and may be unavailable without WLAN AutoConfig.
  Other adapter transitions and Windows connectivity hints are reported
  separately; they do not verify VPN or Internet reachability.
- Windows updates may affect compatibility with Shell integrations.

## Credits and license

Copyright (c) Reg Chen. Licensed under **GPL-3.0**.

The `WindhawkBlur` implementation is adapted directly from
[Windows 11 Taskbar Styler](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/windows-11-taskbar-styler.wh.cpp)
by m417z (GPL-3.0), itself based on
[TranslucentTB's XamlBlurBrush](https://github.com/TranslucentTB/TranslucentTB/blob/release/ExplorerTAP/XamlBlurBrush.cpp).
External project and product names/trademarks belong to their owners.
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
          $description: Reports network adapter connection/disconnection and Windows connectivity changes. Does not ping hosts or verify individual VPN tunnels.
          $description:zh-TW: 顯示網路介面卡連線／中斷及 Windows 網路狀態變化；不執行 Ping 或逐一驗證 VPN 通道。
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
          $name: Borderless custom OSD cards
          $name:zh-TW: 自訂 OSD 卡片無邊框
          $description: Removes the XAML card outline for all custom OSD categories. Does not control other mods.
          $description:zh-TW: 移除所有自訂 OSD 類別的 XAML 卡片外框，不影響其他 Mod。
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
        - ddcBackgroundEffect: opacity
          $name: Background effect
          $name:zh-TW: 背景效果
          $description: Use the original solid background or a list of one to five composited brushes.
          $description:zh-TW: 使用原有純色背景，或以 1 至 5 個筆刷圖層疊加；單層也使用相同功能。
          $options:
          - opacity: Transparency
          - layers: Brush layers
          $options:zh-TW:
          - opacity: 透明度
          - layers: 筆刷圖層
        - ddcBackgroundOpacity: 96
          $name: Background opacity (%)
          $name:zh-TW: 背景不透明度（%）
          #! $showIf: {ddcBackgroundEffect: opacity}
          #! $min: 0
          #! $max: 100
          #! $format: slider
        - ddcBrushLayers:
            - - enabled: true
                $name: Enable layer
                $name:zh-TW: 啟用圖層
              - opacity: 100
                $name: Layer opacity (%)
                $name:zh-TW: 圖層不透明度（%）
                $description: For blur brushes, 100% is recommended.
                $description:zh-TW: 模糊筆刷建議維持 100%。
                #! $min: 0
                #! $max: 100
                #! $format: slider
              - markup: '<AcrylicBrush BackgroundSource="Backdrop" TintColor="$mainColor" TintOpacity="0.1" TintLuminosityOpacity="0" />'
                $name: Brush markup (single line)
                $name:zh-TW: 筆刷語法（單行）
            - - enabled: true
              - opacity: 100
              - markup: '<LinearGradientBrush StartPoint="0,0" EndPoint="1,1"><GradientStop Color="#30FF0000" Offset="0" /><GradientStop Color="#300000FF" Offset="1" /></LinearGradientBrush>'
          $name: Background brush layers (bottom to top, maximum 5)
          $name:zh-TW: 背景筆刷圖層（由下至上，最多 5 層）
          $description: Put blur brushes first (bottom); add gradients or highlights above them.
          $description:zh-TW: 建議模糊筆刷放第一層，漸層及高光疊加在上方。
          #! $showIf: {ddcBackgroundEffect: layers}
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
        - ddcCornerRadius: 17
          $name: OSD window corner radius (logical px)
          $name:zh-TW: OSD 視窗圓角半徑（邏輯像素）
          $description: Controls the visible XAML card corners for all custom OSDs, including volume, SMTC, mixer and DDC. The transparent Win32 host uses no additional DWM rounding.
          $description:zh-TW: 控制所有自訂 OSD 的可見卡片圓角，包含音量、SMTC、混音器及 DDC。透明 Win32 宿主不額外套用 DWM 圓角。
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
        - ddcShowSun: true
          $name: Show sun icon
          $name:zh-TW: 顯示太陽圖示
        - ddcShowValue: true
          $name: Show volume / brightness value
          $name:zh-TW: 顯示音量／亮度數值
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
        - ddcSizePercent: 75
          $name: Custom OSD size (%)
          $name:zh-TW: 自訂 OSD 大小（%）
          $description: Overall uniform scale applied after the configurable logical width/height and monitor DPI. Does not change the aspect ratio of either layout.
          $description:zh-TW: 在可設定的邏輯寬高及螢幕 DPI 之後套用整體等比縮放，不會改變任何版面的長寬比例。
        - fadeOsd: true
          $name: Enable custom OSD fade animation
          $name:zh-TW: 啟用自訂 OSD 淡入淡出動畫
        - fadeDurationMs: 160
          $name: Fade duration (ms)
          $name:zh-TW: 淡入淡出時間（毫秒）
          #! $showIf: {fadeOsd: true}
          #! $min: 60
          #! $max: 450
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
      $name: Layout, display and animation
      $name:zh-TW: 版面、顯示螢幕與動畫
  $name: 2. Custom OSD
  $name:zh-TW: 2. 自訂 OSD
  $description: A Show switch controls only its own custom flyout. Native visibility is controlled exclusively by the native Hide switches above; when Hide is off and Show is on, both native and custom OSDs will appear.
  $description:zh-TW: 每個顯示開關只控制對應的自訂提示；原生提示則完全由上方的隱藏開關管理。隱藏關閉、顯示開啟時，原生與自訂提示會同時出現。
*/
// ==/WindhawkModSettings==

#include <winsock2.h>
#include <windows.h>
#include <dbt.h>
#include <setupapi.h>
#include <iphlpapi.h>
#include <shellapi.h>
#include <windhawk_utils.h>
#include <lowlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <atomic>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <cwchar>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <wincodec.h>
#include <initguid.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <windows.graphics.effects.h>
#include <dwmapi.h>
#include <shellscalingapi.h>
#include <cstdint>
#include <cstddef>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <wbemidl.h>
#include <audiopolicy.h>
#include <propidl.h>
#include <new>
#include <wrl/client.h>
#include <winrt/base.h>
#undef GetCurrentTime
#include <winrt/Windows.Foundation.h>
// WriteableBitmap::PixelBuffer returns Windows.Storage.Streams.IBuffer;
// calling Length() needs its full projection (as with PointerPoint).
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.ViewManagement.h>
// PointerRoutedEventArgs::GetCurrentPoint returns Windows.UI.Input.PointerPoint.
// Its Position/Properties members require the full projection, not just XAML.Input.
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.Media.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <array>
#include <mutex>
#include <vector>
#include <memory>
#include <limits>
#include <random>
#include <string_view>
#include <utility>
#include <type_traits>
#include <string>

// Interop declaration used by Windows.UI.Composition custom effects.
template <>
inline constexpr winrt::guid
    winrt::impl::guid_v<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>{
        winrt::impl::guid_v<winrt::Windows::Foundation::IPropertyValue>};

typedef enum MY_D2D1_GAUSSIANBLUR_OPTIMIZATION {
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_SPEED = 0,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED = 1,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY = 2,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_FORCE_DWORD = 0xffffffff
} MY_D2D1_GAUSSIANBLUR_OPTIMIZATION;

#ifndef BUILD_WINDOWS
namespace ABI {
#endif
namespace Windows {
namespace Graphics {
namespace Effects {

typedef interface IGraphicsEffectSource IGraphicsEffectSource;
typedef interface IGraphicsEffectD2D1Interop IGraphicsEffectD2D1Interop;

typedef enum GRAPHICS_EFFECT_PROPERTY_MAPPING {
    GRAPHICS_EFFECT_PROPERTY_MAPPING_UNKNOWN,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORX,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORY,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORZ,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORW,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_RECT_TO_VECTOR4,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_RADIANS_TO_DEGREES,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLORMATRIX_ALPHA_MODE,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLOR_TO_VECTOR3,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLOR_TO_VECTOR4
} GRAPHICS_EFFECT_PROPERTY_MAPPING;

#undef INTERFACE
#define INTERFACE IGraphicsEffectD2D1Interop
DECLARE_INTERFACE_IID_(IGraphicsEffectD2D1Interop,
                       IUnknown,
                       "2FC57384-A068-44D7-A331-30982FCF7177") {
    STDMETHOD(GetEffectId)(_Out_ GUID* id) PURE;
    STDMETHOD(GetNamedPropertyMapping)
    (LPCWSTR name,
     _Out_ UINT* index,
     _Out_ GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) PURE;
    STDMETHOD(GetPropertyCount)(_Out_ UINT* count) PURE;
    STDMETHOD(GetProperty)
    (UINT index, _Outptr_ winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) PURE;
    STDMETHOD(GetSource)(UINT index,
                         _Outptr_ IGraphicsEffectSource** source) PURE;
    STDMETHOD(GetSourceCount)(_Out_ UINT* count) PURE;
};

}  // namespace Effects
}  // namespace Graphics
}  // namespace Windows
#ifndef BUILD_WINDOWS
}  // namespace ABI
#endif

template <>
inline constexpr winrt::guid
    winrt::impl::guid_v<ABI::Windows::Graphics::Effects::IGraphicsEffectD2D1Interop>{
        0x2FC57384,
        0xA068,
        0x44D7,
        {0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77}};


namespace {

// Segoe Fluent Icons: monochrome glyphs, colored only by XAML Foreground.
// Keep PUA code points in one place instead of scattering them through views.
namespace osd_glyph {
constexpr PCWSTR kChevronLeft = L"\uE76B";
constexpr PCWSTR kChevronRight = L"\uE76C";
constexpr PCWSTR kChevronUp = L"\uE70E";
constexpr PCWSTR kChevronDown = L"\uE70D";
constexpr PCWSTR kMute = L"\uE74F";
constexpr PCWSTR kVolume = L"\uE767";
constexpr PCWSTR kBrightness = L"\uE706";
constexpr PCWSTR kMediaPrevious = L"\uE892";
constexpr PCWSTR kMediaPause = L"\uE769";
constexpr PCWSTR kMediaPlay = L"\uE768";
constexpr PCWSTR kMediaNext = L"\uE893";
constexpr PCWSTR kMediaShuffle = L"\uE8B1";
constexpr PCWSTR kMediaRepeatOne = L"\uE8ED";
constexpr PCWSTR kMediaRepeatAll = L"\uE8EE";
constexpr PCWSTR kClose = L"\uE8BB";
constexpr PCWSTR kBluetooth = L"\uE702";
constexpr PCWSTR kUsb = L"\uE88E";
constexpr PCWSTR kNetwork = L"\uE968";
constexpr PCWSTR kWifi = L"\uE701";
constexpr PCWSTR kKeyboardStandard = L"\uE92E";
constexpr PCWSTR kMouse = L"\uE962";
constexpr PCWSTR kHeadset = L"\uE95B";
constexpr PCWSTR kHeadphone = L"\uE7F6";
constexpr PCWSTR kSpeakers = L"\uE7F5";
constexpr PCWSTR kKeyboardClassic = L"\uE765";
constexpr PCWSTR kAirplane = L"\uE709";
constexpr PCWSTR kCamera = L"\uE722";
constexpr PCWSTR kMicrophone = L"\uE720";
constexpr PCWSTR kTaskView = L"\uE7C4";
constexpr PCWSTR kPage = L"\uE7C3";
constexpr PCWSTR kClipboardFile = L"\uF000";
constexpr PCWSTR kClipboardText = L"\uE9A4";
constexpr PCWSTR kClipboard = L"\uE8C8";
} // namespace osd_glyph

// Presentation-independent input arithmetic. Both the legacy GDI+
// controls and migrated XAML controls use these same normalized units.
namespace osd_input {
constexpr int kWheelStepPercent = 5; // Unified notch size for level and Mixer.
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

// Data/intent contracts have no dependency on XAML or its STA. The Win32
// receiver/RECT/device IDs are transport and placement facts, not UI objects.
namespace osd_model {
enum class Kind {
    Volume, NativeBrightness, DdcBrightness, LockStatus, NoticeStatus,
    NoticeDetails, NativeEvent, ClipboardImage, Mixer, Media
};
enum class ChevronDirection { Left, Right, Up, Down };
// Plain-value SMTC view state. The worker remains the sole GSMTC accessor.
struct MediaModel {
    std::wstring sourceId, title, artist;
    std::vector<uint8_t> encodedArtwork;
    uint32_t generation = 0, sessionCount = 0, selectionSerial = 0;
    bool playing = false, canPrevious = false, canToggle = false, canNext = false;
    bool canShuffle = false, shuffleKnown = false, shuffleActive = false;
    bool canRepeat = false, hasTimeline = false, canSeek = false;
    int repeatMode = -1, controlSizePercent = 100;
    bool squareButtons = false;
    int buttonCornerRadius = 6; // DIP radius in square mode, 0 = sharp.
    int64_t start = 0, end = 0, position = 0;
    uint64_t observedTick = 0;
};
// Pure presentation calculations: no clock reads, XAML or GSMTC calls.
int64_t MediaPosition(const MediaModel& m, uint64_t now) {
    if (!m.hasTimeline || m.end <= m.start) return 0;
    int64_t p = std::clamp(m.position, m.start, m.end);
    if (m.playing && now >= m.observedTick) {
        const uint64_t elapsed = std::min<uint64_t>(
            now - m.observedTick, static_cast<uint64_t>((m.end - p) / 10000));
        p += static_cast<int64_t>(elapsed * 10000);
    }
    return std::clamp(p, m.start, m.end);
}
std::wstring MediaTime(int64_t ticks100ns) {
    const uint64_t t = static_cast<uint64_t>(
        std::max<int64_t>(0, ticks100ns)) / 10000000ULL;
    const auto two = [](uint64_t n) -> std::wstring {
        return (n < 10 ? L"0" : L"") + std::to_wstring(n);
    };
    if (t >= 3600)
        return std::to_wstring(t / 3600) + L":" +
               two((t / 60) % 60) + L":" + two(t % 60);
    return std::to_wstring(t / 60) + L":" + two(t % 60);
}
struct MixerRow {
    std::wstring title;
    int percent = 0;
    bool muted = false, enabled = true;
    std::vector<uint8_t> iconPixels; // Optional 20x20 BGRA; owned bytes.
    std::wstring sessionId; // Unique Core Audio session instance or master endpoint.
};
struct MixerOutput {
    std::wstring title;
    bool selected = false;
    std::wstring id; // Device identity, not just its friendly display name.
};
struct MixerModel {
    std::wstring title, outputHeading, selectedOutput, outputError;
    std::vector<MixerRow> rows;
    std::vector<MixerOutput> outputs;
    uint32_t generation = 0;
    bool outputExpanded = false, outputFailed = false;
    int maxVisibleRows = 6;
};
struct BrushLayer {
    bool enabled = true;
    int opacity = 100;
    std::wstring markup;
};
bool SameBrushLayers(const std::vector<BrushLayer>& a,
                     const std::vector<BrushLayer>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (a[i].enabled != b[i].enabled ||
            a[i].opacity != b[i].opacity ||
            a[i].markup != b[i].markup)
            return false;
    return true;
}
struct Snapshot {
    Kind kind = Kind::Volume;
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
    ChevronDirection noticeDirection = ChevronDirection::Down;
    uint32_t noticeGeneration = 0;
    DWORD noticeInteractiveDurationMs = 8000;
    uint32_t clipboardWidth = 0, clipboardHeight = 0;
    std::vector<uint8_t> clipboardPixels; // Bounded 32-bit BGRA, no HBITMAP on STA.
    MixerModel mixer;
    MediaModel media;
    bool passiveRefresh = false;
    bool mirrorView = false; // Controller-projected XAML-only replica.
    bool mixerChevron = false;
    ChevronDirection mixerDirection = ChevronDirection::Down;
    bool brightness = false;
    bool showIcon = true;
    BYTE backgroundAlpha = 255;
    bool layeredBackground = false;
    // Internal, parser-only field. Each configured layer supplies its markup.
    std::wstring backgroundMarkup;
    std::vector<BrushLayer> backgroundLayers;
    bool borderless = true, fadeEnabled = false;
    int cornerRadius = 17;
    DWORD fadeDurationMs = 160;
    DWORD durationMs = 3000;
    RECT anchor{};          // Existing placement canvas in physical pixels.
    float scale = 1.0f;     // Monitor DPI * user-defined size.
    bool vertical = false;
    bool showValue = true;
    int innerPadding = 14;
    int iconSize = 16, fontSize = 15;
    DWORD background = 0x232327, text = 0xf8f8fc;
    DWORD accent = 0x67acff, track = 0x56565c;
};

// Functional transformations: unchanged input -> new owned output.
// No renderer, HWND lookup or hardware operation occurs in these functions.
enum class View { Level, Status, Details, ClipboardImage, Mixer, Media };
View SelectView(Kind kind) {
    if (kind == Kind::Media) return View::Media;
    if (kind == Kind::Mixer) return View::Mixer;
    if (kind == Kind::NoticeDetails) return View::Details;
    if (kind == Kind::ClipboardImage) return View::ClipboardImage;
    if (kind == Kind::LockStatus || kind == Kind::NoticeStatus ||
        kind == Kind::NativeEvent) return View::Status;
    return View::Level;
}
bool CanExpand(const Snapshot& data) {
    return data.kind == Kind::NoticeStatus &&
        data.noticeDetails.size() > 1;
}
bool SameNotice(const Snapshot& previous, const Snapshot& next,
                bool previouslyVisible) {
    return previouslyVisible &&
        previous.kind == Kind::NoticeStatus &&
        next.kind == Kind::NoticeStatus &&
        previous.statusTitle == next.statusTitle &&
        previous.noticeDetails == next.noticeDetails;
}
DWORD NoticeDuration(const Snapshot& data, bool expanded,
                     DWORD originalDuration) {
    return CanExpand(data) && expanded
        ? data.noticeInteractiveDurationMs : originalDuration;
}
Snapshot WithPercent(Snapshot data, int percent) {
    data.percent = std::clamp(percent, 0, 100);
    data.rawValue = data.kind == Kind::DdcBrightness
        ? static_cast<int>(osd_input::PercentToRaw(
            data.minimum, data.maximum, data.percent))
        : data.percent;
    return data;
}
Snapshot AsStatus(Snapshot data, Kind category,
                  DWORD duration, bool fluentIcon) {
    data.kind = category;
    data.brightness = false;
    data.valueKnown = false;
    data.showValue = false;
    data.statusFontIcon = fluentIcon;
    data.durationMs = duration;
    return data;
}
} // namespace osd_model

// Control adapter: XAML (or a future renderer) may emit a command, but
// hardware and audio APIs are called only by the existing UI-thread handler.
namespace osd_control {
enum class Action {
    SetPercent, Wheel, ToggleMute,
    OpenMixer, CloseMixer, ToggleNoticeDetails, MixerSetPercent, MixerToggleMute,
    MixerSelectOutput, MixerToggleOutput,
    MediaAction, MediaSeek, CloseMedia
};
enum class Target { None, Volume, NativeBrightness, DdcBrightness, Mixer, Media, Notice };
struct Command {
    Target target = Target::None;
    Action action = Action::SetPercent;
    int value = 0;
    int index = -1; // 0=master, positive=audio session, or output index.
    int64_t mediaPosition = 0; // 100 ns; no WinRT or playback object.
    uint64_t mixerSessionTag = 0; // POD fingerprint; full ID stays in Mixer snapshots.
    uint32_t generation = 0;
    WCHAR device[CCHDEVICENAME]{};
    DWORD physicalIndex = 0, minimum = 0, maximum = 0;
};
constexpr UINT kMessage = WM_APP + 690;
// XAML produces value commands, but only the controller executes hardware
// operations. The posted flag and pending queue are protected by one lock.
struct CommandMailbox {
    SRWLOCK lock = SRWLOCK_INIT;
    std::vector<Command> pending;
    bool posted = false;
    static constexpr size_t kCapacity = 64;

    static bool IsReplaceable(const Command& command) {
        switch (command.action) {
            case Action::SetPercent:
                return command.target == Target::Volume ||
                       command.target == Target::NativeBrightness ||
                       command.target == Target::DdcBrightness;
            case Action::MixerSetPercent:
                return command.target == Target::Mixer;
            case Action::MediaSeek:
                return command.target == Target::Media;
            default:
                return false; // Wheel, toggles, and selections are ordered actions.
        }
    }

    static bool CanReplace(const Command& previous, const Command& next) {
        if (!IsReplaceable(previous) || !IsReplaceable(next) ||
            previous.target != next.target || previous.action != next.action ||
            previous.generation != next.generation)
            return false;
        if (next.target == Target::Mixer)
            return previous.index == next.index &&
                   previous.mixerSessionTag == next.mixerSessionTag;
        if (next.target == Target::Media)
            return previous.index == next.index;
        if (next.target == Target::DdcBrightness)
            return previous.physicalIndex == next.physicalIndex &&
                   previous.minimum == next.minimum &&
                   previous.maximum == next.maximum &&
                   wcscmp(previous.device, next.device) == 0;
        return true;
    }

    bool Enqueue(const Command& command, HWND receiver) {
        if (!receiver) return false;
        bool accepted = false;
        bool full = false;
        DWORD postError = NO_ERROR;
        AcquireSRWLockExclusive(&lock);
        // Only adjacent updates may coalesce: intervening actions are barriers.
        const bool replace = !pending.empty() &&
                             CanReplace(pending.back(), command);
        auto disposable = pending.end();
        if (!replace && pending.size() >= kCapacity)
            disposable = std::find_if(pending.begin(), pending.end(),
                                     IsReplaceable);
        if (!replace && pending.size() >= kCapacity &&
            disposable == pending.end()) {
            full = true;
        } else if (!posted && !PostMessageW(receiver, kMessage, 0, 0)) {
            // Posting is done under the same lock, *before* mutation.
            // A failed post therefore cannot strand or later replay a command.
            postError = GetLastError();
        } else {
            if (replace) {
                pending.back() = command;
            } else {
                // At capacity, sacrifice an idempotent value update rather
                // than a mute/toggle/selection command.
                if (disposable != pending.end()) pending.erase(disposable);
                pending.push_back(command);
            }
            posted = true;
            accepted = true;
        }
        ReleaseSRWLockExclusive(&lock);
        if (full)
            Wh_Log(L"OSD command queue full; rejected action %u",
                   static_cast<unsigned>(command.action));
        if (postError != NO_ERROR)
            Wh_Log(L"OSD command post failed (%lu)", postError);
        return accepted;
    }

    std::vector<Command> Take() {
        std::vector<Command> result;
        AcquireSRWLockExclusive(&lock);
        result.swap(pending);
        posted = false;
        ReleaseSRWLockExclusive(&lock);
        return result;
    }
    void ReleaseAfterHooksRemoved() {
        std::vector<Command> oldPending;
        AcquireSRWLockExclusive(&lock);
        pending.swap(oldPending);
        posted = false;
        ReleaseSRWLockExclusive(&lock);
        // Destruct storage after dropping the mailbox lock.
    }
};
struct ControlModuleState final {
    CommandMailbox mailbox;
    void ReleaseAfterHooksRemoved() { mailbox.ReleaseAfterHooksRemoved(); }
};
// Process shutdown skips normal mod unload: never destruct this mailbox
// from DLL_PROCESS_DETACH while another thread could still own its lock.
ControlModuleState& GetControlState() {
    [[clang::no_destroy]] static ControlModuleState instance;
    return instance;
}

Target ForCategory(osd_model::Kind kind) {
    switch (kind) {
        case osd_model::Kind::Volume: return Target::Volume;
        case osd_model::Kind::NativeBrightness: return Target::NativeBrightness;
        case osd_model::Kind::DdcBrightness: return Target::DdcBrightness;
        case osd_model::Kind::Mixer: return Target::Mixer;
        case osd_model::Kind::Media: return Target::Media;
        case osd_model::Kind::NoticeStatus: return Target::Notice;
        default: return Target::None;
    }
}
Command Build(const osd_model::Snapshot& source, Action action, int value) {
    Command cmd;
    cmd.target = action == Action::OpenMixer
        ? Target::Mixer : ForCategory(source.kind);
    cmd.action = action;
    cmd.value = value;
    cmd.generation = action == Action::ToggleNoticeDetails
        ? source.noticeGeneration : source.mixer.generation;
    wcscpy_s(cmd.device, source.device);
    cmd.physicalIndex = source.physicalIndex;
    cmd.minimum = source.minimum;
    cmd.maximum = source.maximum;
    return cmd;
}
// POD command transport holds a non-cryptographic identity fingerprint,
 // while the UI snapshot and Core Audio owner retain complete session IDs.
// Full strings must never be placed in Command (trivially_copyable contract).
uint64_t MixerIdentityTag(const std::wstring& id) {
    if (id.empty()) return 0;
    uint64_t tag = 14695981039346656037ULL; // FNV-1a 64-bit offset
    for (wchar_t ch : id) {
        tag ^= static_cast<uint16_t>(ch);
        tag *= 1099511628211ULL;
    }
    return tag ? tag : 1;
}
Command BuildMixer(const osd_model::Snapshot& source,
                   Action action, int row, int value = 0) {
    Command cmd = Build(source, action, value);
    cmd.target = Target::Mixer;
    cmd.index = row;
    if ((action == Action::MixerSetPercent ||
         action == Action::MixerToggleMute) &&
        row >= 0 && static_cast<size_t>(row) < source.mixer.rows.size())
        cmd.mixerSessionTag = MixerIdentityTag(source.mixer.rows[row].sessionId);
    return cmd;
}
Command BuildMedia(const osd_model::Snapshot& source, Action action,
                   int actionCode = 0, int64_t position = 0) {
    Command cmd = Build(source, action, actionCode);
    cmd.target = Target::Media;
    cmd.mediaPosition = position;
    cmd.generation = source.media.generation;
    cmd.index = static_cast<int>(source.media.selectionSerial);
    return cmd;
}
void Submit(const Command& cmd, HWND receiver) {
    if (!receiver || cmd.target == Target::None) return;
    (void)GetControlState().mailbox.Enqueue(cmd, receiver);
}
std::vector<Command> Drain() {
    return GetControlState().mailbox.Take();
}
} // namespace osd_control

// Pure geometry functions. Inputs are owned values; outputs are dimensions
// and coordinates only. No HWND queries, XAML controls, GDI state or timers.
namespace osd_layout {
struct Frame {
    double insetX = 0, insetY = 0;
    double width = 0, height = 0;
};
Frame CardFrame(const osd_model::Snapshot& value,
                double insetXRatio, double insetYRatio) {
    const double scale = std::clamp(
        static_cast<double>(value.scale), 0.5, 6.0);
    const double logicalW = std::max(32.0,
        static_cast<double>(value.anchor.right - value.anchor.left) / scale);
    const double logicalH = std::max(32.0,
        static_cast<double>(value.anchor.bottom - value.anchor.top) / scale);
    const double x = std::min(logicalW * insetXRatio, logicalW / 8.0);
    const double y = std::min(logicalH * insetYRatio, logicalH / 8.0);
    return {x, y, std::max(28.0, logicalW - x * 2.0),
                  std::max(28.0, logicalH - y * 2.0)};
}
// Main level and attached Mixer share the exact same visible card insets.
Frame LevelFrame(const osd_model::Snapshot& value) {
    const double scale = std::clamp(
        static_cast<double>(value.scale), 0.5, 6.0);
    const double w = static_cast<double>(
        value.anchor.right - value.anchor.left) / scale;
    const double h = static_cast<double>(
        value.anchor.bottom - value.anchor.top) / scale;
    const double x = value.vertical ? 7.0 : 13.0;
    const double y = value.vertical ? 6.0 : 10.0;
    return {x, y, std::max(28.0, w - 2.0 * x),
        std::max(28.0, h - (value.vertical ? 12.0 : 23.0))};
}
// Use the actual calculated panel and primary-card positions. The chevron
// points toward the Mixer when closed and back toward the level when open.
osd_model::ChevronDirection MixerChevronDirection(
        const RECT& main, const RECT& panel, bool vertical, bool expanded) {
    const int64_t mainCenter2 = vertical
        ? int64_t(main.left) + main.right
        : int64_t(main.top) + main.bottom;
    const int64_t panelCenter2 = vertical
        ? int64_t(panel.left) + panel.right
        : int64_t(panel.top) + panel.bottom;
    const bool pointsBefore = (panelCenter2 < mainCenter2) != expanded;
    if (vertical)
        return pointsBefore ? osd_model::ChevronDirection::Left
                            : osd_model::ChevronDirection::Right;
    return pointsBefore ? osd_model::ChevronDirection::Up
                        : osd_model::ChevronDirection::Down;
}
const wchar_t* MixerChevronGlyph(osd_model::ChevronDirection direction) {
    switch (direction) {
        case osd_model::ChevronDirection::Left:  return osd_glyph::kChevronLeft;
        case osd_model::ChevronDirection::Right: return osd_glyph::kChevronRight;
        case osd_model::ChevronDirection::Up:    return osd_glyph::kChevronUp;
        case osd_model::ChevronDirection::Down:  return osd_glyph::kChevronDown;
    }
    return osd_glyph::kChevronDown;
}
struct MixerButton {
    bool visible = false;
    double size = 0, x = 0, y = 0, verticalReserve = 0;
};
MixerButton MixerButtonGeometry(const osd_model::Snapshot& value,
                                double bodyW, double bodyH) {
    if (value.kind != osd_model::Kind::Volume || !value.mixerChevron)
        return {};
    if (!value.vertical) {
        const double size = std::clamp(bodyW * .09, 20.0, 28.0);
        const double top = std::max(0.0, (bodyH - size) / 2.0);
        // The original 2px trailing gap placed the Button's corners
        // inside the rounded card's clipped area (especially at small
        // heights and large user-configured corner radii).
        // Solve the rounded-rectangle arc at the Button's top/bottom
        // instead of guessing an offset based on one default width.
        const double radius = std::clamp(
            static_cast<double>(value.cornerRadius), 0.0,
            std::min(bodyW, bodyH) / 2.0);
        const double cornerCut = top < radius
            ? radius - std::sqrt(std::max(0.0, top * (2.0 * radius - top)))
            : 0.0;
        const double breathingRoom = std::clamp(
            static_cast<double>(value.innerPadding) * .65, 4.0, 15.0);
        const double trailingInset = cornerCut + breathingRoom;
        return {true, size,
            std::max(0.0, bodyW - size - trailingInset),
            top, 0.0};
    }
    // On the slim card, the button has its own bottom row rather
    // than sharing the speaker/track region.
    const double size = std::clamp(bodyW * .40, 20.0, 28.0);
    const double bottom = std::clamp(bodyH * .04, 4.0, 9.0);
    const double gap = std::clamp(bodyH * .025, 4.0, 10.0);
    return {true, size, std::max(0.0, (bodyW - size) / 2.0),
        std::max(0.0, bodyH - size - bottom), size + bottom + gap};
}
// Use measured rows with rounded-corner clearance, not hard-coded edge gaps.
// A centered label or icon must clear the actual corner arc at its own width.
// On a short user-configured card, spacing yields first to Slider travel.
struct VerticalLevelFlow {
    double topPad = 0, bottomPad = 0, gap = 0;
    double sliderTop = 0, sliderBottom = 0, iconTop = 0;
};
VerticalLevelFlow VerticalLevelBounds(
        const osd_model::Snapshot& value, double bodyWidth,
        double bodyHeight, double chevronReserve,
        double iconWidth, double iconHeight,
        double labelWidth, double labelHeight) {
    const double contentHeight = std::max(0.0,
        bodyHeight - chevronReserve);
    const double freeHeight = std::max(0.0,
        contentHeight - iconHeight - labelHeight);
    const double radius = std::clamp(
        static_cast<double>(value.cornerRadius), 0.0,
        std::min(bodyWidth, bodyHeight) / 2.0);
    const auto cornerInset = [&](double glyphWidth) {
        if (radius <= 0.0 || glyphWidth <= 0.0) return 0.0;
        // Keep 3 logical pixels between the glyph and the rounded edge.
        const double sideRoom = std::max(0.0,
            (bodyWidth - glyphWidth) / 2.0 - 3.0);
        if (sideRoom >= radius) return 0.0;
        const double arcX = radius - sideRoom;
        return radius - std::sqrt(std::max(0.0,
            radius * radius - arcX * arcX));
    };
    const double desiredPad = std::clamp(
        double(value.innerPadding) * .48, 8.0, 12.0);
    const double desiredTop = std::max(desiredPad,
        value.showValue ? cornerInset(labelWidth) + 2.0 : desiredPad);
    const double desiredBottom = std::max(desiredPad,
        value.showIcon ? cornerInset(iconWidth) + 2.0 : desiredPad);
    const double desiredGap = std::clamp(
        double(value.innerPadding) * .50, 7.0, 10.0);
    const int gapCount = int(value.showIcon) + int(value.showValue);
    const double wantedSpacing =
        desiredTop + desiredBottom + gapCount * desiredGap;
    // Preserve a meaningful Slider travel range when a panel is short.
    const double minTrack = std::min(36.0, freeHeight);
    const double spacingScale = wantedSpacing > 0.0
        ? std::clamp((freeHeight - minTrack) / wantedSpacing, 0.0, 1.0)
        : 1.0;
    VerticalLevelFlow out;
    out.topPad = desiredTop * spacingScale;
    out.bottomPad = desiredBottom * spacingScale;
    out.gap = desiredGap * spacingScale;
    out.iconTop = bodyHeight - chevronReserve -
        out.bottomPad - iconHeight;
    out.sliderTop = out.topPad +
        (value.showValue ? labelHeight + out.gap : 0.0);
    out.sliderBottom = std::max(out.sliderTop,
        value.showIcon ? out.iconTop - out.gap :
            bodyHeight - chevronReserve - out.bottomPad);
    return out;
}
// Computed card layout, shared by future XAML painting and hit geometry.
// One shape policy for Previous/Play/Next, Shuffle/Repeat and session switch.
double MediaButtonCornerRadius(const osd_model::MediaModel& model,
                               double diameter) {
    const double radius = std::max(0.0, diameter / 2.0);
    return model.squareButtons
        ? std::clamp(static_cast<double>(model.buttonCornerRadius), 0.0, radius)
        : radius;
}
struct MediaGeometry {
    Frame frame;
    bool hasTimeline = false, cycleVisible = false;
    double artX = 0, artY = 0, artSize = 0, artCorner = 0;
    double textX = 0, textW = 0;
    double titleY = 0, titleH = 0, titleFont = 0;
    double artistY = 0, artistH = 0, artistFont = 0;
    double timelineY = 0, timelineH = 0;
    double timeY = 0, timeHeight = 0, timeFont = 0;
    double controlsY = 0, controlRadius = 0, controlX[3]{};
    double extraX = 0, extraY[2]{};
    double cycleX = 0, cycleY = 0, cycleSize = 0, cycleFont = 0;
    double placeholderFont = 0;
};
MediaGeometry MediaLayout(const osd_model::Snapshot& value) {
    MediaGeometry g;
    g.frame = LevelFrame(value);
    const auto& m = value.media;
    const double w = g.frame.width, h = g.frame.height;
    const double pad = std::clamp(value.innerPadding * .7, 9.0, 17.0);
    const double artGap = std::clamp(w * .035, 8.0, 16.0);
    const double availableW = std::max(1.0, w - 2.0 * pad);
    const double availableH = std::max(1.0, h - 2.0 * pad);
    const double scale = std::clamp(m.controlSizePercent / 100.0, .9, 1.35);
    const bool shuffle = m.canShuffle && m.shuffleKnown;
    const bool repeat = m.canRepeat && m.repeatMode >= 0;
    const bool extra = shuffle || repeat, both = shuffle && repeat;
    const bool buttons = m.canPrevious || m.canToggle || m.canNext || extra;
    g.hasTimeline = m.hasTimeline && m.end > m.start;

    // The control row should USE the available text-column width, not
    // merely squeeze into the smallest group that fits beside the cover.
    // A generous preferred separation is part of the cover-size constraint.
    const auto mainSpacing = [](double width) {
        return std::clamp(width * .085, 10.0, 18.0);
    };
    const auto extraSpacing = [](double width) {
        return std::clamp(width * .065, 8.0, 13.0);
    };

    // Solve cover width only AFTER reserving enough room for the transport
    // controls and comfortable gaps. Otherwise maximizing artwork consumes
    // nearly all of the playback row even on a relatively wide panel.
    const auto fits = [&](double art) {
        const double textWidth = availableW - art - artGap;
        const double mainGap = mainSpacing(textWidth);
        const double auxGap = extra ? extraSpacing(textWidth) : 0.0;
        const double r = std::min(art * .115 * scale, 20.0 * scale);
        return textWidth >= (extra ? 7.0 : 6.0) * r +
            2.0 * mainGap + auxGap;
    };
    const double maxArt = std::max(1.0,
        std::min(availableH, availableW * .52));
    g.artSize = maxArt;
    if (!fits(maxArt)) {
        double low = 1.0, high = maxArt;
        // Pure bounded search: at larger art sizes, the remaining text
        // column is narrower and the desired transport buttons are larger.
        for (int i = 0; i < 18; ++i) {
            const double mid = (low + high) / 2.0;
            if (fits(mid)) low = mid;
            else high = mid;
        }
        g.artSize = low;
    }
    g.artX = pad;
    g.artY = pad + std::max(0.0,
        (availableH - g.artSize) / 2.0);
    const double artBottom = g.artY + g.artSize;
    g.artCorner = std::clamp(g.artSize * .056, 4.0, 14.0);
    g.placeholderFont = std::clamp(g.artSize * .30, 20.0, 48.0);
    g.textX = g.artX + g.artSize + artGap;
    g.textW = std::max(1.0, w - pad - g.textX);

    // Typography and the complete vertical stack are functions of the
    // available cover area and user's font size, not absolute positions.
    const double fontScale = std::clamp(g.artSize / 120.0, .78, 1.0);
    g.titleFont = std::max(10.0,
        std::clamp(double(value.fontSize + 1), 12.0, 22.0) * fontScale);
    g.artistFont = std::max(9.0,
        std::clamp(double(value.fontSize - 2), 10.0, 18.0) * fontScale);
    g.timeFont = std::max(9.0,
        std::clamp(double(value.fontSize - 4), 9.0, 14.0) * fontScale);
    g.titleH = g.titleFont * 1.25;
    g.artistH = g.artistFont * 1.25;
    g.timeHeight = g.timeFont * 1.25;
    g.timelineH = std::clamp(g.artSize * .18, 20.0, 30.0);
    const double titleGap = std::clamp(g.artSize * .02, 2.0, 5.0);
    const double artistSeekGap = std::clamp(g.artSize * .03, 2.0, 6.0);
    const double seekTimeGap = std::clamp(g.artSize * .014, 1.0, 3.0);
    const double timeControlsGap = std::clamp(g.artSize * .025, 2.0, 6.0);
    const double stackedExtraGap = both
        ? std::clamp(g.artSize * .022, 2.0, 5.0) : 0.0;

    // Align every main transport button's BOTTOM with the cover bottom.
    // With both extras, Repeat's bottom shares that baseline; Shuffle sits
    // above it at the calculated gap. This is a constraint, not a Y ratio.
    const double preferredMainGap = mainSpacing(g.textW);
    const double auxGap = extra ? extraSpacing(g.textW) : 0.0;
    const double rows = g.titleH + titleGap + g.artistH +
        (g.hasTimeline ? artistSeekGap + g.timelineH +
            seekTimeGap + g.timeHeight : 0.0);
    const double maxVerticalRadius = std::max(1.0,
        (artBottom - pad - rows - timeControlsGap - stackedExtraGap) / 2.0);
    g.controlRadius = buttons ? std::max(1.0, std::min({
        g.artSize * .115 * scale, 20.0 * scale,
        (g.textW - 2.0 * preferredMainGap - auxGap) /
            (extra ? 7.0 : 6.0),
        maxVerticalRadius})) : 0.0;
    g.controlsY = artBottom - g.controlRadius;
    const double auxiliaryWidth = extra ? g.controlRadius : 0.0;
    // Distribute all remaining horizontal space into the TWO main gaps.
    // Previous/Play/Next are spread across the full text column, while
    // Shuffle/Repeat retain their own separate stacked column at the left.
    const double mainGap = std::max(preferredMainGap,
        (g.textW - auxiliaryWidth - auxGap -
            6.0 * g.controlRadius) / 2.0);
    g.controlX[0] = g.textX + auxiliaryWidth +
        auxGap + g.controlRadius;
    g.controlX[1] = g.controlX[0] + 2.0 * g.controlRadius + mainGap;
    g.controlX[2] = g.controlX[1] + 2.0 * g.controlRadius + mainGap;
    g.extraX = g.textX + auxiliaryWidth / 2.0;
    g.extraY[0] = both ? artBottom - 1.5 * g.controlRadius -
        stackedExtraGap : artBottom - g.controlRadius / 2.0;
    g.extraY[1] = artBottom - g.controlRadius / 2.0;

    // Lay out content backwards from the cover-anchored control group.
    // Labels can rise into free panel space above the image when a narrow
    // album cover cannot contain a large user-configured font and Slider.
    const double controlTop = artBottom -
        2.0 * g.controlRadius - stackedExtraGap;
    if (g.hasTimeline) {
        g.timeY = controlTop - timeControlsGap - g.timeHeight;
        g.timelineY = g.timeY - seekTimeGap - g.timelineH;
        g.titleY = std::max(pad, std::min(g.artY,
            g.timelineY - artistSeekGap - g.artistH -
            titleGap - g.titleH));
    } else {
        g.titleY = std::max(pad, std::min(g.artY,
            controlTop - timeControlsGap - g.artistH -
            titleGap - g.titleH));
    }
    g.artistY = g.titleY + g.titleH + titleGap;

    // The session-switch badge is anchored INSIDE the cover, and does
    // not depend on the independently configurable transport-button size.
    const double overlayInset = std::clamp(g.artSize * .035, 3.0, 8.0);
    g.cycleSize = std::clamp(g.artSize * .20, 16.0, 28.0);
    g.cycleVisible = m.sessionCount > 1 &&
        g.cycleSize + 2.0 * overlayInset < g.artSize;
    g.cycleX = g.artX + g.artSize - overlayInset - g.cycleSize;
    g.cycleY = g.artY + overlayInset;
    g.cycleFont = std::clamp(g.cycleSize * .50, 8.0, 16.0);
    return g;
}
struct Status {
    Frame frame;
    bool lock = false, interactive = false;
    double radius = 0, pad = 0, tileSize = 0, tileX = 0, tileY = 0;
    double textX = 0, textW = 0, lineGap = 0;
    double underlineH = 0, underlineTop = 0, textTop = 0;
    int titleFont = 15, detailFont = 12;
};
Status StatusGeometry(const osd_model::Snapshot& value) {
    Status g;
    // The fractions preserve the former 296x92 base card margins, but
    // all positions are recomputed from the actual current dimensions.
    g.frame = CardFrame(value, 8.0 / 296.0, 7.0 / 92.0);
    const double w = g.frame.width, h = g.frame.height;
    g.lock = value.kind == osd_model::Kind::LockStatus;
    g.interactive = osd_model::CanExpand(value);
    g.radius = static_cast<double>(
        std::clamp(value.cornerRadius, 0, 34));
    g.pad = std::clamp(
        static_cast<double>(value.innerPadding), 6.0, 22.0) * .68;
    g.tileSize = std::max(18.0,
        std::min(h - 2.0 * g.pad, h * .69));
    g.tileX = g.pad;
    g.tileY = (h - g.tileSize) / 2.0;
    g.textX = g.tileX + g.tileSize + g.pad;
    const double arrowW = g.interactive
        ? std::clamp(h * .32, 20.0, 28.0) + g.pad * .5 : 0.0;
    g.textW = std::max(1.0, w - g.textX - g.pad - arrowW);
    g.titleFont = std::clamp(value.fontSize, 10, 24);
    g.detailFont = std::max(10, g.titleFont - 3);
    g.lineGap = std::clamp(h * .045, 2.0, 6.0);
    const double textBlockH =
        g.titleFont * 1.43 + g.detailFont * 1.43 + g.lineGap;
    g.underlineH = std::max(2.0, h * .04);
    const double bottomInset = std::max(g.pad, g.radius * .65);
    g.underlineTop = std::max(0.0,
        h - bottomInset - g.underlineH);
    const double centeredTop = std::max(0.0,
        (h - textBlockH) / 2.0 - 2.0);
    const double availableTop = std::max(0.0,
        g.underlineTop - g.lineGap - textBlockH);
    g.textTop = g.lock ? std::min(centeredTop, availableTop) : centeredTop;
    return g;
}
struct Clipboard {
    Frame frame;
    double inset = 0, radius = 0, previewW = 0, previewH = 0;
    double captionFont = 12;
};
Clipboard ClipboardGeometry(const osd_model::Snapshot& value) {
    Clipboard g;
    g.frame = CardFrame(value, 8.0 / 264.0, 7.0 / 224.0);
    g.inset = std::clamp(
        static_cast<double>(value.innerPadding), 6.0, 22.0) * .68;
    g.captionFont = std::clamp(value.fontSize - 2, 10, 18);
    g.previewW = std::max(1.0, g.frame.width - 2.0 * g.inset);
    g.previewH = std::max(1.0,
        g.frame.height - 3.0 * g.inset - g.captionFont * 1.5);
    g.radius = static_cast<double>(std::clamp(value.cornerRadius, 0, 34));
    return g;
}
struct Surface {
    int x = 0, y = 0, width = 0, height = 0;
};
Surface SurfaceGeometry(const osd_model::Snapshot& value,
                        double insetX, double insetY,
                        double width, double height,
                        const RECT* work) {
    const double scale = std::clamp(
        static_cast<double>(value.scale), 0.5, 6.0);
    Surface out;
    out.width = std::max(28, static_cast<int>(std::lround(width * scale)));
    out.height = std::max(28, static_cast<int>(std::lround(height * scale)));
    out.x = value.anchor.left +
        static_cast<int>(std::lround(insetX * scale));
    out.y = value.anchor.top +
        static_cast<int>(std::lround(insetY * scale));
    if (work && value.kind == osd_model::Kind::NoticeStatus &&
        height > static_cast<double>(
            value.anchor.bottom - value.anchor.top) / scale -
            2.0 * insetY + .5)
        out.y = std::clamp(out.y, static_cast<int>(work->top),
            std::max(static_cast<int>(work->top),
                     static_cast<int>(work->bottom) - out.height));
    return out;
}
} // namespace osd_layout

// Compile-time structural contracts: owned cross-thread view descriptions,
// plain-value control commands, and no WinRT types at either boundary.
static_assert(std::is_copy_constructible_v<osd_model::Snapshot>,
    "OSD snapshots must own their data across the renderer boundary");
static_assert(std::is_trivially_copyable_v<osd_control::Command>,
    "OSD control commands must be plain-value transport records");

// Optional native XAML backend. WinRT visual objects stay on its STA.
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
constexpr UINT kRendererFailedMessage = WM_APP + 687;
constexpr UINT kRendererReadyMessage = WM_APP + 688;
constexpr UINT_PTR kHideTimer = 683;
constexpr UINT_PTR kFadeTimer = 684;
constexpr UINT_PTR kStatusLineTimer = 685;
constexpr UINT_PTR kMediaProgressTimer = 686;
constexpr double kOffLineRatio = .35;
constexpr DWORD kStatusLineAnimationMs = 220;
constexpr int kWidth = 354, kHeight = 49; // Default horizontal card pixels.
constexpr double kFallbackTrackThickness = 8.0;
constexpr double kNativeSliderLayoutClearance = 20.0;

DWORD WINAPI ThreadProc(void*);

// XAML/WinRT objects remain STA-owned. This owner only publishes the
// cross-thread lifetime state and joins the STA before module unload.
class XamlLifecycleState {
    std::atomic<HWND> ready_{nullptr};
    std::atomic<DWORD> threadId_{0};
    std::atomic<bool> stopping_{false};
    std::atomic<bool> failed_{false};
    std::atomic<HWND> controller_{nullptr}; // Win32 message-only receiver.
    std::mutex startLock_;
    HANDLE thread_ = nullptr;

public:
    bool IsStopping() const noexcept { return stopping_.load(); }
    bool IsFailed() const noexcept { return failed_.load(); }
    void MarkFailed() noexcept {
        if (!failed_.exchange(true, std::memory_order_acq_rel) &&
            !stopping_.load(std::memory_order_acquire)) {
            const HWND receiver = controller_.load(std::memory_order_acquire);
            if (receiver)
                (void)PostMessageW(receiver, kRendererFailedMessage, 0, 0);
        }
    }
    void MarkFailedAndWithdrawReady() noexcept {
        MarkFailed();
        WithdrawReady();
    }
    void PublishReady(HWND hwnd) noexcept {
        ready_.store(hwnd, std::memory_order_release);
        const HWND receiver = controller_.load(std::memory_order_acquire);
        if (receiver && !stopping_.load(std::memory_order_acquire))
            (void)PostMessageW(receiver, kRendererReadyMessage, 0, 0);
    }
    void WithdrawReady() noexcept {
        ready_.store(nullptr, std::memory_order_release);
    }
    HWND ReadyWindow() const noexcept {
        return ready_.load(std::memory_order_acquire);
    }
    void PublishThreadId(DWORD id) noexcept {
        threadId_.store(id, std::memory_order_release);
    }
    // First launch and explicit user retry share this single startup path.
    // Only the Win32 controller calls Restart; never join the current STA.
    bool Restart(HWND receiver) {
        std::lock_guard<std::mutex> guard(startLock_);
        if (!receiver || IsStopping() || (thread_ && !IsFailed()))
            return false;
        if (thread_) {
            const DWORD priorId = threadId_.load(std::memory_order_acquire);
            if (priorId == GetCurrentThreadId()) return false;
            if (priorId)
                (void)PostThreadMessageW(priorId, WM_QUIT, 0, 0);
            (void)WaitForSingleObject(thread_, INFINITE);
            CloseHandle(thread_);
            thread_ = nullptr;
        }
        WithdrawReady();
        threadId_.store(0, std::memory_order_release);
        controller_.store(receiver, std::memory_order_release);
        failed_.store(false, std::memory_order_release);
        thread_ = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
        if (!thread_) {
            const DWORD error = GetLastError();
            MarkFailed();
            Wh_Log(L"Fluent OSD/XAML: STA creation failed (%lu)", error);
        }
        return thread_ != nullptr;
    }
    void Start(HWND receiver) { (void)Restart(receiver); }
    void Stop() {
        std::lock_guard<std::mutex> guard(startLock_);
        stopping_.store(true);
        const HWND hwnd = ready_.exchange(nullptr);
        if (hwnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
        const DWORD id = threadId_.load(std::memory_order_acquire);
        if (id) PostThreadMessageW(id, WM_QUIT, 0, 0);
        if (thread_) {
            // Join rather than unloading while XAML/WinRT still executes.
            WaitForSingleObject(thread_, INFINITE);
            CloseHandle(thread_);
            thread_ = nullptr;
        }
        controller_.store(nullptr, std::memory_order_release);
    }
};
// XAML lifecycle and owned snapshot transport share one STA-side owner.


using LevelKind = osd_model::Kind;
using Snapshot = osd_model::Snapshot;
using InputAction = osd_control::Action;
// The controller publishes owned snapshots to the XAML STA. DDC batches
// merge by physical target; other categories keep full-snapshot replacement.
struct SnapshotMailbox {
    SRWLOCK lock = SRWLOCK_INIT;
    std::vector<Snapshot> pending;

    void Publish(const std::vector<Snapshot>& snapshots) {
        AcquireSRWLockExclusive(&lock);
        // DDC batches are deltas. Merge consecutive deliveries so an event
        // for B cannot be lost when A arrives before the STA drains B.
        if (!pending.empty() && !snapshots.empty() &&
            pending.front().kind == LevelKind::DdcBrightness &&
            snapshots.front().kind == LevelKind::DdcBrightness) {
            for (const auto& snap : snapshots) {
                auto existing = std::find_if(pending.begin(), pending.end(),
                    [&](const Snapshot& old) { return old.key == snap.key; });
                if (existing != pending.end()) {
                    *existing = snap;
                } else {
                    // Match the controller's bounded 16-target DDC cache.
                    if (pending.size() == 16) pending.erase(pending.begin());
                    pending.push_back(snap);
                }
            }
        } else {
            pending = snapshots;
        }
        ReleaseSRWLockExclusive(&lock);
    }
    std::vector<Snapshot> Take() {
        std::vector<Snapshot> batch;
        AcquireSRWLockExclusive(&lock);
        batch.swap(pending);
        ReleaseSRWLockExclusive(&lock);
        return batch;
    }
    void ReleaseAfterThreadsStop() {
        std::vector<Snapshot> oldPending;
        AcquireSRWLockExclusive(&lock);
        pending.swap(oldPending);
        ReleaseSRWLockExclusive(&lock);
        // Destruct snapshots outside the lock and after both UI owners join.
    }
};
struct XamlModuleState final {
    XamlLifecycleState lifecycle;
    SnapshotMailbox snapshots;
    void ReleaseAfterThreadsStop() { snapshots.ReleaseAfterThreadsStop(); }
};
// STA-only view objects belong to ThreadProc; this cross-thread owner must
// not run a global destructor when Explorer exits without Wh_ModUninit.
XamlModuleState& GetXamlState() {
    [[clang::no_destroy]] static XamlModuleState instance;
    return instance;
}

// Cached view references live and die on the XAML STA, not in Core Audio.
struct MixerRowVisual {
    controls::Button mute{nullptr};
    controls::Slider slider{nullptr};
    controls::TextBlock percentLabel{nullptr};
    controls::Image icon{nullptr};
    bool muted = false, enabled = true;
};
// STA-only visual references are grouped by feature. Every sub-state releases
// WinRT controls before DesktopWindowXamlSource and the apartment are closed.
struct MediaViewState {
    controls::Canvas mediaSurface{nullptr};
    controls::Slider mediaSlider{nullptr};
    controls::TextBlock mediaElapsed{nullptr};
    controls::Image mediaCover{nullptr};
    imaging::WriteableBitmap mediaBitmap{nullptr};
    std::vector<uint8_t> mediaArtworkCache;
    bool mediaPopulating = false, mediaDragging = false;
    int64_t mediaPreview = 0;
    uint64_t mediaPreviewHold = 0;

    void ReleaseBeforeIslandClose() {
        mediaSlider = nullptr;
        mediaElapsed = nullptr;
        mediaCover = nullptr;
        mediaBitmap = nullptr;
        mediaArtworkCache.clear();
        mediaSurface = nullptr;
    }
};

struct MixerViewState {
    controls::Button mixerChevron{nullptr};
    controls::Border mixerSurface{nullptr};
    controls::StackPanel mixerColumn{nullptr}, mixerRows{nullptr},
                         mixerOutputs{nullptr};
    controls::ScrollViewer mixerRowsScroll{nullptr},
                           mixerOutputsScroll{nullptr};
    std::vector<MixerRowVisual> mixerRowVisuals;
    bool mixerPopulating = false;
    int mixerWheelRow = -1, mixerWheelRemainder = 0;

    void ReleaseBeforeIslandClose() {
        mixerRowVisuals.clear();
        mixerOutputsScroll = nullptr;
        mixerRowsScroll = nullptr;
        mixerOutputs = nullptr;
        mixerRows = nullptr;
        mixerColumn = nullptr;
        mixerSurface = nullptr;
        mixerChevron = nullptr;
    }
};

struct ClipboardViewState {
    controls::Border clipboardFrame{nullptr};
    controls::Image clipboardImage{nullptr};
    controls::TextBlock clipboardCaption{nullptr};

    void ReleaseBeforeIslandClose() {
        clipboardCaption = nullptr;
        clipboardImage = nullptr;
        clipboardFrame = nullptr;
    }
};

struct StatusViewState {
    controls::Border statusTile{nullptr};
    controls::TextBlock statusGlyph{nullptr}, statusTitle{nullptr},
                        statusDetail{nullptr};
    shapes::Rectangle statusUnderline{nullptr};
    controls::Button noticeChevron{nullptr};
    controls::TextBlock noticeHeading{nullptr};
    controls::ScrollViewer noticeScroll{nullptr};
    controls::StackPanel noticeRows{nullptr};
    bool noticeExpanded = false;
    double noticeHeaderH = 0;
    DWORD noticeNormalDurationMs = 3000;
    // Preserve the interpolated underline position across status changes.
    bool statusLineAnimating = false;
    ULONGLONG statusLineStart = 0;
    double statusLineFrom = 1.0, statusLineTo = 1.0;
    double statusLineRatio = 1.0, statusLineTextW = 0.0;
    double statusLineCenterX = 0.0;

    void ReleaseBeforeIslandClose() {
        noticeScroll = nullptr;
        noticeRows = nullptr;
        noticeHeading = nullptr;
        noticeChevron = nullptr;
        statusUnderline = nullptr;
        statusDetail = nullptr;
        statusTitle = nullptr;
        statusGlyph = nullptr;
        statusTile = nullptr;
    }
};

struct State {
    MediaViewState mediaView;
    MixerViewState mixerView;
    ClipboardViewState clipboardView;
    StatusViewState statusView;
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
    controls::Grid backgroundStack{nullptr};
    std::vector<controls::Border> backgroundLayerCards;
    controls::Canvas canvas{nullptr};
    controls::Viewbox viewbox{nullptr};
    controls::TextBlock icon{nullptr};
    controls::TextBlock value{nullptr};
    controls::Slider levelSlider{nullptr};
    bool levelPopulating = false, viewOnly = false;
    shapes::Rectangle track{nullptr};
    shapes::Rectangle fill{nullptr};
    media::RectangleGeometry fillClip{nullptr};
    bool attachedPeerOpen = false;
    State* pairedPanel = nullptr;  // STA-only, owned by root.peers.
    State* pairedVolume = nullptr; // STA-only, root owns this State.

    // Intrinsic size of *all possible* speaker and volume-value states.
    // These change only with the corresponding font size; neither text
    // changes nor mute/volume events may change progress-track geometry.
    int measuredIconFontSize = -1;
    int measuredValueFontSize = -1;
    double iconSlotWidth = 0.0, iconSlotHeight = 0.0;
    double valueSlotWidth = 0.0, valueSlotHeight = 0.0;
    double rawSlotWidth = 0.0, rawSlotHeight = 0.0;
    bool backgroundCached = false;
    bool cachedLayeredBackground = false;
    DWORD cachedBackground = 0, cachedAccent = 0,
          cachedText = 0, cachedTrack = 0;
    BYTE cachedBackgroundAlpha = 0;
    std::vector<osd_model::BrushLayer> cachedBackgroundLayers;
};
media::SolidColorBrush Brush(DWORD rgb, BYTE alpha = 255) {
    return media::SolidColorBrush(winrt::Windows::UI::Color{
        alpha, static_cast<BYTE>(rgb >> 16), static_cast<BYTE>(rgb >> 8),
        static_cast<BYTE>(rgb)});
}

// Directly adapted from m417z's Windows 11 Taskbar Styler (GPL-3.0),
// XamlBlurBrush in windows-11-taskbar-styler.wh.cpp v1.11.2,
// itself based on TranslucentTB's XamlBlurBrush.
// Preserve its 5-stage D2D/Composition graph; Fluent OSD owns a bounded
// parser, STA-safe noise cache, and independent XAML Island lifetime.
// No Styler theme engine, XamlReader or taskbar-specific code is included.
namespace osd_blur {
namespace wf = winrt::Windows::Foundation;
namespace wge = winrt::Windows::Graphics::Effects;
namespace awge = ABI::Windows::Graphics::Effects;
namespace wss = winrt::Windows::Storage::Streams;
namespace wuc = winrt::Windows::UI::Composition;
wss::IRandomAccessStream CreateNoiseStream(float density);
struct GaussianBlurEffect
    : winrt::implements<GaussianBlurEffect, wge::IGraphicsEffect,
                        wge::IGraphicsEffectSource,
                        awge::IGraphicsEffectD2D1Interop> {
    wge::IGraphicsEffectSource Source{nullptr};
    float BlurAmount = 0.0f;
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION Optimization =
        MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED;
    D2D1_BORDER_MODE BorderMode = D2D1_BORDER_MODE_SOFT;

    winrt::hstring Name() const noexcept { return m_name; }
    void Name(winrt::hstring name) { m_name = std::move(name); }

    HRESULT GetEffectId(GUID* id) noexcept;
    HRESULT GetNamedPropertyMapping(
        LPCWSTR name, UINT* index,
        awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept;
    HRESULT GetPropertyCount(UINT* count) noexcept;
    HRESULT GetProperty(UINT index,
                        winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept;
    HRESULT GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept;
    HRESULT GetSourceCount(UINT* count) noexcept;

   private:
    // Preserve the default effect name from m417z's implementation.
    winrt::hstring m_name{L"GaussianBlurEffect"};
};

struct ColorMatrixEffect
    : winrt::implements<ColorMatrixEffect, wge::IGraphicsEffect,
                        wge::IGraphicsEffectSource,
                        awge::IGraphicsEffectD2D1Interop> {
    wge::IGraphicsEffectSource Source{nullptr};
    // 5x4, row-major: rows 0-3 scale R/G/B/A, row 4 is the offset.
    // Identity by default.
    std::array<float, 20> Matrix{1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                                1, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    D2D1_COLORMATRIX_ALPHA_MODE AlphaMode =
        D2D1_COLORMATRIX_ALPHA_MODE_PREMULTIPLIED;
    BOOL ClampOutput = FALSE;

    winrt::hstring Name() const noexcept { return m_name; }
    void Name(winrt::hstring name) { m_name = std::move(name); }

    HRESULT GetEffectId(GUID* id) noexcept;
    HRESULT GetNamedPropertyMapping(
        LPCWSTR name, UINT* index,
        awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept;
    HRESULT GetPropertyCount(UINT* count) noexcept;
    HRESULT GetProperty(UINT index,
                        winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept;
    HRESULT GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept;
    HRESULT GetSourceCount(UINT* count) noexcept;

   private:
    // Preserve the original effect name.
    winrt::hstring m_name{L"ColorMatrixEffect"};
};

struct CompositeEffect
    : winrt::implements<CompositeEffect, wge::IGraphicsEffect,
                        wge::IGraphicsEffectSource,
                        awge::IGraphicsEffectD2D1Interop> {
    std::vector<wge::IGraphicsEffectSource> Sources;
    D2D1_COMPOSITE_MODE Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;

    winrt::hstring Name() const noexcept { return m_name; }
    void Name(winrt::hstring name) { m_name = std::move(name); }

    HRESULT GetEffectId(GUID* id) noexcept;
    HRESULT GetNamedPropertyMapping(
        LPCWSTR name, UINT* index,
        awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept;
    HRESULT GetPropertyCount(UINT* count) noexcept;
    HRESULT GetProperty(UINT index,
                        winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept;
    HRESULT GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept;
    HRESULT GetSourceCount(UINT* count) noexcept;

   private:
    // The root composite retains its original default name.
    winrt::hstring m_name{L"CompositeEffect"};
};

struct FloodEffect : winrt::implements<FloodEffect, wge::IGraphicsEffect,
                                      wge::IGraphicsEffectSource,
                                      awge::IGraphicsEffectD2D1Interop> {
    winrt::Windows::UI::Color Color{};

    winrt::hstring Name() const noexcept { return m_name; }
    void Name(winrt::hstring name) { m_name = std::move(name); }

    HRESULT GetEffectId(GUID* id) noexcept;
    HRESULT GetNamedPropertyMapping(
        LPCWSTR name, UINT* index,
        awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept;
    HRESULT GetPropertyCount(UINT* count) noexcept;
    HRESULT GetProperty(UINT index,
                        winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept;
    HRESULT GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept;
    HRESULT GetSourceCount(UINT* count) noexcept;

   private:
    // Preserve the original effect name.
    winrt::hstring m_name{L"FloodEffect"};
};

struct BorderEffect : winrt::implements<BorderEffect, wge::IGraphicsEffect,
                                       wge::IGraphicsEffectSource,
                                       awge::IGraphicsEffectD2D1Interop> {
    wge::IGraphicsEffectSource Source{nullptr};
    D2D1_BORDER_EDGE_MODE ExtendX = D2D1_BORDER_EDGE_MODE_WRAP;
    D2D1_BORDER_EDGE_MODE ExtendY = D2D1_BORDER_EDGE_MODE_WRAP;

    winrt::hstring Name() const noexcept { return m_name; }
    void Name(winrt::hstring name) { m_name = std::move(name); }

    HRESULT GetEffectId(GUID* id) noexcept;
    HRESULT GetNamedPropertyMapping(
        LPCWSTR name, UINT* index,
        awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept;
    HRESULT GetPropertyCount(UINT* count) noexcept;
    HRESULT GetProperty(UINT index,
                        winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept;
    HRESULT GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept;
    HRESULT GetSourceCount(UINT* count) noexcept;

   private:
    // The border effect retains its original default name.
    winrt::hstring m_name{L"BorderEffect"};
};



namespace {

// The two casts every GetProperty / GetSource needs. Kept here so the reason
// lives in one place: cppwinrt's abi_t<T> and the MIDL ABI::...::T the SDK
// interop header declares are the same vtable under two C++ type names.
winrt::impl::abi_t<wf::IPropertyValue>* DetachPropertyValue(
    wf::IInspectable const& boxed) {
    return reinterpret_cast<winrt::impl::abi_t<wf::IPropertyValue>*>(
        boxed.as<winrt::impl::abi_t<wf::IPropertyValue>>().detach());
}

HRESULT DetachSource(wge::IGraphicsEffectSource const& source,
                     awge::IGraphicsEffectSource** out) {
    if (!source) {
        *out = nullptr;
        return E_BOUNDS;
    }
    // Preserve the actual source interface, not the object's canonical
    // IUnknown identity (which can have a different address/vtable).
    // copy_to_abi requires a null destination, even if our caller's out
    // parameter initially contains something else.
    void* raw = nullptr;
    winrt::copy_to_abi(source, raw);
    *out = static_cast<awge::IGraphicsEffectSource*>(raw);
    return S_OK;
}

}  // namespace

// ---------------------------------------------------------------- noise ----

// The noise brush is rendered on the XAML STA. Keep cache ownership on that
// thread, but never rely on a TLS destructor after apartment teardown.
struct NoiseCache {
    float density = std::numeric_limits<float>::quiet_NaN();
    wss::InMemoryRandomAccessStream stream{nullptr};
};

NoiseCache& GetThreadNoiseCache() noexcept {
    [[clang::no_destroy]] thread_local NoiseCache cache;
    return cache;
}

void ReleaseThreadNoiseCache() noexcept {
    auto& cache = GetThreadNoiseCache();
    cache.stream = nullptr;
    cache.density = std::numeric_limits<float>::quiet_NaN();
}

wss::IRandomAccessStream CreateNoiseStream(float density) {
    auto& cache = GetThreadNoiseCache();

    if (cache.stream && density == cache.density) {
        return cache.stream.CloneStream();
    }

    // 256x256 keeps tiled noise seams inconspicuous on OSD surfaces.
    constexpr int kSize = 256;
    constexpr DWORD kBpp = 32;
    constexpr DWORD kRowSize = kSize * (kBpp / 8);
    constexpr DWORD kDataSize = kRowSize * kSize;

    BITMAPFILEHEADER file_header{};
    file_header.bfType = 0x4D42;
    file_header.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + kDataSize;
    file_header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    BITMAPINFOHEADER info_header{};
    info_header.biSize = sizeof(BITMAPINFOHEADER);
    info_header.biWidth = kSize;
    info_header.biHeight = kSize;
    info_header.biPlanes = 1;
    info_header.biBitCount = kBpp;
    info_header.biSizeImage = kDataSize;

    // The OSD parser already bounds density; guard against bypassing it.
    if (!(density > 0.0f)) {
        density = 1.0f;
    }

    // Density shapes the grey distribution through a power curve; precompute
    // it over the 256 possible samples instead of calling pow 65536 times.
    const float safe_density = std::clamp(density, 0.001f, 1.0f);
    const float exponent = 1.0f / safe_density;
    std::array<uint8_t, 256> lut{};
    for (int i = 0; i < 256; ++i) {
        lut[static_cast<size_t>(i)] = static_cast<uint8_t>(
            std::pow(i / 255.0f, exponent) * 255.0f);
    }

    // Fixed seed: the noise must be identical on every thread and every run,
    // or two OSD surfaces would show visibly different grain.
    std::mt19937 rng(0);
    std::uniform_int_distribution<int> dist(0, 255);

    std::vector<uint8_t> pixels(kDataSize);
    for (size_t i = 0; i < pixels.size(); i += 4) {
        uint8_t grey = lut[static_cast<size_t>(dist(rng))];
        pixels[i] = grey;
        pixels[i + 1] = grey;
        pixels[i + 2] = grey;
        // Fully opaque; NoiseOpacity is applied downstream by the
        // ColorMatrixEffect, so the texture itself stays neutral.
        pixels[i + 3] = 0xFF;
    }

    wss::InMemoryRandomAccessStream stream;
    wss::DataWriter writer(stream);
    writer.WriteBytes(winrt::array_view<const uint8_t>(
        reinterpret_cast<const uint8_t*>(&file_header),
        reinterpret_cast<const uint8_t*>(&file_header) + sizeof(file_header)));
    writer.WriteBytes(winrt::array_view<const uint8_t>(
        reinterpret_cast<const uint8_t*>(&info_header),
        reinterpret_cast<const uint8_t*>(&info_header) + sizeof(info_header)));
    writer.WriteBytes(pixels);

    // In-memory writes normally finish inline. Never block this XAML STA if
    // that changes: let the brush's existing error path choose its fallback.
    // GetResults also propagates an already-completed Error/Canceled result,
    // so a failed write cannot poison the per-thread bitmap cache.
    auto store = writer.StoreAsync();
    if (store.Status() == wf::AsyncStatus::Started) {
        store.Cancel();
        winrt::throw_hresult(E_PENDING);
    }
    store.GetResults();
    writer.DetachStream();
    stream.Seek(0);

    cache.stream = stream;
    cache.density = density;
    return cache.stream.CloneStream();
}

// ------------------------------------------------------- GaussianBlur ------

HRESULT GaussianBlurEffect::GetEffectId(GUID* id) noexcept {
    if (!id) {
        return E_INVALIDARG;
    }
    *id = CLSID_D2D1GaussianBlur;
    return S_OK;
}

HRESULT GaussianBlurEffect::GetNamedPropertyMapping(
    LPCWSTR name, UINT* index,
    awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept {
    if (!name || !index || !mapping) {
        return E_INVALIDARG;
    }
    const std::wstring_view n(name);
    if (n == L"BlurAmount") {
        *index = D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    if (n == L"Optimization") {
        *index = D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    if (n == L"BorderMode") {
        *index = D2D1_GAUSSIANBLUR_PROP_BORDER_MODE;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    return E_INVALIDARG;
}

HRESULT GaussianBlurEffect::GetPropertyCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 3;
    return S_OK;
}

HRESULT GaussianBlurEffect::GetProperty(
    UINT index, winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept try {
    if (!value) {
        return E_INVALIDARG;
    }
    switch (index) {
        case D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION:
            *value = DetachPropertyValue(
                wf::PropertyValue::CreateSingle(BlurAmount));
            return S_OK;
        case D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION:
            *value = DetachPropertyValue(wf::PropertyValue::CreateUInt32(
                static_cast<uint32_t>(Optimization)));
            return S_OK;
        case D2D1_GAUSSIANBLUR_PROP_BORDER_MODE:
            *value = DetachPropertyValue(wf::PropertyValue::CreateUInt32(
                static_cast<uint32_t>(BorderMode)));
            return S_OK;
        default:
            return E_BOUNDS;
    }
} catch (...) {
    return winrt::to_hresult();
}

HRESULT GaussianBlurEffect::GetSource(
    UINT index, awge::IGraphicsEffectSource** source) noexcept try {
    if (!source) {
        return E_INVALIDARG;
    }
    if (index != 0) {
        *source = nullptr;
        return E_BOUNDS;
    }
    return DetachSource(Source, source);
} catch (...) {
    return winrt::to_hresult();
}

HRESULT GaussianBlurEffect::GetSourceCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 1;
    return S_OK;
}

// --------------------------------------------------------- ColorMatrix -----

HRESULT ColorMatrixEffect::GetEffectId(GUID* id) noexcept {
    if (!id) {
        return E_INVALIDARG;
    }
    *id = CLSID_D2D1ColorMatrix;
    return S_OK;
}

HRESULT ColorMatrixEffect::GetNamedPropertyMapping(
    LPCWSTR name, UINT* index,
    awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept {
    if (!name || !index || !mapping) {
        return E_INVALIDARG;
    }
    const std::wstring_view n(name);
    if (n == L"ColorMatrix") {
        *index = D2D1_COLORMATRIX_PROP_COLOR_MATRIX;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    if (n == L"AlphaMode") {
        *index = D2D1_COLORMATRIX_PROP_ALPHA_MODE;
        // DIRECT, not COLORMATRIX_ALPHA_MODE: we box a raw
        // D2D1_COLORMATRIX_ALPHA_MODE value ourselves (GetProperty below),
        // so no further mapping conversion is needed.
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    if (n == L"ClampOutput") {
        *index = D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    return E_INVALIDARG;
}

HRESULT ColorMatrixEffect::GetPropertyCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 3;
    return S_OK;
}

HRESULT ColorMatrixEffect::GetProperty(
    UINT index, winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept try {
    if (!value) {
        return E_INVALIDARG;
    }
    switch (index) {
        case D2D1_COLORMATRIX_PROP_COLOR_MATRIX:
            *value = DetachPropertyValue(wf::PropertyValue::CreateSingleArray(
                winrt::array_view<const float>(Matrix.data(),
                                               Matrix.data() + Matrix.size())));
            return S_OK;
        case D2D1_COLORMATRIX_PROP_ALPHA_MODE:
            *value = DetachPropertyValue(
                wf::PropertyValue::CreateUInt32(static_cast<uint32_t>(AlphaMode)));
            return S_OK;
        case D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT:
            *value = DetachPropertyValue(
                wf::PropertyValue::CreateBoolean(ClampOutput != FALSE));
            return S_OK;
        default:
            return E_BOUNDS;
    }
} catch (...) {
    return winrt::to_hresult();
}

HRESULT ColorMatrixEffect::GetSource(
    UINT index, awge::IGraphicsEffectSource** source) noexcept try {
    if (!source) {
        return E_INVALIDARG;
    }
    if (index != 0) {
        *source = nullptr;
        return E_BOUNDS;
    }
    return DetachSource(Source, source);
} catch (...) {
    return winrt::to_hresult();
}

HRESULT ColorMatrixEffect::GetSourceCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 1;
    return S_OK;
}

// ----------------------------------------------------------- Composite -----

HRESULT CompositeEffect::GetEffectId(GUID* id) noexcept {
    if (!id) {
        return E_INVALIDARG;
    }
    *id = CLSID_D2D1Composite;
    return S_OK;
}

HRESULT CompositeEffect::GetNamedPropertyMapping(
    LPCWSTR name, UINT* index,
    awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept {
    if (!name || !index || !mapping) {
        return E_INVALIDARG;
    }
    if (std::wstring_view(name) == L"Mode") {
        *index = D2D1_COMPOSITE_PROP_MODE;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    return E_INVALIDARG;
}

HRESULT CompositeEffect::GetPropertyCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 1;
    return S_OK;
}

HRESULT CompositeEffect::GetProperty(
    UINT index, winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept try {
    if (!value) {
        return E_INVALIDARG;
    }
    if (index != D2D1_COMPOSITE_PROP_MODE) {
        return E_BOUNDS;
    }
    *value = DetachPropertyValue(
        wf::PropertyValue::CreateUInt32(static_cast<uint32_t>(Mode)));
    return S_OK;
} catch (...) {
    return winrt::to_hresult();
}

HRESULT CompositeEffect::GetSource(
    UINT index, awge::IGraphicsEffectSource** source) noexcept try {
    if (!source) {
        return E_INVALIDARG;
    }
    if (index >= Sources.size()) {
        *source = nullptr;
        return E_BOUNDS;
    }
    return DetachSource(Sources[index], source);
} catch (...) {
    return winrt::to_hresult();
}

HRESULT CompositeEffect::GetSourceCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = static_cast<UINT>(Sources.size());
    return S_OK;
}

// --------------------------------------------------------------- Flood -----

HRESULT FloodEffect::GetEffectId(GUID* id) noexcept {
    if (!id) {
        return E_INVALIDARG;
    }
    *id = CLSID_D2D1Flood;
    return S_OK;
}

HRESULT FloodEffect::GetNamedPropertyMapping(
    LPCWSTR name, UINT* index,
    awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept {
    if (!name || !index || !mapping) {
        return E_INVALIDARG;
    }
    if (std::wstring_view(name) == L"Color") {
        *index = D2D1_FLOOD_PROP_COLOR;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    return E_INVALIDARG;
}

HRESULT FloodEffect::GetPropertyCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 1;
    return S_OK;
}

HRESULT FloodEffect::GetProperty(
    UINT index, winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept try {
    if (!value) {
        return E_INVALIDARG;
    }
    if (index != D2D1_FLOOD_PROP_COLOR) {
        return E_BOUNDS;
    }
    // Preserve the original straight (non-premultiplied) RGBA tint.
    const float rgba[4] = {Color.R / 255.0f, Color.G / 255.0f,
                           Color.B / 255.0f, Color.A / 255.0f};
    *value = DetachPropertyValue(wf::PropertyValue::CreateSingleArray(
        winrt::array_view<const float>(rgba, rgba + 4)));
    return S_OK;
} catch (...) {
    return winrt::to_hresult();
}

HRESULT FloodEffect::GetSource(UINT,
                               awge::IGraphicsEffectSource** source) noexcept {
    if (!source) {
        return E_INVALIDARG;
    }
    *source = nullptr;
    return E_BOUNDS;  // Flood generates; it has no input.
}

HRESULT FloodEffect::GetSourceCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 0;
    return S_OK;
}

// -------------------------------------------------------------- Border -----

HRESULT BorderEffect::GetEffectId(GUID* id) noexcept {
    if (!id) {
        return E_INVALIDARG;
    }
    *id = CLSID_D2D1Border;
    return S_OK;
}

HRESULT BorderEffect::GetNamedPropertyMapping(
    LPCWSTR name, UINT* index,
    awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept {
    if (!name || !index || !mapping) {
        return E_INVALIDARG;
    }
    const std::wstring_view n(name);
    if (n == L"ExtendX") {
        *index = D2D1_BORDER_PROP_EDGE_MODE_X;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    if (n == L"ExtendY") {
        *index = D2D1_BORDER_PROP_EDGE_MODE_Y;
        *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
        return S_OK;
    }
    return E_INVALIDARG;
}

HRESULT BorderEffect::GetPropertyCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 2;
    return S_OK;
}

HRESULT BorderEffect::GetProperty(
    UINT index, winrt::impl::abi_t<wf::IPropertyValue>** value) noexcept try {
    if (!value) {
        return E_INVALIDARG;
    }
    switch (index) {
        case D2D1_BORDER_PROP_EDGE_MODE_X:
            *value = DetachPropertyValue(
                wf::PropertyValue::CreateUInt32(static_cast<uint32_t>(ExtendX)));
            return S_OK;
        case D2D1_BORDER_PROP_EDGE_MODE_Y:
            *value = DetachPropertyValue(
                wf::PropertyValue::CreateUInt32(static_cast<uint32_t>(ExtendY)));
            return S_OK;
        default:
            return E_BOUNDS;
    }
} catch (...) {
    return winrt::to_hresult();
}

HRESULT BorderEffect::GetSource(
    UINT index, awge::IGraphicsEffectSource** source) noexcept try {
    if (!source) {
        return E_INVALIDARG;
    }
    if (index != 0) {
        *source = nullptr;
        return E_BOUNDS;
    }
    return DetachSource(Source, source);
} catch (...) {
    return winrt::to_hresult();
}

HRESULT BorderEffect::GetSourceCount(UINT* count) noexcept {
    if (!count) {
        return E_INVALIDARG;
    }
    *count = 1;
    return S_OK;
}


struct BrushSpec {
    float blurAmount = 18.0f;
    float tintSaturation = 1.0f;
    float tintLuminosityOpacity = 0.0f;
    float noiseOpacity = 0.0f;
    float noiseDensity = 1.0f;
    winrt::Windows::UI::Color tint{0, 0, 0, 0};
    winrt::Windows::UI::Color fallback{255, 35, 35, 39};
    bool hasFallback = false;
};
bool ShouldFallback(const BrushSpec& spec) {
    // m417z XamlBlurBrush: no fallback unless FallbackColor was requested.
    if (!spec.hasFallback) return false;

    // EnergySaverState is authoritative for "Always use energy saver" on
    // Windows 11 24H2+, unlike WinRT/Win32 power status on those builds.
    DWORD saverState = 0;
    DWORD bytes = sizeof(saverState);
    bool saverActive = RegGetValueW(
        HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power",
        L"EnergySaverState", RRF_RT_REG_DWORD, nullptr,
        &saverState, &bytes) == ERROR_SUCCESS && saverState == 1;

    if (!saverActive) {
        SYSTEM_POWER_STATUS power{};
        if (GetSystemPowerStatus(&power) && power.SystemStatusFlag == 1)
            saverActive = true;
    }

    bool effectsDisabled = false;
    try {
        winrt::Windows::UI::ViewManagement::UISettings uiSettings;
        effectsDisabled = !uiSettings.AdvancedEffectsEnabled();
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"Fluent OSD: AdvancedEffectsEnabled unavailable (0x%08lX)",
            static_cast<unsigned long>(ex.code()));
    } catch (...) {
        Wh_Log(L"Fluent OSD: AdvancedEffectsEnabled query failed");
    }

    return saverActive || effectsDisabled;
}
class WindhawkBlurBrush : public media::XamlCompositionBrushBaseT<WindhawkBlurBrush> {
public:
    WindhawkBlurBrush(wx::UIElement const& owner, BrushSpec settings)
        : compositor(hosting::ElementCompositionPreview::GetElementVisual(
              owner).Compositor()), spec(std::move(settings)) {}
    void OnConnected() {
        if (CompositionBrush()) return;
        try {
            wuc::CompositionBrush result{nullptr};
            if (!ShouldFallback(spec)) {
                try { result = CreateEffectBrush(); }
                catch (const winrt::hresult_error& ex) {
                    Wh_Log(L"WindhawkBlur effect failed: 0x%08lX",
                        static_cast<unsigned long>(ex.code()));
                } catch (...) {
                    Wh_Log(L"WindhawkBlur effect construction failed");
                }
            }
            if (!result) result = compositor.CreateColorBrush(
                spec.hasFallback ? spec.fallback : spec.tint);
            CompositionBrush(result);
        } catch (...) {
            // Never throw across an XAML composition callback in Explorer.
        }
    }
    void OnDisconnected() {
        try {
            auto old = CompositionBrush();
            CompositionBrush(nullptr);
            if (old) old.Close();
        } catch (...) {}
    }
private:
    wuc::CompositionBrush CreateEffectBrush();
    wuc::Compositor compositor{nullptr};
    BrushSpec spec;
};
wuc::CompositionBrush WindhawkBlurBrush::CreateEffectBrush()
{
    auto backdropBrush = compositor.CreateBackdropBrush();

    // Rec. 709 luma coefficients, used for saturation and luminosity.
    constexpr float kLumaR = 0.2126f;
    constexpr float kLumaG = 0.7152f;
    constexpr float kLumaB = 0.0722f;

    // 1. Blur
    auto blurEffect = winrt::make_self<GaussianBlurEffect>();
    blurEffect->Source = wuc::CompositionEffectSourceParameter(L"backdrop");
    blurEffect->BlurAmount = spec.blurAmount;
    blurEffect->Name(L"BlurEffect");

    wge::IGraphicsEffectSource topOfStack = *blurEffect;

    // 2. Saturation (optional)
    if (spec.tintSaturation != 1.0f)
    {
        float s = (std::max)(spec.tintSaturation, 0.0f);
        float invS = 1.0f - s;

        auto satMatrix = winrt::make_self<ColorMatrixEffect>();
        satMatrix->Source = topOfStack;

        // Standard saturation matrix: lerp between luminance and identity.
        auto& m = satMatrix->Matrix;
        m[0]  = invS * kLumaR + s; m[1]  = invS * kLumaR;     m[2]  = invS * kLumaR;     m[3]  = 0.0f;
        m[4]  = invS * kLumaG;     m[5]  = invS * kLumaG + s; m[6]  = invS * kLumaG;     m[7]  = 0.0f;
        m[8]  = invS * kLumaB;     m[9]  = invS * kLumaB;     m[10] = invS * kLumaB + s; m[11] = 0.0f;
        m[12] = 0.0f;              m[13] = 0.0f;              m[14] = 0.0f;              m[15] = 1.0f;

        satMatrix->Name(L"SaturationEffect");
        topOfStack = *satMatrix;
    }

    // 3. Luminosity (optional) - shifts pixel luminance towards the tint's
    // luminance, blended by the opacity factor.
    if (spec.tintLuminosityOpacity > 0.0f)
    {
        float op = std::clamp(spec.tintLuminosityOpacity, 0.0f, 1.0f);

        float tintLum = (spec.tint.R / 255.0f) * kLumaR +
                        (spec.tint.G / 255.0f) * kLumaG +
                        (spec.tint.B / 255.0f) * kLumaB;

        auto lumMatrix = winrt::make_self<ColorMatrixEffect>();
        lumMatrix->Source = topOfStack;

        auto& m = lumMatrix->Matrix;
        m[0]  = 1.0f - (kLumaR * op); m[1]  = -(kLumaR * op);       m[2]  = -(kLumaR * op);       m[3]  = 0.0f;
        m[4]  = -(kLumaG * op);       m[5]  = 1.0f - (kLumaG * op); m[6]  = -(kLumaG * op);       m[7]  = 0.0f;
        m[8]  = -(kLumaB * op);       m[9]  = -(kLumaB * op);       m[10] = 1.0f - (kLumaB * op); m[11] = 0.0f;
        m[12] = 0.0f;                 m[13] = 0.0f;                 m[14] = 0.0f;                 m[15] = 1.0f;
        m[16] = tintLum * op;         m[17] = tintLum * op;         m[18] = tintLum * op;         m[19] = 0.0f;

        lumMatrix->Name(L"LuminosityBlend");
        topOfStack = *lumMatrix;
    }

    // 4. Noise overlay (optional) - procedural tiled noise with adjustable
    // density and opacity.
    wuc::CompositionSurfaceBrush noiseBrush{nullptr};
    if (spec.noiseOpacity > 0.0f)
    {
        float density = spec.noiseDensity;

        auto stream = CreateNoiseStream(density);
        auto surface =
            media::LoadedImageSurface::StartLoadFromStream(stream);
        noiseBrush = compositor.CreateSurfaceBrush(surface);
        noiseBrush.Stretch(wuc::CompositionStretch::None);

        // Tile via border effect (wrap mode).
        auto borderEffect = winrt::make_self<BorderEffect>();
        borderEffect->Source =
            wuc::CompositionEffectSourceParameter(L"NoiseSource");

        // Scale all channels by opacity for premultiplied blending.
        float nOp = std::clamp(spec.noiseOpacity, 0.0f, 1.0f);

        auto opacityEffect = winrt::make_self<ColorMatrixEffect>();
        opacityEffect->Source = *borderEffect;
        // Matrix: Scale all channels by opacity (for premultiplied blending).
        opacityEffect->Matrix[0] = nOp;
        opacityEffect->Matrix[5] = nOp;
        opacityEffect->Matrix[10] = nOp;
        opacityEffect->Matrix[15] = nOp;
        opacityEffect->Name(L"NoiseOpacityEffect");

        // Composite noise over the current stack.
        auto noiseComposite = winrt::make_self<CompositeEffect>();
        noiseComposite->Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
        noiseComposite->Sources.push_back(topOfStack);
        noiseComposite->Sources.push_back(*opacityEffect);
        noiseComposite->Name(L"NoiseComposite");
        topOfStack = *noiseComposite;
    }

    // 5. Tint (flood color composited over the stack).
    auto floodEffect = winrt::make_self<FloodEffect>();
    floodEffect->Color = spec.tint;
    floodEffect->Name(L"FloodEffect");

    auto compositeEffect = winrt::make_self<CompositeEffect>();
    compositeEffect->Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
    compositeEffect->Sources.push_back(topOfStack);
    compositeEffect->Sources.push_back(*floodEffect);

    auto factory = compositor.CreateEffectFactory(*compositeEffect);
    auto brush = factory.CreateBrush();

    brush.SetSourceParameter(L"backdrop", backdropBrush);

    // Bind the noise brush if we created one.
    if (noiseBrush)
    {
        brush.SetSourceParameter(L"NoiseSource", noiseBrush);
    }

    return brush;
}


} // namespace osd_blur

// Only a tiny, bounded, non-executable subset of Brush markup is accepted.
// No XML entities, namespaces, attached properties, markup extensions or
// arbitrary XAML objects may enter Explorer's XAML STA.
struct BrushTag {
    std::wstring name;
    std::vector<std::pair<std::wstring, std::wstring>> attrs;
    bool closing = false, selfClosing = false;
};
bool BrushWhiteSpace(wchar_t c) {
    return c == L' ' || c == L'\t' || c == L'\r' || c == L'\n';
}
void SkipBrushSpaces(const std::wstring& input, size_t& pos) {
    while (pos < input.size() && BrushWhiteSpace(input[pos])) ++pos;
}
bool IsBrushLetter(wchar_t c) {
    return (c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z');
}
bool ReadBrushTag(const std::wstring& input, size_t& pos, BrushTag& tag) {
    SkipBrushSpaces(input, pos);
    if (pos >= input.size() || input[pos++] != L'<') return false;
    if (pos < input.size() && input[pos] == L'/') {
        tag.closing = true;
        ++pos;
    }
    const size_t nameStart = pos;
    while (pos < input.size() && IsBrushLetter(input[pos])) ++pos;
    if (pos == nameStart) return false;
    tag.name = input.substr(nameStart, pos - nameStart);
    if (tag.closing) {
        SkipBrushSpaces(input, pos);
        if (pos >= input.size() || input[pos++] != L'>') return false;
        return true;
    }
    while (pos < input.size()) {
        const size_t beforeSpace = pos;
        SkipBrushSpaces(input, pos);
        if (pos + 1 < input.size() &&
            input[pos] == L'/' && input[pos + 1] == L'>') {
            pos += 2;
            tag.selfClosing = true;
            return true;
        }
        if (pos < input.size() && input[pos] == L'>') {
            ++pos;
            return true;
        }
        if (beforeSpace == pos || tag.attrs.size() >= 12 ||
            pos >= input.size() || !IsBrushLetter(input[pos]))
            return false;
        const size_t keyStart = pos;
        while (pos < input.size() && IsBrushLetter(input[pos])) ++pos;
        const std::wstring key = input.substr(keyStart, pos - keyStart);
        SkipBrushSpaces(input, pos);
        if (pos >= input.size() || input[pos++] != L'=') return false;
        SkipBrushSpaces(input, pos);
        if (pos >= input.size() ||
            (input[pos] != L'"' && input[pos] != L'\'')) return false;
        const wchar_t quote = input[pos++];
        const size_t valueStart = pos;
        while (pos < input.size() && input[pos] != quote) {
            if (input[pos] == L'<' || input[pos] == L'>' ||
                input[pos] == L'&' || input[pos] == L'{' ||
                input[pos] == L'}') return false;
            ++pos;
        }
        if (pos >= input.size()) return false;
        std::wstring value = input.substr(valueStart, pos - valueStart);
        ++pos;
        for (const auto& existing : tag.attrs)
            if (existing.first == key) return false;
        tag.attrs.emplace_back(key, std::move(value));
    }
    return false;
}
bool ParseBrushFraction(const std::wstring& text, double& value) {
    if (text.empty() || text.size() > 16) return false;
    double n = 0.0, factor = 1.0;
    bool seenDigit = false, seenDot = false;
    for (wchar_t c : text) {
        if (c == L'.' && !seenDot) { seenDot = true; continue; }
        if (c < L'0' || c > L'9') return false;
        seenDigit = true;
        if (!seenDot) n = n * 10.0 + (c - L'0');
        else { factor *= 0.1; n += (c - L'0') * factor; }
    }
    if (!seenDigit || n < 0.0 || n > 1.0) return false;
    value = n;
    return true;
}
bool ParseBrushNumber(const std::wstring& input, double min, double max,
                      float& value) {
    if (input.empty() || input.size() > 16) return false;
    double num = 0.0, fraction = 1.0;
    bool dot = false, digit = false;
    for (wchar_t c : input) {
        if (c == L'.' && !dot) { dot = true; continue; }
        if (c < L'0' || c > L'9') return false;
        digit = true;
        if (!dot) num = num * 10.0 + (c - L'0');
        else { fraction *= 0.1; num += (c - L'0') * fraction; }
    }
    if (!digit || num < min || num > max) return false;
    value = static_cast<float>(num);
    return true;
}
// XAML gradient points may extend outside 0..1 or use absolute coordinates.
// Keep parsing locale-independent and bounded to avoid untrusted numeric data
// becoming NaN, infinity or enormous Composition geometry.
bool ParseBrushCoordinate(const std::wstring& text, double& value) {
    if (text.empty() || text.size() > 20) return false;
    size_t pos = 0;
    double sign = 1.0;
    if (text[pos] == L'-' || text[pos] == L'+') {
        sign = text[pos] == L'-' ? -1.0 : 1.0;
        if (++pos == text.size()) return false;
    }
    double num = 0.0, scale = 1.0;
    bool dot = false, digit = false;
    for (; pos < text.size(); ++pos) {
        const wchar_t c = text[pos];
        if (c == L'.' && !dot) { dot = true; continue; }
        if (c < L'0' || c > L'9') return false;
        digit = true;
        if (!dot) num = num * 10.0 + (c - L'0');
        else { scale *= 0.1; num += (c - L'0') * scale; }
        if (num > 4096.0) return false;
    }
    if (!digit) return false;
    value = num * sign;
    return true;
}
bool ParseBrushPoint(const std::wstring& text,
                     winrt::Windows::Foundation::Point& result) {
    const size_t comma = text.find(L',');
    if (comma == std::wstring::npos || comma == 0 ||
        comma + 1 >= text.size() ||
        text.find(L',', comma + 1) != std::wstring::npos) return false;
    double x = 0.0, y = 0.0;
    if (!ParseBrushCoordinate(text.substr(0, comma), x) ||
        !ParseBrushCoordinate(text.substr(comma + 1), y)) return false;
    result = {static_cast<float>(x), static_cast<float>(y)};
    return true;
}
bool ParseBrushColor(const Snapshot& state, const std::wstring& text,
                     winrt::Windows::UI::Color& color) {
    DWORD rgb = 0;
    BYTE alpha = 255;
    if (text == L"$mainColor") rgb = state.background;
    else if (text == L"$accentColor") rgb = state.accent;
    else if (text == L"$textColor") rgb = state.text;
    else if (text == L"$trackColor") rgb = state.track;
    else {
        // Bounded set of XAML named colors used by Styler-style themes.
        // ThemeResource/markup expressions deliberately remain disallowed.
        static constexpr std::pair<PCWSTR, uint32_t> kNamedColors[] = {
            {L"Transparent", 0x00000000},
            {L"Black", 0xFF000000},
            {L"White", 0xFFFFFFFF},
            {L"Red", 0xFFFF0000},
            {L"Green", 0xFF008000},
            {L"Blue", 0xFF0000FF},
            {L"Yellow", 0xFFFFFF00},
            {L"Lime", 0xFF00FF00},
            {L"LimeGreen", 0xFF32CD32},
            {L"Cyan", 0xFF00FFFF},
            {L"Aqua", 0xFF00FFFF},
            {L"Magenta", 0xFFFF00FF},
            {L"Fuchsia", 0xFFFF00FF},
            {L"Orange", 0xFFFFA500},
            {L"Purple", 0xFF800080},
            {L"Gray", 0xFF808080},
            {L"Silver", 0xFFC0C0C0},
            {L"DarkGray", 0xFFA9A9A9},
            {L"LightGray", 0xFFD3D3D3},
            {L"Navy", 0xFF000080},
            {L"Teal", 0xFF008080},
            {L"Olive", 0xFF808000},
            {L"Maroon", 0xFF800000},
            {L"DarkBlue", 0xFF00008B},
        };
        bool named = false;
        uint32_t packed = 0;
        for (const auto& entry : kNamedColors) {
            if (_wcsicmp(text.c_str(), entry.first) == 0) {
                packed = entry.second;
                named = true;
                break;
            }
        }
        if (named) {
            alpha = static_cast<BYTE>(packed >> 24);
        } else {
            if (text.empty() || text[0] != L'#' ||
                (text.size() != 7 && text.size() != 9)) return false;
            for (size_t i = 1; i < text.size(); ++i) {
                const wchar_t c = text[i];
                const int digit = c >= L'0' && c <= L'9' ? c - L'0' :
                    c >= L'a' && c <= L'f' ? c - L'a' + 10 :
                    c >= L'A' && c <= L'F' ? c - L'A' + 10 : -1;
                if (digit < 0) return false;
                packed = (packed << 4) | static_cast<uint32_t>(digit);
            }
            if (text.size() == 9) alpha = static_cast<BYTE>(packed >> 24);
        }
        rgb = packed & 0xFFFFFF;
    }
    color = {alpha, static_cast<BYTE>(rgb >> 16),
             static_cast<BYTE>(rgb >> 8), static_cast<BYTE>(rgb)};
    return true;
}
imaging::WriteableBitmap LoadLocalBackgroundImage(const std::wstring& path);
bool TryBuildBackgroundBrush(const Snapshot& state,
                             const controls::Border& card,
                             media::Brush& output) {
    const std::wstring& input = state.backgroundMarkup;
    if (input.empty() || input.size() > 4096) return false;
    size_t pos = 0;
    BrushTag root;
    if (!ReadBrushTag(input, pos, root) || root.closing) return false;
    if (root.name == L"SolidColorBrush") {
        if (!root.selfClosing) return false;
        winrt::Windows::UI::Color color{};
        bool hasColor = false;
        double opacity = 1.0;
        for (const auto& attr : root.attrs) {
            if (attr.first == L"Color") {
                if (!ParseBrushColor(state, attr.second, color)) return false;
                hasColor = true;
            } else if (attr.first == L"Opacity") {
                if (!ParseBrushFraction(attr.second, opacity)) return false;
            } else return false;
        }
        SkipBrushSpaces(input, pos);
        if (!hasColor || pos != input.size()) return false;
        auto brush = media::SolidColorBrush(color);
        brush.Opacity(opacity);
        output = brush;
        return true;
    }
    if (root.name == L"AcrylicBrush") {
        if (!root.selfClosing) return false;
        SkipBrushSpaces(input, pos);
        if (pos != input.size()) return false;
        auto tint = winrt::Windows::UI::Color{255,
            static_cast<BYTE>(state.background >> 16),
            static_cast<BYTE>(state.background >> 8),
            static_cast<BYTE>(state.background)};
        auto fallback = tint;
        double opacity = 1.0, tintOpacity = 1.0, luminosityOpacity = 0.0;
        bool hasFallback = false, forceFallback = false;
        bool hasLuminosityOpacity = false;
        for (const auto& attr : root.attrs) {
            if (attr.first == L"TintColor") {
                if (!ParseBrushColor(state, attr.second, tint)) return false;
            } else if (attr.first == L"FallbackColor") {
                if (!ParseBrushColor(state, attr.second, fallback))
                    return false;
                hasFallback = true;
            } else if (attr.first == L"TintOpacity") {
                if (!ParseBrushFraction(attr.second, tintOpacity))
                    return false;
            } else if (attr.first == L"TintLuminosityOpacity") {
                if (!ParseBrushFraction(attr.second, luminosityOpacity))
                    return false;
                hasLuminosityOpacity = true;
            } else if (attr.first == L"Opacity") {
                if (!ParseBrushFraction(attr.second, opacity)) return false;
            } else if (attr.first == L"BackgroundSource") {
                // HostBackdrop belongs to the host/window backdrop surface.
                // Nested Grid layers cannot assume ownership of that surface.
                // Never silently map HostBackdrop to another backdrop mode.
                if (attr.second == L"HostBackdrop") {
                    Wh_Log(L"Fluent OSD/XAML: HostBackdrop unsupported in "
                           L"layered native AcrylicBrush; layer rejected");
                    return false;
                }
                if (attr.second != L"Backdrop") return false;
            } else if (attr.first == L"AlwaysUseFallback") {
                if (attr.second == L"True" || attr.second == L"true")
                    forceFallback = true;
                else if (attr.second == L"False" || attr.second == L"false")
                    forceFallback = false;
                else return false;
            } else return false;
        }

        // Native Windows.UI.Xaml.Media.AcrylicBrush. Backdrop sampling in
        // a non-activating Island does not guarantee window-external blur
        // or post-processing of already composed sibling layers.
        // Preserve native fallback handling rather than synthesizing blur.
        if (!hasFallback) fallback = tint;
        auto brush = media::AcrylicBrush();
        brush.BackgroundSource(media::AcrylicBackgroundSource::Backdrop);
        brush.TintColor(tint);
        brush.TintOpacity(tintOpacity);
        if (hasLuminosityOpacity)
            brush.TintLuminosityOpacity(
                winrt::box_value(luminosityOpacity)
                    .as<winrt::Windows::Foundation::IReference<double>>());
        brush.FallbackColor(fallback);
        brush.AlwaysUseFallback(forceFallback);
        brush.Opacity(opacity);
        output = brush;

        // Construction does not prove that Windows rendered the blur effect.
        // Windows may choose fallback depending on host and system policy.
        Wh_Log(L"Fluent OSD/XAML: native AcrylicBrush constructed "
               L"(source=Backdrop, forcedFallback=%d)",
               forceFallback ? 1 : 0);
        return true;
    }
    if (root.name == L"ImageBrush") {
        if (!root.selfClosing) return false;
        SkipBrushSpaces(input, pos);
        if (pos != input.size()) return false;
        std::wstring path;
        double opacity = 1.0;
        auto stretch = media::Stretch::UniformToFill;
        auto alignX = media::AlignmentX::Center;
        auto alignY = media::AlignmentY::Center;
        for (const auto& attr : root.attrs) {
            if (attr.first == L"ImageSource") {
                path = attr.second;
            } else if (attr.first == L"Opacity") {
                if (!ParseBrushFraction(attr.second, opacity)) return false;
            } else if (attr.first == L"Stretch") {
                if (attr.second == L"UniformToFill")
                    stretch = media::Stretch::UniformToFill;
                else if (attr.second == L"Uniform")
                    stretch = media::Stretch::Uniform;
                else if (attr.second == L"Fill")
                    stretch = media::Stretch::Fill;
                else if (attr.second == L"None")
                    stretch = media::Stretch::None;
                else return false;
            } else if (attr.first == L"AlignmentX") {
                if (attr.second == L"Left") alignX = media::AlignmentX::Left;
                else if (attr.second == L"Center")
                    alignX = media::AlignmentX::Center;
                else if (attr.second == L"Right")
                    alignX = media::AlignmentX::Right;
                else return false;
            } else if (attr.first == L"AlignmentY") {
                if (attr.second == L"Top") alignY = media::AlignmentY::Top;
                else if (attr.second == L"Center")
                    alignY = media::AlignmentY::Center;
                else if (attr.second == L"Bottom")
                    alignY = media::AlignmentY::Bottom;
                else return false;
            } else return false;
        }
        if (path.empty()) return false;
        auto pixels = LoadLocalBackgroundImage(path);
        if (!pixels) return false;
        auto brush = media::ImageBrush();
        brush.ImageSource(pixels);
        brush.Stretch(stretch);
        brush.AlignmentX(alignX);
        brush.AlignmentY(alignY);
        brush.Opacity(opacity);
        output = brush;
        return true;
    }
    if (root.name == L"WindhawkBlur") {
        if (!root.selfClosing) return false;
        SkipBrushSpaces(input, pos);
        if (pos != input.size()) return false;
        osd_blur::BrushSpec settings;
        settings.tint = {255, static_cast<BYTE>(state.background >> 16),
                         static_cast<BYTE>(state.background >> 8),
                         static_cast<BYTE>(state.background)};
        settings.fallback = settings.tint;
        double opacity = 1.0, tintOpacity = -1.0;
        for (const auto& attr : root.attrs) {
            if (attr.first == L"BlurAmount") {
                if (!ParseBrushNumber(attr.second, 0.0, 80.0,
                    settings.blurAmount)) return false;
            } else if (attr.first == L"TintColor") {
                if (!ParseBrushColor(state, attr.second, settings.tint))
                    return false;
            } else if (attr.first == L"TintOpacity") {
                if (!ParseBrushFraction(attr.second, tintOpacity)) return false;
            } else if (attr.first == L"TintLuminosityOpacity") {
                if (!ParseBrushNumber(attr.second, 0.0, 1.0,
                    settings.tintLuminosityOpacity)) return false;
            } else if (attr.first == L"TintSaturation") {
                if (!ParseBrushNumber(attr.second, 0.0, 4.0,
                    settings.tintSaturation)) return false;
            } else if (attr.first == L"NoiseOpacity") {
                if (!ParseBrushNumber(attr.second, 0.0, 1.0,
                    settings.noiseOpacity)) return false;
            } else if (attr.first == L"NoiseDensity") {
                if (!ParseBrushNumber(attr.second, 0.001, 1.0,
                    settings.noiseDensity)) return false;
            } else if (attr.first == L"FallbackColor") {
                if (!ParseBrushColor(state, attr.second, settings.fallback))
                    return false;
                settings.hasFallback = true;
            } else if (attr.first == L"Opacity") {
                if (!ParseBrushFraction(attr.second, opacity)) return false;
            } else return false;
        }
        if (tintOpacity >= 0.0)
            settings.tint.A = static_cast<BYTE>(
                std::lround(tintOpacity * 255.0));
        if (!settings.hasFallback) settings.fallback = settings.tint;
        if (!card) return false;
        auto value = winrt::make<osd_blur::WindhawkBlurBrush>(card, settings)
                         .as<media::Brush>();
        value.Opacity(opacity);
        output = value;
        return true;
    }
    if (root.name != L"LinearGradientBrush" || root.selfClosing)
        return false;
    auto brush = media::LinearGradientBrush();
    winrt::Windows::Foundation::Point start{0.0f, 0.0f};
    winrt::Windows::Foundation::Point end{1.0f, 1.0f};
    double opacity = 1.0;
    auto spread = media::GradientSpreadMethod::Pad;
    for (const auto& attr : root.attrs) {
        if (attr.first == L"StartPoint") {
            if (!ParseBrushPoint(attr.second, start)) return false;
        } else if (attr.first == L"EndPoint") {
            if (!ParseBrushPoint(attr.second, end)) return false;
        } else if (attr.first == L"Opacity") {
            if (!ParseBrushFraction(attr.second, opacity)) return false;
        } else if (attr.first == L"SpreadMethod") {
            if (attr.second == L"Pad")
                spread = media::GradientSpreadMethod::Pad;
            else if (attr.second == L"Reflect")
                spread = media::GradientSpreadMethod::Reflect;
            else if (attr.second == L"Repeat")
                spread = media::GradientSpreadMethod::Repeat;
            else return false;
        } else if (attr.first == L"MappingMode") {
            if (attr.second == L"RelativeToBoundingBox")
                brush.MappingMode(media::BrushMappingMode::RelativeToBoundingBox);
            else if (attr.second == L"Absolute")
                brush.MappingMode(media::BrushMappingMode::Absolute);
            else return false;
        } else if (attr.first == L"ColorInterpolationMode") {
            if (attr.second == L"SRgbLinearInterpolation")
                brush.ColorInterpolationMode(
                    media::ColorInterpolationMode::SRgbLinearInterpolation);
            else if (attr.second == L"ScRgbLinearInterpolation")
                brush.ColorInterpolationMode(
                    media::ColorInterpolationMode::ScRgbLinearInterpolation);
            else return false;
        } else return false;
    }
    int count = 0;
    for (;;) {
        BrushTag child;
        if (!ReadBrushTag(input, pos, child)) return false;
        if (child.closing) {
            if (child.name != L"LinearGradientBrush" || count < 2)
                return false;
            break;
        }
        if (!child.selfClosing || child.name != L"GradientStop" ||
            count >= 12) return false;
        winrt::Windows::UI::Color color{};
        double offset = 0.0;
        bool hasColor = false, hasOffset = false;
        for (const auto& attr : child.attrs) {
            if (attr.first == L"Color") {
                if (!ParseBrushColor(state, attr.second, color))
                    return false;
                hasColor = true;
            } else if (attr.first == L"Offset") {
                // Native XAML permits stops outside 0..1 (Styler themes do
                // use this); keep a finite bounded range.
                float bounded = 0.0f;
                if (!ParseBrushNumber(attr.second, 0.0, 4.0, bounded))
                    return false;
                offset = bounded;
                hasOffset = true;
            } else return false;
        }
        if (!hasColor || !hasOffset) return false;
        auto stop = media::GradientStop();
        stop.Color(color);
        stop.Offset(offset);
        brush.GradientStops().Append(stop);
        ++count;
    }
    SkipBrushSpaces(input, pos);
    if (pos != input.size()) return false;
    brush.StartPoint(start);
    brush.EndPoint(end);
    brush.SpreadMethod(spread);
    brush.Opacity(opacity);
    output = brush;
    return true;
}
// The Viewbox remains last; all brush layers belong below it in the Grid.
// Disconnect custom Composition brushes before removing the XAML visuals.
void ClearBackgroundLayers(State& state) {
    if (!state.backgroundStack) return;
    auto children = state.backgroundStack.Children();
    for (auto& layer : state.backgroundLayerCards) {
        try { layer.Background(nullptr); } catch (...) {}
    }
    const size_t count = state.backgroundLayerCards.size();
    for (size_t i = 0; i < count && children.Size() > 1; ++i)
        children.RemoveAt(0);
    state.backgroundLayerCards.clear();
}
void SetBackgroundLayerRadius(State& state, double radius) {
    radius = std::clamp(radius, 0.0, 34.0);
    for (auto& layer : state.backgroundLayerCards)
        layer.CornerRadius(wx::CornerRadius{
            radius, radius, radius, radius});
}
void ApplyBackground(State& state, const Snapshot& snapshot) {
    if (state.backgroundCached &&
        state.cachedLayeredBackground == snapshot.layeredBackground &&
        state.cachedBackground == snapshot.background &&
        state.cachedBackgroundAlpha == snapshot.backgroundAlpha &&
        state.cachedAccent == snapshot.accent &&
        state.cachedText == snapshot.text &&
        state.cachedTrack == snapshot.track &&
        osd_model::SameBrushLayers(
            state.cachedBackgroundLayers, snapshot.backgroundLayers))
        return;
    ClearBackgroundLayers(state);
    bool valid = false;
    if (snapshot.layeredBackground && state.backgroundStack) {
        state.card.Background(Brush(0, 0));
        auto children = state.backgroundStack.Children();
        for (const auto& spec : snapshot.backgroundLayers) {
            if (!spec.enabled || spec.markup.empty()) continue;
            controls::Border layer;
            layer.IsHitTestVisible(false);
            layer.HorizontalAlignment(wx::HorizontalAlignment::Stretch);
            layer.VerticalAlignment(wx::VerticalAlignment::Stretch);
            // UI composite opacity is applied after brush rendering.
            // For blur brushes use 100% to avoid unfiltered content bleeding
            // through this entire XAML layer. Tint opacity is independent.
            layer.Opacity(std::clamp(spec.opacity, 0, 100) / 100.0);
            const double radius =
                std::clamp(static_cast<double>(snapshot.cornerRadius),
                           0.0, 34.0);
            layer.CornerRadius(wx::CornerRadius{
                radius, radius, radius, radius});
            // Attach before Composition creation so ElementCompositionPreview
            // can resolve the correct XAML Island compositor.
            children.InsertAt(children.Size() - 1, layer);
            Snapshot single = snapshot;
            single.backgroundMarkup = spec.markup;
            media::Brush layerBrush{nullptr};
            bool built = false;
            try {
                built = TryBuildBackgroundBrush(single, layer, layerBrush);
                if (built) layer.Background(layerBrush);
            } catch (const winrt::hresult_error& ex) {
                Wh_Log(L"Fluent OSD: background layer failed: 0x%08lX",
                       static_cast<unsigned long>(ex.code()));
                built = false;
            } catch (...) {
                Wh_Log(L"Fluent OSD: background layer creation failed");
                built = false;
            }
            if (built) {
                state.backgroundLayerCards.push_back(layer);
                valid = true;
            } else {
                // A bad upper layer must not hide lower, valid layers.
                try { layer.Background(nullptr); } catch (...) {}
                children.RemoveAt(children.Size() - 2);
                Wh_Log(L"Fluent OSD: invalid background layer skipped");
            }
        }
        Wh_Log(L"Fluent OSD/XAML: layer render configured=%u built=%u",
               static_cast<unsigned>(snapshot.backgroundLayers.size()),
               static_cast<unsigned>(state.backgroundLayerCards.size()));
    }
    if (!valid)
        state.card.Background(Brush(snapshot.background, snapshot.backgroundAlpha));
    state.backgroundCached = true;
    state.cachedLayeredBackground = snapshot.layeredBackground;
    state.cachedBackground = snapshot.background;
    state.cachedBackgroundAlpha = snapshot.backgroundAlpha;
    state.cachedAccent = snapshot.accent;
    state.cachedText = snapshot.text;
    state.cachedTrack = snapshot.track;
    state.cachedBackgroundLayers = snapshot.backgroundLayers;
}

void DrawSnapshot(State&, const Snapshot&);
void DrawStatusSnapshot(State&, const Snapshot&);
void DrawClipboardImageSnapshot(State&, const Snapshot&);
imaging::WriteableBitmap BitmapFromPixels(
    uint32_t, uint32_t, const std::vector<uint8_t>&, uint32_t maxSide = 320);
void DrawMixerSnapshot(State&, const Snapshot&);
[[maybe_unused]] void ToggleNoticeDetails(State&);
bool PointerInsideHost(const State&);

// All audio/WMI/DDC writes stay on the original Explorer OSD UI thread.
// The STA handles pointer geometry and sends only bounded POD commands.
void SendInput(State& state, InputAction action, int value) {
    if (state.viewOnly || GetXamlState().lifecycle.IsStopping() || !state.current.receiver) return;
    osd_control::Submit(
        osd_control::Build(state.current, action, value),
        state.current.receiver);
}
void SendMixerInput(State& state, InputAction action, int index,
                    int value = 0) {
    if (state.viewOnly || GetXamlState().lifecycle.IsStopping() || !state.current.receiver) return;
    osd_control::Submit(
        osd_control::BuildMixer(state.current, action, index, value),
        state.current.receiver);
}

void ArmInteractionTimer(State&, bool);
void SendMediaCommand(State& state, InputAction action,
                      int value = 0, int64_t pos = 0) {
    if (state.viewOnly || GetXamlState().lifecycle.IsStopping() || !state.current.receiver) return;
    osd_control::Submit(osd_control::BuildMedia(
        state.current, action, value, pos), state.current.receiver);
}
// XAML delegates retain these callbacks at runtime. Windhawk Editor's
// standalone Clang pass can report the delegate targets as unneeded.
[[maybe_unused]] void CompleteMediaSeek(State& state) {
    if (!state.mediaView.mediaDragging || state.current.kind != LevelKind::Media ||
        !state.mediaView.mediaSlider) return;
    state.mediaView.mediaDragging = false;
    const auto& m = state.current.media;
    if (!m.canSeek || !m.hasTimeline || m.end <= m.start) return;
    const double ratio=std::clamp(state.mediaView.mediaSlider.Value(),0.0,100.0)/100.0;
    const int64_t dest=std::clamp(m.start+
        static_cast<int64_t>(std::llround(double(m.end-m.start)*ratio)),
        m.start,m.end);
    state.mediaView.mediaPreview=dest;
    state.mediaView.mediaPreviewHold=GetTickCount64()+1800;
    SendMediaCommand(state,InputAction::MediaSeek,0,dest);
    ArmInteractionTimer(state,true);
}
// Replicas share the source card's fade clock, not a separate timeout.
void FadeMirrorsWith(State& owner, ULONGLONG at) {
    State* root = owner.pairedVolume ? owner.pairedVolume : &owner;
    for (auto& item : root->peers) {
        auto& mirror = *item.second;
        if (!mirror.viewOnly || !mirror.host || !mirror.card ||
            !IsWindowVisible(mirror.host) || !mirror.current.fadeEnabled)
            continue;
        mirror.fading = mirror.fadeOut = true;
        mirror.fadeStart = at;
        SetTimer(mirror.host, kFadeTimer, 16, nullptr);
    }
}
void HideSurface(State& state) {
    if (state.host) {
        KillTimer(state.host, kHideTimer);
        KillTimer(state.host, kFadeTimer);
        KillTimer(state.host, kStatusLineTimer);
        KillTimer(state.host, kMediaProgressTimer);
    }
    state.statusView.statusLineAnimating = false;
    state.statusView.noticeExpanded = false;
    // Drop the STA image source on dismissal without letting an optional
    // COM failure unwind through Explorer's HWND/teardown callback.
    if (state.clipboardView.clipboardImage) {
        try { state.clipboardView.clipboardImage.Source(nullptr); }
        catch (...) { /* The Island may already be closing. */ }
    }
    // Reclaim the bounded clipboard payload without shrink_to_fit allocation.
    std::vector<uint8_t>{}.swap(state.current.clipboardPixels);
    if (state.mediaView.mediaCover) state.mediaView.mediaCover.Source(nullptr);
    state.mediaView.mediaBitmap=nullptr;
    state.mediaView.mediaArtworkCache.clear();
    state.current.media.encodedArtwork.clear();
    state.mediaView.mediaDragging=false;
    state.mediaView.mediaPreviewHold=0;
    if (state.canvas) state.canvas.ReleasePointerCaptures();
    // CaptureLost may invoke the shared interaction callback and restart
    // the inactivity timer. Cancel once more before hiding the HWND.
    if (state.host) KillTimer(state.host, kHideTimer);
    state.dragging = state.iconPressed = state.pointerActive = false;
    state.fading = state.fadeOut = false;
    if (state.host) ShowWindow(state.host, SW_HIDE);
    if (!state.viewOnly && !state.pairedVolume)
        for (auto& peer : state.peers)
            if (peer.second->viewOnly) HideSurface(*peer.second);
    // Mirror the native panel's lifetime in its UI-thread controller.
    // The action is idempotent and generation-checked at the receiver.
    if (state.current.kind == LevelKind::Mixer && !GetXamlState().lifecycle.IsStopping())
        SendMixerInput(state, InputAction::CloseMixer, -1);
    if (state.current.kind == LevelKind::Media && !GetXamlState().lifecycle.IsStopping())
        SendMediaCommand(state, InputAction::CloseMedia);
    if ((state.current.kind == LevelKind::Media ||
         state.current.kind == LevelKind::Mixer ||
         state.current.kind == LevelKind::NoticeDetails) && state.pairedVolume)
        HideSurface(*state.pairedVolume);
}

void HideAll(State& root) {
    HideSurface(root);
    for (auto& peer : root.peers) HideSurface(*peer.second);
}

// XAML itself owns hit testing and pointer capture. No detached topmost
// HWND can cover the Island (or another physical monitor's Island).
void ArmInteractionTimer(State& state, bool active) {
    if (!state.host || state.viewOnly) return;
    KillTimer(state.host, kHideTimer);
    if (active && state.fadeOut) {
        KillTimer(state.host, kFadeTimer);
        state.fading = state.fadeOut = false;
        if (state.card) state.card.Opacity(1.0);
    }
    if (state.attachedPeerOpen && state.pairedPanel &&
        state.pairedPanel->host) {
        // The attached pair is one interactive surface. Hovering either
        // card pauses the MIXER inactivity timer; volume stays visible.
        State& panel = *state.pairedPanel;
        KillTimer(panel.host, kHideTimer);
        if (!(active || PointerInsideHost(state) ||
              PointerInsideHost(panel))) {
            SetTimer(panel.host, kHideTimer,
                std::clamp(panel.current.durationMs, DWORD(500),
                           DWORD(20000)), nullptr);
        }
        return;
    }
    if (!active && (state.current.kind == LevelKind::Mixer ||
                    state.current.kind == LevelKind::Media ||
                    state.current.kind == LevelKind::NoticeDetails) &&
        state.pairedVolume &&
        (PointerInsideHost(*state.pairedVolume) ||
         PointerInsideHost(state)))
        return;
    if (!active)
        SetTimer(state.host, kHideTimer,
            std::clamp(state.current.durationMs, DWORD(500), DWORD(20000)),
            nullptr);
}

// Interactive XAML details remain visible while the pointer is over their
// native host. The normal configured timeout resumes when it leaves.
bool PointerInsideHost(const State& state) {
    if (!state.host || state.viewOnly) return false;
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
    const Snapshot updated = osd_model::WithPercent(state.current, percent);
    // The renderer previews an owned value; the hardware controller receives
    // only a typed user-intent command, never a mutable XAML State.
    SendInput(state, InputAction::SetPercent, updated.percent);
    DrawSnapshot(state, updated);
    ArmInteractionTimer(state, true);
}

[[maybe_unused]] void PointerPressed(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.canvas || !state.host ||
        (state.current.kind == LevelKind::LockStatus ||
         state.current.kind == LevelKind::NativeEvent ||
         state.current.kind == LevelKind::Mixer ||
         state.current.kind == LevelKind::Media)) return;
    const auto point = args.GetCurrentPoint(state.canvas);
    if (!point.Properties().IsLeftButtonPressed()) return;
    const auto pos = point.Position();
    // Only the dedicated XAML Button owns the notice chevron hit region.
    if (state.current.kind == LevelKind::NoticeStatus) return;
    const double halo = 8.0; // Fixed input halo for icon/fallback track.
    const bool icon = state.current.kind == LevelKind::Volume &&
        state.current.showIcon &&
        InHitRegion(pos.X, pos.Y, state.iconX, state.iconY,
                    state.iconW, state.iconH, halo);
    const bool native = state.levelSlider &&
        state.levelSlider.Visibility() == wx::Visibility::Visible;
    const bool bar = state.current.valueKnown && !native &&
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

[[maybe_unused]] void PointerMoved(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.pointerActive || !state.dragging || !state.canvas ||
        args.Pointer().PointerId() != state.activePointerId) return;
    const auto pos = args.GetCurrentPoint(state.canvas).Position();
    DragTrack(state, pos.X, pos.Y);
    args.Handled(true);
}

[[maybe_unused]] void PointerReleased(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.pointerActive || !state.canvas ||
        args.Pointer().PointerId() != state.activePointerId) return;
    const auto pos = args.GetCurrentPoint(state.canvas).Position();
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

[[maybe_unused]] void PointerCancelled(State& state) {
    state.pointerActive = state.dragging = state.iconPressed = false;
    ArmInteractionTimer(state, state.current.kind == LevelKind::Mixer &&
                               PointerInsideHost(state));
}

[[maybe_unused]] void PointerWheel(State& state, const xinput::PointerRoutedEventArgs& args) {
    if (!state.current.valueKnown ||
        state.current.kind == LevelKind::LockStatus ||
        state.current.kind == LevelKind::NoticeStatus ||
        state.current.kind == LevelKind::NativeEvent ||
        state.current.kind == LevelKind::Mixer ||
        state.current.kind == LevelKind::Media) return;
    const auto point = args.GetCurrentPoint(state.canvas);
    const auto pos = point.Position();
    if (state.levelSlider &&
        state.levelSlider.Visibility() == wx::Visibility::Visible &&
        InHitRegion(pos.X, pos.Y, state.trackX, state.trackY,
                    state.trackW, state.trackH, 12.0)) {
        ArmInteractionTimer(state, false);
        return; // Native Slider owns wheel over its track.
    }
    const int delta = point.Properties().MouseWheelDelta();
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
            osd_glyph::kMute, osd_glyph::kVolume, osd_glyph::kBrightness};
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
    // Only this adapter asks Windows for work-area bounds. The positioning
    // arithmetic itself is pure and can be exercised without an HWND.
    MONITORINFO monitor{sizeof(monitor)};
    const bool hasWork = GetMonitorInfoW(
        MonitorFromRect(&value.anchor, MONITOR_DEFAULTTONEAREST),
        &monitor) != FALSE;
    const auto placed = osd_layout::SurfaceGeometry(value,
        insetX, insetY, bodyW, bodyH,
        hasWork ? &monitor.rcWork : nullptr);
    const bool wasVisible = IsWindowVisible(state.host) != FALSE;
    if (!wasVisible)
        state.card.Opacity(value.fadeEnabled ? 0.0 : 1.0);
    else if (state.fadeOut) {
        KillTimer(state.host, kFadeTimer);
        state.fading = state.fadeOut = false;
        state.card.Opacity(1.0);
    }
    if (!SetWindowPos(state.host, HWND_TOPMOST,
                       placed.x, placed.y, placed.width, placed.height,
                      SWP_NOACTIVATE | SWP_SHOWWINDOW)) {
        Wh_Log(L"Fluent OSD/XAML: show failed (%lu)", GetLastError());
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
    if (state.viewOnly) {
        if (state.card) state.card.IsHitTestVisible(false);
        if (state.canvas) state.canvas.IsHitTestVisible(false);
    }
    if ((!value.passiveRefresh || !wasVisible) && !state.viewOnly)
        ArmInteractionTimer(state, state.dragging || state.iconPressed);
}


// Native XAML status underline: animate a dimensionless width ratio instead
// of pixel positions. The underline stays centered through custom size/DPI
// changes, and a second key event reverses from its current visible width.
void PaintStatusUnderline(State& state) {
    if (!state.statusView.statusUnderline) return;
    const double width = state.statusView.statusLineTextW * state.statusView.statusLineRatio;
    state.statusView.statusUnderline.Width(width);
    controls::Canvas::SetLeft(state.statusView.statusUnderline,
        state.statusView.statusLineCenterX - width / 2.0);
    // Interpolate visual emphasis with the same eased width transition.
    const double activeBlend = std::clamp(
        (state.statusView.statusLineRatio - kOffLineRatio) /
            (1.0 - kOffLineRatio), 0.0, 1.0);
    state.statusView.statusUnderline.Opacity(.57 + .43 * activeBlend);
}

void AdvanceStatusUnderline(State& state, ULONGLONG now) {
    if (!state.statusView.statusLineAnimating) return;
    const double fraction = std::clamp(
        static_cast<double>(now - state.statusView.statusLineStart) /
            kStatusLineAnimationMs, 0.0, 1.0);
    // Cubic ease-in/out: gentle start and stop, symmetrical on reversal.
    const double ease = fraction * fraction * (3.0 - 2.0 * fraction);
    state.statusView.statusLineRatio = state.statusView.statusLineFrom +
        (state.statusView.statusLineTo - state.statusView.statusLineFrom) * ease;
    PaintStatusUnderline(state);
    if (fraction >= 1.0) {
        state.statusView.statusLineAnimating = false;
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
        state.statusView.statusLineRatio = active ? kOffLineRatio : 1.0;
        state.statusView.statusLineAnimating = false;
        if (state.host) KillTimer(state.host, kStatusLineTimer);
    } else if (sameTarget && !state.statusView.statusLineAnimating) {
        state.statusView.statusLineRatio = target;
    }
    state.statusView.statusLineTextW = textW;
    state.statusView.statusLineCenterX = textX + textW / 2.0;
    PaintStatusUnderline(state);

    // Identical repeat events do not restart an in-flight animation.
    if (sameTarget && state.statusView.statusLineAnimating) return;
    if (std::abs(state.statusView.statusLineRatio - target) < 0.0001) {
        state.statusView.statusLineRatio = target;
        state.statusView.statusLineAnimating = false;
        PaintStatusUnderline(state);
        if (state.host) KillTimer(state.host, kStatusLineTimer);
        return;
    }
    state.statusView.statusLineFrom = state.statusView.statusLineRatio;
    state.statusView.statusLineTo = target;
    state.statusView.statusLineStart = now;
    state.statusView.statusLineAnimating = true;
    if (!SetTimer(state.host, kStatusLineTimer, 16, nullptr)) {
        state.statusView.statusLineAnimating = false;
        state.statusView.statusLineRatio = target;
        PaintStatusUnderline(state);
    }
}


void UpdateNoticeDetails(State& state, const Snapshot& value,
                         double bodyW, double headerH, double pad,
                         double, double& totalBodyH) {
    const bool canExpand = osd_model::CanExpand(value);
    state.statusView.noticeHeaderH = headerH;
    state.statusView.noticeChevron.Visibility(canExpand
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    // Same XAML Button/glyph contract as the volume Mixer.
    state.statusView.noticeChevron.Content(winrt::box_value(winrt::hstring(
        osd_layout::MixerChevronGlyph(value.noticeDirection))));
    state.statusView.noticeChevron.Foreground(Brush(value.accent));
    const double size = std::clamp(headerH * .32, 20.0, 28.0);
    state.statusView.noticeChevron.Width(size);
    state.statusView.noticeChevron.Height(size);
    controls::Canvas::SetLeft(state.statusView.noticeChevron,
        std::max(0.0, bodyW - pad - size));
    controls::Canvas::SetTop(state.statusView.noticeChevron,
        std::max(0.0, (headerH - size) * .5));
    state.statusView.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeScroll.Visibility(wx::Visibility::Collapsed);
    // Details occupy a sibling peer window; main card never changes size.
    totalBodyH = headerH;
}
[[maybe_unused]] void ToggleNoticeDetails(State& state) {
    if (!state.viewOnly && osd_model::CanExpand(state.current))
        SendInput(state, InputAction::ToggleNoticeDetails, 0);
}
void DrawNoticeDetailsPanel(State& state, const Snapshot& value) {
    if (!state.host || !state.card || !state.canvas ||
        !state.statusView.noticeHeading || !state.statusView.noticeScroll || !state.statusView.noticeRows)
        return;
    state.current = value;
    state.scale = std::clamp(static_cast<double>(value.scale), 0.5, 6.0);
    const auto frame = osd_layout::CardFrame(value, 8.0 / 296.0, 7.0 / 210.0);
    const double w = frame.width, h = frame.height;
    const double pad = std::clamp(
        static_cast<double>(value.innerPadding), 6.0, 22.0) * .68;
    state.canvas.IsHitTestVisible(true);
    state.canvas.Width(w);
    state.canvas.Height(h);
    ApplyBackground(state, value);
    const double radius = std::clamp(
        static_cast<double>(value.cornerRadius), 0.0, 34.0);
    state.card.CornerRadius(wx::CornerRadius{
        radius, radius, radius, radius});
    state.card.BorderBrush(Brush(value.track));
    const double border = value.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{
        border, border, border, border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerSurface.Visibility(wx::Visibility::Collapsed);
    state.mediaView.mediaSurface.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardFrame.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardCaption.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeHeading.Visibility(wx::Visibility::Visible);
    state.statusView.noticeScroll.Visibility(wx::Visibility::Visible);
    const double headingH = std::max(20.0, value.fontSize * 1.5);
    const double rowH = std::max(26.0, value.fontSize * 1.8);
    state.statusView.noticeHeading.Text(winrt::hstring(value.noticeDetailsHeading));
    state.statusView.noticeHeading.FontSize(std::clamp(value.fontSize, 11, 22));
    state.statusView.noticeHeading.Foreground(Brush(value.text));
    state.statusView.noticeHeading.Width(std::max(1.0, w - 2.0 * pad));
    controls::Canvas::SetLeft(state.statusView.noticeHeading, pad);
    controls::Canvas::SetTop(state.statusView.noticeHeading, pad);
    state.statusView.noticeScroll.Width(std::max(1.0, w - 2.0 * pad));
    state.statusView.noticeScroll.Height(std::max(1.0, h - headingH - 2.5 * pad));
    controls::Canvas::SetLeft(state.statusView.noticeScroll, pad);
    controls::Canvas::SetTop(state.statusView.noticeScroll, pad * 1.5 + headingH);
    state.statusView.noticeRows.Children().Clear();
    for (const auto& name : value.noticeDetails) {
        controls::TextBlock row;
        row.Text(winrt::hstring(name));
        row.Width(std::max(1.0, w - 3.0 * pad));
        row.Height(rowH);
        row.FontSize(std::clamp(value.fontSize - 2, 10, 18));
        row.Foreground(Brush(value.text));
        row.TextTrimming(wx::TextTrimming::CharacterEllipsis);
        state.statusView.noticeRows.Children().Append(row);
    }
    ShowPositionedSurface(state, value, frame.insetX, frame.insetY, w, h);
}

void DrawStatusSnapshot(State& state, const Snapshot& value) {
    if (!state.host || !state.card || !state.canvas ||
        !state.statusView.statusTile || !state.statusView.statusTitle || !state.statusView.statusGlyph ||
        !state.statusView.statusDetail || !state.statusView.statusUnderline ||
        !state.statusView.noticeScroll || !state.statusView.noticeRows ||
        !state.statusView.noticeHeading || !state.statusView.noticeChevron) return;
    if (state.pointerActive && state.canvas)
        state.canvas.ReleasePointerCaptures();
    // Sample previous value before overwriting the key and toggle state.
    const bool visible = IsWindowVisible(state.host) != FALSE;
    const bool sameVisibleStatus =
        visible && state.current.kind == LevelKind::LockStatus &&
        state.current.statusTitle == value.statusTitle;
    const bool sameNotice =
        osd_model::SameNotice(state.current, value, visible);
    if (!sameNotice) {
        state.statusView.noticeExpanded = false;
        state.statusView.noticeNormalDurationMs = value.durationMs;
    }
    state.wheelRemainder = 0;
    state.dragging = state.iconPressed = state.pointerActive = false;
    state.scale = std::clamp(static_cast<double>(value.scale), 0.5, 6.0);

    const auto layout = osd_layout::StatusGeometry(value);
    const double insetX = layout.frame.insetX, insetY = layout.frame.insetY;
    const double bodyW = layout.frame.width, bodyH = layout.frame.height;
    const double pad = layout.pad, tileSize = layout.tileSize;
    const double tileX = layout.tileX, tileY = layout.tileY;
    const double textX = layout.textX, textW = layout.textW;
    const bool clickableNotice = layout.interactive;

    state.canvas.IsHitTestVisible(clickableNotice);
    state.canvas.Width(bodyW);
    ApplyBackground(state, value);
    const double radius = layout.radius;
    state.card.CornerRadius(wx::CornerRadius{radius, radius, radius, radius});
    SetBackgroundLayerRadius(state, radius);
    state.card.BorderBrush(Brush(value.track));
    const double border = value.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{border, border, border, border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);

    state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerSurface.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTile.Visibility(wx::Visibility::Visible);
    state.statusView.statusGlyph.Visibility(wx::Visibility::Visible);
    state.statusView.statusTitle.Visibility(wx::Visibility::Visible);
    state.statusView.statusDetail.Visibility(wx::Visibility::Visible);
    const bool lock = value.kind == LevelKind::LockStatus;
    state.statusView.statusUnderline.Visibility(lock
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    if (!lock) {
        if (state.statusView.statusLineAnimating && state.host)
            KillTimer(state.host, kStatusLineTimer);
        state.statusView.statusLineAnimating = false;
    }

    state.statusView.statusTile.Width(tileSize);
    state.statusView.statusTile.Height(tileSize);
    state.statusView.statusGlyph.Width(tileSize);
    const double tileRadius = std::min(tileSize * .19, radius);
    state.statusView.statusTile.CornerRadius(wx::CornerRadius{
        tileRadius, tileRadius, tileRadius, tileRadius});
    state.statusView.statusTile.Background(Brush(value.track, 120));
    controls::Canvas::SetLeft(state.statusView.statusTile, tileX);
    controls::Canvas::SetTop(state.statusView.statusTile, tileY);

    state.statusView.statusGlyph.FontFamily(media::FontFamily{
        value.statusFontIcon ? L"Segoe Fluent Icons" : L"Segoe UI"});
    state.statusView.statusGlyph.Text(winrt::hstring(value.statusGlyph));
    state.statusView.statusGlyph.FontSize(value.statusFontIcon
        ? std::clamp(tileSize * .53, 15.0, 32.0)
        : static_cast<double>(value.statusGlyph.size() > 1
            ? std::clamp(value.fontSize, 12, 24)
            : std::clamp(value.iconSize + 7, 16, 32)));
    state.statusView.statusGlyph.Foreground(Brush(
        value.statusFontIcon || value.statusActive ? value.accent : value.text,
        value.statusFontIcon || value.statusActive ? 255 : 195));
    state.statusView.statusTitle.Text(winrt::hstring(value.statusTitle));
    state.statusView.statusDetail.Text(winrt::hstring(value.statusDetail));
    const int titleFont = layout.titleFont, detailFont = layout.detailFont;
    state.statusView.statusTitle.FontSize(titleFont);
    state.statusView.statusDetail.FontSize(detailFont);
    state.statusView.statusTitle.Foreground(Brush(value.text));
    state.statusView.statusDetail.Foreground(Brush(value.text, 195));
    state.statusView.statusTitle.Width(textW);
    state.statusView.statusDetail.Width(textW);
    state.statusView.statusTitle.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    state.statusView.statusDetail.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    const double lineGap = layout.lineGap;
    const double lineHeight = layout.underlineH;
    const double underlineTop = layout.underlineTop;
    const double top = layout.textTop;
    controls::Canvas::SetLeft(state.statusView.statusTitle, textX);
    controls::Canvas::SetTop(state.statusView.statusTitle, top);
    controls::Canvas::SetLeft(state.statusView.statusDetail, textX);
    controls::Canvas::SetTop(state.statusView.statusDetail, top + titleFont * 1.43 + lineGap);
    // ON expands to the full text column; OFF contracts to 35%.
    // Animate both while keeping the underline centered below the text.
    state.statusView.statusUnderline.Height(lineHeight);
    state.statusView.statusUnderline.RadiusX(lineHeight / 2.0);
    state.statusView.statusUnderline.RadiusY(lineHeight / 2.0);
    state.statusView.statusUnderline.Fill(Brush(value.accent));
    controls::Canvas::SetTop(state.statusView.statusUnderline, underlineTop);
    if (lock)
        TransitionStatusUnderline(state, sameVisibleStatus,
                                  value.statusActive, textX, textW);
    double totalBodyH = bodyH;
    UpdateNoticeDetails(state, value, bodyW, bodyH, pad,
                        insetY, totalBodyH);
    state.canvas.Height(totalBodyH);
    state.current = value;
    if (value.kind == LevelKind::NoticeStatus)
        state.current.durationMs = osd_model::NoticeDuration(
            value, state.statusView.noticeExpanded, state.statusView.noticeNormalDurationMs);
    ShowPositionedSurface(state, state.current, insetX, insetY,
                          bodyW, totalBodyH);
}


void DrawClipboardImageSnapshot(State& state, const Snapshot& data) {
    if (!state.host || !state.card || !state.canvas ||
        !state.clipboardView.clipboardFrame || !state.clipboardView.clipboardImage ||
        !state.clipboardView.clipboardCaption) return;
    state.scale = std::clamp(static_cast<double>(data.scale), 0.5, 6.0);
    const auto layout = osd_layout::ClipboardGeometry(data);
    const double insetX = layout.frame.insetX, insetY = layout.frame.insetY;
    const double bodyW = layout.frame.width, bodyH = layout.frame.height;
    const double inset = layout.inset, captionFont = layout.captionFont;
    const double frameW = layout.previewW, frameH = layout.previewH;
    const double radius = layout.radius;
    state.canvas.IsHitTestVisible(false);
    state.canvas.Width(bodyW);
    state.canvas.Height(bodyH);
    ApplyBackground(state, data);
    state.card.CornerRadius(wx::CornerRadius{radius, radius, radius, radius});
    SetBackgroundLayerRadius(state, radius);
    state.card.BorderBrush(Brush(data.track));
    const double border = data.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{border, border, border, border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeScroll.Visibility(wx::Visibility::Collapsed);
    if (state.statusView.statusLineAnimating) KillTimer(state.host, kStatusLineTimer);
    state.statusView.statusLineAnimating = false;
    state.statusView.noticeExpanded = false;

    // Do not retain an old image when a new snapshot is malformed.
    state.clipboardView.clipboardImage.Source(nullptr);
    state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerSurface.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardFrame.Visibility(wx::Visibility::Visible);
    state.clipboardView.clipboardCaption.Visibility(wx::Visibility::Visible);
    state.clipboardView.clipboardFrame.Background(Brush(data.track, 72));
    const double previewRadius = std::min(radius, frameH * .14);
    state.clipboardView.clipboardFrame.CornerRadius(wx::CornerRadius{
        previewRadius, previewRadius, previewRadius, previewRadius});
    state.clipboardView.clipboardFrame.Width(frameW);
    state.clipboardView.clipboardFrame.Height(frameH);
    controls::Canvas::SetLeft(state.clipboardView.clipboardFrame, inset);
    controls::Canvas::SetTop(state.clipboardView.clipboardFrame, inset);
    state.clipboardView.clipboardImage.Width(frameW);
    state.clipboardView.clipboardImage.Height(frameH);
    state.clipboardView.clipboardCaption.Text(winrt::hstring(data.statusTitle));
    state.clipboardView.clipboardCaption.Width(frameW);
    state.clipboardView.clipboardCaption.FontSize(captionFont);
    state.clipboardView.clipboardCaption.Foreground(Brush(data.text));
    state.clipboardView.clipboardCaption.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    controls::Canvas::SetLeft(state.clipboardView.clipboardCaption, inset);
    controls::Canvas::SetTop(state.clipboardView.clipboardCaption,
        inset * 2.0 + frameH);

    // Construct WriteableBitmap only on the Island's STA. The original
    // Explorer UI thread transferred copied bytes, never an HBITMAP/HDC.
    if (auto bitmap = BitmapFromPixels(
            data.clipboardWidth, data.clipboardHeight,
            data.clipboardPixels))
        state.clipboardView.clipboardImage.Source(bitmap);
    state.current = data;
    ShowPositionedSurface(state, data, insetX, insetY, bodyW, bodyH);
}

// Native, scrollable Mixer panel. All controls are constructed on the XAML
// STA from a copied view-model; no Core Audio pointers are shared with it.
// The one BGRA -> WriteableBitmap adapter for clipboard, Mixer icons and
// already-downscaled SMTC art. Clipboard has its own stricter source bounds.
// Only the XAML STA creates the bitmap.
constexpr uint32_t kMaxXamlBitmapSide = 320;
imaging::WriteableBitmap BitmapFromPixels(
        uint32_t width, uint32_t height,
        const std::vector<uint8_t>& pixels, uint32_t maxSide) {
    if (!width || !height || width > maxSide ||
        height > maxSide)
        return imaging::WriteableBitmap{nullptr};
    const size_t bytes = static_cast<size_t>(width) * height * 4;
    if (bytes != pixels.size()) return imaging::WriteableBitmap{nullptr};
    imaging::WriteableBitmap bitmap{
        static_cast<int32_t>(width), static_cast<int32_t>(height)};
    const auto buffer = bitmap.PixelBuffer();
    if (buffer.Length() < bytes) return imaging::WriteableBitmap{nullptr};
    ComPtr<IBufferByteAccess> access;
    winrt::check_hresult(winrt::get_unknown(buffer)->QueryInterface(
        kBufferByteAccessIID,
        reinterpret_cast<void**>(access.GetAddressOf())));
    BYTE* output = nullptr;
    winrt::check_hresult(access->Buffer(&output));
    if (!output) return imaging::WriteableBitmap{nullptr};
    memcpy(output, pixels.data(), bytes);
    bitmap.Invalidate();
    return bitmap;
}

namespace media_artwork {
// WIC adapter, never runs in SMTC worker, bounded to 1 MiB/8 megapixels.
imaging::WriteableBitmap Decode(const std::vector<uint8_t>& bytes) {
    if (bytes.empty() || bytes.size()>1024u*1024u)
        return imaging::WriteableBitmap{nullptr};
    HGLOBAL mem=GlobalAlloc(GMEM_MOVEABLE,bytes.size());
    if (!mem) return imaging::WriteableBitmap{nullptr};
    void* ptr=GlobalLock(mem);
    if (!ptr) { GlobalFree(mem); return imaging::WriteableBitmap{nullptr}; }
    memcpy(ptr,bytes.data(),bytes.size());
    GlobalUnlock(mem);
    ComPtr<IStream> stream;
    if (FAILED(CreateStreamOnHGlobal(mem,TRUE,stream.GetAddressOf()))) {
        GlobalFree(mem); return imaging::WriteableBitmap{nullptr};
    }
    ComPtr<IWICImagingFactory> factory;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory,nullptr,
             CLSCTX_INPROC_SERVER,IID_PPV_ARGS(factory.GetAddressOf()))))
        return imaging::WriteableBitmap{nullptr};
    ComPtr<IWICBitmapDecoder> decoder;
    if (FAILED(factory->CreateDecoderFromStream(stream.Get(),nullptr,
             WICDecodeMetadataCacheOnLoad,decoder.GetAddressOf())))
        return imaging::WriteableBitmap{nullptr};
    ComPtr<IWICBitmapFrameDecode> frame;
    if (FAILED(decoder->GetFrame(0,frame.GetAddressOf())))
        return imaging::WriteableBitmap{nullptr};
    UINT w=0,h=0;
    if (FAILED(frame->GetSize(&w,&h))||!w||!h||w>4096||h>4096||
        uint64_t(w)*h>8388608ULL)
        return imaging::WriteableBitmap{nullptr};
    // Cover artwork often arrives as 300/512/1024px squares. The shared
    // bitmap adapter intentionally owns a small bounded pixel buffer; feeding
    // WIC's full-size decode into it silently discarded other SMTC covers.
    // Constrain the longest side while preserving aspect ratio and let WIC
    // downsample rather than allocating the original 8MP pixel buffer.
    const double ratio = std::min(1.0, double(kMaxXamlBitmapSide) /
        double(std::max(w, h)));
    const UINT targetW = std::max<UINT>(1,
        static_cast<UINT>(std::lround(double(w) * ratio)));
    const UINT targetH = std::max<UINT>(1,
        static_cast<UINT>(std::lround(double(h) * ratio)));
    ComPtr<IWICBitmapScaler> scaler;
    IWICBitmapSource* source = frame.Get();
    if (targetW != w || targetH != h) {
        if (FAILED(factory->CreateBitmapScaler(scaler.GetAddressOf())) ||
            FAILED(scaler->Initialize(frame.Get(), targetW, targetH,
                WICBitmapInterpolationModeFant)))
            return imaging::WriteableBitmap{nullptr};
        source = scaler.Get();
    }
    ComPtr<IWICFormatConverter> cv;
    if (FAILED(factory->CreateFormatConverter(cv.GetAddressOf())) ||
        FAILED(cv->Initialize(source, GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom)))
        return imaging::WriteableBitmap{nullptr};
    w = targetW;
    h = targetH;
    const uint32_t stride = w * 4;
    std::vector<uint8_t> pixels(static_cast<size_t>(stride)*h);
    if (FAILED(cv->CopyPixels(nullptr,stride,
             static_cast<UINT>(pixels.size()),pixels.data())))
        return imaging::WriteableBitmap{nullptr};
    try { return BitmapFromPixels(w,h,pixels); }
    catch (...) { return imaging::WriteableBitmap{nullptr}; }
}
}

// Background-image adapter: local file only, decoded on the XAML STA and
// cached by ApplyBackground. Image data never crosses the HWND command ABI.
imaging::WriteableBitmap LoadLocalBackgroundImage(const std::wstring& path) {
    if (path.size() < 4 || path.size() > 1024 ||
        !((path[0] >= L'A' && path[0] <= L'Z') ||
          (path[0] >= L'a' && path[0] <= L'z')) ||
        path[1] != L':' || path[2] != L'\\' ||
        path.find(L"..") != std::wstring::npos)
        return imaging::WriteableBitmap{nullptr};
    WIN32_FILE_ATTRIBUTE_DATA attributes{};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard,
                              &attributes) ||
        (attributes.dwFileAttributes &
            (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_REPARSE_POINT)))
        return imaging::WriteableBitmap{nullptr};
    const uint64_t bytes =
        (uint64_t(attributes.nFileSizeHigh) << 32) |
         attributes.nFileSizeLow;
    if (!bytes || bytes > 16ULL * 1024 * 1024)
        return imaging::WriteableBitmap{nullptr};
    ComPtr<IWICImagingFactory> factory;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr,
          CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory.GetAddressOf()))))
        return imaging::WriteableBitmap{nullptr};
    ComPtr<IWICBitmapDecoder> decoder;
    if (FAILED(factory->CreateDecoderFromFilename(path.c_str(), nullptr,
          GENERIC_READ, WICDecodeMetadataCacheOnDemand,
          decoder.GetAddressOf())))
        return imaging::WriteableBitmap{nullptr};
    ComPtr<IWICBitmapFrameDecode> frame;
    if (FAILED(decoder->GetFrame(0, frame.GetAddressOf())))
        return imaging::WriteableBitmap{nullptr};
    UINT w = 0, h = 0;
    if (FAILED(frame->GetSize(&w, &h)) || !w || !h ||
        w > 8192 || h > 8192 || uint64_t(w) * h > 33554432ULL)
        return imaging::WriteableBitmap{nullptr};
    constexpr UINT kMaxBackgroundSide = 1024;
    const double ratio = std::min(1.0,
        double(kMaxBackgroundSide) / double(std::max(w, h)));
    const UINT tw = std::max<UINT>(1,
        static_cast<UINT>(std::lround(w * ratio)));
    const UINT th = std::max<UINT>(1,
        static_cast<UINT>(std::lround(h * ratio)));
    ComPtr<IWICBitmapScaler> scaler;
    IWICBitmapSource* source = frame.Get();
    if (tw != w || th != h) {
        if (FAILED(factory->CreateBitmapScaler(scaler.GetAddressOf())) ||
            FAILED(scaler->Initialize(frame.Get(), tw, th,
                    WICBitmapInterpolationModeFant)))
            return imaging::WriteableBitmap{nullptr};
        source = scaler.Get();
    }
    ComPtr<IWICFormatConverter> converter;
    if (FAILED(factory->CreateFormatConverter(converter.GetAddressOf())) ||
        FAILED(converter->Initialize(source, GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone, nullptr, 0.0,
            WICBitmapPaletteTypeCustom)))
        return imaging::WriteableBitmap{nullptr};
    std::vector<uint8_t> pixels(static_cast<size_t>(tw) * th * 4);
    if (FAILED(converter->CopyPixels(nullptr, tw * 4,
        static_cast<UINT>(pixels.size()), pixels.data())))
        return imaging::WriteableBitmap{nullptr};
    return BitmapFromPixels(tw, th, pixels, kMaxBackgroundSide);
}
void AdvanceMediaTimeline(State& state) {
    if (state.current.kind!=LevelKind::Media||
        !state.mediaView.mediaSlider||!state.mediaView.mediaElapsed||state.mediaView.mediaDragging) return;
    const auto& m=state.current.media;
    if (!m.hasTimeline||m.end<=m.start) return;
    const uint64_t now=GetTickCount64();
    if (now<state.mediaView.mediaPreviewHold) return;
    const int64_t pos=osd_model::MediaPosition(m,now);
    state.mediaView.mediaPopulating=true;
    state.mediaView.mediaSlider.Value(std::clamp(
        100.0*double(pos-m.start)/double(m.end-m.start),0.0,100.0));
    state.mediaView.mediaElapsed.Text(osd_model::MediaTime(pos-m.start));
    state.mediaView.mediaPopulating=false;
}
void DrawMediaSnapshot(State& state,const Snapshot& snap) {
    if (!state.host||!state.card||!state.canvas||!state.mediaView.mediaSurface) return;
    const auto& m=snap.media;
    if (state.current.kind==LevelKind::Media&&state.mediaView.mediaDragging&&
        state.current.media.sourceId==m.sourceId&&
        state.current.media.selectionSerial==m.selectionSerial)
        return; // Seeking owns capture; do not reconstruct the controls.
    const auto& prev=state.current.media;
    const bool same=state.current.kind==LevelKind::Media &&
        IsWindowVisible(state.host)&&prev.sourceId==m.sourceId &&
        prev.selectionSerial==m.selectionSerial&&
        prev.generation==m.generation&&prev.title==m.title&&
        prev.artist==m.artist&&prev.encodedArtwork==m.encodedArtwork&&
        prev.playing==m.playing&&prev.canPrevious==m.canPrevious&&
        prev.canToggle==m.canToggle&&prev.canNext==m.canNext&&
        prev.canShuffle==m.canShuffle&&prev.canRepeat==m.canRepeat&&
        prev.shuffleKnown==m.shuffleKnown&&
        prev.shuffleActive==m.shuffleActive&&
        prev.repeatMode==m.repeatMode&&prev.hasTimeline==m.hasTimeline&&
        prev.canSeek==m.canSeek&&prev.start==m.start&&prev.end==m.end&&
        prev.controlSizePercent==m.controlSizePercent&&
        prev.squareButtons==m.squareButtons&&
        prev.buttonCornerRadius==m.buttonCornerRadius&&
        state.current.fontSize==snap.fontSize&&
        state.current.innerPadding==snap.innerPadding&&
        state.current.cornerRadius==snap.cornerRadius&&
        state.current.vertical==snap.vertical&&
        state.current.background==snap.background&&
        state.current.backgroundAlpha==snap.backgroundAlpha&&
        state.current.layeredBackground==snap.layeredBackground&&
        osd_model::SameBrushLayers(
            state.current.backgroundLayers, snap.backgroundLayers)&&
        state.current.accent==snap.accent&&
        state.current.text==snap.text&&
        state.current.track==snap.track&&
        state.current.borderless==snap.borderless&&
        state.current.anchor.left==snap.anchor.left&&
        state.current.anchor.top==snap.anchor.top&&
        state.current.anchor.right==snap.anchor.right&&
        state.current.anchor.bottom==snap.anchor.bottom&&
        state.current.scale==snap.scale;
    if (state.mediaView.mediaPreviewHold&&
        (prev.sourceId!=m.sourceId||
         prev.selectionSerial!=m.selectionSerial||
         std::llabs(m.position-state.mediaView.mediaPreview)<15000000LL))
        state.mediaView.mediaPreviewHold=0;
    state.current=snap;
    if (same) { AdvanceMediaTimeline(state); return; }
    state.mediaView.mediaDragging=false;
    state.mediaView.mediaPopulating=true;
    state.dragging=state.iconPressed=state.pointerActive=false;
    const auto g=osd_layout::MediaLayout(snap);
    const double w=g.frame.width,h=g.frame.height;
    state.canvas.IsHitTestVisible(true);
    state.canvas.Width(w);state.canvas.Height(h);
    ApplyBackground(state, snap);
    const double radius=std::clamp(double(snap.cornerRadius),0.0,34.0);
    state.card.CornerRadius(wx::CornerRadius{
        radius,radius,radius,radius});
    SetBackgroundLayerRadius(state, radius);
    state.card.BorderBrush(Brush(snap.track));
    const double border=snap.borderless?0.0:1.0;
    state.card.BorderThickness(wx::Thickness{border,border,border,border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerSurface.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeScroll.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardFrame.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardCaption.Visibility(wx::Visibility::Collapsed);
    state.mediaView.mediaSurface.Visibility(wx::Visibility::Visible);
    state.mediaView.mediaSurface.Width(w);state.mediaView.mediaSurface.Height(h);
    state.mediaView.mediaSlider=nullptr;
    state.mediaView.mediaElapsed=nullptr;
    state.mediaView.mediaCover=nullptr;
    state.mediaView.mediaSurface.Children().Clear();
    if (state.mediaView.mediaArtworkCache!=m.encodedArtwork) {
        state.mediaView.mediaArtworkCache=m.encodedArtwork;
        state.mediaView.mediaBitmap=media_artwork::Decode(m.encodedArtwork);
    }
    auto place=[&](wx::FrameworkElement const& e,double x,double y) {
        controls::Canvas::SetLeft(e,x);
        controls::Canvas::SetTop(e,y);
        state.mediaView.mediaSurface.Children().Append(e);
    };
    controls::Border cover;
    cover.Width(g.artSize);cover.Height(g.artSize);
    cover.CornerRadius(wx::CornerRadius{
        g.artCorner,g.artCorner,g.artCorner,g.artCorner});
    cover.Background(Brush(snap.track,180));
    if (state.mediaView.mediaBitmap) {
        controls::Image img;
        img.Width(g.artSize);img.Height(g.artSize);
        img.Stretch(media::Stretch::UniformToFill);
        img.Source(state.mediaView.mediaBitmap);
        cover.Child(img);state.mediaView.mediaCover=img;
    } else {
        controls::TextBlock fallback;
        fallback.Text(L"\u266B");
        fallback.FontSize(g.placeholderFont);
        fallback.Foreground(Brush(snap.text,190));
        fallback.TextAlignment(wx::TextAlignment::Center);
        fallback.VerticalAlignment(wx::VerticalAlignment::Center);
        cover.Child(fallback);
    }
    place(cover,g.artX,g.artY);
    auto text=[&](const std::wstring& t,double x,double y,
                  double width,double height,double font,BYTE alpha) {
        controls::TextBlock v;
        v.Text(winrt::hstring(t));
        v.Width(std::max(1.0,width));v.Height(std::max(1.0,height));
        v.FontSize(font);v.Foreground(Brush(snap.text,alpha));
        v.TextTrimming(wx::TextTrimming::CharacterEllipsis);
        v.VerticalAlignment(wx::VerticalAlignment::Center);
        place(v,x,y);
        return v;
    };
    text(m.title,g.textX,g.titleY,g.textW,g.titleH,
         g.titleFont,255);
    text(m.artist,g.textX,g.artistY,g.textW,g.artistH,
         g.artistFont,190);
    if (g.cycleVisible) {
        controls::Button cycle;
        cycle.Width(g.cycleSize);cycle.Height(g.cycleSize);
        cycle.MinWidth(0);cycle.MinHeight(0);
        cycle.Padding(wx::Thickness{0,0,0,0});
        const double corner = osd_layout::MediaButtonCornerRadius(
            m, g.cycleSize);
        cycle.CornerRadius(wx::CornerRadius{
            corner, corner, corner, corner});
        cycle.FontFamily(media::FontFamily{L"Segoe Fluent Icons"});
        cycle.FontSize(g.cycleFont);
        cycle.Content(winrt::box_value(winrt::hstring(osd_glyph::kChevronRight)));
        cycle.Background(Brush(0x181b22,205));
        cycle.Foreground(Brush(0xffffff));
        cycle.Click([&state](auto const&,auto const&) {
            SendMediaCommand(state,InputAction::MediaAction,7);
            ArmInteractionTimer(state,true);
        });
        place(cycle,g.cycleX,g.cycleY);
    }
    if (g.hasTimeline) {
        controls::Slider slider;
        slider.Width(g.textW);
        slider.Height(g.timelineH);
        slider.MinWidth(0);
        slider.Minimum(0);slider.Maximum(100);
        slider.SmallChange(1);slider.IsEnabled(m.canSeek);
        const int64_t pos=osd_model::MediaPosition(m,GetTickCount64());
        slider.Value(std::clamp(100.0*double(pos-m.start)/
            double(m.end-m.start),0.0,100.0));
        state.mediaView.mediaElapsed=text(osd_model::MediaTime(pos-m.start),
            g.textX,g.timeY,g.textW*.5,g.timeHeight,
            g.timeFont,190);
        auto total=text(osd_model::MediaTime(m.end-m.start),
            g.textX+g.textW*.5,g.timeY,g.textW*.5,g.timeHeight,
            g.timeFont,190);
        total.TextAlignment(wx::TextAlignment::Right);
        state.mediaView.mediaSlider=slider;
        slider.ValueChanged([&state](auto const&,auto const& a) {
            if (state.mediaView.mediaPopulating||
                state.current.kind!=LevelKind::Media||
                !state.current.media.canSeek) return;
            const auto& m=state.current.media;
            const int64_t p=m.start+static_cast<int64_t>(std::llround(
                double(m.end-m.start)*
                (std::clamp(a.NewValue(),0.0,100.0)/100.0)));
            if (state.mediaView.mediaElapsed)
                state.mediaView.mediaElapsed.Text(osd_model::MediaTime(p-m.start));
            if (!state.mediaView.mediaDragging)
                SendMediaCommand(state,InputAction::MediaSeek,0,p);
            ArmInteractionTimer(state,true);
        });
        slider.AddHandler(wx::UIElement::PointerPressedEvent(),
            winrt::box_value(xinput::PointerEventHandler(
                [&state](auto const&,auto const&) {
                    if (state.current.kind==LevelKind::Media)
                        state.mediaView.mediaDragging=true;
                })),true);
        slider.AddHandler(wx::UIElement::PointerReleasedEvent(),
            winrt::box_value(xinput::PointerEventHandler(
                [&state](auto const&,auto const&) {
                    CompleteMediaSeek(state);
                })),true);
        slider.PointerCaptureLost([&state](auto const&,auto const&) {
            CompleteMediaSeek(state);
        });
        place(slider,g.textX,g.timelineY);
    }
    auto action=[&](int code,const wchar_t* glyph,
                    double x,double y,double size,bool enabled,bool active) {
        controls::Button b;
        b.Width(size);b.Height(size);
        b.MinWidth(0);b.MinHeight(0);
        b.Padding(wx::Thickness{0,0,0,0});
        const double corner = osd_layout::MediaButtonCornerRadius(m, size);
        b.CornerRadius(wx::CornerRadius{
            corner, corner, corner, corner});
        b.HorizontalContentAlignment(wx::HorizontalAlignment::Center);
        b.VerticalContentAlignment(wx::VerticalAlignment::Center);
        b.FontFamily(media::FontFamily{L"Segoe Fluent Icons"});
        b.FontSize(std::clamp(size*.46, 7.0, 24.0));
        b.Content(winrt::box_value(winrt::hstring(glyph)));
        b.Background(Brush(active?snap.accent:snap.track,active?110:175));
        b.Foreground(Brush(snap.text));b.IsEnabled(enabled);
        b.Click([&state,code](auto const&,auto const&) {
            SendMediaCommand(state,InputAction::MediaAction,code);
            ArmInteractionTimer(state,true);
        });
        place(b,x-size/2,y-size/2);
    };
    const double sz=g.controlRadius*2;
    if (m.canPrevious||m.canToggle||m.canNext) {
        action(1,osd_glyph::kMediaPrevious,g.controlX[0],g.controlsY,
               sz,m.canPrevious,false);
        action(2,m.playing?osd_glyph::kMediaPause:osd_glyph::kMediaPlay,
               g.controlX[1],g.controlsY,sz,m.canToggle,false);
        action(3,osd_glyph::kMediaNext,g.controlX[2],g.controlsY,
               sz,m.canNext,false);
    }
    if (m.canShuffle&&m.shuffleKnown)
        action(5,osd_glyph::kMediaShuffle,g.extraX,g.extraY[0],
               g.controlRadius,true,m.shuffleActive);
    if (m.canRepeat&&m.repeatMode>=0)
        action(6,m.repeatMode==1?osd_glyph::kMediaRepeatOne:osd_glyph::kMediaRepeatAll,
               g.extraX,g.extraY[1],g.controlRadius,true,m.repeatMode>0);
    state.mediaView.mediaPopulating=false;
    ShowPositionedSurface(state,snap,g.frame.insetX,g.frame.insetY,w,h);
    if (m.hasTimeline&&m.playing)
        SetTimer(state.host,kMediaProgressTimer,100,nullptr);
    else KillTimer(state.host,kMediaProgressTimer);
}
// Reused XAML events must still target their original session. An unknown
// session ID is valid only within the generation where its row was created.
bool MixerRowBindingValid(const State& state, int index,
                          const std::wstring& identity,
                          uint32_t boundGeneration) {
    if (state.current.kind != LevelKind::Mixer || index < 0 ||
        static_cast<size_t>(index) >= state.current.mixer.rows.size())
        return false;
    if (identity.empty())
        return state.current.mixer.generation == boundGeneration;
    return state.current.mixer.rows[index].sessionId == identity;
}

// A generation bump is NOT a reason to rebuild when the sessions at each
// index are still identical. Order, output IDs, appearance and layout must
// match, otherwise fall back to the original full-tree reconstruction.
bool CanReuseMixerRows(const State& state, const Snapshot& next) {
    if (state.current.kind != LevelKind::Mixer) return false;
    const auto& prev = state.current;
    const auto& a = prev.mixer;
    const auto& b = next.mixer;
    if (a.rows.size() != b.rows.size() ||
        a.outputs.size() != b.outputs.size() ||
        state.mixerView.mixerRowVisuals.size() != b.rows.size() ||
        !state.mixerView.mixerColumn || !state.mixerView.mixerRows ||
        state.mixerView.mixerColumn.Children().Size() == 0)
        return false;
    if (a.title != b.title || a.outputHeading != b.outputHeading ||
        a.selectedOutput != b.selectedOutput ||
        a.outputError != b.outputError ||
        a.outputExpanded != b.outputExpanded ||
        a.outputFailed != b.outputFailed ||
        a.maxVisibleRows != b.maxVisibleRows)
        return false;
    if (prev.anchor.left != next.anchor.left ||
        prev.anchor.top != next.anchor.top ||
        prev.anchor.right != next.anchor.right ||
        prev.anchor.bottom != next.anchor.bottom ||
        prev.scale != next.scale || prev.vertical != next.vertical ||
        prev.innerPadding != next.innerPadding ||
        prev.fontSize != next.fontSize ||
        prev.cornerRadius != next.cornerRadius ||
        prev.borderless != next.borderless ||
        prev.background != next.background ||
        prev.backgroundAlpha != next.backgroundAlpha ||
        prev.text != next.text || prev.track != next.track ||
        prev.accent != next.accent ||
        prev.layeredBackground != next.layeredBackground ||
        prev.backgroundMarkup != next.backgroundMarkup ||
        !osd_model::SameBrushLayers(prev.backgroundLayers,
                                    next.backgroundLayers))
        return false;
    for (size_t i = 0; i < b.outputs.size(); ++i)
        if (a.outputs[i].title != b.outputs[i].title ||
            a.outputs[i].selected != b.outputs[i].selected ||
            a.outputs[i].id != b.outputs[i].id)
            return false;
    for (size_t i = 0; i < b.rows.size(); ++i) {
        const auto& oldRow = a.rows[i];
        const auto& newRow = b.rows[i];
        const auto& visual = state.mixerView.mixerRowVisuals[i];
        if (!visual.mute || !visual.slider || !visual.percentLabel ||
            newRow.sessionId.empty() ||
            oldRow.sessionId != newRow.sessionId ||
            oldRow.title != newRow.title ||
            oldRow.iconPixels != newRow.iconPixels)
            return false;
    }
    return true;
}

// XAML redraws the changed properties. Preserve the control tree, wheel
// state, event registrations, ScrollViewer and Slider pointer capture.
void UpdateMixerRowVisuals(State& state, const Snapshot& next) {
    for (size_t i = 0; i < next.mixer.rows.size(); ++i) {
        auto& visual = state.mixerView.mixerRowVisuals[i];
        const auto& row = next.mixer.rows[i];
        if (visual.muted != row.muted) {
            if (visual.icon) {
                visual.icon.Opacity(row.muted ? .35 : 1.0);
            } else {
                visual.mute.Content(winrt::box_value(winrt::hstring(
                    row.muted ? osd_glyph::kMute : osd_glyph::kVolume)));
            }
            visual.muted = row.muted;
        }
        if (visual.enabled != row.enabled) {
            visual.mute.IsEnabled(row.enabled);
            visual.slider.IsEnabled(row.enabled);
            visual.enabled = row.enabled;
        }
        const int percent = std::clamp(row.percent, 0, 100);
        if (std::abs(visual.slider.Value() - static_cast<double>(percent)) > .49)
            visual.slider.Value(percent);
        const winrt::hstring percentText(std::to_wstring(percent) + L"%");
        if (visual.percentLabel.Text() != percentText)
            visual.percentLabel.Text(percentText);
    }
}

void DrawMixerSnapshot(State& state, const Snapshot& data) {
    if (!state.host || !state.canvas || !state.card ||
        !state.mixerView.mixerSurface || !state.mixerView.mixerColumn ||
        !state.mixerView.mixerRows || !state.mixerView.mixerRowsScroll ||
        !state.mixerView.mixerOutputs || !state.mixerView.mixerOutputsScroll) return;
    const bool reuseRows = CanReuseMixerRows(state, data);
    state.mixerView.mixerPopulating = true;
    if (state.current.kind != LevelKind::Mixer ||
        state.current.mixer.generation != data.mixer.generation) {
        state.mixerView.mixerWheelRow = -1;
        state.mixerView.mixerWheelRemainder = 0;
    }
    state.current = data;
    const auto frame = osd_layout::LevelFrame(data);
    const double w = frame.width, h = frame.height;
    const double pad = std::clamp(
        static_cast<double>(data.innerPadding), 6.0, 22.0) * .68;
    const double contentW = std::max(40.0, w - 2.0 * pad);
    const double radius = std::clamp(
        static_cast<double>(data.cornerRadius), 0.0, 34.0);

    state.canvas.IsHitTestVisible(true);
    state.canvas.Width(w);
    state.canvas.Height(h);
    ApplyBackground(state, data);
    state.card.CornerRadius(wx::CornerRadius{radius, radius, radius, radius});
    SetBackgroundLayerRadius(state, radius);
    state.card.BorderBrush(Brush(data.track));
    const double border = data.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{border, border, border, border});
    state.icon.Visibility(wx::Visibility::Collapsed);
    state.value.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Collapsed);
    state.fill.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeScroll.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardFrame.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardCaption.Visibility(wx::Visibility::Collapsed);
    state.clipboardView.clipboardImage.Source(nullptr);
    if (state.statusView.statusLineAnimating) KillTimer(state.host, kStatusLineTimer);
    state.statusView.statusLineAnimating = false;
    state.statusView.noticeExpanded = false;

    state.mixerView.mixerSurface.Visibility(wx::Visibility::Visible);
    state.mixerView.mixerSurface.Background(Brush(data.background, 0));
    state.mixerView.mixerSurface.Width(w);
    state.mixerView.mixerSurface.Height(h);
    controls::Canvas::SetLeft(state.mixerView.mixerSurface, 0.0);
    controls::Canvas::SetTop(state.mixerView.mixerSurface, 0.0);
    state.mixerView.mixerColumn.Width(contentW);
    state.mixerView.mixerColumn.Margin(wx::Thickness{pad, pad * .4, pad, pad * .4});
    if (reuseRows) {
        UpdateMixerRowVisuals(state, data);
        state.mixerView.mixerPopulating = false;
        ShowPositionedSurface(state, data, frame.insetX, frame.insetY, w, h);
        return;
    }
    state.mixerView.mixerRowVisuals.clear();
    state.mixerView.mixerColumn.Children().Clear();

    auto makeButton = [&](const std::wstring& title, double width,
                          double height) {
        controls::Button result;
        result.Content(winrt::box_value(winrt::hstring(title)));
        result.Width(std::max(16.0, width));
        result.Height(height);
        result.MinWidth(0.0);
        result.MinHeight(0.0);
        result.FontSize(std::clamp(data.fontSize - 1, 10, 18));
        result.Foreground(Brush(data.text));
        return result;
    };
    auto makeIconButton = [&](const std::wstring& glyph, double width) {
        auto button = makeButton(glyph, width, 32.0);
        button.FontFamily(media::FontFamily{L"Segoe Fluent Icons"});
        // The stock button's padding eats into 34px content bounds and
        // crops both the close glyph and 20px application bitmaps.
        button.Padding(wx::Thickness{0.0, 0.0, 0.0, 0.0});
        button.HorizontalContentAlignment(wx::HorizontalAlignment::Center);
        button.VerticalContentAlignment(wx::VerticalAlignment::Center);
        return button;
    };
    // Header: title and a real, hit-tested close command.
    controls::StackPanel header;
    header.Orientation(controls::Orientation::Horizontal);
    header.Height(36.0);
    controls::TextBlock title;
    title.Text(winrt::hstring(data.mixer.title));
    title.Width(std::max(1.0, contentW - 38.0));
    title.FontSize(std::clamp(data.fontSize + 1, 12, 22));
    title.Foreground(Brush(data.text));
    title.VerticalAlignment(wx::VerticalAlignment::Center);
    title.TextTrimming(wx::TextTrimming::CharacterEllipsis);
    header.Children().Append(title);
    auto close = makeIconButton(osd_glyph::kClose, 34.0);
    close.Click([&state](auto const&, auto const&) {
        SendMixerInput(state, InputAction::CloseMixer, -1);
    });
    header.Children().Append(close);
    state.mixerView.mixerColumn.Children().Append(header);

    const auto& model = data.mixer;
    auto output = makeButton(
        model.outputHeading + L": " + model.selectedOutput +
        (model.outputFailed ? L" (" + model.outputError + L")"
                            : L"  \uE70D"),
        contentW, 32.0);
    output.HorizontalAlignment(wx::HorizontalAlignment::Left);
    output.Click([&state](auto const&, auto const&) {
        SendMixerInput(state, InputAction::MixerToggleOutput, -1);
    });
    state.mixerView.mixerColumn.Children().Append(output);

    const double availableMenuH = std::max(32.0,
        h - 2.0 * pad - 36.0 - 32.0);
    const double outputRowsH = model.outputExpanded
        ? std::min(
            static_cast<double>(std::min<size_t>(
                model.outputs.size(), 4)) * 32.0, availableMenuH)
        : 0.0;
    state.mixerView.mixerOutputsScroll.Visibility(model.outputExpanded
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    if (model.outputExpanded) {
        state.mixerView.mixerOutputs.Children().Clear();
        for (size_t i = 0; i < model.outputs.size(); ++i) {
            const auto& item = model.outputs[i];
            auto option = makeButton(
                (item.selected ? L"\u2713 " : L"   ") + item.title,
                contentW, 32.0);
            const int index = static_cast<int>(i);
            option.Click([&state, index](auto const&, auto const&) {
                SendMixerInput(state, InputAction::MixerSelectOutput, index);
            });
            state.mixerView.mixerOutputs.Children().Append(option);
        }
        state.mixerView.mixerOutputsScroll.Width(contentW);
        state.mixerView.mixerOutputsScroll.Height(std::max(30.0, outputRowsH));
        state.mixerView.mixerColumn.Children().Append(state.mixerView.mixerOutputsScroll);
    }

    // The host size is a setting; the scrollbar uses the remaining space.
    // The number of visible audio sessions is bounded independently.
    const double rowH = std::max(38.0, data.fontSize * 2.5);
    const double availableH = std::max(32.0,
        h - 2.0 * pad - 36.0 - 32.0 - outputRowsH);
    const double maxH = std::max(rowH, model.maxVisibleRows * rowH);
    const double viewportH = std::min(availableH, maxH);
    state.mixerView.mixerRowsScroll.Width(contentW);
    state.mixerView.mixerRowsScroll.Height(viewportH);
    state.mixerView.mixerRows.Children().Clear();
    state.mixerView.mixerRowVisuals.reserve(model.rows.size());
    const double muteW = 34.0, percentW = 43.0;
    // Give the app name less of each row; preserve a dedicated gap between
    // the right-aligned percent label and the ScrollViewer's vertical bar.
    const double nameW = std::clamp(contentW * .22, 54.0, 112.0);
    const double scrollBarGap = 22.0;
    const double sliderW = std::max(40.0,
        contentW - muteW - nameW - percentW - scrollBarGap);
    for (size_t i = 0; i < model.rows.size(); ++i) {
        const auto& item = model.rows[i];
        const int index = static_cast<int>(i);
        const std::wstring rowIdentity = item.sessionId;
        const uint32_t boundGeneration = model.generation;
        MixerRowVisual visual;
        visual.muted = item.muted;
        visual.enabled = item.enabled;
        controls::StackPanel row;
        row.Orientation(controls::Orientation::Horizontal);
        row.Height(rowH);
        auto mute = makeIconButton(
            item.muted ? osd_glyph::kMute : osd_glyph::kVolume, muteW);
        if (item.iconPixels.size() == 20u * 20u * 4u) {
            auto bitmap = BitmapFromPixels(20, 20, item.iconPixels);
            if (bitmap) {
                controls::Image picture;
                picture.Width(20.0);
                picture.Height(20.0);
                picture.Stretch(media::Stretch::Uniform);
                picture.Opacity(item.muted ? .35 : 1.0);
                picture.Source(bitmap);
                mute.Content(picture);
                visual.icon = picture;
            }
        }
        mute.IsEnabled(item.enabled);
        mute.Click([&state, index, rowIdentity, boundGeneration](
                auto const&, auto const&) {
            if (!MixerRowBindingValid(state, index, rowIdentity, boundGeneration))
                return;
            SendMixerInput(state, InputAction::MixerToggleMute, index);
        });
        row.Children().Append(mute);
        controls::TextBlock name;
        name.Width(nameW);
        name.Text(winrt::hstring(item.title));
        name.FontSize(std::clamp(data.fontSize - 2, 10, 17));
        name.Foreground(Brush(data.text));
        name.TextTrimming(wx::TextTrimming::CharacterEllipsis);
        name.VerticalAlignment(wx::VerticalAlignment::Center);
        row.Children().Append(name);
        controls::Slider slider;
        slider.Width(sliderW);
        slider.Height(rowH);
        slider.Minimum(0.0);
        slider.Maximum(100.0);
        slider.SmallChange(1.0);
        slider.StepFrequency(1.0);
        slider.IsEnabled(item.enabled);
        slider.Value(std::clamp(item.percent, 0, 100));
        controls::TextBlock label;
        label.Width(percentW);
        label.FontSize(std::clamp(data.fontSize - 2, 10, 17));
        label.Text(winrt::hstring(
            std::to_wstring(std::clamp(item.percent, 0, 100)) + L"%"));
        label.TextAlignment(wx::TextAlignment::Right);
        label.VerticalAlignment(wx::VerticalAlignment::Center);
        label.Foreground(Brush(data.text));
        // Update feedback without rebuilding the panel during pointer drag.
        slider.ValueChanged(
            [&state, index, label, rowIdentity, boundGeneration](
                    auto const&, auto const& args) {
                if (state.mixerView.mixerPopulating ||
                    !MixerRowBindingValid(state, index, rowIdentity,
                                          boundGeneration)) return;
                const int percent = static_cast<int>(std::lround(
                    std::clamp(args.NewValue(), 0.0, 100.0)));
                label.Text(winrt::hstring(std::to_wstring(percent) + L"%"));
                SendMixerInput(state, InputAction::MixerSetPercent,
                               index, percent);
                ArmInteractionTimer(state, true);
            });
        // Slider/ScrollViewer can mark PointerWheelChanged as handled.
        // Observe handled events on the hovered Slider specifically,
        // without stealing wheel scrolling from the remaining Mixer list.
        slider.AddHandler(
            wx::UIElement::PointerWheelChangedEvent(),
            winrt::box_value(xinput::PointerEventHandler(
                [&state, index, rowIdentity, boundGeneration](
                        winrt::Windows::Foundation::IInspectable const& sender,
                        xinput::PointerRoutedEventArgs const& args) {
                    // Resolve the owning control from this event's sender:
                    // capturing slider in its own handler leaks the visual
                    // tree by forming a strong reference cycle.
                    auto slider = sender.try_as<controls::Slider>();
                    if (!slider || state.mixerView.mixerPopulating ||
                        !MixerRowBindingValid(state, index, rowIdentity,
                                              boundGeneration) ||
                        !slider.IsEnabled()) return;
                    const int delta = args.GetCurrentPoint(slider)
                        .Properties().MouseWheelDelta();
                    if (!delta) return;
                    if (state.mixerView.mixerWheelRow != index) {
                        state.mixerView.mixerWheelRow = index;
                        state.mixerView.mixerWheelRemainder = 0;
                    }
                    const int steps = osd_input::ConsumeWheelSteps(
                        delta, state.mixerView.mixerWheelRemainder);
                    if (steps) {
                        const int current = static_cast<int>(std::lround(
                            std::clamp(slider.Value(), 0.0, 100.0)));
                        const int next = std::clamp(
                            current + steps * osd_input::kWheelStepPercent,
                            0, 100);
                        if (next != current) slider.Value(next);
                        // ValueChanged owns immediate % feedback and the
                        // existing typed command to Core Audio.
                    }
                    ArmInteractionTimer(state, true);
                    args.Handled(true);
                })),
            true);
        row.Children().Append(slider);
        row.Children().Append(label);
        visual.mute = mute;
        visual.slider = slider;
        visual.percentLabel = label;
        state.mixerView.mixerRowVisuals.push_back(std::move(visual));
        state.mixerView.mixerRows.Children().Append(row);
    }
    state.mixerView.mixerRowsScroll.Visibility(model.outputExpanded
        ? wx::Visibility::Collapsed : wx::Visibility::Visible);
    // Output selection occupies the available panel viewport. Do not
    // allow its list to overlap active sliders or escape the card.
    if (!model.outputExpanded)
        state.mixerView.mixerColumn.Children().Append(state.mixerView.mixerRowsScroll);
    state.mixerView.mixerPopulating = false;
    ShowPositionedSurface(state, data, frame.insetX, frame.insetY, w, h);
}
void DrawSnapshot(State& state, const Snapshot& value) {
    const auto view = osd_model::SelectView(value.kind);
    if (view != osd_model::View::Level && state.levelSlider)
        state.levelSlider.Visibility(wx::Visibility::Collapsed);
    if (view == osd_model::View::Mixer) {
        DrawMixerSnapshot(state, value);
        return;
    }
    if (view == osd_model::View::Media) {
        DrawMediaSnapshot(state, value);
        return;
    }
    if (view == osd_model::View::Details) {
        DrawNoticeDetailsPanel(state, value);
        return;
    }
    if (state.mixerView.mixerChevron)
        state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    if (state.mixerView.mixerSurface)
        state.mixerView.mixerSurface.Visibility(wx::Visibility::Collapsed);
    if (state.mediaView.mediaSurface)
        state.mediaView.mediaSurface.Visibility(wx::Visibility::Collapsed);
    if (view == osd_model::View::ClipboardImage) {
        DrawClipboardImageSnapshot(state, value);
        return;
    }
    if (state.clipboardView.clipboardImage) state.clipboardView.clipboardImage.Source(nullptr);
    if (state.clipboardView.clipboardFrame)
        state.clipboardView.clipboardFrame.Visibility(wx::Visibility::Collapsed);
    if (state.clipboardView.clipboardCaption)
        state.clipboardView.clipboardCaption.Visibility(wx::Visibility::Collapsed);
    if (view == osd_model::View::Status) {
        DrawStatusSnapshot(state, value);
        return;
    }
    if (!state.host || !state.card || !state.canvas ||
        !state.icon || !state.value || !state.track || !state.fill ||
        !state.fillClip || !state.levelSlider || !state.statusView.statusTile) return;
    if (state.current.kind != value.kind) state.wheelRemainder = 0;
    state.current = value;
    state.scale = std::clamp(static_cast<double>(value.scale), 0.5, 6.0);
    state.canvas.IsHitTestVisible(true);
    if (state.statusView.statusLineAnimating && state.host)
        KillTimer(state.host, kStatusLineTimer);
    state.statusView.statusLineAnimating = false;
    state.statusView.noticeExpanded = false;
    state.statusView.noticeChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerChevron.Visibility(wx::Visibility::Collapsed);
    state.mixerView.mixerSurface.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeHeading.Visibility(wx::Visibility::Collapsed);
    state.statusView.noticeScroll.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTile.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusTitle.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusDetail.Visibility(wx::Visibility::Collapsed);
    state.statusView.statusUnderline.Visibility(wx::Visibility::Collapsed);
    state.track.Visibility(wx::Visibility::Visible);
    state.fill.Visibility(wx::Visibility::Visible);

    const auto frame = osd_layout::LevelFrame(value);
    const double insetX = frame.insetX, insetY = frame.insetY;
    const double bodyW = frame.width, bodyH = frame.height;
    const auto mixerButton =
        osd_layout::MixerButtonGeometry(value, bodyW, bodyH);
    state.canvas.Width(bodyW);
    state.canvas.Height(bodyH);
    ApplyBackground(state, value);
    const double radius = static_cast<double>(
        std::clamp(value.cornerRadius, 0, 34));
    state.card.CornerRadius(wx::CornerRadius{
        radius, radius, radius, radius});
    SetBackgroundLayerRadius(state, radius);
    state.card.BorderBrush(Brush(value.track));
    const double border = value.borderless ? 0.0 : 1.0;
    state.card.BorderThickness(wx::Thickness{
        border, border, border, border});
    state.icon.Foreground(Brush(value.text));
    state.value.Foreground(Brush(value.text));
    state.track.Fill(Brush(value.track));
    state.fill.Fill(Brush(value.accent));
    // Known 0-100% values always use the native Windows Slider's own track
    // and Thumb. Unknown raw brightness only shows the neutral fallback bar.
    const int percent = std::clamp(value.percent, 0, 100);
    const bool nativeLevel = value.valueKnown;
    state.levelSlider.Visibility(nativeLevel
        ? wx::Visibility::Visible : wx::Visibility::Collapsed);
    state.levelSlider.IsEnabled(nativeLevel);
    state.levelSlider.Orientation(value.vertical
        ? controls::Orientation::Vertical : controls::Orientation::Horizontal);
    state.levelSlider.IsDirectionReversed(false);
    state.levelSlider.Background(Brush(value.track));
    state.levelSlider.Foreground(Brush(value.accent));
    auto resources = state.levelSlider.Resources();
    const auto themeBrush = [&](const wchar_t* key, DWORD color) {
        resources.Insert(winrt::box_value(winrt::hstring(key)), Brush(color));
    };
    themeBrush(L"SliderTrackValueFill", value.accent);
    themeBrush(L"SliderTrackValueFillPointerOver", value.accent);
    themeBrush(L"SliderTrackValueFillPressed", value.accent);
    themeBrush(L"SliderTrackFill", value.track);
    themeBrush(L"SliderTrackFillPointerOver", value.track);
    themeBrush(L"SliderTrackFillPressed", value.track);
    state.levelPopulating = true;
    state.levelSlider.Value(percent);
    state.levelPopulating = false;
    state.track.Visibility(nativeLevel
        ? wx::Visibility::Collapsed : wx::Visibility::Visible);
    state.fill.Visibility(nativeLevel
        ? wx::Visibility::Collapsed : wx::Visibility::Visible);
    // Segoe Fluent Icons is provided by Windows; no external font assets.
    state.icon.Text(value.brightness ? osd_glyph::kBrightness :
        (value.muted || percent == 0 ? osd_glyph::kMute : osd_glyph::kVolume));
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

    // Fixed clearance for layout, not a native Slider appearance override.
    const double trackThickness = kFallbackTrackThickness;
    const int fillPercent = value.valueKnown ? percent : 0;
    const double wantedThumb = kNativeSliderLayoutClearance;

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
        // Controls and text have distinct measured rows. Layout budgets
        // modest gaps first and assigns the entire remainder to the Slider.
        const auto flow = osd_layout::VerticalLevelBounds(value,
            bodyW, bodyH, mixerButton.verticalReserve,
            iconW, iconH, labelW, labelH);
        const double iconTop = flow.iconTop;
        const double trackTop = flow.sliderTop;
        const double trackBottom = flow.sliderBottom;
        const double length = trackBottom - trackTop;
        const double filled = length * fillPercent / 100.0;
        const double centerX = bodyW / 2.0;
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

        controls::Canvas::SetLeft(state.icon,
            std::max(0.0, (bodyW - iconW) / 2.0));
        controls::Canvas::SetTop(state.icon, iconTop);
        state.value.Width(bodyW);
        state.value.TextAlignment(wx::TextAlignment::Center);
        controls::Canvas::SetLeft(state.value, 0.0);
        controls::Canvas::SetTop(state.value, flow.topPad);
        state.levelSlider.Width(std::max(30.0,
            std::max(trackThickness, wantedThumb) + 12.0));
        state.levelSlider.Height(std::max(1.0, length));
        controls::Canvas::SetLeft(state.levelSlider,
            centerX - state.levelSlider.Width() / 2.0);
        controls::Canvas::SetTop(state.levelSlider, trackTop);
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
        // Reserve the entire trailing button area, including its computed
        // rounded-corner clearance. Keep the value label/bar away from it.
        const double chevronSpace = mixerButton.visible
            ? bodyW - mixerButton.x + 4.0 : 0.0;
        const double freeWidth = std::max(0.0,
            bodyW - iconW - labelW - minTrack - chevronSpace);
        const double pad = std::min(inner + insetX,
            freeWidth / (value.showValue ? 4.0 : 3.0));
        const double gap = std::min(std::max(iconH, labelH),
            std::max(0.0,
                (freeWidth - 2.0 * pad) /
                (value.showValue ? 2.0 : 1.0)));
        const double iconX = pad;
        const double valueX = bodyW - pad - labelW - chevronSpace;
        const double trackX = iconX + iconW + gap;
        const double trackRight = value.showValue
            ? valueX - gap : bodyW - pad;
        const double trackW = std::max(0.0, trackRight - trackX);
        const double filled = trackW * fillPercent / 100.0;
        const double midY = bodyH / 2.0;
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

        controls::Canvas::SetLeft(state.icon, iconX);
        controls::Canvas::SetTop(state.icon,
            std::max(0.0, (bodyH - iconH) / 2.0));
        state.value.Width(labelW);
        state.value.TextAlignment(wx::TextAlignment::Right);
        controls::Canvas::SetLeft(state.value,
            std::max(0.0, valueX));
        controls::Canvas::SetTop(state.value,
            std::max(0.0, (bodyH - labelH) / 2.0));
        state.levelSlider.Width(std::max(1.0, trackW));
        state.levelSlider.Height(std::max(30.0,
            std::max(trackThickness, wantedThumb) + 12.0));
        controls::Canvas::SetLeft(state.levelSlider, trackX);
        controls::Canvas::SetTop(state.levelSlider,
            midY - state.levelSlider.Height() / 2.0);
        state.trackX = trackX;
        state.trackY = midY - trackThickness / 2.0;
        state.trackW = trackW;
        state.trackH = trackThickness;
        state.iconX = iconX;
        state.iconY = std::max(0.0, (bodyH - iconH) / 2.0);
        state.iconW = iconW;
        state.iconH = iconH;
    }

    if (mixerButton.visible) {
        state.mixerView.mixerChevron.Content(winrt::box_value(
            winrt::hstring(osd_layout::MixerChevronGlyph(value.mixerDirection))));
        state.mixerView.mixerChevron.Width(mixerButton.size);
        state.mixerView.mixerChevron.Height(mixerButton.size);
        controls::Canvas::SetLeft(state.mixerView.mixerChevron, mixerButton.x);
        controls::Canvas::SetTop(state.mixerView.mixerChevron, mixerButton.y);
        state.mixerView.mixerChevron.Visibility(wx::Visibility::Visible);
    }
    ShowPositionedSurface(state, value, insetX, insetY, bodyW, bodyH);
}
void DeliverPending(State& root); // Defined after native/XAML host creation.
LRESULT WndProcImpl(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
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
                    Wh_Log(L"Fluent OSD/XAML: draw exception 0x%08lX; disabling renderer",
                           static_cast<unsigned long>(ex.code()));
                    GetXamlState().lifecycle.MarkFailedAndWithdrawReady();
                    try { HideAll(*state); }
                    catch (...) { Wh_Log(L"Fluent OSD/XAML: draw cleanup failed"); }
                    PostQuitMessage(0);
                } catch (...) {
                    Wh_Log(L"Fluent OSD/XAML: unexpected draw exception; disabling renderer");
                    GetXamlState().lifecycle.MarkFailedAndWithdrawReady();
                    try { HideAll(*state); }
                    catch (...) { Wh_Log(L"Fluent OSD/XAML: draw cleanup failed"); }
                    PostQuitMessage(0);
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
                        if (!state->viewOnly) {
                            FadeMirrorsWith(*state, state->fadeStart);
                            if (state->pairedVolume &&
                                state->pairedVolume->host &&
                                state->pairedVolume->card) {
                                auto& master = *state->pairedVolume;
                                master.fading = master.fadeOut = true;
                                master.fadeStart = state->fadeStart;
                                SetTimer(master.host, kFadeTimer, 16, nullptr);
                            }
                        }
                    } else HideSurface(*state);
                } else if (wp == kStatusLineTimer) {
                    AdvanceStatusUnderline(*state, GetTickCount64());
                } else if (wp == kMediaProgressTimer) {
                    AdvanceMediaTimeline(*state);
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
        case WM_NCHITTEST:
            if (state && state->viewOnly) return HTTRANSPARENT;
            break;
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
// C++/WinRT exceptions must never escape a Win32 window callback.
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    try {
        return WndProcImpl(hwnd, msg, wp, lp);
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"Fluent OSD/XAML: HWND callback exception 0x%08lX",
               static_cast<unsigned long>(ex.code()));
    } catch (...) {
        Wh_Log(L"Fluent OSD/XAML: unexpected HWND callback exception");
    }
    GetXamlState().lifecycle.MarkFailedAndWithdrawReady();
    auto* state = reinterpret_cast<State*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (state) {
        try { HideAll(*state); }
        catch (...) { Wh_Log(L"Fluent OSD/XAML: error cleanup also failed"); }
    }
    PostQuitMessage(0);
    return 0;
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
    icon.Text(osd_glyph::kVolume);
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

    controls::Slider levelSlider;
    levelSlider.Visibility(wx::Visibility::Collapsed);
    levelSlider.Minimum(0.0);
    levelSlider.Maximum(100.0);
    levelSlider.SmallChange(5.0);
    levelSlider.StepFrequency(1.0);
    levelSlider.MinWidth(0.0);
    levelSlider.MinHeight(0.0);
    levelSlider.IsThumbToolTipEnabled(false);
    levelSlider.ValueChanged([&state](auto const&, auto const& args) {
        if (state.levelPopulating || !state.current.valueKnown ||
            (state.current.kind != LevelKind::Volume &&
             state.current.kind != LevelKind::NativeBrightness &&
             state.current.kind != LevelKind::DdcBrightness)) return;
        const int percent = static_cast<int>(std::lround(
            std::clamp(args.NewValue(), 0.0, 100.0)));
        if (percent == state.current.percent) return;
        state.current = osd_model::WithPercent(state.current, percent);
        state.value.Text(winrt::hstring(std::to_wstring(percent) + L"%"));
        SendInput(state, InputAction::SetPercent, percent);
        ArmInteractionTimer(state, true);
    });
    canvas.Children().Append(levelSlider);

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

    controls::Button noticeChevron;
    noticeChevron.Visibility(wx::Visibility::Collapsed);
    noticeChevron.Content(winrt::box_value(winrt::hstring(osd_glyph::kChevronDown)));
    noticeChevron.FontFamily(media::FontFamily{L"Segoe Fluent Icons"});
    noticeChevron.MinWidth(0.0);
    noticeChevron.MinHeight(0.0);
    noticeChevron.Padding(wx::Thickness{0.0, 0.0, 0.0, 0.0});
    noticeChevron.HorizontalContentAlignment(wx::HorizontalAlignment::Center);
    noticeChevron.VerticalContentAlignment(wx::VerticalAlignment::Center);
    noticeChevron.Click([&state](auto const&, auto const&) {
        if (state.current.kind == LevelKind::NoticeStatus)
            ToggleNoticeDetails(state);
    });
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


    // A Mixer button is part of the same native volume Island. Its click
    // becomes a typed command; the render thread owns no Core Audio object.
    controls::Button mixerChevron;
    mixerChevron.Visibility(wx::Visibility::Collapsed);
    mixerChevron.Content(winrt::box_value(winrt::hstring(osd_glyph::kChevronDown)));
    mixerChevron.FontFamily(media::FontFamily{L"Segoe Fluent Icons"});
    // Default Button styles can exceed the width of a vertical OSD.
    mixerChevron.MinWidth(0.0);
    mixerChevron.MinHeight(0.0);
    mixerChevron.Padding(wx::Thickness{0.0, 0.0, 0.0, 0.0});
    mixerChevron.HorizontalContentAlignment(wx::HorizontalAlignment::Center);
    mixerChevron.VerticalContentAlignment(wx::VerticalAlignment::Center);
    mixerChevron.Click([&state](auto const&, auto const&) {
        if (state.current.kind == LevelKind::Volume)
            SendInput(state, InputAction::OpenMixer, 0);
    });
    canvas.Children().Append(mixerChevron);

    // One native XAML panel peer for Mixer, with owned scroll viewports.
    controls::StackPanel mixerColumn;
    controls::StackPanel mixerRows;
    controls::ScrollViewer mixerRowsScroll;
    mixerRowsScroll.VerticalScrollBarVisibility(
        controls::ScrollBarVisibility::Auto);
    mixerRowsScroll.HorizontalScrollBarVisibility(
        controls::ScrollBarVisibility::Disabled);
    mixerRowsScroll.Content(mixerRows);
    controls::StackPanel mixerOutputs;
    controls::ScrollViewer mixerOutputsScroll;
    mixerOutputsScroll.Visibility(wx::Visibility::Collapsed);
    mixerOutputsScroll.VerticalScrollBarVisibility(
        controls::ScrollBarVisibility::Auto);
    mixerOutputsScroll.HorizontalScrollBarVisibility(
        controls::ScrollBarVisibility::Disabled);
    mixerOutputsScroll.Content(mixerOutputs);
    controls::Border mixerSurface;
    mixerSurface.Visibility(wx::Visibility::Collapsed);
    mixerSurface.Child(mixerColumn);
    canvas.Children().Append(mixerSurface);

    controls::Canvas mediaSurface;
    mediaSurface.Visibility(wx::Visibility::Collapsed);
    mediaSurface.Background(Brush(0,0));
    canvas.Children().Append(mediaSurface);

    controls::Viewbox viewbox;
    viewbox.Stretch(media::Stretch::Fill);
    viewbox.Child(canvas);
    // XAML Grid shares the card geometry; brushes are behind the Viewbox.
    controls::Grid backgroundStack;
    backgroundStack.Children().Append(viewbox);
    card.Child(backgroundStack);
    state.source.Content(card);
    state.card = card;
    state.backgroundStack = backgroundStack;
    state.canvas = canvas;
    state.viewbox = viewbox;
    state.icon = icon;
    state.track = track;
    state.fill = fill;
    state.fillClip = fillClip;
    state.levelSlider = levelSlider;
    state.value = value;
    state.statusView.statusTile = statusTile;
    state.statusView.statusGlyph = statusGlyph;
    state.statusView.statusTitle = statusTitle;
    state.statusView.statusDetail = statusDetail;
    state.statusView.statusUnderline = statusUnderline;
    state.statusView.noticeChevron = noticeChevron;
    state.statusView.noticeHeading = noticeHeading;
    state.statusView.noticeRows = noticeRows;
    state.statusView.noticeScroll = noticeScroll;
    state.clipboardView.clipboardFrame = clipboardFrame;
    state.clipboardView.clipboardImage = clipboardImage;
    state.clipboardView.clipboardCaption = clipboardCaption;
    state.mixerView.mixerChevron = mixerChevron;
    state.mixerView.mixerSurface = mixerSurface;
    state.mixerView.mixerColumn = mixerColumn;
    state.mixerView.mixerRows = mixerRows;
    state.mixerView.mixerOutputs = mixerOutputs;
    state.mixerView.mixerRowsScroll = mixerRowsScroll;
    state.mixerView.mixerOutputsScroll = mixerOutputsScroll;
    state.mediaView.mediaSurface = mediaSurface;
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
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE |
            (state.viewOnly ? WS_EX_TRANSPARENT : 0),
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
    Wh_Log(L"Fluent OSD/XAML: rounded=0x%08lX border=0x%08lX frame=0x%08lX",
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
    if (state.viewOnly)
        SetWindowLongPtrW(state.island, GWL_EXSTYLE,
            GetWindowLongPtrW(state.island, GWL_EXSTYLE) |
                WS_EX_TRANSPARENT);
    if (!SetWindowPos(state.island, nullptr, 0, 0, kWidth, kHeight,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_SHOWWINDOW))
        winrt::throw_hresult(HRESULT_FROM_WIN32(GetLastError()));
    CreateContent(state);
}

void CloseSurface(State& state) {
    try { HideSurface(state); }
    catch (...) { Wh_Log(L"Fluent OSD/XAML: teardown hide failed"); }
    // Detach Composition callbacks from all user-defined layers before
    // tearing down the XAML Island and its owning STA.
    try { ClearBackgroundLayers(state); }
    catch (...) { Wh_Log(L"Fluent OSD/XAML: layer detach failed"); }
    state.cachedBackgroundLayers.clear();
    // Detach module-owned Composition callbacks before Island destruction.
    if (state.card) {
        try { state.card.Background(nullptr); }
        catch (...) { Wh_Log(L"Custom background detach failed"); }
    }
    state.backgroundCached = false;
    state.mediaView.ReleaseBeforeIslandClose();
    state.mixerView.ReleaseBeforeIslandClose();
    state.clipboardView.ReleaseBeforeIslandClose();
    state.statusView.ReleaseBeforeIslandClose();
    state.levelSlider = nullptr;
    state.fillClip = nullptr;
    state.fill = nullptr;
    state.track = nullptr;
    state.value = nullptr;
    state.icon = nullptr;
    state.canvas = nullptr;
    state.viewbox = nullptr;
    state.backgroundStack = nullptr;
    state.card = nullptr;
    if (state.source) {
        try { state.source.Content(nullptr); state.source.Close(); }
        catch (...) { Wh_Log(L"Fluent OSD/XAML: island close failed"); }
        state.source = nullptr;
    }
    state.island = nullptr;
    if (state.host) DestroyWindow(state.host);
    state.host = nullptr;
}

// The primary STA HWND is the dispatcher. DDC uses one HWND and Island
// per *physical* target. DDC updates are deltas; other categories reconcile
// complete snapshots. Each DDC peer keeps its own visibility timer.
void DeliverPending(State& root) {
    std::vector<Snapshot> batch = GetXamlState().snapshots.Take();
    if (batch.empty()) return;
    const bool ddc = batch.front().kind == LevelKind::DdcBrightness;
    const bool attached = batch.size() >= 2 &&
        ((batch[0].kind == LevelKind::Volume &&
          (batch[1].kind == LevelKind::Media ||
           batch[1].kind == LevelKind::Mixer)) ||
         (batch[0].kind == LevelKind::NoticeStatus &&
          batch[1].kind == LevelKind::NoticeDetails));
    const std::wstring panelKey = !attached ? L"" :
        batch[1].kind == LevelKind::Media ? L"media" :
        batch[1].kind == LevelKind::NoticeDetails ? L"notice-details" : L"mixer";
    const size_t extraStart = attached ? 2 : (ddc ? 0 : 1);
    std::unordered_set<std::wstring> active;
    if (attached) active.insert(panelKey);
    for (size_t i = extraStart; i < batch.size(); ++i)
        if ((ddc || batch[i].mirrorView) && !batch[i].key.empty())
            active.insert(batch[i].key);

    root.attachedPeerOpen = false;
    root.pairedPanel = nullptr;
    for (auto it = root.peers.begin(); it != root.peers.end();) {
        const State& peer = *it->second;
        // A DDC snapshot only updates its changed physical targets. Keep
        // unrelated, still-visible DDC Islands and their independent timers.
        // Hidden peers are reclaimed on the next batch; other categories
        // retain their existing full-snapshot reconciliation behavior.
        const bool independentDdc = ddc &&
            peer.current.kind == LevelKind::DdcBrightness &&
            peer.host && IsWindowVisible(peer.host);
        if (active.find(it->first) == active.end() && !independentDdc) {
            it->second->pairedVolume = nullptr;
            CloseSurface(*it->second);
            it = root.peers.erase(it);
        } else ++it;
    }
    auto renderPeer = [&](const Snapshot& snap, const std::wstring& key,
                          bool readOnly) -> State* {
        auto found = root.peers.find(key);
        if (found == root.peers.end()) {
            auto peer = std::make_unique<State>();
            peer->viewOnly = readOnly;
            try { CreateSurface(*peer, GetModuleHandleW(nullptr)); }
            catch (const winrt::hresult_error& ex) {
                Wh_Log(L"Fluent OSD/XAML: peer create failed 0x%08lX",
                    static_cast<unsigned long>(ex.code()));
                CloseSurface(*peer);
                return nullptr;
            }
            found = root.peers.emplace(key, std::move(peer)).first;
        }
        DrawSnapshot(*found->second, snap);
        return found->second.get();
    };
    if (ddc) {
        // DDC's per-display value is authoritative, never a clone.
        HideSurface(root);
        for (const auto& snap : batch)
            if (!snap.key.empty()) (void)renderPeer(snap,snap.key,false);
        return;
    }
    DrawSnapshot(root, batch.front());
    if (attached) {
        root.attachedPeerOpen = true;
        if (root.host) KillTimer(root.host, kHideTimer);
        State* panel = renderPeer(batch[1], panelKey, false);
        if (!panel) {
            root.attachedPeerOpen = false;
            HideSurface(root);
            return;
        }
        root.pairedPanel = panel;
        panel->pairedVolume = &root;
        // A metadata/progress refresh is not user interaction. Re-arming
        // every 3s while the player worker polls prevents the configured
        // timeout from ever firing (especially with Media duration 3s).
        // On first show, ShowPositionedSurface already arms the timer.
        if (!batch[1].passiveRefresh)
            ArmInteractionTimer(*panel, false);
    }
    for (size_t i = extraStart; i < batch.size(); ++i)
        if (batch[i].mirrorView && !batch[i].key.empty())
            (void)renderPeer(batch[i], batch[i].key, true);
}

void TryEnableIslandTransparency() {
    // Official IXamlSourceTransparency applies to every Island on the
    // current XAML STA. Log QI failure; do not silently claim opacity works.
    try {
        auto currentWindow = wx::Window::Current();
        if (!currentWindow) {
            Wh_Log(L"Fluent OSD/XAML: Window.Current unavailable for transparency");
            return;
        }
        ComPtr<IXamlSourceTransparency> transparency;
        HRESULT hr = winrt::get_unknown(currentWindow)->QueryInterface(
            kTransparencyIID,
            reinterpret_cast<void**>(transparency.GetAddressOf()));
        if (SUCCEEDED(hr) && transparency)
            hr = transparency->put_IsBackgroundTransparent(1);
        Wh_Log(L"Fluent OSD/XAML: Island transparency HRESULT=0x%08lX",
            static_cast<unsigned long>(hr));
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"Fluent OSD/XAML: transparency initialization exception 0x%08lX",
            static_cast<unsigned long>(ex.code()));
    }
}

DWORD WINAPI ThreadProc(void*) {
    State root;
    MSG msg{};
    bool apartment = false, registered = false;
    const HINSTANCE instance = GetModuleHandleW(nullptr);
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    GetXamlState().lifecycle.PublishThreadId(GetCurrentThreadId());
    try {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
        apartment = true;
        if (!GetXamlState().lifecycle.IsStopping()) {
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
            if (!GetXamlState().lifecycle.IsStopping()) {
                CreateSurface(root, instance);
                // Window.Current is available once the first Island has
                // been created; the interface applies to the entire STA.
                TryEnableIslandTransparency();
                GetXamlState().lifecycle.PublishReady(root.host);
                Wh_Log(L"Fluent OSD/XAML: renderer ready (per-display DDC)");
                while (!GetXamlState().lifecycle.IsStopping() &&
                       GetMessageW(&msg, nullptr, 0, 0) > 0) {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
            }
        }
    } catch (const winrt::hresult_error& ex) {
        Wh_Log(L"Fluent OSD/XAML: startup failed 0x%08lX (%s)",
               static_cast<unsigned long>(ex.code()), ex.message().c_str());
        GetXamlState().lifecycle.MarkFailed();
    } catch (...) {
        Wh_Log(L"Fluent OSD/XAML: unexpected startup exception");
        GetXamlState().lifecycle.MarkFailed();
    }
    GetXamlState().lifecycle.WithdrawReady();
    // Break STA-only peer references before either Island is destroyed;
    // CloseSurface releases pointer captures and may invoke callbacks.
    root.attachedPeerOpen = false;
    root.pairedPanel = nullptr;
    for (auto& peer : root.peers) {
        peer.second->pairedVolume = nullptr;
        CloseSurface(*peer.second);
    }
    root.peers.clear(); // Release peer WinRT refs while STA is still alive.
    CloseSurface(root);
    if (root.manager) {
        try { root.manager.Close(); }
        catch (...) { Wh_Log(L"Fluent OSD/XAML: manager close failed"); }
        root.manager = nullptr;
    }
    if (registered) UnregisterClassW(kClass, instance);
    if (apartment) {
        // Drop the STA-owned WinRT stream before CoUninitialize; the
        // no_destroy TLS cache must not release it during thread exit.
        osd_blur::ReleaseThreadNoiseCache();
        winrt::uninit_apartment();
    }
    GetXamlState().lifecycle.PublishThreadId(0);
    return 0;
}
void Start(HWND receiver) {
    GetXamlState().lifecycle.Start(receiver);
}
bool Restart(HWND receiver) {
    return GetXamlState().lifecycle.Restart(receiver);
}
bool IsFailed() {
    return GetXamlState().lifecycle.IsFailed();
}
bool IsReady() {
    return GetXamlState().lifecycle.ReadyWindow() != nullptr &&
           !GetXamlState().lifecycle.IsFailed();
}
bool ShowBatch(const std::vector<Snapshot>& snapshots) {
    const HWND hwnd = GetXamlState().lifecycle.ReadyWindow();
    if (!hwnd || GetXamlState().lifecycle.IsStopping() || GetXamlState().lifecycle.IsFailed() ||
        snapshots.empty()) return false;
    GetXamlState().snapshots.Publish(snapshots);
    return PostMessageW(hwnd, kShowMessage, 0, 0) != FALSE;
}
bool IsPrimaryVisible() {
    const HWND hwnd=GetXamlState().lifecycle.ReadyWindow();
    return hwnd && IsWindowVisible(hwnd)!=FALSE;
}
void Hide() {
    const HWND hwnd = GetXamlState().lifecycle.ReadyWindow();
    if (hwnd) PostMessageW(hwnd, kHideMessage, 0, 0);
}
void Stop() {
    GetXamlState().lifecycle.Stop();
}
} // namespace xaml_osd

constexpr WCHAR kWindowClass[] = L"WH.NativeOSD.DDC.01E7AFB2";
constexpr UINT kXamlFailureTrayCallback = WM_APP + 696;
constexpr UINT kXamlFailureTrayId = 0x32032;
constexpr ULONG_PTR kCopyDataTag = 0x1E7AFB2;
constexpr UINT_PTR kEventBatchTimer = 322;
constexpr UINT_PTR kDdcBatchTimer = 324;
constexpr UINT_PTR kNetworkRefreshTimer = 325;
constexpr UINT kNetworkDebounceMs = 320;
constexpr UINT kNetworkSettleMs = 640;
// Shell startup is signaled by the InputSite creation hook, not polled.
constexpr UINT kDdcBatchDelayMs = 90;
constexpr UINT_PTR kMediaAnimationTimer = 323;
constexpr UINT kMediaAnimationIntervalMs = 100;
constexpr ULONGLONG kMediaRefreshIntervalMs = 3000;
constexpr UINT kBrightnessWheelResultMessage = WM_APP + 326;
constexpr UINT kBluetoothQueueMessage = WM_APP + 327;
constexpr UINT kBluetoothConfigMessage = WM_APP + 328;
constexpr int kMaxMixerOutputDevices = 64;
constexpr int kWheelStepPercent = osd_input::kWheelStepPercent; // Shared with XAML.
constexpr UINT kNativeOsdMessage = WM_APP + 320;
constexpr UINT kMediaUpdateMessage = WM_APP + 321;
constexpr UINT kLockToggleMessage = WM_APP + 322;
constexpr UINT kAudioRefreshMessage = WM_APP + 323;
constexpr UINT kNetworkNoticeMessage = WM_APP + 324;
constexpr UINT kNativeExtraMessage = WM_APP + 325;
constexpr UINT kShellInputSiteReadyMessage = WM_APP + 329;
constexpr UINT kNetworkConfigMessage = WM_APP + 330;
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
enum class NoticeIcon { Clipboard, ClipboardFile, ClipboardText, Usb, Bluetooth, Network, Wifi,
                        Keyboard, Mouse, Headset, Headphone, Speaker };
// Central icon selection; classification never needs renderer objects.
namespace osd_glyph {
constexpr PCWSTR ForNotice(NoticeIcon icon) {
    switch (icon) {
        case NoticeIcon::Clipboard:     return kClipboard;
        case NoticeIcon::ClipboardFile: return kClipboardFile;
        case NoticeIcon::ClipboardText: return kClipboardText;
        case NoticeIcon::Usb:           return kUsb;
        case NoticeIcon::Bluetooth:     return kBluetooth;
        case NoticeIcon::Network:       return kNetwork;
        case NoticeIcon::Wifi:          return kWifi;
        case NoticeIcon::Keyboard:      return kKeyboardStandard;
        case NoticeIcon::Mouse:         return kMouse;
        case NoticeIcon::Headset:       return kHeadset;
        case NoticeIcon::Headphone:     return kHeadphone;
        case NoticeIcon::Speaker:       return kSpeakers;
    }
    return nullptr;
}
constexpr PCWSTR ForNative(Kind kind) {
    switch (kind) {
        case Kind::Keyboard:   return kKeyboardClassic;
        case Kind::Airplane:   return kAirplane;
        case Kind::Camera:     return kCamera;
        case Kind::Microphone: return kMicrophone;
        case Kind::Desktop:    return kTaskView;
        case Kind::Text:       return kPage;
        default:               return nullptr;
    }
}
} // namespace osd_glyph

enum class NoticeAction { Connected, Disconnected, Removed, NetworkChanged,
                          WifiEnabled, WifiDisabled };
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
constexpr float kClipboardImageCanvasW = 264.0f;
constexpr float kClipboardImageCanvasH = 224.0f;
constexpr float kClipboardImageMaxW = 224.0f;
constexpr float kClipboardImageMaxH = 164.0f;
constexpr int kLockVk[4] = {VK_CAPITAL, VK_NUMLOCK, VK_SCROLL, VK_INSERT};

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
    XamlRendererFailed,
    XamlRetryHint,
    ProcessPrefix,
    On,
    Off,
    AudioOutput,
    AudioSwitchFailed,
    NoAudioOutputs,
    MasterVolume,
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
    {L"XAML renderer unavailable", L"XAML 顯示引擎無法使用"}, // XamlRendererFailed
    {L"Click here or the temporary tray icon to retry.", L"點選通知或暫時的通知區圖示，即可手動重試。"}, // XamlRetryHint
    {L"Process ", L"處理程序 "}, // ProcessPrefix
    {L"On", L"開啟"}, // On
    {L"Off", L"關閉"}, // Off
    {L"Output", L"輸出裝置"}, // AudioOutput
    {L"Switch failed", L"切換失敗"}, // AudioSwitchFailed
    {L"No playback devices", L"沒有可用的播放裝置"}, // NoAudioOutputs
    {L"Master volume", L"主音量"}, // MasterVolume
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
    DWORD observedValue = 0;
    bool valueObserved = false; // Read or successful write, per physical handle.
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

// --- Config state, read across UI and Windhawk settings threads ---
struct OsdSettingsState {
    std::atomic<int> displayLanguage{0}; // 0=Auto, 1=English, 2=zh-TW
    std::atomic<bool> hideAllNativeOsd{false};
    std::atomic<bool> hide[static_cast<int>(Kind::Count)]{};
    std::atomic<bool> showCustomNative[static_cast<int>(Kind::Count)]{};
    std::atomic<bool> showDdcBrightness{false};
    std::atomic<bool> verticalVolumeBrightness{true};
    std::atomic<bool> fromExplorer{true};
    std::atomic<bool> fromTwinkle{true};
    std::atomic<int> vcpCode{16};

    std::atomic<int> globalDurationMs{3000};
    std::atomic<bool> individualDurations{false};
    std::atomic<int> durationOverrides[static_cast<int>(DurationKind::Count)]{};
    // Only the dedicated OSD UI thread reads/writes this current category.

    std::atomic<int> ddcTheme{0};
    std::atomic<int> ddcSizePercent{75};
    // Independent logical dimensions; global DPI and size % are applied later.
    std::atomic<int> horizontalOsdWidth{380};
    std::atomic<int> horizontalOsdHeight{72};
    std::atomic<int> verticalOsdWidth{72};
    std::atomic<int> verticalOsdHeight{200};
    std::atomic<int> horizontalSmtcHeight{200};
    std::atomic<int> horizontalMixerHeight{200};
    std::atomic<int> verticalSmtcWidth{380};
    std::atomic<int> verticalMixerWidth{380};
    std::atomic<bool> ddcBorderless{true};
    std::atomic<bool> showSmtcOnVolume{false};
    std::atomic<bool> showMediaArtwork{true};
    std::atomic<bool> showMediaControls{true};
    std::atomic<int> mediaControlSizePercent{100};
    std::atomic<bool> controlButtonSquare{false};
    std::atomic<int> controlButtonCornerRadius{6};
    std::atomic<bool> showMixerArrow{false};
    std::atomic<int> mixerMaxRows{6};
    std::atomic<bool> showLockKeys[4]{};
    std::atomic<int> innerPadding{14};
    std::atomic<bool> showClipboardOsd{false};
    std::atomic<bool> clipboardTextPreview{false};
    std::atomic<bool> clipboardImagePreview{true};
    std::atomic<int> clipboardChars{48};
    std::atomic<bool> showUsbEvents{false};
    std::atomic<bool> showBluetoothEvents{false};
    std::atomic<bool> showNetworkEvents{false};
    std::atomic<bool> fadeEnabled{true};
    std::atomic<int> fadeDuration{160};
    // Layout and palette options. Values are atomic because settings can be
    // reloaded outside the Explorer OSD UI thread.
    std::atomic<int> accentMode{0};
    std::atomic<DWORD> customAccent{0};
    std::atomic<bool> validCustomAccent{false};
    std::atomic<int> backgroundMode{0};
    std::atomic<DWORD> customBackground{0};
    std::atomic<bool> validCustomBackground{false};
    std::atomic<int> textMode{0};
    std::atomic<DWORD> customText{0};
    std::atomic<bool> validCustomText{false};
    std::atomic<int> trackMode{0};
    std::atomic<DWORD> customTrack{0};
    std::atomic<bool> validCustomTrack{false};
    std::atomic<int> backgroundOpacity{96};
    std::atomic<bool> useLayeredBackground{false};
    mutable std::mutex backgroundLayersMutex;
    std::vector<osd_model::BrushLayer> backgroundLayers;
    std::atomic<int> cornerRadius{17};
    std::atomic<int> fontSize{15};
    std::atomic<int> iconSize{16};
    std::atomic<bool> showSun{true};
    std::atomic<bool> showValue{true};
    // 0=source, 1=primary, 2=selected DISPLAYn, 3=all screens
    std::atomic<int> displayOutputMode{0};
    std::atomic<int> displayOutputNumber{1};
    std::atomic<int> position{5};
    std::atomic<int> offsetX{0};
    std::atomic<int> offsetY{0};

    // The background mode and its ordered layers form one coherent snapshot.
    // Windhawk may reload settings outside the dedicated controller thread.
    void SetBrushLayers(bool layered, std::vector<osd_model::BrushLayer> layers) {
        std::lock_guard<std::mutex> lock(backgroundLayersMutex);
        backgroundLayers = std::move(layers);
        useLayeredBackground.store(layered, std::memory_order_release);
    }
    void CopyBrushLayers(bool& layered, std::vector<osd_model::BrushLayer>& layers) const {
        std::lock_guard<std::mutex> lock(backgroundLayersMutex);
        layered = useLayeredBackground.load(std::memory_order_acquire);
        if (layered) layers = backgroundLayers;
        else layers.clear();
    }
};
// Publish complete settings versions separately from the controller.
// Readers hold shared ownership until their operations finish.
struct SettingsModuleState final {
    std::mutex reloadMutex;
    std::shared_ptr<const OsdSettingsState> published =
        std::make_shared<const OsdSettingsState>();

    std::shared_ptr<const OsdSettingsState> Snapshot() const {
        return std::atomic_load_explicit(&published, std::memory_order_acquire);
    }
    void Publish(std::shared_ptr<const OsdSettingsState> next) {
        std::atomic_store_explicit(
            &published, std::move(next), std::memory_order_release);
    }
    void ReleaseAfterThreadsStop() {
        std::atomic_store_explicit(
            &published, std::shared_ptr<const OsdSettingsState>{},
            std::memory_order_release);
    }
};
SettingsModuleState& GetSettingsModuleState() {
    [[clang::no_destroy]] static SettingsModuleState instance;
    return instance;
}
std::shared_ptr<const OsdSettingsState> GetSettingsState() {
    return GetSettingsModuleState().Snapshot();
}

// Shell creation trampoline ABI is owned by the host module.
using CreateWindowInBand_t =
    HWND (WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD,
                   int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID, DWORD);
// Entry points and OSD receiver lifecycle; workers keep their own handles.
struct ModuleRuntimeState {
    bool isExplorer = false;
    HMODULE ddcDll = nullptr, confirmatorDll = nullptr;
    std::atomic<bool> loggedUnmapped{false};
    HANDLE uiThread = nullptr, uiReady = nullptr;
    DWORD uiThreadId = 0;
    HWND receiveWnd = nullptr; // Controller-thread only.
    // The single cross-thread publication of the receiver HWND.
    std::atomic<HWND> publishedReceiver{nullptr};
    bool clipboardListener = false;
    bool xamlFailureTrayVisible = false; // Receiver-thread only.
    HDEVNOTIFY usbNotification = nullptr;
    std::atomic<bool> closing{false};
    bool shellXamlStarted = false;
    CreateWindowInBand_t createWindowInBandOriginal = nullptr;

    void PublishReceiver(HWND hwnd) {
        publishedReceiver.store(hwnd, std::memory_order_release);
    }
    HWND ReceiverForCallbacks() const {
        const HWND hwnd = publishedReceiver.load(std::memory_order_acquire);
        return closing.load(std::memory_order_acquire) ? nullptr : hwnd;
    }
    void BeginShutdown() {
        closing.store(true, std::memory_order_release);
        publishedReceiver.store(nullptr, std::memory_order_release);
    }
};
// Module host lifecycle is owned by CoreModuleState below.


struct NoticeBatch {
    NoticeCategory category = NoticeCategory::Usb;
    NoticeAction action = NoticeAction::Connected;
    std::vector<std::wstring> names;
    std::unordered_set<std::wstring> identities;
    NoticeIcon icon = NoticeIcon::Bluetooth;
    bool iconKnown = false, mixedIcons = false;
    bool pending = false;
};

struct NoticeRuntimeState {
    // All non-atomic fields are owned by the OSD receiver thread.
    std::wstring title, body;
    NoticeIcon icon = NoticeIcon::Clipboard;
    bool panelOpen = false;
    uint32_t generation = 1;
    DurationKind duration = DurationKind::Devices;
    NoticeBatch batch;
    std::vector<std::wstring> details;
    std::unordered_map<std::wstring, std::wstring> usbNames;
    // Clipboard data is opt-in, and the owned bitmap is released explicitly.
    HBITMAP clipboardThumbnail = nullptr;

    void ResetBatch() { batch = NoticeBatch{}; }
};
// Notice state is owned by NoticeModuleState below.


struct NetInterfaceState {
    std::wstring name;
    bool connected = false;
    NoticeIcon icon = NoticeIcon::Network; // Captured with interface identity.
    std::wstring wlanProfile; // Last/current Native Wi-Fi profile, not IP adapter name.
    bool wlanRadioKnown = false; // Independent of association/connected.
    bool wlanRadioOn = false;
};
struct NetworkRuntimeState {
    // Callback-shared references are atomic. Other fields are receiver-thread owned.
    HMODULE dll = nullptr;
    HANDLE notification = nullptr;
    HANDLE ipNotification = nullptr;
    HANDLE addressNotification = nullptr;
    std::atomic<int> previousLevel{-1};
    bool refreshPending = false;
    bool refreshSecondPass = false;
    bool sawInterfaceTransition = false;
    bool hintPending = false;
    int hintLevel = -1;
    bool uiSettingEnabled = false;
    std::unordered_map<std::string, NetInterfaceState> interfaces;

    void ResetRefresh() {
        refreshPending = false;
        refreshSecondPass = false;
        sawInterfaceTransition = false;
        hintPending = false;
        hintLevel = -1;
    }
    void ReleaseAfterControllerStops() {
        std::unordered_map<std::string, NetInterfaceState> oldInterfaces;
        interfaces.swap(oldInterfaces);
    }
    // Stop subscriptions before WLAN teardown; release iphlpapi.dll last.
    // Preserve handles on cancellation failure for another shutdown attempt.
    bool CancelCallbacksOnControllerThread();
    void ReleaseLibraryOnControllerThread() {
        if (notification || ipNotification || addressNotification) {
            Wh_Log(L"Fluent OSD/network: iphlpapi still owns active registrations");
            return;
        }
        if (dll) FreeLibrary(dll);
        dll = nullptr;
    }
};
// Network state is owned by ConnectivityModuleState below.


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
struct MediaCommand {
    int action = 0;  // 1-3=transport; 4=seek; 5-6=shuffle/repeat; 7=next SMTC session
    INT64 position = 0; // SMTC 100-ns ticks for action 4
};
struct MediaRuntimeState {
    // Snapshot publication is worker -> controller; UI owns current.
    SRWLOCK snapshotLock = SRWLOCK_INIT;
    MediaSnapshot pending;
    MediaSnapshot current;
    ULONGLONG lastRefreshTick = 0;
    HANDLE wake = nullptr, thread = nullptr;
    std::atomic<bool> stop{false};
    SRWLOCK commandLock = SRWLOCK_INIT;
    std::vector<MediaCommand> commands;

    void Publish(MediaSnapshot value) {
        AcquireSRWLockExclusive(&snapshotLock);
        pending = std::move(value);
        ReleaseSRWLockExclusive(&snapshotLock);
    }
    void ConsumeOnControllerThread() {
        AcquireSRWLockShared(&snapshotLock);
        current = pending;
        ReleaseSRWLockShared(&snapshotLock);
        lastRefreshTick = GetTickCount64();
    }
    // Wake handle publication and signalling share the command lock, so a
    // controller request cannot race CloseHandle during worker shutdown.
    void PublishWake(HANDLE handle) {
        AcquireSRWLockExclusive(&commandLock);
        wake = handle;
        ReleaseSRWLockExclusive(&commandLock);
    }
    void Request(int action, INT64 position) {
        AcquireSRWLockExclusive(&commandLock);
        if (wake && !stop.load()) {
            // Repeated seeking keeps its latest value; transport stays FIFO.
            if (action == 4)
                commands.erase(std::remove_if(commands.begin(), commands.end(),
                    [](const MediaCommand& entry) { return entry.action == 4; }),
                    commands.end());
            if (action && commands.size() < 32)
                commands.push_back(MediaCommand{action, position});
            SetEvent(wake);
        }
        ReleaseSRWLockExclusive(&commandLock);
    }
    void SignalStop() {
        AcquireSRWLockExclusive(&commandLock);
        stop.store(true);
        if (wake) SetEvent(wake);
        ReleaseSRWLockExclusive(&commandLock);
    }
    void CloseWakeAfterWorkerStops() {
        AcquireSRWLockExclusive(&commandLock);
        if (wake) CloseHandle(wake);
        wake = nullptr;
        ReleaseSRWLockExclusive(&commandLock);
    }
    std::vector<MediaCommand> TakeCommands() {
        std::vector<MediaCommand> result;
        AcquireSRWLockExclusive(&commandLock);
        result.swap(commands);
        ReleaseSRWLockExclusive(&commandLock);
        return result;
    }
    // Normal mod unload only: both SMTC worker and controller are joined.
    // no_destroy intentionally prevents DLL_PROCESS_DETACH destructors.
    void ReleaseStorageAfterThreadsStop() {
        MediaSnapshot oldPending, oldCurrent;
        std::vector<MediaCommand> oldCommands;
        AcquireSRWLockExclusive(&snapshotLock);
        std::swap(pending, oldPending);
        std::swap(current, oldCurrent);
        lastRefreshTick = 0;
        ReleaseSRWLockExclusive(&snapshotLock);
        AcquireSRWLockExclusive(&commandLock);
        commands.swap(oldCommands);
        ReleaseSRWLockExclusive(&commandLock);
        // Old storage is destroyed after both locks are released.
    }
};
// Explicit media worker lifetime is owned by AudioModuleState below.


struct MixerEntry {
    std::wstring title;
    std::wstring sessionId; // IAudioSessionControl2 session instance identity.
    HICON appIcon = nullptr; // owned; released before clear
    std::vector<uint8_t> iconPixels; // Captured once per session refresh.
    Microsoft::WRL::ComPtr<ISimpleAudioVolume> volume;
    float scalar = 0;
    bool muted = false;
};
std::vector<uint8_t> MixerIconPixels(HICON);
struct AudioOutputOption { std::wstring id; std::wstring name; };
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
// Mixer COM interfaces never enter the XAML STA.
struct MixerRuntimeState {
    std::vector<MixerEntry> entries;
    Microsoft::WRL::ComPtr<IAudioEndpointVolume> master;
    float masterLevel = 0;
    bool masterMuted = false;
    std::vector<AudioOutputOption> outputOptions;
    std::wstring outputId;
    bool outputSwitchFailed = false;
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> notifyEnumerator;
    Microsoft::WRL::ComPtr<MixerOutputNotifications> notify;

    // All these operations stay on the dedicated controller's COM apartment.
    // A callback can still arrive until its registration is revoked.
    void StopNotificationsOnControllerThread() {
        if (notify) notify->Stop();
        if (notify && notifyEnumerator) {
            (void)notifyEnumerator->UnregisterEndpointNotificationCallback(
                notify.Get());
        }
        notify.Reset();
        notifyEnumerator.Reset();
    }
    void ClearSessionsOnControllerThread() {
        // HICON ownership is independent of the Core Audio ComPtr objects.
        for (auto& entry : entries) {
            if (entry.appIcon) DestroyIcon(entry.appIcon);
            entry.appIcon = nullptr;
        }
        entries.clear();
        master.Reset();
    }
    void ClearOutputDevicesOnControllerThread() {
        outputOptions.clear();
        outputId.clear();
    }
    void PrepareRefreshOnControllerThread() {
        // Preserve previously selected output metadata until enumeration
        // actually starts, just as the prior refresh path did.
        ClearSessionsOnControllerThread();
        masterLevel = 0;
        masterMuted = false;
    }
    void ClosePanelOnControllerThread() {
        StopNotificationsOnControllerThread();
        ClearSessionsOnControllerThread();
        // Retain outputId and status fields as in the existing close path.
        outputOptions.clear();
    }
    void ReleaseStorageOnControllerThread() {
        // Called during controller shutdown, before CoUninitialize().
        StopNotificationsOnControllerThread();
        ClearSessionsOnControllerThread();
        ClearOutputDevicesOnControllerThread();
        masterLevel = 0;
        masterMuted = false;
        outputSwitchFailed = false;
        // no_destroy means these capacities are not freed at DLL detach.
        std::vector<MixerEntry> oldEntries;
        std::vector<AudioOutputOption> oldOptions;
        std::wstring oldOutputId;
        entries.swap(oldEntries);
        outputOptions.swap(oldOptions);
        outputId.swap(oldOutputId);
    }
};
// Core Audio / Mixer lifetime is owned by AudioModuleState below.


// Interactive panel state is independent of Core Audio ownership.
struct PanelControllerState {
    float scale = 1.0f;
    bool mixerOpen = false, mixerOutputExpanded = false;
    bool mediaOpen = false;
    uint32_t mixerGeneration = 1, mediaGeneration = 1;
};
// All Core Audio COM operations retain their controller-apartment owner.
// no_destroy retains the existing explicit worker/controller cleanup contract.
struct AudioModuleState final {
    MediaRuntimeState media;
    MixerRuntimeState mixer;
    PanelControllerState panel;
};
AudioModuleState& GetAudioState() {
    [[clang::no_destroy]] static AudioModuleState instance;
    return instance;
}

// Low-level keyboard hook and key latches share a single UI-thread owner.
struct LockKeyState {
    HHOOK hook = nullptr;
    bool pressed[4]{};
    bool toggle[4]{};
    int last = 0;
    bool lastValue = false;
};
// Notice and keyboard state remain controller-thread owned.
struct NoticeModuleState final {
    NoticeRuntimeState notice;
    LockKeyState keys;
    void ReleaseAfterControllerStops() {
        // The receiver already revoked its hook and released its HBITMAP.
        // Only dynamic storage belongs here; never release HWND/HHOOK off-owner.
        std::wstring oldTitle, oldBody;
        NoticeBatch oldBatch;
        std::vector<std::wstring> oldDetails;
        std::unordered_map<std::wstring, std::wstring> oldUsbNames;
        notice.title.swap(oldTitle);
        notice.body.swap(oldBody);
        std::swap(notice.batch, oldBatch);
        notice.details.swap(oldDetails);
        notice.usbNames.swap(oldUsbNames);
    }
};
NoticeModuleState& GetNoticeState() {
    [[clang::no_destroy]] static NoticeModuleState instance;
    return instance;
}

// --- Event state and worker coordination ---
struct NativeEventMailbox {
    SRWLOCK lock = SRWLOCK_INIT;
    NativeEventInfo pending;
    bool posted = false;

    bool Offer(NativeEventInfo value) {
        AcquireSRWLockExclusive(&lock);
        pending = std::move(value);
        const bool needsPost = !posted;
        posted = true;
        ReleaseSRWLockExclusive(&lock);
        return needsPost;
    }
    void PostFailed() {
        AcquireSRWLockExclusive(&lock);
        posted = false;
        ReleaseSRWLockExclusive(&lock);
    }
    NativeEventInfo Take() {
        AcquireSRWLockExclusive(&lock);
        NativeEventInfo value = std::move(pending);
        pending = NativeEventInfo{};
        posted = false;
        ReleaseSRWLockExclusive(&lock);
        return value;
    }
    // Invoked only after Windhawk removes native hooks and the receiver exits.
    void ReleaseAfterHooksRemoved() {
        NativeEventInfo oldPending;
        AcquireSRWLockExclusive(&lock);
        std::swap(pending, oldPending);
        posted = false;
        ReleaseSRWLockExclusive(&lock);
    }
};
struct NativeEventModuleState final {
    NativeEventMailbox mailbox;
};
NativeEventModuleState& GetNativeEventState() {
    [[clang::no_destroy]] static NativeEventModuleState instance;
    return instance;
}

struct DdcRuntimeState {
    // This guard belongs to the DDC owner type but remains per-calling-thread.
    static thread_local bool insideHighLevelSet;
    // Handle identity cache is hook-thread shared; batches and pending writes
    // are exclusively owned by the native controller thread.
    struct PendingWrite {
        BrightnessEvent event{};
        DWORD previousValue = 0, generation = 0;
    };

    SRWLOCK handleLock = SRWLOCK_INIT;
    std::unordered_map<ULONG_PTR, PhysicalInfo> handles;
    std::vector<BrightnessEvent> batchEvents;
    std::vector<DdcTargetState> targets;
    std::vector<PendingWrite> pendingWrites;
    bool batchPending = false;
    WCHAR lastUnresolved[CCHDEVICENAME]{};
    WCHAR lastTarget[CCHDEVICENAME]{};
    int lastConfirmedNative = -1;
    DWORD lastConfirmedDdc = 0;

    // DDC hooks can run concurrently in Explorer or Twinkle Tray. Keep
    // identity lookup, range adjustment and handle lifetime under one lock.
    PhysicalInfo LookupHandle(HANDLE handle) {
        AcquireSRWLockShared(&handleLock);
        auto it = handles.find(reinterpret_cast<ULONG_PTR>(handle));
        PhysicalInfo result = it == handles.end() ? PhysicalInfo{} : it->second;
        ReleaseSRWLockShared(&handleLock);
        return result;
    }
    void UpdateHandleRange(HANDLE handle, DWORD low, DWORD high) {
        if (high <= low) return;
        AcquireSRWLockExclusive(&handleLock);
        auto it = handles.find(reinterpret_cast<ULONG_PTR>(handle));
        if (it != handles.end()) {
            it->second.minimum = low;
            it->second.maximum = high;
        }
        ReleaseSRWLockExclusive(&handleLock);
    }
    void ObserveRead(HANDLE handle, DWORD value) {
        AcquireSRWLockExclusive(&handleLock);
        auto it = handles.find(reinterpret_cast<ULONG_PTR>(handle));
        if (it != handles.end()) {
            it->second.observedValue = value;
            it->second.valueObserved = true;
        }
        ReleaseSRWLockExclusive(&handleLock);
    }
    bool RecordSuccessfulWrite(HANDLE handle, DWORD value) {
        AcquireSRWLockExclusive(&handleLock);
        auto it = handles.find(reinterpret_cast<ULONG_PTR>(handle));
        bool changed = true; // Unknown baseline: do not suppress the first write.
        if (it != handles.end()) {
            changed = !it->second.valueObserved ||
                it->second.observedValue != value;
            it->second.observedValue = value;
            it->second.valueObserved = true;
        }
        ReleaseSRWLockExclusive(&handleLock);
        return changed;
    }
    void RememberHandles(PCWSTR device, DWORD count,
                         LPPHYSICAL_MONITOR items) {
        AcquireSRWLockExclusive(&handleLock);
        for (DWORD i = 0; i < count; ++i) {
            PhysicalInfo info{};
            wcscpy_s(info.device, device);
            info.physicalIndex = i;
            handles[reinterpret_cast<ULONG_PTR>(items[i].hPhysicalMonitor)] = info;
        }
        ReleaseSRWLockExclusive(&handleLock);
    }
    void ForgetHandle(HANDLE handle) {
        AcquireSRWLockExclusive(&handleLock);
        handles.erase(reinterpret_cast<ULONG_PTR>(handle));
        ReleaseSRWLockExclusive(&handleLock);
    }
    void ForgetHandles(DWORD count, LPPHYSICAL_MONITOR items) {
        if (!items || count > 32) return;
        AcquireSRWLockExclusive(&handleLock);
        for (DWORD i = 0; i < count; ++i)
            handles.erase(reinterpret_cast<ULONG_PTR>(items[i].hPhysicalMonitor));
        ReleaseSRWLockExclusive(&handleLock);
    }

    // Batch state belongs solely to the controller. Its most-recent write
    // wins per physical monitor; a refreshed monitor moves to the back.
    bool AccumulateOnControllerThread(const BrightnessEvent& event) {
        const bool firstInBatch = !batchPending;
        auto sameTarget = [&](const BrightnessEvent& existing) {
            return existing.physicalIndex == event.physicalIndex &&
                   _wcsicmp(existing.device, event.device) == 0;
        };
        auto same = std::find_if(batchEvents.begin(), batchEvents.end(),
                                 sameTarget);
        if (same != batchEvents.end()) {
            batchEvents.erase(same);
            batchEvents.push_back(event);
        } else if (batchEvents.size() < kMaxDdcTargets) {
            batchEvents.push_back(event);
        }
        if (batchEvents.empty()) return false;
        batchPending = true;
        return firstInBatch;
    }
    std::vector<BrightnessEvent> TakeBatchOnControllerThread() {
        if (!batchPending) return {};
        batchPending = false;
        std::vector<BrightnessEvent> events = std::move(batchEvents);
        batchEvents.clear();
        return events;
    }
    // Pending writes have a different lifetime from event batches. Repeated
    // writes preserve the first known-good value for failure rollback.
    void RememberPendingWriteOnControllerThread(
            const BrightnessEvent& event, DWORD generation) {
        auto pending = std::find_if(pendingWrites.begin(), pendingWrites.end(),
            [&](const PendingWrite& item) {
                return item.event.physicalIndex == event.physicalIndex &&
                    _wcsicmp(item.event.device, event.device) == 0;
            });
        if (pending == pendingWrites.end()) {
            if (pendingWrites.size() >= kMaxDdcTargets)
                pendingWrites.erase(pendingWrites.begin());
            pendingWrites.push_back({event, event.value, generation});
        } else {
            pending->generation = generation;
        }
    }
    bool TakePendingWriteOnControllerThread(
            DWORD generation, PendingWrite& result) {
        auto pending = std::find_if(pendingWrites.begin(), pendingWrites.end(),
            [generation](const PendingWrite& item) {
                return item.generation == generation;
            });
        if (pending == pendingWrites.end()) return false;
        result = *pending;
        pendingWrites.erase(pending);
        return true;
    }
    void ClearPendingOnControllerThread() {
        batchPending = false;
        batchEvents.clear();
        targets.clear();
        pendingWrites.clear();
    }
    // DDC hooks still exist during BeforeUninit; clear their identity cache
    // only in ModUninit, after Windhawk has removed those hooks.
    void ReleaseAfterHooksRemoved() {
        std::unordered_map<ULONG_PTR, PhysicalInfo> oldHandles;
        AcquireSRWLockExclusive(&handleLock);
        handles.swap(oldHandles);
        ReleaseSRWLockExclusive(&handleLock);
        std::vector<BrightnessEvent> oldEvents;
        std::vector<DdcTargetState> oldTargets;
        std::vector<PendingWrite> oldPendingWrites;
        batchEvents.swap(oldEvents);
        targets.swap(oldTargets);
        pendingWrites.swap(oldPendingWrites);
        batchPending = false;
    }
};
thread_local bool DdcRuntimeState::insideHighLevelSet = false;
// DDC hook data and worker use the same explicit unload phase.


struct BrightnessWriterState {
    SRWLOCK lock = SRWLOCK_INIT;
    std::vector<BrightnessWheelTask> pending;
    HANDLE wake = nullptr, thread = nullptr;
    std::atomic<bool> stop{false};
    DWORD generation = 0;

    static bool SameTarget(const BrightnessWheelTask& a,
                           const BrightnessWheelTask& b) {
        return a.native == b.native &&
            (a.native ||
             (a.monitor.physicalIndex == b.monitor.physicalIndex &&
              _wcsicmp(a.monitor.device, b.monitor.device) == 0));
    }
    // The existing queue lock also protects wake-handle publication and
    // signalling against shutdown closing the handle on another thread.
    void PublishWake(HANDLE handle) {
        AcquireSRWLockExclusive(&lock);
        wake = handle;
        ReleaseSRWLockExclusive(&lock);
    }
    bool ReadyForCommands() {
        AcquireSRWLockShared(&lock);
        const bool ready = wake && !stop.load();
        ReleaseSRWLockShared(&lock);
        return ready;
    }
    // Preserve one latest write per physical target and the hard queue cap.
    void EnqueueAndSignal(const BrightnessWheelTask& task) {
        AcquireSRWLockExclusive(&lock);
        if (!wake || stop.load()) {
            ReleaseSRWLockExclusive(&lock);
            return;
        }
        auto found = std::find_if(pending.begin(), pending.end(),
            [&](const BrightnessWheelTask& queued) {
                return SameTarget(queued, task);
            });
        if (found != pending.end()) {
            *found = task;
        } else if (pending.size() < kMaxDdcTargets + 1) {
            pending.push_back(task);
        } else {
            pending.erase(pending.begin());
            pending.push_back(task);
        }
        SetEvent(wake);
        ReleaseSRWLockExclusive(&lock);
    }
    void SignalStop() {
        AcquireSRWLockExclusive(&lock);
        stop.store(true);
        if (wake) SetEvent(wake);
        ReleaseSRWLockExclusive(&lock);
    }
    void CloseWakeAfterWorkerStops() {
        AcquireSRWLockExclusive(&lock);
        if (wake) CloseHandle(wake);
        wake = nullptr;
        ReleaseSRWLockExclusive(&lock);
    }
    bool IsSuperseded(const BrightnessWheelTask& task) {
        AcquireSRWLockShared(&lock);
        const bool superseded = std::any_of(pending.begin(), pending.end(),
            [&](const BrightnessWheelTask& newer) {
                return newer.generation > task.generation &&
                       SameTarget(newer, task);
            });
        ReleaseSRWLockShared(&lock);
        return superseded;
    }
    std::vector<BrightnessWheelTask> TakePending() {
        std::vector<BrightnessWheelTask> result;
        AcquireSRWLockExclusive(&lock);
        result.swap(pending);
        ReleaseSRWLockExclusive(&lock);
        return result;
    }
    void ReleaseStorageAfterWorkerStops() {
        std::vector<BrightnessWheelTask> oldPending;
        AcquireSRWLockExclusive(&lock);
        pending.swap(oldPending);
        ReleaseSRWLockExclusive(&lock);
    }
};
// DDC and brightness writer state are owned independently of the UI module.
struct BrightnessModuleState final {
    DdcRuntimeState ddc;
    BrightnessWriterState writer;
};
BrightnessModuleState& GetBrightnessState() {
    [[clang::no_destroy]] static BrightnessModuleState instance;
    return instance;
}

struct PopupPlacement {
    float scale = 1.0f;
    int width = 0, height = 0;
    RECT work{}, monitorBounds{}, bounds{};
};
// Controller-thread-owned geometry belongs to the existing UI presentation
// state. There is no independent global Placement lifetime to manage.
struct PlacementModuleState final {
    PopupPlacement current{};
    bool valid = false;
};
static_assert(std::is_trivially_destructible_v<PlacementModuleState>,
              "Placement state must remain trivially destructible");
// UI-thread-owned platform provider and current on-screen event.
struct UiPresentationState {
    HMODULE combase = nullptr;
    RoUninitialize_t roUninitialize = nullptr;
    bool roInitialized = false;
    IUiSettings3Raw* uiSettings = nullptr;
    BrightnessEvent visible{};
    PopupKind popupKind = PopupKind::DdcBrightness;
    PlacementModuleState placement;
    NativeEventInfo nativeEventCurrent;
    int nativePercent = 0;
    bool nativePercentKnown = false;
    bool nativeMuted = false;
    void ReleaseAfterControllerStops() {
        std::wstring oldText;
        nativeEventCurrent.text.swap(oldText);
    }
};
struct CoreModuleState final {
    ModuleRuntimeState module;
    UiPresentationState presentation;
    void ReleaseAfterThreadsStop() {
        presentation.ReleaseAfterControllerStops();
    }
};
// Settings callbacks and the receiver must not race global STL/mutex
// destructors during Explorer process termination.
CoreModuleState& GetCoreState() {
    [[clang::no_destroy]] static CoreModuleState instance;
    return instance;
}

// ============================================================
// Shared helpers: localization, settings, UI state and geometry
// ============================================================

bool UseTraditionalChinese() {
    const int selected = GetSettingsState()->displayLanguage.load(std::memory_order_relaxed);
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
UINT OsdDuration(DurationKind kind, const OsdSettingsState& settings) {
    if (!settings.individualDurations.load(std::memory_order_relaxed))
        return static_cast<UINT>(settings.globalDurationMs.load(std::memory_order_relaxed));
    return static_cast<UINT>(settings.durationOverrides[static_cast<int>(kind)]
        .load(std::memory_order_relaxed));
}
UINT OsdDuration(DurationKind kind) {
    const auto settings = GetSettingsState();
    return OsdDuration(kind, *settings);
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
        case NoticeAction::WifiEnabled: return Tr(OsdText::Enabled);
        case NoticeAction::WifiDisabled: return Tr(OsdText::Disabled);
    }
    return L"";
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


BYTE OsdBackgroundAlpha(const OsdSettingsState& settings) {
    return static_cast<BYTE>((settings.backgroundOpacity.load() * 255 + 50) / 100);
}

// A single direction and anchor rule drives panel placement and chevrons.
// --- Common placement, sizing and monitor identity ---
float MainLogicalWidth() {
    const auto settings = GetSettingsState();
    return static_cast<float>(settings->verticalVolumeBrightness.load()
        ? settings->verticalOsdWidth.load() : settings->horizontalOsdWidth.load());
}
float MainLogicalHeight() {
    const auto settings = GetSettingsState();
    return static_cast<float>(settings->verticalVolumeBrightness.load()
        ? settings->verticalOsdHeight.load() : settings->horizontalOsdHeight.load());
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

struct FindDisplay {
    WCHAR name[CCHDEVICENAME]{};
    HMONITOR monitor = nullptr;
};
BOOL CALLBACK FindDisplayCallback(HMONITOR m, HDC, LPRECT, LPARAM context) {
    auto* f = reinterpret_cast<FindDisplay*>(context);
    MONITORINFOEXW mi{};
    mi.cbSize = sizeof(mi);
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

// ============================================================
// Forward declarations: cross-feature callbacks and UI entrypoints
// ============================================================
void MovePopupToDisplay(const BrightnessEvent&);
void FlushNoticeBatch();
void ShowNotice(std::wstring, std::wstring, DurationKind, NoticeIcon);
void ShowMigratedXamlDeviceNotice(DurationKind);
void ShowMigratedXamlClipboardNotice();
void ResetXamlMixerController();
void ResetXamlMediaController();
bool BuildMixerPanelAnchors(RECT& main, RECT& panel, float scale);
bool ShowXamlMediaPanel(bool passiveRefresh = false);
std::vector<std::pair<std::string, NetInterfaceState>> GetNetworkSnapshot(
    bool* succeeded = nullptr);
namespace bt_monitor {
    void Start();
    void Stop();
    void Drain();
} // namespace bt_monitor

void LoadSettings() {
    // Reloads are serialized, but readers never lock against the writer.
    std::lock_guard<std::mutex> reload(GetSettingsModuleState().reloadMutex);
    auto staged = std::make_shared<OsdSettingsState>();
    OsdSettingsState& settings = *staged;
    PCWSTR selectedLanguage = Wh_GetStringSetting(L"displayLanguage");
    const int chosen = selectedLanguage &&
        _wcsicmp(selectedLanguage, L"zh-TW") == 0 ? 2 :
        selectedLanguage && _wcsicmp(selectedLanguage, L"en") == 0 ? 1 : 0;
    settings.displayLanguage.store(chosen, std::memory_order_relaxed);
    Wh_FreeStringSetting(selectedLanguage);
    settings.hideAllNativeOsd.store(
        Wh_GetIntSetting(L"NativeHide.hideAllNativeOsd") != 0);
    LoadBoolSettings(settings.hide, kNativeHideSettingKeys);
    LoadBoolSettings(settings.showCustomNative, kCustomNativeSettingKeys);
    settings.showDdcBrightness.store(Wh_GetIntSetting(L"CustomOSD.Switches.showDdcBrightness") != 0);
    settings.verticalVolumeBrightness.store(Wh_GetIntSetting(L"CustomOSD.Layout.verticalVolumeBrightness") != 0);
    settings.fromExplorer.store(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcFromExplorer") != 0);
    settings.fromTwinkle.store(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcFromTwinkle") != 0);
    settings.vcpCode.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcVcpCode"), 0, 255));
    settings.globalDurationMs.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Timing.globalDurationMs"), 500, 20000));
    settings.individualDurations.store(
        Wh_GetIntSetting(L"CustomOSD.Timing.individualDurations") != 0);
    for (int i = 0; i < static_cast<int>(DurationKind::Count); ++i) {
        std::wstring path = L"CustomOSD.Timing.";
        path += kDurationSettingKeys[i];
        settings.durationOverrides[i].store(std::clamp(
            Wh_GetIntSetting(path.c_str()), 500, 20000));
    }
    PCWSTR selectedTheme = Wh_GetStringSetting(L"CustomOSD.Appearance.ddcTheme");
    const int selectedMode = selectedTheme &&
        (_wcsicmp(selectedTheme, L"light") == 0 || wcscmp(selectedTheme, L"1") == 0)
        ? 1 : selectedTheme &&
        (_wcsicmp(selectedTheme, L"dark") == 0 || wcscmp(selectedTheme, L"2") == 0)
        ? 2 : 0;
    settings.ddcTheme.store(selectedMode);
    Wh_FreeStringSetting(selectedTheme);
    settings.ddcSizePercent.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcSizePercent"), 55, 120));
    settings.horizontalOsdWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.horizontalOsdWidth"), 300, 650));
    settings.horizontalOsdHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.horizontalOsdHeight"), 72, 220));
    settings.verticalOsdWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.verticalOsdWidth"), 72, 180));
    settings.verticalOsdHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.verticalOsdHeight"), 160, 430));
    settings.horizontalSmtcHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.horizontalSmtcHeight"), 176, 480));
    settings.horizontalMixerHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.horizontalMixerHeight"), 176, 480));
    settings.verticalSmtcWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.verticalSmtcWidth"), 300, 650));
    settings.verticalMixerWidth.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ExpandedPanelSize.verticalMixerWidth"), 300, 650));
    settings.ddcBorderless.store(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcBorderless") != 0);
    settings.showSmtcOnVolume.store(Wh_GetIntSetting(L"CustomOSD.Switches.showSmtcOnVolume") != 0);
    settings.showMediaArtwork.store(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.showMediaArtwork") != 0);
    settings.showMediaControls.store(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.showMediaControls") != 0);
    settings.mediaControlSizePercent.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.mediaControlSizePercent"), 90, 135));
    {
        PCWSTR shape = Wh_GetStringSetting(L"CustomOSD.Appearance.controlButtonShape");
        settings.controlButtonSquare.store(shape && _wcsicmp(shape, L"square") == 0);
        Wh_FreeStringSetting(shape);
    }
    settings.controlButtonCornerRadius.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Appearance.controlButtonCornerRadius"), 0, 16));
    settings.showMixerArrow.store(Wh_GetIntSetting(L"CustomOSD.Switches.showVolumeMixerArrow") != 0);
    settings.mixerMaxRows.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.mixerMaxRows"), 3, 16));
    LoadBoolSettings(settings.showLockKeys, kLockSettingKeys);
    settings.innerPadding.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcInnerPadding"), 6, 22));
    settings.showClipboardOsd.store(Wh_GetIntSetting(L"CustomOSD.Switches.showClipboardOsd") != 0);
    settings.clipboardTextPreview.store(Wh_GetIntSetting(L"CustomOSD.ClipboardAndDevices.clipboardTextPreview") != 0);
    settings.clipboardImagePreview.store(Wh_GetIntSetting(L"CustomOSD.ClipboardAndDevices.clipboardImagePreview") != 0);
    settings.clipboardChars.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.ClipboardAndDevices.clipboardMaxChars"), 12, 100));
    settings.showUsbEvents.store(Wh_GetIntSetting(L"CustomOSD.Switches.showUsbEvents") != 0);
    settings.showBluetoothEvents.store(Wh_GetIntSetting(L"CustomOSD.Switches.showBluetoothEvents") != 0);
    settings.showNetworkEvents.store(Wh_GetIntSetting(L"CustomOSD.Switches.showNetworkEvents") != 0);
    settings.fadeEnabled.store(Wh_GetIntSetting(L"CustomOSD.Layout.fadeOsd") != 0);
    settings.fadeDuration.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.fadeDurationMs"), 60, 450));
    settings.accentMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcAccentMode"));
    settings.backgroundMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcBackgroundMode"));
    settings.textMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcTextMode"));
    settings.trackMode.store(IsCustomMode(L"CustomOSD.Appearance.ddcTrackMode"));
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomAccent", settings.customAccent, settings.validCustomAccent);
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomBackground", settings.customBackground, settings.validCustomBackground);
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomText", settings.customText, settings.validCustomText);
    LoadHexSetting(L"CustomOSD.Appearance.ddcCustomTrack", settings.customTrack, settings.validCustomTrack);
    settings.backgroundOpacity.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcBackgroundOpacity"), 0, 100));
    {
        PCWSTR effect = Wh_GetStringSetting(L"CustomOSD.Appearance.ddcBackgroundEffect");
        const bool layered = effect && _wcsicmp(effect, L"layers") == 0;
        Wh_FreeStringSetting(effect);
        std::vector<osd_model::BrushLayer> layers;
        if (layered) {
            // Windhawk array ordering is controlled by Add item / reorder.
            // Limit the loaded layers to five to bound Explorer GPU resources.
            for (int i = 0; i < 5; ++i) {
                PCWSTR value = Wh_GetStringSetting(
                    L"CustomOSD.Appearance.ddcBrushLayers[%d].markup", i);
                std::wstring def = value ? value : L"";
                Wh_FreeStringSetting(value);
                if (def.empty()) continue;
                osd_model::BrushLayer layer;
                layer.markup = std::move(def);
                layer.enabled = Wh_GetIntSetting(
                    L"CustomOSD.Appearance.ddcBrushLayers[%d].enabled", i) != 0;
                layer.opacity = std::clamp(Wh_GetIntSetting(
                    L"CustomOSD.Appearance.ddcBrushLayers[%d].opacity", i), 0, 100);
                layers.push_back(std::move(layer));
            }
        }
        if (layered)
            Wh_Log(L"Fluent OSD/XAML: layered settings loaded=%u",
                   static_cast<unsigned>(layers.size()));
        // Publish the entire array as one snapshot for the OSD controller.
        settings.SetBrushLayers(layered, std::move(layers));
    }
    settings.cornerRadius.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcCornerRadius"), 0, 34));
    settings.fontSize.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcFontSize"), 10, 24));
    settings.iconSize.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcIconSize"), 10, 24));
    settings.showSun.store(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcShowSun") != 0);
    settings.showValue.store(Wh_GetIntSetting(L"CustomOSD.Appearance.ddcShowValue") != 0);
    PCWSTR outputMode = Wh_GetStringSetting(L"CustomOSD.Layout.displayOutputMode");
    const int displayMode = outputMode && _wcsicmp(outputMode, L"all") == 0 ? 3 :
        outputMode && _wcsicmp(outputMode, L"selected") == 0 ? 2 :
        outputMode && _wcsicmp(outputMode, L"primary") == 0 ? 1 : 0;
    settings.displayOutputMode.store(displayMode);
    Wh_FreeStringSetting(outputMode);
    settings.displayOutputNumber.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Layout.displayOutputNumber"), 1, 16));
    settings.position.store(ReadPositionSetting());
    settings.offsetX.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcOffsetX"), -500, 500));
    settings.offsetY.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcOffsetY"), -500, 500));
    // Commit scalars and brush layers with a single atomic publication.
    GetSettingsModuleState().Publish(std::move(staged));
}

// ============================================================
// Native shell hooks and event routing
// ============================================================
bool Hidden(Kind k) {
    const auto settings = GetSettingsState();
    return settings->hideAllNativeOsd.load(std::memory_order_relaxed) ||
           settings->hide[static_cast<int>(k)].load(std::memory_order_relaxed);
}

bool ShowCustomNative(Kind kind) {
    const auto settings = GetSettingsState();
    return settings->showCustomNative[static_cast<int>(kind)].load(
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
    if (!GetNativeEventState().mailbox.Offer(
            NativeEventInfo{kind, value, variant, std::move(text)})) return true;
    if (PostMessageW(receiver, kNativeExtraMessage, 0, 0)) return true;
    GetNativeEventState().mailbox.PostFailed();
    return false;
}

bool DdcAllowed() {
    return GetSettingsState()->showDdcBrightness.load(std::memory_order_relaxed) &&
        (GetCoreState().module.isExplorer ? GetSettingsState()->fromExplorer.load(std::memory_order_relaxed)
                      : GetSettingsState()->fromTwinkle.load(std::memory_order_relaxed));
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
    GetCoreState().module.confirmatorDll = LoadLibraryExW(
        L"Windows.Internal.HardwareConfirmator.dll", nullptr,
        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!GetCoreState().module.confirmatorDll) {
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
    if (!WindhawkUtils::HookSymbols(GetCoreState().module.confirmatorDll, hooks, ARRAYSIZE(hooks)))
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
using GetPhysical_t = BOOL(WINAPI*)(HMONITOR, DWORD, LPPHYSICAL_MONITOR);
GetPhysical_t GetPhysicalOriginal = nullptr;
BOOL WINAPI GetPhysicalHook(HMONITOR display, DWORD count,
                            LPPHYSICAL_MONITOR items) {
    BOOL ok = GetPhysicalOriginal(display, count, items);
    if (!ok || !items || !count || count > 32) return ok;
    MONITORINFOEXW mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(display, &mi)) return ok;
    GetBrightnessState().ddc.RememberHandles(mi.szDevice, count, items);
    return ok;
}

using DestroyPhysical_t = BOOL(WINAPI*)(HANDLE);
DestroyPhysical_t DestroyPhysicalOriginal = nullptr;
BOOL WINAPI DestroyPhysicalHook(HANDLE handle) {
    GetBrightnessState().ddc.ForgetHandle(handle);
    return DestroyPhysicalOriginal(handle);
}

using DestroyPhysicalArray_t = BOOL(WINAPI*)(DWORD, LPPHYSICAL_MONITOR);
DestroyPhysicalArray_t DestroyPhysicalArrayOriginal = nullptr;
BOOL WINAPI DestroyPhysicalArrayHook(DWORD count, LPPHYSICAL_MONITOR items) {
    GetBrightnessState().ddc.ForgetHandles(count, items);
    return DestroyPhysicalArrayOriginal(count, items);
}

using GetBrightness_t = BOOL(WINAPI*)(HANDLE, LPDWORD, LPDWORD, LPDWORD);
GetBrightness_t GetBrightnessOriginal = nullptr;
BOOL WINAPI GetBrightnessHook(HANDLE handle, LPDWORD low, LPDWORD current,
                              LPDWORD high) {
    BOOL ok = GetBrightnessOriginal(handle, low, current, high);
    if (ok && low && high)
        GetBrightnessState().ddc.UpdateHandleRange(handle, *low, *high);
    if (ok && current && !DdcRuntimeState::insideHighLevelSet)
        GetBrightnessState().ddc.ObserveRead(handle, *current);
    return ok;
}

using GetVcp_t = BOOL(WINAPI*)(HANDLE, BYTE, LPMC_VCP_CODE_TYPE,
                               LPDWORD, LPDWORD);
GetVcp_t GetVcpOriginal = nullptr;
BOOL WINAPI GetVcpHook(HANDLE handle, BYTE code, LPMC_VCP_CODE_TYPE type,
                       LPDWORD current, LPDWORD maximum) {
    BOOL ok = GetVcpOriginal(handle, code, type, current, maximum);
    if (ok && code == static_cast<BYTE>(GetSettingsState()->vcpCode.load())) {
        if (maximum)
            GetBrightnessState().ddc.UpdateHandleRange(handle, 0, *maximum);
        if (current && !DdcRuntimeState::insideHighLevelSet)
            GetBrightnessState().ddc.ObserveRead(handle, *current);
    }
    return ok;
}

void QueueBrightnessWheelTask(const BrightnessWheelTask& task) {
    GetBrightnessState().writer.EnqueueAndSignal(task);
}

void Publish(HANDLE handle, DWORD value) {
    if (!DdcAllowed()) return;
    PhysicalInfo info = GetBrightnessState().ddc.LookupHandle(handle);
    if (!info.device[0]) {
        if (!GetCoreState().module.loggedUnmapped.exchange(true))
            Wh_Log(L"DDC target monitor unknown: handle was not observed in "
                   L"GetPhysicalMonitorsFromHMONITOR. Fully quit/restart "
                   L"Twinkle Tray to rebuild its physical-monitor handle map.");
        // The Event target monitor mode must not silently move an unknown
        // target to DISPLAY1. Other output modes are location-independent.
        if (GetSettingsState()->displayOutputMode.load(std::memory_order_relaxed) == 0)
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
BOOL WINAPI SetBrightnessHook(HANDLE handle, DWORD value) {
    bool prior = DdcRuntimeState::insideHighLevelSet;
    DdcRuntimeState::insideHighLevelSet = true;
    BOOL ok = SetBrightnessOriginal(handle, value);
    DWORD lastError = GetLastError();
    DdcRuntimeState::insideHighLevelSet = prior;
    if (ok && !prior &&
        GetBrightnessState().ddc.RecordSuccessfulWrite(handle, value))
        Publish(handle, value);
    SetLastError(lastError);
    return ok;
}

using SetVcp_t = BOOL(WINAPI*)(HANDLE, BYTE, DWORD);
SetVcp_t SetVcpOriginal = nullptr;
BOOL WINAPI SetVcpHook(HANDLE handle, BYTE code, DWORD value) {
    BOOL ok = SetVcpOriginal(handle, code, value);
    DWORD lastError = GetLastError();
    if (ok && !DdcRuntimeState::insideHighLevelSet &&
        code == static_cast<BYTE>(GetSettingsState()->vcpCode.load()) &&
        GetBrightnessState().ddc.RecordSuccessfulWrite(handle, value))
        Publish(handle, value);
    SetLastError(lastError);
    return ok;
}

void HookDdc() {
    GetCoreState().module.ddcDll = LoadLibraryExW(L"dxva2.dll", nullptr,
                              LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!GetCoreState().module.ddcDll) {
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
        void* address = reinterpret_cast<void*>(GetProcAddress(GetCoreState().module.ddcDll, e.name));
        if (!address || !Wh_SetFunctionHook(address, e.detour, e.original))
            Wh_Log(L"DDC Hook failed: %hs", e.name);
    }
}

// ============================================================
// Windows accent/theme helpers
// ============================================================
void InitWindowsAccentProvider() {
    GetCoreState().presentation.combase = LoadLibraryExW(L"combase.dll", nullptr,
                               LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!GetCoreState().presentation.combase) return;
    auto roInit = reinterpret_cast<RoInitialize_t>(
        GetProcAddress(GetCoreState().presentation.combase, "RoInitialize"));
    auto activate = reinterpret_cast<RoActivateInstance_t>(
        GetProcAddress(GetCoreState().presentation.combase, "RoActivateInstance"));
    auto createString = reinterpret_cast<WindowsCreateString_t>(
        GetProcAddress(GetCoreState().presentation.combase, "WindowsCreateString"));
    auto deleteString = reinterpret_cast<WindowsDeleteString_t>(
        GetProcAddress(GetCoreState().presentation.combase, "WindowsDeleteString"));
    GetCoreState().presentation.roUninitialize = reinterpret_cast<RoUninitialize_t>(
        GetProcAddress(GetCoreState().presentation.combase, "RoUninitialize"));
    if (!roInit || !activate || !createString || !deleteString ||
        !GetCoreState().presentation.roUninitialize) return;

    // Dedicated UI thread: initialize WinRT on this same thread.
    HRESULT hr = roInit(1); // RO_INIT_MULTITHREADED
    if (FAILED(hr)) return;
    GetCoreState().presentation.roInitialized = true;
    void* classId = nullptr;
    if (FAILED(createString(kUiSettingsRuntimeClass, ARRAYSIZE(kUiSettingsRuntimeClass) - 1, &classId)))
        return;
    IUnknown* object = nullptr;
    hr = activate(classId, &object);
    deleteString(classId);
    if (SUCCEEDED(hr) && object) {
        hr = object->QueryInterface(kIUiSettings3,
                                    reinterpret_cast<void**>(&GetCoreState().presentation.uiSettings));
        object->Release();
    }
    if (FAILED(hr))
        Wh_Log(L"UISettings unavailable (HRESULT=0x%08lX); using accent fallbacks",
               static_cast<unsigned long>(hr));
}

void ReleaseWindowsAccentProvider() {
    if (GetCoreState().presentation.uiSettings) {
        GetCoreState().presentation.uiSettings->Release();
        GetCoreState().presentation.uiSettings = nullptr;
    }
    if (GetCoreState().presentation.roInitialized && GetCoreState().presentation.roUninitialize)
        GetCoreState().presentation.roUninitialize();
    GetCoreState().presentation.roInitialized = false;
    GetCoreState().presentation.roUninitialize = nullptr;
    if (GetCoreState().presentation.combase) FreeLibrary(GetCoreState().presentation.combase);
    GetCoreState().presentation.combase = nullptr;
}

DWORD SystemAccentRgb() {
    // Reading UISettings for each actual render supports changes to the
    // Windows accent without a timer, additional thread, or injected hook.
    if (GetCoreState().presentation.uiSettings) {
        UiColor c{};
        if (SUCCEEDED(GetCoreState().presentation.uiSettings->GetColorValue(5, &c))) // UIColorType.Accent
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

bool IsLightTheme(const OsdSettingsState& settings) {
    const int setting = settings.ddcTheme.load(std::memory_order_relaxed);
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
DWORD OsdBackgroundRgb(bool light, const OsdSettingsState& settings) {
    return ConfiguredOsdRgb(settings.backgroundMode, settings.validCustomBackground,
                            settings.customBackground, light ? 0xFAFAFC : 0x26262A);
}
DWORD OsdTextRgb(bool light, const OsdSettingsState& settings) {
    return ConfiguredOsdRgb(settings.textMode, settings.validCustomText,
                            settings.customText, light ? 0x1C1C20 : 0xFAFAFB);
}
DWORD OsdTrackRgb(bool light, bool mixer, const OsdSettingsState& settings) {
    return ConfiguredOsdRgb(settings.trackMode, settings.validCustomTrack,
                            settings.customTrack, mixer
                                ? (light ? 0xE0E1E7 : 0x5E5E65)
                                : (light ? 0xDEDFE3 : 0x595A60));
}
DWORD OsdAccentRgb(const OsdSettingsState& settings) {
    return settings.accentMode.load() && settings.validCustomAccent.load()
        ? settings.customAccent.load() : SystemAccentRgb();
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

// Core Audio operation: the XAML controller owns rendering and timeouts.
bool AdjustDefaultAudioWheel(int steps) {
    if (!steps || GetCoreState().presentation.popupKind != PopupKind::NativeVolume) return false;
    Microsoft::WRL::ComPtr<IAudioEndpointVolume> volume;
    if (!OpenDefaultAudioEndpointVolume(volume)) return false;
    float scalar = 0.0f;
    if (FAILED(volume->GetMasterVolumeLevelScalar(&scalar))) return false;
    const float requested = std::clamp(
        scalar + steps * (kWheelStepPercent / 100.0f), 0.0f, 1.0f);
    if (FAILED(volume->SetMasterVolumeLevelScalar(requested, nullptr)))
        return false;
    if (FAILED(volume->GetMasterVolumeLevelScalar(&scalar)))
        scalar = requested;
    BOOL muted = FALSE;
    (void)volume->GetMute(&muted);
    GetCoreState().presentation.nativePercent = static_cast<int>(std::lround(
        std::clamp(scalar, 0.0f, 1.0f) * 100.0f));
    GetCoreState().presentation.nativePercentKnown = true;
    GetCoreState().presentation.nativeMuted = muted != FALSE;
    return true;
}

// Absolute set for click/drag of the main volume track. Do not unmute: mute
// is a separate user state, and moving the track should not silently clear it.
bool SetDefaultAudioBarPercent(int percent) {
    percent = std::clamp(percent, 0, 100);
    if (GetCoreState().presentation.popupKind != PopupKind::NativeVolume || !GetCoreState().presentation.nativePercentKnown)
        return false;
    if (percent == GetCoreState().presentation.nativePercent) return true;
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
    GetCoreState().presentation.nativePercent = static_cast<int>(std::lround(
        std::clamp(actual, 0.0f, 1.0f) * 100.0f));
    GetCoreState().presentation.nativeMuted = muted != FALSE;
    return true;
}

// Toggle the default endpoint's mute without changing its stored volume.
bool ToggleDefaultAudioMute() {
    if (GetCoreState().presentation.popupKind != PopupKind::NativeVolume || GetCoreState().module.closing.load())
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
        GetCoreState().presentation.nativePercent = static_cast<int>(std::lround(
            std::clamp(scalar, 0.0f, 1.0f) * 100.0f));
        GetCoreState().presentation.nativePercentKnown = true;
    }
    GetCoreState().presentation.nativeMuted = actual != FALSE;
    if (GetAudioState().panel.mixerOpen) GetAudioState().mixer.masterMuted = GetCoreState().presentation.nativeMuted;
    return true;
}

// Clipboard image acquisition uses an ephemeral Win32 HBITMAP. Only
// bounded pixel bytes cross to the XAML STA renderer.
void ClearClipboardThumbnail() {
    if (GetNoticeState().notice.clipboardThumbnail) {
        DeleteObject(GetNoticeState().notice.clipboardThumbnail);
        GetNoticeState().notice.clipboardThumbnail = nullptr;
    }
}

// All text/status notifications share exactly the same canvas and card/tile
// geometry. A separate, image-first clipboard layout intentionally uses its
// own canvas so image previews can preserve their aspect ratio.
void AddNoticeEvent(NoticeCategory category, NoticeAction action,
                    std::wstring identity, std::wstring label,
                    NoticeIcon deviceIcon = NoticeIcon::Bluetooth) {
    if (!GetCoreState().module.receiveWnd || GetCoreState().module.closing.load()) return;
    if (identity.empty()) identity = label;
    if (label.empty()) label = std::wstring(NoticeCategoryLabel(category)) +
        L" " + Tr(OsdText::Device);
    if (GetNoticeState().notice.batch.pending &&
        (GetNoticeState().notice.batch.category != category || GetNoticeState().notice.batch.action != action))
        FlushNoticeBatch();
    if (!GetNoticeState().notice.batch.pending) {
        GetNoticeState().notice.ResetBatch();
        GetNoticeState().notice.batch.pending = true;
        GetNoticeState().notice.batch.category = std::move(category);
        GetNoticeState().notice.batch.action = std::move(action);
    }
    if (label.size() > 120) label.resize(120);
    if (identity.size() > 2048) identity.resize(2048);
    if (GetNoticeState().notice.batch.identities.insert(identity).second &&
        GetNoticeState().notice.batch.names.size() < 64) {
        if (category == NoticeCategory::Bluetooth ||
            category == NoticeCategory::Network) {
            if (!GetNoticeState().notice.batch.iconKnown) {
                GetNoticeState().notice.batch.icon = deviceIcon;
                GetNoticeState().notice.batch.iconKnown = true;
            } else if (GetNoticeState().notice.batch.icon != deviceIcon) {
                GetNoticeState().notice.batch.mixedIcons = true;
            }
        }
        GetNoticeState().notice.batch.names.push_back(std::move(label));
    }
    // 320 ms debounce; repeated device-interface announcements coalesce.
    SetTimer(GetCoreState().module.receiveWnd, kEventBatchTimer, 320, nullptr);
}

void FlushNoticeBatch() {
    if (GetCoreState().module.receiveWnd) KillTimer(GetCoreState().module.receiveWnd, kEventBatchTimer);
    if (!GetNoticeState().notice.batch.pending) return;
    NoticeBatch batch = std::move(GetNoticeState().notice.batch);
    GetNoticeState().notice.ResetBatch();
    if (batch.names.empty()) return;
    GetNoticeState().notice.details = batch.names;
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
        ? (batch.mixedIcons ? NoticeIcon::Bluetooth : batch.icon)
        : batch.category == NoticeCategory::Network
        ? (batch.mixedIcons ? NoticeIcon::Network : batch.icon)
        : NoticeIcon::Usb;
    // Diagnostics identify origin without logging device names or WLAN profiles.
    Wh_Log(L"Fluent OSD/notice: category=%d action=%d icon=%d items=%lu",
           static_cast<int>(batch.category), static_cast<int>(batch.action),
           static_cast<int>(icon), static_cast<unsigned long>(batch.names.size()));
    ShowNotice(std::move(title), std::move(body),
        batch.category == NoticeCategory::Network ? DurationKind::Network : DurationKind::Devices,
        icon);
}

void ShowNotice(std::wstring title, std::wstring body, DurationKind kind,
                NoticeIcon icon) {
    if (GetCoreState().module.closing.load() || !GetCoreState().module.receiveWnd) return;
    if (kind != DurationKind::Clipboard) ClearClipboardThumbnail();
    GetCoreState().presentation.popupKind = PopupKind::Notification;
    GetNoticeState().notice.panelOpen = false;
    ++GetNoticeState().notice.generation;
    GetNoticeState().notice.duration = kind;
    GetNoticeState().notice.title = std::move(title);
    GetNoticeState().notice.body = std::move(body);
    GetNoticeState().notice.icon = icon;
    BrightnessEvent event{};
    MovePopupToDisplay(event);
    if (kind == DurationKind::Clipboard)
        ShowMigratedXamlClipboardNotice();
    else
        ShowMigratedXamlDeviceNotice(kind);
}

// ============================================================
// ============================================================
// Clipboard event processing
// ============================================================
void ProcessClipboard() {
    if (!GetSettingsState()->showClipboardOsd.load()) return;
    if (!OpenClipboard(GetCoreState().module.receiveWnd)) return;
    std::wstring title = Tr(OsdText::Clipboard), body = Tr(OsdText::ContentCopied);
    HBITMAP newThumbnail = nullptr;
    NoticeIcon icon = NoticeIcon::Clipboard;
    // Explorer file selections may also advertise a text or image format.
    // Prefer the semantic CF_HDROP file selection over its representations.
    if (IsClipboardFormatAvailable(CF_HDROP)) {
        title = Tr(OsdText::FilesCopied);
        body = Tr(OsdText::ClipboardFiles);
        icon = NoticeIcon::ClipboardFile;
    } else if (IsClipboardFormatAvailable(CF_BITMAP) ||
               IsClipboardFormatAvailable(CF_DIB) ||
               IsClipboardFormatAvailable(CF_DIBV5)) {
        title = Tr(OsdText::ImageCopied);
        body = Tr(OsdText::ClipboardImage);
        if (GetSettingsState()->clipboardImagePreview.load()) {
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
        icon = NoticeIcon::ClipboardText;
        if (GetSettingsState()->clipboardTextPreview.load()) {
            HANDLE handle = GetClipboardData(CF_UNICODETEXT);
            SIZE_T cb = handle ? GlobalSize(handle) : 0;
            if (handle && cb >= sizeof(wchar_t)) {
                const wchar_t* text = static_cast<const wchar_t*>(GlobalLock(handle));
                if (text) {
                    const size_t bound = std::min<size_t>(cb / sizeof(wchar_t),
                            static_cast<size_t>(GetSettingsState()->clipboardChars.load()) + 1);
                    body.clear();
                    for (size_t i = 0; i < bound && text[i]; ++i) {
                        const wchar_t ch = text[i];
                        body.push_back(ch < 0x20 || ch == 0x7f ? L' ' : ch);
                    }
                    if (cb / sizeof(wchar_t) > body.size() &&
                        body.size() >= static_cast<size_t>(GetSettingsState()->clipboardChars.load()))
                        body += L"…";
                    GlobalUnlock(handle);
                }
            }
            if (body.empty()) body = Tr(OsdText::EmptyText);
        }
    }
    CloseClipboard();
    ClearClipboardThumbnail();
    GetNoticeState().notice.details.clear();
    GetNoticeState().notice.clipboardThumbnail = newThumbnail;
    ShowNotice(std::move(title), std::move(body), DurationKind::Clipboard,
               icon);
}

// ============================================================
// USB, network and Bluetooth device event handlers
// ============================================================
// Event-based USB interface notifications and OS connectivity hints.
// Bluetooth uses typed Windows DeviceWatcher projections below.

// Keep the modern network hint API dynamically resolved for older SDKs.
// Hint callbacks report only aggregate connectivity, not individual NIC
// state. IP-interface and address callbacks supply per-adapter triggers.
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

bool NetworkRuntimeState::CancelCallbacksOnControllerThread() {
    if (!notification && !ipNotification && !addressNotification)
        return true;
    const auto cancel = dll ? reinterpret_cast<CancelNetworkHint>(
        GetProcAddress(dll, "CancelMibChangeNotify2")) : nullptr;
    if (!cancel) {
        Wh_Log(L"Fluent OSD/network: cancellation API unavailable");
        return false;
    }
    bool complete = true;
    const auto revoke = [&](HANDLE& handle, PCWSTR label) {
        if (!handle) return;
        const DWORD result = cancel(handle);
        if (result == NO_ERROR) {
            handle = nullptr;
        } else {
            complete = false;
            Wh_Log(L"Fluent OSD/network: cancel %s returned %lu", label, result);
        }
    };
    revoke(addressNotification, L"address");
    revoke(ipNotification, L"interface");
    revoke(notification, L"connectivity");
    return complete;
}

// Native Wi-Fi callbacks expose association changes even when the physical
// adapter stays enabled and GetAdaptersAddresses reports the same OperStatus.
// The old Windhawk MinGW SDK lacks newer WLAN declarations, so use a strict,
// read-only ABI prefix with dynamic exports from System32 wlanapi.dll.
struct WlanNotificationCompat {
    DWORD source, code;
    GUID interfaceGuid;
    DWORD dataSize;
    void* data;
};
using WlanNotificationCallback = void (WINAPI*)(WlanNotificationCompat*, void*);
using WlanRegisterNotify = DWORD (WINAPI*)(
    HANDLE, DWORD, BOOL, WlanNotificationCallback, void*, void*, DWORD*);
using WlanClose = DWORD (WINAPI*)(HANDLE, void*);
constexpr DWORD kWlanAcmSource = 0x00000008;
constexpr DWORD kWlanMsmSource = 0x00000010;
constexpr DWORD kWlanRadioStateChanged = 7; // wlan_notification_msm_radio_state_change

struct WlanLiveState {
    bool connected = false;
    std::wstring profile;
    bool radioKnown = false;
    bool radioOn = false;
};
// WLAN subscriptions are separate from aggregate/IP-interface notifications.
struct WlanRuntimeState {
    HMODULE dll = nullptr;
    HANDLE client = nullptr;
    bool notifyRegistered = false; // OSD receiver thread only.
    std::unordered_map<ULONGLONG, WlanLiveState> live;
    std::unordered_set<ULONGLONG> physicalLuids;
    bool inventoryValid = false;

    // A disabled WLAN may disappear from enumeration. Keep known physical
    // LUIDs across refreshes so virtual SoftAP children remain suppressed.
    void RememberPhysicalLuid(ULONGLONG luid) {
        if (physicalLuids.size() < 64) physicalLuids.insert(luid);
    }
    bool HasPhysicalLuids() const { return !physicalLuids.empty(); }
    bool IsPhysicalLuid(ULONGLONG luid) const {
        return physicalLuids.count(luid) != 0;
    }
    void StopClientOnControllerThread() {
        if (client && dll) {
            const auto registerNotify = reinterpret_cast<WlanRegisterNotify>(
                GetProcAddress(dll, "WlanRegisterNotification"));
            // Revoke callbacks synchronously before closing the WLAN handle.
            if (notifyRegistered && registerNotify)
                (void)registerNotify(client, 0, FALSE, nullptr,
                                     nullptr, nullptr, nullptr);
            const auto closeWlan = reinterpret_cast<WlanClose>(
                GetProcAddress(dll, "WlanCloseHandle"));
            if (closeWlan) (void)closeWlan(client, nullptr);
        }
        client = nullptr;
        notifyRegistered = false;
        if (dll) FreeLibrary(dll);
        dll = nullptr;
        live.clear();
        physicalLuids.clear();
        inventoryValid = false;
    }
    void ReleaseAfterControllerStops() {
        std::unordered_map<ULONGLONG, WlanLiveState> oldLive;
        std::unordered_set<ULONGLONG> oldPhysicalLuids;
        live.swap(oldLive);
        physicalLuids.swap(oldPhysicalLuids);
    }
};
// IP and WLAN state are bound to one controller-owned connectivity module.
struct ConnectivityModuleState final {
    NetworkRuntimeState network;
    WlanRuntimeState wlan;
    void ReleaseAfterControllerStops() {
        // Subscriptions and WLAN handles were released by the receiver owner.
        // This only frees retained baseline container capacities.
        network.ReleaseAfterControllerStops();
        wlan.ReleaseAfterControllerStops();
    }
};
ConnectivityModuleState& GetConnectivityState() {
    [[clang::no_destroy]] static ConnectivityModuleState instance;
    return instance;
}

void QueueNetworkRefreshEvent(WPARAM source, LPARAM hintLevel);
void WINAPI WlanChanged(WlanNotificationCompat* notice, void*) {
    if (!notice) return;
    const DWORD code = notice->code;
    // ACM reports WLAN profile and interface events. MSM radio notifications
    // are a separate source; no SSID association is implied by a radio toggle.
    if ((notice->source == kWlanAcmSource &&
         (code == 9 || code == 10 || code == 13 || code == 14 ||
          code == 20 || code == 21)) ||
        (notice->source == kWlanMsmSource &&
         code == kWlanRadioStateChanged))
        QueueNetworkRefreshEvent(3, 0);
}

// Both IP Helper notification callbacks share the same ABI:
// PVOID context, pointer to a short-lived MIB row, 32-bit notification type.
// We do not inspect or retain the row from the callback thread.
using NetworkMibCallback = void (WINAPI*)(void*, void*, int);
using RegisterNetworkMib = DWORD (WINAPI*)(
    ADDRESS_FAMILY, NetworkMibCallback, void*, BOOLEAN, HANDLE*);

void QueueNetworkRefreshEvent(WPARAM source, LPARAM hintLevel) {
    if (!GetSettingsState()->showNetworkEvents.load()) return;
    const HWND receiver = GetCoreState().module.ReceiverForCallbacks();
    if (receiver) (void)PostMessageW(
        receiver, kNetworkNoticeMessage, source, hintLevel);
}

void WINAPI NetworkChanged(void*, NetworkHintAbi hint) {
    const int prior = GetConnectivityState().network.previousLevel.exchange(hint.connectivityLevel);
    if (prior < 0 || prior == hint.connectivityLevel) return;
    QueueNetworkRefreshEvent(1, static_cast<LPARAM>(hint.connectivityLevel));
}

void WINAPI NetworkMibChanged(void*, void*, int) {
    // No GetAdaptersAddresses or XAML work on Windows' callback thread.
    QueueNetworkRefreshEvent(2, 0);
}

void CaptureNetworkBaseline() {
    bool succeeded = false;
    auto current = GetNetworkSnapshot(&succeeded);
    if (!succeeded) {
        Wh_Log(L"Fluent OSD/network: adapter baseline unavailable");
        return;
    }
    GetConnectivityState().network.interfaces.clear();
    for (auto& item : current)
        GetConnectivityState().network.interfaces.emplace(std::move(item.first),
                                    std::move(item.second));
}

void RefreshNetworkHintBaseline() {
    if (!GetConnectivityState().network.dll) return;
    const auto hint = reinterpret_cast<GetNetworkHint>(
        GetProcAddress(GetConnectivityState().network.dll, "GetNetworkConnectivityHint"));
    NetworkHintAbi state{};
    if (hint && hint(&state) == NO_ERROR)
        GetConnectivityState().network.previousLevel.store(state.connectivityLevel);
}

void InitNetworkEvents() {
    const bool enabled = GetSettingsState()->showNetworkEvents.load();
    GetConnectivityState().network.uiSettingEnabled = enabled;
    if (!enabled) return; // No network subscriptions unless explicitly enabled.
    CaptureNetworkBaseline();
    if (!GetConnectivityState().network.dll)
        GetConnectivityState().network.dll = LoadLibraryExW(
            L"iphlpapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!GetConnectivityState().network.dll) {
        Wh_Log(L"Fluent OSD/network: iphlpapi unavailable (%lu)",
               GetLastError());
        return;
    }

    RefreshNetworkHintBaseline();
    const auto subscribeHint = reinterpret_cast<RegisterNetworkHint>(
        GetProcAddress(GetConnectivityState().network.dll, "NotifyNetworkConnectivityHintChange"));
    if (subscribeHint && !GetConnectivityState().network.notification) {
        const DWORD err = subscribeHint(NetworkChanged, nullptr, FALSE,
                                       &GetConnectivityState().network.notification);
        if (err != NO_ERROR) {
            GetConnectivityState().network.notification = nullptr;
            Wh_Log(L"Fluent OSD/network: hint registration failed (%lu)", err);
        }
    }

    // Unlike aggregate hints, these events occur even when another adapter
    // still provides Internet access. Both are needed for interface and IP
    // transitions on Wi-Fi, Ethernet, and virtual adapters.
    const auto subscribeInterface = reinterpret_cast<RegisterNetworkMib>(
        GetProcAddress(GetConnectivityState().network.dll, "NotifyIpInterfaceChange"));
    if (subscribeInterface && !GetConnectivityState().network.ipNotification) {
        const DWORD err = subscribeInterface(AF_UNSPEC, NetworkMibChanged,
            nullptr, FALSE, &GetConnectivityState().network.ipNotification);
        if (err != NO_ERROR) {
            GetConnectivityState().network.ipNotification = nullptr;
            Wh_Log(L"Fluent OSD/network: interface registration failed (%lu)", err);
        }
    } else if (!subscribeInterface) {
        Wh_Log(L"Fluent OSD/network: interface notification API unavailable");
    }

    const auto subscribeAddress = reinterpret_cast<RegisterNetworkMib>(
        GetProcAddress(GetConnectivityState().network.dll, "NotifyUnicastIpAddressChange"));
    if (subscribeAddress && !GetConnectivityState().network.addressNotification) {
        const DWORD err = subscribeAddress(AF_UNSPEC, NetworkMibChanged,
            nullptr, FALSE, &GetConnectivityState().network.addressNotification);
        if (err != NO_ERROR) {
            GetConnectivityState().network.addressNotification = nullptr;
            Wh_Log(L"Fluent OSD/network: address registration failed (%lu)", err);
        }
    } else if (!subscribeAddress) {
        Wh_Log(L"Fluent OSD/network: address notification API unavailable");
    }
    Wh_Log(L"Fluent OSD/network: subscriptions hint=%d interface=%d address=%d",
           GetConnectivityState().network.notification != nullptr,
           GetConnectivityState().network.ipNotification != nullptr,
           GetConnectivityState().network.addressNotification != nullptr);
}

void InitDeviceEvents() {
    DEV_BROADCAST_DEVICEINTERFACE_W usb{};
    usb.dbcc_size = sizeof(usb);
    usb.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    usb.dbcc_classguid = kUsbDeviceInterface;
    GetCoreState().module.usbNotification = RegisterDeviceNotificationW(
        GetCoreState().module.receiveWnd, &usb, DEVICE_NOTIFY_WINDOW_HANDLE);
    bt_monitor::Start(); // No-op unless opt-in is enabled.
}

void StopDeviceEvents() {
    // Revoke WinRT callbacks before destroying the UI receiver or COM MTA.
    bt_monitor::Stop();
    if (GetCoreState().module.usbNotification) UnregisterDeviceNotification(GetCoreState().module.usbNotification);
    GetCoreState().module.usbNotification = nullptr;
    if (!GetConnectivityState().network.CancelCallbacksOnControllerThread())
        Wh_Log(L"Fluent OSD/network: one or more subscriptions survived stop");
    GetConnectivityState().wlan.StopClientOnControllerThread();
    GetConnectivityState().network.ReleaseLibraryOnControllerThread();
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

// Dynamic Native Wi-Fi enumeration works with Windhawk's older MinGW SDK:
// it does not require a MIB_IF_ROW2 declaration or wlanapi.h. WLAN interface
// GUIDs are mapped to the same LUIDs returned by GetAdaptersAddresses.
// Keep known LUIDs across WLAN radio disable (WlanEnumInterfaces may then
// omit the interface); no polling, GATT scanning or name matching is used.
struct WlanInterfaceInfoCompat {
    GUID guid;
    WCHAR description[256];
    DWORD state;
};
struct WlanInterfaceListCompat {
    DWORD count, index;
    WlanInterfaceInfoCompat interfaces[1];
};
static_assert(sizeof(WlanInterfaceInfoCompat) == 532);
static_assert(offsetof(WlanInterfaceListCompat, interfaces) == 8);
// Only the beginning of WLAN_CONNECTION_ATTRIBUTES is needed to read the
// current connection's exact configured profile name. It is not an SSID guess.
struct WlanConnectionPrefix {
    DWORD state;
    DWORD mode;
    WCHAR profile[256];
};
static_assert(sizeof(WlanConnectionPrefix) == 520);

// Minimal Windows Native Wi-Fi radio-state ABI for Windhawk's older SDK.
// A PHY is usable only if both its software and hardware switches are on.
// Unknown query results never become a fabricated toggle notification.
struct WlanPhyRadioCompat {
    DWORD phyIndex;
    DWORD softwareState;
    DWORD hardwareState;
};
struct WlanRadioCompat {
    DWORD phyCount;
    WlanPhyRadioCompat phys[1];
};
static_assert(sizeof(WlanPhyRadioCompat) == 12);
static_assert(offsetof(WlanRadioCompat, phys) == sizeof(DWORD));

bool EnsureWlanClient() {
    if (!GetConnectivityState().wlan.dll) {
        GetConnectivityState().wlan.dll = LoadLibraryExW(
            L"wlanapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!GetConnectivityState().wlan.dll) return false;
    }
    if (!GetConnectivityState().wlan.client) {
        using Open = DWORD (WINAPI*)(DWORD, PVOID, PDWORD, PHANDLE);
        const auto open = reinterpret_cast<Open>(
            GetProcAddress(GetConnectivityState().wlan.dll, "WlanOpenHandle"));
        DWORD negotiated = 0;
        if (!open || open(2, nullptr, &negotiated, &GetConnectivityState().wlan.client) !=
                ERROR_SUCCESS || !GetConnectivityState().wlan.client)
            return false; // WLAN AutoConfig unavailable; retry next refresh.
    }
    if (!GetConnectivityState().wlan.notifyRegistered) {
        const auto subscribe = reinterpret_cast<WlanRegisterNotify>(
            GetProcAddress(GetConnectivityState().wlan.dll, "WlanRegisterNotification"));
        if (subscribe && subscribe(GetConnectivityState().wlan.client,
                kWlanAcmSource | kWlanMsmSource, FALSE,
                WlanChanged, nullptr, nullptr, nullptr) == ERROR_SUCCESS)
            GetConnectivityState().wlan.notifyRegistered = true;
    }
    return true;
}

void RefreshPhysicalWlanLuids() {
    GetConnectivityState().wlan.inventoryValid = false;
    if (!GetConnectivityState().network.dll || !EnsureWlanClient()) return;
    using Enumerate = DWORD (WINAPI*)(
        HANDLE, PVOID, WlanInterfaceListCompat**);
    using Query = DWORD (WINAPI*)(
        HANDLE, const GUID*, DWORD, void*, DWORD*, void**, DWORD*);
    using Free = void (WINAPI*)(void*);
    using GuidToLuid = DWORD (WINAPI*)(const GUID*, void*);
    const auto convert = reinterpret_cast<GuidToLuid>(
        GetProcAddress(GetConnectivityState().network.dll, "ConvertInterfaceGuidToLuid"));
    const auto enumerate = reinterpret_cast<Enumerate>(
        GetProcAddress(GetConnectivityState().wlan.dll, "WlanEnumInterfaces"));
    const auto query = reinterpret_cast<Query>(
        GetProcAddress(GetConnectivityState().wlan.dll, "WlanQueryInterface"));
    const auto freeMemory = reinterpret_cast<Free>(
        GetProcAddress(GetConnectivityState().wlan.dll, "WlanFreeMemory"));
    if (!convert || !enumerate || !freeMemory) return;
    WlanInterfaceListCompat* list = nullptr;
    if (enumerate(GetConnectivityState().wlan.client, nullptr, &list) != ERROR_SUCCESS ||
        !list) {
        if (list) freeMemory(list);
        return;
    }
    GetConnectivityState().wlan.inventoryValid = true;
    std::unordered_map<ULONGLONG, WlanLiveState> live;
    for (DWORD i = 0; i < std::min<DWORD>(list->count, 64); ++i) {
        ULONGLONG luid = 0;
        if (convert(&list->interfaces[i].guid, &luid) != NO_ERROR ||
            !luid) continue;
        GetConnectivityState().wlan.RememberPhysicalLuid(luid);
        WlanLiveState entry;
        // The Native Wi-Fi interface state reflects 802.11 association,
        // independently of NDIS OperStatus and IPv4/IPv6 addressing.
        entry.connected = list->interfaces[i].state == 1;
        if (query) {
            DWORD dataSize = 0, opcodeType = 0;
            void* data = nullptr;
            // wlan_intf_opcode_radio_state == 4; not a profile query.
            if (query(GetConnectivityState().wlan.client, &list->interfaces[i].guid, 4, nullptr,
                    &dataSize, &data, &opcodeType) == ERROR_SUCCESS &&
                data && dataSize >= offsetof(WlanRadioCompat, phys)) {
                const auto* radio = reinterpret_cast<const WlanRadioCompat*>(data);
                const DWORD count = radio->phyCount;
                if (count && count <= 64 &&
                    dataSize >= offsetof(WlanRadioCompat, phys) +
                                count * sizeof(WlanPhyRadioCompat)) {
                    bool anyOn = false, allOff = true;
                    for (DWORD phy = 0; phy < count; ++phy) {
                        const auto& state = radio->phys[phy];
                        if (state.softwareState == 1 && state.hardwareState == 1)
                            anyOn = true;
                        if (state.softwareState != 2 && state.hardwareState != 2)
                            allOff = false;
                    }
                    if (anyOn || allOff) {
                        entry.radioKnown = true;
                        entry.radioOn = anyOn;
                    }
                }
            }
            if (data) freeMemory(data);
        }
        // A genuinely associated WLAN must have at least one powered PHY;
        // use this as a conservative fallback if radio-state query fails.
        if (entry.connected && !entry.radioKnown) {
            entry.radioKnown = true;
            entry.radioOn = true;
        }
        if (entry.connected && query) {
            DWORD dataSize = 0, opcodeType = 0;
            void* data = nullptr;
            // wlan_intf_opcode_current_connection == 7.
            if (query(GetConnectivityState().wlan.client, &list->interfaces[i].guid, 7, nullptr,
                    &dataSize, &data, &opcodeType) == ERROR_SUCCESS &&
                data && dataSize >= sizeof(WlanConnectionPrefix)) {
                const auto* info =
                    reinterpret_cast<const WlanConnectionPrefix*>(data);
                if (info->state == 1) {
                    size_t count = 0;
                    while (count < 256 && info->profile[count]) ++count;
                    entry.profile.assign(info->profile, count);
                    if (entry.profile.size() > 120)
                        entry.profile.resize(120);
                }
            }
            if (data) freeMemory(data);
        }
        live.emplace(luid, std::move(entry));
    }
    freeMemory(list);
    GetConnectivityState().wlan.live = std::move(live);
}

// Bluetooth PAN is an IP/Ethernet-like adapter (often IfType 6), not an
// 802.11 profile. Match its PnP service BthPan to the exact NetCfgInstanceId;
// neither the friendly name nor the interface type can identify it reliably.
// Enumerate installed network devices on the controller thread only.
std::vector<GUID> GetBluetoothPanAdapterGuids() {
    // GUID_DEVCLASS_NET; literal avoids adding a newer SDK header dependency.
    const GUID networkClass = {0x4d36e972, 0xe325, 0x11ce,
                               {0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18}};
    std::vector<GUID> panGuids;
    HDEVINFO devices = SetupDiGetClassDevsW(&networkClass, nullptr, nullptr, 0);
    if (devices == INVALID_HANDLE_VALUE) return panGuids;
    for (DWORD i = 0; i < 256; ++i) {
        SP_DEVINFO_DATA info{};
        info.cbSize = sizeof(info);
        if (!SetupDiEnumDeviceInfo(devices, i, &info)) break;
        WCHAR service[96]{};
        DWORD type = 0, required = 0;
        if (!SetupDiGetDeviceRegistryPropertyW(
                devices, &info, SPDRP_SERVICE, &type,
                reinterpret_cast<PBYTE>(service), sizeof(service), &required) ||
            type != REG_SZ || _wcsicmp(service, L"BthPan") != 0)
            continue;
        HKEY key = SetupDiOpenDevRegKey(
            devices, &info, DICS_FLAG_GLOBAL, 0, DIREG_DRV, KEY_QUERY_VALUE);
        if (key == INVALID_HANDLE_VALUE) continue;
        WCHAR instanceId[64]{};
        DWORD bytes = sizeof(instanceId);
        const LONG result = RegGetValueW(
            key, nullptr, L"NetCfgInstanceId", RRF_RT_REG_SZ, nullptr,
            instanceId, &bytes);
        RegCloseKey(key);
        if (result != ERROR_SUCCESS || !instanceId[0]) continue;
        // CLSIDFromString requires a brace-enclosed GUID, not a ProgID.
        std::wstring guidText(instanceId);
        if (guidText.size() == 36)
            guidText = L"{" + guidText + L"}";
        GUID guid{};
        if (guidText.size() == 38 && guidText.front() == L'{' &&
            guidText.back() == L'}' &&
            SUCCEEDED(CLSIDFromString(guidText.c_str(), &guid)))
            panGuids.push_back(guid);
    }
    SetupDiDestroyDeviceInfoList(devices);
    return panGuids;
}

// Capture interface transitions on network-hint events. A connectivity hint
// alone does not expose an SSID or a VPN connection's authenticated status.
std::vector<std::pair<std::string, NetInterfaceState>> GetNetworkSnapshot(
        bool* succeeded) {
    if (succeeded) *succeeded = false;
    std::vector<std::pair<std::string, NetInterfaceState>> out;
    ULONG size = 16 * 1024;
    std::vector<BYTE> buffer(size);
    // Include adapters with no assigned IPv4/IPv6 address (often disabled).
    constexpr ULONG flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
        GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_INCLUDE_ALL_INTERFACES;
    ULONG err = GetAdaptersAddresses(AF_UNSPEC, flags, nullptr,
        reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &size);
    if (err == ERROR_BUFFER_OVERFLOW && size <= 256 * 1024) {
        buffer.resize(size);
        err = GetAdaptersAddresses(AF_UNSPEC, flags, nullptr,
            reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &size);
    }
    // No adapters is a valid disconnected state, not an API failure.
    if (err == ERROR_NO_DATA) {
        if (succeeded) *succeeded = true;
        return out;
    }
    if (err != NO_ERROR) {
        Wh_Log(L"Fluent OSD/network: GetAdaptersAddresses failed (%lu)", err);
        return out;
    }
    if (succeeded) *succeeded = true;
    RefreshPhysicalWlanLuids();
    const auto bluetoothPanGuids = GetBluetoothPanAdapterGuids();
    const auto* adapter = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());
    for (int count = 0; adapter && count < 128;
         adapter = adapter->Next, ++count) {
        if (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK ||
            adapter->IfType == 248 /* IF_TYPE_BLUETOOTH */)
            continue;
        // Bluetooth PAN may instead report as Ethernet (IfType 6).
        // Match PnP NetCfgInstanceId, not a localized adapter/phone name.
        if (adapter->AdapterName && !bluetoothPanGuids.empty()) {
            const size_t len = strlen(adapter->AdapterName);
            if (len > 0 && len < 64) {
                std::wstring adapterGuid(
                    adapter->AdapterName, adapter->AdapterName + len);
                if (adapterGuid.size() == 36)
                    adapterGuid = L"{" + adapterGuid + L"}";
                GUID guid{};
                if (adapterGuid.size() == 38 &&
                    adapterGuid.front() == L'{' &&
                    adapterGuid.back() == L'}' &&
                    SUCCEEDED(CLSIDFromString(adapterGuid.c_str(), &guid))) {
                    bool isBluetoothPan = false;
                    for (const auto& pan : bluetoothPanGuids) {
                        if (IsEqualGUID(pan, guid)) {
                            isBluetoothPan = true;
                            break;
                        }
                    }
                    if (isBluetoothPan) continue;
                }
            }
        }
        // Native WLAN inventory omits virtual SoftAP interfaces. When we
        // have identified a physical WLAN LUID, suppress other 802.11 child
        // interfaces; leave Ethernet, VPN and TUN adapters untouched.
        bool physicalWifi = false;
        if (adapter->IfType == IF_TYPE_IEEE80211 &&
            GetConnectivityState().wlan.HasPhysicalLuids()) {
            ULONGLONG luid = 0;
            static_assert(sizeof(luid) == sizeof(adapter->Luid));
            memcpy(&luid, &adapter->Luid, sizeof(luid));
            physicalWifi = GetConnectivityState().wlan.IsPhysicalLuid(luid);
            if (!physicalWifi) continue;
        }
        NetInterfaceState state;
        state.icon = physicalWifi ? NoticeIcon::Wifi : NoticeIcon::Network;
        state.connected = adapter->OperStatus == IfOperStatusUp;
        if (physicalWifi) {
            ULONGLONG luid = 0;
            memcpy(&luid, &adapter->Luid, sizeof(luid));
            const auto wlan = GetConnectivityState().wlan.live.find(luid);
            if (wlan != GetConnectivityState().wlan.live.end()) {
                state.connected = wlan->second.connected;
                state.wlanProfile = wlan->second.profile;
                state.wlanRadioKnown = wlan->second.radioKnown;
                state.wlanRadioOn = wlan->second.radioOn;
            } else if (GetConnectivityState().wlan.inventoryValid) {
                // The physical adapter remains in IP Helper's inventory but
                // disappeared from a *successful* Native WLAN enumeration.
                // That means its WLAN interface is disabled/unavailable,
                // not merely disconnected from an SSID profile.
                state.connected = false;
                state.wlanRadioKnown = true;
                state.wlanRadioOn = false;
            }
        }
        state.name = adapter->FriendlyName ? adapter->FriendlyName : Tr(OsdText::NetworkInterface);
        if (state.name.size() > 80) state.name.resize(80);
        out.emplace_back(adapter->AdapterName ? adapter->AdapterName : "",
                         std::move(state));
    }
    return out;
}

bool CaptureNetworkEvents() {
    bool succeeded = false;
    auto current = GetNetworkSnapshot(&succeeded);
    if (!succeeded) return false;
    bool changed = false;
    std::unordered_map<std::string, NetInterfaceState> next;
    next.reserve(current.size() + GetConnectivityState().network.interfaces.size());

    for (auto& item : current) {
        if (item.first.empty()) continue;
        const auto previous = GetConnectivityState().network.interfaces.find(item.first);
        // A new active adapter is also a connection event. Initial adapters
        // were captured at registration and are not announced at startup.
        const bool wasConnected = previous != GetConnectivityState().network.interfaces.end()
            && previous->second.connected;
        // On a WLAN disconnect, WlanQueryInterface no longer returns the
        // previous profile. Use our snapshot from when it was connected.
        const bool wifi = item.second.icon == NoticeIcon::Wifi;
        const std::wstring currentLabel = wifi &&
            !item.second.wlanProfile.empty()
            ? item.second.wlanProfile : item.second.name;
        const std::wstring previousLabel = wifi &&
            previous != GetConnectivityState().network.interfaces.end() &&
            !previous->second.wlanProfile.empty()
            ? previous->second.wlanProfile : item.second.name;
        const bool radioChanged = wifi &&
            previous != GetConnectivityState().network.interfaces.end() &&
            previous->second.wlanRadioKnown &&
            item.second.wlanRadioKnown &&
            previous->second.wlanRadioOn != item.second.wlanRadioOn;
        if (radioChanged) {
            // Radio power != association to a Wi-Fi profile. Report only a
            // *known* PHY radio transition, not an IP link-status inference.
            AddNoticeEvent(NoticeCategory::Network,
                item.second.wlanRadioOn ? NoticeAction::WifiEnabled :
                                          NoticeAction::WifiDisabled,
                std::wstring(item.first.begin(), item.first.end()) + L":radio",
                L"Wi-Fi", NoticeIcon::Wifi);
            changed = true;
        }
        const bool switchedProfile = wifi && wasConnected &&
            item.second.connected &&
            previous != GetConnectivityState().network.interfaces.end() &&
            !previous->second.wlanProfile.empty() &&
            !item.second.wlanProfile.empty() &&
            previous->second.wlanProfile != item.second.wlanProfile;
        if (switchedProfile && !radioChanged) {
            // A -> B with no lasting down state is a single final connected
            // transition. Publishing A-disconnected and B-connected on the
            // same OSD caused an unnecessary flash of the intermediate state.
            AddNoticeEvent(NoticeCategory::Network, NoticeAction::Connected,
                std::wstring(item.first.begin(), item.first.end()),
                currentLabel, NoticeIcon::Wifi);
            changed = true;
        } else if (item.second.connected != wasConnected &&
                   !(radioChanged && !item.second.wlanRadioOn)) {
            // Turning Wi-Fi radio off already has an explicit power event;
            // do not mislabel that same transition as a profile disconnect.
            AddNoticeEvent(NoticeCategory::Network, item.second.connected ?
                NoticeAction::Connected : NoticeAction::Disconnected,
                std::wstring(item.first.begin(), item.first.end()),
                item.second.connected ? currentLabel : previousLabel,
                item.second.icon);
            changed = true;
        }
        // Retain the last connected WLAN profile while disconnected, so an
        // eventual adapter removal can still identify the old connection.
        if (wifi && !item.second.connected &&
            item.second.wlanProfile.empty() &&
            previous != GetConnectivityState().network.interfaces.end())
            item.second.wlanProfile = previous->second.wlanProfile;
        // A temporary radio-query failure is not evidence that the radio
        // changed state; preserve the last known radio state.
        if (wifi && !item.second.wlanRadioKnown &&
            previous != GetConnectivityState().network.interfaces.end() &&
            previous->second.wlanRadioKnown) {
            item.second.wlanRadioKnown = true;
            item.second.wlanRadioOn = previous->second.wlanRadioOn;
        }
        next.emplace(std::move(item.first), std::move(item.second));
    }

    // Disabled adapters can disappear from the returned list altogether.
    // Preserve their last identity as "down" so re-enabling is reported.
    for (const auto& prior : GetConnectivityState().network.interfaces) {
        if (next.find(prior.first) != next.end()) continue;
        if (prior.second.icon == NoticeIcon::Wifi &&
            prior.second.wlanRadioKnown && prior.second.wlanRadioOn) {
            // A previously known physical WLAN interface disappeared. This
            // covers Device Manager disables that remove the IP interface.
            AddNoticeEvent(NoticeCategory::Network, NoticeAction::WifiDisabled,
                std::wstring(prior.first.begin(), prior.first.end()) + L":radio",
                L"Wi-Fi", NoticeIcon::Wifi);
            changed = true;
        } else if (prior.second.connected &&
                   prior.second.icon != NoticeIcon::Wifi) {
            AddNoticeEvent(NoticeCategory::Network, NoticeAction::Disconnected,
                std::wstring(prior.first.begin(), prior.first.end()),
                prior.second.name, prior.second.icon);
            changed = true;
        }
        if (next.size() < 256) {
            NetInterfaceState down = prior.second;
            down.connected = false;
            if (down.icon == NoticeIcon::Wifi) {
                down.wlanRadioKnown = true;
                down.wlanRadioOn = false;
            }
            next.emplace(prior.first, std::move(down));
        }
    }
    GetConnectivityState().network.interfaces = std::move(next);
    return changed;
}

void FinishNetworkRefresh() {
    if (GetConnectivityState().network.hintPending && !GetConnectivityState().network.sawInterfaceTransition) {
        // A genuine aggregate change without any observed NIC transition.
        // A level hint is not proof that any specific interface changed.
        AddNoticeEvent(NoticeCategory::Network, GetConnectivityState().network.hintLevel == 1 ?
            NoticeAction::Disconnected : NoticeAction::NetworkChanged,
            L"aggregate-connectivity", Tr(OsdText::WindowsNetwork),
            NoticeIcon::Network);
    }
    GetConnectivityState().network.ResetRefresh();
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
        if (!GetSettingsState()->showUsbEvents.load()) return true;
        const size_t pathMax = (header->dbch_size -
            offsetof(DEV_BROADCAST_DEVICEINTERFACE_W, dbcc_name)) / sizeof(WCHAR);
        if (pathMax == 0) return true;
        const size_t maxChars = std::min<size_t>(pathMax, 2048);
        size_t pathChars = 0;
        while (pathChars < maxChars && dev->dbcc_name[pathChars]) ++pathChars;
        const std::wstring path(dev->dbcc_name, pathChars);
        if (path.empty()) return true;
        std::wstring label;
        auto known = GetNoticeState().notice.usbNames.find(path);
        if (known != GetNoticeState().notice.usbNames.end()) label = known->second;
        else label = UsbDeviceLabel(path);
        if (type == DBT_DEVICEARRIVAL) {
            if (GetNoticeState().notice.usbNames.size() >= 256) GetNoticeState().notice.usbNames.clear();
            GetNoticeState().notice.usbNames[path] = label;
        } else {
            GetNoticeState().notice.usbNames.erase(path);
        }
        AddNoticeEvent(NoticeCategory::Usb, type == DBT_DEVICEARRIVAL ?
            NoticeAction::Connected : NoticeAction::Removed,
                       path, label);
        return true;
    }
    return false;
}

// --- Bluetooth AEP watcher (Classic + LE), UI-thread-owned WinRT objects. ---
// Use projected WinRT delegates rather than implementing custom COM
// IInspectable vtables; the Windows projection owns the ABI details.
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
    NoticeIcon icon = NoticeIcon::Bluetooth;
};
enum class ConnectionTransition : uint8_t { None, Connected, Disconnected };
struct DeviceState {
    std::wstring name;
    bool connectionKnown = false, connected = false;
    NoticeIcon icon = NoticeIcon::Bluetooth;

    // Enumeration is an observation, not an arrival event. The first
    // explicit IsConnected value is a silent baseline; only a later live
    // Updated event may yield a notification.
    ConnectionTransition ObserveConnection(bool next, bool liveUpdate) {
        const bool changed = connectionKnown && connected != next;
        connected = next;
        connectionKnown = true;
        if (!liveUpdate || !changed) return ConnectionTransition::None;
        return next ? ConnectionTransition::Connected
                    : ConnectionTransition::Disconnected;
    }
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
// Watchers, callbacks and baseline state form a single Bluetooth module.
// Stop() revokes callbacks before releasing owned collections.
struct BluetoothModuleState final {
    std::mutex queueMutex;
    std::vector<Event> queue;
    std::unordered_map<std::wstring, DeviceState> known;
    std::array<std::unique_ptr<Watcher>, 2> watchers;
    std::array<bool, 2> enumerationComplete{};
    std::atomic<HWND> receiver{nullptr};
    std::atomic<bool> accepting{false};
};
BluetoothModuleState& GetBluetoothState() {
    [[clang::no_destroy]] static BluetoothModuleState instance;
    return instance;
}
constexpr auto kInitialSnapshotTimeout = std::chrono::milliseconds(1800);

// Share exactly the same AEP property list across initial enumeration and
// live Watcher events, including IsConnected and Bluetooth device class.
auto ObservedProperties() {
    return winrt::single_threaded_vector<winrt::hstring>(
        std::vector<winrt::hstring>{kConnectedProperty,
            L"System.Devices.Aep.Bluetooth.Cod.Major",
            L"System.Devices.Aep.Bluetooth.Cod.Minor",
            L"System.Devices.Aep.Bluetooth.Le.Appearance.Category",
            L"System.Devices.Aep.Bluetooth.Le.Appearance.Subcategory"});
}

std::wstring Limited(winrt::hstring const& input, size_t maxChars) {
    return {input.c_str(), std::min<size_t>(input.size(), maxChars)};
}

bool TryCode(fc::IMapView<winrt::hstring,
    winrt::Windows::Foundation::IInspectable> const& properties,
    wchar_t const* key, uint16_t& code) {
    if (!properties || !properties.HasKey(key)) return false;
    try {
        const auto value = properties.Lookup(key);
        if (!value) return false;
        code = winrt::unbox_value<uint16_t>(value);
        return true;
    } catch (...) { return false; } // Optional class data is not fatal.
}
// CoD and LE Appearance are system metadata, not device-name heuristics.
NoticeIcon Classify(fc::IMapView<winrt::hstring,
    winrt::Windows::Foundation::IInspectable> const& properties,
    int transport) {
    uint16_t major = 0, minor = 0;
    if (transport == 0 &&
        TryCode(properties, L"System.Devices.Aep.Bluetooth.Cod.Major", major) &&
        TryCode(properties, L"System.Devices.Aep.Bluetooth.Cod.Minor", minor)) {
        if (major == 5) { // SIG peripheral: minor keyboard/mouse bits.
            if (minor >= 64) minor >>= 2;
            switch (minor & 0x30) {
                case 0x10: return NoticeIcon::Keyboard;
                case 0x20: return NoticeIcon::Mouse;
                default: break; // Composite keyboard+mouse is ambiguous.
            }
        } else if (major == 4) { // SIG audio/video minor classes.
            if (minor == 1 || minor == 2)
                return NoticeIcon::Headset;
            if (minor == 6) // SIG Audio/Video: Headphones.
                return NoticeIcon::Headphone;
            if (minor == 5 || minor == 7 || minor == 10)
                return NoticeIcon::Speaker;
        }
    } else if (transport == 1 &&
        TryCode(properties,
            L"System.Devices.Aep.Bluetooth.Le.Appearance.Category", major) &&
        TryCode(properties,
            L"System.Devices.Aep.Bluetooth.Le.Appearance.Subcategory", minor)) {
        if (major == 15) { // SIG LE human-interface appearance.
            if (minor == 1) return NoticeIcon::Keyboard;
            if (minor == 2) return NoticeIcon::Mouse;
        }
    }
    return NoticeIcon::Bluetooth;
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
    if (!GetBluetoothState().accepting.load(std::memory_order_acquire) ||
        GetCoreState().module.closing.load(std::memory_order_relaxed)) return;
    HWND target = GetBluetoothState().receiver.load(std::memory_order_acquire);
    if (!target) return;
    bool queued = false;
    {
        std::lock_guard<std::mutex> lock(GetBluetoothState().queueMutex);
        queued = GetBluetoothState().accepting.load(std::memory_order_relaxed) &&
                 GetBluetoothState().queue.size() < kMaxQueuedEvents;
        if (queued) GetBluetoothState().queue.emplace_back(std::move(event));
    }
    // A failed PostMessage leaves the event in the GetBluetoothState().queue. Any later callback
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
    GetBluetoothState().accepting.store(false, std::memory_order_release);
    GetBluetoothState().receiver.store(nullptr, std::memory_order_release);
    for (auto& watcher : GetBluetoothState().watchers) {
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
    for (auto& watcher : GetBluetoothState().watchers) {
        if (!watcher) continue;
        // All callbacks are bounded to a property read and a GetBluetoothState().queue append.
        // They cannot call user callbacks or wait for the OSD message loop.
        while (watcher->gate->inFlight.load(std::memory_order_acquire))
            Sleep(1);
        watcher.reset();
    }
    std::vector<Event> oldQueue;
    {
        std::lock_guard<std::mutex> lock(GetBluetoothState().queueMutex);
        GetBluetoothState().queue.swap(oldQueue);
    }
    // Stop already revoked every watcher and joined in-flight callbacks.
    // Release buckets instead of only clearing values in no_destroy globals.
    std::unordered_map<std::wstring, DeviceState> oldKnown;
    GetBluetoothState().known.swap(oldKnown);
    GetBluetoothState().enumerationComplete = {false, false};
}

// Capture existing paired AEPs during monitor initialization, before
// subscribing to watcher callbacks; never notify for the initial snapshot.
void SeedInitialState(int transport, winrt::hstring const& selector) {
    try {
        auto operation = de::DeviceInformation::FindAllAsync(
            selector, ObservedProperties(),
            de::DeviceInformationKind::AssociationEndpoint);
        const auto status = operation.wait_for(kInitialSnapshotTimeout);
        if (status != winrt::Windows::Foundation::AsyncStatus::Completed) {
            // The device broker must not block the OSD GetBluetoothState().receiver indefinitely.
            // Unknown IsConnected stays unknown, never assumed false.
            operation.Cancel();
            Wh_Log(L"Fluent OSD/Bluetooth: initial query transport=%d status=%d",
                   transport, static_cast<int>(status));
            return;
        }
        size_t seeded = 0, unknown = 0;
        for (auto const& info : operation.GetResults()) {
            if (GetBluetoothState().known.size() >= kMaxKnownDevices) break;
            try {
                const std::wstring id = Limited(info.Id(), 512);
                if (id.empty()) continue;
                const std::wstring key =
                    (transport ? L"ble:" : L"classic:") + id;
                DeviceState state;
                state.name = Limited(info.Name(), 80);
                state.icon = Classify(info.Properties(), transport);
                state.connectionKnown =
                    TryConnected(info.Properties(), state.connected);
                if (!state.connectionKnown) ++unknown;
                if (GetBluetoothState().known.emplace(key, std::move(state)).second) ++seeded;
            } catch (...) {
                ++unknown; // One malformed device must not discard the set.
            }
        }
        Wh_Log(L"Fluent OSD/Bluetooth: initial state transport=%d seeded=%u unknown=%u",
               transport, static_cast<unsigned>(seeded),
               static_cast<unsigned>(unknown));
    } catch (winrt::hresult_error const& error) {
        Wh_Log(L"Fluent OSD/Bluetooth: initial query transport=%d failed=0x%08lX",
               transport, static_cast<unsigned long>(error.code().value));
    } catch (...) {
        Wh_Log(L"Fluent OSD/Bluetooth: initial query transport=%d failed", transport);
    }
}

void StartOne(int transport, winrt::hstring const& selector) {
    auto item = std::make_unique<Watcher>();
    item->gate = std::make_shared<CallbackGate>();
    auto weak = std::weak_ptr<CallbackGate>(item->gate);
    item->value = de::DeviceInformation::CreateWatcher(
        selector, ObservedProperties(),
        de::DeviceInformationKind::AssociationEndpoint);

    item->added = item->value.Added([weak, transport](
        de::DeviceWatcher const&, de::DeviceInformation const& info) {
        WithGate(weak, [&] {
            Event event;
            event.transport = transport;
            event.change = Change::Added;
            event.id = Limited(info.Id(), 512);
            if (event.id.empty()) return;
            event.name = Limited(info.Name(), 80);
            event.icon = Classify(info.Properties(), transport);
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
            if (event.connectionPresent) {
                event.icon = Classify(info.Properties(), transport);
                Post(std::move(event));
            }
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
    GetBluetoothState().watchers[transport] = std::move(item);
    GetBluetoothState().watchers[transport]->value.Start();
}

void Start() {
    if (!GetCoreState().module.receiveWnd || GetCoreState().module.closing.load() ||
        !GetSettingsState()->showBluetoothEvents.load()) return;
    if (GetBluetoothState().watchers[0] || GetBluetoothState().watchers[1]) return;
    GetBluetoothState().receiver.store(GetCoreState().module.receiveWnd, std::memory_order_release);
    GetBluetoothState().accepting.store(true, std::memory_order_release);
    try {
        // Paired-only selectors do not trigger scans for arbitrary unpaired
        // nearby BLE devices. Classic and LE are both tracked as AEPs.
        const auto selector =
            db::BluetoothDevice::GetDeviceSelectorFromPairingState(true);
        SeedInitialState(0, selector);
        StartOne(0, selector);
    } catch (winrt::hresult_error const& error) {
        Wh_Log(L"Bluetooth Classic watcher failed: 0x%08lX",
               static_cast<unsigned long>(error.code().value));
    } catch (...) { Wh_Log(L"Bluetooth Classic watcher failed"); }
    try {
        const auto selector =
            db::BluetoothLEDevice::GetDeviceSelectorFromPairingState(true);
        SeedInitialState(1, selector);
        StartOne(1, selector);
    } catch (winrt::hresult_error const& error) {
        Wh_Log(L"Bluetooth LE watcher failed: 0x%08lX",
               static_cast<unsigned long>(error.code().value));
    } catch (...) { Wh_Log(L"Bluetooth LE watcher failed"); }
    if (!GetBluetoothState().watchers[0] && !GetBluetoothState().watchers[1]) Stop();
}

void Drain() {
    std::vector<Event> events;
    {
        std::lock_guard<std::mutex> lock(GetBluetoothState().queueMutex);
        events.swap(GetBluetoothState().queue);
    }
    if (!GetBluetoothState().accepting.load(std::memory_order_acquire)) return;

    for (auto& event : events) {
        if (event.transport < 0 || event.transport > 1) continue;
        const size_t transport = static_cast<size_t>(event.transport);
        if (event.change == Change::Completed) {
            GetBluetoothState().enumerationComplete[transport] = true; // Initial scan is silent.
            continue;
        }
        if (event.id.empty()) continue;
        const std::wstring id = (transport ? L"ble:" : L"classic:") + event.id;
        auto previous = GetBluetoothState().known.find(id);
        if (event.change == Change::Removed) {
            // DeviceWatcher collection removal is not proof of a transport
            // disconnect. Discard the baseline and do not notify.
            if (previous != GetBluetoothState().known.end()) GetBluetoothState().known.erase(previous);
            continue;
        }
        if (previous == GetBluetoothState().known.end()) {
            if (GetBluetoothState().known.size() >= kMaxKnownDevices) continue;
            previous = GetBluetoothState().known.emplace(id, DeviceState{}).first;
        }
        auto& current = previous->second;
        if (!event.name.empty()) current.name = std::move(event.name);
        // Partial updates without classification cannot erase a GetBluetoothState().known icon.
        if (event.icon != NoticeIcon::Bluetooth) current.icon = event.icon;
        if (!event.connectionPresent) continue;
        // A proactive startup snapshot seeds the state; Watcher Added then
        // silently reconciles observations made during subscription.
        // Require the initial enumeration to finish
        // and an explicit IsConnected transition from a live Updated event.
        const bool liveUpdate = GetBluetoothState().enumerationComplete[transport] &&
            event.change == Change::Updated;
        const bool wasConnected = current.connected;
        const ConnectionTransition transition =
            current.ObserveConnection(event.connected, liveUpdate);
        if (transition != ConnectionTransition::None &&
            GetSettingsState()->showBluetoothEvents.load()) {
            Wh_Log(L"Fluent OSD/Bluetooth: AEP update transport=%d old=%d new=%d",
                   event.transport, static_cast<int>(wasConnected),
                   static_cast<int>(event.connected));
            AddNoticeEvent(NoticeCategory::Bluetooth,
                transition == ConnectionTransition::Connected
                    ? NoticeAction::Connected : NoticeAction::Disconnected,
                id, current.name.empty() ? Tr(OsdText::BluetoothDevice)
                                         : current.name, current.icon);
        }
    }
}
} // namespace bt_monitor

// ============================================================
// Master and multi-display rendering
// ============================================================
// No DDC or monitor I/O, timers or extra worker threads in this renderer.
// Draw to premultiplied BGRA pixels before publishing a layered surface.
// Shared placement output is authoritative for both render backends.
// A renderer reads the calculated bounds, never measures another
// backend's hidden HWND to discover where it should draw.
namespace osd_placement {
void Publish(const PopupPlacement& placement) {
    auto& state = GetCoreState().presentation.placement;
    state.current = placement;
    state.valid = true;
}
void Invalidate() {
    GetCoreState().presentation.placement.valid = false;
}
bool CurrentAnchor(RECT& anchor) {
    const auto& state = GetCoreState().presentation.placement;
    if (!state.valid) return false;
    anchor = state.current.bounds;
    return true;
}
}
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
        GetSettingsState()->ddcSizePercent.load(std::memory_order_relaxed) / 100.0f;
    p.scale = dpiScale * sizeScale;
    const bool statusNotice = GetCoreState().presentation.popupKind == PopupKind::LockStatus ||
        GetCoreState().presentation.popupKind == PopupKind::NativeEvent ||
        GetCoreState().presentation.popupKind == PopupKind::Notification;
    const bool imageNotice = GetCoreState().presentation.popupKind == PopupKind::Notification &&
        GetNoticeState().notice.clipboardThumbnail;
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
    switch (GetSettingsState()->position.load(std::memory_order_relaxed)) {
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
    x += static_cast<int>(std::lround(GetSettingsState()->offsetX.load() * dpiScale));
    y += static_cast<int>(std::lround(GetSettingsState()->offsetY.load() * dpiScale));
    const int position = GetSettingsState()->position.load(std::memory_order_relaxed);
    x = ClampPopupAxis(x, p.width,
        PositionCentersX(position) ? display : work, true);
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
void MovePopupToDisplay(const BrightnessEvent& ev) {
    WCHAR device[CCHDEVICENAME]{};
    const int outputMode = GetSettingsState()->displayOutputMode.load(std::memory_order_relaxed);
    if ((outputMode == 0 ||
         (outputMode == 3 && GetCoreState().presentation.popupKind == PopupKind::DdcBrightness)) &&
        ev.device[0]) {
        wcscpy_s(device, ev.device);
    } else if (outputMode == 2) {
        swprintf_s(device, L"\\\\.\\DISPLAY%d",
                   GetSettingsState()->displayOutputNumber.load(std::memory_order_relaxed));
    }
    HMONITOR monitor = FindMonitorByDeviceName(device);
    if (!monitor)
        monitor = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    PopupPlacement place{};
    if (!CalculatePopupPlacement(monitor, place)) {
        osd_placement::Invalidate();
        return;
    }
    osd_placement::Publish(place);
    GetAudioState().panel.scale = place.scale;
    // XAML owns the visible HWND; this adapter publishes owned geometry.
}

// Reapply anchor placement only when opening/closing a panel changes the
// expected composite bounds. This also keeps the bar/chevron/speaker input
// windows aligned with the relocated main popup.
// Shared properties of all migrated XAML level indicators; the source
// value, event identity and monitor placement remain category-specific.
xaml_osd::Snapshot MakeXamlSnapshot(
        PopupKind kind, const RECT& anchor, float scale) {
    const auto settings = GetSettingsState();
    xaml_osd::Snapshot data;
    data.kind = kind == PopupKind::NativeVolume
        ? xaml_osd::LevelKind::Volume
        : kind == PopupKind::DdcBrightness
        ? xaml_osd::LevelKind::DdcBrightness
        : xaml_osd::LevelKind::NativeBrightness;
    data.brightness = kind != PopupKind::NativeVolume;
    data.receiver = GetCoreState().module.receiveWnd;
    data.showIcon = !data.brightness || settings->showSun.load();
    data.percent = GetCoreState().presentation.nativePercent;
    data.rawValue = GetCoreState().presentation.nativePercent;
    data.valueKnown = GetCoreState().presentation.nativePercentKnown;
    data.muted = !data.brightness && GetCoreState().presentation.nativeMuted;
    data.mixerChevron = kind == PopupKind::NativeVolume &&
        settings->showMixerArrow.load();
    data.durationMs = OsdDuration(kind == PopupKind::DdcBrightness
        ? DurationKind::DdcBrightness
        : kind == PopupKind::NativeBrightness
        ? DurationKind::NativeBrightness : DurationKind::Volume, *settings);
    data.anchor = anchor;
    data.scale = scale;
    data.vertical = settings->verticalVolumeBrightness.load();
    data.showValue = settings->showValue.load();
    data.innerPadding = settings->innerPadding.load();
    data.iconSize = settings->iconSize.load();
    data.fontSize = settings->fontSize.load();
    const bool light = IsLightTheme(*settings);
    data.background = OsdBackgroundRgb(light, *settings);
    data.backgroundAlpha = OsdBackgroundAlpha(*settings);
    settings->CopyBrushLayers(data.layeredBackground, data.backgroundLayers);
    data.borderless = settings->ddcBorderless.load();
    data.cornerRadius = settings->cornerRadius.load();
    data.fadeEnabled = settings->fadeEnabled.load();
    data.fadeDurationMs = static_cast<DWORD>(settings->fadeDuration.load());
    data.text = OsdTextRgb(light, *settings);
    data.accent = OsdAccentRgb(*settings);
    data.track = OsdTrackRgb(light, false, *settings);
    return data;
}

// Multi-display projection belongs to the controller, NOT XAML painting.
// Replicas have per-display DPI/placement but no input commands or timers.
int XamlMirrorOffset(int position, int difference, bool horizontal) {
    if (horizontal) {
        if (position == 2 || position == 6 || position == 8)
            return difference;
        if (PositionCentersX(position)) return difference / 2;
    } else {
        if (position == 0 || position == 1 || position == 2)
            return difference;
        if (PositionCentersY(position)) return difference / 2;
    }
    return 0;
}
bool ShowXamlMirroredBatch(std::vector<xaml_osd::Snapshot> batch) {
    if (batch.empty()) return false;
    if (GetSettingsState()->displayOutputMode.load(std::memory_order_relaxed) == 3 &&
        batch.front().kind != xaml_osd::LevelKind::DdcBrightness) {
        const bool attached = batch.size() == 2 &&
            ((batch.front().kind == xaml_osd::LevelKind::Volume &&
              (batch[1].kind == xaml_osd::LevelKind::Media ||
               batch[1].kind == xaml_osd::LevelKind::Mixer)) ||
             (batch.front().kind == xaml_osd::LevelKind::NoticeStatus &&
              batch[1].kind == xaml_osd::LevelKind::NoticeDetails));
        const xaml_osd::Snapshot master = batch.front();
        MirrorScan scan{MonitorFromRect(&master.anchor,
            MONITOR_DEFAULTTONEAREST), {}};
        EnumDisplayMonitors(nullptr, nullptr, FindMirrorCallback,
            reinterpret_cast<LPARAM>(&scan));
        const int position = GetSettingsState()->position.load(std::memory_order_relaxed);
        const double originalScale = std::max(.5, double(master.scale));
        for (HMONITOR monitor : scan.peers) {
            MONITORINFOEXW info{};
            info.cbSize = sizeof(info);
            PopupPlacement target{};
            if (!GetMonitorInfoW(monitor, &info) ||
                !CalculatePopupPlacement(monitor, target) ||
                target.scale <= 0.0f) continue;
            const double ratio = target.scale / originalScale;
            const auto scaled = [&](LONG length) {
                return std::clamp(
                    static_cast<int>(std::lround(length * ratio)), 1, 4096);
            };
            const int width = scaled(
                master.anchor.right-master.anchor.left);
            const int height = scaled(
                master.anchor.bottom-master.anchor.top);
            int x = target.bounds.left + XamlMirrorOffset(
                position, target.width-width, true);
            int y = target.bounds.top + XamlMirrorOffset(
                position, target.height-height, false);
            x = ClampPopupAxis(x,width,PositionCentersX(position)
                ? target.monitorBounds : target.work,true);
            y = ClampPopupAxis(y,height,PositionCentersY(position)
                ? target.monitorBounds : target.work,false);
            RECT main{x,y,x+width,y+height}, panel{};
            if (attached) {
                const auto& originalPanel = batch[1];
                const int pw = scaled(originalPanel.anchor.right -
                                      originalPanel.anchor.left);
                const int ph = scaled(originalPanel.anchor.bottom -
                                      originalPanel.anchor.top);
                const bool vertical = master.vertical;
                const auto direction = DirectionForPopup(
                    main,target.work,position,vertical);
                auto offset = GetPanelAttachment(
                    vertical,direction,target.scale,width,height,pw,ph);
                if (vertical) {
                    const int correction = static_cast<int>(
                        std::lround(3.0*target.scale));
                    offset.x += direction == FlyoutDirection::Left
                        ? correction : -correction;
                }
                if (vertical && PositionCentersX(position)) {
                    const int low = std::min(0,offset.x);
                    const int high = std::max(width,offset.x+pw);
                    const int shift = (width-low-high)/2;
                    main.left += shift; main.right += shift;
                } else if (!vertical && PositionCentersY(position)) {
                    const int low = std::min(0,offset.y);
                    const int high = std::max(height,offset.y+ph);
                    const int shift = (height-low-high)/2;
                    main.top += shift; main.bottom += shift;
                }
                const int px = ClampPopupAxis(main.left+offset.x,pw,
                    !vertical && PositionCentersX(position)
                        ? target.monitorBounds : target.work,true);
                const int py = ClampPopupAxis(main.top+offset.y,ph,
                    vertical && PositionCentersY(position)
                        ? target.monitorBounds : target.work,false);
                panel=RECT{px,py,px+pw,py+ph};
            }
            const std::wstring prefix=std::wstring(L"mirror:")+
                info.szDevice;
            auto replica=master;
            replica.key=prefix+L":main";
            replica.anchor=main;
            replica.scale=target.scale;
            replica.receiver=nullptr;
            replica.mirrorView=true;
            batch.push_back(std::move(replica));
            if (attached) {
                auto other=batch[1];
                other.key=prefix+L":panel";
                other.anchor=panel;
                other.scale=target.scale;
                other.receiver=nullptr;
                other.mirrorView=true;
                batch.push_back(std::move(other));
            }
        }
    }
    return xaml_osd::ShowBatch(batch);
}
bool ShowXamlMirrored(xaml_osd::Snapshot snapshot) {
    return ShowXamlMirroredBatch({std::move(snapshot)});
}

// All compact XAML categories share one rendering snapshot contract.
// Device/native notices and lock keys differ only in content and behavior;
// the background/theme/placement lifecycle is inherited from MakeXamlSnapshot.
xaml_osd::Snapshot MakeXamlStatusSnapshot(
        xaml_osd::LevelKind category, const RECT& anchor,
        DurationKind duration, bool fluentIcon = false) {
    return osd_model::AsStatus(
        MakeXamlSnapshot(PopupKind::NativeBrightness, anchor, GetAudioState().panel.scale),
        category, OsdDuration(duration), fluentIcon);
}

// Category changes are controller state, never rendering side effects.
void PrepareXamlCategory() {
    if (GetCoreState().presentation.popupKind != PopupKind::NativeVolume) {
        ResetXamlMixerController();
        ResetXamlMediaController();
    }
}
bool ShowXamlDdcTargets(
        const BrightnessEvent& master,
        const std::vector<BrightnessEvent>* changedTargets = nullptr) {
    const int mode = GetSettingsState()->displayOutputMode.load(std::memory_order_relaxed);
    std::vector<xaml_osd::Snapshot> batch;
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
        // Source and All both pin DDC to the *changed* physical outputs.
        // Cached values remain available for input/rollback, but do not
        // cause previously touched monitors to reappear or restart timers.
        const auto appendTarget = [&](const BrightnessEvent& ev) {
            HMONITOR monitor = FindMonitorByDeviceName(ev.device);
            PopupPlacement placement{};
            if (!monitor || !CalculatePopupPlacement(monitor, placement)) {
                Wh_Log(L"Fluent OSD/XAML: unresolved DDC display '%s'",
                       ev.device);
                return;
            }
            push(ev, placement.bounds, placement.scale);
        };
        if (changedTargets) {
            for (const auto& ev : *changedTargets) appendTarget(ev);
        } else {
            appendTarget(master);
        }
    } else {
        // Primary/selected output remains one card with the chosen event.
        RECT anchor{};
        if (osd_placement::CurrentAnchor(anchor))
            push(master, anchor, GetAudioState().panel.scale);
    }
    if (batch.empty()) {
        Wh_Log(L"Fluent OSD/XAML: no resolvable DDC snapshots");
        // An unresolved delta must not dismiss another monitor's live OSD.
        return false;
    }
    const bool ok = xaml_osd::ShowBatch(batch);
    if (!ok)
        Wh_Log(L"Fluent OSD/XAML: DDC batch not delivered");
    return ok;
}

// Coalesce writes per physical display, not across all displays. Each
// target's raw value and range survive the burst for independent painting.
void DisplayDdcBatch() {
    std::vector<BrightnessEvent> events =
        GetBrightnessState().ddc.TakeBatchOnControllerThread();
    if (GetCoreState().module.closing.load() || !GetSettingsState()->showDdcBrightness.load() || events.empty())
        return;

    const ULONGLONG now = GetTickCount64();
    const int mode = GetSettingsState()->displayOutputMode.load(std::memory_order_relaxed);
    const ULONGLONG expiry = now + static_cast<ULONGLONG>(
        OsdDuration(DurationKind::DdcBrightness));
    // The cache lasts only for the active OSD period, never indefinitely.
    GetBrightnessState().ddc.targets.erase(std::remove_if(GetBrightnessState().ddc.targets.begin(),
        GetBrightnessState().ddc.targets.end(), [now](const DdcTargetState& item) {
            return item.expiresAt <= now;
        }), GetBrightnessState().ddc.targets.end());

    BrightnessEvent master{};
    bool masterChosen = false;
    std::vector<BrightnessEvent> changedTargets;
    changedTargets.reserve(events.size());
    // XAML keeps the primary host hidden in DDC multi-target mode. The
    // unexpired per-display target cache, not that HWND, determines pinning.
    const bool priorTargetActive = std::any_of(
        GetBrightnessState().ddc.targets.begin(), GetBrightnessState().ddc.targets.end(),
        [&](const DdcTargetState& previous) {
            return previous.expiresAt > now &&
                previous.event.physicalIndex == GetCoreState().presentation.visible.physicalIndex &&
                _wcsicmp(previous.event.device, GetCoreState().presentation.visible.device) == 0;
        });
    bool pinnedMaster = false; // Only a genuinely changed target may pin.
    WCHAR preferredDevice[CCHDEVICENAME]{};
    if (mode == 1 || mode == 2) {
        HMONITOR preferredMonitor = nullptr;
        if (mode == 2) {
            WCHAR device[CCHDEVICENAME]{};
            swprintf_s(device, L"\\\\.\\DISPLAY%d",
                GetSettingsState()->displayOutputNumber.load(std::memory_order_relaxed));
            preferredMonitor = FindMonitorByDeviceName(device);
        }
        if (!preferredMonitor)
            preferredMonitor = MonitorFromPoint(
                POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
        MONITORINFOEXW monitorInfo{};
        monitorInfo.cbSize = sizeof(monitorInfo);
        if (GetMonitorInfoW(preferredMonitor, &monitorInfo))
            wcscpy_s(preferredDevice, monitorInfo.szDevice);
    }

    for (const BrightnessEvent& ev : events) {
        const HMONITOR target = FindMonitorByDeviceName(ev.device);
        if (!target && (mode == 0 || mode == 3)) {
            if (_wcsicmp(GetBrightnessState().ddc.lastUnresolved, ev.device) != 0 ||
                !GetBrightnessState().ddc.lastUnresolved[0]) {
                wcscpy_s(GetBrightnessState().ddc.lastUnresolved, ev.device);
                Wh_Log(L"DDC event target unresolved: device='%s', "
                       L"physicalIndex=%lu, senderPID=%lu; skipping "
                       L"unknown target.", ev.device, ev.physicalIndex,
                       ev.producerPid);
            }
            continue;
        }
        bool valueChanged = true;
        if (target) {
            if (_wcsicmp(GetBrightnessState().ddc.lastTarget, ev.device) != 0) {
                wcscpy_s(GetBrightnessState().ddc.lastTarget, ev.device);
                Wh_Log(L"DDC target resolved: '%s' (physicalIndex=%lu)",
                       ev.device, ev.physicalIndex);
            }
            GetBrightnessState().ddc.lastUnresolved[0] = L'\0';
            const auto sameDevice = [&](const DdcTargetState& state) {
                return state.event.physicalIndex == ev.physicalIndex &&
                       _wcsicmp(state.event.device, ev.device) == 0;
            };
            auto it = std::find_if(GetBrightnessState().ddc.targets.begin(),
                                   GetBrightnessState().ddc.targets.end(), sameDevice);
            if (it != GetBrightnessState().ddc.targets.end()) {
                valueChanged = it->event.value != ev.value;
                it->event = ev; // Preserve the latest range even for same-value writes.
                if (valueChanged) it->expiresAt = expiry;
            } else if (GetBrightnessState().ddc.targets.size() < kMaxDdcTargets) {
                GetBrightnessState().ddc.targets.push_back({ev, expiry});
            }
        }
        if (!valueChanged) continue;
        changedTargets.push_back(ev);
        // Preserve an actively edited physical target as controller master
        // only when that target actually changed in this batch.
        const bool editedMaster = (mode == 0 || mode == 3) &&
            GetCoreState().presentation.popupKind == PopupKind::DdcBrightness &&
            priorTargetActive &&
            ev.physicalIndex == GetCoreState().presentation.visible.physicalIndex &&
            _wcsicmp(ev.device, GetCoreState().presentation.visible.device) == 0;
        if (editedMaster) {
            master = ev;
            masterChosen = true;
            pinnedMaster = true;
        } else if (!masterChosen ||
                   ((mode == 0 || mode == 3) && !pinnedMaster) ||
                   (preferredDevice[0] &&
                    _wcsicmp(preferredDevice, ev.device) == 0)) {
            master = ev;
            masterChosen = true;
        }
    }
    if (!masterChosen) return;

    GetCoreState().presentation.visible = master;
    GetBrightnessState().ddc.lastConfirmedDdc = master.value;
    GetCoreState().presentation.popupKind = PopupKind::DdcBrightness;
    MovePopupToDisplay(master);
    PrepareXamlCategory();
    (void)ShowXamlDdcTargets(master, &changedTargets);
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
            GetBrightnessState().ddc.UpdateHandleRange(
                monitor, task.monitor.minimum, task.monitor.maximum);
            const int vcp = GetSettingsState()->vcpCode.load();
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
    while (WaitForSingleObject(GetBrightnessState().writer.wake, INFINITE) == WAIT_OBJECT_0) {
        if (GetBrightnessState().writer.stop.load()) break;
        std::vector<BrightnessWheelTask> tasks = GetBrightnessState().writer.TakePending();
        for (const auto& task : tasks) {
            if (GetBrightnessState().writer.stop.load()) break;
            // Skip a snapshot superseded while another DDC command ran.
            if (GetBrightnessState().writer.IsSuperseded(task)) continue;
            const ULONGLONG startedAt = GetTickCount64();
            const bool success = task.native ?
                (comReady && WriteNativeBrightnessWmi(
                    static_cast<BYTE>(std::clamp(task.value, 0, 100))))
                : WriteExternalBrightnessDdc(task);
            const ULONGLONG elapsed = GetTickCount64() - startedAt;
            if (elapsed >= 1500)
                Wh_Log(L"Fluent OSD/brightness: slow worker operation native=%d duration=%llu ms",
                       task.native, static_cast<unsigned long long>(elapsed));
            // This worker must not read the controller-owned HWND.
            const HWND receiver = GetCoreState().module.ReceiverForCallbacks();
            if (receiver)
                PostMessageW(receiver, kBrightnessWheelResultMessage,
                    static_cast<WPARAM>(task.generation),
                    static_cast<LPARAM>((success ? 1 : 0) |
                                        (task.native ? 2 : 0)));
        }
    }
    if (comReady) CoUninitialize();
    return 0;
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
        if (GetAudioState().media.stop.load(std::memory_order_relaxed) ||
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
    if (!thumbnail || !GetSettingsState()->showMediaArtwork.load(std::memory_order_relaxed))
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
            if (GetSettingsState()->showMediaArtwork.load(std::memory_order_relaxed)) {
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
    GetAudioState().media.Request(command, position);
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
        while (WaitForSingleObject(GetAudioState().media.wake, INFINITE) == WAIT_OBJECT_0) {
            if (GetAudioState().media.stop.load()) break;
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
                std::vector<MediaCommand> commands = GetAudioState().media.TakeCommands();
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
                GetAudioState().media.Publish(std::move(snapshot));
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

// The Windows System Sounds session has no conventional application icon.
// EarTrumpet uses audiosrv.dll RT_GROUP_ICON resource 203 for this purpose.
// A negative ExtractIconEx index selects a resource ID (not its ordinal).
// The caller owns the resulting HICON and must destroy it after conversion.
HICON SystemSoundsIcon() {
    WCHAR systemDir[MAX_PATH]{};
    const UINT length = GetSystemDirectoryW(systemDir, ARRAYSIZE(systemDir));
    if (!length || length >= ARRAYSIZE(systemDir)) return nullptr;
    std::wstring path(systemDir, length);
    path += L"\\audiosrv.dll";
    HICON icon = nullptr;
    if (ExtractIconExW(path.c_str(), -203, nullptr, &icon, 1) != 1) {
        if (icon) DestroyIcon(icon);
        return nullptr;
    }
    return icon;
}

void ResetXamlMediaController() {
    if (!GetAudioState().panel.mediaOpen) return;
    GetAudioState().panel.mediaOpen=false;
    if (GetCoreState().module.receiveWnd) KillTimer(GetCoreState().module.receiveWnd,kMediaAnimationTimer);
    ++GetAudioState().panel.mediaGeneration;
    if (!GetAudioState().panel.mediaGeneration) ++GetAudioState().panel.mediaGeneration;
}
void ResetXamlMixerController() {
    if (!GetAudioState().panel.mixerOpen) return;
    GetAudioState().panel.mixerOpen = false;
    GetAudioState().panel.mixerOutputExpanded = false;
    GetAudioState().mixer.ClosePanelOnControllerThread();
    ++GetAudioState().panel.mixerGeneration; // Discard commands from the old Mixer Island.
    if (!GetAudioState().panel.mixerGeneration) ++GetAudioState().panel.mixerGeneration;
}

void StartMixerOutputNotifications() {
    if (GetAudioState().mixer.notify || !GetCoreState().module.receiveWnd) return;
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(enumerator.GetAddressOf()));
    if (FAILED(hr)) return;
    auto* callback = new (std::nothrow) MixerOutputNotifications(GetCoreState().module.receiveWnd);
    if (!callback) return;
    hr = enumerator->RegisterEndpointNotificationCallback(callback);
    if (SUCCEEDED(hr)) {
        GetAudioState().mixer.notify.Attach(callback); // callback's construction reference
        GetAudioState().mixer.notifyEnumerator = std::move(enumerator);
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
    GetAudioState().mixer.ClearOutputDevicesOnControllerThread();
    Microsoft::WRL::ComPtr<IMMDevice> current;
    if (SUCCEEDED(enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia,
                                                    current.GetAddressOf()))) {
        LPWSTR id = nullptr;
        if (SUCCEEDED(current->GetId(&id)) && id) {
            GetAudioState().mixer.outputId.assign(id);
            CoTaskMemFree(id);
        }
    }
    Microsoft::WRL::ComPtr<IMMDeviceCollection> collection;
    if (FAILED(enumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE,
                                              collection.GetAddressOf())))
        return;
    UINT count = 0;
    if (FAILED(collection->GetCount(&count))) return;
    for (UINT i = 0; i < count && GetAudioState().mixer.outputOptions.size() <
            static_cast<size_t>(kMaxMixerOutputDevices); ++i) {
        Microsoft::WRL::ComPtr<IMMDevice> device;
        if (FAILED(collection->Item(i, device.GetAddressOf()))) continue;
        LPWSTR id = nullptr;
        if (FAILED(device->GetId(&id)) || !id) continue;
        AudioOutputOption output{id, AudioOutputFriendlyName(device.Get())};
        CoTaskMemFree(id);
        if (output.id == GetAudioState().mixer.outputId)
            GetAudioState().mixer.outputOptions.insert(GetAudioState().mixer.outputOptions.begin(), std::move(output));
        else
            GetAudioState().mixer.outputOptions.push_back(std::move(output));
    }
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
    ++GetAudioState().panel.mixerGeneration;
    if (!GetAudioState().panel.mixerGeneration) ++GetAudioState().panel.mixerGeneration;
    GetAudioState().mixer.PrepareRefreshOnControllerThread();
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_ALL, IID_PPV_ARGS(enumerator.GetAddressOf()));
    if (FAILED(hr) || !enumerator) {
        GetAudioState().mixer.ClearOutputDevicesOnControllerThread();
        return;
    }
    ReadMixerOutputDevices(enumerator.Get());
    IMMDevice* device = nullptr;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (FAILED(hr) || !device) return;
    device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL,
        nullptr, reinterpret_cast<void**>(GetAudioState().mixer.master.GetAddressOf()));
    if (GetAudioState().mixer.master) {
        GetAudioState().mixer.master->GetMasterVolumeLevelScalar(&GetAudioState().mixer.masterLevel);
        BOOL muted = FALSE;
        if (SUCCEEDED(GetAudioState().mixer.master->GetMute(&muted)))
            GetAudioState().mixer.masterMuted = muted != FALSE;
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
            LPWSTR instanceId = nullptr;
            if (SUCCEEDED(info->GetSessionInstanceIdentifier(&instanceId)) &&
                instanceId)
                entry.sessionId.assign(instanceId);
            if (instanceId) CoTaskMemFree(instanceId);
            // System Sounds may supply an indirect MUI resource string as its
            // display name. Prefer Core Audio's explicit session identity
            // instead of showing the unresolved resource or guessing by PID.
            // S_FALSE means a normal application session, not an API failure.
            const bool systemSounds = info->IsSystemSoundsSession() == S_OK;
            if (systemSounds) {
                entry.title = Tr(OsdText::SystemSounds);
                entry.appIcon = SystemSoundsIcon();
                entry.iconPixels = MixerIconPixels(entry.appIcon);
            }
            DWORD pid = 0;
            if (!systemSounds && SUCCEEDED(info->GetProcessId(&pid))) {
                if (entry.title.empty()) entry.title = ProcessTitle(pid);
                entry.appIcon = ProcessIcon(pid);
                entry.iconPixels = MixerIconPixels(entry.appIcon);
            }
            info->Release();
        }
        if (entry.title.empty()) entry.title = L"Application";
        control->Release();
        GetAudioState().mixer.entries.emplace_back(std::move(entry));
    }
    sessions->Release();
}

void SelectMixerOutput(int index) {
    if (index < 0 || index >= static_cast<int>(GetAudioState().mixer.outputOptions.size()))
        return;
    const std::wstring target = GetAudioState().mixer.outputOptions[index].id;
    GetAudioState().mixer.outputSwitchFailed = false;
    if (target != GetAudioState().mixer.outputId) {
        const HRESULT hr = SetWindowsDefaultPlaybackEndpoint(target,
                                                             GetAudioState().mixer.outputId);
        if (FAILED(hr)) {
            GetAudioState().mixer.outputSwitchFailed = true;
            Wh_Log(L"Mixer default output switch failed: 0x%08lX",
                   static_cast<unsigned long>(hr));
        } else {
            // Drop stale Core Audio endpoint/session references immediately.
            // Endpoint notifications also catch asynchronous Windows changes.
            RefreshMixer();
        }
    }
}

// Generation rejects commands from previous enumerations. This additional
// POD fingerprint rejects mismatched session identities within a generation.
// A missing ID falls back to the existing generation/index validation.
bool MixerCommandMatchesCurrentRow(const osd_control::Command& cmd) {
    if (cmd.index < 0 ||
        cmd.index > static_cast<int>(GetAudioState().mixer.entries.size()))
        return false;
    if (!cmd.mixerSessionTag) return true;
    if (cmd.index == 0)
        return !GetAudioState().mixer.outputId.empty() &&
            cmd.mixerSessionTag == osd_control::MixerIdentityTag(
                L"@master:" + GetAudioState().mixer.outputId);
    return cmd.mixerSessionTag == osd_control::MixerIdentityTag(
        GetAudioState().mixer.entries[cmd.index - 1].sessionId);
}

// Shared Core Audio operation used by both view backends.
bool SetMixerPercent(int index, int percent) {
    if (index < 0 || index > static_cast<int>(GetAudioState().mixer.entries.size()))
        return false;
    const float value = std::clamp(percent, 0, 100) / 100.0f;
    if (!index) {
        if (!GetAudioState().mixer.master || FAILED(
            GetAudioState().mixer.master->SetMasterVolumeLevelScalar(value, nullptr)))
            return false;
        GetAudioState().mixer.masterLevel = value;
        return true;
    }
    auto& entry = GetAudioState().mixer.entries[index - 1];
    if (!entry.volume || FAILED(entry.volume->SetMasterVolume(value, nullptr)))
        return false;
    entry.scalar = value;
    return true;
}

void ToggleMixerMute(int index) {
    if (index < 0 || index > static_cast<int>(GetAudioState().mixer.entries.size())) return;
    if (index == 0) {
        if (!GetAudioState().mixer.master) return;
        BOOL current = FALSE;
        if (FAILED(GetAudioState().mixer.master->GetMute(&current))) return;
        const BOOL requested = current ? FALSE : TRUE;
        if (SUCCEEDED(GetAudioState().mixer.master->SetMute(requested, nullptr))) {
            BOOL actual = requested;
            GetAudioState().mixer.master->GetMute(&actual);
            GetAudioState().mixer.masterMuted = actual != FALSE;
        }
    } else {
        auto& entry = GetAudioState().mixer.entries[index - 1];
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
}

// ============================================================
// Lock key hook and XAML-only category routing
// ============================================================
LRESULT CALLBACK LockKeyProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && lp) {
        const auto* event = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lp);
        for (int i = 0; i < 4; ++i) {
            if (event->vkCode != static_cast<DWORD>(kLockVk[i])) continue;
            bool down = wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN;
            bool up = wp == WM_KEYUP || wp == WM_SYSKEYUP;
            if (down && !GetNoticeState().keys.pressed[i]) {
                GetNoticeState().keys.pressed[i] = true;
                GetNoticeState().keys.toggle[i] = !GetNoticeState().keys.toggle[i];
                if (GetSettingsState()->showLockKeys[i].load() && GetCoreState().module.receiveWnd)
                    PostMessageW(GetCoreState().module.receiveWnd, kLockToggleMessage,
                                 static_cast<WPARAM>(i),
                                 static_cast<LPARAM>(GetNoticeState().keys.toggle[i]));
            } else if (up) GetNoticeState().keys.pressed[i] = false;
            break;
        }
    }
    return CallNextHookEx(GetNoticeState().keys.hook, code, wp, lp);
}

// XAML Island controls all pointer input; no detached hit HWND is needed.
void ShowMigratedXamlLevel(PopupKind kind) {
    const bool brightness = kind == PopupKind::NativeBrightness;
    if (!brightness&&GetSettingsState()->showSmtcOnVolume.load()&&
       GetAudioState().media.current.available&&!GetAudioState().panel.mixerOpen&&
       ShowXamlMediaPanel()) return;
    if (GetAudioState().panel.mediaOpen) ResetXamlMediaController();
    PrepareXamlCategory();
    RECT target{};
    if (!osd_placement::CurrentAnchor(target)) {
        Wh_Log(L"Fluent OSD/XAML: XAML %s missing anchor",
               brightness ? L"brightness" : L"volume");
        return;
    }
    auto snapshot = MakeXamlSnapshot(kind, target, GetAudioState().panel.scale);
    if (!brightness && snapshot.mixerChevron) {
        RECT plannedMain{}, plannedPanel{};
        if (BuildMixerPanelAnchors(plannedMain, plannedPanel, GetAudioState().panel.scale))
            snapshot.mixerDirection = osd_layout::MixerChevronDirection(
                plannedMain, plannedPanel, snapshot.vertical, false);
    }
    static bool routeLogged[2]{};
    static bool unavailableLogged[2]{};
    const int index = brightness ? 1 : 0;
    if (ShowXamlMirrored(snapshot)) {
        if (!routeLogged[index]) {
            Wh_Log(L"Fluent OSD/XAML: native %s -> XAML only",
                   brightness ? L"brightness" : L"volume");
            routeLogged[index] = true;
        }
        unavailableLogged[index] = false;
    } else if (!unavailableLogged[index]) {
        Wh_Log(L"Fluent OSD/XAML: XAML %s unavailable; NO GDI+ fallback",
               brightness ? L"brightness" : L"volume");
        unavailableLogged[index] = true;
    }
}


// Lock-key OSD is the first compact, noninteractive XAML status category.
// Retain the keyboard hook, localization, placement and duration engine.
void ShowMigratedXamlLockStatus() {
    PrepareXamlCategory();
    RECT target{};
    if (!osd_placement::CurrentAnchor(target)) {
        Wh_Log(L"Fluent OSD/XAML: lock status missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::LockStatus, target, DurationKind::LockKeys);
    snapshot.statusTitle = kLockDisplayNames[std::clamp(GetNoticeState().keys.last, 0, 3)];
    snapshot.statusGlyph = kLockGlyphs[std::clamp(GetNoticeState().keys.last, 0, 3)];
    snapshot.statusDetail = GetNoticeState().keys.lastValue
        ? Tr(OsdText::On) : Tr(OsdText::Off);
    snapshot.statusActive = GetNoticeState().keys.lastValue;
    if (!ShowXamlMirrored(snapshot))
        Wh_Log(L"Fluent OSD/XAML: lock status unavailable; NO GDI+ fallback");
}

// Entire USB/Bluetooth/network category: single-item notifications and
// aggregated, clickable device lists share the same XAML Island renderer.
// Event identity and debounce stay in the existing event engine; the
// XAML snapshot owns the names and uses installed Segoe Fluent Icons.
void ShowMigratedXamlDeviceNotice(DurationKind duration) {
    PrepareXamlCategory();
    RECT target{};
    if (!osd_placement::CurrentAnchor(target)) {
        Wh_Log(L"Fluent OSD/XAML: device notice missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::NoticeStatus, target, duration, true);
    snapshot.vertical = false; // Status notices are horizontal regardless of level settings.
    snapshot.statusTitle = GetNoticeState().notice.title;
    snapshot.statusDetail = GetNoticeState().notice.body;
    snapshot.noticeDetails = GetNoticeState().notice.details;
    snapshot.noticeDetailsHeading = Tr(OsdText::EventDetails);
    snapshot.noticeInteractiveDurationMs = OsdDuration(DurationKind::Interactive);
    snapshot.noticeGeneration = GetNoticeState().notice.generation;
    const PCWSTR glyph = osd_glyph::ForNotice(GetNoticeState().notice.icon);
    if (!glyph) return; // Unknown category: do not invent an icon.
    snapshot.statusGlyph = glyph;
    RECT detailsRect{};
    bool canPlace = false;
    if (GetNoticeState().notice.details.size() > 1) {
        MONITORINFO monitor{sizeof(monitor)};
        if (GetMonitorInfoW(MonitorFromRect(
                &target, MONITOR_DEFAULTTONEAREST), &monitor)) {
            const int width = target.right - target.left;
            const int height = target.bottom - target.top;
            const int preferredHeight = std::max(84, static_cast<int>(std::lround(
                (48.0 + std::min<size_t>(6, GetNoticeState().notice.details.size()) *
                 std::max(26.0, snapshot.fontSize * 1.8)) *
                std::max(0.5f, snapshot.scale))));
            const int panelHeight = std::clamp(preferredHeight, 64,
                std::max(64, static_cast<int>(
                    monitor.rcWork.bottom - monitor.rcWork.top - 16)));
            const FlyoutDirection direction = DirectionForPopup(
                target, monitor.rcWork, GetSettingsState()->position.load(), false);
            const auto offset = GetPanelAttachment(
                false, direction, snapshot.scale,
                width, height, width, panelHeight);
            const int x = ClampPopupAxis(
                target.left + offset.x, width, monitor.rcWork, true);
            const int y = ClampPopupAxis(
                target.top + offset.y, panelHeight, monitor.rcWork, false);
            detailsRect = RECT{x, y, x + width, y + panelHeight};
            snapshot.noticeDirection = osd_layout::MixerChevronDirection(
                target, detailsRect, false, GetNoticeState().notice.panelOpen);
            canPlace = true;
        }
    }
    if (GetNoticeState().notice.panelOpen && canPlace) {
        auto details = MakeXamlStatusSnapshot(
            xaml_osd::LevelKind::NoticeDetails, detailsRect,
            DurationKind::Interactive, false);
        details.vertical = false;
        details.noticeDetails = GetNoticeState().notice.details;
        details.noticeDetailsHeading = Tr(OsdText::EventDetails);
        if (!ShowXamlMirroredBatch({snapshot, details}))
            Wh_Log(L"Fluent OSD/XAML: notice-details pair unavailable");
    } else if (!ShowXamlMirrored(std::move(snapshot))) {
        Wh_Log(L"Fluent OSD/XAML: device notice unavailable");
    }
}

// A native system event already has one immutable display payload; use
// the existing XAML status card, not another GDI+ painter or Win32 hit HWND.
// Glyph identifiers are Microsoft Segoe Fluent Icons (Windows 11).
void ShowMigratedXamlNativeEvent() {
    PrepareXamlCategory();
    RECT target{};
    if (!osd_placement::CurrentAnchor(target)) {
        Wh_Log(L"Fluent OSD/XAML: native event missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::NativeEvent, target,
        DurationKind::NativeEvents, true);

    const NativeEventInfo& event = GetCoreState().presentation.nativeEventCurrent;
    const PCWSTR glyph = osd_glyph::ForNative(event.kind);
    if (!glyph) return;
    snapshot.statusGlyph = glyph;
    switch (event.kind) {
        case Kind::Keyboard:
            snapshot.statusTitle = Tr(OsdText::KeyboardBacklight);
            snapshot.statusDetail = event.value >= 0 && event.value <= 100
                ? std::to_wstring(event.value) + L"%"
                : std::wstring(Tr(OsdText::Level)) +
                  std::to_wstring(event.value);
            break;
        case Kind::Airplane:
            snapshot.statusTitle = Tr(OsdText::AirplaneMode);
            snapshot.statusDetail = event.value
                ? Tr(OsdText::Enabled) : Tr(OsdText::Disabled);
            break;
        case Kind::Camera: {
            const bool access = event.variant == 1;
            snapshot.statusTitle = access
                ? Tr(OsdText::CameraAccess) : Tr(OsdText::Camera);
            snapshot.statusDetail = access
                ? (event.value ? Tr(OsdText::Allowed) : Tr(OsdText::Blocked))
                : (event.value ? Tr(OsdText::Enabled) : Tr(OsdText::Disabled));
            break;
        }
        case Kind::Microphone:
            snapshot.statusTitle = Tr(OsdText::Microphone);
            // 0/1 are the only recognized states of this non-public event.
            snapshot.statusDetail = event.value == 0 ? Tr(OsdText::Unmuted)
                : event.value == 1 ? Tr(OsdText::Muted)
                : Tr(OsdText::StatusChanged);
            break;
        case Kind::Desktop:
            snapshot.statusTitle = Tr(OsdText::VirtualDesktop);
            snapshot.statusDetail = event.text.empty()
                ? Tr(OsdText::DesktopSwitched) : event.text;
            break;
        case Kind::Text:
            snapshot.statusTitle = Tr(OsdText::SystemNotice);
            snapshot.statusDetail = event.text.empty()
                ? Tr(OsdText::StatusChanged) : event.text;
            break;
        default:
            // Do not turn unknown payload kinds into invented status UI.
            return;
    }
    if (!ShowXamlMirrored(snapshot))
        Wh_Log(L"Fluent OSD/XAML: native event unavailable; NO GDI+ fallback");
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
    PrepareXamlCategory();
    RECT target{};
    if (!osd_placement::CurrentAnchor(target)) {
        ClearClipboardThumbnail();
        Wh_Log(L"Fluent OSD/XAML: clipboard notice missing placement anchor");
        return;
    }
    auto snapshot = MakeXamlStatusSnapshot(
        xaml_osd::LevelKind::NoticeStatus, target,
        DurationKind::Clipboard, true);
    snapshot.statusTitle = GetNoticeState().notice.title;
    snapshot.statusDetail = GetNoticeState().notice.body;
    snapshot.statusGlyph = osd_glyph::ForNotice(GetNoticeState().notice.icon);
    const bool image = CopyClipboardThumbnailPixels(
        GetNoticeState().notice.clipboardThumbnail, snapshot);
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
        if (!osd_placement::CurrentAnchor(snapshot.anchor)) return;
        snapshot.scale = GetAudioState().panel.scale;
    }
    if (!ShowXamlMirrored(snapshot))
        Wh_Log(L"Fluent OSD/XAML: clipboard notice unavailable; NO GDI+ fallback");
}


// Bounded one-time HICON conversion in the original UI thread; the Island
// receives copied pixels, never the native icon or a live device context.
std::vector<uint8_t> MixerIconPixels(HICON icon) {
    constexpr int side = 20;
    constexpr size_t bytes = side * side * 4;
    if (!icon) return {};
    HDC screen = GetDC(nullptr);
    if (!screen) return {};
    HDC dc = CreateCompatibleDC(screen);
    if (!dc) { ReleaseDC(nullptr, screen); return {}; }
    BITMAPINFO info{};
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = side;
    info.bmiHeader.biHeight = -side;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    void* pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(screen, &info, DIB_RGB_COLORS,
                                     &pixels, nullptr, 0);
    std::vector<uint8_t> result;
    if (bitmap && pixels) {
        const HGDIOBJ previous = SelectObject(dc, bitmap);
        memset(pixels, 0, bytes);
        if (DrawIconEx(dc, 0, 0, icon, side, side, 0, nullptr, DI_NORMAL)) {
            const auto* data = static_cast<const uint8_t*>(pixels);
            // If a legacy masked icon lacks valid alpha, use the Fluent
            // fallback rather than an opaque black tile.
            for (size_t i = 3; i < bytes; i += 4) {
                if (data[i]) {
                    result.assign(data, data + bytes);
                    break;
                }
            }
        }
        if (previous && previous != HGDI_ERROR)
            SelectObject(dc, previous);
    }
    if (bitmap) DeleteObject(bitmap);
    DeleteDC(dc);
    ReleaseDC(nullptr, screen);
    return result;
}

// Build an owned Mixer display model from Core Audio UI-thread values.
osd_model::MixerModel BuildMixerModel() {
    osd_model::MixerModel model;
    model.title = Tr(OsdText::VolumeMixer);
    model.outputHeading = Tr(OsdText::AudioOutput);
    model.outputError = Tr(OsdText::AudioSwitchFailed);
    model.generation = GetAudioState().panel.mixerGeneration;
    model.outputExpanded = GetAudioState().panel.mixerOutputExpanded;
    model.outputFailed = GetAudioState().mixer.outputSwitchFailed;
    model.maxVisibleRows = std::clamp(GetSettingsState()->mixerMaxRows.load(), 3, 16);
    model.selectedOutput = Tr(OsdText::NoAudioOutputs);
    for (const auto& item : GetAudioState().mixer.outputOptions) {
        const bool selected = item.id == GetAudioState().mixer.outputId;
        model.outputs.push_back({item.name, selected, item.id});
        if (selected) model.selectedOutput = item.name;
    }
    model.rows.push_back({
        Tr(OsdText::MasterVolume),
        std::clamp(static_cast<int>(
            std::lround(GetAudioState().mixer.masterLevel * 100.0f)), 0, 100),
        GetAudioState().mixer.masterMuted, static_cast<bool>(GetAudioState().mixer.master)});
    // Master volume is tied to its output endpoint, not an app session.
    if (!GetAudioState().mixer.outputId.empty())
        model.rows.back().sessionId = L"@master:" + GetAudioState().mixer.outputId;
    for (const auto& item : GetAudioState().mixer.entries) {
        if (model.rows.size() >= 129) break;
        osd_model::MixerRow row;
        row.title = item.title;
        row.percent = std::clamp(static_cast<int>(
            std::lround(item.scalar * 100.0f)), 0, 100);
        row.muted = item.muted;
        row.enabled = item.volume.Get() != nullptr;
        row.iconPixels = item.iconPixels;
        row.sessionId = item.sessionId;
        model.rows.push_back(std::move(row));
    }
    return model;
}

osd_model::MediaModel BuildXamlMediaModel() {
    osd_model::MediaModel m;
    m.generation=GetAudioState().panel.mediaGeneration;
    m.sessionCount=GetAudioState().media.current.sessionCount;
    m.selectionSerial=GetAudioState().media.current.selectionSerial;
    m.sourceId=GetAudioState().media.current.sourceId;
    m.title=GetAudioState().media.current.title.empty()?
        Tr(OsdText::MediaPlayback):GetAudioState().media.current.title;
    m.artist=GetAudioState().media.current.artist;
    if (GetSettingsState()->showMediaArtwork.load())
        m.encodedArtwork.assign(GetAudioState().media.current.artwork.begin(),
                                GetAudioState().media.current.artwork.end());
    m.playing=GetAudioState().media.current.playing;
    m.canPrevious=GetAudioState().media.current.canPrevious;
    m.canToggle=GetAudioState().media.current.canToggle;
    m.canNext=GetAudioState().media.current.canNext;
    m.canShuffle=GetAudioState().media.current.canShuffle;
    m.shuffleKnown=GetAudioState().media.current.shuffleKnown;
    m.shuffleActive=GetAudioState().media.current.shuffleActive;
    m.canRepeat=GetAudioState().media.current.canRepeat;
    m.repeatMode=GetAudioState().media.current.repeatMode;
    m.hasTimeline=GetAudioState().media.current.hasTimeline;
    m.canSeek=GetAudioState().media.current.canSeek;
    m.start=GetAudioState().media.current.timelineStart;
    m.end=GetAudioState().media.current.timelineEnd;
    m.position=GetAudioState().media.current.timelinePosition;
    m.observedTick=GetAudioState().media.current.timelineObservedTick;
    m.controlSizePercent=GetSettingsState()->mediaControlSizePercent.load();
    m.squareButtons=GetSettingsState()->controlButtonSquare.load();
    m.buttonCornerRadius=GetSettingsState()->controlButtonCornerRadius.load();
    if (!GetSettingsState()->showMediaControls.load()) {
        m.canPrevious=m.canToggle=m.canNext=false;
        m.canShuffle=m.canRepeat=false;
    }
    return m;
}
// Controller-owned monitor and panel geometry; no renderer HWND lookup.
bool BuildAttachedPanelAnchors(
        RECT& main, RECT& panel, float scale, bool isMedia) {
    if (!osd_placement::CurrentAnchor(main)) return false;
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(MonitorFromRect(&main,
            MONITOR_DEFAULTTONEAREST), &mi)) return false;
    const bool vertical = GetSettingsState()->verticalVolumeBrightness.load();
    const int mw = main.right - main.left, mh = main.bottom - main.top;
    const int pw = vertical ? static_cast<int>(std::lround(
        (isMedia?GetSettingsState()->verticalSmtcWidth.load():
                 GetSettingsState()->verticalMixerWidth.load())*scale)) : mw;
    const int ph = vertical ? mh : static_cast<int>(std::lround(
        (isMedia?GetSettingsState()->horizontalSmtcHeight.load():
                 GetSettingsState()->horizontalMixerHeight.load())*scale));
    const int position = GetSettingsState()->position.load();
    const auto direction = DirectionForPopup(main, mi.rcWork,
                                             position, vertical);
    auto attachment = GetPanelAttachment(vertical, direction, scale,
                                         mw, mh, pw, ph);
    if (vertical) {
        // GetPanelAttachment assumes the 4px legacy panel inset;
        // both XAML cards now have a 7px side inset.
        const int delta = static_cast<int>(std::lround(3.0f * scale));
        attachment.x += direction == FlyoutDirection::Left ? delta : -delta;
    }
    // Center the composition as one unit on the relevant central axis,
    // preserving the same attachment offset as the original panel.
    if (vertical && PositionCentersX(position)) {
        const int minX = std::min(0, attachment.x);
        const int maxX = std::max(mw, attachment.x + pw);
        const int shift = (mw - minX - maxX) / 2;
        main.left += shift;
        main.right += shift;
    } else if (!vertical && PositionCentersY(position)) {
        const int minY = std::min(0, attachment.y);
        const int maxY = std::max(mh, attachment.y + ph);
        const int shift = (mh - minY - maxY) / 2;
        main.top += shift;
        main.bottom += shift;
    }
    int px = main.left + attachment.x;
    int py = main.top + attachment.y;
    px = ClampPopupAxis(px, pw,
        !vertical && PositionCentersX(position)
            ? mi.rcMonitor : mi.rcWork, true);
    py = ClampPopupAxis(py, ph,
        vertical && PositionCentersY(position)
            ? mi.rcMonitor : mi.rcWork, false);
    panel = RECT{px, py, px + pw, py + ph};
    return true;
}

bool BuildMixerPanelAnchors(RECT& main, RECT& panel, float scale) {
    return BuildAttachedPanelAnchors(main, panel, scale, false);
}
bool BuildMediaPanelAnchors(RECT& main, RECT& panel, float scale) {
    return BuildAttachedPanelAnchors(main, panel, scale, true);
}
bool ShowXamlMediaPanel(bool passiveRefresh) {
    if (GetAudioState().panel.mixerOpen ||
        !GetSettingsState()->showSmtcOnVolume.load() ||
        !GetAudioState().media.current.available)
        return false;
    RECT main{}, panel{};
    if (!BuildMediaPanelAnchors(main, panel, GetAudioState().panel.scale))
        return false;
    PrepareXamlCategory();
    auto volume = MakeXamlSnapshot(
        PopupKind::NativeVolume, main, GetAudioState().panel.scale);
    volume.durationMs = OsdDuration(DurationKind::Media);
    volume.passiveRefresh = passiveRefresh;
    if (volume.mixerChevron) {
        RECT pairedMain{}, pairedPanel{};
        if (BuildMixerPanelAnchors(pairedMain, pairedPanel, GetAudioState().panel.scale))
            volume.mixerDirection = osd_layout::MixerChevronDirection(
                pairedMain, pairedPanel, volume.vertical, false);
    }
    auto media = MakeXamlSnapshot(
        PopupKind::NativeVolume, panel, GetAudioState().panel.scale);
    media.kind = osd_model::Kind::Media;
    media.mixerChevron = false;
    media.durationMs = OsdDuration(DurationKind::Media);
    media.passiveRefresh = passiveRefresh;
    media.media = BuildXamlMediaModel();
    if (!ShowXamlMirroredBatch({volume, media})) {
        Wh_Log(L"XAML SMTC: panel unavailable");
        ResetXamlMediaController();
        return false;
    }
    GetAudioState().panel.mediaOpen = true;
    if (GetCoreState().module.receiveWnd)
        SetTimer(GetCoreState().module.receiveWnd, kMediaAnimationTimer,
                 kMediaAnimationIntervalMs, nullptr);
    return true;
}
void ShowXamlMixerPanel() {
    if (!GetAudioState().panel.mixerOpen) return;
    RECT main{}, panel{};
    if (!BuildMixerPanelAnchors(main, panel, GetAudioState().panel.scale)) {
        Wh_Log(L"XAML Mixer: missing calculated placement");
        ResetXamlMixerController();
        return;
    }
    PrepareXamlCategory();
    auto volume = MakeXamlSnapshot(
        PopupKind::NativeVolume, main, GetAudioState().panel.scale);
    volume.mixerChevron = GetSettingsState()->showMixerArrow.load();
    volume.mixerDirection = osd_layout::MixerChevronDirection(
        main, panel, volume.vertical, true);
    volume.durationMs = OsdDuration(DurationKind::Interactive);
    auto mixer = MakeXamlSnapshot(
        PopupKind::NativeVolume, panel, GetAudioState().panel.scale);
    mixer.kind = osd_model::Kind::Mixer;
    mixer.anchor = panel;
    mixer.durationMs = OsdDuration(DurationKind::Interactive);
    mixer.mixerChevron = false;
    mixer.mixer = BuildMixerModel();
    if (!ShowXamlMirroredBatch({volume, mixer})) {
        Wh_Log(L"XAML Mixer: panel unavailable");
        ResetXamlMixerController();
    }
}

void ShowNativeVolumePopup() {
    BrightnessEvent event{};
    MovePopupToDisplay(event);
    if (GetSettingsState()->showSmtcOnVolume.load() && !GetAudioState().panel.mixerOpen) RequestMedia();
    if (GetAudioState().panel.mixerOpen) ShowXamlMixerPanel();
    else ShowMigratedXamlLevel(PopupKind::NativeVolume);
}

// Imperative control boundary: returns refresh intents instead of drawing.
// Every hardware target keeps its existing identity and async write behavior.
struct ControlEffects {
    bool volume = false, nativeBrightness = false;
    bool mixer = false, notice = false;
    std::vector<BrightnessEvent> changedDdcTargets;
    void RecordDdc(const BrightnessEvent& event) {
        auto existing = std::find_if(changedDdcTargets.begin(),
            changedDdcTargets.end(), [&](const BrightnessEvent& prev) {
                return prev.physicalIndex == event.physicalIndex &&
                    _wcsicmp(prev.device, event.device) == 0;
            });
        if (existing != changedDdcTargets.end()) *existing = event;
        else if (changedDdcTargets.size() < kMaxDdcTargets)
            changedDdcTargets.push_back(event);
    }
};
ControlEffects ApplyOsdCommands(
        const std::vector<osd_control::Command>& commands) {
    ControlEffects effects;
    if (GetCoreState().module.closing.load()) return effects;
    for (const auto& cmd : commands) {
        if (cmd.target == osd_control::Target::Notice) {
            if (cmd.action == osd_control::Action::ToggleNoticeDetails &&
                GetCoreState().presentation.popupKind == PopupKind::Notification &&
                GetNoticeState().notice.icon != NoticeIcon::Clipboard &&
                GetNoticeState().notice.icon != NoticeIcon::ClipboardFile &&
                GetNoticeState().notice.icon != NoticeIcon::ClipboardText &&
                GetNoticeState().notice.details.size() > 1 &&
                cmd.generation == GetNoticeState().notice.generation) {
                GetNoticeState().notice.panelOpen = !GetNoticeState().notice.panelOpen;
                effects.notice = true;
            }
            continue;
        }
        if (cmd.target==osd_control::Target::Media) {
            if (!GetAudioState().panel.mediaOpen||
               cmd.generation!=GetAudioState().panel.mediaGeneration) continue;
            if (cmd.action==osd_control::Action::CloseMedia) {
                ResetXamlMediaController();
                continue;
            }
            if (cmd.index!=static_cast<int>(
                    GetAudioState().media.current.selectionSerial)) continue;
            if (cmd.action==osd_control::Action::MediaAction) {
                if (cmd.value>=1&&cmd.value<=7&&cmd.value!=4)
                    RequestMedia(cmd.value);
            } else if (cmd.action==osd_control::Action::MediaSeek&&
                      GetAudioState().media.current.canSeek&&GetAudioState().media.current.hasTimeline&&
                      GetAudioState().media.current.timelineEnd>GetAudioState().media.current.timelineStart) {
                RequestMedia(4,std::clamp(cmd.mediaPosition,
                    GetAudioState().media.current.timelineStart,
                    GetAudioState().media.current.timelineEnd));
            }
            continue;
        }
        if (cmd.target == osd_control::Target::Mixer) {
            if (cmd.action == osd_control::Action::OpenMixer) {
                if (GetAudioState().panel.mixerOpen) {
                    ResetXamlMixerController();
                } else if (GetSettingsState()->showMixerArrow.load() &&
                           GetCoreState().presentation.popupKind == PopupKind::NativeVolume) {
                    ResetXamlMediaController();
                    
                    GetAudioState().panel.mixerOutputExpanded = false;
                    RefreshMixer();
                    StartMixerOutputNotifications();
                    GetAudioState().panel.mixerOpen = true;
                }
                effects.mixer = true;
                continue;
            }
            if (cmd.action == osd_control::Action::CloseMixer) {
                if (GetAudioState().panel.mixerOpen &&
                    cmd.generation == GetAudioState().panel.mixerGeneration) {
                    ResetXamlMixerController();
                    effects.mixer = true;
                }
                continue;
            }
            if (!GetAudioState().panel.mixerOpen ||
                cmd.generation != GetAudioState().panel.mixerGeneration) continue;
            if ((cmd.action == osd_control::Action::MixerSetPercent ||
                 cmd.action == osd_control::Action::MixerToggleMute) &&
                !MixerCommandMatchesCurrentRow(cmd)) continue;
            switch (cmd.action) {
                case osd_control::Action::MixerSetPercent:
                    (void)SetMixerPercent(cmd.index, cmd.value);
                    // Never rebuild controls mid-drag: Slider keeps capture.
                    break;
                case osd_control::Action::MixerToggleMute:
                    ToggleMixerMute(cmd.index);
                    effects.mixer = true;
                    break;
                case osd_control::Action::MixerToggleOutput:
                    if (!GetAudioState().panel.mixerOutputExpanded) {
                        RefreshMixer(); // Reconcile current endpoints.
                        GetAudioState().panel.mixerOutputExpanded =
                            !GetAudioState().mixer.outputOptions.empty();
                    } else {
                        GetAudioState().panel.mixerOutputExpanded = false;
                    }
                    effects.mixer = true;
                    break;
                case osd_control::Action::MixerSelectOutput:
                    if (cmd.index >= 0 &&
                        cmd.index < static_cast<int>(
                            GetAudioState().mixer.outputOptions.size())) {
                        SelectMixerOutput(cmd.index);
                        GetAudioState().panel.mixerOutputExpanded = false;
                        effects.mixer = true;
                    }
                    break;
                default: break;
            }
            continue;
        }
        if (cmd.target == osd_control::Target::Volume) {
            if (GetCoreState().presentation.popupKind != PopupKind::NativeVolume) continue;
            bool ok = false;
            if (cmd.action == osd_control::Action::ToggleMute)
                ok = ToggleDefaultAudioMute();
            else if (cmd.action == osd_control::Action::Wheel) {
                const int steps = cmd.value / WHEEL_DELTA;
                ok = steps != 0 && AdjustDefaultAudioWheel(steps);
            } else ok = SetDefaultAudioBarPercent(cmd.value);
            if (ok) effects.volume = true;
            continue;
        }
        if (!GetBrightnessState().writer.ReadyForCommands()) continue;

        if (cmd.target == osd_control::Target::NativeBrightness) {
            if (GetCoreState().presentation.popupKind != PopupKind::NativeBrightness ||
                !GetCoreState().presentation.nativePercentKnown) continue;
            if (cmd.action == osd_control::Action::ToggleMute) continue;
            const int requested = cmd.action == osd_control::Action::Wheel
                ? GetCoreState().presentation.nativePercent + (cmd.value / WHEEL_DELTA) * kWheelStepPercent
                : cmd.value;
            const int percent = std::clamp(requested, 0, 100);
            if (percent == GetCoreState().presentation.nativePercent) continue;
            BrightnessWheelTask task{};
            task.native = true;
            task.value = percent;
            task.generation = ++GetBrightnessState().writer.generation;
            if (GetBrightnessState().ddc.lastConfirmedNative < 0)
                GetBrightnessState().ddc.lastConfirmedNative = GetCoreState().presentation.nativePercent;
            GetCoreState().presentation.nativePercent = percent;
            QueueBrightnessWheelTask(task);
            effects.nativeBrightness = true;
            continue;
        }

        if (cmd.target != osd_control::Target::DdcBrightness ||
            GetCoreState().presentation.popupKind != PopupKind::DdcBrightness ||
            cmd.action == osd_control::Action::ToggleMute) continue;
        const auto selected = std::find_if(
            GetBrightnessState().ddc.targets.begin(), GetBrightnessState().ddc.targets.end(),
            [&](const DdcTargetState& target) {
                return target.event.physicalIndex == cmd.physicalIndex &&
                    _wcsicmp(target.event.device, cmd.device) == 0;
            });
        if (selected == GetBrightnessState().ddc.targets.end()) continue;
        auto& event = selected->event;
        if (event.maximum <= event.minimum) continue; // Unknown range.
        // Keep the actively edited physical target in the XAML batch.
        selected->expiresAt = GetTickCount64() +
            OsdDuration(DurationKind::DdcBrightness);
        int percent = 0;
        if (cmd.action == osd_control::Action::Wheel) {
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
        task.generation = ++GetBrightnessState().writer.generation;
        GetBrightnessState().ddc.RememberPendingWriteOnControllerThread(event, task.generation);
        event.value = raw;
        if (GetCoreState().presentation.visible.physicalIndex == event.physicalIndex &&
            _wcsicmp(GetCoreState().presentation.visible.device, event.device) == 0)
            GetCoreState().presentation.visible.value = raw;
        QueueBrightnessWheelTask(task);
        effects.RecordDdc(event);
    }
    return effects;
}

// Match the established upstream taskbar input discovery hierarchy.
// A Bridge alone may exist before InputSite has been created.
constexpr WCHAR kShellBridgeClass[] =
    L"Windows.UI.Composition.DesktopWindowContentBridge";
constexpr WCHAR kShellInputSiteClass[] =
    L"Windows.UI.Input.InputSite.WindowClass";

// Used by both the initial snapshot and event-delivered controller check.
// Reject Explorer file-window processes which do not own Shell_TrayWnd.
bool IsShellInputSiteReady() {
    HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!taskbar) return false;
    DWORD taskbarPid = 0;
    DWORD taskbarThread = GetWindowThreadProcessId(taskbar, &taskbarPid);
    if (!taskbarThread || taskbarPid != GetCurrentProcessId()) return false;
    HWND bridge = FindWindowExW(taskbar, nullptr, kShellBridgeClass, nullptr);
    if (!bridge) return false;
    HWND site = FindWindowExW(bridge, nullptr, kShellInputSiteClass, nullptr);
    if (!site || GetParent(site) != bridge || GetParent(bridge) != taskbar)
        return false;
    DWORD sitePid = 0;
    return GetWindowThreadProcessId(site, &sitePid) == taskbarThread &&
           sitePid == taskbarPid;
}

void TryStartXamlAfterShellInputSite(HWND receiver) {
    if (!receiver || GetCoreState().module.closing.load(std::memory_order_acquire) ||
        GetCoreState().module.shellXamlStarted || !IsShellInputSiteReady()) return;
    GetCoreState().module.shellXamlStarted = true;
    Wh_Log(L"Fluent OSD: Shell InputSite hierarchy ready; starting XAML");
    xaml_osd::Start(receiver);
}

// Same creation export observed by upstream Taskbar Volume Control and
// Taskbar Scroll Actions. Run the original first. Only notify the controller
// asynchronously, never initialize XAML within the Shell creation stack.

HWND WINAPI ShellCreateWindowInBandHook(
        DWORD exStyle, LPCWSTR className, LPCWSTR title, DWORD style,
        int x, int y, int width, int height, HWND parent, HMENU menu,
        HINSTANCE instance, LPVOID param, DWORD band) {
    HWND created = GetCoreState().module.createWindowInBandOriginal(
        exStyle, className, title, style, x, y, width, height,
        parent, menu, instance, param, band);
    if (!created || GetCoreState().module.closing.load(std::memory_order_acquire))
        return created;
    // lpClassName may contain a 16-bit ATOM. Do not dereference an ATOM.
    if ((reinterpret_cast<ULONG_PTR>(className) &
         ~static_cast<ULONG_PTR>(0xffff)) == 0 ||
        _wcsicmp(className, kShellInputSiteClass) != 0)
        return created;

    // If the controller does not yet exist, its one-time snapshot after
    // window creation covers this early event. The receiver is published
    // atomically for callbacks, not read from controller-thread state.
    const HWND receiver = GetCoreState().module.ReceiverForCallbacks();
    if (receiver)
        (void)PostMessageW(receiver, kShellInputSiteReadyMessage, 0, 0);
    return created;
}

void HookShellInputSiteCreation() {
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (!user32) {
        Wh_Log(L"Fluent OSD: user32 unavailable; InputSite hook not installed");
        return;
    }
    auto target = reinterpret_cast<CreateWindowInBand_t>(
        GetProcAddress(user32, "CreateWindowInBand"));
    if (!target) {
        Wh_Log(L"Fluent OSD: CreateWindowInBand unavailable; "
               L"existing-InputSite snapshot only");
        return;
    }
    WindhawkUtils::SetFunctionHook(
        target, ShellCreateWindowInBandHook,
        &GetCoreState().module.createWindowInBandOriginal);
    Wh_Log(L"Fluent OSD: InputSite creation hook configured");
}

// The native notification is independent of XAML. A temporary tray icon
// remains discoverable for manual retry if the balloon disappears.
NOTIFYICONDATAW XamlFailureTrayData(HWND hwnd) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = kXamlFailureTrayId;
    return nid;
}
void ClearXamlFailureNotice(HWND hwnd) {
    if (!GetCoreState().module.xamlFailureTrayVisible || !hwnd) return;
    auto nid = XamlFailureTrayData(hwnd);
    (void)Shell_NotifyIconW(NIM_DELETE, &nid);
    GetCoreState().module.xamlFailureTrayVisible = false;
}
void ShowXamlFailureNotice(HWND hwnd) {
    if (!hwnd || GetCoreState().module.closing.load() || !xaml_osd::IsFailed())
        return;
    auto nid = XamlFailureTrayData(hwnd);
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
    nid.uCallbackMessage = kXamlFailureTrayCallback;
    nid.hIcon = LoadIconW(nullptr, IDI_WARNING); // Shared system icon.
    wcscpy_s(nid.szTip, Tr(OsdText::XamlRendererFailed));
    wcscpy_s(nid.szInfoTitle, L"Fluent OSD");
    wcscpy_s(nid.szInfo, Tr(OsdText::XamlRetryHint));
    nid.dwInfoFlags = NIIF_WARNING;
    const bool existing = GetCoreState().module.xamlFailureTrayVisible;
    if (!Shell_NotifyIconW(existing ? NIM_MODIFY : NIM_ADD, &nid)) {
        Wh_Log(L"Fluent OSD/XAML: native failure notification unavailable (%lu)",
               GetLastError());
        return;
    }
    if (!existing) {
        GetCoreState().module.xamlFailureTrayVisible = true;
        nid.uVersion = NOTIFYICON_VERSION_4;
        (void)Shell_NotifyIconW(NIM_SETVERSION, &nid);
    }
}
LRESULT CALLBACK UiWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (hwnd == GetCoreState().module.receiveWnd &&
        msg == xaml_osd::kRendererFailedMessage) {
        ShowXamlFailureNotice(hwnd);
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd &&
        msg == xaml_osd::kRendererReadyMessage) {
        if (xaml_osd::IsReady()) ClearXamlFailureNotice(hwnd);
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd &&
        msg == kXamlFailureTrayCallback) {
        const UINT event = LOWORD(static_cast<DWORD>(lp));
        if (GetCoreState().module.xamlFailureTrayVisible &&
            !GetCoreState().module.closing.load() &&
            (event == NIN_BALLOONUSERCLICK ||
             event == NIN_SELECT || event == NIN_KEYSELECT))
            (void)xaml_osd::Restart(hwnd);
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == kShellInputSiteReadyMessage) {
        TryStartXamlAfterShellInputSite(hwnd);
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == osd_control::kMessage) {
        const auto commands = osd_control::Drain();
        // Event routing owns the active-backend policy; hardware execution
        // does not read an XAML feature flag or depend on renderer types.
        {
            const auto effects = ApplyOsdCommands(commands);
            if (effects.mixer ||
                (effects.volume && GetAudioState().panel.mixerOpen)) {
                if (GetAudioState().panel.mixerOpen) ShowXamlMixerPanel();
                else ShowMigratedXamlLevel(PopupKind::NativeVolume);
            } else if (effects.volume) {
                ShowMigratedXamlLevel(PopupKind::NativeVolume);
            }
            if (effects.nativeBrightness)
                ShowMigratedXamlLevel(PopupKind::NativeBrightness);
            if (!effects.changedDdcTargets.empty())
                (void)ShowXamlDdcTargets(
                    effects.changedDdcTargets.back(), &effects.changedDdcTargets);
            if (effects.notice)
                ShowMigratedXamlDeviceNotice(GetNoticeState().notice.duration);
        }
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == WM_TIMER && wp == kEventBatchTimer) {
        FlushNoticeBatch();
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == WM_TIMER && wp == kDdcBatchTimer) {
        KillTimer(hwnd, kDdcBatchTimer);
        DisplayDdcBatch();
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == WM_TIMER &&
        wp == kMediaAnimationTimer) {
        if (!GetAudioState().panel.mediaOpen || !xaml_osd::IsPrimaryVisible()) {
            KillTimer(hwnd, kMediaAnimationTimer);
            return 0;
        }
        const uint64_t now = GetTickCount64();
        if (now - GetAudioState().media.lastRefreshTick >= kMediaRefreshIntervalMs) {
            GetAudioState().media.lastRefreshTick = now;
            RequestMedia();
        }
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == WM_CLIPBOARDUPDATE) {
        ProcessClipboard();
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == WM_DEVICECHANGE) {
        if (HandleDeviceChange(wp, lp)) return TRUE;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == kBluetoothQueueMessage) {
        bt_monitor::Drain();
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == kBluetoothConfigMessage) {
        if (GetSettingsState()->showBluetoothEvents.load()) bt_monitor::Start();
        else bt_monitor::Stop();
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == kNetworkNoticeMessage) {
        if (!GetSettingsState()->showNetworkEvents.load()) return 0;
        if (!GetConnectivityState().network.refreshPending) {
            GetConnectivityState().network.ResetRefresh();
            GetConnectivityState().network.refreshPending = true;
        }
        if (wp == 1) {
            GetConnectivityState().network.hintPending = true;
            GetConnectivityState().network.hintLevel = static_cast<int>(lp);
        }
        GetConnectivityState().network.refreshSecondPass = false;
        if (!SetTimer(hwnd, kNetworkRefreshTimer, kNetworkDebounceMs, nullptr)) {
            Wh_Log(L"Fluent OSD/network: debounce timer unavailable (%lu)",
                   GetLastError());
            GetConnectivityState().network.sawInterfaceTransition |= CaptureNetworkEvents();
            FinishNetworkRefresh();
        }
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == WM_TIMER &&
        wp == kNetworkRefreshTimer) {
        KillTimer(hwnd, kNetworkRefreshTimer);
        if (!GetSettingsState()->showNetworkEvents.load()) {
            GetConnectivityState().network.ResetRefresh();
            return 0;
        }
        GetConnectivityState().network.sawInterfaceTransition |= CaptureNetworkEvents();
        if (!GetConnectivityState().network.refreshSecondPass) {
            GetConnectivityState().network.refreshSecondPass = true;
            if (SetTimer(hwnd, kNetworkRefreshTimer, kNetworkSettleMs, nullptr))
                return 0;
        }
        FinishNetworkRefresh();
        return 0;
    }
    if (hwnd == GetCoreState().module.receiveWnd && msg == kNetworkConfigMessage) {
        const bool enabled = GetSettingsState()->showNetworkEvents.load();
        if (enabled && !GetConnectivityState().network.uiSettingEnabled)
            InitNetworkEvents();
        if (!enabled) {
            KillTimer(hwnd, kNetworkRefreshTimer);
            GetConnectivityState().network.ResetRefresh();
            if (GetConnectivityState().network.uiSettingEnabled) {
                if (GetConnectivityState().network.CancelCallbacksOnControllerThread())
                    GetConnectivityState().network.ReleaseLibraryOnControllerThread();
            }
        }
        GetConnectivityState().network.uiSettingEnabled = enabled;
        return 0;
    }
    if (msg == kNativeExtraMessage && hwnd == GetCoreState().module.receiveWnd) {
        NativeEventInfo received = GetNativeEventState().mailbox.Take();
        if (!ShowCustomNative(received.kind)) return 0;
        
        GetCoreState().presentation.nativeEventCurrent = std::move(received);
        GetCoreState().presentation.popupKind = PopupKind::NativeEvent;
        BrightnessEvent ev{};
        MovePopupToDisplay(ev);
        ShowMigratedXamlNativeEvent();
        return 0;
    }
    if (msg == kNativeOsdMessage && hwnd == GetCoreState().module.receiveWnd) {
        const Kind kind = static_cast<Kind>(wp);
        if (kind != Kind::Volume && kind != Kind::Brightness)
            return 0;
        if (!ShowCustomNative(kind)) return 0;
        GetCoreState().presentation.popupKind = kind == Kind::Volume ?
            PopupKind::NativeVolume : PopupKind::NativeBrightness;
        GetCoreState().presentation.nativePercent = static_cast<int>(lp);
        if (kind == Kind::Brightness)
            GetBrightnessState().ddc.lastConfirmedNative = GetCoreState().presentation.nativePercent;
        GetCoreState().presentation.nativePercentKnown = GetCoreState().presentation.nativePercent >= 0 && GetCoreState().presentation.nativePercent <= 100;
        GetCoreState().presentation.nativeMuted = false;
        if (kind == Kind::Volume) {
            int actual = 0;
            bool mute = false;
            if (ReadDefaultAudioVolume(actual, mute)) {
                GetCoreState().presentation.nativePercent = actual;
                GetCoreState().presentation.nativePercentKnown = true;
                GetCoreState().presentation.nativeMuted = mute;
            }
            ShowNativeVolumePopup();
        } else {
            BrightnessEvent ev{};
            MovePopupToDisplay(ev);
            ShowMigratedXamlLevel(PopupKind::NativeBrightness);
        }
        return 0;
    }
    if (msg == kAudioRefreshMessage && hwnd == GetCoreState().module.receiveWnd) {
        if (GetAudioState().mixer.notify) GetAudioState().mixer.notify->ClearPending();
        if (GetAudioState().panel.mixerOpen && !GetCoreState().module.closing.load()) {
            RefreshMixer();
            ShowXamlMixerPanel();
        }
        return 0;
    }
    if (msg == kMediaUpdateMessage && hwnd == GetCoreState().module.receiveWnd) {
        GetAudioState().media.ConsumeOnControllerThread();
        if (GetCoreState().presentation.popupKind == PopupKind::NativeVolume &&
            !GetAudioState().panel.mixerOpen && xaml_osd::IsPrimaryVisible()) {
            if (GetAudioState().media.current.available&&GetSettingsState()->showSmtcOnVolume.load())
                (void)ShowXamlMediaPanel(true);
            else {
                ResetXamlMediaController();
                ShowMigratedXamlLevel(PopupKind::NativeVolume);
            }
        }
        return 0;
    }
    if (msg == kLockToggleMessage && hwnd == GetCoreState().module.receiveWnd) {
        int index = static_cast<int>(wp);
        if (index < 0 || index >= 4 || !GetSettingsState()->showLockKeys[index].load()) return 0;
        
        GetNoticeState().keys.last = index;
        GetNoticeState().keys.lastValue = lp != 0;
        GetCoreState().presentation.popupKind = PopupKind::LockStatus;
        BrightnessEvent ev{};
        MovePopupToDisplay(ev);
        ShowMigratedXamlLockStatus();
        return 0;
    }
    if (msg == kBrightnessWheelResultMessage && hwnd == GetCoreState().module.receiveWnd) {
        const DWORD generation = static_cast<DWORD>(wp);
        const bool success = (lp & 1) != 0;
        const bool native = (lp & 2) != 0;
        if (!native) {
            DdcRuntimeState::PendingWrite write{};
            if (!GetBrightnessState().ddc.TakePendingWriteOnControllerThread(generation, write))
                return 0; // Superseded DDC write: never roll back its target.
            const auto target = std::find_if(
                GetBrightnessState().ddc.targets.begin(), GetBrightnessState().ddc.targets.end(),
                [&](const DdcTargetState& item) {
                    return item.event.physicalIndex ==
                            write.event.physicalIndex &&
                        _wcsicmp(item.event.device,
                                write.event.device) == 0;
                });
            const bool master = GetCoreState().presentation.visible.physicalIndex ==
                    write.event.physicalIndex &&
                _wcsicmp(GetCoreState().presentation.visible.device, write.event.device) == 0;
            if (!success) {
                if (target != GetBrightnessState().ddc.targets.end())
                    target->event.value = write.previousValue;
                if (master) GetCoreState().presentation.visible.value = write.previousValue;
                Wh_Log(L"Fluent OSD/XAML: DDC write failed for '%s' index %lu",
                    write.event.device, write.event.physicalIndex);
                if (GetCoreState().presentation.popupKind == PopupKind::DdcBrightness &&
                    target != GetBrightnessState().ddc.targets.end())
                    (void)ShowXamlDdcTargets(target->event);
            } else if (master && target != GetBrightnessState().ddc.targets.end()) {
                GetBrightnessState().ddc.lastConfirmedDdc = target->event.value;
            }
            return 0;
        }
        if (generation != GetBrightnessState().writer.generation) return 0;
        if (native) {
            if (success) GetBrightnessState().ddc.lastConfirmedNative = GetCoreState().presentation.nativePercent;
            else if (GetBrightnessState().ddc.lastConfirmedNative >= 0) {
                GetCoreState().presentation.nativePercent = GetBrightnessState().ddc.lastConfirmedNative;
                if (GetCoreState().presentation.popupKind == PopupKind::NativeBrightness)
                    ShowMigratedXamlLevel(PopupKind::NativeBrightness);
                Wh_Log(L"Native brightness wheel write failed; restored value");
            }
        }
        return 0;
    }
    if (msg == WM_COPYDATA && hwnd == GetCoreState().module.receiveWnd) {
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
        if (!terminator || GetCoreState().module.closing.load()) return FALSE;
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
        if (!GetSettingsState()->showDdcBrightness.load()) return TRUE;
        // Coalesce by GDI display + physical index, retaining last-write order.
        const bool firstInBatch = GetBrightnessState().ddc.AccumulateOnControllerThread(ev);
        if (firstInBatch &&
            !SetTimer(GetCoreState().module.receiveWnd, kDdcBatchTimer, kDdcBatchDelayMs, nullptr))
            DisplayDdcBatch(); // Timer allocation failure must not lose updates.
        return TRUE;
    }
    if (msg == WM_ERASEBKGND) return TRUE;
    return DefWindowProcW(hwnd, msg, wp, lp);
}

DWORD WINAPI UiThreadProc(void*) {
    // Message-only controller and event dispatcher. Every visible card is
    // owned by the native XAML STA, never by this worker thread.
    const HRESULT apartment = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    const bool initialized = SUCCEEDED(apartment);
    InitWindowsAccentProvider();
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = UiWndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kWindowClass;
    MSG msg{};
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"OSD message receiver registration failed (%lu)",
               GetLastError());
        if (GetCoreState().module.uiReady) SetEvent(GetCoreState().module.uiReady);
        ReleaseWindowsAccentProvider();
        if (initialized) CoUninitialize();
        return 0;
    }
    GetCoreState().module.receiveWnd = CreateWindowExW(0, kWindowClass, L"", 0,
        0, 0, 0, 0, HWND_MESSAGE, nullptr, wc.hInstance, nullptr);
    if (GetCoreState().module.receiveWnd) {
        GetCoreState().module.PublishReceiver(GetCoreState().module.receiveWnd);
        GetCoreState().module.clipboardListener =
            AddClipboardFormatListener(GetCoreState().module.receiveWnd) != FALSE;
        InitDeviceEvents();
        InitNetworkEvents();
    } else {
        Wh_Log(L"OSD message receiver creation failed (%lu)", GetLastError());
    }
    for (int i = 0; i < 4; ++i)
        GetNoticeState().keys.toggle[i] = (GetKeyState(kLockVk[i]) & 1) != 0;
    HMODULE module = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<PCWSTR>(reinterpret_cast<void*>(LockKeyProc)),
        &module);
    GetNoticeState().keys.hook = SetWindowsHookExW(WH_KEYBOARD_LL, LockKeyProc, module, 0);
    if (!GetNoticeState().keys.hook)
        Wh_Log(L"Lock-key keyboard hook unavailable (%lu)", GetLastError());
    // Single check handles late injection; creation hook handles new InputSites.
    if (GetCoreState().module.receiveWnd) TryStartXamlAfterShellInputSite(GetCoreState().module.receiveWnd);
    if (GetCoreState().module.uiReady) SetEvent(GetCoreState().module.uiReady);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    GetCoreState().module.BeginShutdown();
    if (GetNoticeState().keys.hook) { UnhookWindowsHookEx(GetNoticeState().keys.hook); GetNoticeState().keys.hook = nullptr; }
    if (GetCoreState().module.clipboardListener && GetCoreState().module.receiveWnd)
        RemoveClipboardFormatListener(GetCoreState().module.receiveWnd);
    GetCoreState().module.clipboardListener = false;
    if (GetCoreState().module.receiveWnd) {
        ClearXamlFailureNotice(GetCoreState().module.receiveWnd);
        KillTimer(GetCoreState().module.receiveWnd, kEventBatchTimer);
        KillTimer(GetCoreState().module.receiveWnd, kDdcBatchTimer);
        KillTimer(GetCoreState().module.receiveWnd, kMediaAnimationTimer);
        KillTimer(GetCoreState().module.receiveWnd, kNetworkRefreshTimer);
    }
    GetBrightnessState().ddc.ClearPendingOnControllerThread();
    GetNoticeState().notice.ResetBatch();
    GetNoticeState().notice.usbNames.clear();
    GetConnectivityState().network.ResetRefresh();
    GetConnectivityState().network.interfaces.clear();
    StopDeviceEvents();
    ClearClipboardThumbnail();
    GetAudioState().mixer.ReleaseStorageOnControllerThread();
    if (GetCoreState().module.receiveWnd) DestroyWindow(GetCoreState().module.receiveWnd);
    GetCoreState().module.receiveWnd = nullptr;
    UnregisterClassW(kWindowClass, wc.hInstance);
    ReleaseWindowsAccentProvider();
    if (initialized) CoUninitialize();
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
    GetCoreState().module.isExplorer = _wcsicmp(name, L"explorer.exe") == 0;
    const bool isTwinkle = _wcsicmp(name, L"Twinkle Tray.exe") == 0;
    if (!GetCoreState().module.isExplorer && !isTwinkle) return FALSE;
    LoadSettings();
    if (GetCoreState().module.isExplorer) {
        HookNativeOsd();
        HookShellInputSiteCreation();
    }
    HookDdc();
    Wh_Log(L"Fluent OSD v%s initialized (%s)", WH_MOD_VERSION, name);
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!GetCoreState().module.isExplorer) return;
    GetCoreState().module.uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!GetCoreState().module.uiReady) {
        Wh_Log(L"Cannot create UI ready event: %lu", GetLastError());
        return;
    }
    GetCoreState().module.uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0,
                              &GetCoreState().module.uiThreadId);
    if (!GetCoreState().module.uiThread) {
        Wh_Log(L"Cannot start OSD UI thread: %lu", GetLastError());
        CloseHandle(GetCoreState().module.uiReady);
        GetCoreState().module.uiReady = nullptr;
        return;
    }
    if (WaitForSingleObject(GetCoreState().module.uiReady, 1500) != WAIT_OBJECT_0)
        Wh_Log(L"OSD UI initialization did not signal readiness");
    GetBrightnessState().writer.stop.store(false);
    const HANDLE writerWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    GetBrightnessState().writer.PublishWake(writerWake);
    if (writerWake) {
        GetBrightnessState().writer.thread = CreateThread(nullptr, 0,
            BrightnessWheelThreadProc, nullptr, 0, nullptr);
        if (!GetBrightnessState().writer.thread)
            GetBrightnessState().writer.CloseWakeAfterWorkerStops();
    }
    GetAudioState().media.stop.store(false);
    const HANDLE mediaWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    GetAudioState().media.PublishWake(mediaWake);
    if (mediaWake) {
        GetAudioState().media.thread = CreateThread(nullptr, 0, MediaThreadProc, nullptr,
                                    0, nullptr);
        if (!GetAudioState().media.thread)
            GetAudioState().media.CloseWakeAfterWorkerStops();
    }
    // XAML starts from the input event or one-time controller snapshot,
    // never directly during Windhawk's AfterInit callback.
}

void Wh_ModSettingsChanged() {
    LoadSettings();
    // Settings may be called on Windhawk's worker thread. Never bypass the
    // shell-readiness gate when reloading settings during cold startup.
    const HWND target = GetCoreState().module.ReceiverForCallbacks();
    if (GetCoreState().module.isExplorer && target)
        (void)PostMessageW(target, kShellInputSiteReadyMessage, 0, 0);
    if (GetCoreState().module.isExplorer && target)
        (void)PostMessageW(target, kBluetoothConfigMessage, 0, 0);
    if (GetCoreState().module.isExplorer && target)
        (void)PostMessageW(target, kNetworkConfigMessage, 0, 0);
    // Refresh the next OSD using the newly selected theme. Settings never
    // force an unexpected brightness write or background monitor read.
}

void Wh_ModBeforeUninit() {
    // Withdraw the published HWND before joining workers and the controller.
    GetCoreState().module.BeginShutdown();
    // WinRT/XAML is STA-owned and must exit before the module unloads.
    xaml_osd::Stop();
    // Stop all worker threads before the UI windows or DLL can be unloaded.
    GetBrightnessState().writer.SignalStop();
    if (GetBrightnessState().writer.thread) {
        // Keep the safe unbounded join; report unusually slow hardware exits.
        const DWORD first = WaitForSingleObject(GetBrightnessState().writer.thread, 2500);
        if (first == WAIT_TIMEOUT) {
            Wh_Log(L"Fluent OSD/brightness: worker still active after 2500 ms; awaiting safe exit");
            (void)WaitForSingleObject(GetBrightnessState().writer.thread, INFINITE);
        } else if (first != WAIT_OBJECT_0) {
            Wh_Log(L"Fluent OSD/brightness: join returned %lu", first);
        }
        CloseHandle(GetBrightnessState().writer.thread);
        GetBrightnessState().writer.thread = nullptr;
    }
    GetBrightnessState().writer.CloseWakeAfterWorkerStops();
    GetAudioState().media.SignalStop();
    if (GetAudioState().media.thread) {
        // Await completion to guarantee there is no executing code in the
        // Windhawk DLL after unload. The WinRT worker is independent of Explorer.
        WaitForSingleObject(GetAudioState().media.thread, INFINITE);
        CloseHandle(GetAudioState().media.thread);
        GetAudioState().media.thread = nullptr;
    }
    GetAudioState().media.CloseWakeAfterWorkerStops();
    if (GetCoreState().module.uiThread) {
        // Waiting with a 2.5-second timeout and then unloading could leave
        // this DLL executing on a live UI thread. Join before the unload.
        PostThreadMessageW(GetCoreState().module.uiThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(GetCoreState().module.uiThread, INFINITE);
        CloseHandle(GetCoreState().module.uiThread);
        GetCoreState().module.uiThread = nullptr;
    }
    if (GetCoreState().module.uiReady) {
        CloseHandle(GetCoreState().module.uiReady);
        GetCoreState().module.uiReady = nullptr;
    }
}

void Wh_ModUninit() {
    // Windhawk removes hooks between BeforeUninit and Uninit. Worker
    // and receiver threads have also joined, so these no_destroy buffers
    // can now release their allocations without racing hook callbacks.
    GetNativeEventState().mailbox.ReleaseAfterHooksRemoved();
    GetBrightnessState().ddc.ReleaseAfterHooksRemoved();
    GetBrightnessState().writer.ReleaseStorageAfterWorkerStops();
    GetAudioState().media.ReleaseStorageAfterThreadsStop();
    // Do not depend on global C++ destructors at DLL_PROCESS_DETACH.
    // Threads are joined and callbacks/hooks have been withdrawn by now.
    osd_control::GetControlState().ReleaseAfterHooksRemoved();
    xaml_osd::GetXamlState().ReleaseAfterThreadsStop();
    GetNoticeState().ReleaseAfterControllerStops();
    GetConnectivityState().ReleaseAfterControllerStops();
    GetCoreState().ReleaseAfterThreadsStop();
    GetSettingsModuleState().ReleaseAfterThreadsStop();
    // Mixer COM objects and containers are released by the UI owner thread.
    GetCoreState().module.createWindowInBandOriginal = nullptr; // Windhawk removed hooks.
    if (GetCoreState().module.confirmatorDll) {
        FreeLibrary(GetCoreState().module.confirmatorDll);
        GetCoreState().module.confirmatorDll = nullptr;
    }
    if (GetCoreState().module.ddcDll) {
        FreeLibrary(GetCoreState().module.ddcDll);
        GetCoreState().module.ddcDll = nullptr;
    }
}