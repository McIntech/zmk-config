#if IS_ENABLED(CONFIG_ZMK_DISPLAY)

#include <zephyr/kernel.h>
#include <zephyr/types.h>
#include <zephyr/display/cfb.h>
#include <zmk/display.h>
#include <zmk/usb.h>
#include <zmk/ble.h>
#include <zmk/battery.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/layer_state_changed.h>

static void draw_status_screen(struct zmk_display_work_cb_node *cb_node, struct k_work *work) {
    struct display_device *display = cb_node->display;
    int display_width;
    int display_height;
    int line_height = 10;
    int y_offset = 0;

    if (display == NULL) {
        return;
    }

    display_width = cfb_get_display_parameter(display, CFB_DISPLAY_WIDTH);
    display_height = cfb_get_display_parameter(display, CFB_DISPLAY_HEIGHT);

    cfb_framebuffer_clear(display);

    // Draw battery info
    uint8_t battery_level = zmk_battery_state_of_charge();
    char battery_str[32];
    snprintf(battery_str, sizeof(battery_str), "Battery: %d%%", battery_level);
    cfb_print(display, battery_str, 0, y_offset);
    y_offset += line_height;

    // Draw layer info
    zmk_keymap_layer_state_t layer_state = zmk_keymap_layer_state;
    char layer_str[32];
    snprintf(layer_str, sizeof(layer_str), "Layer: %u", 31 - __builtin_clz(layer_state));
    cfb_print(display, layer_str, 0, y_offset);
    y_offset += line_height;

    // Draw BLE/USB status
    zmk_usb_conn_state_t usb_state = zmk_usb_get_conn_state();
    char status_str[32];
    if (usb_state == ZMK_USB_CONN_HID) {
        snprintf(status_str, sizeof(status_str), "USB: Connected");
    } else {
        uint8_t profile = zmk_ble_active_profile_index;
        snprintf(status_str, sizeof(status_str), "BLE: Prof %d", profile);
    }
    cfb_print(display, status_str, 0, y_offset);

    cfb_framebuffer_finalize(display);
}

int zmk_display_init(void) {
    return 0;
}

#endif
