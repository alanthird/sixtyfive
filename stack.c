#include <stdint.h>
#include <stdio.h>
#include "registers.h"
#include "status.h"
#include "mem.h"

static int sp = 0x200;

void push(unsigned char c)
{
    if (sp == 0x100) {
        perror("Stack overflow, exiting\n");
        exit(1);
    }
    memwrite(c, --sp);
}

unsigned char pop()
{
    if (sp == 0x200) {
        perror("Stack underflow, exiting\n");
        exit(1);
    }
    return memread(sp++);
}

void txs(void)
{
    push(readxreg());
}

void tsx(void)
{
    writexreg(pop());
}

void pha(void)
{
    push(readareg());
}

void pla(void)
{
    writeareg(pop());
}

void php(void)
{
    push(readsreg());
}

void plp(void)
{
    writesreg(pop());
}


void pushpc(void)
{
    push(readpcl());
    push(readpch());
}

void pullpc(void)
{
    writepch(pop());
    writepcl(pop());
}
