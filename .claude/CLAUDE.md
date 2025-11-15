# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a ZMK (Zephyr Mechanical Keyboard) firmware configuration repository for a Corne split keyboard. The project uses the official ZMK build system and GitHub Actions to compile firmware for the `nice_nano_v2` board with `corne_left` and `corne_right` shields.

## Build System

The firmware is built using GitHub Actions with the official ZMK build workflow. The build configuration is defined in:
- `build.yaml`: Specifies the board/shield combinations to build (nice_nano_v2 with corne_left and corne_right)
- `config/west.yml`: Manifest file that imports ZMK firmware dependencies from the zmkfirmware organization
- `.github/workflows/build.yml`: Triggers the official ZMK build workflow from `zmkfirmware/zmk/.github/workflows/build-user-config.yml@v0.3`

When you push to the repository or open a PR, GitHub Actions automatically builds the firmware. The compiled `.uf2` files are attached as build artifacts.

## Configuration Files

The ZMK keyboard configuration is split into two main files in the `config/` directory:

### `config/corne.keymap`
Contains the keyboard layout and behaviors. Key sections:
- **Macros**: Custom key sequences for common actions (e.g., `vol_up`, `spootlight` for Spotlight search, `accent_dead` for accent characters)
- **Behaviors**: Custom key behaviors and key mappings
- **Layers**: Multiple keyboard layers for different key functions
- Uses ZMK behavior syntax with device tree include files (`.dtsi`)

### `config/corne.conf`
Contains ZMK configuration options:
- Feature flags (e.g., `CONFIG_ZMK_DISPLAY=y` to enable OLED display)
- Hardware settings (RGB underglow, backlight configuration)
- Uses `CONFIG_` prefix for ZMK Kconfig options

## Development Workflow

1. **Edit configuration**: Modify `config/corne.keymap` (key layout/macros) or `config/corne.conf` (feature flags)
2. **Build & Test**: Push changes to GitHub. The build workflow automatically compiles firmware
3. **Review Build Artifacts**: GitHub Actions attaches the compiled `.uf2` files to the workflow run
4. **Flash to Keyboard**: Download the `.uf2` file and flash it to the keyboard using UF2 bootloader

## Git Workflow

- **Main branch**: `production` (where builds are deployed)
- All commits should be made to the `production` branch or a feature branch
- The GitHub Actions build is triggered on push and pull requests

## Important Notes

- The actual ZMK firmware source is imported via `config/west.yml` from the zmkfirmware organization. You do not modify the core ZMK firmware in this repository
- ZMK documentation: https://zmk.dev/docs
- The keyboard uses macOS key bindings (LGUI for Command key, LALT for Option key)
- Firmware changes may require careful testing due to the split keyboard architecture (left and right halves must be built separately)
