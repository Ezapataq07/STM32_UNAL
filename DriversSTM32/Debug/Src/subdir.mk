################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AdcDriver.c \
../Src/BasicTimer.c \
../Src/ExtiDriver.c \
../Src/FPU_Driver.c \
../Src/GPIOxDriver.c \
../Src/I2CDriver.c \
../Src/LCD_Driver.c \
../Src/PLL_Driver.c \
../Src/PwmDriver.c \
../Src/StepMotorDriver.c \
../Src/SysTickDriver.c \
../Src/USARTxDriver.c 

OBJS += \
./Src/AdcDriver.o \
./Src/BasicTimer.o \
./Src/ExtiDriver.o \
./Src/FPU_Driver.o \
./Src/GPIOxDriver.o \
./Src/I2CDriver.o \
./Src/LCD_Driver.o \
./Src/PLL_Driver.o \
./Src/PwmDriver.o \
./Src/StepMotorDriver.o \
./Src/SysTickDriver.o \
./Src/USARTxDriver.o 

C_DEPS += \
./Src/AdcDriver.d \
./Src/BasicTimer.d \
./Src/ExtiDriver.d \
./Src/FPU_Driver.d \
./Src/GPIOxDriver.d \
./Src/I2CDriver.d \
./Src/LCD_Driver.d \
./Src/PLL_Driver.d \
./Src/PwmDriver.d \
./Src/StepMotorDriver.d \
./Src/SysTickDriver.d \
./Src/USARTxDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/ezque/STM32CubeIDE/workspace_1.9.0/mcu_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ezque/STM32CubeIDE/workspace_1.9.0/mcu_headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/AdcDriver.d ./Src/AdcDriver.o ./Src/AdcDriver.su ./Src/BasicTimer.d ./Src/BasicTimer.o ./Src/BasicTimer.su ./Src/ExtiDriver.d ./Src/ExtiDriver.o ./Src/ExtiDriver.su ./Src/FPU_Driver.d ./Src/FPU_Driver.o ./Src/FPU_Driver.su ./Src/GPIOxDriver.d ./Src/GPIOxDriver.o ./Src/GPIOxDriver.su ./Src/I2CDriver.d ./Src/I2CDriver.o ./Src/I2CDriver.su ./Src/LCD_Driver.d ./Src/LCD_Driver.o ./Src/LCD_Driver.su ./Src/PLL_Driver.d ./Src/PLL_Driver.o ./Src/PLL_Driver.su ./Src/PwmDriver.d ./Src/PwmDriver.o ./Src/PwmDriver.su ./Src/StepMotorDriver.d ./Src/StepMotorDriver.o ./Src/StepMotorDriver.su ./Src/SysTickDriver.d ./Src/SysTickDriver.o ./Src/SysTickDriver.su ./Src/USARTxDriver.d ./Src/USARTxDriver.o ./Src/USARTxDriver.su

.PHONY: clean-Src

