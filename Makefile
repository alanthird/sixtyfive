CFLAGS = -g -Wall -O2
SRCS = alu.c branch.c compare.c mem.c opcodes.c registers.c status.c stack.c
CC = gcc

all: sixtyfive

sixtyfive:
	$(CC) $(CFLAGS) -o sixtyfive main.c $(SRCS);

clean:
	rm -f sixtyfive
	rm -rf sixtyfive.dSYM
	$(MAKE) -C testing clean

check: sixtyfive
	$(MAKE) -C testing check
