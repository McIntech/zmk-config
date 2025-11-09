# Display Widgets Documentation

Esta carpeta contiene la documentación completa sobre los widgets de display disponibles en ZMK para tu Corne keyboard.

## Archivos Disponibles

### 📖 [DISPLAY_WIDGETS.md](./DISPLAY_WIDGETS.md)
**Guía completa de widgets disponibles**

Contiene:
- Descripción de cada widget (Battery, Layer, Output, Peripheral, WPM)
- Qué muestra cada widget
- Configuración necesaria para habilitar/deshabilitar
- Explicación del sistema de eventos
- Opciones avanzadas de fuentes y work queue
- Implementaciones especiales (Nice!View, Corneish Zen)

**Úsalo cuando:** Quieras entender qué hace cada widget y cómo funciona.

---

### ⚙️ [DISPLAY_WIDGET_CONFIGS.md](./DISPLAY_WIDGET_CONFIGS.md)
**9 configuraciones predefinidas listas para copiar y pegar**

Contiene:
1. ✅ Configuración Recomendada (Balance perfecto)
2. 🔋 Solo Lo Mínimo (Ahorra memoria)
3. 📊 Información Completa + WPM
4. 🎨 Mostrar Porcentaje de Batería
5. 🚀 Máximo Rendimiento (Dedicado)
6. ⚫ Pantalla Invertida (Dark Mode)
7. 💤 Pantalla Apagada en Reposo
8. 📱 Compatible con Nice!View
9. 🔧 Personalizada (Plantilla)

Tabla comparativa con memoria y performance de cada opción.

**Úsalo cuando:** Quieras cambiar rápidamente tu configuración copiando una opción.

---

### 💻 [DISPLAY_WIDGET_SOURCE.md](./DISPLAY_WIDGET_SOURCE.md)
**Código fuente completo de cada widget**

Contiene:
- Estructura de datos de cada widget (struct)
- Headers (.h) de cada widget
- Implementación (código C simplificado)
- Eventos que escucha cada widget
- Sistema de eventos de widgets
- Símbolos LVGL disponibles
- Cómo crear tu propio widget personalizado

**Úsalo cuando:** Quieras personalizar widgets o crear uno propio.

---

## Resumen Rápido

### Todos los Widgets Disponibles

| Widget | Muestra | Config | Por Defecto |
|--------|---------|--------|-------------|
| 🔋 Battery | Nivel/% de batería + carga | `CONFIG_ZMK_WIDGET_BATTERY_STATUS` | ❌ |
| ⌨️ Layer | Nombre de capa actual | `CONFIG_ZMK_WIDGET_LAYER_STATUS` | ❌ |
| 📶 Output | USB/Bluetooth + perfil | `CONFIG_ZMK_WIDGET_OUTPUT_STATUS` | ❌ |
| 📡 Peripheral | Split keyboard status | `CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS` | ❌ |
| ⌨️📊 WPM | Palabras por minuto | `CONFIG_ZMK_WIDGET_WPM_STATUS` | ❌ |

**Nota:** Actualmente todos están deshabilitados (`=n`) en tu configuración.

---

## Estado Actual de tu Corne

**Archivo:** `config/corne.conf`

```conf
CONFIG_ZMK_WIDGET_WPM_STATUS=n
CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=n
CONFIG_ZMK_WIDGET_BATTERY_STATUS_SHOW_PERCENTAGE=n
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=n  # ← Display desactivado
```

**Para activar widgets:** Necesitas cambiar estos valores a `=y` en `config/corne.conf`.

---

## Cómo Empezar (3 Pasos)

### 1️⃣ Elige una configuración
Abre [DISPLAY_WIDGET_CONFIGS.md](./DISPLAY_WIDGET_CONFIGS.md) y elige una de las 9 opciones.

**Recomendación inicial:** Opción 1 (Configuración Recomendada) - es el balance perfecto.

### 2️⃣ Copia la configuración
Copia el bloque `CONFIG_*` de tu opción elegida.

### 3️⃣ Reemplaza en tu archivo
Abre `config/corne.conf` y reemplaza la sección de display (líneas 6-14).

---

## Preguntas Frecuentes

### ❓ ¿Qué es un Widget?
Un widget es un pequeño elemento visual en el display que muestra información (batería, capa, velocidad, etc.) y se actualiza automáticamente.

### ❓ ¿Dónde aparecen los widgets?
En el display derecho de tu Corne (si tienes uno). Se distribuyen:
- **Arriba-Izquierda:** Output Status (USB/BLE)
- **Arriba-Derecha:** Battery Status
- **Abajo-Izquierda:** Layer Status
- **Abajo-Derecha:** WPM Status

### ❓ ¿Cuáles son los mejores widgets?
Recomendación:
- ✅ Battery Status (siempre útil)
- ✅ Layer Status (importante para split keyboard)
- ✅ Output Status (saber si está por USB o BLE)
- ❌ WPM (útil si te interesa medir velocidad)
- ✅ Peripheral Status (importante para split keyboard)

### ❓ ¿Cuál opción elegir?
- **Para principiante:** Opción 1 (Recomendada)
- **Para ahorrar memoria:** Opción 2 (Mínima)
- **Para máxima info:** Opción 3 (Completa)
- **Para máxima batería:** Opción 7 (Blank on Idle)

### ❓ ¿Cómo cambio después?
1. Edita `config/corne.conf` con otra opción
2. Commit y push a GitHub
3. GitHub Actions reconstruye automáticamente
4. Flashea el nuevo firmware

### ❓ ¿Qué pasa si no aparecen?
- Verifica que `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y`
- Verifica que `CONFIG_ZMK_DISPLAY=y`
- Intenta `CONFIG_ZMK_DISPLAY_INVERT=y` si la pantalla está negra

---

## Código Fuente en ZMK

Si quieres ver el código real en GitHub:

**Widgets:**
- Battery: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/widgets/battery_status.c
- Layer: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/widgets/layer_status.c
- Output: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/widgets/output_status.c
- WPM: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/widgets/wpm_status.c
- Peripheral: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/widgets/peripheral_status.c

**Display System:**
- Status Screen: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/status_screen.c
- Display Main: https://github.com/zmkfirmware/zmk/blob/main/app/src/display/main.c

---

## Crear tu Propio Widget

Si quieres un widget personalizado (como el diamante animado que viste):

1. Lee [DISPLAY_WIDGET_SOURCE.md](./DISPLAY_WIDGET_SOURCE.md) - última sección
2. Usa LVGL para dibujar (https://docs.lvgl.io/)
3. Suscríbete a eventos que te interesen
4. Configura un timer para animar

Ejemplos de widgets personalizados:
- **Bongo cat** - Gato que escribe cuando escribes
- **Diamante rotando** - Forma geométrica rotando
- **Onda animada** - Onda que se mueve
- **Contador visual** - Barras que suben/bajan

---

## Cambio Reciente en tu Repo

Hace poco, tu repo tuvo cambios sobre display:

- **Commit:** `de0486b` - "fix: revert display changes"
- **Cambios:** Los widgets fueron deshabilitados (`=n`)
- **Razón:** Probablemente para optimizar memoria

Para volver a activarlos, usa las opciones en [DISPLAY_WIDGET_CONFIGS.md](./DISPLAY_WIDGET_CONFIGS.md).

---

## Próximos Pasos

1. **Lee** [DISPLAY_WIDGETS.md](./DISPLAY_WIDGETS.md) para entender qué hace cada widget
2. **Elige** una configuración en [DISPLAY_WIDGET_CONFIGS.md](./DISPLAY_WIDGET_CONFIGS.md)
3. **Copia** el bloque `CONFIG_*` a tu `config/corne.conf`
4. **Commit y Push** a GitHub
5. **Flashea** el nuevo firmware cuando GitHub Actions termine

Si quieres personalizar o crear widgets propios, consulta [DISPLAY_WIDGET_SOURCE.md](./DISPLAY_WIDGET_SOURCE.md).

---

## Documentación Original de ZMK

- **ZMK Display Configuration:** https://zmk.dev/docs/config/displays
- **ZMK Events:** https://zmk.dev/docs/development/subsystems/events
- **LVGL Documentation:** https://docs.lvgl.io/

