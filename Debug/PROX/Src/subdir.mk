################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PROX/Src/PROX_prog.c 

OBJS += \
./PROX/Src/PROX_prog.o 

C_DEPS += \
./PROX/Src/PROX_prog.d 


# Each subdirectory must supply rules for building sources it contributes
PROX/Src/%.o PROX/Src/%.su PROX/Src/%.cyclo: ../PROX/Src/%.c PROX/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Racing_Team_ARM/CubeIDE_WS/Dashboard_/Dashboard/Inc" -I"D:/Racing_Team_ARM/CubeIDE_WS/Dashboard_/Nextion/Inc" -I"D:/Racing_Team_ARM/CubeIDE_WS/Dashboard_/PROX/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-PROX-2f-Src

clean-PROX-2f-Src:
	-$(RM) ./PROX/Src/PROX_prog.cyclo ./PROX/Src/PROX_prog.d ./PROX/Src/PROX_prog.o ./PROX/Src/PROX_prog.su

.PHONY: clean-PROX-2f-Src

