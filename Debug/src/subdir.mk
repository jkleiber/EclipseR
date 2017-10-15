################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eclipse.cpp \
../src/EclipseR.cpp \
../src/FileInput.cpp \
../src/UnitTests.cpp 

OBJS += \
./src/Eclipse.o \
./src/EclipseR.o \
./src/FileInput.o \
./src/UnitTests.o 

CPP_DEPS += \
./src/Eclipse.d \
./src/EclipseR.d \
./src/FileInput.d \
./src/UnitTests.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


