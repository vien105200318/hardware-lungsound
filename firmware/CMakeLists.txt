cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(usb_microphone)

pico_sdk_init()

add_executable(usb_microphone
    usb_microphone.c
)

target_link_libraries(usb_microphone pico_stdlib pico_audio_tinyusb hardware_adc)

pico_add_extra_outputs(usb_microphone)
cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(usb_microphone)

pico_sdk_init()

add_executable(usb_microphone
    usb_microphone.c
)

target_link_libraries(usb_microphone pico_stdlib pico_audio_tinyusb hardware_adc)

pico_add_extra_outputs(usb_microphone)
