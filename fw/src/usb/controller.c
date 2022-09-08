#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

void hid_task(void);

struct report {
    uint16_t buttons;
    uint8_t joy0;
    uint8_t joy1;
    uint8_t joy2;
    uint8_t joy3;
} report;

int main(void) {

    board_init();

    tusb_init();

    gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, false);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.f);
    pwm_init(slice_num, &config, true);

    while (1) {
        hid_task();
        tud_task(); // tinyusb device task
    }

    return 0;
}

void con_panic(uint16_t errcode) {

    report.buttons = errcode;
    while (1) {
        tud_task(); // tinyusb device task

        if (tud_suspended()) {
            tud_remote_wakeup();
        }

        if (tud_hid_ready()) {
            tud_hid_n_report(0x00, 0x01, &report, sizeof(report));
        }
    }
}

typedef struct {
    uint8_t r, g, b;
} RGB_t;

union {

    struct {
        uint8_t buttons[16];
        RGB_t rgb[3];
    } lights;

    uint8_t raw[25];

} light_data;

void hid_task(void) {

    const uint32_t interval_ms = 1;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms) { 
        return; 
    } 

    start_ms += interval_ms;

    report.buttons = ((board_millis() / 1000) % 2) << ((board_millis() / 2000) % 16);
    report.joy0 = light_data.lights.rgb[2].g;
    report.joy1 = light_data.lights.rgb[2].b;
    report.joy2 = ((board_millis() / 1000) % 4) * 64;
    report.joy3 = board_millis() / 2;
    int fade = report.joy1;
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);

    // Remote wakeup
    if (tud_suspended())
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }

    if (tud_hid_ready())
    {
        tud_hid_n_report(0x00, 0x01, &report, sizeof(report));
    }
}

// Device callbacks
// Invoked when device is mounted
void tud_mount_cb(void) {
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
    (void)remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
}

// USB HID

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
    // TODO not Implemented
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
//
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {

    if (report_id == 2 && report_type == HID_REPORT_TYPE_OUTPUT && buffer[0] == 2 && bufsize >= sizeof(light_data)) //light data {
        size_t i = 0;
        for (i; i < sizeof(light_data); i++) {
            light_data.raw[i] = buffer[i + 1];
        }
    }

    tud_hid_report(0, buffer, bufsize);
}
