ifeq ($(shell uname), Darwin)
	INCDIR ?= /usr/local/include
else
	INCDIR ?= /usr/include
endif

CURDIR = $(shell pwd)

BIN = build/p1test
LIB = build/libphase1.a
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR)/uarm -I../libs -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/uarm/ldscripts/elf32ltsarm.h.uarmcore.x
AR = arm-none-eabi-ar
ARFLAGS = rcs

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

.PHONY: all clean test export

all: test

$(BIN).core.uarm: $(BIN)
	elf2uarm -k $(BIN)

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) $(INCDIR)/uarm/crtso.o $(INCDIR)/uarm/libuarm.o $(OBJS)

build/%.o: src/%.c
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f build/* tests/machine.uarm.cfg tests/term0.uarm

test: $(BIN).core.uarm tests/machine.uarm.cfg
	@uarm -c tests/machine.uarm.cfg -e -x && echo "Success, test passed." || (echo "Test failed." && exit 1)

tests/machine.uarm.cfg:
	@sed -e "s|\@INCDIR\@|$(INCDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" tests/machine.uarm.tmp > tests/machine.uarm.cfg

export: $(LIB)
	cp $(LIB) $(HEADERS) ../libs/

$(LIB): build/asl.o build/pcb.o
	$(AR) $(ARFLAGS) $@ $^