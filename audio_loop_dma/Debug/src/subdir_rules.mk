################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/\ main.obj: ../src/\ main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/ main.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/EQfilter.obj: ../src/EQfilter.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/EQfilter.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/LFO.obj: ../src/LFO.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/LFO.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/aic3204.obj: ../src/aic3204.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/aic3204.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/aic_dma.obj: ../src/aic_dma.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/aic_dma.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/echo.obj: ../src/echo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/echo.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/fir2.obj: ../src/fir2.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/fir2.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/fuzz.obj: ../src/fuzz.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/fuzz.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/stereo.obj: ../src/stereo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/stereo.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/svf.obj: ../src/svf.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/svf.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/systemInit.obj: ../src/systemInit.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/systemInit.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/tremolo.obj: ../src/tremolo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/tremolo.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/uart_config.obj: ../src/uart_config.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include" --include_path="C:/Users/eld.hakansson/Documents/Chalmers/Kandidatarbete/Digital-musical-effects-with-DSP/audio_loop_dma/include/csl" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --preproc_with_compile --preproc_dependency="src/uart_config.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


