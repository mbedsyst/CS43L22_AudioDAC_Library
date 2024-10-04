################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CS43xx.c \
../Src/I2C.c \
../Src/I2S.c \
../Src/LED.c \
../Src/SYSTICK.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_init.c 

OBJS += \
./Src/CS43xx.o \
./Src/I2C.o \
./Src/I2S.o \
./Src/LED.o \
./Src/SYSTICK.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_init.o 

C_DEPS += \
./Src/CS43xx.d \
./Src/I2C.d \
./Src/I2S.d \
./Src/LED.d \
./Src/SYSTICK.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_init.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -DSTM32F411E_DISCO -DSTM32F411xE -c -I../Inc -I"C:/Users/zalma/OneDrive/Documents/F411_DSP/Musa_Audio/Headers/Device/ST/STM32F4xx/Include" -I"C:/Users/zalma/OneDrive/Documents/F411_DSP/Musa_Audio/Headers/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/CS43xx.cyclo ./Src/CS43xx.d ./Src/CS43xx.o ./Src/CS43xx.su ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/I2S.cyclo ./Src/I2S.d ./Src/I2S.o ./Src/I2S.su ./Src/LED.cyclo ./Src/LED.d ./Src/LED.o ./Src/LED.su ./Src/SYSTICK.cyclo ./Src/SYSTICK.d ./Src/SYSTICK.o ./Src/SYSTICK.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_init.cyclo ./Src/system_init.d ./Src/system_init.o ./Src/system_init.su

.PHONY: clean-Src

