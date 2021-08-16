################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MyLib/%.obj: ../MyLib/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/CCS/CCS10.4/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/Singlechip/msp432/MyCode/05.PWM" --include_path="E:/Singlechip/msp432/MyCode/05.PWM/Debug" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos" --include_path="D:/CCS/MSP432E4_SDK/simplelink_msp432e4_sdk_4_20_00_12/kernel/nortos/posix" --include_path="D:/CCS/CCS10.4/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="MyLib/$(basename $(<F)).d_raw" --include_path="E:/Singlechip/msp432/MyCode/05.PWM/Debug/syscfg" --obj_directory="MyLib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


