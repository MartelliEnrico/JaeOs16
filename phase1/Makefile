.phony: all clean

all: p1test

p1test:
	arm-none-eabi-gcc p1test.c -I. -I/usr/include/uarm -o p1test --specs=nosys.specs

clean:
	rm p1test
