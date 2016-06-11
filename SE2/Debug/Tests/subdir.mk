################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tests/FreeRTOS_Tests.c \
../Tests/GPIO_Tests.c \
../Tests/KBD_Tests.c 

OBJS += \
./Tests/FreeRTOS_Tests.o \
./Tests/GPIO_Tests.o \
./Tests/KBD_Tests.o 

C_DEPS += \
./Tests/FreeRTOS_Tests.d \
./Tests/GPIO_Tests.d \
./Tests/KBD_Tests.d 


# Each subdirectory must supply rules for building sources it contributes
Tests/%.o: ../Tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -DCR_INTEGER_PRINTF -DCR_PRINTF_CHAR -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\SE2\inc" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\include" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\portable" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


