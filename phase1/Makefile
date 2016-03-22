UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	INCDIR ?= /usr/local/include
else
	INCDIR ?= /usr/include
endif

BIN = build/p1test
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR)/uarm -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

all: $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) $(INCDIR)/uarm/crtso.o $(INCDIR)/uarm/libuarm.o $(OBJS)
	elf2uarm -k $(BIN)

build/%.o: src/%.c
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f build/*
