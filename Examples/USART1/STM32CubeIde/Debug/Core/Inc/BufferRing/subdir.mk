################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/BufferRing/BufferRing.c 

OBJS += \
./Core/Inc/BufferRing/BufferRing.o 

C_DEPS += \
./Core/Inc/BufferRing/BufferRing.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/BufferRing/%.o Core/Inc/BufferRing/%.su Core/Inc/BufferRing/%.cyclo: ../Core/Inc/BufferRing/%.c Core/Inc/BufferRing/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-BufferRing

clean-Core-2f-Inc-2f-BufferRing:
	-$(RM) ./Core/Inc/BufferRing/BufferRing.cyclo ./Core/Inc/BufferRing/BufferRing.d ./Core/Inc/BufferRing/BufferRing.o ./Core/Inc/BufferRing/BufferRing.su

.PHONY: clean-Core-2f-Inc-2f-BufferRing

