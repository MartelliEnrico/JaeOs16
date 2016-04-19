ifeq ($(shell uname), Darwin)
	INCDIR ?= /usr/local/include
else
	INCDIR ?= /usr/include
endif

CURDIR = $(shell pwd)

BIN = build/p1test
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR)/uarm -Iinclude -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

all: $(BIN).core.uarm

$(BIN).core.uarm: $(BIN)
	elf2uarm -k $(BIN)

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) $(INCDIR)/uarm/crtso.o $(INCDIR)/uarm/libuarm.o $(OBJS)

build/%.o: src/%.c
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f build/* tests/machine.uarm.cfg tests/term0.uarm

test: all tests/machine.uarm.cfg
	@echo "--- Test start"
	@uarm -c tests/machine.uarm.cfg -e -x
	@echo "--- Result: \c"
	@cat tests/term0.uarm | grep -q "SYSTEM HALTED" && echo "Ok!" || echo "Error"

tests/machine.uarm.cfg:
	@sed -e "s|\@INCDIR\@|$(INCDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" tests/machine.uarm.tmp > tests/machine.uarm.cfg
