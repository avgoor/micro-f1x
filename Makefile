PREFIX_DIR=
BUILD_DIR=build
APP_NAME=example
CC=$(PREFIX_DIR)arm-none-eabi-g++
SZ=$(PREFIX_DIR)arm-none-eabi-size
OBJCOPY=$(PREFIX_DIR)arm-none-eabi-objcopy
INC_DIR=./includes/
OPTIMIZE=3
DEBUG=1
START=$(INC_DIR)/startup_stm32f103xb.s
LD_SCRIPT=-T$(INC_DIR)/STM32F103C8Tx_FLASH.ld
CPU_FLAGS=-mcpu=cortex-m3 -mthumb
CPP_STD=-std=c++2a
CFLAGS=$(CPU_FLAGS) $(CPP_STD) $(LD_SCRIPT) -I$(INC_DIR) -O$(OPTIMIZE) -g$(DEBUG) -specs=nosys.specs
SOURCES=main.cc $(START)
LIBS=-lnosys

all: $(BUILD_DIR)/$(APP_NAME).bin


$(BUILD_DIR)/$(APP_NAME).elf: $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LIBS)
	$(SZ) $@

$(BUILD_DIR)/$(APP_NAME).bin: $(BUILD_DIR)/$(APP_NAME).elf
	$(OBJCOPY) -O binary -S $(BUILD_DIR)/$(APP_NAME).elf $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm $(BUILD_DIR)/$(APP_NAME).bin $(BUILD_DIR)/$(APP_NAME).elf
