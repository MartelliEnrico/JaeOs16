ifeq ($(shell uname), Darwin)
	INCDIR ?= /usr/local/include
else
	INCDIR ?= /usr/include
endif

CURDIR = $(shell pwd)

BIN = build/phase2
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR)/uarm -I../libs -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/uarm/ldscripts/elf32ltsarm.h.uarmcore.x -L../libs -lphase1

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

.PHONY: all clean test

all: test

$(BIN).core.uarm: $(BIN)
	elf2uarm -k $(BIN)

$(BIN): $(OBJS)
	$(LD) -o $(BIN) $(INCDIR)/uarm/crtso.o $(INCDIR)/uarm/libuarm.o $(OBJS) $(LDFLAGS)

build/%.o: src/%.c
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f build/* tests/machine.uarm.cfg tests/term0.uarm

test: $(BIN).core.uarm tests/machine.uarm.cfg
	@uarm -c tests/machine.uarm.cfg -e -x && echo "Success, test passed." || (echo "Test failed." && exit 1)

tests/machine.uarm.cfg:
	@sed -e "s|\@INCDIR\@|$(INCDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" tests/machine.uarm.tmp > tests/machine.uarm.cfg