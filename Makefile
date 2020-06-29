PREFIX_DIR=
BUILD_DIR=build
APP_NAME=example
CC=$(PREFIX_DIR)arm-none-eabi-gcc
SZ=$(PREFIX_DIR)arm-none-eabi-size
OBJCOPY=$(PREFIX_DIR)arm-none-eabi-objcopy
INCLUDES=-I./includes/ -I./lib/
OPTIMIZE=3
DEBUG=1
START=./lib/startup_stm32f103xb.s
LD_SCRIPT=-T./lib/STM32F103C8Tx_FLASH.ld
CPU_FLAGS=-mcpu=cortex-m3 -mthumb -fdata-sections -ffunction-sections -Wl,--gc-sections
CPP_STD=
CFLAGS=$(CPU_FLAGS) $(CPP_STD) $(LD_SCRIPT) $(INCLUDES) -O$(OPTIMIZE) -g$(DEBUG) -specs=nano.specs
SOURCES=main.c $(START) lib/gpio.c
LIBS=

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
