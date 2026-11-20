// ==WindhawkMod==
// @id              fluent-osd-media
// @name            Fluent OSD & Media
// @description     Fluent-style Windows 11 OSDs for volume, DDC/CI brightness, media controls, per-app audio mixer, lock keys, clipboard and device events.
// @version         1.7.0
// @author          Reg Chen
// @github          https://github.com/reg-chen
// @include         explorer.exe
// @include         Twinkle Tray.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lgdiplus -lshcore -ladvapi32 -lole32 -luuid -lshell32 -lsetupapi -liphlpapi -loleaut32
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Fluent OSD & Media

Configurable Windows 11 on-screen indicators for volume, brightness, media
playback, keyboard lock states and selected device/connectivity events. The
flyouts are rendered using GDI+ layered windows in Explorer.

## Native versus custom OSDs

Native Windows indicators have eight independent **Hide** switches plus a
**Hide all supported native OSDs** master switch: volume, display brightness,
keyboard backlight, airplane mode, camera, microphone, text and virtual
desktop names. The master switch overrides individual Hide settings without
resetting them.

Each custom event has a separate **Show** switch. Native Hide and custom Show
are independent, so you may display the native indicator, the custom one,
both or neither. Custom volume/brightness is not implicitly enabled by a
media-card, mixer-arrow or layout option. Overlapping native and custom
indicators may require different display positions.

## Volume, brightness and audio

- **Volume:** Current default output endpoint level and mute status, with
  horizontal/vertical layouts, an optional expandable mixer button, and
  wheel, click or drag adjustment directly over the main volume track.
- **External-monitor brightness:** DDC/CI OSD on successful
  `SetMonitorBrightness` or `SetVCPFeature` writes (default VCP `0x10`)
  made by supported host processes (Explorer and Twinkle Tray). This tracks
  requested values and cached monitor ranges; it is not a hardware readback.
  Wheel and click/drag changes use a separate DDC/CI worker. Other DDC backends and
  firmware brightness buttons are not detected.
- **Windows brightness:** Optional replacement of supported native brightness
  indications; wheel and click/drag control of built-in brightness require a working WMI
  brightness interface. Unsupported hardware writes do not change brightness.
- **Mixer:** System master audio plus individual Core Audio sessions on the
  default multimedia output device. Application icons toggle mute; sliders
  and wheel input adjust the corresponding volume. Large session lists can
  scroll independently of the slider wheel areas.
- **SMTC media card:** Song title, artist, artwork, previous/play-pause/next
  controls and press feedback. A supported media timeline displays elapsed
  and total time, supports clicking/dragging to seek when the player permits,
  and does **not** use wheel seeking. Missing durations or seek capabilities
  are respected. Artwork reads are bounded and cached while displayed.

## Other custom indicators

- **Keyboard:** Caps Lock, Num Lock and Scroll Lock toggle notifications;
  optional Insert indication (its toggle state is application-dependent).
- **Clipboard (opt-in):** Shortened text or image-first preview. Text previews
  are separately configurable; bitmap support depends on the data format.
- **USB:** Device-interface arrival/removal, with available friendly names.
- **Bluetooth:** Classic Bluetooth ACL connection/disconnection events;
  BLE/profile connections may not provide the same events.
- **Network:** Windows connectivity-hint and interface-state changes, which
  do not independently establish Internet access or VPN/SSID identity.

Nearby device events are batched. A single event can show its name; multiple
events show a count and offer a scrollable details panel. Clipboard and
device/network notices are off by default.

## Appearance, layout and duration

- Configurable Windows-following, light or dark **Custom OSD theme**, system
  accent or custom colors, typography, opacity, corners, borders, icons and
  progress-bar/thumb geometry. Default text colors adapt to light/dark mode.
- Nine screen positions, X/Y offsets, per-monitor DPI and overall scaling.
  Main volume/brightness OSD width and height are independently configurable
  for horizontal and vertical layouts.
- In horizontal layout, SMTC/Mixer inherit the main OSD **width** and have
  separate adjustable **heights**. In vertical layout, they inherit the main
  OSD **height** and have separate adjustable **widths**. Artwork and controls
  share the same padded layout; severely constrained sizes prioritize
  preserving aspect ratios and avoiding overlap.
- Optional fade-in/fade-out. One global visible duration with optional
  per-indicator overrides; hovering interactive panels delays auto-hide.

## Compatibility and behavior

Targets Windows 11 x64. Native shell OSD hooks depend on internal symbols
and may need revision following Windows updates. DDC/CI support depends on
monitor firmware, physical-monitor APIs and the process performing the write.
For Taskbar Scroll Actions, its **Custom** DDC/CI method is the supported
integration path. Restart Twinkle Tray if it was already running before the
hooks were enabled.

The UI owns the GDI+ notification hook on its existing message-loop thread;
GDI+'s separate background notification thread is disabled. This avoids
creating another independent GDI+ message pump. During normal Windhawk mod
unloading, the mod stops its workers and releases windows, timers and GDI+
resources. It does not monitor or intercept system shutdown separately;
Windows owns process cleanup when Explorer exits. This limits one potential
source of "GDI+ Window is preventing shutdown" without claiming to resolve
shutdown blockers originating in other processes.

## Display language

Custom OSD text can follow the Windows UI language (**Auto**, default),
or explicitly use **English** or **繁體中文**. Auto uses Traditional Chinese
for zh-TW / zh-HK / zh-MO and English otherwise. Media titles, app/process
names, device names and Windows-supplied text remain unchanged. Windhawk's
settings-label localization is independent. Display strings never serve as
internal event identifiers.

## Resource and input limits

Cross-process brightness notifications are checked for structure size, bounded
DDC/CI values, monitor index and null-terminated display ID before use.
The producer PID is informational; it is not treated as authentication.
SMTC text is capped at 4,096 UTF-16 code units; album-art reads are capped
at 1 MiB and decoded artwork is rejected above 4,096 px per dimension or
8 Mi pixels. Clipboard previews remain optional and transient.

## License and acknowledgements

Copyright (c) Reg Chen. Licensed under **GPL-3.0**. Integrates with Windows
APIs and is compatible with relevant actions in **Taskbar Scroll Actions**
and **Twinkle Tray**. No third-party UI assets are bundled. Names and
trademarks remain the property of their respective owners.
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
      $description: Master override for all eight native OSD categories below. Custom Show switches remain independent; disabling this restores individual Hide choices.
    - hideNativeVolume: false
      $name: Hide Windows volume OSD
    - hideNativeBrightness: false
      $name: Hide Windows native brightness OSD
    - hideNativeKeyboardBrightness: false
      $name: Hide keyboard brightness OSD
    - hideNativeAirplane: false
      $name: Hide airplane mode OSD
    - hideNativeCamera: false
      $name: Hide camera OSD
    - hideNativeMicrophone: false
      $name: Hide microphone OSD
    - hideNativeText: false
      $name: Hide miscellaneous text OSD
    - hideNativeVirtualDesktop: false
      $name: Hide virtual desktop name OSD
  $name: 1. Windows native OSD — Hide switches
  $description: All native Hide switches default to off. The master switch hides all supported native OSDs; individual switches apply independently when the master is off. Show custom switches never affect native visibility.
- CustomOSD:
    - Switches:
        - showCustomVolume: false
          $name: Show custom Windows volume OSD
          $description: The only switch that enables the custom Windows volume indicator. Media card, mixer arrow, and vertical layout only customize it and never enable it implicitly.
        - showCustomBrightness: false
          $name: Show custom Windows brightness OSD
          $description: Enabled only by this switch; vertical layout changes appearance without enabling it implicitly.
        - showCustomKeyboardBrightness: false
          $name: Show custom keyboard backlight OSD
        - showCustomAirplane: false
          $name: Show custom airplane mode OSD
        - showCustomCamera: false
          $name: Show custom camera OSD
          $description: Includes camera use and camera access state; labels distinguish the two.
        - showCustomMicrophone: false
          $name: Show custom microphone mute OSD
        - showCustomText: false
          $name: Show custom miscellaneous text OSD
        - showCustomVirtualDesktop: false
          $name: Show custom virtual desktop name OSD
          $description: Shows the text provided by Windows when available; desktop routing is best effort and depends on shell symbols.
        - showDdcBrightness: true
          $name: Show custom DDC/CI brightness OSD
          $description: Independent of Windows native brightness Hide. Enabled by default for existing DDC/CI functionality.
        - showSmtcOnVolume: true
          $name: Show SMTC media card on volume change
          $description: Show playing media title, artist, artwork and controls beside the volume OSD, if the player provides SMTC data.
        - showVolumeMixerArrow: true
          $name: Show per-app volume mixer expand arrow
          $description: Click the arrow to adjust Core Audio session volumes in an interactive popup.
        - showCapsLockOsd: true
          $name: Show custom Caps Lock OSD
        - showNumLockOsd: true
          $name: Show custom Num Lock OSD
        - showScrollLockOsd: true
          $name: Show custom Scroll Lock OSD
        - showInsertOsd: false
          $name: Show custom Insert OSD
          $description: Insert state is not a system-wide toggle on every application; this indicator tracks its key presses only.
        - showClipboardOsd: false
          $name: Show clipboard OSD (opt-in)
          $description: Disabled by default for privacy. Only processes clipboard updates after you enable it.
        - showUsbEvents: false
          $name: Show USB connection/disconnection OSD
          $description: USB device-interface arrivals/removals; multiple interfaces from one physical device are coalesced.
        - showBluetoothEvents: false
          $name: Show Bluetooth connection OSD (Classic HCI)
          $description: Bluetooth radio HCI ACL link events; may not cover BLE logical/device profile connections.
        - showNetworkEvents: false
          $name: Show network connectivity OSD
          $description: Windows aggregate connectivity hints, not ping or per-VPN connectivity verification.
      $name: Individual OSD switches
    - AudioAndMedia:
        - showMediaArtwork: true
          $name: Show SMTC thumbnail
        - showMediaControls: true
          $name: Show previous / play-pause / next buttons
        - mediaControlSizePercent: 125
          $name: SMTC playback button size (%)
          $description: Scales both the button circles and their icons, default 125%. Mouse hit regions follow the drawn buttons.
          #! $min: 90
          #! $max: 135
          #! $format: slider
        - mixerMaxRows: 6
          $name: Visible mixer rows
          #! $min: 3
          #! $max: 16
          #! $format: slider
      $name: Media and audio mixer
    - ClipboardAndDevices:
        - clipboardTextPreview: false
          $name: Show copied text excerpt
          $description: May expose passwords and private text on screen. Disabled by default.
        - clipboardImagePreview: true
          $name: Show copied image thumbnail
          $description: Displays a larger image-first preview fitted to available space without distortion; currently requires a usable bitmap clipboard format.
        - clipboardMaxChars: 48
          $name: Maximum copied-text preview characters
          #! $min: 12
          #! $max: 100
      $name: Clipboard and device event details
    - BrightnessSources:
        - ddcFromExplorer: true
          $name: Monitor Taskbar Scroll Actions (explorer.exe)
        - ddcFromTwinkle: true
          $name: Monitor Twinkle Tray
        - ddcVcpCode: 16
          $name: Brightness VCP code (decimal; default 16 = 0x10)
      $name: DDC/CI sources
    - Appearance:
        - ddcTheme: system
          $name: Custom OSD theme
          $options:
          - system: Follow Windows app theme
          - light: Light
          - dark: Dark
        - ddcBorderless: true
          $name: Borderless DDC/CI OSD (no outline or shadow)
          $description: Matches the border/shadow behavior of Notification Center Styler's Borderless theme. Only this custom OSD is affected; no automatic cross-mod theme sync.
        - ddcAccentMode: system
          $name: Progress bar color source
          $options:
          - system: Windows system accent color (automatic)
          - custom: Custom color
        - ddcCustomAccent: "#B97DFF"
          $name: Custom progress color (#RRGGBB)
          $description: Used only when Progress bar color source = Custom. Invalid hex falls back to system accent.
          #! $showIf: {ddcAccentMode: custom}
          #! $format: colorRgb
        - ddcBackgroundMode: system
          $name: Background color source
          $options:
          - system: Follow light/dark theme
          - custom: Custom color
        - ddcCustomBackground: "#28282C"
          $name: Custom background color (#RRGGBB)
          #! $showIf: {ddcBackgroundMode: custom}
          #! $format: colorRgb
        - ddcTextMode: system
          $name: Text and icon color (Light theme defaults to dark text)
          $options:
          - system: Follow light/dark theme
          - custom: Custom color
        - ddcCustomText: "#FAFAFA"
          $name: Custom text and icon color (#RRGGBB)
          #! $showIf: {ddcTextMode: custom}
          #! $format: colorRgb
        - ddcTrackMode: system
          $name: Progress track color
          $options:
          - system: Follow light/dark theme
          - custom: Custom color
        - ddcCustomTrack: "#5A5A60"
          $name: Custom track color (#RRGGBB)
          #! $showIf: {ddcTrackMode: custom}
          #! $format: colorRgb
        - ddcBackgroundOpacity: 96
          $name: Background opacity (%)
          #! $min: 0
          #! $max: 100
          #! $format: slider
        - ddcCornerRadius: 17
          $name: Card corner radius (logical px)
          #! $min: 0
          #! $max: 34
          #! $format: slider
        - ddcBarThickness: 8
          $name: Bar thickness (logical px)
          #! $min: 2
          #! $max: 18
          #! $format: slider
        - ddcThumbDiameter: 11
          $name: Thumb diameter (0 = hidden)
          #! $min: 0
          #! $max: 20
          #! $format: slider
        - ddcFontSize: 15
          $name: Value font size (logical px)
          #! $min: 10
          #! $max: 24
          #! $format: slider
        - ddcIconSize: 16
          $name: Vertical OSD icon size (logical px)
          $description: Same bounding box for the speaker and sun icons. Defaults to a compact 16px before DPI and overall size scaling.
          #! $min: 10
          #! $max: 24
          #! $format: slider
        - ddcIconStrokeWidth: 2
          $name: Vertical OSD icon stroke width (logical px)
          $description: One stroke width is shared by both icon types, independent of speaker volume level.
          #! $min: 1
          #! $max: 3
          #! $format: slider
        - ddcShowSun: true
          $name: Show sun icon
        - ddcShowValue: true
          $name: Show brightness value
        - ddcInnerPadding: 14
          $name: Vertical OSD interior padding (logical px)
          #! $min: 6
          #! $max: 22
          #! $format: slider
      $name: Fluent appearance
    - Timing:
        - globalDurationMs: 3000
          $name: Global OSD visibility (ms)
          $description: Shared by every custom OSD, unless individual durations are enabled. The fade animation is configured separately.
          #! $min: 500
          #! $max: 20000
        - individualDurations: false
          $name: Override individual OSD durations
          $description: Disabled by default. Turn on to configure the categories below; otherwise every category inherits the global duration.
        - volumeDurationMs: 1250
          $name: Volume without SMTC (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - mediaDurationMs: 4000
          $name: Volume with SMTC media (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - nativeBrightnessDurationMs: 1250
          $name: Windows brightness (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - ddcBrightnessDurationMs: 1250
          $name: DDC/CI brightness (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - nativeEventDurationMs: 1250
          $name: Other Windows native OSD replacements (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - lockDurationMs: 1250
          $name: Caps / Num / Scroll / Insert (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - clipboardDurationMs: 2100
          $name: Clipboard notification (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - deviceDurationMs: 2100
          $name: USB and Bluetooth notifications (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - networkDurationMs: 2100
          $name: Network notification (ms)
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
        - interactiveDurationMs: 8000
          $name: Expanded Mixer / media / details (ms)
          $description: Inactivity timeout after an interactive action. While hovering an interactive panel, auto-hide is paused and restarts on mouse leave.
          #! $showIf: {individualDurations: true}
          #! $min: 500
          #! $max: 20000
      $name: OSD timing
    - MainOSDSize:
            - horizontalOsdWidth: 336
              $name: Horizontal OSD width (logical px)
              $description: Main volume and brightness OSD canvas width. SMTC and Mixer inherit this width in horizontal layout.
              #! $min: 300
              #! $max: 650
            - horizontalOsdHeight: 92
              $name: Horizontal OSD height (logical px)
              $description: Main volume and brightness OSD canvas height. SMTC and Mixer use an independently adjustable expanded height.
              #! $min: 80
              #! $max: 220
            - verticalOsdWidth: 72
              $name: Vertical OSD width (logical px)
              $description: Main volume and brightness OSD canvas width. Expanded SMTC and Mixer use an independent width.
              #! $min: 72
              #! $max: 180
            - verticalOsdHeight: 176
              $name: Vertical OSD height (logical px)
              $description: Main volume and brightness OSD canvas height. SMTC and Mixer inherit this height in vertical layout.
              #! $min: 160
              #! $max: 430
      $name: Main OSD dimensions
    - ExpandedPanelSize:
            - horizontalSmtcHeight: 176
              $name: Horizontal SMTC height (logical px)
              $description: SMTC width inherits horizontal main OSD width; only its height is independent.
              #! $min: 176
              #! $max: 480
            - horizontalMixerHeight: 176
              $name: Horizontal Mixer height (logical px)
              $description: Mixer width inherits horizontal main OSD width; only its height is independent.
              #! $min: 176
              #! $max: 480
            - verticalSmtcWidth: 340
              $name: Vertical SMTC width (logical px)
              $description: SMTC height inherits vertical main OSD height; only its width is independent.
              #! $min: 300
              #! $max: 650
            - verticalMixerWidth: 340
              $name: Vertical Mixer width (logical px)
              $description: Mixer height inherits vertical main OSD height; only its width is independent.
              #! $min: 300
              #! $max: 650
      $name: SMTC / Mixer dimensions
    - Layout:
        - verticalVolumeBrightness: false
          $name: Use vertical volume and brightness layout
          $description: Layout only; it does not enable Windows custom volume or brightness OSDs. Other native-event replacements retain compact icon-and-state cards.
        - fadeOsd: true
          $name: Enable custom OSD fade animation
        - ddcSizePercent: 75
          $name: Custom OSD size (%)
          $description: Overall uniform scale applied after the configurable logical width/height and monitor DPI. Does not change the aspect ratio of either layout.
        - ddcPosition: bottomCenter
          $name: OSD position
          $options:
          - topLeft: Top left
          - topCenter: Top center
          - topRight: Top right
          - centerLeft: Center left
          - center: Center
          - centerRight: Center right
          - bottomLeft: Bottom left
          - bottomCenter: Bottom center (default)
          - bottomRight: Bottom right
        - ddcOffsetX: 0
          $name: Horizontal offset (logical px, right positive)
          #! $min: -500
          #! $max: 500
        - ddcOffsetY: 0
          $name: Vertical offset (logical px, down positive)
          #! $min: -500
          #! $max: 500
        - fadeDurationMs: 160
          $name: Fade duration (ms)
          #! $min: 60
          #! $max: 450
      $name: Position and size
  $name: 2. Custom OSD
  $description: A Show switch controls only its own custom flyout. Native visibility is controlled exclusively by the native Hide switches above; when Hide is off and Show is on, both native and custom OSDs will appear.
*/
// ==/WindhawkModSettings==

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <dbt.h>
#include <bluetoothapis.h>
#include <setupapi.h>
#include <iphlpapi.h>
#include <shellapi.h>
#include <bthdef.h>
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
#include <shellscalingapi.h>
#include <cstdint>
#include <cstddef>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <windowsx.h>
#include <wbemidl.h>
#include <audiopolicy.h>
#include <wrl/client.h>
#include <vector>
#include <memory>
#include <cstdlib>
#include <utility>
#include <string>

namespace {

constexpr WCHAR kWindowClass[] = L"WH.NativeOSD.DDC.01E7AFB2";
constexpr ULONG_PTR kCopyDataTag = 0x1E7AFB2;
constexpr UINT_PTR kHideTimer = 320;
constexpr UINT_PTR kFadeTimer = 321;
constexpr UINT_PTR kEventBatchTimer = 322;
constexpr UINT_PTR kMediaAnimationTimer = 323;
constexpr UINT kMediaAnimationIntervalMs = 100;
constexpr ULONGLONG kMediaFeedbackMs = 240;
constexpr ULONGLONG kMediaRefreshIntervalMs = 3000;
constexpr UINT kBrightnessWheelResultMessage = WM_APP + 326;
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
};
static_assert(ARRAYSIZE(kLocalizedText) == static_cast<size_t>(OsdText::Count));
std::atomic<int> g_displayLanguage{0}; // 0=Auto, 1=English, 2=zh-TW
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

std::atomic<bool> g_hideAllNativeOsd{false};
std::atomic<bool> g_hide[static_cast<int>(Kind::Count)]{};
std::atomic<bool> g_showCustomNative[static_cast<int>(Kind::Count)]{};
std::atomic<bool> g_showDdcBrightness{true};
std::atomic<bool> g_verticalVolumeBrightness{false};
std::atomic<bool> g_fromExplorer{true};
std::atomic<bool> g_fromTwinkle{true};
std::atomic<int> g_vcpCode{16};
enum class DurationKind : int {
    Volume, Media, NativeBrightness, DdcBrightness, NativeEvents, LockKeys,
    Clipboard, Devices, Network, Interactive, Count
};

std::atomic<int> g_globalDurationMs{3000};
std::atomic<bool> g_individualDurations{false};
std::atomic<int> g_durationOverrides[static_cast<int>(DurationKind::Count)]{};
// Only the dedicated OSD UI thread reads/writes this current category.
DurationKind g_activeDurationKind = DurationKind::Volume;

UINT OsdDuration(DurationKind kind) {
    if (!g_individualDurations.load(std::memory_order_relaxed))
        return static_cast<UINT>(g_globalDurationMs.load(std::memory_order_relaxed));
    return static_cast<UINT>(g_durationOverrides[static_cast<int>(kind)]
        .load(std::memory_order_relaxed));
}

std::atomic<int> g_ddcTheme{0};
std::atomic<int> g_ddcSizePercent{75};
// Independent logical dimensions; global DPI and size % are applied later.
std::atomic<int> g_horizontalOsdWidth{336};
std::atomic<int> g_horizontalOsdHeight{92};
std::atomic<int> g_verticalOsdWidth{72};
std::atomic<int> g_verticalOsdHeight{176};
std::atomic<int> g_horizontalSmtcHeight{176};
std::atomic<int> g_horizontalMixerHeight{176};
std::atomic<int> g_verticalSmtcWidth{340};
std::atomic<int> g_verticalMixerWidth{340};
std::atomic<bool> g_ddcBorderless{true};
std::atomic<bool> g_showSmtcOnVolume{true};
std::atomic<bool> g_showMediaArtwork{true};
std::atomic<bool> g_showMediaControls{true};
std::atomic<int> g_mediaControlSizePercent{125};
std::atomic<bool> g_showMixerArrow{true};
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
std::atomic<int> g_position{0};
std::atomic<int> g_offsetX{0};
std::atomic<int> g_offsetY{0};

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

bool g_isExplorer = false;
HMODULE g_ddcDll = nullptr;
HMODULE g_confirmatorDll = nullptr;
std::atomic<bool> g_loggedUnmapped{false};
HANDLE g_uiThread = nullptr;
HANDLE g_uiReady = nullptr;
DWORD g_uiThreadId = 0;
HWND g_receiveWnd = nullptr;
HWND g_popupWnd = nullptr;
HWND g_panelWnd = nullptr;
HWND g_arrowWnd = nullptr;
// Hover and press state belong to the Explorer UI thread, like the flyouts.
bool g_arrowHovered = false;
bool g_arrowPressed = false;
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
std::vector<HDEVNOTIFY> g_bluetoothNotifications;
std::vector<HANDLE> g_bluetoothRadios;
HMODULE g_bluetoothDll = nullptr;
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
enum class NoticeCategory { Usb, Bluetooth, Network };
enum class NoticeAction { Connected, Disconnected, Removed, NetworkChanged };
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
constexpr float kClipboardImageCanvasW = 264.0f;
constexpr float kClipboardImageCanvasH = 224.0f;
constexpr float kClipboardImageMaxW = 224.0f;
constexpr float kClipboardImageMaxH = 164.0f;
DWORD g_usbLastEvent = 0;
WPARAM g_usbLastEventType = 0;
struct BtPreviousEvent { bool connected; DWORD when; };
std::unordered_map<ULONGLONG, BtPreviousEvent> g_btPrevious;

// The SMTC worker never touches HWND/GDI+/CoreAudio objects directly.
struct MediaSnapshot {
    bool available = false;
    bool playing = false;
    bool canPrevious = false;
    bool canToggle = false;
    bool canNext = false;
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
int g_mediaFeedbackIndex = -1;
ULONGLONG g_mediaFeedbackTick = 0;
ULONGLONG g_mediaLastRefreshTick = 0;
HANDLE g_mediaWake = nullptr;
HANDLE g_mediaThread = nullptr;
std::atomic<bool> g_mediaStop{false};
SRWLOCK g_mediaCommandLock = SRWLOCK_INIT;
struct MediaCommand {
    int action = 0;  // 1=previous; 2=toggle; 3=next; 4=seek
    INT64 position = 0; // SMTC 100-ns ticks for action 4
};
std::vector<MediaCommand> g_mediaCommands; // Bounded, worker-owned after swap.

enum class PanelMode { None, Media, Mixer, Details };
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
constexpr float kMixerRowStep = 30.0f;
constexpr float kMixerFirstRowY = 45.0f;
// Shared by painting, hit-testing and drag calculations. App icons occupy
// approximately x=25..44, followed by an 18px gap to the volume track.
constexpr float kMixerTrackStart = 62.0f;
constexpr float kMixerTrackLength = 216.0f;
float MixerTrackLength() {
    if (g_panelWidth <= 0 || g_scale <= 0.0f) return kMixerTrackLength;
    const float w = g_panelWidth / g_scale;
    // Keep room at the right for the volume number and scrollbar.
    return std::max(110.0f, w -
        (g_verticalVolumeBrightness.load() ? 124.0f : 120.0f));
}
constexpr float kMixerTrackHeight = 7.0f;
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


// Hook callback and UI message loop share the same dedicated UI thread.
HHOOK g_lockHook = nullptr;
bool g_lockPressed[4]{};
bool g_lockToggle[4]{};
int g_lastLock = 0;
bool g_lastLockValue = false;
constexpr int kLockVk[4] = {VK_CAPITAL, VK_NUMLOCK, VK_SCROLL, VK_INSERT};

bool IsCustomMode(PCWSTR name) {
    PCWSTR value = Wh_GetStringSetting(name);
    const bool custom = value && _wcsicmp(value, L"custom") == 0;
    Wh_FreeStringSetting(value);
    return custom;
}

int ReadPositionSetting() {
    PCWSTR value = Wh_GetStringSetting(L"CustomOSD.Layout.ddcPosition");
    int result = 0; // bottomCenter
    if (value) {
        if (_wcsicmp(value, L"bottomLeft") == 0) result = 1;
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

void LoadSettings() {
    PCWSTR selectedLanguage = Wh_GetStringSetting(L"displayLanguage");
    const int chosen = selectedLanguage &&
        _wcsicmp(selectedLanguage, L"zh-TW") == 0 ? 2 :
        selectedLanguage && _wcsicmp(selectedLanguage, L"en") == 0 ? 1 : 0;
    g_displayLanguage.store(chosen, std::memory_order_relaxed);
    Wh_FreeStringSetting(selectedLanguage);
    g_hideAllNativeOsd.store(
        Wh_GetIntSetting(L"NativeHide.hideAllNativeOsd") != 0);
    constexpr PCWSTR names[] = {
        L"NativeHide.hideNativeVolume", L"NativeHide.hideNativeBrightness", L"NativeHide.hideNativeKeyboardBrightness",
        L"NativeHide.hideNativeAirplane", L"NativeHide.hideNativeCamera", L"NativeHide.hideNativeMicrophone",
        L"NativeHide.hideNativeText", L"NativeHide.hideNativeVirtualDesktop"
    };
    for (int i = 0; i < static_cast<int>(Kind::Count); ++i)
        g_hide[i].store(Wh_GetIntSetting(names[i]) != 0);
    constexpr PCWSTR customKeys[] = {
        L"CustomOSD.Switches.showCustomVolume",
        L"CustomOSD.Switches.showCustomBrightness",
        L"CustomOSD.Switches.showCustomKeyboardBrightness",
        L"CustomOSD.Switches.showCustomAirplane",
        L"CustomOSD.Switches.showCustomCamera",
        L"CustomOSD.Switches.showCustomMicrophone",
        L"CustomOSD.Switches.showCustomText",
        L"CustomOSD.Switches.showCustomVirtualDesktop"
    };
    static_assert(ARRAYSIZE(customKeys) == static_cast<int>(Kind::Count));
    for (int i = 0; i < static_cast<int>(Kind::Count); ++i)
        g_showCustomNative[i].store(Wh_GetIntSetting(customKeys[i]) != 0);
    g_showDdcBrightness.store(Wh_GetIntSetting(L"CustomOSD.Switches.showDdcBrightness") != 0);
    g_verticalVolumeBrightness.store(Wh_GetIntSetting(L"CustomOSD.Layout.verticalVolumeBrightness") != 0);
    g_fromExplorer.store(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcFromExplorer") != 0);
    g_fromTwinkle.store(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcFromTwinkle") != 0);
    g_vcpCode.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.BrightnessSources.ddcVcpCode"), 0, 255));
    g_globalDurationMs.store(std::clamp(
        Wh_GetIntSetting(L"CustomOSD.Timing.globalDurationMs"), 500, 20000));
    g_individualDurations.store(
        Wh_GetIntSetting(L"CustomOSD.Timing.individualDurations") != 0);
    constexpr PCWSTR durationKeys[] = {
        L"volumeDurationMs", L"mediaDurationMs",
        L"nativeBrightnessDurationMs", L"ddcBrightnessDurationMs",
        L"nativeEventDurationMs", L"lockDurationMs", L"clipboardDurationMs",
        L"deviceDurationMs", L"networkDurationMs",
        L"interactiveDurationMs"
    };
    static_assert(ARRAYSIZE(durationKeys) == static_cast<int>(DurationKind::Count));
    for (int i = 0; i < static_cast<int>(DurationKind::Count); ++i) {
        std::wstring path = L"CustomOSD.Timing.";
        path += durationKeys[i];
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
    g_horizontalOsdHeight.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.MainOSDSize.horizontalOsdHeight"), 80, 220));
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
    g_showMixerArrow.store(Wh_GetIntSetting(L"CustomOSD.Switches.showVolumeMixerArrow") != 0);
    g_mixerMaxRows.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.AudioAndMedia.mixerMaxRows"), 3, 16));
    constexpr PCWSTR lockNames[] = {
        L"CustomOSD.Switches.showCapsLockOsd", L"CustomOSD.Switches.showNumLockOsd", L"CustomOSD.Switches.showScrollLockOsd", L"CustomOSD.Switches.showInsertOsd"
    };
    for (int i = 0; i < 4; ++i)
        g_showLockKeys[i].store(Wh_GetIntSetting(lockNames[i]) != 0);
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
    g_position.store(ReadPositionSetting());
    g_offsetX.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcOffsetX"), -500, 500));
    g_offsetY.store(std::clamp(Wh_GetIntSetting(L"CustomOSD.Layout.ddcOffsetY"), -500, 500));
}

bool Hidden(Kind k) {
    // Hide never changes whether the custom OSD is displayed. A master
    // override hides all native categories, even if their local Hide is off.
    return g_hideAllNativeOsd.load(std::memory_order_relaxed) ||
           g_hide[static_cast<int>(k)].load(std::memory_order_relaxed);
}

// A transient native display request is not the underlying system state.
// The shell hook never draws a window or performs device I/O.
struct NativeEventInfo {
    Kind kind = Kind::Keyboard;
    int value = 0;
    int variant = 0; // 1 = camera access (not camera activity)
    std::wstring text;
};
SRWLOCK g_nativeEventLock = SRWLOCK_INIT;
NativeEventInfo g_nativeEventPending;
bool g_nativeEventPosted = false;

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

// --- DDC hooks and per-process HANDLE -> display identity / range cache ---
struct PhysicalInfo {
    WCHAR device[CCHDEVICENAME]{}; // GDI display, e.g. \\.\DISPLAY2
    DWORD physicalIndex = 0;
    DWORD minimum = 0;
    DWORD maximum = 0; // 0 = unknown, do not pretend raw=percent
};
SRWLOCK g_handleLock = SRWLOCK_INIT;
std::unordered_map<ULONG_PTR, PhysicalInfo> g_handles;

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

// The wire format contains no HANDLE or pointers: physical HANDLEs are
// process-local and cannot be interpreted in explorer.exe.
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

struct BrightnessWheelTask {
    bool native = false;
    DWORD generation = 0;
    int value = 0;                // Native: 0..100; DDC: device raw value
    BrightnessEvent monitor{};   // Only display ID/physical index, no handles
};
SRWLOCK g_wheelWriteLock = SRWLOCK_INIT;
BrightnessWheelTask g_wheelWritePending;
bool g_wheelWriteHasPending = false;
HANDLE g_wheelWriteWake = nullptr;
HANDLE g_wheelWriteThread = nullptr;
std::atomic<bool> g_wheelWriteStop{false};
std::atomic<DWORD> g_wheelWriteLatest{0};
void QueueBrightnessWheelTask(const BrightnessWheelTask& task) {
    if (!g_wheelWriteWake || g_wheelWriteStop.load()) return;
    AcquireSRWLockExclusive(&g_wheelWriteLock);
    g_wheelWritePending = task;
    g_wheelWriteHasPending = true; // Replace older pending writes on rapid wheel turns.
    g_wheelWriteLatest.store(task.generation, std::memory_order_relaxed);
    ReleaseSRWLockExclusive(&g_wheelWriteLock);
    SetEvent(g_wheelWriteWake);
}


void Publish(HANDLE handle, DWORD value) {
    if (!DdcAllowed()) return;
    PhysicalInfo info = GetPhysicalInfo(handle);
    if (!info.device[0] && !g_loggedUnmapped.exchange(true))
        Wh_Log(L"DDC monitor handle not mapped. Restart Twinkle Tray if it was already running when the mod was enabled.");
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

// --- Non-activating Windows 11-like OSD, Explorer UI thread only ---
// Per-pixel alpha + antialiased GDI+ rendering. This resembles the native
// Win11 flyout; it is intentionally NOT a claim of real WinUI/Acrylic blur.
BrightnessEvent g_visible{};  // UI thread only
constexpr int kLogicalWidth = 336;
constexpr int kLogicalHeight = 92;
// User-configured canvases retain these dimensions as defaults; painting,
// scroll input and panel sizes depend on the live setting values.
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
enum class PopupKind { DdcBrightness, NativeBrightness, NativeVolume, NativeEvent, LockStatus, Notification };
PopupKind g_popupKind = PopupKind::DdcBrightness; // UI thread only
NativeEventInfo g_nativeEventCurrent;         // UI thread only
int g_nativePercent = 0;                        // UI thread only
bool g_nativePercentKnown = false;              // UI thread only
bool g_nativeMuted = false;                     // UI thread only
int g_width = kLogicalWidth;
int g_height = kLogicalHeight;
ULONG_PTR g_gdiplusToken = 0;

// A single direction and set of anchors drives BOTH flyout placement and
// the chevron. Independent panel heights never change the anchoring rule.
enum class FlyoutDirection { Left, Right, Up, Down };
FlyoutDirection InverseDirection(FlyoutDirection dir) {
    switch (dir) {
        case FlyoutDirection::Left: return FlyoutDirection::Right;
        case FlyoutDirection::Right: return FlyoutDirection::Left;
        case FlyoutDirection::Up: return FlyoutDirection::Down;
        case FlyoutDirection::Down: return FlyoutDirection::Up;
    }
    return FlyoutDirection::Right;
}
// The chevron follows the configurable main canvas edges. Its drawn center
// is shared with UpdateArrowHitWindow() to keep click targets aligned.
constexpr float kHorizontalArrowRadius = 12.5f;
constexpr float kVerticalArrowRadius = 11.5f;
// The transparent interaction target is slightly larger than the visible button.
constexpr float kArrowHitDiameter = 30.0f;

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

FlyoutDirection GetFlyoutDirection() {
    const int pos = g_position.load(std::memory_order_relaxed);
    const bool vertical = g_verticalVolumeBrightness.load(
        std::memory_order_relaxed);
    if (vertical) {
        if (PositionIsLeft(pos)) return FlyoutDirection::Right;
        if (PositionIsRight(pos)) return FlyoutDirection::Left;
    } else {
        if (PositionIsTop(pos)) return FlyoutDirection::Down;
        if (PositionIsBottom(pos)) return FlyoutDirection::Up;
    }

    // Centered anchors have no intrinsic direction; use the side with the
    // most room. Media/Mixer panel dimensions are separately configurable.
    RECT main{};
    MONITORINFO mi{sizeof(mi)};
    if (!g_popupWnd || !GetWindowRect(g_popupWnd, &main) ||
        !GetMonitorInfoW(MonitorFromWindow(g_popupWnd,
                                         MONITOR_DEFAULTTONEAREST), &mi))
        return vertical ? FlyoutDirection::Right : FlyoutDirection::Down;
    const RECT& work = mi.rcWork;
    if (vertical) {
        const int freeRight = work.right - main.right;
        const int freeLeft = main.left - work.left;
        return freeRight >= freeLeft ? FlyoutDirection::Right
                                     : FlyoutDirection::Left;
    }
    const int freeDown = work.bottom - main.bottom;
    const int freeUp = main.top - work.top;
    return freeDown >= freeUp ? FlyoutDirection::Down
                              : FlyoutDirection::Up;
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

// UISettings.GetColorValue(UIColorType.Accent): actual user-configured
// Windows UI accent, not DWM's distinct glass composition color.
// Raw WinRT ABI avoids a dependency on the C++/WinRT header package in the
// Windhawk compiler. IUISettings3 IID and method order follow WinRT metadata.
struct UiColor {
    BYTE a, r, g, b;
};
struct IUiSettings3Raw : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetIids(ULONG*, GUID**) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetRuntimeClassName(void**) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetTrustLevel(int*) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetColorValue(int, UiColor*) = 0;
};
constexpr GUID kIUiSettings3 = {
    0x03021be4, 0x5254, 0x4781,
    {0x81, 0x94, 0x51, 0x68, 0xf7, 0xd0, 0x6d, 0x7b}
};
using RoInitialize_t = HRESULT(WINAPI*)(int);
using RoUninitialize_t = void(WINAPI*)();
using WindowsCreateString_t = HRESULT(WINAPI*)(PCWSTR, UINT, void**);
using WindowsDeleteString_t = HRESULT(WINAPI*)(void*);
using RoActivateInstance_t = HRESULT(WINAPI*)(void*, IUnknown**);

HMODULE g_combase = nullptr;               // UI thread only
RoUninitialize_t g_roUninitialize = nullptr;
bool g_roInitialized = false;
IUiSettings3Raw* g_uiSettings = nullptr;    // UI thread only

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
    constexpr WCHAR className[] = L"Windows.UI.ViewManagement.UISettings";
    void* classId = nullptr;
    if (FAILED(createString(className, ARRAYSIZE(className) - 1, &classId)))
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

int BrightnessPercent(bool* known) {
    *known = g_visible.maximum > g_visible.minimum;
    if (!*known) return 0;
    const DWORD current = std::clamp(g_visible.value,
                                     g_visible.minimum, g_visible.maximum);
    const unsigned long long range = g_visible.maximum - g_visible.minimum;
    return static_cast<int>((
        static_cast<unsigned long long>(current - g_visible.minimum) * 100ULL +
        range / 2ULL) / range);
}

// Called ONLY on the Explorer OSD UI thread when Windows requests its
// native volume indicator. We do not query continuously or alter the volume.
bool ReadDefaultAudioVolume(int& percent, bool& muted) {
    IMMDeviceEnumerator* enumerator = nullptr;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
                                  CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
                                  reinterpret_cast<void**>(&enumerator));
    if (FAILED(hr) || !enumerator) return false;
    IMMDevice* device = nullptr;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (FAILED(hr) || !device)
        hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
    enumerator->Release();
    if (FAILED(hr) || !device) return false;
    IAudioEndpointVolume* volume = nullptr;
    hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL,
                          nullptr, reinterpret_cast<void**>(&volume));
    device->Release();
    if (FAILED(hr) || !volume) return false;
    float scalar = 0.0f;
    BOOL isMuted = FALSE;
    const bool ok = SUCCEEDED(volume->GetMasterVolumeLevelScalar(&scalar)) &&
                    SUCCEEDED(volume->GetMute(&isMuted));
    volume->Release();
    if (ok) {
        percent = static_cast<int>(std::lround(
            std::clamp(scalar, 0.0f, 1.0f) * 100.0f));
        muted = isMuted != FALSE;
    }
    return ok;
}

void RenderPopup();
void ResetHideTimerFor(DurationKind kind);

bool AdjustDefaultAudioWheel(int steps) {
    if (!steps) return false;
    IMMDeviceEnumerator* enumerator = nullptr;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        reinterpret_cast<void**>(&enumerator));
    if (FAILED(hr) || !enumerator) return false;
    IMMDevice* device = nullptr;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (FAILED(hr) || !device)
        hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
    enumerator->Release();
    if (FAILED(hr) || !device) return false;
    IAudioEndpointVolume* volume = nullptr;
    hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL,
        nullptr, reinterpret_cast<void**>(&volume));
    device->Release();
    if (FAILED(hr) || !volume) return false;
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
    volume->Release();
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
    IMMDeviceEnumerator* enumerator = nullptr;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        reinterpret_cast<void**>(&enumerator));
    if (FAILED(hr) || !enumerator) return false;
    IMMDevice* device = nullptr;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (FAILED(hr) || !device)
        hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
    enumerator->Release();
    if (FAILED(hr) || !device) return false;
    IAudioEndpointVolume* volume = nullptr;
    hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL,
        nullptr, reinterpret_cast<void**>(&volume));
    device->Release();
    if (FAILED(hr) || !volume) return false;
    hr = volume->SetMasterVolumeLevelScalar(percent / 100.0f, nullptr);
    float actual = percent / 100.0f;
    BOOL muted = FALSE;
    if (SUCCEEDED(hr)) {
        volume->GetMasterVolumeLevelScalar(&actual);
        volume->GetMute(&muted);
    }
    volume->Release();
    if (FAILED(hr)) return false;
    g_nativePercent = static_cast<int>(std::lround(
        std::clamp(actual, 0.0f, 1.0f) * 100.0f));
    g_nativeMuted = muted != FALSE;
    RenderPopup();
    return true;
}

// Draws independently constructed Fluent-style outline symbols in one shared
// 20 x 20 coordinate space. Both symbols use the same size, stroke width and
// visual anchor. Speaker detail follows the current volume level; both
// symbols are locally drawn vector paths, with no external glyph assets.
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
        constexpr float tau = 6.28318530718f;
        gfx.DrawEllipse(&pen, X(7.1f), Y(7.1f),
                        5.8f * unit, 5.8f * unit);
        for (int i = 0; i < 8; ++i) {
            const float angle = tau * static_cast<float>(i) / 8.0f;
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
void DrawVerticalPopup(Gdiplus::Graphics& gfx) {
    const bool light = IsLightTheme();
    const DWORD defaultBg = light ? 0xFAFAFC : 0x26262A;
    const DWORD defaultText = light ? 0x1C1C20 : 0xFAFAFB;
    const DWORD defaultTrack = light ? 0xDEDFE3 : 0x595A60;
    const DWORD backgroundRgb =
        g_backgroundMode.load() && g_validCustomBackground.load()
        ? g_customBackground.load() : defaultBg;
    const DWORD textRgb =
        g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : defaultText;
    const DWORD trackRgb =
        g_trackMode.load() && g_validCustomTrack.load()
        ? g_customTrack.load() : defaultTrack;
    const DWORD accentRgb =
        g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    const BYTE opacity = static_cast<BYTE>(
        (g_backgroundOpacity.load() * 255 + 50) / 100);
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
        percent = BrightnessPercent(&known);
        raw = g_visible.value;
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
        const float iconY = hasChevron
            ? (iconBottom - glyphSize / 2.0f)
            : (logicalH - 6.0f - edge - glyphSize / 2.0f);
        DrawUniformStatusIcon(gfx, foreground, centerX, iconY,
                              g_popupKind, percent, g_nativeMuted);
    }
    if (hasChevron)
        DrawExpandChevron(gfx, VerticalChevronX(),
                          VerticalChevronY(), foreground);
}
// Draws to premultiplied BGRA pixels, then sends them to UpdateLayeredWindow.

// --- Event notifications & shared animation state ---
void DrawText(Gdiplus::Graphics&, const std::wstring&, float, float, float,
              float, float, Gdiplus::Color, bool = false, bool = false);
void ShowPopupAnimated();
void RenderPopup();
void RenderPanel();
void MovePopupToDisplay(const BrightnessEvent&);
void ResetHideTimer(UINT milliseconds);
void ResetHideTimerFor(DurationKind kind);
void ClosePanel();
void UpdateArrowHitWindow();
void FlushNoticeBatch();
void ShowPanel();
void ShowNotice(std::wstring, std::wstring, DurationKind);

void ClearClipboardThumbnail() {
    if (g_clipboardThumbnail) {
        DeleteObject(g_clipboardThumbnail);
        g_clipboardThumbnail = nullptr;
    }
}

// Compact icon-and-state OSD for HardwareConfirmator categories that do not
// have a meaningful volume/brightness slider. Values come from the native
// display request itself, not from polling device state.
void DrawNativeEvent(Gdiplus::Graphics& gfx) {
    const bool light = IsLightTheme();
    const DWORD bgRgb = g_backgroundMode.load() && g_validCustomBackground.load()
        ? g_customBackground.load() : (light ? 0xFAFAFC : 0x26262A);
    const DWORD fgRgb = g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : (light ? 0x1C1C20 : 0xFAFAFB);
    const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    const Gdiplus::Color fg = ToGdiColor(fgRgb);
    const Gdiplus::Color muted(195, fg.GetR(), fg.GetG(), fg.GetB());
    const Gdiplus::Color accent = ToGdiColor(accentRgb);
    Gdiplus::GraphicsPath card;
    AddRoundedRect(card, 8.0f, 7.0f, 280.0f, 77.0f,
                   static_cast<float>(g_cornerRadius.load()));
    Gdiplus::SolidBrush background(ToGdiColor(bgRgb, static_cast<BYTE>(
        (g_backgroundOpacity.load() * 255 + 50) / 100)));
    gfx.FillPath(&background, &card);
    Gdiplus::GraphicsPath tile;
    AddRoundedRect(tile, 18.0f, 19.0f, 52.0f, 52.0f, 10.0f);
    Gdiplus::SolidBrush tileBrush(light ? Gdiplus::Color(255,235,236,240)
                                        : Gdiplus::Color(255,64,66,72));
    gfx.FillPath(&tileBrush, &tile);
    Gdiplus::Pen symbol(accent, 2.0f);
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
    DrawText(gfx, title, 84.0f, 21.0f, 190.0f, 25.0f, 15.0f, fg);
    DrawText(gfx, detail, 84.0f, 46.0f, 190.0f, 24.0f, 12.0f, muted);
}

void DrawNotification(Gdiplus::Graphics& gfx) {
    // OSD text is ephemeral and never written to disk or Windhawk logs.
    const bool light = IsLightTheme();
    const DWORD bg = g_backgroundMode.load() && g_validCustomBackground.load()
        ? g_customBackground.load() : light ? 0xFAFAFC : 0x26262A;
    const DWORD fgRgb = g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : light ? 0x1C1C20 : 0xFAFAFB;
    const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    const Gdiplus::Color fg = ToGdiColor(fgRgb);
    const Gdiplus::Color quiet(195, fg.GetR(), fg.GetG(), fg.GetB());
    // Image-first clipboard notice: the image occupies nearly the whole
    // canvas. Do not crop or distort portrait/panoramic clipboard images.
    if (g_clipboardThumbnail) {
        Gdiplus::GraphicsPath card;
        AddRoundedRect(card, 8.0f, 7.0f,
                       kClipboardImageCanvasW - 16.0f,
                       kClipboardImageCanvasH - 14.0f,
                       static_cast<float>(g_cornerRadius.load()));
        Gdiplus::SolidBrush background(ToGdiColor(bg,
            static_cast<BYTE>((g_backgroundOpacity.load() * 255 + 50) / 100)));
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
    Gdiplus::GraphicsPath body;
    AddRoundedRect(body, 8, 7, 280, 77,
                   static_cast<float>(g_cornerRadius.load()));
    Gdiplus::SolidBrush bgBrush(ToGdiColor(bg,
        static_cast<BYTE>((g_backgroundOpacity.load() * 255 + 50) / 100)));
    gfx.FillPath(&bgBrush, &body);
    const float iconX = 18.0f, iconY = 19.0f, iconW = 52.0f;
    Gdiplus::GraphicsPath tile;
    AddRoundedRect(tile, iconX, iconY, iconW, iconW, 10);
    Gdiplus::SolidBrush fill(light ? Gdiplus::Color(255,234,236,240)
                                    : Gdiplus::Color(255,66,68,72));
    gfx.FillPath(&fill, &tile);
    Gdiplus::SolidBrush mark(ToGdiColor(accentRgb));
    gfx.FillEllipse(&mark, iconX + 19.0f, iconY + 19.0f, 14.0f, 14.0f);
    DrawText(gfx, g_noticeTitle, 84, 22, 188, 25, 15, fg, false);
    DrawText(gfx, g_noticeBody, 84, 48, 188, 23, 12, quiet, false);
    if (g_noticeClickable) DrawText(gfx, L"›", 269, 34, 17, 20, 20, fg, true);
}

// Windows 11 layered GDI+ windows use UpdateLayeredWindow (premultiplied
// alpha). NEVER mix SetLayeredWindowAttributes on the popup/panel: doing so
// would break subsequent UpdateLayeredWindow calls.
void FinishPopupHide() {
    g_fadeActive = false;
    g_fadeAlpha = 255;
    if (g_popupWnd) ShowWindow(g_popupWnd, SW_HIDE);
    if (g_arrowWnd) ShowWindow(g_arrowWnd, SW_HIDE);
    g_arrowHovered = false;
    g_arrowPressed = false;
    if (g_arrowWnd && GetCapture() == g_arrowWnd) ReleaseCapture();
    if (g_barWheelWnd) ShowWindow(g_barWheelWnd, SW_HIDE);
    g_mainBarDragging = false;
    g_mainBarDragKind = -1;
    if (g_barWheelWnd && GetCapture() == g_barWheelWnd) ReleaseCapture();
    ClosePanel();
    ClearClipboardThumbnail();
    g_noticeTitle.clear();
    g_noticeBody.clear();
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
    ShowNotice(std::move(title), std::move(body),
        batch.category == NoticeCategory::Network ? DurationKind::Network : DurationKind::Devices);
}

void ShowNotice(std::wstring title, std::wstring body, DurationKind kind) {
    if (g_closing || !g_popupWnd) return;
    if (kind != DurationKind::Clipboard) ClearClipboardThumbnail();
    ClosePanel();
    g_popupKind = PopupKind::Notification;
    g_noticeTitle = std::move(title);
    g_noticeBody = std::move(body);
    BrightnessEvent ev{};
    MovePopupToDisplay(ev);
    SetNoticeHitTesting(g_noticeClickable);
    ShowPopupAnimated();
    UpdateArrowHitWindow();
    ResetHideTimerFor(kind);
}

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
    ShowNotice(std::move(title), std::move(body), DurationKind::Clipboard);
}

// Event-based USB interface notifications, Bluetooth classic radio HCI
// notifications and OS aggregate network connectivity hints.
constexpr GUID kUsbDeviceInterface = {0xa5dcbf10,0x6530,0x11d2,
    {0x90,0x1f,0x00,0xc0,0x4f,0xb9,0x51,0xed}};
constexpr GUID kBtHciEvent = {0xfc240062,0x1541,0x49be,
    {0xb4,0x63,0x84,0xc4,0xdc,0xd7,0xbf,0x7f}};

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

std::vector<std::pair<std::string, NetInterfaceState>> GetNetworkSnapshot();
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

    g_bluetoothDll = LoadLibraryExW(L"bthprops.cpl", nullptr,
                                    LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!g_bluetoothDll) return;
    using FirstRadio = HBLUETOOTH_RADIO_FIND (WINAPI*)(
        const BLUETOOTH_FIND_RADIO_PARAMS*, HANDLE*);
    using NextRadio = BOOL (WINAPI*)(HBLUETOOTH_RADIO_FIND, HANDLE*);
    using CloseFind = BOOL (WINAPI*)(HBLUETOOTH_RADIO_FIND);
    const auto first = reinterpret_cast<FirstRadio>(
        GetProcAddress(g_bluetoothDll, "BluetoothFindFirstRadio"));
    const auto next = reinterpret_cast<NextRadio>(
        GetProcAddress(g_bluetoothDll, "BluetoothFindNextRadio"));
    const auto finish = reinterpret_cast<CloseFind>(
        GetProcAddress(g_bluetoothDll, "BluetoothFindRadioClose"));
    if (!first || !next || !finish) return;
    BLUETOOTH_FIND_RADIO_PARAMS search{};
    search.dwSize = sizeof(search);
    HANDLE radio = nullptr;
    HBLUETOOTH_RADIO_FIND iteration = first(&search, &radio);
    if (!iteration) return;
    do {
        if (radio && radio != INVALID_HANDLE_VALUE) {
            DEV_BROADCAST_HANDLE filter{};
            filter.dbch_size = sizeof(filter);
            filter.dbch_devicetype = DBT_DEVTYP_HANDLE;
            filter.dbch_handle = radio;
            HDEVNOTIFY notify = RegisterDeviceNotificationW(
                g_receiveWnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE);
            if (notify) g_bluetoothNotifications.push_back(notify);
            g_bluetoothRadios.push_back(radio);
        }
        radio = nullptr;
    } while (next(iteration, &radio));
    finish(iteration);
}

void StopDeviceEvents() {
    if (g_usbNotification) UnregisterDeviceNotification(g_usbNotification);
    g_usbNotification = nullptr;
    for (auto notify : g_bluetoothNotifications) UnregisterDeviceNotification(notify);
    g_bluetoothNotifications.clear();
    for (HANDLE radio : g_bluetoothRadios) CloseHandle(radio);
    g_bluetoothRadios.clear();
    if (g_bluetoothDll) FreeLibrary(g_bluetoothDll);
    g_bluetoothDll = nullptr;
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

std::wstring BluetoothDeviceLabel(HANDLE radio, ULONGLONG address) {
    using GetBtInfo = DWORD (WINAPI*)(HANDLE, BLUETOOTH_DEVICE_INFO*);
    if (g_bluetoothDll) {
        auto getInfo = reinterpret_cast<GetBtInfo>(
            GetProcAddress(g_bluetoothDll, "BluetoothGetDeviceInfo"));
        if (getInfo) {
            BLUETOOTH_DEVICE_INFO info{};
            info.dwSize = sizeof(info);
            info.Address.ullLong = address;
            if (getInfo(radio, &info) == ERROR_SUCCESS && info.szName[0])
                return std::wstring(info.szName,
                    std::min<size_t>(wcslen(info.szName), 80));
        }
    }
    return Tr(OsdText::BluetoothDevice);
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
    if (header->dbch_devicetype == DBT_DEVTYP_HANDLE &&
        type == DBT_CUSTOMEVENT && g_showBluetoothEvents.load() &&
        header->dbch_size >= offsetof(DEV_BROADCAST_HANDLE, dbch_data) +
                             sizeof(BTH_HCI_EVENT_INFO)) {
        const auto* dev = reinterpret_cast<const DEV_BROADCAST_HANDLE*>(value);
        if (!IsEqualGUID(dev->dbch_eventguid, kBtHciEvent)) return false;
        BTH_HCI_EVENT_INFO event{};
        memcpy(&event, dev->dbch_data, sizeof(event));
        if (event.connectionType != 1 /* HCI_CONNECTION_TYPE_ACL */) return true;
        const DWORD now = GetTickCount();
        const ULONGLONG address = event.bthAddress;
        const bool connected = event.connected != 0;
        const auto existing = g_btPrevious.find(address);
        if (existing != g_btPrevious.end() &&
            existing->second.connected == connected &&
            now - existing->second.when < 700) return true;
        if (g_btPrevious.size() >= 64) g_btPrevious.clear();
        g_btPrevious[address] = {connected, now};
        AddNoticeEvent(NoticeCategory::Bluetooth, connected ?
            NoticeAction::Connected : NoticeAction::Disconnected,
            std::to_wstring(address), BluetoothDeviceLabel(dev->dbch_handle, address));
        return true;
    }
    return false;
}

// No DDC or monitor I/O, timers or extra worker threads in this renderer.
// Forward declarations for the new UI renderer.
void DrawHorizontalVolume(Gdiplus::Graphics& gfx);
void DrawLockStatus(Gdiplus::Graphics& gfx);
void DrawNotification(Gdiplus::Graphics& gfx);
void DrawExpandChevron(Gdiplus::Graphics& gfx, float x, float y,
                       Gdiplus::Color color);

void RenderPopup() {
    if (!g_popupWnd || !g_gdiplusToken) return;
    HDC screen = GetDC(nullptr);
    if (!screen) return;
    HDC memory = CreateCompatibleDC(screen);
    if (!memory) { ReleaseDC(nullptr, screen); return; }

    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = g_width;
    bi.bmiHeader.biHeight = -g_height;  // top-down
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(screen, &bi, DIB_RGB_COLORS,
                                      &pixels, nullptr, 0);
    if (bitmap && pixels) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        {
            Gdiplus::Bitmap surface(g_width, g_height, g_width * 4,
                                    PixelFormat32bppPARGB,
                                    static_cast<BYTE*>(pixels));
            Gdiplus::Graphics gfx(&surface);
            gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
            gfx.Clear(Gdiplus::Color(0, 0, 0, 0));
            gfx.ScaleTransform(g_scale, g_scale);
            if (g_popupKind == PopupKind::LockStatus) {
                DrawLockStatus(gfx);
            } else if (g_popupKind == PopupKind::Notification) {
                DrawNotification(gfx);
            } else if (g_popupKind == PopupKind::NativeEvent) {
                DrawNativeEvent(gfx);
            } else if (g_verticalVolumeBrightness.load(std::memory_order_relaxed)) {
                DrawVerticalPopup(gfx);
            } else if (g_popupKind == PopupKind::NativeVolume) {
                DrawHorizontalVolume(gfx);
            } else {

            const bool light = IsLightTheme();
            const DWORD baseBackground = light ? 0xFAFAFC : 0x26262A;
            const DWORD baseText = light ? 0x1C1C20 : 0xFAFAFB;
            const DWORD baseTrack = light ? 0xDEDFE3 : 0x595A60;
            const DWORD backgroundRgb =
                g_backgroundMode.load() && g_validCustomBackground.load()
                ? g_customBackground.load() : baseBackground;
            const DWORD textRgb =
                g_textMode.load() && g_validCustomText.load()
                ? g_customText.load() : baseText;
            const DWORD trackRgb =
                g_trackMode.load() && g_validCustomTrack.load()
                ? g_customTrack.load() : baseTrack;
            const DWORD accentRgb =
                g_accentMode.load() && g_validCustomAccent.load()
                ? g_customAccent.load() : SystemAccentRgb();
            const BYTE backgroundAlpha = static_cast<BYTE>(
                (g_backgroundOpacity.load() * 255 + 50) / 100);
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
            constexpr float tau = 6.28318530718f;
            for (int i = 0; i < 8; ++i) {
                const float a = tau * i / 8.0f;
                const float sx = std::cos(a), sy = std::sin(a);
                gfx.DrawLine(&sunPen, 50.5f + sx * 9.6f,
                             centerY + sy * 9.6f,
                             50.5f + sx * 12.0f,
                             centerY + sy * 12.0f);
            }

            }
            bool known = false;
            int percent = 0;
            DWORD rawBrightness = g_visible.value;
            if (g_popupKind == PopupKind::NativeBrightness) {
                known = g_nativePercentKnown;
                percent = std::clamp(g_nativePercent, 0, 100);
                rawBrightness = static_cast<DWORD>(std::max(g_nativePercent, 0));
            } else {
                percent = BrightnessPercent(&known);
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
        SIZE size{g_width, g_height};
        POINT origin{0, 0};
        BLENDFUNCTION blend{AC_SRC_OVER, 0, static_cast<BYTE>(g_fadeAlpha), AC_SRC_ALPHA};
        if (!UpdateLayeredWindow(g_popupWnd, screen, nullptr, &size,
                                 memory, &origin, 0, &blend, ULW_ALPHA)) {
            Wh_Log(L"UpdateLayeredWindow failed: %lu", GetLastError());
        }
        SelectObject(memory, previous);
        DeleteObject(bitmap);
    }
    DeleteDC(memory);
    ReleaseDC(nullptr, screen);
}

void MovePopupToDisplay(const BrightnessEvent& ev) {
    FindDisplay f{};
    wcscpy_s(f.name, ev.device);
    if (f.name[0]) EnumDisplayMonitors(nullptr, nullptr, FindDisplayCallback,
                                       reinterpret_cast<LPARAM>(&f));
    if (!f.monitor)
        f.monitor = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(f.monitor, &mi)) return;
    UINT dpiX = 96, dpiY = 96;
    if (GetDpiForMonitor(f.monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY) != S_OK)
        dpiX = 96;
    // Apply an independent user-selected size factor after monitor DPI.
    // The renderer keeps the same Win11-inspired vector geometry.
    const float dpiScale = std::clamp(dpiX / 96.0f, 0.75f, 3.0f);
    const float sizeScale =
        g_ddcSizePercent.load(std::memory_order_relaxed) / 100.0f;
    g_scale = dpiScale * sizeScale;
    const bool vertical = g_verticalVolumeBrightness.load(
        std::memory_order_relaxed);
    g_width = static_cast<int>(std::lround(
        (g_popupKind == PopupKind::LockStatus ? 178 :
         g_popupKind == PopupKind::NativeEvent ? 296 :
         g_popupKind == PopupKind::Notification ?
             (g_clipboardThumbnail ? kClipboardImageCanvasW : 296.0f) :
         MainLogicalWidth()) * g_scale));
    g_height = static_cast<int>(std::lround(
        (g_popupKind == PopupKind::LockStatus ? 66 :
         g_popupKind == PopupKind::NativeEvent ? 92 :
         g_popupKind == PopupKind::Notification ?
             (g_clipboardThumbnail ? kClipboardImageCanvasH : 92.0f) :
         MainLogicalHeight()) * g_scale));
    const RECT& r = mi.rcWork;
    const int margin = static_cast<int>(std::lround(24.0f * dpiScale));
    const int centerX = r.left + ((r.right - r.left) - g_width) / 2;
    const int centerY = r.top + ((r.bottom - r.top) - g_height) / 2;
    const int leftX = r.left + margin;
    const int rightX = r.right - g_width - margin;
    const int topY = r.top + margin;
    const int bottomY = r.bottom - g_height - margin;
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
    // Avoid accidentally placing the entire popup outside its display.
    x = std::clamp<int>(x, r.left, std::max(r.left, r.right - g_width));
    y = std::clamp<int>(y, r.top, std::max(r.top, r.bottom - g_height));
    SetWindowPos(g_popupWnd, HWND_TOPMOST, x, y, g_width, g_height,
                 SWP_NOACTIVATE);
}


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
    constexpr GUID clsid = {0x4590f811, 0x1d3a, 0x11d0,
        {0x89,0x1f,0x00,0xaa,0x00,0x4b,0x2e,0x24}};
    constexpr GUID iid = {0xdc12a687, 0x737f, 0x11cf,
        {0x88,0x4d,0x00,0xaa,0x00,0x4b,0x2e,0x24}};
    if (FAILED(CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER,
            iid, reinterpret_cast<void**>(&locator))) || !locator)
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
        BrightnessWheelTask task{};
        bool pending = false;
        AcquireSRWLockExclusive(&g_wheelWriteLock);
        if (g_wheelWriteHasPending) {
            task = g_wheelWritePending;
            g_wheelWriteHasPending = false;
            pending = true;
        }
        ReleaseSRWLockExclusive(&g_wheelWriteLock);
        if (!pending || task.generation != g_wheelWriteLatest.load()) continue;
        const bool success = task.native ?
            (comReady && WriteNativeBrightnessWmi(
                static_cast<BYTE>(std::clamp(task.value, 0, 100))))
            : WriteExternalBrightnessDdc(task);
        HWND receiver = g_receiveWnd;
        if (receiver && !g_closing.load())
            PostMessageW(receiver, kBrightnessWheelResultMessage,
                static_cast<WPARAM>(task.generation),
                static_cast<LPARAM>((success ? 1 : 0) |
                                    (task.native ? 2 : 0)));
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
        const DWORD next = g_visible.minimum + static_cast<DWORD>(
            std::lround(static_cast<double>(range) * percent / 100.0));
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
    const float fraction = g_verticalVolumeBrightness.load()
        ? (track.y + track.h - y) / track.h
        : (x - track.x) / track.w;
    const int percent = std::clamp(static_cast<int>(std::lround(
        std::clamp(fraction, 0.0f, 1.0f) * 100.0f)), 0, 100);
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
    g_barWheelRemainder += delta;
    const int steps = g_barWheelRemainder / WHEEL_DELTA;
    g_barWheelRemainder %= WHEEL_DELTA;
    if (!steps) return;
    if (g_popupKind == PopupKind::NativeVolume)
        AdjustDefaultAudioWheel(steps);
    else if (g_popupKind == PopupKind::NativeBrightness ||
             g_popupKind == PopupKind::DdcBrightness)
        AdjustBrightnessWheel(steps);
}

// -- SMTC: lean WinRT ABI implementation. Avoid the enormous C++/WinRT
// projection headers in the Windhawk/Clang compile unit. All calls occur on
// this private MTA worker and are bounded. No UI or DDCCI calls occur here.
// The interface IIDs and vtable slots follow public Windows Runtime metadata.
// WinRT IInspectable adds GetIids/GetRuntimeClassName/GetTrustLevel after
// IUnknown's three entries, so class-specific methods begin at slot 6.
namespace smtc_abi {
using RawHString = void*;
constexpr GUID kManagerStatics = {0x2050c4ee,0x11a0,0x57de,{0xae,0xd7,0xc9,0x7c,0x70,0x33,0x82,0x45}};
constexpr GUID kIAsyncInfo = {0x00000036,0,0,{0xc0,0,0,0,0,0,0,0x46}};
constexpr GUID kIBufferFactory = {0x71af914d,0xc10f,0x484b,{0xbc,0x50,0x14,0xbc,0x62,0x3b,0x3a,0x27}};
constexpr GUID kIBufferAccess = {0x905a0fef,0xbc53,0x11df,{0x8c,0x49,0,0x1e,0x4f,0xc6,0x86,0xda}};
constexpr GUID kInputStream = {0x905a0fe2,0xbc53,0x11df,{0x8c,0x49,0,0x1e,0x4f,0xc6,0x86,0xda}};
constexpr GUID kRandomStream = {0x905a0fe1,0xbc53,0x11df,{0x8c,0x49,0,0x1e,0x4f,0xc6,0x86,0xda}};

// Only Windows ABI method invocations (no synthesized WinRT generic types).
template <typename... Args>
HRESULT Call(IUnknown* obj, size_t index, Args... args) {
    if (!obj) return E_POINTER;
    auto table = *reinterpret_cast<void***>(obj);
    using Method = HRESULT(STDMETHODCALLTYPE*)(void*, Args...);
    return reinterpret_cast<Method>(table[index])(obj, args...);
}

using CPtr = Microsoft::WRL::ComPtr<IUnknown>;
using RoInit = HRESULT(WINAPI*)(int);
using RoUninit = void(WINAPI*)();
using RoFactory = HRESULT(WINAPI*)(RawHString, REFIID, void**);
using CreateString = HRESULT(WINAPI*)(PCWSTR, UINT32, RawHString*);
using DeleteString = HRESULT(WINAPI*)(RawHString);
using GetRawString = PCWSTR(WINAPI*)(RawHString, UINT32*);

struct Runtime {
    HMODULE dll = nullptr;
    RoUninit uninit = nullptr;
    RoFactory factory = nullptr;
    CreateString make = nullptr;
    DeleteString remove = nullptr;
    GetRawString raw = nullptr;
    bool initialized = false;

    bool Init() {
        dll = LoadLibraryExW(L"combase.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!dll) return false;
        auto init = reinterpret_cast<RoInit>(GetProcAddress(dll, "RoInitialize"));
        uninit = reinterpret_cast<RoUninit>(GetProcAddress(dll, "RoUninitialize"));
        factory = reinterpret_cast<RoFactory>(GetProcAddress(dll, "RoGetActivationFactory"));
        make = reinterpret_cast<CreateString>(GetProcAddress(dll, "WindowsCreateString"));
        remove = reinterpret_cast<DeleteString>(GetProcAddress(dll, "WindowsDeleteString"));
        raw = reinterpret_cast<GetRawString>(GetProcAddress(dll, "WindowsGetStringRawBuffer"));
        if (!init || !uninit || !factory || !make || !remove || !raw)
            return false;
        HRESULT hr = init(1); // RO_INIT_MULTITHREADED
        initialized = SUCCEEDED(hr);
        return initialized;
    }
    ~Runtime() {
        if (initialized && uninit) uninit();
        if (dll) FreeLibrary(dll);
    }

    std::wstring Text(RawHString h) {
        if (!h) return {};
        UINT32 n = 0;
        PCWSTR p = raw(h, &n);
        if (!p) return {};
        // Media metadata is untrusted. Limit allocations independently of
        // the advertised HSTRING length; avoid cutting a UTF-16 surrogate.
        constexpr UINT32 kMaxMediaTextChars = 4096;
        UINT32 length = std::min(n, kMaxMediaTextChars);
        if (length < n && length &&
            p[length - 1] >= 0xD800 && p[length - 1] <= 0xDBFF)
            --length;
        return std::wstring(p, length);
    }

    HRESULT Activate(PCWSTR className, REFIID iid, CPtr& result) {
        RawHString name = nullptr;
        HRESULT hr = make(className, static_cast<UINT32>(wcslen(className)), &name);
        if (FAILED(hr)) return hr;
        IUnknown* object = nullptr;
        hr = factory(name, iid, reinterpret_cast<void**>(&object));
        remove(name);
        if (SUCCEEDED(hr)) result.Attach(object);
        else if (object) object->Release();
        return hr;
    }
};

// WinRT IAsyncInfo::Status: Started=0, Completed=1, Canceled=2, Error=3.
// Poll only within the on-demand worker, not on Explorer's UI thread.
HRESULT Wait(CPtr& operation, DWORD timeout = 1800) {
    if (!operation) return E_POINTER;
    CPtr info;
    HRESULT hr = operation->QueryInterface(kIAsyncInfo,
        reinterpret_cast<void**>(info.GetAddressOf()));
    if (FAILED(hr)) return hr;
    ULONGLONG start = GetTickCount64();
    for (;;) {
        INT32 status = 0;
        hr = Call(info.Get(), 7, &status); // IAsyncInfo::get_Status
        if (FAILED(hr)) return hr;
        if (status == 1) return S_OK;
        if (status == 2 || status == 3) return E_FAIL;
        if (g_mediaStop.load(std::memory_order_relaxed))
            return HRESULT_FROM_WIN32(ERROR_CANCELLED);
        if (GetTickCount64() - start >= timeout)
            return HRESULT_FROM_WIN32(WAIT_TIMEOUT);
        Sleep(15);
    }
}

HRESULT GetAsyncObject(CPtr& operation, CPtr& result,
                       size_t resultsSlot = 8) {
    HRESULT hr = Wait(operation);
    if (FAILED(hr)) return hr;
    IUnknown* out = nullptr;
    hr = Call(operation.Get(), resultsSlot, &out);
    if (SUCCEEDED(hr)) result.Attach(out);
    else if (out) out->Release();
    return hr;
}

void RequestMediaAction(CPtr& session, const MediaCommand& command) {
    if (command.action == 4) {
        // WinRT IGlobalSystemMediaTransportControlsSession vtable slot 24:
        // TryChangePlaybackPositionAsync(INT64 requestedPlaybackPosition).
        // Honor the player's seek capability: some streams have a timeline
        // without permitting user-initiated position changes.
        CPtr info, controls;
        BOOLEAN allowed = FALSE;
        if (FAILED(Call(session.Get(), 9, info.GetAddressOf())) || !info ||
            FAILED(Call(info.Get(), 6, controls.GetAddressOf())) || !controls ||
            FAILED(Call(controls.Get(), 20, &allowed)) || !allowed)
            return;
        CPtr seekTask;
        if (SUCCEEDED(Call(session.Get(), 24, command.position,
                           seekTask.GetAddressOf())) && seekTask) {
            if (SUCCEEDED(Wait(seekTask, 1800))) {
                BOOLEAN completed = FALSE;
                (void)Call(seekTask.Get(), 8, &completed);
            }
        }
        return;
    }
    const int action = command.action;
    // GlobalSystemMediaTransportControlsSession vtable:
    // 16=TrySkipNextAsync, 17=TrySkipPreviousAsync,
    // 20=TryTogglePlayPauseAsync, 10/11=TryPlay/PauseAsync.
    size_t slot = action == 1 ? 17 : action == 3 ? 16 : 20;
    if (action == 2) {
        CPtr info;
        if (SUCCEEDED(Call(session.Get(), 9, info.GetAddressOf())) && info) {
            int status = 0;
            if (SUCCEEDED(Call(info.Get(), 7, &status)))
                (void)status;
            // Fallback to toggle if player supports it; failed commands
            // simply leave the current media session unchanged.
            CPtr controls;
            if (SUCCEEDED(Call(info.Get(), 6, controls.GetAddressOf())) && controls) {
                BOOLEAN supported = 0;
                if (FAILED(Call(controls.Get(), 16, &supported)) || !supported)
                    slot = status == 4 ? 11 : 10;
            }
        }
    }
    CPtr task;
    if (SUCCEEDED(Call(session.Get(), slot, task.GetAddressOf())) && task) {
        if (SUCCEEDED(Wait(task, 1800))) {
            BOOLEAN succeeded = 0;
            (void)Call(task.Get(), 8, &succeeded); // IAsyncOperation<bool>::GetResults
        }
    }
}

// GlobalSystemMediaTransportControlsSession::GetTimelineProperties is slot
// 8; GlobalSystemMediaTransportControlsSessionTimelineProperties is a WinRT
// IInspectable whose StartTime/EndTime/Position/LastUpdatedTime getters are
// slots 6/7/10/11. Foundation TimeSpan/DateTime are signed 100-ns integers.
void ReadTimeline(CPtr& session, MediaSnapshot& snapshot) {
    CPtr timeline;
    if (FAILED(Call(session.Get(), 8, timeline.GetAddressOf())) || !timeline)
        return;
    INT64 start = 0, end = 0, pos = 0, updated = 0;
    if (FAILED(Call(timeline.Get(), 6, &start)) ||
        FAILED(Call(timeline.Get(), 7, &end)) ||
        FAILED(Call(timeline.Get(), 10, &pos)) || end <= start)
        return; // Live streams / unknown duration must not show invented time.
    // Clamp nonsensical values without dividing by a zero/negative range.
    if (end - start <= 0) return;
    pos = std::clamp(pos, start, end);
    if (snapshot.playing && SUCCEEDED(Call(timeline.Get(), 11, &updated)) &&
        updated > 0) {
        FILETIME now{};
        GetSystemTimeAsFileTime(&now);
        ULARGE_INTEGER absolute{};
        absolute.LowPart = now.dwLowDateTime;
        absolute.HighPart = now.dwHighDateTime;
        constexpr INT64 kMaxTimeLag = INT64(24) * 60 * 60 * 10000000;
        const INT64 now100ns = static_cast<INT64>(absolute.QuadPart);
        if (now100ns >= updated && now100ns - updated <= kMaxTimeLag)
            pos += std::min(end - pos, now100ns - updated);
    }
    snapshot.hasTimeline = true;
    snapshot.timelineStart = start;
    snapshot.timelineEnd = end;
    snapshot.timelinePosition = pos;
    snapshot.timelineObservedTick = GetTickCount64();
}

// Read artwork through ABI IBuffer/IBufferByteAccess rather than importing
// Windows.Storage.Streams C++/WinRT projections. Limited to 1 MiB.
void ReadArtwork(Runtime& api, IUnknown* thumbnail,
                 std::vector<BYTE>& output) {
    if (!thumbnail || !g_showMediaArtwork.load(std::memory_order_relaxed)) return;
    CPtr openAsync;
    if (FAILED(Call(thumbnail, 6, openAsync.GetAddressOf())) || !openAsync) return;
    CPtr stream;
    if (FAILED(GetAsyncObject(openAsync, stream)) || !stream) return;
    CPtr randomStream;
    if (FAILED(stream->QueryInterface(kRandomStream,
            reinterpret_cast<void**>(randomStream.GetAddressOf()))) || !randomStream) return;
    UINT64 length = 0;
    if (FAILED(Call(randomStream.Get(), 6, &length))) return; // Size
    constexpr UINT32 kMaxArtwork = 1024u * 1024u;
    // Reject oversize files rather than decoding a truncated stream.
    if (!length || length > kMaxArtwork) return;
    UINT32 count = static_cast<UINT32>(length);
    CPtr factory;
    if (FAILED(api.Activate(L"Windows.Storage.Streams.Buffer", kIBufferFactory, factory)))
        return;
    CPtr buffer;
    if (FAILED(Call(factory.Get(), 6, count, buffer.GetAddressOf())) || !buffer)
        return; // IBufferFactory::Create
    CPtr input;
    if (FAILED(stream->QueryInterface(kInputStream,
            reinterpret_cast<void**>(input.GetAddressOf()))) || !input) return;
    CPtr readAsync;
    if (FAILED(Call(input.Get(), 6, buffer.Get(), count, UINT32(0),
                    readAsync.GetAddressOf())) || !readAsync) return;
    CPtr bytes;
    if (FAILED(GetAsyncObject(readAsync, bytes, 10)) || !bytes) return;
    UINT32 actual = 0;
    if (FAILED(Call(bytes.Get(), 7, &actual)) || !actual || actual > kMaxArtwork)
        return;
    CPtr access;
    if (FAILED(bytes->QueryInterface(kIBufferAccess,
            reinterpret_cast<void**>(access.GetAddressOf()))) || !access) return;
    BYTE* ptr = nullptr;
    if (SUCCEEDED(Call(access.Get(), 3, &ptr)) && ptr)
        output.assign(ptr, ptr + actual);
}
} // namespace smtc_abi

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
    using namespace smtc_abi;
    Runtime api;
    if (!api.Init()) {
        Wh_Log(L"SMTC WinRT runtime unavailable");
        return 0;
    }
    CPtr statics;
    HRESULT hr = api.Activate(
        L"Windows.Media.Control.GlobalSystemMediaTransportControlsSessionManager",
        kManagerStatics, statics);
    if (FAILED(hr) || !statics) {
        Wh_Log(L"SMTC activation factory unavailable: 0x%08lX",
               static_cast<unsigned long>(hr));
        return 0;
    }
    CPtr managerAsync;
    hr = Call(statics.Get(), 6, managerAsync.GetAddressOf()); // RequestAsync
    CPtr manager;
    if (FAILED(hr) || !managerAsync ||
        FAILED(GetAsyncObject(managerAsync, manager)) || !manager) {
        Wh_Log(L"SMTC manager initialization failed");
        return 0;
    }
    MediaSnapshot lastSnapshot;
    while (WaitForSingleObject(g_mediaWake, INFINITE) == WAIT_OBJECT_0) {
        if (g_mediaStop.load()) break;
        CPtr session;
        HRESULT getSessionHr = Call(manager.Get(), 6, session.GetAddressOf());
        if (FAILED(getSessionHr)) {
            Wh_Log(L"SMTC GetCurrentSession failed: 0x%08lX",
                   static_cast<unsigned long>(getSessionHr));
            continue;
        }
        std::vector<MediaCommand> commands;
        AcquireSRWLockExclusive(&g_mediaCommandLock);
        commands.swap(g_mediaCommands);
        ReleaseSRWLockExclusive(&g_mediaCommandLock);
        if (session) {
            for (const auto& command : commands) RequestMediaAction(session, command);
        }
        MediaSnapshot snapshot;
        if (session) {
            snapshot.available = true;
            CPtr info;
            if (SUCCEEDED(Call(session.Get(), 9, info.GetAddressOf())) && info) {
                int status = 0;
                if (SUCCEEDED(Call(info.Get(), 7, &status)))
                    snapshot.playing = status == 4;
                CPtr controls;
                if (SUCCEEDED(Call(info.Get(), 6, controls.GetAddressOf())) && controls) {
                    BOOLEAN flag = 0;
                    if (SUCCEEDED(Call(controls.Get(), 13, &flag))) snapshot.canPrevious = flag != 0;
                    if (SUCCEEDED(Call(controls.Get(), 12, &flag))) snapshot.canNext = flag != 0;
                    if (SUCCEEDED(Call(controls.Get(), 16, &flag))) snapshot.canToggle = flag != 0;
                    if (SUCCEEDED(Call(controls.Get(), 20, &flag))) snapshot.canSeek = flag != 0;
                    if (!snapshot.canToggle && SUCCEEDED(Call(controls.Get(), 6, &flag))) snapshot.canToggle = flag != 0;
                    if (!snapshot.canToggle && SUCCEEDED(Call(controls.Get(), 7, &flag))) snapshot.canToggle = flag != 0;
                }
            }
            CPtr propsAsync;
            if (SUCCEEDED(Call(session.Get(), 7, propsAsync.GetAddressOf())) && propsAsync) {
                CPtr props;
                if (SUCCEEDED(GetAsyncObject(propsAsync, props)) && props) {
                    RawHString title = nullptr, artist = nullptr;
                    if (SUCCEEDED(Call(props.Get(), 6, &title))) {
                        snapshot.title = api.Text(title);
                        if (title) api.remove(title);
                    }
                    if (SUCCEEDED(Call(props.Get(), 9, &artist))) {
                        snapshot.artist = api.Text(artist);
                        if (artist) api.remove(artist);
                    }
                    if (g_showMediaArtwork.load() &&
                        snapshot.title == lastSnapshot.title &&
                        snapshot.artist == lastSnapshot.artist &&
                        !lastSnapshot.artwork.empty()) {
                        snapshot.artwork = lastSnapshot.artwork;
                    } else if (g_showMediaArtwork.load()) {
                        CPtr thumbnail;
                        if (SUCCEEDED(Call(props.Get(), 15, thumbnail.GetAddressOf())) && thumbnail)
                            ReadArtwork(api, thumbnail.Get(), snapshot.artwork);
                    }
                }
            }
            ReadTimeline(session, snapshot);
        }
        lastSnapshot = snapshot;
        AcquireSRWLockExclusive(&g_mediaLock);
        g_mediaPending = std::move(snapshot);
        ReleaseSRWLockExclusive(&g_mediaLock);
        HWND receiver = FindWindowExW(HWND_MESSAGE, nullptr, kWindowClass, nullptr);
        if (receiver) PostMessageW(receiver, kMediaUpdateMessage, 0, 0);
    }
    return 0;
}

// -- Interactive Core Audio session mixer, created/refreshed only on demand.
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

void RefreshMixer() {
    CleanupMixerIcons();
    g_mixerEntries.clear();
    g_mixerMaster.Reset();
    g_mixerMasterLevel = 0;
    g_mixerMasterMuted = false;
    IMMDeviceEnumerator* enumerator = nullptr;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        reinterpret_cast<void**>(&enumerator));
    if (FAILED(hr) || !enumerator) return;
    IMMDevice* device = nullptr;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    enumerator->Release();
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

// Draw tiny Fluent-like transport controls at one fixed visual scale.
// Glyphs use the exact same user scale as the button's hit box. The default
// 125% produces 40px logical circles and ~16px transport symbols.
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

void DrawPanelCard(Gdiplus::Graphics& gfx, float width, float height,
                   bool alignToMainVolume = false) {
    bool light = IsLightTheme();
    DWORD bg = g_backgroundMode.load() && g_validCustomBackground.load()
               ? g_customBackground.load() : light ? 0xFAFAFC : 0x26262A;
    BYTE alpha = static_cast<BYTE>((g_backgroundOpacity.load() * 255 + 50) / 100);
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
        Gdiplus::Pen border(light ? Gdiplus::Color(170, 190, 190, 195)
                                  : Gdiplus::Color(170, 90, 90, 97), .8f);
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

    // Reserve space for THREE full-size controls and a minimum metadata
    // column. Its required width changes with artwork-relative control size.
    // Binary search is monotonic: larger artwork also means larger buttons.
    auto controlScale = [](float art) {
        return std::clamp(art / 125.0f, 0.78f, 1.45f);
    };
    auto fits = [&](float art) {
        const float radius = baseRadius * controlScale(art);
        const float infoWidth = std::max(86.0f, 6.0f * radius + 8.0f);
        return art + infoWidth <= usableWidth;
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
                                  std::max(1.0f, (textWidth - 8.0f) / 6.0f));
    const float leftButtonX = textX + radius;
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
        if (enabled[i] && dx * dx + dy * dy <=
            layout.buttonRadius * layout.buttonRadius) return i;
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
    const DWORD rgb = g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : light ? 0x1C1C20 : 0xFAFAFB;
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
        const DWORD trackRgb = g_trackMode.load() && g_validCustomTrack.load()
            ? g_customTrack.load() : light ? 0xDEDFE3 : 0x595A60;
        const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
            ? g_customAccent.load() : SystemAccentRgb();
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
        Gdiplus::GraphicsPath circle;
        AddRoundedRect(circle, layout.controlsX[i] - radius,
                       layout.controlsY - radius,
                       radius * 2, radius * 2, radius);
        const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
            ? g_customAccent.load() : SystemAccentRgb();
        Gdiplus::SolidBrush fill(pressed || tapped
            ? ToGdiColor(accentRgb, pressed ? 96 : static_cast<BYTE>(
                (kMediaFeedbackMs - (now - g_mediaFeedbackTick)) * 85 /
                 kMediaFeedbackMs))
            : (light ? Gdiplus::Color(255,233,234,238)
                     : Gdiplus::Color(255,67,68,74)));
        gfx.FillPath(&fill, &circle);
        if (tapped) {
            const float t = static_cast<float>(now - g_mediaFeedbackTick) /
                static_cast<float>(kMediaFeedbackMs);
            Gdiplus::Pen ring(ToGdiColor(accentRgb, static_cast<BYTE>(
                (1.0f - t) * 145.0f)), 1.6f);
            gfx.DrawEllipse(&ring, layout.controlsX[i] - radius * (0.75f + 0.3f*t),
                layout.controlsY - radius * (0.75f + 0.3f*t),
                2.0f * radius * (0.75f + 0.3f*t),
                2.0f * radius * (0.75f + 0.3f*t));
        }
        DrawMediaControl(gfx, layout.controlsX[i], layout.controlsY,
                         i + 1, g_mediaCurrent.playing,
                         allowed[i] ? fg : quiet,
                         layout.contentScale * (pressed ? 0.90f : 1.0f));
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
        g_textMode.load() && g_validCustomText.load() ? g_customText.load()
        : (light ? 0x1C1C20 : 0xFAFAFB));
    DrawText(gfx, Tr(OsdText::EventDetails), 16, 10, 290, 24, 15, fg);
    const int visible = NoticeVisibleRows();
    const int maxStart = std::max<int>(0, static_cast<int>(g_noticeDetails.size()) - visible);
    g_noticeScroll = std::clamp(g_noticeScroll, 0, maxStart);
    for (int i = 0; i < visible && i + g_noticeScroll < static_cast<int>(g_noticeDetails.size()); ++i)
        DrawText(gfx, g_noticeDetails[i + g_noticeScroll], 18,
                 42.0f + i * 28.0f, 304, 25, 13, fg);
    if (maxStart > 0) {
        const DWORD accent = g_accentMode.load() && g_validCustomAccent.load()
            ? g_customAccent.load() : SystemAccentRgb();
        Gdiplus::SolidBrush b(ToGdiColor(accent));
        const float travel = std::max(12.0f, h - 52.0f);
        const float thumb = std::max(12.0f, travel * visible / g_noticeDetails.size());
        const float offset = (travel - thumb) * g_noticeScroll / maxStart;
        gfx.FillRectangle(&b, 332.0f, 41.0f + offset, 3.0f, thumb);
    }
}

void DrawMixerPanel(Gdiplus::Graphics& gfx) {
    const float width = g_panelWidth / g_scale;
    const float h = g_panelHeight / g_scale;
    DrawPanelCard(gfx, width, h, true);
    const bool horizontal = !g_verticalVolumeBrightness.load();
    const bool light = IsLightTheme();
    const DWORD textRgb = g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : light ? 0x1C1C20 : 0xFAFAFB;
    const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    const DWORD trackRgb = g_trackMode.load() && g_validCustomTrack.load()
        ? g_customTrack.load() : light ? 0xE0E1E7 : 0x5E5E65;
    const Gdiplus::Color fg = ToGdiColor(textRgb);
    Gdiplus::SolidBrush track(ToGdiColor(trackRgb));
    Gdiplus::SolidBrush active(ToGdiColor(accentRgb));
    DrawText(gfx, Tr(OsdText::VolumeMixer), horizontal ? 27.0f : 17.0f,
             10.0f, width - 55.0f, 30.0f, 15.0f, fg);
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
}

void RenderPanel() {
    if (!g_panelWnd || !g_gdiplusToken || g_panelMode == PanelMode::None) return;
    const int w = g_panelWidth, h = g_panelHeight;
    if (w <= 0 || h <= 0) return;
    HDC screen = GetDC(nullptr);
    if (!screen) return;
    HDC memory = CreateCompatibleDC(screen);
    if (!memory) { ReleaseDC(nullptr, screen); return; }
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* pixels = nullptr;
    HBITMAP bmp = CreateDIBSection(screen, &bi, DIB_RGB_COLORS,
                                   &pixels, nullptr, 0);
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
        SIZE sz{w,h}; POINT origin{0,0};
        BLENDFUNCTION blend{AC_SRC_OVER, 0, static_cast<BYTE>(g_fadeAlpha), AC_SRC_ALPHA};
        UpdateLayeredWindow(g_panelWnd, screen, nullptr, &sz,
                            memory, &origin, 0, &blend, ULW_ALPHA);
        SelectObject(memory, old);
        DeleteObject(bmp);
    }
    DeleteDC(memory);
    ReleaseDC(nullptr, screen);
}

void ClosePanel() {
    if (g_popupWnd) KillTimer(g_popupWnd, kMediaAnimationTimer);
    const bool heldCapture = g_mediaPressedIndex >= 0 ||
        g_mixerDrag || g_mixerMutePressedIndex >= 0;
    g_mediaPressedIndex = -1;
    g_mediaPressedInside = false;
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
}


void ShowPanel() {
    if (!g_panelWnd || !g_popupWnd || g_panelMode == PanelMode::None) return;
    const bool vertical = g_verticalVolumeBrightness.load();
    const bool matchHorizontalVolume = !vertical &&
        (g_panelMode == PanelMode::Media || g_panelMode == PanelMode::Mixer);
    const bool volumePanel = g_panelMode == PanelMode::Media ||
                             g_panelMode == PanelMode::Mixer;
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
    const int gap = static_cast<int>(std::lround(7.0f * g_scale));
    const int panelInset = static_cast<int>(std::lround(4.0f * g_scale));
    const int sideInset = static_cast<int>(std::lround(
        (vertical ? 7.0f : 13.0f) * g_scale));
    const int topInset = static_cast<int>(std::lround(
        (vertical ? 6.0f : 10.0f) * g_scale));
    const int bottomInset = static_cast<int>(std::lround(
        (vertical ? 6.0f : 13.0f) * g_scale));
    const FlyoutDirection direction = GetFlyoutDirection();
    const int position = g_position.load();
    int x = main.left, y = main.top;
    if (vertical) {
        x = direction == FlyoutDirection::Left
            ? main.left + sideInset - gap + panelInset - g_panelWidth
            : main.right - sideInset + gap - panelInset;
        // Both cards have same canvas height and same visible top and bottom.
        y = main.top;
    } else {
        y = direction == FlyoutDirection::Up
            ? main.top + topInset - gap + bottomInset - g_panelHeight
            : main.bottom - bottomInset + gap - topInset;
        if (matchHorizontalVolume) {
            // Cards share the same painted x=13..(width-13) edges.
            x = main.left;
        } else if (PositionIsLeft(position)) {
            x = main.left + sideInset - panelInset;
        } else if (PositionIsRight(position)) {
            x = main.right - sideInset + panelInset - g_panelWidth;
        } else {
            x = main.left + ((main.right - main.left) - g_panelWidth) / 2;
        }
    }
    x = std::clamp<int>(x, work.left,
                        std::max<int>(work.left, work.right - g_panelWidth));
    y = std::clamp<int>(y, work.top,
                        std::max<int>(work.top, work.bottom - g_panelHeight));
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
    const bool light = IsLightTheme();
    const bool expanded = g_panelMode == PanelMode::Mixer;
    const float radius = vertical ? kVerticalArrowRadius
                                  : kHorizontalArrowRadius;
    const bool pressed = g_arrowPressed;
    const bool hovered = g_arrowHovered;
    Gdiplus::Color surface = light
        ? (pressed ? Gdiplus::Color(248, 200, 212, 230)
           : hovered ? Gdiplus::Color(236, 215, 225, 241)
                     : Gdiplus::Color(218, 229, 233, 241))
        : (pressed ? Gdiplus::Color(248, 94, 103, 120)
           : hovered ? Gdiplus::Color(236, 78, 86, 100)
                     : Gdiplus::Color(218, 60, 66, 77));
    Gdiplus::SolidBrush fill(surface);
    gfx.FillEllipse(&fill, x - radius, y - radius,
                    radius * 2.0f, radius * 2.0f);
    const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    Gdiplus::Pen outline(expanded
        ? ToGdiColor(accentRgb, 205)
        : light ? Gdiplus::Color(180, 185, 196, 210)
                : Gdiplus::Color(180, 115, 123, 139),
        expanded ? 1.3f : 0.8f);
    gfx.DrawEllipse(&outline, x - radius + 0.5f, y - radius + 0.5f,
                    radius * 2.0f - 1.0f, radius * 2.0f - 1.0f);
    Gdiplus::Pen pen(color, 2.15f);
    pen.SetStartCap(Gdiplus::LineCapRound);
    pen.SetEndCap(Gdiplus::LineCapRound);
    pen.SetLineJoin(Gdiplus::LineJoinRound);
    // Invert only while the mixer is expanded; anchor logic remains shared.
    const FlyoutDirection dir = expanded
        ? InverseDirection(GetFlyoutDirection()) : GetFlyoutDirection();
    const float extent = 4.8f;
    const float shift = pressed ? 0.45f : 0.0f;
    const float cy = y + shift;
    switch (dir) {
        case FlyoutDirection::Up:
            gfx.DrawLine(&pen, x - extent, cy + extent / 2.0f,
                         x, cy - extent / 2.0f);
            gfx.DrawLine(&pen, x, cy - extent / 2.0f,
                         x + extent, cy + extent / 2.0f);
            break;
        case FlyoutDirection::Down:
            gfx.DrawLine(&pen, x - extent, cy - extent / 2.0f,
                         x, cy + extent / 2.0f);
            gfx.DrawLine(&pen, x, cy + extent / 2.0f,
                         x + extent, cy - extent / 2.0f);
            break;
        case FlyoutDirection::Left:
            gfx.DrawLine(&pen, x + extent / 2.0f, cy - extent,
                         x - extent / 2.0f, cy);
            gfx.DrawLine(&pen, x - extent / 2.0f, cy,
                         x + extent / 2.0f, cy + extent);
            break;
        case FlyoutDirection::Right:
            gfx.DrawLine(&pen, x - extent / 2.0f, cy - extent,
                         x + extent / 2.0f, cy);
            gfx.DrawLine(&pen, x + extent / 2.0f, cy,
                         x - extent / 2.0f, cy + extent);
            break;
    }
}

void DrawHorizontalVolume(Gdiplus::Graphics& gfx) {
    const float logicalW = MainLogicalWidth();
    const float logicalH = MainLogicalHeight();
    const float centerY = MainCenterY();
    bool light = IsLightTheme();
    DWORD bg = g_backgroundMode.load() && g_validCustomBackground.load()
        ? g_customBackground.load() : light ? 0xFAFAFC : 0x26262A;
    DWORD fgRgb = g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : light ? 0x1C1C20 : 0xFAFAFB;
    DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    DWORD trackRgb = g_trackMode.load() && g_validCustomTrack.load()
        ? g_customTrack.load() : light ? 0xDEDFE3 : 0x595A60;
    Gdiplus::GraphicsPath body;
    AddRoundedRect(body, 13.0f, 10.0f, logicalW - 26.0f,
                   logicalH - 23.0f, static_cast<float>(g_cornerRadius.load()));
    Gdiplus::SolidBrush base(ToGdiColor(bg,
        static_cast<BYTE>((g_backgroundOpacity.load() * 255 + 50) / 100)));
    gfx.FillPath(&base, &body);
    Gdiplus::Color fg = ToGdiColor(fgRgb);
    DrawUniformStatusIcon(gfx, fg, 49.0f, centerY, PopupKind::NativeVolume,
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


// Compact lock-key status surface. The symbol is vector text in a
// common 24px tile; no third-party UI artwork is embedded.
void DrawLockStatus(Gdiplus::Graphics& gfx) {
    DrawPanelCard(gfx, 178.0f, 66.0f);
    const bool light = IsLightTheme();
    const DWORD rgb = g_textMode.load() && g_validCustomText.load()
        ? g_customText.load() : light ? 0x1C1C20 : 0xFAFAFB;
    const DWORD accentRgb = g_accentMode.load() && g_validCustomAccent.load()
        ? g_customAccent.load() : SystemAccentRgb();
    const Gdiplus::Color fg = ToGdiColor(rgb);
    const Gdiplus::Color quiet(168, fg.GetR(), fg.GetG(), fg.GetB());
    const int key = std::clamp(g_lastLock, 0, 3);
    constexpr PCWSTR names[] = {L"Caps Lock", L"Num Lock", L"Scroll Lock", L"Insert"};
    constexpr PCWSTR glyphs[] = {L"A", L"1", L"↕", L"Ins"};
    const Gdiplus::Color active = ToGdiColor(accentRgb);
    const Gdiplus::Color faded(130, active.GetR(), active.GetG(), active.GetB());
    Gdiplus::GraphicsPath tile;
    AddRoundedRect(tile, 13, 12, 38, 38, 9);
    Gdiplus::SolidBrush tileBrush(light ? Gdiplus::Color(255,234,235,239)
                                         : Gdiplus::Color(255,66,67,72));
    gfx.FillPath(&tileBrush, &tile);
    DrawText(gfx, glyphs[key], 14, 13, 36, 34,
             key == 3 ? 12.0f : 21.0f,
             g_lastLockValue ? active : quiet, true);
    DrawText(gfx, names[key], 61, 14, 100, 22, 14, fg);
    DrawText(gfx, g_lastLockValue ? Tr(OsdText::On) : Tr(OsdText::Off), 61, 35, 60, 18,
             12, quiet);
    Gdiplus::GraphicsPath progress;
    AddRoundedRect(progress, 61, 54, 96, 3, 1.5f);
    Gdiplus::SolidBrush bar(g_lastLockValue ? active : faded);
    gfx.FillPath(&bar, &progress);
}

// Low-level keyboard hook: event-driven and no keyboard polling. Toggle state
// is tracked on first key down (not repeated autorepeat key-down messages).
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

void ResetHideTimer(UINT ms) {
    if (g_popupWnd)
        SetTimer(g_popupWnd, kHideTimer, ms, nullptr);
}

void ResetHideTimerFor(DurationKind kind) {
    g_activeDurationKind = kind;
    ResetHideTimer(OsdDuration(kind));
}

void ShowNativeVolumePopup() {
    BrightnessEvent ev{};
    MovePopupToDisplay(ev);
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
        g_panelMode = PanelMode::None;
        CleanupMixerIcons();
        g_mixerEntries.clear();
        g_mixerMaster.Reset();
        ShowVolumePanelIfReady();
    } else {
        g_panelMode = PanelMode::Mixer;
        g_mixerScroll = 0;
        RefreshMixer();
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

LRESULT CALLBACK UiWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (hwnd == g_receiveWnd && msg == WM_TIMER && wp == kEventBatchTimer) {
        FlushNoticeBatch();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == WM_CLIPBOARDUPDATE) {
        ProcessClipboard();
        return 0;
    }
    if (hwnd == g_receiveWnd && msg == WM_DEVICECHANGE) {
        if (HandleDeviceChange(wp, lp)) return TRUE;
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
        SetPopupInteractive(false);
        ShowPopupAnimated();
        UpdateArrowHitWindow();
        ResetHideTimerFor(DurationKind::NativeEvents);
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
            ClosePanel();
            BrightnessEvent ev{};
            MovePopupToDisplay(ev);
            SetPopupInteractive(false);
            ShowPopupAnimated();
            UpdateArrowHitWindow();
            ResetHideTimerFor(DurationKind::NativeBrightness);
        }
        return 0;
    }
    if (msg == kMediaUpdateMessage && hwnd == g_receiveWnd) {
        AcquireSRWLockShared(&g_mediaLock);
        g_mediaCurrent = g_mediaPending;
        ReleaseSRWLockShared(&g_mediaLock);
        g_mediaLastRefreshTick = GetTickCount64();
        if (!g_mediaSeeking && g_mediaSeekHoldUntil &&
            g_mediaCurrent.hasTimeline &&
            std::llabs(g_mediaCurrent.timelinePosition -
                       g_mediaPreviewPosition) < 15000000LL)
            g_mediaSeekHoldUntil = 0;
        UpdateMediaArtworkCache();
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
        SetPopupInteractive(false);
        ShowPopupAnimated();
        UpdateArrowHitWindow();
        ResetHideTimerFor(DurationKind::LockKeys);
        return 0;
    }
    if (msg == kBrightnessWheelResultMessage && hwnd == g_receiveWnd) {
        if (static_cast<DWORD>(wp) != g_wheelWriteGeneration) return 0;
        const bool success = (lp & 1) != 0;
        const bool native = (lp & 2) != 0;
        if (native) {
            if (success) g_lastConfirmedNativeBrightness = g_nativePercent;
            else if (g_lastConfirmedNativeBrightness >= 0) {
                g_nativePercent = g_lastConfirmedNativeBrightness;
                RenderPopup();
                Wh_Log(L"Native brightness wheel write failed; restored value");
            }
        } else {
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
        constexpr DWORD kMaxVcpValue = 0xFFFF;
        if (ev.physicalIndex >= 32 ||
            ev.value > kMaxVcpValue || ev.minimum > kMaxVcpValue ||
            ev.maximum > kMaxVcpValue ||
            (ev.maximum == 0 && ev.minimum != 0) ||
            (ev.maximum != 0 && (ev.maximum <= ev.minimum ||
                                  ev.value < ev.minimum || ev.value > ev.maximum)))
            return FALSE;
        // producerPid is descriptive metadata, not sender authentication.
        if (!g_showDdcBrightness.load()) return TRUE;
        ClosePanel();
        g_visible = ev;
        g_lastConfirmedDdcBrightness = ev.value;
        g_popupKind = PopupKind::DdcBrightness;
        MovePopupToDisplay(ev);
        SetPopupInteractive(false);
        ShowPopupAnimated();
        UpdateArrowHitWindow();
        ResetHideTimerFor(DurationKind::DdcBrightness);
        return TRUE;
    }
    if (msg == WM_TIMER && hwnd == g_popupWnd && wp == kHideTimer) {
        if (g_mixerDrag || g_mainBarDragging) return 0;
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
        hwnd == g_barWheelWnd ||
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
        if (hwnd == g_arrowWnd && g_arrowHovered) {
            g_arrowHovered = false;
            if (!g_arrowPressed) RenderPopup();
        }
        if (!g_mainBarDragging && g_popupWnd && IsWindowVisible(g_popupWnd))
            ResetHideTimerFor(g_activeDurationKind);
        return 0;
    }
    if (msg == WM_NCHITTEST) {
        if (hwnd == g_popupWnd) return g_popupKind == PopupKind::Notification && g_noticeClickable ? HTCLIENT : HTTRANSPARENT;
        if (hwnd == g_panelWnd || hwnd == g_arrowWnd ||
            hwnd == g_barWheelWnd) return HTCLIENT;
    }
    if (msg == WM_SETCURSOR && hwnd == g_popupWnd &&
        g_popupKind == PopupKind::Notification && g_noticeClickable) {
        SetCursor(LoadCursorW(nullptr, IDC_HAND));
        return TRUE;
    }
    if (msg == WM_SETCURSOR &&
        (hwnd == g_panelWnd || hwnd == g_arrowWnd ||
         hwnd == g_barWheelWnd)) {
        bool overClickableIcon = hwnd == g_arrowWnd ||
            hwnd == g_barWheelWnd;
        if (hwnd == g_panelWnd && g_scale > 0) {
            POINT point{};
            if (GetCursorPos(&point) && ScreenToClient(hwnd, &point)) {
                const float x = point.x / g_scale, y = point.y / g_scale;
                if (g_panelMode == PanelMode::Mixer)
                    overClickableIcon = MixerIconHitTest(x, y) >= 0;
                else if (g_panelMode == PanelMode::Media)
                    overClickableIcon = MediaButtonHitTest(x, y) >= 0 ||
                        MediaTimelineHitTest(x, y);
            }
        }
        SetCursor(LoadCursorW(nullptr,
            overClickableIcon ? IDC_HAND : IDC_ARROW));
        return TRUE;
    }
    if (msg == WM_MOUSEACTIVATE &&
        (hwnd == g_popupWnd || hwnd == g_panelWnd ||
         hwnd == g_arrowWnd || hwnd == g_barWheelWnd))
        return MA_NOACTIVATE;
    if (msg == WM_LBUTTONUP && hwnd == g_popupWnd &&
        g_popupKind == PopupKind::Notification && g_noticeClickable) {
        if (g_panelMode == PanelMode::Details) ClosePanel();
        else { g_panelMode = PanelMode::Details; g_noticeScroll = 0; ShowPanel(); }
        ResetHideTimerFor(DurationKind::Interactive);
        return 0;
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
            if (MediaTimelineHitTest(x, y)) {
                g_mediaSeeking = true;
                g_mediaSeekHoldUntil = 0;
                SetCapture(hwnd);
                PreviewMediaSeek(x);
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
        if (msg == WM_MOUSEMOVE && g_mediaSeeking) {
            const float x = static_cast<float>(GET_X_LPARAM(lp)) / g_scale;
            PreviewMediaSeek(x);
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
        if (g_mediaPressedIndex >= 0) {
            g_mediaPressedIndex = -1;
            g_mediaPressedInside = false;
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
    if (g_receiveWnd) KillTimer(g_receiveWnd, kEventBatchTimer);
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
    if (g_barWheelWnd) DestroyWindow(g_barWheelWnd);
    if (g_arrowWnd) DestroyWindow(g_arrowWnd);
    if (g_panelWnd) DestroyWindow(g_panelWnd);
    if (g_popupWnd) DestroyWindow(g_popupWnd);
    if (g_receiveWnd) DestroyWindow(g_receiveWnd);
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
    Wh_Log(L"Fluent OSD & Media v1.7.0 initialized (%s)", name);
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
}

void Wh_ModSettingsChanged() {
    LoadSettings();
    // Refresh the next OSD using the newly selected theme. Settings never
    // force an unexpected brightness write or background monitor read.
}

void Wh_ModBeforeUninit() {
    // Prevent callbacks from posting into a receiver that is going away.
    g_closing.store(true);
    g_networkReceiver.store(nullptr);
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
