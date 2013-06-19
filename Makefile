
NAME := SUPERWATCH
HEX := $(NAME).hex
OUT := $(NAME).out
MAP := $(NAME).map
SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

MCU := atmega328p
MCU_AVRDUDE := atmega328p
MCU_FREQ := 1000000UL

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size -A
DOXYGEN := doxygen

CFLAGS := -Wall -pedantic -mmcu=$(MCU) -std=c99 -g -Os -DF_CPU=$(MCU_FREQ) -gstabs

SIMCC := gcc
SIMCFLAGS := -Wall -pedantic -std=c99 -g -Os -IC:\WinAVR\avr\include

all: $(HEX)

clean:
	del $(HEX) $(OUT) $(MAP) $(OBJECTS)
	del doc/html

flash: $(HEX)
	avrdude -y -c usbtiny -p $(MCU_AVRDUDE) -U flash:w:$(HEX)

$(HEX): $(OUT)
	$(OBJCOPY) -R .eeprom -O ihex $< $@

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ -Wl,-Map,$(MAP) $^
	@echo
	$(SIZE) $@
	@echo

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean flash

