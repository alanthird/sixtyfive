#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "registers.h"
#include "mem.h"

static unsigned char *memspace;

/* allocate the 64K of addressable memory */

void allocateram()
{
    memspace = (unsigned char *)calloc(65536, sizeof(unsigned char));
    if (memspace == NULL) {
        perror("Could not allocate memory: ");
        exit(1);
    }
}

void blockwrite(const void* data, uint16_t offset, int size)
{
    memcpy(memspace+offset, data, size);
}

/* write one byte of data to address in memory */

void memwrite(unsigned char data, uint16_t address)
{
    *(memspace + address) = data;
}

/* read one byte of data from address */

unsigned char memread(uint16_t address)
{
    return *(memspace + address);
}


void lda(uint16_t address)
{
    writeareg(memread(address));
}

void ldx(uint16_t address)
{
    writexreg(memread(address));
}

void ldy(uint16_t address)
{
    writeyreg(memread(address));
}

void sta(uint16_t address)
{
    memwrite(readareg(), address);
}

void stx(uint16_t address)
{
    memwrite(readxreg(), address);
}

void sty(uint16_t address)
{
    memwrite(readyreg(), address);
}
