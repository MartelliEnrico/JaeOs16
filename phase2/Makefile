ifeq ($(shell uname), Darwin)
	INCDIR ?= /usr/local/include
else
	INCDIR ?= /usr/include
endif

CURDIR = $(shell pwd)

BIN = build/phase3
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR)/uarm -Iinclude -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

.PHONY: all clean

all: $(BIN).core.uarm

$(BIN).core.uarm: $(BIN)
	elf2uarm -k $(BIN)

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) $(INCDIR)/uarm/crtso.o $(INCDIR)/uarm/libuarm.o $(OBJS)

build/%.o: src/%.c
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f build/*