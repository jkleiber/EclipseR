################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/LinkedListTest.cpp \
../test/ResizableArrayTest.cpp \
../test/UnitTests.cpp 

OBJS += \
./test/LinkedListTest.o \
./test/ResizableArrayTest.o \
./test/UnitTests.o 

CPP_DEPS += \
./test/LinkedListTest.d \
./test/ResizableArrayTest.d \
./test/UnitTests.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


