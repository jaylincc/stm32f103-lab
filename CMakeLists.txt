#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.20)
 
# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
 
# project settings
project(stm32f103c8t6  C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
 
#Uncomment for hardware floating point
#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
#add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
#add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
 
#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)

# 
add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
# 指定编译优化选项
add_compile_options(-O2)
 
# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(VERBOSE "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(VERBOSE "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(VERBOSE "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(VERBOSE "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

#添加宏定义
add_definitions(-DSTM32F103xB -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD)

#添加头文件路径，即.h文件
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/driver)
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/core)
include_directories(${CMAKE_SOURCE_DIR}/lib/CMSIS/CM3/CoreSupport)
include_directories(${CMAKE_SOURCE_DIR}/lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x)
include_directories(${CMAKE_SOURCE_DIR}/lib/STM32F10x_StdPeriph_Driver/inc)

#添加源文件路径,即.c或者.s文件
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/core/*.c
                          ${CMAKE_SOURCE_DIR}/src/*.c
                          ${CMAKE_SOURCE_DIR}/src/driver/*.c
                          ${CMAKE_SOURCE_DIR}/lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/startup_stm32f10x_md.s
                          ${CMAKE_SOURCE_DIR}/lib/STM32F10x_StdPeriph_Driver/*.c)
#===================================================================
#追加项目源文件
# file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/syscalls.c)
# 1. GPIO示例程序
file(GLOB_RECURSE GPIO_SOURCES ${CMAKE_SOURCE_DIR}/src/01.gpio_demo/*.c)
list(APPEND SOURCES ${GPIO_SOURCES})
#===================================================================

message(STATUS "PROJECT_BINARY_DIR is ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR is ${CMAKE_BINARY_DIR}")

#添加你的STM32F103ZETx_FLASH.ld的连接脚本路径
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld)
 
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
#选择cortex-m3内核
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})
# 禁止 RWX 段（提高安全性）
add_link_options(-Wl,--no-warn-rwx-segments)
add_link_options(-specs=nano.specs -specs=nosys.specs -u _printf_float)
 
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

# 生成hex和bin文件
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE}"
    )
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${BIN_FILE}"
)