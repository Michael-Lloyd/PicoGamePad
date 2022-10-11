cmake_minimum_required(VERSION 3.13)

set (CMAKE_CONFIGURATION_TYPES "Debug;Release")
set (PICOGAMEPAD_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set (PICOGAMEPAD_DEFINITIONS PICOGAMEPAD_DEBUG=1) 


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/usr/share/pico-sdk")
include(pico_sdk_import.cmake)


project(PicoGamePad C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)
pico_sdk_init()

# src/include/*
set(picogamepad_LIBRARY_DIR ${PICOGAMEPAD_SOURCE_DIR}/include)
# src/lib/*
set(picogamepad_LIBRARY_DIR ${PICOGAMEPAD_SOURCE_DIR}/lib)
find_library(NAMES gtest PATHS 
link_directories(${CMAKE_SOURCE_DIR}/lib) 

add_executable(picogamepad 
        ${PICOGAMEPAD_SRCS}
)

pico_generate_pio_header(PicoGamePad ${CMAKE_CURRENT_LIST_DIR}/WS2812.pio)

pico_set_program_name(PicoGamePad "PicoGamePad Firmware V3A")
pico_set_program_version(PicoGamePad "3.0.0-A")

pico_enable_stdio_uart(PicoGamePad 1)
pico_enable_stdio_usb(PicoGamePad 1)

# Add the standard library to the build
target_link_libraries(PicoGamePad 
        pico_stdlib
)

# Add any user requested libraries
target_link_libraries(PicoGamePad
        hardware_pio
)

pico_add_extra_outputs(PicoGamePad)
