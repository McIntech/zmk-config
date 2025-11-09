# Display Widget Configuration Presets

Aquí encontrarás configuraciones predefinidas que puedes copiar directamente a tu `config/corne.conf`.

---

## ✅ Opción 1: Configuración Recomendada (Defecto)

**Descripción:** Balance entre información útil y uso de memoria. Muestra batería, capa actual y estado de conexión.

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Battery Status Widget
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n

# Layer Status Widget
CONFIG_ZMK_WIDGET_LAYER_STATUS=y

# Output Status Widget (USB/BLE)
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y

# Peripheral Status Widget (para split keyboards)
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y

# WPM Status Widget (palabras por minuto)
CONFIG_ZMK_WIDGET_WPM_STATUS=n

# Display configuration
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=n
```

**Resultado en pantalla:**
```
┌─────────────────────────────────┐
│ 📶 1 ✓          🔋               │
│                                 │
│                                 │
│                                 │
│ ⌨ BASE                  (blank) │
└─────────────────────────────────┘
```

---

## 🔋 Opción 2: Solo Información Esencial

**Descripción:** Mínimo de widgets para ahorrar memoria y batería. Solo batería y capa actual.

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Minimal ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Battery Status Widget ONLY
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n

# Layer Status Widget ONLY
CONFIG_ZMK_WIDGET_LAYER_STATUS=y

# Disable others
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=n
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=n
CONFIG_ZMK_WIDGET_WPM_STATUS=n

# Display configuration
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=n
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=n
```

**Resultado en pantalla:**
```
┌─────────────────────────────────┐
│               🔋               │
│                                 │
│                                 │
│                                 │
│ ⌨ BASE                          │
└─────────────────────────────────┘
```

---

## 📊 Opción 3: Información Completa + WPM

**Descripción:** Todos los widgets habilitados. Muestra batería, capa, conexión, y velocidad de escritura en tiempo real.

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Full ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Enable ALL widgets
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=y

CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=y

# Display configuration - optimized for performance
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=n
```

**Resultado en pantalla:**
```
┌─────────────────────────────────┐
│ 📶 1 ✓           100%           │
│                                 │
│                                 │
│                                 │
│ ⌨ BASE                 85 WPM  │
└─────────────────────────────────┘
```

---

## 🎨 Opción 4: Mostrar Porcentaje de Batería

**Descripción:** Como Opción 1 pero con el porcentaje exacto de batería en lugar del icono.

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Battery Percentage ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Battery Status with PERCENTAGE
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=y  # ← Cambio principal

# Other widgets
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=n

# Display configuration
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=n
```

**Resultado en pantalla:**
```
┌─────────────────────────────────┐
│ 📶 1 ✓            85%            │
│                                 │
│                                 │
│                                 │
│ ⌨ BASE                          │
└─────────────────────────────────┘
```

---

## 🚀 Opción 5: Máximo Rendimiento (Dedicado)

**Descripción:** Usa un thread dedicado para el display (mejor rendimiento, más RAM).

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Max Performance ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# All widgets
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n

CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=y

# Display configuration - DEDICATED THREAD
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE=2048
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_PRIORITY=5
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=n
```

---

## ⚫ Opción 6: Pantalla Invertida (Dark Mode)

**Descripción:** Para pantallas OLED con fondo oscuro. Invierte los colores del display.

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Inverted (Dark Mode) ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Widgets
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n

CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=n

# Display configuration - INVERTED
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=y  # ← Cambio principal
```

---

## 💤 Opción 7: Pantalla Apagada en Reposo

**Descripción:** Display se apaga cuando no hay actividad. Ahorra batería significativamente.

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Blank on Idle ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Widgets
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n

CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=n

# Display configuration - BLANK ON IDLE
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y  # ← Apaga pantalla en reposo
CONFIG_ZMK_DISPLAY_INVERT=n
```

---

## 📱 Opción 8: Compatible con Nice!View Shield

**Descripción:** Optimizado para el shield Nice!View (160×68 píxeles, pantalla vertical).

**Copia esto a `config/corne.conf`:**

```conf
# === Display Widgets Configuration - Nice!View ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# Nice!View uses custom widgets
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y

# Still can enable individual widgets
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=y

# Display configuration - Nice!View optimized
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_20=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
CONFIG_ZMK_DISPLAY_INVERT=n
```

---

## 🔧 Opción 9: Personalizada - Crea la Tuya

**Descripción:** Plantilla para crear tu propia configuración.

**Copia esto a `config/corne.conf` y modifica según necesites:**

```conf
# === Display Widgets Configuration - Custom ===

# Enable display
CONFIG_ZMK_DISPLAY=y

# === Choose which widgets to enable ===
# Battery widget (muestra 🔋 o %)
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n  # y=show %, n=show icon

# Layer widget (muestra ⌨ + nombre capa)
CONFIG_ZMK_WIDGET_LAYER_STATUS=y

# Output/Connection widget (muestra 🔌 o 📶 + estado BLE)
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y

# Peripheral widget (solo para split keyboards - muestra 📡 + estado)
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y

# WPM widget (muestra velocidad de escritura en tiempo real)
CONFIG_ZMK_WIDGET_WPM_STATUS=n

# === Display Features ===
# Built-in status screen (vs custom)
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y

# Font selection (elige UNO)
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_16=n
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_20=n
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y  # ← Recomendado
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_28=n

# Work queue (dedicado = más rápido pero más RAM)
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y

# Apagar en reposo (ahorra batería)
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y

# Invertir colores (para pantallas oscuras)
CONFIG_ZMK_DISPLAY_INVERT=n

# === Advanced ===
# Solo si usas trabajo dedicado
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE=2048
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_PRIORITY=5
```

---

## 📋 Tabla de Comparación

| Opción | Batería | Capa | Conexión | WPM | Memoria | Performance |
|--------|---------|------|----------|-----|---------|-------------|
| 1 (Recomendada) | ✓ | ✓ | ✓ | ✗ | Media | Bueno |
| 2 (Mínima) | ✓ | ✓ | ✗ | ✗ | Baja | Excelente |
| 3 (Completa) | ✓ | ✓ | ✓ | ✓ | Alta | Bueno |
| 4 (% Batería) | ✓ | ✓ | ✓ | ✗ | Media | Bueno |
| 5 (Dedicada) | ✓ | ✓ | ✓ | ✓ | Alta | Excelente |
| 6 (Dark) | ✓ | ✓ | ✓ | ✗ | Media | Bueno |
| 7 (Idle) | ✓ | ✓ | ✓ | ✗ | Media | Mejor (Batería) |
| 8 (Nice!View) | ✓ | ✓ | ✓ | ✓ | Alta | Excelente |

---

## 📝 Cómo Usar Estas Configuraciones

1. **Abre tu archivo:** `config/corne.conf`

2. **Busca la sección de display** (líneas 6-14 aproximadamente):
   ```conf
   # No WPM widget
   # https://zmk.dev/docs/config/displays
   CONFIG_ZMK_WIDGET_WPM_STATUS=n
   CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=n
   # ... etc
   ```

3. **Reemplaza esa sección** con una de las opciones arriba

4. **Guarda el archivo**

5. **Sube a GitHub** (o compila localmente) para que se reconstruya el firmware

6. **Flashea el nuevo firmware** a tu Corne

---

## ⚠️ Notas Importantes

- **Memoria:** Cada widget adicional usa más RAM. El nice!nano tiene ~24KB de RAM disponible.
- **Batería:** Los widgets que se actualizan constantemente (como WPM) usan más energía.
- **Pantalla en Reposo:** Activar `BLANK_ON_IDLE` ahorra batería significativamente.
- **Thread Dedicado:** `DISPLAY_WORK_QUEUE_DEDICATED=y` mejora el rendimiento pero usa más RAM.

---

## 🔄 Cambiar Entre Opciones

Si quieres cambiar después:

1. Edita `config/corne.conf` con otra opción
2. Commit y push
3. GitHub Actions reconstruirá automáticamente
4. Descarga el nuevo `.uf2` y flashea

---

## ¿Necesitas Ayuda?

- **¿No aparecen los widgets?** Asegúrate de que `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y`
- **¿Pantalla en blanco?** Intenta `CONFIG_ZMK_DISPLAY_INVERT=y`
- **¿Lento?** Activa `CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y`
- **¿Poca batería?** Activa `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y`

