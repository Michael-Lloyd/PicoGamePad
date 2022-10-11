// lib/ws2812.cpp

/*
 *  Author:     Michael Lloyd (micl.dev)
 *  Version:    1.0.0
 *  Date:       2/10/22
 *
 *      __   ___.--'_`. 
 *     ( _`.'. -   'o` ) 
 *     _\.'_'      _.-'  
 *     ( `. )    //`    
 *     \_`-'`---'\__,   
 *      \`        \`--    
 *
 */

#include "WS2812.hpp"
#include "WS2812.pio.h"

// ================================================================================================
// FIXME
// ================================================================================================


// ========================================================
// FIXME
WS2812::WS2812(
        uint pin, 
        uint length, 
        PIO pio, 
        uint sm) {

    initialise(pin, length, pio, sm, NONE, GREEN, RED, BLUE);

}

// ========================================================
// FIXME
WS2812::WS2812(
        uint pin, 
        uint length, 
        PIO pio, 
        uint sm, 
        WS2812Format format) {

    switch (format) {
        case FORMAT_RGB:
            initialise(pin, length, pio, sm, 
                    NONE, RED, GREEN, BLUE);
            break;
        case FORMAT_GRB:
            initialise(pin, length, pio, sm, 
                    NONE, GREEN, RED, BLUE);
            break;
        case FORMAT_WRGB:
            initialise(pin, length, pio, sm, 
                    WHITE, RED, GREEN, BLUE);
            break;
    }

}

// ========================================================
// FIXME
WS2812::WS2812(
        uint pin, 
        uint length,
        PIO pio, 
        uint sm, 
        WS2812DataByte b1, 
        WS2812DataByte b2, 
        WS2812DataByte b3) {
    
    initialise(
            pin, length, pio, sm, 
            b1, b1, b2, b3
            );
}

// ========================================================
// FIXME
WS2812::WS2812(
        uint pin, 
        uint length, 
        PIO pio,
        uint sm, 
        WS2812DataByte b1, 
        WS2812DataByte b2, 
        WS2812DataByte b3, 
        WS2812DataByte b4) {

    initialise(
            pin, length, pio, sm, 
            b1, b2, b3, b4
            );

}

// ========================================================
// FIXME
WS2812::~WS2812() {
    // https://www.youtube.com/watch?v=9Tel0SBsF5g  
}

// ========================================================
// FIXME
void WS2812::initialise(
        uint pin, 
        uint length, 
        PIO pio, 
        uint sm, 
        WS2812DataByte b1,
        WS2812DataByte b2,
        WS2812DataByte b3,
        WS2812DataByte b4) {

    this->pin = pin;
    this->length = length;
    this->pio = pio;
    this->sm = sm;
    this->data = new colourData[length];
    this->bytes[0] = b1;
    this->bytes[1] = b2;
    this->bytes[2] = b3;
    this->bytes[3] = b4;

    uint offset = pio_add_program(pio, &ws2812_program);
    uint n_bits = (b1 == NONE ? 24 : 32);
    ws2812_program_init(
            pio,    // TODO: 
            sm,     //
            offset, //
            pin,    //
            800000, // 
            n_bits  // 
            );

}

// ========================================================
// FIXME
colourData WS2812::convertData(colourData rgbw) {

    colourData result = 0;
    for (uint b = 0; b < 4; b++) {
        switch (bytes[b]) {
            case RED:
                result |= (rgbw & 0xFF);
                break;
            case GREEN:
                result |= (rgbw & 0xFF00) >> 8;
                break;
            case BLUE:
                result |= (rgbw & 0xFF0000) >> 16;
                break;
            case WHITE:
                result |= (rgbw & 0xFF000000) >> 24;
                break;
        }
        result <<= 8;
    }

    return result;

}

// ========================================================
// FIXME
void WS2812::setPixelColor(
        uint index, 
        colourData c) {

    if (index < length) {
        data[index] = convertData(c);
    }

    return; 

}

// ========================================================
// FIXME
void WS2812::setPixelColor(
        uint index, 
        colourValue red, 
        colourValue green, 
        colourValue blue) {

    setPixelColor(index, 
            RGB(red, green, blue));

    return;
}

// ========================================================
// FIXME
void WS2812::setPixelColor(
        uint index, 
        colourValue red, 
        colourValue green, 
        colourValue blue, 
        colourValue white) {

    setPixelColor(index, 
            RGBW(red, green, blue, white));

    return; 

}

// ========================================================
// FIXME
void WS2812::fill(colourData color) {

    fill(color, 0, length);

    return; 

}

// ========================================================
// FIXME
void WS2812::fill(colourData color, uint first) {

    fill(color, first, length-first);

    return; 

}

// ========================================================
// FIXME
void WS2812::fill(colourData color, uint first, uint count) {

    uint last = (first + count);

    if (last > length) 
        last = length;

    color = convertData(color);

    for (uint i = first; i < last; i++) {
        data[i] = color;
    }

    return; 

}

// * - *

// FIXME: 
// void WS2812::show() {
//     #ifdef DEBUG
//     for (uint i = 0; i < length; i++) {
//         printf("WS2812 / Put data: %08X\n", data[i]);
//     }
//     #endif
//     for (uint i = 0; i < length; i++) {
//         pio_sm_put_blocking(pio, sm, data[i]);
//     }
// }
//
// ^ Standardize logging format 
