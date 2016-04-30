ifeq ($(shell uname), Darwin)
	INCDIR ?= /usr/local/include
else
	INCDIR ?= /usr/include
endif

CURDIR = $(shell pwd)

BIN = build/phase2
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR)/uarm -Iinclude -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
OBJS += $(patsubst include/%.c, build/%.o, $(wildcard include/*.c))

.PHONY: all clean

all: test
	@echo "Success, test passed."

$(BIN).core.uarm: $(BIN)
	elf2uarm -k $(BIN)

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) $(INCDIR)/uarm/crtso.o $(INCDIR)/uarm/libuarm.o $(OBJS)

build/%.o: src/%.c
	$(GCC) $(CFLAGS) $< -o $@

build/%.o: include/%.c
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f build/* tests/machine.uarm.cfg tests/term0.uarm

test: $(BIN).core.uarm tests/machine.uarm.cfg
	@uarm -c tests/machine.uarm.cfg -e -x || (echo "Test failed." && exit 1)

tests/machine.uarm.cfg:
	@sed -e "s|\@INCDIR\@|$(INCDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" tests/machine.uarm.tmp > tests/machine.uarm.cfg