// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#define PICOGAMEPAD 
#ifndef _BOARDS_PICOGAMEPAD_V3A_H
#define _BOARDS_PICOGAMEPAD_V3A_H 

// ========================================================
// PIN AND PERIPHERAL DEFAULTS: 
// =====================

// UART Defaults 
//
// Note: There are many you can assign. 
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 1
#endif
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 20
#endif
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 21
#endif

// =====================
// Default WS2812 pin 
#ifndef PICO_DEFAULT_WS2812_PIN
#define PICO_DEFAULT_WS2812_PIN 16
#endif

// =====================
// Flash 

// Notes Author: https://github.com/adafruit/nvm.toml/blob/main/flash/winbond/W25Q16JVxQ.toml
// # Settings for the Winbond W25Q16JV-IQ 2MiB SPI flash. Note that JV-IM has a different
// .memory_type (0x70)
// # Datasheet: https://www.winbond.com/resource-files/w25q16jv%20spi%20revf%2005092017.pdf
// total_size = 0x200000 # 2 MiB
// start_up_time_us = 5000
// memory_type = 0x40
// capacity = 0x15
// max_clock_speed_mhz = 133
// quad_enable_bit_mask = 0x02
// quad_enable_status_byte = 2
// write_status_register_split = false
// 01_continuous_status_write = true
// 6b_quad_read = true
// 32_qspi_write = true


#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

// Flash QSPI Clock Rate
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

// Flash Memory size (BYTES, NOT BITS)
// In our case, 16MBit = 16/8 = 2MBytes 
#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 0
#endif

#endif
