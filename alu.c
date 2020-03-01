#include <stdint.h>
#include "registers.h"
#include "status.h"
#include "alu.h"
#include "mem.h"

void setflagvc(HEX_PAIR test)
{
    if (test.w>127)
        {
        setvflag();
        if (test.w>255)
            setcflag();
        else
            resetcflag();
        }
    else
        {
        resetvflag();
        resetcflag();
        }
}

void setflagc(HEX_PAIR test)
{
    if (test.w>255)
        setcflag();
    else
        resetcflag();
}

void adc(unsigned char data)
{
    HEX_PAIR test;
    unsigned char areg=readareg();

    test.w=data+areg;
    setflagvc(test);
    writeareg(test.c[LOWBYTE]);
}

void sbc( unsigned char data)
{
    HEX_PAIR test;
    unsigned char areg=readareg();

    test.w=areg-data;
    setflagvc(test);
    writeareg(test.c[LOWBYTE]);
}

unsigned char asl(unsigned char data)
{
    HEX_PAIR test;

    test.w = data << 1;
    setflagc(test);
    setnzflag(test.c[LOWBYTE]);
    return test.c[LOWBYTE];
}

unsigned char lsr(unsigned char data)
{
    char b = data & 0x01;   /* original bit zero */
    data = data >> 1;
    b ? setcflag() : resetcflag();            /* is put into carry */
    setnzflag(data);

    return data;
}

unsigned char rol(unsigned char data)
{                                    
    char b = data & 0x01;   /* original bit zero */
    char c = readcflag();   /* original carry */
    data = data << 1;
    data |= c >> 7;         /* carry shifted into bit 0 */
    b ? setcflag() : resetcflag();            /* is put into carry */
    setnzflag(data);

    return data;
}               

unsigned char ror(unsigned char data)
{
    char b = data & 0x01;   /* original bit zero */
    char c = readcflag();   /* original carry */
    data = data >> 1;
    data |= c << 7;         /* carry shifted into bit 7 */
    b ? setcflag() : resetcflag();            /* is put into carry */
    setnzflag(data);

    return data;
}

void ora(unsigned char data)
{
    unsigned char areg=readareg();

    areg |= data;
    writeareg(areg);
}

void and(unsigned char data)
{
    unsigned char areg=readareg();

    areg &= data;
    writeareg(areg);
}

void eor(unsigned char data)
{
    unsigned char areg=readareg();

    areg ^= data;
    writeareg(areg);
}

unsigned char inc(unsigned char data)
{
    data++;
    return data;
}

unsigned char dec(unsigned char data)   
{                                    
    data--;
    return data;   
}

void inm(uint16_t address)
{
    unsigned char data;
    data=inc(memread(address));
    setnzflag(data);
    memwrite(data, address);
}

void ina()
{
    writeareg(inc(readareg()));
}

void inx()
{
    writexreg(inc(readxreg()));
}

void iny()
{
    writeyreg(inc(readyreg()));
}

void dem(uint16_t address)
{                         
    unsigned char data;
    data=dec(memread(address));
    setnzflag(data);           
    memwrite(data, address);
}                                   
 
void dea()
{         
    writeareg(dec(readareg()));
}
 
void dex()
{         
    writexreg(dec(readxreg())); 
}                              

void dey()
{         
    writeyreg(dec(readxreg()));
}                              
