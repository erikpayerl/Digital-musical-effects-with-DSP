################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)
CG_TOOL_ROOT := C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./src/usbstk5505_led.obj" \
"./src/usbstk5505_i2c.obj" \
"./src/usbstk5505_gpio.obj" \
"./src/usbstk5505.obj" \
"./src/uart_config.obj" \
"./src/tremolo.obj" \
"./src/svf.obj" \
"./src/stereo.obj" \
"./src/reverb.obj" \
"./src/main.obj" \
"./src/fuzz.obj" \
"./src/echo.obj" \
"./src/aic3204_init.obj" \
"./src/aic3204.obj" \
"./src/PLL.obj" \
"./src/LFO.obj" \
"./src/LEDFlasher5505.obj" \
"./src/FIR_filters_asm.obj" \
"./src/EQfilter.obj" \
-l"C:\Users\eld.hakansson\Documents\Chalmers\Kandidatarbete\Digital-musical-effects-with-DSP\audio_loop_dma\lib\CSLc55x5h.lib" \
-l"C:\Users\eld.hakansson\Documents\Chalmers\Kandidatarbete\Digital-musical-effects-with-DSP\audio_loop_dma\lib\ezdsp5535bsl.lib" \
-l"rts55h.lib" \
"../lnkx.cmd" \
"../lib/55xdsph.lib" \
"../lib/CSLc55x5h.lib" \
"../lib/ezdsp5535bsl.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include lib/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include lib/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: lms_test_new_dma.out

# Tool invocations
lms_test_new_dma.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --assume_bss_onchip -z -m"lms_test_new_dma.map" --warn_sections -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --reread_libs --rom_model -o "lms_test_new_dma.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QTD) "lms_test_new_dma.out"
	-$(RM) ".\src\EQfilter.obj" ".\src\FIR_filters_asm.obj" ".\src\LEDFlasher5505.obj" ".\src\LFO.obj" ".\src\PLL.obj" ".\src\aic3204.obj" ".\src\aic3204_init.obj" ".\src\echo.obj" ".\src\fuzz.obj" ".\src\main.obj" ".\src\reverb.obj" ".\src\stereo.obj" ".\src\svf.obj" ".\src\tremolo.obj" ".\src\uart_config.obj" ".\src\usbstk5505.obj" ".\src\usbstk5505_gpio.obj" ".\src\usbstk5505_i2c.obj" ".\src\usbstk5505_led.obj" 
	-$(RM) ".\src\FIR_filters_asm.pp" 
	-$(RM) ".\src\EQfilter.pp" ".\src\LEDFlasher5505.pp" ".\src\LFO.pp" ".\src\PLL.pp" ".\src\aic3204.pp" ".\src\aic3204_init.pp" ".\src\echo.pp" ".\src\fuzz.pp" ".\src\main.pp" ".\src\reverb.pp" ".\src\stereo.pp" ".\src\svf.pp" ".\src\tremolo.pp" ".\src\uart_config.pp" ".\src\usbstk5505.pp" ".\src\usbstk5505_gpio.pp" ".\src\usbstk5505_i2c.pp" ".\src\usbstk5505_led.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
