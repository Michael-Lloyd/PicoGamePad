// lib/ws2812.h

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

#ifndef _PGP_ws2812_H 
#define _PGP_ws2812_H

#include "pico/types.h"
#include "hardware/pio.h"

// ================================================================================================
// WS2812 Entity, for abstraction over each RGB(?W) LED
// ================================================================================================


// ========================================================
// WS2812 value selections 
// =====================
// Bitfield colour enum 
using WS2812DataByte = enum _led_byte_data { 
        NONE    =   0x0     , 
        RED     =   0x1     ,
        GREEN   =   0x2     ,
        BLUE    =   0x3     ,
        WHITE   =   0x4
}; 

// =====================
// LED format select  
using WS2812Format = enum _led_data_format {
        FORMAT_RGB  =   0   ,
        FORMAT_GRB  =   1   ,
        FORMAT_WRGB =   2
};

typedef uint8_t     _colour_value   colourValue; 
typedef uint32_t    _colour_data    colourData;

typedef class _ws2812_c {

        public:

          // ========================================================
          // Object instantiation methods  

          // =====================
          // Constructors  

          ws2812(uint pin, uint length, PIO pio, uint sm);

          ws2812(uint pin, uint length, PIO pio, uint sm, 
                          WS2812Format format);

          ws2812(uint pin, uint length, PIO pio, uint sm, 
                          WS2812DataByte b1, 
                          WS2812DataByte b2, 
                          WS2812DataByte b3);

          ws2812(uint pin, uint length, PIO pio, uint sm, 
                          WS2812DataByte b1, 
                          WS2812DataByte b2, 
                          WS2812DataByte b3, 
                          WS2812DataByte b4);

          // =====================
          // Destructor 
          ~ws2812();

          // ========================================================
          // Hexadecimal masking of colours in RGB 
          static colourMix RGB(
                          colourValue red, 
                          colourValue green, 
                          colourValue blue) {

                  return(
                          (colourData)(blue)    << 16  
                          | (colourData)(green) << 8 
                          | (colourData)(red)
                        );

          };

          // ========================================================
          // Hexadecimal masking of colours in RGBW
          static colourData RGBW(
                          colourValue red, 
                          colourValue green, 
                          colourValue blue, 
                          colourValue white) {

                  return(
                          (colourData)(white)   << 24 
                          | (colourData)(blue)  << 16 
                          | (colourData)(green) << 8 
                          | (colourData)(red) 
                        );

          }

          // ========================================================
          // LED Control methods 

          // ========================================================
          // FIXME
          void setPixelColor(uint index, colourData color);

          // ========================================================
          // FIXME
          void setPixelColor(
                          uint index, 
                          colourValue red, 
                          colourValue green, 
                          colourValue blue);

          // ========================================================
          // FIXME
          void setPixelColor(
                          uint index, 
                          colourValue red, 
                          colourValue green, 
                          colourValue blue,
                          colourValue white);

          // ========================================================
          // FIXME
          void fill(
                          colourData color);

          // ========================================================
          // FIXME
          void fill(
                          colourData color, 
                          uint first);

          // ========================================================
          // FIXME
          void fill(colourData color, uint first, uint count);

          // ========================================================
          // FIXME
          void show();

        private:

          uint pin;
          uint length;
          PIO pio;
          uint sm;

          WS2812DataByte bytes[4];

          colourData *data;

          void initialise(uint pin, uint length, PIO pio, uint sm, 
            WS2812DataByte b1, 
            WS2812DataByte b2, 
            WS2812DataByte b3, 
            WS2812DataByte b4);

          colourData convertData(colourData rgbw);

} WS2812;

// * - *
#endif
