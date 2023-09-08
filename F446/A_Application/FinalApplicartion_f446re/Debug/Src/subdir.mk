################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP3_program.c \
../Src/APP_2_program.c \
../Src/DMA_program.c \
../Src/EXTI_program.c \
../Src/GPIO_program.c \
../Src/I2C_program.c \
../Src/NVIC_program.c \
../Src/RCC_prog.c \
../Src/RTC_program.c \
../Src/SCB_program.c \
../Src/SPI_program.c \
../Src/STK_program.c \
../Src/SYSCFG_program.c \
../Src/USART_program.c \
../Src/USR_program.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/APP3_program.o \
./Src/APP_2_program.o \
./Src/DMA_program.o \
./Src/EXTI_program.o \
./Src/GPIO_program.o \
./Src/I2C_program.o \
./Src/NVIC_program.o \
./Src/RCC_prog.o \
./Src/RTC_program.o \
./Src/SCB_program.o \
./Src/SPI_program.o \
./Src/STK_program.o \
./Src/SYSCFG_program.o \
./Src/USART_program.o \
./Src/USR_program.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/APP3_program.d \
./Src/APP_2_program.d \
./Src/DMA_program.d \
./Src/EXTI_program.d \
./Src/GPIO_program.d \
./Src/I2C_program.d \
./Src/NVIC_program.d \
./Src/RCC_prog.d \
./Src/RTC_program.d \
./Src/SCB_program.d \
./Src/SPI_program.d \
./Src/STK_program.d \
./Src/SYSCFG_program.d \
./Src/USART_program.d \
./Src/USR_program.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/APP3_program.d ./Src/APP3_program.o ./Src/APP3_program.su ./Src/APP_2_program.d ./Src/APP_2_program.o ./Src/APP_2_program.su ./Src/DMA_program.d ./Src/DMA_program.o ./Src/DMA_program.su ./Src/EXTI_program.d ./Src/EXTI_program.o ./Src/EXTI_program.su ./Src/GPIO_program.d ./Src/GPIO_program.o ./Src/GPIO_program.su ./Src/I2C_program.d ./Src/I2C_program.o ./Src/I2C_program.su ./Src/NVIC_program.d ./Src/NVIC_program.o ./Src/NVIC_program.su ./Src/RCC_prog.d ./Src/RCC_prog.o ./Src/RCC_prog.su ./Src/RTC_program.d ./Src/RTC_program.o ./Src/RTC_program.su ./Src/SCB_program.d ./Src/SCB_program.o ./Src/SCB_program.su ./Src/SPI_program.d ./Src/SPI_program.o ./Src/SPI_program.su ./Src/STK_program.d ./Src/STK_program.o ./Src/STK_program.su ./Src/SYSCFG_program.d ./Src/SYSCFG_program.o ./Src/SYSCFG_program.su ./Src/USART_program.d ./Src/USART_program.o ./Src/USART_program.su ./Src/USR_program.d ./Src/USR_program.o ./Src/USR_program.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

