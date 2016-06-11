################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portable/heap_4.c \
../portable/port.c 

OBJS += \
./portable/heap_4.o \
./portable/port.o 

C_DEPS += \
./portable/heap_4.d \
./portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
portable/%.o: ../portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS-template" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\include" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\portable" -O1 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


