################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Aplicacion/Comparar.c \
../src/Aplicacion/EnviarTrama.c \
../src/Aplicacion/Metronomo.c \
../src/Aplicacion/Nota_deseada.c \
../src/Aplicacion/fft.c \
../src/Aplicacion/main.c \
../src/Aplicacion/mde.c 

OBJS += \
./src/Aplicacion/Comparar.o \
./src/Aplicacion/EnviarTrama.o \
./src/Aplicacion/Metronomo.o \
./src/Aplicacion/Nota_deseada.o \
./src/Aplicacion/fft.o \
./src/Aplicacion/main.o \
./src/Aplicacion/mde.o 

C_DEPS += \
./src/Aplicacion/Comparar.d \
./src/Aplicacion/EnviarTrama.d \
./src/Aplicacion/Metronomo.d \
./src/Aplicacion/Nota_deseada.d \
./src/Aplicacion/fft.d \
./src/Aplicacion/main.d \
./src/Aplicacion/mde.d 


# Each subdirectory must supply rules for building sources it contributes
src/Aplicacion/%.o: ../src/Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN\nxp\Workspace\TPO_v2\src\Aplicacion" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Drivers" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Headers" -I"D:\UTN\nxp\Workspace\TPO_v2\src\Primitivas" -I"D:\UTN\nxp\Workspace\cr_dsplib_cm3" -I"D:\UTN\nxp\Workspace\cr_dsplibFFTbin_cm3" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


