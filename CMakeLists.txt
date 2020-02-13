# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

message("SRC ${CMAKE_SOURCE_DIR} end")

set(STM32_MODEL STM32F103C8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Modules/STM32.cmake)
set(STM32_LINKER_SCRIPT STM32F103CBTx_FLASH.ld)
set(STM32_STARTUP_SOURCE system/CMSIS/Device/Source/startup_stm32f103xb.S)


project(boot)

#include( ${CMAKE_CURRENT_SOURCE_DIR}/Modules/FindSTM32Cube.cmake NO_POLICY_SCOPE)

file(GLOB_RECURSE STM32_SOURCE_FILES system/*.c system/*.cpp system/*.S)
file(GLOB_RECURSE SOURCE_FILES  src/*.c src/*.cpp)

#add_definitions(-DUSE_USART1=256)
#add_definitions(-DUSE_USART2=256,HALFDUPLEX)
add_definitions(-DNDEBUG)
add_definitions(-DUSE_USART3=256,FULDUPLEX,TXE_HI,PORTC,PIN13)
add_definitions(-DUSE_HAL_DRIVER)
add_definitions(-DUSE_FULL_LL_DRIVER)
add_definitions(-DSTM32F103xB)
add_definitions(-DPROTOCOL_MODBUS)
#add_definitions(-DUSE_FULL_ASSERT)
#add_definitions(-DTRACE)
#add_definitions(-DOS_USE_TRACE_ITM)
#add_definitions(-DSTM32F10X_MD)
#add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DUSE_ARDUINO_MAIN)
add_definitions(-DHSE_VALUE=8000000)

include_directories (include/ 
					 system/_LCC/Inc
					 system/CMSIS/Include
					 system/CMSIS/Device/Include
					 system/STM32F1xx_HAL_Driver/Inc
)
include( ${CMAKE_CURRENT_SOURCE_DIR}/Modules/STM32/F1/STM32F103C8.cmake NO_POLICY_SCOPE)
include( ${CMAKE_CURRENT_SOURCE_DIR}/Modules/STM32.cmake NO_POLICY_SCOPE)

#find_package (STM32LL COMPONENTS gpio REQUIRED )


# Outputs
set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_executable ( ${PROJECT_NAME}.elf ${SOURCE_FILES} ${STM32_SOURCE_FILES} ${STM32LL_SOURCE_FILES} )

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
		# Build .hex and .bin files
        COMMAND ${CMAKE_OBJCOPY} -S --strip-unneeded -R .comment -R .debug_macro -R .debug_info -R .debug_abbrev -R .debug_str -O binary  ${ELF_FILE} ${BIN_FILE}
        COMMAND ${CMAKE_OBJCOPY} -S --strip-unneeded -R .comment -R .debug_macro -R .debug_info -R .debug_abbrev -R .debug_str -O ihex  ${ELF_FILE} ${HEX_FILE}
        COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"

        # Copy files to a custom build directory
        #COMMAND ${CMAKE_COMMAND} -E copy ${ELF_FILE} "${ROOT_PROJ}/builds/${CHIP}/${EXE_NAME}.elf"
        #COMMAND ${CMAKE_COMMAND} -E copy ${HEX_FILE} "${ROOT_PROJ}/builds/${CHIP}/${EXE_NAME}.hex"
        #COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${ROOT_PROJ}/builds/${CHIP}/${EXE_NAME}.bin"

        # Display sizes
        COMMAND ${CMAKE_SIZE} --format=berkeley ${ELF_FILE} ${HEX_FILE}
        COMMENT "Invoking: Cross ARM GNU Print Size"
        )
#stm32_add_bin_target ( "boot.elf")
#stm32_add_hex_target( "boot.elf")
#stm32_add_dump_target( "boot.elf")

