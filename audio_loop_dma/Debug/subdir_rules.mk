################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
lnkx.out: ../lnkx.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --diag_warning=225 --ptrdiff_size=16 --no_mac_expand --memory_model=large --assume_bss_onchip -z -m"lms_test_new_dma.map" --warn_sections -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --reread_libs --rom_model -o "$@" "$<" "../lnkx.cmd"
	@echo 'Finished building: $<'
	@echo ' '


