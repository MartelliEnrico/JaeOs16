.phony: all clean

all: p1test

p1test:
	arm-none-eabi-gcc -I. -xc --specs=nosys.specs -o p1test p1test.c process.c tree.c queue.c semaphore.c

clean:
	rm p1test