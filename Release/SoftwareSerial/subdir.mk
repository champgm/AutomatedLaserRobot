################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/Google\ Drive/Arduino/arduino-1.0/libraries/SoftwareSerial/SoftwareSerial.cpp 

OBJS += \
./SoftwareSerial/SoftwareSerial.o 

CPP_DEPS += \
./SoftwareSerial/SoftwareSerial.d 


# Each subdirectory must supply rules for building sources it contributes
SoftwareSerial/SoftwareSerial.o: D:/Google\ Drive/Arduino/arduino-1.0/libraries/SoftwareSerial/SoftwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../NewLaserRobot/Arduino_Uno/arduino -I../NewLaserRobot/Arduino_Uno/standard -I../NewLaserRobot/NewLaserRobot -I../NewLaserRobot/NewLaserRobot/Servo -I"D:/Google Drive/Arduino/eclipse workspace/NewLaserRobot/NewLaserRobot/SoftwareSerial" -I"D:\Google Drive\Arduino\arduino-1.0\libraries\SoftwareSerial" -I"D:\Google Drive\Arduino\arduino-1.0\libraries\Servo" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


