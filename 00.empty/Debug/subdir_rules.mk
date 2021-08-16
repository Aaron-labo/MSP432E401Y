################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/CCS/CCS10.4/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/Singlechip/msp432/MyCode/00.empty" --include_path="E:/Singlechip/msp432/MyCode/00.empty/Debug" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos/posix" --include_path="D:/CCS/CCS10.4/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="E:/Singlechip/msp432/MyCode/00.empty/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2051668543: ../empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/CCS/CCS10.4/ccs/utils/sysconfig_1.9.0/sysconfig_cli.bat" -s "D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/.metadata/product.json" --script "E:/Singlechip/msp432/MyCode/00.empty/empty.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-2051668543 ../empty.syscfg
syscfg/ti_drivers_config.h: build-2051668543
syscfg/ti_utils_build_linker.cmd.exp: build-2051668543
syscfg/syscfg_c.rov.xs: build-2051668543
syscfg/: build-2051668543

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/CCS/CCS10.4/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/Singlechip/msp432/MyCode/00.empty" --include_path="E:/Singlechip/msp432/MyCode/00.empty/Debug" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos/posix" --include_path="D:/CCS/CCS10.4/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="E:/Singlechip/msp432/MyCode/00.empty/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


