PROG := simwatch

ifeq ($(OS),Windows_NT)
S := \\
else
S := /
endif

SRCDIR := src
OBJDIR := obj
BINDIR := bin

OTHER_SRC = ..$(S)micro$(S)src
SOURCES =	main.c \
			MakoVM.c \
			bootstrap.c \
			SimDisk.c \
			SimAnalog.c \
			SimScreen.c \
			SimSerial.c \
			
INCLUDES = -I$(OTHER_SRC)$(S)inc -I$(OTHER_SRC)$(S)res -Isrc$(S)util -Isrc$(S)inc
OBJECTS = $(patsubst %,$(OBJDIR)$(S)%,$(SOURCES:.c=.o))

CFLAGS := -Wall -pedantic -std=c99 -g -Os -gstabs -DSIMULATE
LFLAGS = `sdl-config --libs` -lSDL
CC := gcc

all: $(PROG)

debug:
	@echo $(OTHER_SRC)
	@echo $(OBJECTS)
	@echo $(INCLUDES)

# linking the program.
$(PROG): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)$(S)$(PROG) $(LFLAGS)

# compiling other source files.
$(OBJDIR)$(S)%.o: $(SRCDIR)$(S)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -s -o $@ $<

$(OBJDIR)$(S)%.o: $(OTHER_SRC)$(S)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -s -o $@ $<

clean:
ifeq ($(OS),Windows_NT)
	del $(OBJECTS)
else
	rm $(OBJECTS)
endif

.PHONY: all clean

