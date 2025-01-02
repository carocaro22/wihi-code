################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
"../MatrixLib/CMatrix.cpp" \
"../MatrixLib/MatrixLib.cpp" 

COMPILED_SRCS += \
"MatrixLib/CMatrix.src" \
"MatrixLib/MatrixLib.src" 

CPP_DEPS += \
"./MatrixLib/CMatrix.d" \
"./MatrixLib/MatrixLib.d" 

OBJS += \
"MatrixLib/CMatrix.o" \
"MatrixLib/MatrixLib.o" 


# Each subdirectory must supply rules for building sources it contributes
"MatrixLib/CMatrix.src":"../MatrixLib/CMatrix.cpp" "MatrixLib/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_303_Matrix/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"MatrixLib/CMatrix.o":"MatrixLib/CMatrix.src" "MatrixLib/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"MatrixLib/MatrixLib.src":"../MatrixLib/MatrixLib.cpp" "MatrixLib/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/carolina/AURIX-v1.10.6-workspace/Uebung_303_Matrix/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"MatrixLib/MatrixLib.o":"MatrixLib/MatrixLib.src" "MatrixLib/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-MatrixLib

clean-MatrixLib:
	-$(RM) ./MatrixLib/CMatrix.d ./MatrixLib/CMatrix.o ./MatrixLib/CMatrix.src ./MatrixLib/MatrixLib.d ./MatrixLib/MatrixLib.o ./MatrixLib/MatrixLib.src

.PHONY: clean-MatrixLib

