BASEDIR ?= /usr/local
INCDIR = $(BASEDIR)/include/uarm
CURDIR = $(shell pwd)

CC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR) -Iinclude -Wall
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/ldscripts/elf32ltsarm.h.uarmcore.x

BIN = build/kernel
OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
OBJS += $(patsubst include/%.c, build/%.o, $(wildcard include/*.c))
OBJS += $(INCDIR)/crtso.o $(INCDIR)/libuarm.o

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

build/%.o: **/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/machine.uarm.cfg:
	sed -e "s|\@BASEDIR\@|$(BASEDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" \
		tests/machine.uarm.tmp > tests/machine.uarm.cfg

.PHONY: all clean test

all: $(BIN)

clean:
	$(RM) build/* tests/machine.uarm.cfg tests/term0.uarm

test: $(BIN) tests/machine.uarm.cfg
	uarm -c tests/machine.uarm.cfg -e -x
