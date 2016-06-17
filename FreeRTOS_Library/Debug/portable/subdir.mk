################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portable/BlockQ.c \
../portable/GenQTest.c \
../portable/PollQ.c \
../portable/QPeek.c \
../portable/blocktim.c \
../portable/flash.c \
../portable/heap_4.c \
../portable/integer.c \
../portable/mpu_wrappers.c \
../portable/port.c \
../portable/recmutex.c \
../portable/semtest.c 

OBJS += \
./portable/BlockQ.o \
./portable/GenQTest.o \
./portable/PollQ.o \
./portable/QPeek.o \
./portable/blocktim.o \
./portable/flash.o \
./portable/heap_4.o \
./portable/integer.o \
./portable/mpu_wrappers.o \
./portable/port.o \
./portable/recmutex.o \
./portable/semtest.o 

C_DEPS += \
./portable/BlockQ.d \
./portable/GenQTest.d \
./portable/PollQ.d \
./portable/QPeek.d \
./portable/blocktim.d \
./portable/flash.d \
./portable/heap_4.d \
./portable/integer.d \
./portable/mpu_wrappers.d \
./portable/port.d \
./portable/recmutex.d \
./portable/semtest.d 


# Each subdirectory must supply rules for building sources it contributes
portable/%.o: ../portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS-template" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\include" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\portable\include" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\FreeRTOS_Library\portable" -O1 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


