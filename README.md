# ZMK Config

> Personal firmware configuration for a split mechanical keyboard.

## Description

Personal [ZMK](https://zmk.dev) firmware build for a split wireless mechanical keyboard.
Defines keymap layers, behaviors, combos, and any custom modules used in the build.

## Tech Stack

- ZMK firmware (Zephyr RTOS)
- GitHub Actions for cloud-built `.uf2` artifacts

## Getting Started

```bash
git clone git@github.com:McIntech/zmk-config.git
cd zmk-config
# Edit config/<board>.keymap and config/<board>.conf
# Push to GitHub — Actions will build the firmware automatically
```

## Build

The `.github/workflows/build.yml` workflow runs on every push and produces
`.uf2` files as workflow artifacts. Download them from the Actions tab.

## Project Structure

```
boards/    # Board / shield definitions
config/    # Keymap, configuration and west manifest
modules/   # Additional ZMK modules
build.yaml # Multi-board build matrix
```

## Branches

| Branch       | Purpose                            |
| ------------ | ---------------------------------- |
| `develop`    | Work-in-progress keymap iterations |
| `production` | Stable, daily-driver firmware      |

## Status

![Status](https://img.shields.io/badge/status-active-brightgreen)
