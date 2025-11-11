# ZMK Corne Configuration

Configuración completa de teclado Corne split wireless con ZMK.

## Hardware

- **Keyboard**: Corne (6x3+3 layout)
- **Board**: 2x nice_nano_v2
- **Display**: 2x SSD1306 OLED (128x32) - I2C
- **Connectivity**: Bluetooth Low Energy (BLE) split
- **Features**:
  - Acentos españoles (á, é, í, ó, ú, ñ)
  - Display con widgets (batería, layer, status)
  - Split wireless con lado central y periférico

## Estructura de Archivos

```
config/
├── corne.keymap      # Mapeo de teclas (ambos lados)
├── corne.conf        # Configuración (se aplica a ambos lados)
├── corne.dtsi        # Configuración del display I2C SSD1306
└── west.yml          # Dependencias del proyecto
```

## Configuración de Split Keyboard

**Importante**: La configuración `corne.conf` se aplica a AMBOS lados del teclado.

- **Lado Izquierdo**: Actúa como `CENTRAL` (se conecta a la PC vía BLE/USB)
- **Lado Derecho**: Actúa como `PERIPHERAL` (se conecta al izquierdo vía BLE)

El rol de cada lado se define automáticamente en el shield según el archivo que compiles:
- `shield: corne_left` → Central role
- `shield: corne_right` → Peripheral role

## Build y Flasheo

### Compilar

```bash
# Lado izquierdo (central)
west build -s zmk/app -b nice_nano_v2 -- -DSHIELD=corne_left

# Lado derecho (periférico)
west build -s zmk/app -b nice_nano_v2 -- -DSHIELD=corne_right
```

### Flashear

1. Conecta el lado izquierdo a la PC vía USB
2. Copia `build/zephyr/zmk.uf2` al volumen "NICENANO"
3. Desconecta y repite con el lado derecho

## Configuración de Acentos Españoles

El keymap incluye soporte para:
- **á** - presiona la tecla de acento en la capa
- **é** - presiona la tecla de acento en la capa
- **í** - presiona la tecla de acento en la capa
- **ó** - presiona la tecla de acento en la capa
- **ú** - presiona la tecla de acento en la capa
- **ñ** - presiona la tecla de acento en la capa

Los acentos funcionan con `Option + E` (macOS) o combinaciones equivalentes en Linux.

## Display OLED (SSD1306)

El lado izquierdo muestra:
- **Batería**: Porcentaje de carga
- **Layer**: Layer activo actual
- **Status**: Conexión USB/BLE

El lado derecho muestra: (opcional, requiere configuración)
- Estado de batería del periférico

## Conexión Bluetooth

### Emparejamiento Inicial

1. **Limpiar bonos previos**:
   - En macOS: Preferencias > Bluetooth > Olvidar "Corne"

2. **Reset en el teclado**:
   - Presiona `mo 2` (Layer 2) + primera tecla (BT_CLR)
   - Espera 5 segundos

3. **Emparejar**:
   - Enciende lado DERECHO primero
   - Luego enciende lado IZQUIERDO
   - Espera 10-15 segundos
   - Busca "Corne" en Bluetooth y conecta

### Solución de Problemas

**El lado derecho no se conecta al izquierdo:**
- Verifica que ambos tengan el firmware correcto
- Reset: Presiona el botón físico del lado derecho 2 veces
- Intenta emparejar de nuevo

**Desconexiones frecuentes:**
- Acerca el lado derecho más al izquierdo
- Aleja el teclado de otros dispositivos 2.4GHz
- Intenta en una ubicación diferente

## Customización

### Cambiar layout de teclas

Edita `config/corne.keymap`:
```c
bindings = <
  &kp TAB  &kp Q  &kp W  // etc
  // ...
>;
```

### Agregar macros nuevas

En `config/corne.keymap`, dentro de `macros {}`:
```c
mi_macro: mi_macro {
    compatible = "zmk,behavior-macro";
    #binding-cells = <0>;
    bindings = <&kp A &kp B>;
};
```

### Configurar capas (layers)

En el `keymap`, define nuevas capas:
```c
raise_layer {
    display-name = "Raise";
    bindings = < /* tus keybindings */ >;
};
```

## Recursos

- **ZMK Documentation**: https://zmk.dev/docs
- **ZMK GitHub**: https://github.com/zmkfirmware/zmk
- **Corne Repository**: https://github.com/foostan/crkbd

## Notas

- Los cambios en `corne.conf` requieren recompilar
- Los cambios en `corne.keymap` requieren recompilar
- Los cambios en `corne.dtsi` requieren recompilar
- El firmware se guarda en `build/zephyr/zmk.uf2`

## Licencia

Este proyecto sigue la licencia MIT de ZMK.
