################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/GPIO.c \
../Modules/I2C.c \
../Modules/KBD.c \
../Modules/LCD.c \
../Modules/SPI.c 

OBJS += \
./Modules/GPIO.o \
./Modules/I2C.o \
./Modules/KBD.o \
./Modules/LCD.o \
./Modules/SPI.o 

C_DEPS += \
./Modules/GPIO.d \
./Modules/I2C.d \
./Modules/KBD.d \
./Modules/LCD.d \
./Modules/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/%.o: ../Modules/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -DCR_INTEGER_PRINTF -DCR_PRINTF_CHAR -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\SE2\inc" -I"C:\Users\Red\Documents\LPCXpresso_8.1.4_606\testSpace\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


