#include <stdint.h>
#include "registers.h"
#include "status.h"
#include "mem.h"
#include "compare.h"

/* I'm not really happy with this function, it seems overly complex
 * for what it does
 */
void bit(uint16_t address)
{
    unsigned char areg;
    unsigned char data;
    unsigned char preg;

    areg=readareg();
    data=memread(address);
    preg=readsreg();

    if ((areg & data)==0x00)
        setzflag();
    else
        resetzflag();

    preg=(( preg & 0x3f ) | ( data & 0xc0 ));
    writesreg(preg);
}

void cmp(uint16_t address)
{
    unsigned char areg=readareg();
    unsigned char data=memread(address);

    if (areg == data)
    {
        setzflag();
        setcflag();
    }
    else if (areg > data)
    {
        setcflag();
        resetzflag();
    }
    else
    {
        resetcflag();
        resetzflag();
    }

    if (areg >= 0x80)
        setnflag();
    else
        resetnflag();
}

void cpx(uint16_t address)
{
    unsigned char xreg=readxreg();
    unsigned char data=memread(address);

    if (xreg == data)
    {
        setzflag();
        setcflag();
    }
    else if (xreg > data)
    {
        setcflag();
        resetzflag();
    }
    else
    {
        resetcflag();
        resetzflag();
    }

    if (xreg >= 0x80)
        setnflag();
    else
        resetnflag();
}

void cpy(uint16_t address)
{
    unsigned char yreg=readyreg();
    unsigned char data=memread(address);

    if (yreg == data)
    {
        setzflag();
        setcflag();
    }
    else if (yreg > data)
    {
        setcflag();
        resetzflag();
    }
    else
    {
        resetcflag();
        resetzflag();
    }

    if (yreg >= 0x80)
        setnflag();
    else
        resetnflag();
}
