################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/SVDFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/ReshapeFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/PoolingFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/ConcatenationFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/BasicMathFunctions/subdir.mk
-include Middlewares/tensorflow/third_party/cmsis/CMSIS/NN/Source/ActivationFunctions/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/schema/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/micro/memory_planner/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/micro/kernels/cmsis_nn/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/micro/kernels/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/micro/arena_allocator/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/micro/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/kernels/internal/reference/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/kernels/internal/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/kernels/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/core/api/subdir.mk
-include Middlewares/tensorflow/tensorflow/lite/c/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SineWave_TFMicro
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SineWave_TFMicro.elf \

MAP_FILES += \
SineWave_TFMicro.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SineWave_TFMicro.list \


# All Target
all: main-build

# Main-build Target
main-build: SineWave_TFMicro.elf secondary-outputs

# Tool invocations
SineWave_TFMicro.elf SineWave_TFMicro.map: $(OBJS) $(USER_OBJS) C:\Users\ezque\STM32CubeIDE\workspace_1.9.0\SineWave_TFMicro\STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "SineWave_TFMicro.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\ezque\STM32CubeIDE\workspace_1.9.0\SineWave_TFMicro\STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SineWave_TFMicro.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SineWave_TFMicro.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SineWave_TFMicro.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SineWave_TFMicro.elf SineWave_TFMicro.list SineWave_TFMicro.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
