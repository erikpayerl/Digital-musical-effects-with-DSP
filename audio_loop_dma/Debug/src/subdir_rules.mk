################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/EQ.obj: ../src/EQ.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/EQ.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/LEDFlasher5505.obj: ../src/LEDFlasher5505.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/LEDFlasher5505.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/PLL.obj: ../src/PLL.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/PLL.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/aic3204.obj: ../src/aic3204.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/aic3204.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/aic3204_init.obj: ../src/aic3204_init.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/aic3204_init.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/main.obj: ../src/main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/main.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/stereo.obj: ../src/stereo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/stereo.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505.obj: ../src/usbstk5505.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/usbstk5505.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_gpio.obj: ../src/usbstk5505_gpio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/usbstk5505_gpio.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_i2c.obj: ../src/usbstk5505_i2c.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/usbstk5505_i2c.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_led.obj: ../src/usbstk5505_led.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=32 --no_mac_expand --memory_model=huge --preproc_with_compile --preproc_dependency="src/usbstk5505_led.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


