# Fluent OSD — native XAML renderer experiment

**Branch:** `fluent-osd-xaml`  
**Baseline:** `fluent-osd` v1.0.1 (`8ff2d4352d8c081e78208266ff1561b5e5bfe31b`)  
**Status:** standalone XAML Island probe v0.1.3 has passed the user's Windows rendering / DWM rounded-corner visual test; integrated Fluent OSD v1.0.2 is committed but **has not been compiled or runtime-tested**.

## Goal / non-goals

- **Goal:** investigate a genuine native XAML visual tree as a prospective renderer while preserving Fluent OSD's Explorer integration and event engine.
- **Do not:** introduce HTML, CSS runtime, Electron, CEF, WebView2, .NET or a standalone permanent resident process.
- **Keep:** the existing GDI+ `UpdateLayeredWindow` renderer as the verified 1.0.1 path until a native XAML backend has passed live testing and regression review.
- **Do not:** silently replace 1.0.1 or enable experimental rendering by default.

## First artifact: standalone host probe

File: [`experiments/fluent-osd-xaml-island-probe.wh.cpp`](../experiments/fluent-osd-xaml-island-probe.wh.cpp)

This is a **real Windows.UI.Xaml Island** proof of concept, not a screenshot or GDI+ simulation.

It creates:

1. Its own STA thread within `explorer.exe`, independently of the existing OSD's MTA/GDI+ thread.
2. A native topmost no-activate Win32 host HWND. The diagnostic version intentionally **does not** set `WS_EX_NOREDIRECTIONBITMAP` so that a conventional redirected surface can establish whether the host itself is visible.
3. A `Windows.UI.Xaml.Hosting.WindowsXamlManager` and `DesktopWindowXamlSource` attached to that HWND.
4. A native XAML visual tree: `Border`, `StackPanel`, `TextBlock` and `ProgressBar`.
5. An on-demand volume snapshot via Core Audio (default multimedia render endpoint), **not** continual polling.

This standalone module has a separate Windhawk ID (`fluent-osd-xaml-island-probe`) and does **not** install Shell hooks, suppress Windows OSD, or modify the production `mods/fluent-osd.wh.cpp`.

### Manual test

1. Open Windhawk and create a separate local mod from the entire probe source. Do **not** replace the installed Fluent OSD mod.
2. Compile it using Windhawk's included compiler. Verify there are no missing C++/WinRT/XAML headers or link errors.
3. Enable the probe. After ~0.75 seconds, a native XAML volume preview should **automatically** appear in the **center** of the monitor containing the pointer for **12 seconds**. The shortcut **Ctrl+Alt+Shift+O** manually reopens it. If this does not appear, consult the Windhawk log before changing the styling code.
4. Wait for the preview to hide. Repeat after switching the Windows output device and at different screen scales (100%, 125%, 150%).
5. Disable the probe and verify that Explorer remains responsive, no host HWND remains, and there are no shutdown blockers.
6. Check the **probe's** Windhawk log, and paste the lines beginning `XAML probe:`. Expected checkpoints: `mod init` → `STA worker starting` → `STA initialized` → `Win32 host created` → `initializing WindowsXamlManager` → `manager initialized` → `island attached` → `XAML controls created` → `startup auto-preview scheduled` → `preview requested (startup)` → `preview at ... hostVisible=1 islandVisible=1`. If it stops at the manager or attach step, include the logged HRESULT.

   Microsoft documents a host **manifest / MaxTestedVersion** requirement for UWP XAML Islands. A Win32 desktop process may fail XAML runtime activation even if the mod compiles; the injection scenario requires runtime evidence, not assumptions. [Microsoft UWP XAML hosting API](https://learn.microsoft.com/en-us/windows/uwp/xaml-islands/using-the-xaml-hosting-api#troubleshooting).

**Do not use this prototype as a daily-driver OSD.** It has not passed a compilation, runtime, resource, or compatibility test, and its top-level transparency and rounded outside corners have not been validated. It also does not yet implement UI input, fade animations, mixer, SMTC, device notices or monitor mirroring.

### Shutdown/Explorer risk

All XAML objects are instantiated and closed on the same dedicated STA thread. The host receives an asynchronous stop signal; the plugin waits for that thread to exit **before** unloading code.

The first wait has a six-second diagnostic threshold. If the XAML runtime is stuck at shutdown, the final wait can still block Explorer: it does not abandon an executing thread and allow a use-after-unload crash. **A bounded, verified unload path is a release blocker.**

## Why system Windows.UI.Xaml first?

Styler mods apply styles to existing Windows XAML trees; Fluent OSD has no pre-existing XAML tree. Creating one requires an Island host, not copying the Styler selector engine.

This pilot uses **system `Windows.UI.Xaml`** and the documented legacy Island host. It deliberately does not bootstrap the Windows App SDK / WinUI 3 runtime inside `explorer.exe`. This reduces extra deployment dependencies for an initial feasibility test, but it does **not** prove performance, UI fidelity or the robustness of transparent overlays.

See Microsoft's [UWP XAML hosting documentation](https://learn.microsoft.com/en-us/windows/uwp/xaml-islands/using-the-xaml-hosting-api) and [Win32 C++ XAML Island example](https://learn.microsoft.com/en-us/windows/uwp/xaml-islands/host-standard-control-with-xaml-islands-cpp).

## v0.1.2 — Rounded-corner host clipping (experimental)

Observed on the Windows host: the XAML preview renders, but the four
corners show black opaque pixels outside the card radius.

The XAML `Border.CornerRadius` only rounds the XAML card; the enclosing
Win32 `WS_POPUP` HWND and its XAML Island child still occupy a rectangle.
The prototype therefore applies a Win32 rounded `HRGN` via
`CreateRoundRectRgn` / `SetWindowRgn` to the **top-level host**. The same
14-DIP radius is used by the XAML card and converted to physical pixels
using the host DPI. It is reapplied when the window is shown, resized,
or notified of a DPI change. `gdi32` was added to the link options.

This clips pixels outside the window region; it is **not** per-pixel-alpha
transparency and may produce slightly stepped edges. Verify the four corners
on a light and a dark desktop background, including displays with different
DPI scaling. Do not confuse a region-clipped preview with a production-ready
alpha-composited overlay.

References: [SetWindowRgn](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowrgn),
[CreateRoundRectRgn](https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createroundrectrgn).

## v0.1.3 — DWM compositor rounding trial

The v0.1.2 host region removed the opaque black corner squares, but
`SetWindowRgn` clips against integer pixel boundaries, producing a
visibly jagged outline. Windows documentation also states that **window
regions prevent DWM rounding**, even when a corner preference is requested.

v0.1.3 removes **all** `HRGN` host clipping and requests
`DWMWA_WINDOW_CORNER_PREFERENCE = DWMWCP_ROUND` with
`DwmSetWindowAttribute`; it links to `dwmapi`. DWM is responsible for
anti-aliased corner clipping, if this borderless popup is eligible.
The existing XAML `Border.CornerRadius` is retained.

**Manual validation**: enable the test mod, inspect the corners on a
contrasting desktop background, and look for
`XAML probe v0.1.3: DWM rounded-corner request HRESULT=...` in Windhawk.
`S_OK` confirms attribute submission, **not** that DWM actually rounded
this specific window. If the black rectangular corners return, report both
the visible result and the HRESULT. Do not blindly restore HRGN: that
would restore the jagged edges.

Microsoft reference: [Apply rounded corners in desktop apps](https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/ui/apply-rounded-corners).

## First integrated backend — Fluent OSD v1.0.8 (branch only)

The existing `mods/fluent-osd.wh.cpp` now contains an **opt-in** XAML
volume renderer within the **same** mod.

v1.0.8 fixes the Windhawk Clang `std::clamp` overload mismatch between
Win32 `LONG` (`RECT`) coordinates and local `int` variables. The source
already includes `winsock2.h` before `windows.h`; a remaining Winsock
include warning may originate from Windhawk's generated compilation prelude.
 The proven v0.1.3 standalone
XAML Island probe remains separate and unchanged.

- `CustomOSD.Switches.experimentalXamlVolume` defaults to **false**.
- **XAML enabled:** *every* enabled native volume event uses the XAML
  Island STA renderer, regardless of vertical-layout, SMTC or mixer settings.
  Those extra layouts and interactions are **not implemented yet**; they
  are not silently handed to GDI+.
- **XAML disabled:** the original GDI+ volume renderer runs normally.
  Brightness, lock keys, clipboard, network, SMTC-related notifications
  and other *non-volume* OSD categories retain their original GDI+ paths.
- Failed XAML initialization, an unavailable host, failed event posting or
  render exceptions **do not trigger GDI+ volume fallback**. The event
  may show nothing; Windhawk logs contain `XAML v1.0.8:` or
  `Fluent OSD v1.0.8:` diagnostics.
- Native volume events and Core Audio state remain in the existing code.
  A plain value snapshot (percent, mute, duration, language, colors, anchor)
  is copied across the thread boundary. All XAML/WinRT objects stay on a
  dedicated STA; existing event ingestion stays on the main OSD UI thread.
- This is the **first backend migration**, not a complete separation of
  event processing, layout and interaction responsibilities.

### Manual test

1. Disable the standalone `fluent-osd-xaml-island-probe` mod.
2. Load **`mods/fluent-osd.wh.cpp`** from the `fluent-osd-xaml`
   branch into Windhawk, and verify **`@version 1.0.8`**.
   The test mod has a **separate ID** (`fluent-osd-xaml`), so it can
   be installed alongside the production `fluent-osd`; however, only
   **one should be enabled at a time**, because both install Windows OSD
   hooks into Explorer. The test also uses a distinct message-window
   class and WM_COPYDATA tag to isolate event reception. Restore the
   production ID (`fluent-osd`) when merging back.
3. Enable the normal custom volume switch and
   **Experimental XAML volume renderer (no fallback)**. Change volume with
   the Windows volume buttons. A native XAML popup should show the actual
   volume and mute state.
4. Inspect logs: `XAML v1.0.8: renderer ready`, then
   `Fluent OSD v1.0.8: native volume -> XAML only`.
   If the view is missing, check for
   `XAML volume unavailable; NO GDI+ fallback`, startup or draw errors.
5. Disable the XAML switch and trigger volume again: **only then**
   should the original GDI+ volume popup appear.
6. Check brightness and lock-key popups separately, and test
   disabling/re-enabling the mod. A stalled legacy XAML manager shutdown
   can still block Explorer until the STA exits.

**Important:** compilation, full runtime integration, actual event behavior,
multi-monitor DPI, renderer performance and shutdown have **not** yet been
validated in the user's Windows environment. The production `fluent-osd`
v1.0.1 branch is unchanged.

## v1.0.6–v1.0.8 — DWM border investigation and volume layout port

- **v1.0.6:** request `DWMWA_BORDER_COLOR = DWMWA_COLOR_NONE`
  alongside DWM `DWMWCP_ROUND`. This is intended to remove the
  compositor's thin dark outer border without restoring the aliased
  `SetWindowRgn` path. Log both HRESULTs. It has **not** yet been
  confirmed whether that was the remaining black-pixel source.
- **v1.0.8:** replace the demonstration card
  (`FLUENT OSD / XAML`, heading + stacked progress bar) with a
  **single-row native XAML volume layout**. The XAML canvas now uses
  the existing master-popup rectangle, current DPI × user size scale,
  foreground/accent/track/background colors, icon/font size, track
  thickness and thumb diameter. Horizontal and vertical forms have
  separate native XAML geometry; no GDI+ functions are called to
  paint this XAML volume view.
- The XAML root `Border` now has **zero corner radius**. This avoids
  having two incompatible corner curves: the outer DWM HWND clip
  rounds the entire rectangular XAML Island surface.
- The speaker glyph currently comes from the OS-installed Segoe
  Fluent Icons font rather than the original GDI+ path geometry.
  Full icon parity, vertical thumb hit targets, mixer/media panels,
  animations, opacity and per-monitor mirrors remain incomplete.
- **Important:** this is still a staged migration. Other categories
  have not yet been ported, and their legacy GDI+ code remains in
  this test build. Do **not** claim the GDI+ dependency has been removed
  from the full application.

### Targeted visual test for the new build

1. Load the experimental `@id fluent-osd-xaml` **v1.0.8** source,
   keeping the production mod disabled during test.
2. Enable custom volume + experimental XAML volume rendering; adjust
   volume and mute. The old demo heading should be gone.
3. Check all four corners against a bright background. If any dark
   pixels remain, capture a close-up and check
   `XAML v1.0.8: DWM round=... border-none=...` in the Windhawk log.
4. Compare horizontal and vertical layouts, theme colors, user-defined
   width/height, 100%/125%/150% DPI and disabled value/icon options.
5. If compiling fails, send the **first** compiler error and version
   header. XAML shapes/Viewbox APIs have not been compiled or tested
   in the user's Windhawk environment yet.

## v1.0.8 — Percentage alignment correction

- Vertical percentage: use an explicit TextBlock width spanning the
  card and `TextAlignment::Center` instead of guessing its visual
  position using `centerX - 22`. This should keep 0%, 9%, 100%
  on the same centerline.
- Horizontal percentage: preserve a 54-DIP value field, center its
  contents, and anchor it 7 DIP from the right card edge by default.
  Reserve 32 DIP when the mixer-arrow option is enabled.
- No changes to event routing, display placement, the DWM corner
  preference, other notifications, or the production mod.

## Migration gates

1. **Host viability:** Windows compilation, Island activation, show/hide, transparency behavior, DPI, multimonitor placement, nonactivation and clean unloading.
2. **Backend separation:** define `OsdViewModel` and backend-neutral layout/visual state contracts. Prevent XAML objects or HWNDs from leaking across apartment boundaries; exchange only immutable, owned snapshots.
3. **First real migration:** move a single noninteractive notification surface; retain GDI+ fallback. Confirm icon/text fidelity, opacity and expiry handling.
4. **Controls:** volume/brightness with mouse, wheel and drag; then Mixer and SMTC, sharing layout with hit testing.
5. **Regression:** Win11 build variance, Explorer restarting, Windhawk unload/reload, UWP/XAML startup timing, OS theme changes, mixed DPI/HDR/SDR, CPU/GPU/working set, event floods and shutdown.

**Do not merge to `fluent-osd` until stages are functionally complete and verified on Windows.**
