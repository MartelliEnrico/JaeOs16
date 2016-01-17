BIN = p1test
GCC = arm-none-eabi-gcc
CFLAGS = --specs=nosys.specs -mcpu=arm7tdmi -I/usr/local/include/uarm -Wall -c
LD = arm-none-eabi-ld
LDFLAGS = -T /usr/local/include/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

OBJS = $(patsubst %.c, %.o, $(wildcard ./*.c))

all: $(OBJS)
	$(LD) $(LDFLAGS) -o $(BIN) /usr/local/include/uarm/crtso.o /usr/local/include/uarm/libuarm.o $(OBJS)
	elf2uarm -k $(BIN)

%.o: %.c
	$(GCC) $(CFLAGS) $< -o $@

%.o: %.c %.h
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) *.o
