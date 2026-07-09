#!/usr/bin/env bash
# Regenerate the Corne cheatsheet: keymap-drawer/corne.svg + ~/Pictures/corne-keymap.png
# Deps: keymap-drawer (pip, with tree-sitter<0.25 and tree-sitter-devicetree<0.15),
#       rsvg-convert (brew install librsvg), python3.
set -euo pipefail
cd "$(dirname "$0")/.."

keymap -c keymap-drawer/config.yaml parse -z config/corne.keymap > /tmp/corne-parsed.yaml
keymap -c keymap-drawer/config.yaml draw /tmp/corne-parsed.yaml > keymap-drawer/corne.svg

# librsvg cannot resolve keymap-drawer's nested-<svg> glyph defs nor ids with
# colons, so rasterize a transformed copy (<symbol> defs, sanitized ids).
# Browsers render the committed corne.svg correctly as-is.
python3 - <<'EOF'
import re
svg = open('keymap-drawer/corne.svg').read()
svg = re.sub(
    r'<svg id="([^"]+)">\s*<svg [^>]*?viewBox="([^"]+)"[^>]*>(.*?)</svg>\s*</svg>',
    lambda m: f'<symbol id="{m.group(1)}" viewBox="{m.group(2)}">{m.group(3)}</symbol>',
    svg, flags=re.S).replace('mdi:', 'mdi_')
open('/tmp/corne-render.svg', 'w').write(svg)
EOF

# -b: librsvg does not paint the CSS background-color, so set it explicitly
rsvg-convert -b '#1a1b26' -w 4800 -o "$HOME/Pictures/corne-keymap.png" /tmp/corne-render.svg
echo "Wrote keymap-drawer/corne.svg and ~/Pictures/corne-keymap.png"
