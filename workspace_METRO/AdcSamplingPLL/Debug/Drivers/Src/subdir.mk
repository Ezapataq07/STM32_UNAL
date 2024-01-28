################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/AdcDriver.c \
../Drivers/Src/BasicTimer.c \
../Drivers/Src/GPIOxDriver.c \
../Drivers/Src/RccDriver.c \
../Drivers/Src/USARTxDriver.c 

OBJS += \
./Drivers/Src/AdcDriver.o \
./Drivers/Src/BasicTimer.o \
./Drivers/Src/GPIOxDriver.o \
./Drivers/Src/RccDriver.o \
./Drivers/Src/USARTxDriver.o 

C_DEPS += \
./Drivers/Src/AdcDriver.d \
./Drivers/Src/BasicTimer.d \
./Drivers/Src/GPIOxDriver.d \
./Drivers/Src/RccDriver.d \
./Drivers/Src/USARTxDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Escritorio/UNAL X/InvestigacionMetro/workspace_METRO/mcu_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Escritorio/UNAL X/InvestigacionMetro/workspace_METRO/mcu_headers/CMSIS/Include" -I"D:/Escritorio/UNAL X/InvestigacionMetro/workspace_METRO/AdcSamplingPLL/Src" -I"D:/Escritorio/UNAL X/InvestigacionMetro/workspace_METRO/AdcSamplingPLL/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/AdcDriver.d ./Drivers/Src/AdcDriver.o ./Drivers/Src/AdcDriver.su ./Drivers/Src/BasicTimer.d ./Drivers/Src/BasicTimer.o ./Drivers/Src/BasicTimer.su ./Drivers/Src/GPIOxDriver.d ./Drivers/Src/GPIOxDriver.o ./Drivers/Src/GPIOxDriver.su ./Drivers/Src/RccDriver.d ./Drivers/Src/RccDriver.o ./Drivers/Src/RccDriver.su ./Drivers/Src/USARTxDriver.d ./Drivers/Src/USARTxDriver.o ./Drivers/Src/USARTxDriver.su

.PHONY: clean-Drivers-2f-Src

