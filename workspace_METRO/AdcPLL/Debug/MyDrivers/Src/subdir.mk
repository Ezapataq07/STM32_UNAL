################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyDrivers/Src/AdcDriver.c \
../MyDrivers/Src/BasicTimer.c \
../MyDrivers/Src/GPIOxDriver.c \
../MyDrivers/Src/RccDriver.c \
../MyDrivers/Src/USARTxDriver.c 

OBJS += \
./MyDrivers/Src/AdcDriver.o \
./MyDrivers/Src/BasicTimer.o \
./MyDrivers/Src/GPIOxDriver.o \
./MyDrivers/Src/RccDriver.o \
./MyDrivers/Src/USARTxDriver.o 

C_DEPS += \
./MyDrivers/Src/AdcDriver.d \
./MyDrivers/Src/BasicTimer.d \
./MyDrivers/Src/GPIOxDriver.d \
./MyDrivers/Src/RccDriver.d \
./MyDrivers/Src/USARTxDriver.d 


# Each subdirectory must supply rules for building sources it contributes
MyDrivers/Src/%.o MyDrivers/Src/%.su: ../MyDrivers/Src/%.c MyDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Escritorio/UNAL X/InvestigacionMetro/workspace_METRO/AdcPLL/MyDrivers/Inc" -I"D:/Escritorio/UNAL X/InvestigacionMetro/workspace_METRO/AdcPLL/MyDrivers/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyDrivers-2f-Src

clean-MyDrivers-2f-Src:
	-$(RM) ./MyDrivers/Src/AdcDriver.d ./MyDrivers/Src/AdcDriver.o ./MyDrivers/Src/AdcDriver.su ./MyDrivers/Src/BasicTimer.d ./MyDrivers/Src/BasicTimer.o ./MyDrivers/Src/BasicTimer.su ./MyDrivers/Src/GPIOxDriver.d ./MyDrivers/Src/GPIOxDriver.o ./MyDrivers/Src/GPIOxDriver.su ./MyDrivers/Src/RccDriver.d ./MyDrivers/Src/RccDriver.o ./MyDrivers/Src/RccDriver.su ./MyDrivers/Src/USARTxDriver.d ./MyDrivers/Src/USARTxDriver.o ./MyDrivers/Src/USARTxDriver.su

.PHONY: clean-MyDrivers-2f-Src

