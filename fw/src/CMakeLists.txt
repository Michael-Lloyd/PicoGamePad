cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(picopad)

pico_sdk_init()

#add_executable(picopad #FIXME )

    #pico_enable_stdio_usb( 0)
    #pico_enable_stdio_uart(1)

    #pico_add_extra_outputs(#FIXME)

    #target_link_libraries(picopad
    #pico_stdlib 
    #pico_bootsel_via_double_reset 
    #pico_multicore)

add_compile_options(-Ofast)
