################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_program.c \
../LCD_program.c \
../Masrter.c \
../SPI_program.c \
../UART_Master_program.c 

OBJS += \
./DIO_program.o \
./LCD_program.o \
./Masrter.o \
./SPI_program.o \
./UART_Master_program.o 

C_DEPS += \
./DIO_program.d \
./LCD_program.d \
./Masrter.d \
./SPI_program.d \
./UART_Master_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


