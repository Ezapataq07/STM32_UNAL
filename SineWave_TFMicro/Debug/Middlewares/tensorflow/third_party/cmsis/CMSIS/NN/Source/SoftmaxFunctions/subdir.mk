################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.c \
../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.c 

C_DEPS += \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.d \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.d 

OBJS += \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.o \
./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/%.o Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/%.su: ../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/%.c Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DTFLM_RUNTIME -DCMSIS_NN -DTFLM_RUNTIME_USE_ALL_OPERATORS=0 -DTF_LITE_STATIC_MEMORY -DTF_LITE_DISABLE_X86_NEON -DTF_LITE_MCU_DEBUG_LOG -DARM_MATH -DARM_MATH_LOOPUNROLL -DARM_MATH_DSP -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/tensorflow/third_party/cmsis/CMSIS/DSP/Include/dsp -I../Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Include -I../Middlewares/tensorflow/third_party/cmsis/CMSIS/DSP/Include -I../Middlewares/tensorflow -I../Middlewares/tensorflow/third_party/flatbuffers/include -I../Middlewares/tensorflow/third_party/cmsis/CMSIS/Core/Include -I../Middlewares/tensorflow/third_party/gemmlowp -I../Middlewares/tensorflow/third_party/cmsis -I../Middlewares/tensorflow/third_party/ruy -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-tensorflow-2f-third_party-2f-cmsis-2f-CMSIS-2f-NN-2f-Source-2f-SoftmaxFunctions

clean-Middlewares-2f-tensorflow-2f-third_party-2f-cmsis-2f-CMSIS-2f-NN-2f-Source-2f-SoftmaxFunctions:
	-$(RM) ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.su ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.d ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.o ./Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.su

.PHONY: clean-Middlewares-2f-tensorflow-2f-third_party-2f-cmsis-2f-CMSIS-2f-NN-2f-Source-2f-SoftmaxFunctions

