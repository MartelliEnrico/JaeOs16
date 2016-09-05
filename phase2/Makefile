BASEDIR ?= /usr/local

INCDIR = $(BASEDIR)/include/uarm
CURDIR = $(shell pwd)

BIN = build/kernel
GCC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=arm7tdmi -I$(INCDIR) -Iinclude -Wall
LD = arm-none-eabi-ld
LDFLAGS = -T $(INCDIR)/ldscripts/elf32ltsarm.h.uarmcore.x

OBJS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
OBJS += $(patsubst include/%.c, build/%.o, $(wildcard include/*.c))

.PHONY: all clean test

all: test

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) $(INCDIR)/crtso.o $(INCDIR)/libuarm.o $(OBJS)

-include $(OBJS:.o=.d)

build/%.o: **/%.c
	$(GCC) $(CFLAGS) -c $< -o $@
	@$(GCC) $(CFLAGS) -MM $< -MT "build/$*.o" > build/$*.d

clean:
	rm -f build/* tests/machine.uarm.cfg tests/term0.uarm

test: $(BIN) tests/machine.uarm.cfg
	@uarm -c tests/machine.uarm.cfg -e -x
		&& echo "Success, test passed." \
		|| (echo "Test failed." && exit 1)

tests/machine.uarm.cfg:
	@sed -e "s|\@BASEDIR\@|$(BASEDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" \
		tests/machine.uarm.tmp > tests/machine.uarm.cfg
