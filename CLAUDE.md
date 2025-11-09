# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **ZMK (Zephyr Mechanical Keyboard) firmware configuration** for a **Corne split keyboard** with wireless Bluetooth connectivity and Nice!View display support. ZMK is an open-source keyboard firmware that allows customization of key mappings, behaviors, and hardware features.

- **Keyboard Model:** Corne (split keyboard with left and right halves)
- **MCU:** Nice Nano v2 (runs on each half)
- **Connectivity:** Wireless Bluetooth LE (supports up to 7 paired devices)
- **Display:** Nice!View integrated status display
- **Build System:** GitHub Actions (cloud-based, no local build needed)
- **Current Focus:** Testing Mod-Tap behavior variants for optimal key response

## Repository Structure

### Core Configuration
- **`config/corne.keymap`** - Key mappings, layers, and behavior definitions
- **`config/corne.conf`** - Global ZMK settings (Bluetooth, display, battery monitoring)
- **`config/west.yml`** - Zephyr manifest (project dependencies)
- **`config/boards/shields/corne/nice_view_display.dtsi`** - Display configuration (device tree)

### Build Configuration
- **`build.yaml`** - GitHub Actions matrix (board: nice_nano_v2, shields: corne_left, corne_right)
- **`.github/workflows/build.yml`** - GitHub Actions workflow (delegates to official ZMK build)

### Documentation
- **`docs/`** - Platform-specific setup guides (macos.md, windows.md, android.md)
- **`docs/DISPLAY_WIDGETS_*.md`** - Display widget configuration and implementation

## Development Workflow

### Key Points
1. **No local build required** - GitHub Actions automatically builds firmware on every push to production branch
2. **Edit → Commit → Push → Build** - Changes trigger automatic GitHub Actions workflows
3. **Firmware artifacts** - Download .uf2 files from GitHub Actions (for flashing to keyboard)

### Common Commands

**View recent commits:**
```bash
git log --oneline -10
```

**Create feature branch (if needed):**
```bash
git checkout -b feature/your-feature-name
```

**Commit changes (follow Spanish convention from project):**
```bash
git add config/
git commit -m "feat: description of changes"
git push origin production
```

**Check GitHub Actions build status:**
- Visit: https://github.com/McIntech/zmk-own-config/actions
- Look for workflow run matching your commit

### Build Targets
The GitHub Actions workflow automatically builds for:
- **Board:** nice_nano_v2
- **Shields:** corne_left (left half) and corne_right (right half)
- **Output:** Two .uf2 firmware files ready for flashing

## Configuration Architecture

### Key Concepts

**Mod-Tap Behaviors:** The project tests multiple Mod-Tap variants (mt, mt_hp, mt_rel, mt_long) with different timing and flavor settings. When held, these act as modifiers; when tapped, they send characters. Current configuration:
- `tapping-term-ms: 200` - Time before considering a key "held"
- `quick_tap_ms: 150` - Rapid tap threshold
- `flavor: tap-preferred` - Prioritizes tapping over holding

**Layers:** Multiple key layouts accessible via momentary switches (&mo 1, &mo 2, etc.)

**Shields:** Device tree abstractions for keyboard halves (corne_left, corne_right)

**Device Tree (.dtsi):** Configures hardware features like the Nice!View display with widgets:
- Battery status widget
- Output status (USB/BLE indicator)
- Layer indicator
- Logo display

### Configuration Options Reference

**`corne.conf` - System Settings:**
- Bluetooth: MAX_CONN=7, MAX_PAIRED=7 (max concurrent and paired devices)
- Battery monitoring for split keyboards (CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY)
- Display widgets (can enable/disable via CONFIG_ZMK_WIDGET_*)
- Debounce settings available (commented out)

**`corne.keymap` - Key Mappings:**
- Layers: Default layer + momentary layers accessed via &mo keys
- Mod-Tap definitions: Test multiple variants with custom timing
- Thumb key assignments: GUI, layer switches, Space, Return, Alt

## Important Patterns & Best Practices

### File Organization
- Hardware configuration separate from key mappings
- `.conf` files for system-wide ZMK settings
- `.keymap` files for key definitions and behaviors
- `.dtsi` files (device tree) for hardware abstraction

### Bluetooth Configuration
- Split keyboard uses BLE for wireless (each half is independent MCU)
- Transmission strength increased for reliability
- Battery monitoring enabled for both halves

### Display Configuration
- 9 predefined display widget configurations available (see docs/DISPLAY_WIDGET_CONFIGS.md)
- All widgets currently disabled (=n) for memory optimization
- Can be toggled via CONFIG_ZMK_WIDGET_* settings in corne.conf

### Git Workflow
- Spanish commit messages (following project convention)
- Conventional commit style: `feat:`, `fix:`, `refactor:`, etc.
- Recent focus: Mod-Tap behavior refinement and testing

## When Making Changes

### Modifying Key Mappings
1. Edit `/config/corne.keymap`
2. Update behavior definitions or key bindings
3. Commit and push to production
4. GitHub Actions automatically builds firmware
5. Download .uf2 files and flash to keyboard

### Adjusting System Settings
1. Edit `/config/corne.conf`
2. Change Bluetooth limits, display widgets, debounce, etc.
3. Commit and push
4. GitHub Actions builds new firmware

### Updating Display Configuration
1. Edit `/config/boards/shields/corne/nice_view_display.dtsi`
2. Add/modify widget configurations
3. Push to trigger rebuild

### Testing Behaviors
- The project is actively testing Mod-Tap variants - continue this pattern
- Create custom behavior definitions for testing
- Use feature branches if experimenting with significant changes

## Documentation References

- **ZMK Official Docs:** https://zmk.dev
- **ZMK Configuration Guide:** https://zmk.dev/docs/config/behaviors
- **ZMK Display Guide:** https://zmk.dev/docs/config/displays
- **LVGL (Display Library):** https://docs.lvgl.io/
- **Device Tree Syntax:** https://docs.zephyrproject.org/latest/build/dts/

## Project Status & Recent Activity

**Current Branch:** production
**Recent Focus:** Testing and refining Mod-Tap behavior variants (see last 5 commits)
**Build Status:** Check GitHub Actions for latest build artifacts

**Recent Commits Pattern:**
- feat: Mod-Tap configuration adjustments
- refactor: Keymap simplification
- fix: Configuration syntax fixes

## Notes for Future Development

- The `/docs/` directory contains platform-specific setup guides (WIP Colemak DHm layout for macOS)
- Display widget system is mature and documented; current config disables most for memory
- Split keyboard battery monitoring is enabled and configured
- No local build environment needed - all builds happen in GitHub Actions
