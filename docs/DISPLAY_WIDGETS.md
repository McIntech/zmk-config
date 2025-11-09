# Display Widgets Guide for Corne ZMK Config

Este documento contiene todas las opciones disponibles de widgets para el display del Corne keyboard.

## Widgets Disponibles en ZMK

ZMK proporciona varios widgets de display que puedes combinar para crear tu propia pantalla de estado personalizada.

---

## 1. Battery Status Widget 🔋

**Habilita/Deshabilita:**
```conf
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=y  # Muestra % en lugar de icono
```

**Qué muestra:**
- Icono de batería con nivel (0%, 5%, 25%, 50%, 75%, 100%)
- Símbolo de carga (⚡) cuando conectado a USB
- Opcionalmente: porcentaje exacto

**Ejemplo en pantalla:**
```
USB: 🔌  o  ⚡
BLE: 🔋 (con nivel)
```

**Fuente:** `/app/src/display/widgets/battery_status.c`

---

## 2. Layer Status Widget ⌨️

**Habilita/Deshabilita:**
```conf
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
```

**Qué muestra:**
- Símbolo de teclado (⌨) + nombre de la capa actual
- Se actualiza cuando cambias de capa

**Ejemplo en pantalla:**
```
⌨ BASE
⌨ DEV
⌨ NAV
```

**Fuente:** `/app/src/display/widgets/layer_status.c`

---

## 3. Output Status Widget 📶

**Habilita/Deshabilita:**
```conf
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
```

**Qué muestra:**
- USB: 🔌 (conectado por cable)
- Bluetooth:
  - 📶 Perfil# (1-5)
  - ✓ = Conectado
  - ✗ = Desconectado
  - ⚙ = Modo emparejamiento

**Ejemplo en pantalla:**
```
🔌 (USB mode)
📶 1 ✓ (BLE Profile 1, Connected)
📶 2 ✗ (BLE Profile 2, Disconnected)
⚙ (Pairing mode)
```

**Fuente:** `/app/src/display/widgets/output_status.c`

---

## 4. Peripheral Status Widget 📡

**Habilita/Deshabilita:**
```conf
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
```

**Qué muestra:**
- Solo para teclados split (tu Corne izquierdo/derecho)
- Estado de conexión entre los dos lados

**Ejemplo en pantalla:**
```
📡 ✓ (Derecho conectado)
📡 ✗ (Derecho desconectado)
```

**Fuente:** `/app/src/display/widgets/peripheral_status.c`

---

## 5. WPM Status Widget ⌨️📊

**Habilita/Deshabilita:**
```conf
CONFIG_ZMK_WIDGET_WPM_STATUS=y
```

**Qué muestra:**
- Velocidad de escritura en palabras por minuto (WPM)
- Se actualiza en tiempo real mientras escribes

**Ejemplo en pantalla:**
```
75 WPM
92 WPM
```

**Fuente:** `/app/src/display/widgets/wpm_status.c`

---

## Configuración Completa del Display

### Configuración Base (`corne.conf`)

**Para activar los widgets por defecto:**
```conf
# Display activado
CONFIG_ZMK_DISPLAY=y

# Widget de batería
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n  # Muestra icono, no %

# Otros widgets
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=n  # Desactivado por defecto para ahorrar memoria

# Pantalla de estado integrada
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y

# Fuentes (elige una)
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_LV_FONT_DEFAULT_MONTSERRAT_26=y

# Work queue dedicado (mejor rendimiento)
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y

# Otras opciones
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y  # Apaga pantalla cuando está inactivo
CONFIG_ZMK_DISPLAY_INVERT=n          # Invertir colores (para pantallas invertidas)
```

---

## Disposición Predeterminada de Widgets

En la pantalla de estado por defecto, los widgets se posicionan así:

```
┌─────────────────────────────────┐
│ 📶 1 ✓      🔋 (Battery top-right)
│                                 │
│                                 │
│                                 │
│ ⌨ BASE                  75 WPM  │
└─────────────────────────────────┘
```

- **Arriba-Izquierda:** Output Status (USB/Bluetooth)
- **Arriba-Derecha:** Battery Status
- **Abajo-Izquierda:** Layer Status
- **Abajo-Derecha:** WPM Status

---

## Opciones de Configuración Avanzadas

### Fonts Disponibles
```conf
# Tamaños disponibles: 12, 14, 16, 18, 20, 22, 24, 26, 28, etc.
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_16=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_20=y
CONFIG_ZMK_LV_FONT_DEFAULT_SMALL_MONTSERRAT_26=y
CONFIG_ZMK_LV_FONT_DEFAULT_MONTSERRAT_28=y
# ... más tamaños disponibles
```

### Work Queue Options
```conf
# Sistema (por defecto)
CONFIG_ZMK_DISPLAY_WORK_QUEUE_SYSTEM=n

# Dedicado (mejor rendimiento, más RAM)
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE=2048  # En bytes
CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_PRIORITY=5       # Menor = mayor prioridad
```

---

## Implementaciones Especiales

### Nice!View Widget

Si usas el shield Nice!View (160×68 píxeles):

```conf
# Usa widgets personalizados de Nice!View
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y
```

**Características especiales:**
- Círculos de perfil BLE (1-5) con estados visuales
- Gráfico de WPM con historial de 10 muestras
- Diseño optimizado para pantalla vertical

**Fuente:** `/app/boards/shields/nice_view/widgets/status.c`

---

### Corneish Zen Widget

Si usas el shield Corneish Zen:

**Características especiales:**
- Widgets basados en imágenes (no texto)
- Niveles de batería con íconos (0%, 5%, 25%, 50%, 75%, 100%)
- Indicadores de perfil numerados
- Estados de conexión con gráficos

**Fuente:** `/app/boards/arm/corneish_zen/widgets/`

---

## Recomendaciones para tu Corne

### Configuración Equilibrada (Defecto Recomendado)
```conf
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=n
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
```

### Solo Lo Mínimo (Ahorra Memoria)
```conf
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=n
CONFIG_ZMK_WIDGET_WPM_STATUS=n
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y
```

### Completo (Máxima Información)
```conf
CONFIG_ZMK_WIDGET_BATTERY_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=y
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=y
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y
```

---

## Sistema de Eventos de Widgets

Todos los widgets se actualizan automáticamente cuando ocurren estos eventos:

| Widget | Evento | Qué lo activa |
|--------|--------|---------------|
| Battery | `zmk_battery_state_changed` | Cambio de nivel de batería |
| Battery | `zmk_usb_conn_state_changed` | Conectar/desconectar USB |
| Layer | `zmk_layer_state_changed` | Cambiar de capa |
| Output | `zmk_endpoint_changed` | Cambiar entre USB/BLE |
| Output | `zmk_ble_active_profile_changed` | Cambiar perfil BLE |
| Peripheral | `zmk_split_peripheral_status_changed` | Desconexión split |
| WPM | `zmk_wpm_state_changed` | Cambio en velocidad de escritura |

---

## Cómo Crear Widgets Personalizados

Si quieres crear tu propio widget animado (como el diamante que viste):

1. **Usar LVGL** (Light and Versatile Graphics Library)
2. **Suscribirse a eventos** que te interesen
3. **Dibujar** usando canvas o imágenes

**Ejemplo básico:**
```c
#include <zephyr/kernel.h>
#include <zmk/display/widgets/wpm_status.h>
#include <lvgl.h>

lv_obj_t *my_custom_widget(lv_obj_t *parent) {
    lv_obj_t *widget = lv_obj_create(parent);
    lv_obj_set_size(widget, 64, 64);

    // Añade animaciones, imágenes, etc.
    // ...

    return widget;
}
```

---

## Estado Actual de tu Corne

**Archivo:** `config/corne.conf`

Actualmente tienes:
```conf
CONFIG_ZMK_WIDGET_WPM_STATUS=n           # Desactivado
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=n  # Usa sistema
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n  # Usa icono
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=n  # Desactivado
```

Para activar los widgets, necesitas cambiar `=n` a `=y` en las opciones que quieras.

---

## Referencias

- **ZMK Display Docs:** https://zmk.dev/docs/config/displays
- **ZMK Widget Source:** https://github.com/zmkfirmware/zmk/tree/main/app/src/display/widgets
- **LVGL Library:** https://lvgl.io/

