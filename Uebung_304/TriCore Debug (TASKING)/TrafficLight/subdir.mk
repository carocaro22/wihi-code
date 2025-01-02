################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
"../TrafficLight/CPedesLight.cpp" \
"../TrafficLight/CTrafficControl.cpp" \
"../TrafficLight/CTrafficLight.cpp" \
"../TrafficLight/TrafficLight.cpp" 

COMPILED_SRCS += \
"TrafficLight/CPedesLight.src" \
"TrafficLight/CTrafficControl.src" \
"TrafficLight/CTrafficLight.src" \
"TrafficLight/TrafficLight.src" 

CPP_DEPS += \
"./TrafficLight/CPedesLight.d" \
"./TrafficLight/CTrafficControl.d" \
"./TrafficLight/CTrafficLight.d" \
"./TrafficLight/TrafficLight.d" 

OBJS += \
"TrafficLight/CPedesLight.o" \
"TrafficLight/CTrafficControl.o" \
"TrafficLight/CTrafficLight.o" \
"TrafficLight/TrafficLight.o" 


# Each subdirectory must supply rules for building sources it contributes
"TrafficLight/CPedesLight.src":"../TrafficLight/CPedesLight.cpp" "TrafficLight/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_304/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"TrafficLight/CPedesLight.o":"TrafficLight/CPedesLight.src" "TrafficLight/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"TrafficLight/CTrafficControl.src":"../TrafficLight/CTrafficControl.cpp" "TrafficLight/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_304/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"TrafficLight/CTrafficControl.o":"TrafficLight/CTrafficControl.src" "TrafficLight/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"TrafficLight/CTrafficLight.src":"../TrafficLight/CTrafficLight.cpp" "TrafficLight/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_304/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"TrafficLight/CTrafficLight.o":"TrafficLight/CTrafficLight.src" "TrafficLight/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"TrafficLight/TrafficLight.src":"../TrafficLight/TrafficLight.cpp" "TrafficLight/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_304/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"TrafficLight/TrafficLight.o":"TrafficLight/TrafficLight.src" "TrafficLight/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-TrafficLight

clean-TrafficLight:
	-$(RM) ./TrafficLight/CPedesLight.d ./TrafficLight/CPedesLight.o ./TrafficLight/CPedesLight.src ./TrafficLight/CTrafficControl.d ./TrafficLight/CTrafficControl.o ./TrafficLight/CTrafficControl.src ./TrafficLight/CTrafficLight.d ./TrafficLight/CTrafficLight.o ./TrafficLight/CTrafficLight.src ./TrafficLight/TrafficLight.d ./TrafficLight/TrafficLight.o ./TrafficLight/TrafficLight.src

.PHONY: clean-TrafficLight

