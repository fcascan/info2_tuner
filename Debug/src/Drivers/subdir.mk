################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/FW-CONFIG.c \
../src/Drivers/FW-GPIO.c \
../src/Drivers/FW-OLED.c \
../src/Drivers/FW-UART0.c \
../src/Drivers/IRQhandler.c \
../src/Drivers/Inic_EABaseBoard.c \
../src/Drivers/Inic_Oscilador.c \
../src/Drivers/Inic_Stick.c \
../src/Drivers/cr_startup_lpc176x.c \
../src/Drivers/font5x7.c 

OBJS += \
./src/Drivers/FW-CONFIG.o \
./src/Drivers/FW-GPIO.o \
./src/Drivers/FW-OLED.o \
./src/Drivers/FW-UART0.o \
./src/Drivers/IRQhandler.o \
./src/Drivers/Inic_EABaseBoard.o \
./src/Drivers/Inic_Oscilador.o \
./src/Drivers/Inic_Stick.o \
./src/Drivers/cr_startup_lpc176x.o \
./src/Drivers/font5x7.o 

C_DEPS += \
./src/Drivers/FW-CONFIG.d \
./src/Drivers/FW-GPIO.d \
./src/Drivers/FW-OLED.d \
./src/Drivers/FW-UART0.d \
./src/Drivers/IRQhandler.d \
./src/Drivers/Inic_EABaseBoard.d \
./src/Drivers/Inic_Oscilador.d \
./src/Drivers/Inic_Stick.d \
./src/Drivers/cr_startup_lpc176x.d \
./src/Drivers/font5x7.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/%.o: ../src/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN\nxp\Workspace\TPO_v2\src\Aplicacion" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Drivers" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Headers" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Primitivas" -I"D:\UTN\nxp\Workspace\cr_dsplib_cm3" -I"D:\UTN\nxp\Workspace\cr_dsplibFFTbin_cm3" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


