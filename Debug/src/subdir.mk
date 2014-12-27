################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/inputs.c \
../src/lcd.c \
../src/main.c \
../src/outputs.c \
../src/rtc.c \
../src/stm32f4_discovery.c \
../src/stm32f4xx_it.c \
../src/system_stm32f4xx.c 

S_SRCS += \
../src/startup_stm32f4xx.s 

OBJS += \
./src/inputs.o \
./src/lcd.o \
./src/main.o \
./src/outputs.o \
./src/rtc.o \
./src/startup_stm32f4xx.o \
./src/stm32f4_discovery.o \
./src/stm32f4xx_it.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/inputs.d \
./src/lcd.d \
./src/main.d \
./src/outputs.d \
./src/rtc.d \
./src/stm32f4_discovery.d \
./src/stm32f4xx_it.d \
./src/system_stm32f4xx.d 

S_DEPS += \
./src/startup_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F4XX -DUSE_STM32F4_DISCOVERY -DUSE_STDPERIPH_DRIVER -I"C:\Users\Gergo\workspace\estevan\Libraries\CMSIS\Include" -I"C:\Users\Gergo\workspace\estevan\Application\Module\Flash" -I"C:\Users\Gergo\workspace\estevan\Application\Module\TempMeasurement" -I"C:\Users\Gergo\workspace\estevan\Application\Module\Timers" -I"C:\Users\Gergo\workspace\estevan\Libraries\Device\STM32F4xx\Include" -I"C:\Users\Gergo\workspace\estevan\Libraries\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\Gergo\workspace\estevan\src" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


