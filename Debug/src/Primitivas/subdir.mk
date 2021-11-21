################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Primitivas/PR-ADC.c \
../src/Primitivas/PR-Beep.c \
../src/Primitivas/PR-Interpretar.c \
../src/Primitivas/PR-Joystick.c \
../src/Primitivas/PR-OLED.c \
../src/Primitivas/PR-SW.c \
../src/Primitivas/PR-UART0.c 

OBJS += \
./src/Primitivas/PR-ADC.o \
./src/Primitivas/PR-Beep.o \
./src/Primitivas/PR-Interpretar.o \
./src/Primitivas/PR-Joystick.o \
./src/Primitivas/PR-OLED.o \
./src/Primitivas/PR-SW.o \
./src/Primitivas/PR-UART0.o 

C_DEPS += \
./src/Primitivas/PR-ADC.d \
./src/Primitivas/PR-Beep.d \
./src/Primitivas/PR-Interpretar.d \
./src/Primitivas/PR-Joystick.d \
./src/Primitivas/PR-OLED.d \
./src/Primitivas/PR-SW.d \
./src/Primitivas/PR-UART0.d 


# Each subdirectory must supply rules for building sources it contributes
src/Primitivas/%.o: ../src/Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN\nxp\Workspace\TPO_v2\src\Aplicacion" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Drivers" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Headers" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Primitivas" -I"D:\UTN\nxp\Workspace\cr_dsplib_cm3" -I"D:\UTN\nxp\Workspace\cr_dsplibFFTbin_cm3" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


