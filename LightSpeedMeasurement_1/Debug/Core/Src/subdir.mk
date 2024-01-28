################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.c \
D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.c \
D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.c \
D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/vl53lx_platform.o \
./Core/Src/vl53lx_platform_init.o \
./Core/Src/vl53lx_platform_ipp.o \
./Core/Src/vl53lx_platform_log.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/vl53lx_platform.d \
./Core/Src/vl53lx_platform_init.d \
./Core/Src/vl53lx_platform_ipp.d \
./Core/Src/vl53lx_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/vl53lx_platform.o: D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/vl53lx_platform_init.o: D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/vl53lx_platform_ipp.o: D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/vl53lx_platform_log.o: D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/vl53lx_platform.d ./Core/Src/vl53lx_platform.o ./Core/Src/vl53lx_platform.su ./Core/Src/vl53lx_platform_init.d ./Core/Src/vl53lx_platform_init.o ./Core/Src/vl53lx_platform_init.su ./Core/Src/vl53lx_platform_ipp.d ./Core/Src/vl53lx_platform_ipp.o ./Core/Src/vl53lx_platform_ipp.su ./Core/Src/vl53lx_platform_log.d ./Core/Src/vl53lx_platform_log.o ./Core/Src/vl53lx_platform_log.su

.PHONY: clean-Core-2f-Src

