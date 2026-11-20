# Fluent OSD — native XAML renderer experiment

**Branch:** `fluent-osd-xaml`  
**Baseline:** `fluent-osd` v1.0.1 (`8ff2d4352d8c081e78208266ff1561b5e5bfe31b`)  
**Status:** XAML Island host **prototype committed**; **not yet compiled or run on Windows**.

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
2. A native topmost no-activate Win32 host HWND with `WS_EX_NOREDIRECTIONBITMAP`.
3. A `Windows.UI.Xaml.Hosting.WindowsXamlManager` and `DesktopWindowXamlSource` attached to that HWND.
4. A native XAML visual tree: `Border`, `StackPanel`, `TextBlock` and `ProgressBar`.
5. An on-demand volume snapshot via Core Audio (default multimedia render endpoint), **not** continual polling.

This standalone module has a separate Windhawk ID (`fluent-osd-xaml-island-probe`) and does **not** install Shell hooks, suppress Windows OSD, or modify the production `mods/fluent-osd.wh.cpp`.

### Manual test

1. Open Windhawk and create a separate local mod from the entire probe source. Do **not** replace the installed Fluent OSD mod.
2. Compile it using Windhawk's included compiler. Verify there are no missing C++/WinRT/XAML headers or link errors.
3. Enable the probe; press **Ctrl+Alt+Shift+O**. A native XAML volume preview should appear near the bottom-right of the monitor under the mouse, using the current default multimedia output level.
4. Wait for the preview to hide. Repeat after switching the Windows output device and at different screen scales (100%, 125%, 150%).
5. Disable the probe and verify that Explorer remains responsive, no host HWND remains, and there are no shutdown blockers.
6. Check the Windhawk log: `XAML probe ready`, `startup failed`, `hotkey registration failed`, or an STA-exit warning.

**Do not use this prototype as a daily-driver OSD.** It has not passed a compilation, runtime, resource, or compatibility test, and its top-level transparency and rounded outside corners have not been validated. It also does not yet implement UI input, fade animations, mixer, SMTC, device notices or monitor mirroring.

### Shutdown/Explorer risk

All XAML objects are instantiated and closed on the same dedicated STA thread. The host receives an asynchronous stop signal; the plugin waits for that thread to exit **before** unloading code.

The first wait has a six-second diagnostic threshold. If the XAML runtime is stuck at shutdown, the final wait can still block Explorer: it does not abandon an executing thread and allow a use-after-unload crash. **A bounded, verified unload path is a release blocker.**

## Why system Windows.UI.Xaml first?

Styler mods apply styles to existing Windows XAML trees; Fluent OSD has no pre-existing XAML tree. Creating one requires an Island host, not copying the Styler selector engine.

This pilot uses **system `Windows.UI.Xaml`** and the documented legacy Island host. It deliberately does not bootstrap the Windows App SDK / WinUI 3 runtime inside `explorer.exe`. This reduces extra deployment dependencies for an initial feasibility test, but it does **not** prove performance, UI fidelity or the robustness of transparent overlays.

See Microsoft's [UWP XAML hosting documentation](https://learn.microsoft.com/en-us/windows/uwp/xaml-islands/using-the-xaml-hosting-api) and [Win32 C++ XAML Island example](https://learn.microsoft.com/en-us/windows/uwp/xaml-islands/host-standard-control-with-xaml-islands-cpp).

## Migration gates

1. **Host viability:** Windows compilation, Island activation, show/hide, transparency behavior, DPI, multimonitor placement, nonactivation and clean unloading.
2. **Backend separation:** define `OsdViewModel` and backend-neutral layout/visual state contracts. Prevent XAML objects or HWNDs from leaking across apartment boundaries; exchange only immutable, owned snapshots.
3. **First real migration:** move a single noninteractive notification surface; retain GDI+ fallback. Confirm icon/text fidelity, opacity and expiry handling.
4. **Controls:** volume/brightness with mouse, wheel and drag; then Mixer and SMTC, sharing layout with hit testing.
5. **Regression:** Win11 build variance, Explorer restarting, Windhawk unload/reload, UWP/XAML startup timing, OS theme changes, mixed DPI/HDR/SDR, CPU/GPU/working set, event floods and shutdown.

**Do not merge to `fluent-osd` until stages are functionally complete and verified on Windows.**
