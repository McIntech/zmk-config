# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a ZMK (Zephyr Mechanical Keyboard) firmware configuration repository for a Corne split keyboard. Firmware for the `nice_nano_v2` board with `corne_left` and `corne_right` shields is built **locally with west** — this repo intentionally uses no CI, and GitHub Actions is disabled.

## Build System

Firmware is built locally (full recipe with the Zephyr SDK 0.17 workarounds in the README "Building" section). Key files:

- `build.yaml`: Canonical list of board/shield build targets (nice_nano_v2 with corne_left, corne_right, settings_reset)
- `config/west.yml`: Manifest file that imports ZMK firmware dependencies from the zmkfirmware organization
- `firmware/`: Pre-built `.uf2` images, committed after each successful local build

## Configuration Files

The ZMK keyboard configuration is split into two main files in the `config/` directory:

### `config/corne.keymap`

Contains the keyboard layout: three layers (Base, Lower, Raise) with an ASCII diagram per layer, exactly 42 bindings each. Uses ZMK behavior syntax with device tree include files (`.dtsi`). macOS shortcut keys live on the Raise layer.

### `config/corne.conf`

Contains ZMK configuration options:

- Feature flags (e.g., `CONFIG_ZMK_DISPLAY=y` to enable OLED display)
- Hardware settings (RGB underglow, backlight configuration)
- Uses `CONFIG_` prefix for ZMK Kconfig options

## Development Workflow

1. **Edit configuration**: Modify `config/corne.keymap` (key layout) or `config/corne.conf` (feature flags)
2. **Build**: Run the local west build from the README "Building" section
3. **Update artifacts**: Copy the new `.uf2` files into `firmware/` and regenerate the cheatsheet with `keymap-drawer/render.sh`
4. **Flash**: UF2 bootloader (double-tap reset). Keymap-only changes need the left half only

## Git Workflow

- **Main branch**: `production` (where builds are deployed)
- All commits should be made to the `production` branch or a feature branch
- Do not add CI workflows — builds are local by design (GitHub Actions is disabled for this repo)

## Important Notes

- The actual ZMK firmware source is imported via `config/west.yml` from the zmkfirmware organization. You do not modify the core ZMK firmware in this repository
- ZMK documentation: https://zmk.dev/docs
- The keyboard uses macOS key bindings (LGUI for Command key, LALT for Option key)
- Firmware changes may require careful testing due to the split keyboard architecture (left and right halves must be built separately)
