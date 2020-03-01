CFLAGS = -g -Wall -O2
SRCS = alu.c branch.c compare.c mem.c opcodes.c registers.c status.c stack.c
CC = gcc

all:
	$(CC) $(CFLAGS) -o sixtyfive main.c $(SRCS);

clean:
	rm -f sixtyfive
