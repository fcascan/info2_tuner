################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Primitivas/subdir.mk
-include src/Drivers/subdir.mk
-include src/Aplicacion/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TPO_v2.axf

# Tool invocations
TPO_v2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\UTN\nxp\Workspace\cr_dsplib_cm3" -L"D:\UTN\nxp\Workspace\cr_dsplibFFTbin_cm3" -Xlinker -Map="TPO_v2.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "TPO_v2_Debug.ld" -o "TPO_v2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) TPO_v2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TPO_v2.axf"; # arm-none-eabi-objcopy -O binary "TPO_v2.axf" "TPO_v2.bin" ; checksum -p LPC1769 -d "TPO_v2.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
