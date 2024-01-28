################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/BasicTimer.c \
../Core/Inc/ExtiDriver.c \
../Core/Inc/GPIOxDriver.c \
../Core/Inc/PwmDriver.c 

OBJS += \
./Core/Inc/BasicTimer.o \
./Core/Inc/ExtiDriver.o \
./Core/Inc/GPIOxDriver.o \
./Core/Inc/PwmDriver.o 

C_DEPS += \
./Core/Inc/BasicTimer.d \
./Core/Inc/ExtiDriver.d \
./Core/Inc/GPIOxDriver.d \
./Core/Inc/PwmDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/BasicTimer.d ./Core/Inc/BasicTimer.o ./Core/Inc/BasicTimer.su ./Core/Inc/ExtiDriver.d ./Core/Inc/ExtiDriver.o ./Core/Inc/ExtiDriver.su ./Core/Inc/GPIOxDriver.d ./Core/Inc/GPIOxDriver.o ./Core/Inc/GPIOxDriver.su ./Core/Inc/PwmDriver.d ./Core/Inc/PwmDriver.o ./Core/Inc/PwmDriver.su

.PHONY: clean-Core-2f-Inc

