################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
"../MatricLib/CMatrix.cpp" \
"../MatricLib/MatrixLib.cpp" 

COMPILED_SRCS += \
"MatricLib/CMatrix.src" \
"MatricLib/MatrixLib.src" 

CPP_DEPS += \
"./MatricLib/CMatrix.d" \
"./MatricLib/MatrixLib.d" 

OBJS += \
"MatricLib/CMatrix.o" \
"MatricLib/MatrixLib.o" 


# Each subdirectory must supply rules for building sources it contributes
"MatricLib/CMatrix.src":"../MatricLib/CMatrix.cpp" "MatricLib/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_303_Matrix/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"MatricLib/CMatrix.o":"MatricLib/CMatrix.src" "MatricLib/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MatricLib/MatrixLib.src":"../MatricLib/MatrixLib.cpp" "MatricLib/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_303_Matrix/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"MatricLib/MatrixLib.o":"MatricLib/MatrixLib.src" "MatricLib/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MatricLib

clean-MatricLib:
	-$(RM) ./MatricLib/CMatrix.d ./MatricLib/CMatrix.o ./MatricLib/CMatrix.src ./MatricLib/MatrixLib.d ./MatricLib/MatrixLib.o ./MatricLib/MatrixLib.src

.PHONY: clean-MatricLib

