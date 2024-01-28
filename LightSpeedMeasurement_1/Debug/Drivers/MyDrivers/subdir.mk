################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MyDrivers/BasicTimer.c \
../Drivers/MyDrivers/ExtiDriver.c \
../Drivers/MyDrivers/FPU_Driver.c \
../Drivers/MyDrivers/GPIOxDriver.c \
../Drivers/MyDrivers/StepMotorDriver.c \
../Drivers/MyDrivers/SysTickDriver.c \
../Drivers/MyDrivers/USARTxDriver.c 

OBJS += \
./Drivers/MyDrivers/BasicTimer.o \
./Drivers/MyDrivers/ExtiDriver.o \
./Drivers/MyDrivers/FPU_Driver.o \
./Drivers/MyDrivers/GPIOxDriver.o \
./Drivers/MyDrivers/StepMotorDriver.o \
./Drivers/MyDrivers/SysTickDriver.o \
./Drivers/MyDrivers/USARTxDriver.o 

C_DEPS += \
./Drivers/MyDrivers/BasicTimer.d \
./Drivers/MyDrivers/ExtiDriver.d \
./Drivers/MyDrivers/FPU_Driver.d \
./Drivers/MyDrivers/GPIOxDriver.d \
./Drivers/MyDrivers/StepMotorDriver.d \
./Drivers/MyDrivers/SysTickDriver.d \
./Drivers/MyDrivers/USARTxDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MyDrivers/%.o Drivers/MyDrivers/%.su: ../Drivers/MyDrivers/%.c Drivers/MyDrivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Inc" -I"D:/Escritorio/UNAL X/Taller V/Sensor LiDAR 2D/VL53L3CX/Software STM/en.en.bare_driver_VL53L3CX/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Inc" -I../Drivers/MyDrivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-MyDrivers

clean-Drivers-2f-MyDrivers:
	-$(RM) ./Drivers/MyDrivers/BasicTimer.d ./Drivers/MyDrivers/BasicTimer.o ./Drivers/MyDrivers/BasicTimer.su ./Drivers/MyDrivers/ExtiDriver.d ./Drivers/MyDrivers/ExtiDriver.o ./Drivers/MyDrivers/ExtiDriver.su ./Drivers/MyDrivers/FPU_Driver.d ./Drivers/MyDrivers/FPU_Driver.o ./Drivers/MyDrivers/FPU_Driver.su ./Drivers/MyDrivers/GPIOxDriver.d ./Drivers/MyDrivers/GPIOxDriver.o ./Drivers/MyDrivers/GPIOxDriver.su ./Drivers/MyDrivers/StepMotorDriver.d ./Drivers/MyDrivers/StepMotorDriver.o ./Drivers/MyDrivers/StepMotorDriver.su ./Drivers/MyDrivers/SysTickDriver.d ./Drivers/MyDrivers/SysTickDriver.o ./Drivers/MyDrivers/SysTickDriver.su ./Drivers/MyDrivers/USARTxDriver.d ./Drivers/MyDrivers/USARTxDriver.o ./Drivers/MyDrivers/USARTxDriver.su

.PHONY: clean-Drivers-2f-MyDrivers

