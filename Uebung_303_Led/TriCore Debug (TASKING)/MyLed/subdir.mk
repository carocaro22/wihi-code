################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
"../MyLed/CLed.cpp" \
"../MyLed/MyLed.cpp" 

COMPILED_SRCS += \
"MyLed/CLed.src" \
"MyLed/MyLed.src" 

CPP_DEPS += \
"./MyLed/CLed.d" \
"./MyLed/MyLed.d" 

OBJS += \
"MyLed/CLed.o" \
"MyLed/MyLed.o" 


# Each subdirectory must supply rules for building sources it contributes
"MyLed/CLed.src":"../MyLed/CLed.cpp" "MyLed/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_303_Led/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"MyLed/CLed.o":"MyLed/CLed.src" "MyLed/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MyLed/MyLed.src":"../MyLed/MyLed.cpp" "MyLed/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_303_Led/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"MyLed/MyLed.o":"MyLed/MyLed.src" "MyLed/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MyLed

clean-MyLed:
	-$(RM) ./MyLed/CLed.d ./MyLed/CLed.o ./MyLed/CLed.src ./MyLed/MyLed.d ./MyLed/MyLed.o ./MyLed/MyLed.src

.PHONY: clean-MyLed

