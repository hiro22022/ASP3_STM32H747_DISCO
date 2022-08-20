################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
$(ASP3BASEDIR)/kernel_cfg.c \

OBJS += \
./obj_h747/kernel_cfg.o \

C_DEPS += \
./obj_h747/kernel_cfg.d \

# Each subdirectory must supply rules for building sources it contributes
./obj_h747/kernel_cfg.o: $(ASP3BASEDIR)/kernel_cfg.o
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DDEBUG -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-obj_h747

clean-obj_h747:
	-$(RM) ./asp3/kernel_cfg.o

.PHONY: clean-obj_h747

