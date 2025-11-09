# ZMK Display Widget Source Code Reference

Este documento contiene la referencia del código fuente de cada widget en ZMK. Útil si quieres personalizar o crear widgets propios.

---

## 1. Battery Status Widget

**Ubicación en ZMK:**
- Código: `/app/src/display/widgets/battery_status.c`
- Header: `/app/include/zmk/display/widgets/battery_status.h`

### Header (battery_status.h)

```c
#pragma once

#include <zephyr/kernel.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/usb_conn_state_changed.h>

struct zmk_widget_battery_status {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_battery_status_init(struct zmk_widget_battery_status *widget,
                                    lv_obj_t *parent);
lv_obj_t *zmk_widget_battery_status_obj(struct zmk_widget_battery_status *widget);
```

### Implementación (battery_status.c) - Resumen

```c
// El widget escucha a estos eventos:
// - zmk_battery_state_changed: cuando cambia el nivel de batería
// - zmk_usb_conn_state_changed: cuando se conecta/desconecta USB

// Los estados que puede mostrar:
// 🔋 (0%), 🔋 (25%), 🔋 (50%), 🔋 (75%), 🔋 (100%)
// ⚡ (cargando)

// O en modo porcentaje:
// "100%", "75%", "50%", "25%", "0%"

static void set_battery_symbol(lv_obj_t *label, uint8_t level, bool usb_present) {
    char text[5] = {};

    if (usb_present) {
        strcpy(text, LV_SYMBOL_CHARGE);  // ⚡
    } else if (level > 95) {
        strcpy(text, LV_SYMBOL_BATTERY_FULL);  // 🔋 (llena)
    } else if (level > 66) {
        strcpy(text, LV_SYMBOL_BATTERY_3);     // 🔋 (3/4)
    } else if (level > 33) {
        strcpy(text, LV_SYMBOL_BATTERY_2);     // 🔋 (1/2)
    } else if (level > 10) {
        strcpy(text, LV_SYMBOL_BATTERY_1);     // 🔋 (1/4)
    } else {
        strcpy(text, LV_SYMBOL_BATTERY_EMPTY); // 🔋 (vacía)
    }

    lv_label_set_text(label, text);
}
```

**Configuración disponible:**
- `CONFIG_ZMK_WIDGET_BATTERY_STATUS` - Habilitar/deshabilitar
- `CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE` - Mostrar % en lugar de icono

---

## 2. Layer Status Widget

**Ubicación en ZMK:**
- Código: `/app/src/display/widgets/layer_status.c`
- Header: `/app/include/zmk/display/widgets/layer_status.h`

### Header (layer_status.h)

```c
#pragma once

#include <zephyr/kernel.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/events/layer_state_changed.h>

struct zmk_widget_layer_status {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_layer_status_init(struct zmk_widget_layer_status *widget,
                                  lv_obj_t *parent);
lv_obj_t *zmk_widget_layer_status_obj(struct zmk_widget_layer_status *widget);
```

### Implementación (layer_status.c) - Resumen

```c
// El widget escucha a este evento:
// - zmk_layer_state_changed: cuando cambias de capa

// Muestra:
// ⌨ (icono de teclado) + nombre de la capa

// Por ejemplo:
// ⌨ BASE
// ⌨ DEV
// ⌨ LOWER
// ⌨ RAISE

static void set_layer_symbol(lv_obj_t *label) {
    // Obtiene el nombre de la capa actual
    uint8_t active_layer = zmk_keymap_highest_layer_active();

    char layer_name[20] = {};

    // Mapea números de capa a nombres
    // (esto depende de tu configuración del keymap)
    // En el archivo .dtsi defines los nombres

    snprintf(layer_name, sizeof(layer_name),
             "%s %s", LV_SYMBOL_KEYBOARD, name);

    lv_label_set_text(label, layer_name);
}
```

**Configuración disponible:**
- `CONFIG_ZMK_WIDGET_LAYER_STATUS` - Habilitar/deshabilitar

---

## 3. Output Status Widget

**Ubicación en ZMK:**
- Código: `/app/src/display/widgets/output_status.c`
- Header: `/app/include/zmk/display/widgets/output_status.h`

### Header (output_status.h)

```c
#pragma once

#include <zephyr/kernel.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/ble_active_profile_changed.h>

struct zmk_widget_output_status {
    sys_snode_t node;
    lv_obj_t *obj;
    enum zmk_endpoint endpoint;
    uint8_t active_profile_index;
    bool active;
};

int zmk_widget_output_status_init(struct zmk_widget_output_status *widget,
                                   lv_obj_t *parent);
lv_obj_t *zmk_widget_output_status_obj(struct zmk_widget_output_status *widget);
```

### Implementación (output_status.c) - Resumen

```c
// El widget escucha a estos eventos:
// - zmk_endpoint_changed: cuando cambias entre USB y Bluetooth
// - zmk_ble_active_profile_changed: cuando cambias de perfil BLE

// Estados que puede mostrar:

// USB:
// 🔌 (conectado por USB)

// Bluetooth:
// 📶 1 ✓ (Perfil 1, conectado)
// 📶 1 ✗ (Perfil 1, desconectado)
// 📶 1 ⚙ (Perfil 1, modo emparejamiento)
// 📶 2 ✓ ... etc (para perfiles 2-5)

static void set_status_symbol(lv_obj_t *label) {
    char status[10] = {};

    if (endpoint == ZMK_ENDPOINT_USB) {
        strcpy(status, LV_SYMBOL_USB);  // 🔌
    } else {  // Bluetooth
        uint8_t profile = active_profile_index + 1;  // 1-5

        char *connection_symbol;
        if (active) {
            connection_symbol = LV_SYMBOL_OK;  // ✓
        } else {
            connection_symbol = LV_SYMBOL_CLOSE;  // ✗
        }

        snprintf(status, sizeof(status),
                 "%s %d %s",
                 LV_SYMBOL_WIFI,    // 📶
                 profile,
                 connection_symbol);
    }

    lv_label_set_text(label, status);
}
```

**Configuración disponible:**
- `CONFIG_ZMK_WIDGET_OUTPUT_STATUS` - Habilitar/deshabilitar

**Nota:** Los símbolos LVGL disponibles incluyen:
- `LV_SYMBOL_USB` = 🔌
- `LV_SYMBOL_WIFI` = 📶
- `LV_SYMBOL_OK` = ✓
- `LV_SYMBOL_CLOSE` = ✗
- `LV_SYMBOL_SETTINGS` = ⚙

---

## 4. Peripheral Status Widget

**Ubicación en ZMK:**
- Código: `/app/src/display/widgets/peripheral_status.c`
- Header: `/app/include/zmk/display/widgets/peripheral_status.h`

### Header (peripheral_status.h)

```c
#pragma once

#include <zephyr/kernel.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/events/split_peripheral_status_changed.h>

struct zmk_widget_peripheral_status {
    sys_snode_t node;
    lv_obj_t *obj;
    bool connected;
};

int zmk_widget_peripheral_status_init(struct zmk_widget_peripheral_status *widget,
                                       lv_obj_t *parent);
lv_obj_t *zmk_widget_peripheral_status_obj(struct zmk_widget_peripheral_status *widget);
```

### Implementación (peripheral_status.c) - Resumen

```c
// El widget escucha a este evento:
// - zmk_split_peripheral_status_changed: cambio en conexión del lado derecho/izquierdo

// Solo aparece en el lado del periférico (lado secundario) del split keyboard

// Estados que puede mostrar:
// 📡 ✓ (lado derecho conectado)
// 📡 ✗ (lado derecho desconectado)

static void set_status_symbol(lv_obj_t *label) {
    char status[10] = {};

    if (connected) {
        snprintf(status, sizeof(status),
                 "%s %s",
                 LV_SYMBOL_WIFI,    // 📡
                 LV_SYMBOL_OK);     // ✓
    } else {
        snprintf(status, sizeof(status),
                 "%s %s",
                 LV_SYMBOL_WIFI,    // 📡
                 LV_SYMBOL_CLOSE);  // ✗
    }

    lv_label_set_text(label, status);
}
```

**Configuración disponible:**
- `CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS` - Habilitar/deshabilitar

---

## 5. WPM Status Widget

**Ubicación en ZMK:**
- Código: `/app/src/display/widgets/wpm_status.c`
- Header: `/app/include/zmk/display/widgets/wpm_status.h`

### Header (wpm_status.h)

```c
#pragma once

#include <zephyr/kernel.h>
#include <zmk/events/wpm_state_changed.h>

struct zmk_widget_wpm_status {
    sys_snode_t node;
    lv_obj_t *obj;
    uint16_t wpm;
};

int zmk_widget_wpm_status_init(struct zmk_widget_wpm_status *widget,
                                lv_obj_t *parent);
lv_obj_t *zmk_widget_wpm_status_obj(struct zmk_widget_wpm_status *widget);
```

### Implementación (wpm_status.c) - Resumen

```c
// El widget escucha a este evento:
// - zmk_wpm_state_changed: cambio en la velocidad de escritura

// Muestra:
// El valor numérico de WPM (palabras por minuto)

// Por ejemplo:
// 75
// 92
// 120

static void set_wpm_symbol(lv_obj_t *label) {
    char wpm_text[5] = {};

    // wpm es el valor actual en palabras por minuto
    snprintf(wpm_text, sizeof(wpm_text), "%u", wpm);

    lv_label_set_text(label, wpm_text);
}

// El widget también realiza el cálculo de WPM basado en:
// - Número de keystrokes (pulsaciones de tecla)
// - Tiempo transcurrido
// - Fórmula: WPM = (keystrokes / 5) / minutos

#define ZMK_WPM_COUNTER_EVENT 100  // ms entre updates
```

**Configuración disponible:**
- `CONFIG_ZMK_WIDGET_WPM_STATUS` - Habilitar/deshabilitar

---

## Default Status Screen Layout

**Ubicación en ZMK:**
- Código: `/app/src/display/status_screen.c`

### Estructura de Pantalla Predefinida

```c
lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    // Estilo base
    lv_obj_set_style_bg_color(screen,
                              lv_color_hex(0x000000),
                              0);

    // Widgets en posiciones fijas:

    // 1. Battery - arriba-derecha
    struct zmk_widget_battery_status *battery = ...;
    lv_obj_align(zmk_widget_battery_status_obj(battery),
                 LV_ALIGN_TOP_RIGHT, -2, 2);

    // 2. Output Status - arriba-izquierda
    struct zmk_widget_output_status *output = ...;
    lv_obj_align(zmk_widget_output_status_obj(output),
                 LV_ALIGN_TOP_LEFT, 2, 2);

    // 3. Peripheral Status - arriba-izquierda (debajo de output)
    struct zmk_widget_peripheral_status *peripheral = ...;
    lv_obj_align(zmk_widget_peripheral_status_obj(peripheral),
                 LV_ALIGN_TOP_LEFT, 2, 20);

    // 4. Layer Status - abajo-izquierda
    struct zmk_widget_layer_status *layer = ...;
    lv_obj_align(zmk_widget_layer_status_obj(layer),
                 LV_ALIGN_BOTTOM_LEFT, 2, -2);

    // 5. WPM Status - abajo-derecha
    struct zmk_widget_wpm_status *wpm = ...;
    lv_obj_align(zmk_widget_wpm_status_obj(wpm),
                 LV_ALIGN_BOTTOM_RIGHT, -2, -2);

    return screen;
}
```

---

## Sistema de Eventos de Widgets

Todos los widgets usan el sistema de eventos de ZMK para actualizarse automáticamente:

```c
// Ejemplo: Widget escuchando a eventos

ZMK_DISPLAY_WIDGET_LISTENER(widget_name,
                            struct zmk_widget_name,
                            handle_event,
                            zmk_event_type)

ZMK_SUBSCRIPTION(widget_name, zmk_event_type);

// El macro ZMK_SUBSCRIPTION registra el widget para escuchar el evento
// Cuando ocurre el evento, se llama a handle_event()
```

---

## LVGL Symbols Disponibles

Los widgets usan símbolos LVGL para mostrar iconos:

```c
LV_SYMBOL_BATTERY_FULL       // 🔋 (llena)
LV_SYMBOL_BATTERY_3          // 🔋 (3/4)
LV_SYMBOL_BATTERY_2          // 🔋 (1/2)
LV_SYMBOL_BATTERY_1          // 🔋 (1/4)
LV_SYMBOL_BATTERY_EMPTY      // 🔋 (vacía)
LV_SYMBOL_CHARGE             // ⚡ (cargando)

LV_SYMBOL_KEYBOARD           // ⌨ (teclado)

LV_SYMBOL_USB                // 🔌 (USB)
LV_SYMBOL_WIFI               // 📶 (WiFi/Bluetooth)

LV_SYMBOL_OK                 // ✓ (OK)
LV_SYMBOL_CLOSE              // ✗ (CLOSE)
LV_SYMBOL_SETTINGS           // ⚙ (settings)
```

---

## Cómo Crear tu Propio Widget

Si quieres crear un widget personalizado (como el diamante animado):

```c
#include <zephyr/kernel.h>
#include <lvgl.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/events/key_press.h>  // O el evento que quieras escuchar

// 1. Define la estructura del widget
struct zmk_widget_my_animation {
    sys_snode_t node;
    lv_obj_t *obj;
    lv_obj_t *canvas;  // Para dibujar
    uint16_t rotation;  // Para rotar el diamante
};

// 2. Crea funciones de inicialización
int zmk_widget_my_animation_init(struct zmk_widget_my_animation *widget,
                                  lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 64, 64);

    // Canvas para dibujar
    widget->canvas = lv_canvas_create(widget->obj);
    lv_obj_center(widget->canvas);

    return 0;
}

// 3. Crea una función para animar
static void animate_diamond(lv_obj_t *canvas) {
    widget->rotation += 5;
    if (widget->rotation >= 360) {
        widget->rotation = 0;
    }

    // Dibujar el diamante rotado
    lv_canvas_fill_bg(canvas, lv_color_hex(0x000000), 255);

    // Usar LVGL draw para rotar y dibujar
    // ...
}

// 4. Configura un timer para animar
lv_timer_create(animate_diamond, 50, canvas);  // Actualiza cada 50ms

// 5. Haz que escuche eventos (opcional)
ZMK_DISPLAY_WIDGET_LISTENER(my_animation,
                            struct zmk_widget_my_animation,
                            handle_my_event,
                            zmk_key_press)
```

---

## Referencias

- **ZMK Display Docs:** https://zmk.dev/docs/config/displays
- **ZMK Widget Source:** https://github.com/zmkfirmware/zmk/tree/main/app/src/display/widgets
- **LVGL Documentation:** https://docs.lvgl.io/
- **LVGL Symbols:** https://docs.lvgl.io/8.3/overview/font.html

