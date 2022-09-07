#include <stdio.h> 
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define IS_RGBW true 
#define NUM_PIXELS 1

#ifndef PICO_DEFAULT_WS2812_PIN
    #define WS28128_PIN PICO_DEFAULT_WS2818_PIN 
#else
    #define WS2812_PIN 2
#endif 



static inline void put_led(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void cycle_blink () { 
   put_pixel(rand() % 16 ? 0 : 0xffffffff); 
} 


int main(void) { 

    //set_sys_clock_48();
    stdio_init_all();
    printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    while(1) { 
        // Cycle blink here for autotesting     
        sleep_ms(250); 
    }


    return 0;
} 
