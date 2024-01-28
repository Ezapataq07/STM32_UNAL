################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.c 

OBJS += \
./Drivers/BSP/53L3A2/53l3a2.o 

C_DEPS += \
./Drivers/BSP/53L3A2/53l3a2.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/53L3A2/53l3a2.o: D:/Escritorio/UNAL\ X/Taller\ V/Sensor\ LiDAR\ 2D/VL53L3CX/Software\ STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.c Drivers/BSP/53L3A2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-53L3A2

clean-Drivers-2f-BSP-2f-53L3A2:
	-$(RM) ./Drivers/BSP/53L3A2/53l3a2.d ./Drivers/BSP/53L3A2/53l3a2.o ./Drivers/BSP/53L3A2/53l3a2.su

.PHONY: clean-Drivers-2f-BSP-2f-53L3A2

