# Fluent OSD — native XAML renderer experiment

**Branch:** `fluent-osd-xaml`  
**Baseline:** `fluent-osd` v1.0.1 (`8ff2d4352d8c081e78208266ff1561b5e5bfe31b`)  
**Status:** standalone XAML probe v0.1.3 passed the earlier host test. Experimental `fluent-osd-xaml` **v1.0.18** now includes XAML volume, native brightness, per-target DDC/CI, background-opacity settings and a shared input layer. **v1.0.18 has not yet been compiled or runtime-tested in Windhawk.**

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

## First integrated backend — Fluent OSD v1.0.10 (branch only)

The existing `mods/fluent-osd.wh.cpp` now contains an **opt-in** XAML
volume renderer within the **same** mod.

v1.0.5 fixed the Windhawk Clang `std::clamp` overload mismatch between
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
  may show nothing; Windhawk logs contain `XAML v1.0.10:` or
  `Fluent OSD v1.0.10:` diagnostics.
- Native volume events and Core Audio state remain in the existing code.
  A plain value snapshot (percent, mute, duration, language, colors, anchor)
  is copied across the thread boundary. All XAML/WinRT objects stay on a
  dedicated STA; existing event ingestion stays on the main OSD UI thread.
- This is the **first backend migration**, not a complete separation of
  event processing, layout and interaction responsibilities.

### Manual test

1. Disable the standalone `fluent-osd-xaml-island-probe` mod.
2. Load **`mods/fluent-osd.wh.cpp`** from the `fluent-osd-xaml`
   branch into Windhawk, and verify **`@version 1.0.10`**.
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
4. Inspect logs: `XAML v1.0.10: renderer ready`, then
   `Fluent OSD v1.0.10: native volume -> XAML only`.
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

## v1.0.6–v1.0.9 — DWM border investigation and volume layout port

- **v1.0.6:** request `DWMWA_BORDER_COLOR = DWMWA_COLOR_NONE`
  alongside DWM `DWMWCP_ROUND`. This is intended to remove the
  compositor's thin dark outer border without restoring the aliased
  `SetWindowRgn` path. Log both HRESULTs. It has **not** yet been
  confirmed whether that was the remaining black-pixel source.
- **v1.0.9:** replace the demonstration card
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

1. Load the experimental `@id fluent-osd-xaml` **v1.0.10** source,
   keeping the production mod disabled during test.
2. Enable custom volume + experimental XAML volume rendering; adjust
   volume and mute. The old demo heading should be gone.
3. Check all four corners against a bright background. If any dark
   pixels remain, capture a close-up and check
   `XAML v1.0.10: DWM round=... border-none=...` in the Windhawk log.
4. Compare horizontal and vertical layouts, theme colors, user-defined
   width/height, 100%/125%/150% DPI and disabled value/icon options.
5. If compiling fails, send the **first** compiler error and version
   header. XAML shapes/Viewbox APIs have not been compiled or tested
   in the user's Windhawk environment yet.

## v1.0.9 — Percentage alignment correction

- Vertical percentage: use an explicit TextBlock width spanning the
  card and `TextAlignment::Center` instead of guessing its visual
  position using `centerX - 22`. This should keep 0%, 9%, 100%
  on the same centerline.
- Horizontal percentage: preserve a 54-DIP value field, center its
  contents, and anchor it 7 DIP from the right card edge by default.
  Reserve 32 DIP when the mixer-arrow option is enabled.
- No changes to event routing, display placement, the DWM corner
  preference, other notifications, or the production mod.

## v1.0.9 — Horizontal spacing and progress bounds

- Horizontal value uses **right-aligned** numerals within its 54-DIP
  field, rather than centering within that field. The filled track width
  is derived from the same value-field origin with a 9-DIP gap instead
  of separately subtracting a hardcoded 169 DIP from the canvas width.
- The foreground shape now exactly overlaps the rounded background
  track and is revealed using a reusable XAML `RectangleGeometry` clip
  (`UIElement.Clip`). The clip progresses left-to-right in horizontal
  mode and bottom-to-top in vertical mode.
- The progress thumb center is clamped so its full ellipse remains
  within the track's endpoints at both 0% and 100%.
- Mixer-arrow mode still reserves right-side space, but the XAML
  arrow itself has not yet been implemented. This is not a complete
  media/mixer UI migration.
- No change to event routing, DWM corner treatment or the production
  `fluent-osd` branch. Real-machine compile and visual validation
  are still required.

## v1.0.10 — Remove nonexistent mixer-arrow gutter

- In the XAML volume-only renderer, the mixer-arrow control is **not
  implemented**. The horizontal layout nevertheless reserved **32 DIP**
  instead of **7 DIP** after the percentage text whenever the existing
  mixer-arrow setting was enabled.
- The vertical renderer has **no corresponding bottom-gap branch**.
  That asymmetry explains why the report only affected horizontal mode.
- Remove the unimplemented XAML arrow reservation and its unused
  snapshot member. Align the percentage field 7 DIP from the right
  edge regardless of the mixer setting. The track derives its endpoint
  from that same value-field boundary.
- When XAML mixer controls are implemented, add their spacing together
  with the actual clickable UI rather than allocating invisible space.
- No change to native event routing, DWM rounding, or GDI+ production
  renderer. Runtime verification is still required.

## v1.0.11 — Horizontal percentage optical inset

- Keep the horizontally right-aligned percentage value field but increase
  its card-edge inset from **7 DIP to 16 DIP**. At 7 DIP, the % glyph
  appeared visually flush with the right edge.
- The progress track continues to derive its endpoint from the same
  value-field origin (9 DIP separation), so the bar cannot overlap the
  number when this inset changes.
- Vertical percentage placement, fill clipping, DWM corners and event
  routing are unchanged. Only the experimental `fluent-osd-xaml`
  mod was edited; runtime verification is pending.

## v1.0.12 — Optical margin based on real screenshot

- Screenshot at 520 × 185 px: dark card occupies approximately x=115–446;
  speaker glyph begins at x=141 (26px visible left inset), and the final
  glyph of `100%` ends at about x=431 (15px visible right inset).
- The right-aligned number looked too close to the card boundary even
  though its *layout* right inset was 16 DIP. The unequal **visible**
  margins are the relevant comparison, not the `TextBlock` slot alone.
- Increase only the horizontal value's right inset from **16 to 28 DIP**,
  keeping the same number-field width, right alignment, and 9-DIP gap
  between progress track and number.
- With the same screenshot scale, the expected visible right inset
  grows by roughly 11px, making it comparable to the icon's left inset.
  This is a measured correction, not yet a validated visual result.
- Vertical layout, full-size progress fill clipping, DWM and production
  mod are untouched.

## v1.0.13 — Symmetric inner gaps around horizontal volume track

- The v1.0.12 screenshot shows nearly equal **outer** card-content margins
  (about 26px on each side). Remaining imbalance is **inside** the card:
  icon-to-track ~18px, track-to-number ~27px.
- Move the horizontal track and its filled region/thumb right by 5 DIP:
  `trackX = 68` (previously 63). Reduce `kTrackValueGap` by exactly
  5 DIP to 4 (previously 9). Since their sum is unchanged, the **bar
  length stays the same**, and its right endpoint moves along with it.
- The number field, its 28-DIP right margin, vertical layout and the
  underlying event/DWM systems remain untouched. This is a
  screenshot-based optical correction pending Windhawk visual testing.

## v1.0.14 — Content-measured responsive XAML layout

**Replaces the fixed-coordinate experiments of v1.0.8–v1.0.13.**

- The XAML volume snapshot now copies the existing
  `CustomOSD.Appearance.ddcInnerPadding` setting alongside DPI scale,
  custom width/height, font and icon size, track thickness and thumb size.
- Both `TextBlock` controls are measured with `UIElement.Measure()`
  and `DesiredSize()` after setting their actual glyph/text and font sizes.
  Reset the number's prior explicit width before measuring it.
- **Horizontal:** the measured icon and number sit at matching outer
  insets (derived from inner padding and the original canvas cutout).
  The two icon/bar/number gaps are calculated from measured content height
  and are **identical**. The bar consumes the remaining width. No fixed
  `trackX`, 54-DIP percentage field, or hard-coded right gap remains.
- **Vertical:** top number and bottom icon are measured, then the progress
  bar consumes the remaining height between two calculated gaps.
  Number stays centered within the card; icon uses its actual measured
  width rather than assuming the font-size equals glyph width.
- Available padding and gaps shrink if a custom card is too narrow/short
  to fit the requested dimensions. Fill clipping and the thumb bounds are
  still calculated from the resulting track rectangle.
- A static arithmetic check covered 26 horizontal/vertical combinations
  of card dimensions and optional number visibility; it found no
  overlapping geometry. **Actual XAML measurement/compilation and
  rendering remain unverified** in Windhawk.
- GDI+ rendering of *unported* OSD categories remains in this test build.
  The volume XAML route does not fall back to GDI+.

## v1.0.15 — Invariant progress-track geometry at every volume

### Root cause

v1.0.14 derived `labelW` directly from the currently rendered
`TextBlock.DesiredSize().Width`. Changing `98%` to `100%` therefore
changed the **available track width**, not just its fill percentage.
The speaker icon slot could similarly change when switching to mute.

### Correction

- On the existing XAML STA, use the **actual visible TextBlock**
  controls to measure every possible value from **0% through 100%**,
  plus both speaker/mute glyph variants, with unconstrained intrinsic
  sizes. Reserve the **maximum** width and height for each category.
- Cache the resulting slot metrics per font size. Only setting changes
  that affect the corresponding font size trigger a new measurement;
  normal volume/mute events reuse the same dimensions.
- Reapply the current glyph and label after measurement. The icon
  renders centered inside its fixed-width *measured* slot; the
  percentage remains right-aligned within its stable slot.
- If Show Value is disabled, defer its cache update; a collapsed XAML
  `TextBlock` otherwise reports a zero `DesiredSize`.
- The track length is now a function of card dimensions, typography,
  user padding, and settings, **independent of the current volume**.
  The fill clip still uses `trackW × percent / 100`.

**Regression checks:** compare `0%, 1%, 8%, 9%, 10%, 98%, 99%, 100%`
in both layouts and through mute/unmute. Track background endpoints
must stay fixed throughout. Also toggle Show Value off/on and change
font size to exercise cache invalidation. This requires the user's
Windhawk runtime test; no Windows compiler/runtime validation was run.

## v1.0.16 — XAML switch directly controls migrated OSD categories

### Scope and compatibility

- The existing Windhawk setting key
  `CustomOSD.Switches.experimentalXamlVolume` is retained so earlier
  test configurations are not reset. Its visible name now states
  **XAML renderer for migrated OSDs (no fallback)**.
- The switch now routes **system volume AND Windows native brightness**
  to a shared native XAML rendering path. Their individual
  `showCustomVolume` and `showCustomBrightness` toggles still determine
  whether events are shown at all.
- The XAML off state restores the prior GDI+ path for those categories.
  The XAML on state **never** falls back to GDI+ when unavailable, so
  failures remain observable.
- Brightness uses the OS-provided Segoe Fluent Icons **Brightness E706**
  symbol; `ddcShowSun` controls icon visibility in brightness mode.
  Unknown native brightness levels display their raw reading, with
  no percentage fill or slider thumb.
- Shared popup placement, UI language, dimensions, DPI, color theme,
  show percentage and duration all remain sourced from existing state.
- Volume/brightness text and icons use maximum intrinsic size slots,
  rather than changing bar width with a runtime value. Raw brightness
  reserves a separately cached 5-digit numeric slot and does not
  contaminate the volume percentage's slot.

### Explicitly NOT migrated yet

- **DDC/CI brightness:** current code retains per-monitor latest values,
  physical target identity and simultaneous per-target GDI+ surfaces in
  source/all-display modes. The XAML implementation currently has only
  one window. Blindly redirecting DDC into it would lose this behavior.
  Therefore DDC remains on its existing renderer regardless of the
  XAML switch until an independent XAML host-per-display is implemented.
- **SMTC, Mixer, USB, Bluetooth, network, clipboard and lock-key
  status:** still GDI+. Their dedicated renderers and interactions
  have not been converted.
- No claim is made that GDI+ initialization or rendering has been
  removed from the full test build.

### Manual test

1. Load `fluent-osd-xaml` **v1.0.16** and keep the production
   `fluent-osd` mod disabled.
2. Enable `showCustomVolume` and `showCustomBrightness` plus the
   XAML switch. Change volume then use Windows native brightness keys.
   Both must show the **same XAML styling**, not a GDI+ brightness card.
3. Check log messages:
   `Fluent OSD v1.0.16: native volume -> XAML only` and
   `Fluent OSD v1.0.16: native brightness -> XAML only`.
4. Test 98→100%, brightness 0→100%, theme changes, vertical layout,
   `ddcShowSun` off/on, and XAML renderer off/on.
5. Trigger external-monitor DDC/CI separately. It should remain on
   the existing renderer until per-monitor XAML support is built.
6. Disable/re-enable Windhawk mod, review Explorer shutdown and
   `XAML v1.0.16` startup logs. This source is not yet
   Windows-compiled or runtime-tested by the assistant.

## v1.0.17 — DDC/CI XAML, input and inherited opacity

### Opacity and Window composition

- The original `CustomOSD.Appearance.ddcBackgroundOpacity` setting
  supplies the XAML card's **background alpha**, mapped from 0–100% to
  0–255. Text, progress, and thumb remain independently opaque.
- The Island STA requests the Microsoft
  `IXamlSourceTransparency.IsBackgroundTransparent` interface on
  `Windows.UI.Xaml.Window.Current` after creating the first source.
  The host disables opaque Win32 erase and opts into full-client DWM
  composition while retaining its existing DWM corner preference.
- Look for `XAML v1.0.17: Island transparency HRESULT=...` and
  `rounded=... border=... frame=...`. A successful HRESULT does not by
  itself prove the desired visual blending: **verify 20%, 60%, 96%,
  100% opacity over light and dark windows**. Watch for any return of
  black corner artifacts.

### Independent DDC monitor views

- The same XAML setting now controls **volume, native brightness and
  DDC/CI**. Individual `showDdcBrightness` is still required to enable
  DDC notifications, independently of the native-brightness Show/Hide.
- DDC notification batches still preserve the original display device,
  physical monitor index, VCP min/max and raw value. For source and
  all-monitor output modes, the XAML STA creates an independent
  `DesktopWindowXamlSource`/HWND **per active DDC target** and places it
  using that monitor's DPI and placement calculations. Stale targets
  are hidden rather than mirroring another monitor's value.
- In fixed primary/selected-monitor modes, the existing selected
  master target appears on one output, preserving the previous policy.
- The old mirrored layered GDI+ surfaces are **not created while XAML
  DDC is enabled**. The other unported OSD categories still use GDI+.

### Click, drag, wheel and mute

- The old GDI+ hit windows never overlapped the XAML host, so they
  could not process input. The new renderer owns a lightweight
  near-invisible Win32 hit window for each XAML progress track and
  volume icon, sized using the XAML layout's actual track/icon geometry.
- Drag events and mouse wheel actions pass bounded commands through
  the existing Explorer UI receiver, preserving COM/audio/WMI/DDC
  writes on their original threads. DDC commands carry **both**
  `device` and `physicalIndex` to avoid applying edits to the wrong
  external display. Volume icon click toggles mute.
- The DDC edit keeps its target alive during interaction and
  rolls back only that target when the hardware write fails.
  A per-event preview reflects the requested percentage immediately.
- The input hit windows use `WS_EX_LAYERED` with alpha 1 only for
  mouse capture; **the actual XAML popup is not a layered GDI+ window**.

### Manual regression checklist

1. Disable the production `fluent-osd`, load the independent
   `fluent-osd-xaml` **v1.0.17** in Windhawk, enable the XAML switch.
2. On the Claw + external monitor, enable `showDdcBrightness`,
   then trigger a DDC/CI brightness change. Confirm the XAML card
   appears on the **correct physical monitor** and shows its own
   actual percentage. If two monitors support DDC, update both.
3. Set background opacity to 20, 60, 96 and 100%, observing
   the background versus the text/track opacity and all four corners.
4. Try clicking the bar, dragging across 0–100%, using the mouse
   wheel over the bar, and clicking the volume icon to mute.
   Confirm actual hardware state changes, not only visual updates.
5. Repeat on horizontal/vertical layouts, multiple DPI scales,
   custom sizes, and 98→100% to confirm the underlying bar remains
   constant in length.
6. Disable/re-enable the mod, monitor Explorer cleanup and check
   `XAML v1.0.17` logs. Compilation, visual compositing and hardware
   interaction **require real Windows validation**; they have not
   been verified in the developer environment used for these edits.

## v1.0.18 — Shared input behavior and renderer-neutral arithmetic

After bringing the DDC/CI controls onto native XAML in v1.0.17,
consolidate click/drag/wheel behavior rather than reimplementing it for
each OSD type.

- `osd_input::TrackPercent`: maps either horizontal or inverted
  vertical track coordinates to clamped 0–100% with zero-span and
  non-finite input guards. Used by **both** the original GDI+ hit
  handler and the new XAML pointer handler.
- `osd_input::ConsumeWheelSteps`: accumulates fractional wheel deltas
  into integer steps and retains sub-notch remainder. Shared by the
  GDI+ and XAML scroll paths.
- `osd_input::PercentToRaw`: one rounded 0–100% conversion for
  hardware-specific DDC minimum/maximum values. Shared by visual
  previews, XAML DDC writes and the legacy slider.
- `BeginInputGesture`, `EndInputGesture`,
  `CancelInputGesture`, `ArmInteractionTimer` and
  `PointerInsideClient` implement **one XAML Hit Window capture and
  hide-timer lifecycle**. Volume uses the click action for mute; volume,
  native brightness, and DDC use the exact same slider gesture.
  Their hardware writers remain separate behind `InputCommand` dispatch.
- Input overlays **must not** resize the real XAML Island on
  `WM_SIZE`. The shared window procedure now checks
  `hwnd == state.host` before resizing the Island; overlay close
  messages also must not stop the shared STA.
- The former `xaml_volume` namespace is renamed `xaml_osd`
  because it now implements all migrated level-indicator categories.

### Regression cases

1. Use a mouse to click 0%, 50%, 100% and drag the volume and DDC
   tracks in each axis. The full XAML Island must **not shrink** when
   its transparent input overlay is repositioned.
2. Wheel test: +60 then +60, -60 then -60, and standard ±120 deltas.
   One step should be generated per full notch, not per fractional event.
3. DDC test with non-0–100 ranges: test 20–80 and 0–255. UI endpoints
   must map to the target's real minimum and maximum, never a different
   monitor's brightness.
4. Test muted-speaker click and pointer release outside the icon;
   only a release inside the pressed icon may toggle mute.
5. Disable/re-enable Windhawk, check Explorer teardown, and examine
   `XAML v1.0.18` logs. Compilation and runtime behavior are still
   **unverified** in this editing environment.

## Migration gates

1. **Host viability:** Windows compilation, Island activation, show/hide, transparency behavior, DPI, multimonitor placement, nonactivation and clean unloading.
2. **Backend separation:** define `OsdViewModel` and backend-neutral layout/visual state contracts. Prevent XAML objects or HWNDs from leaking across apartment boundaries; exchange only immutable, owned snapshots.
3. **First real migration:** move a single noninteractive notification surface; retain GDI+ fallback. Confirm icon/text fidelity, opacity and expiry handling.
4. **Controls:** volume/brightness with mouse, wheel and drag; then Mixer and SMTC, sharing layout with hit testing.
5. **Regression:** Win11 build variance, Explorer restarting, Windhawk unload/reload, UWP/XAML startup timing, OS theme changes, mixed DPI/HDR/SDR, CPU/GPU/working set, event floods and shutdown.

**Do not merge to `fluent-osd` until stages are functionally complete and verified on Windows.**
