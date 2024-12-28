cmake_minimum_required(VERSION 3.25)

# Pull in SDK (must be before project)
include(pico-sdk/pico_sdk_init.cmake)

set(PROJECT_NAME "distanceSensor")

project(${PROJECT_NAME})

pico_sdk_init()

add_executable(${PROJECT_NAME}
	./main.c
)

target_link_libraries(${PROJECT_NAME} 
	pico_stdlib
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})
