################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Module/Flash/Flash.c 

OBJS += \
./Application/Module/Flash/Flash.o 

C_DEPS += \
./Application/Module/Flash/Flash.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Module/Flash/%.o: ../Application/Module/Flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F4XX -DUSE_STM32F4_DISCOVERY -DUSE_STDPERIPH_DRIVER -I"C:\Users\Gergo\workspace\estevan\Libraries\CMSIS\Include" -I"C:\Users\Gergo\workspace\estevan\Application\Module\Flash" -I"C:\Users\Gergo\workspace\estevan\Application\Module\TempMeasurement" -I"C:\Users\Gergo\workspace\estevan\Application\Module\Timers" -I"C:\Users\Gergo\workspace\estevan\Libraries\Device\STM32F4xx\Include" -I"C:\Users\Gergo\workspace\estevan\Libraries\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\Gergo\workspace\estevan\src" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


