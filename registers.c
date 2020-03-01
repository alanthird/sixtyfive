#include <stdlib.h>
#include <stdint.h>
#include "status.h"
#include "registers.h"

unsigned char readareg(void)
{
    return a;
}

void writeareg(unsigned char data)
{
    a=data;
    setnzflag(data);
}

unsigned char readxreg(void)
{               
    return x;
}            
 
void writexreg(unsigned char data)
{                     
    x=data;
    setnzflag(data);
}          

unsigned char readyreg(void)
{               
    return y;
}            
 
void writeyreg(unsigned char data)
{                     
    y=data;
    setnzflag(data);
}          

unsigned char readbreg(void)
{
    return 0x00;
}


uint16_t readpc(void)
{
    return PC;
}

void writepc(uint16_t data)
{
    PC=data;
}

unsigned char readpch(void)
{               
    return PCH;
}            
 
void writepch(unsigned char data)
{                     
    PCH=data;
}          


unsigned char readpcl(void)
{               
    return PCL;
}            
 
void writepcl(unsigned char data)
{                     
    PCL=data;
}          

void incpc()
{
    PC++;
}


void tax()
{
    writexreg(readareg());
}

void txa()
{
    writeareg(readxreg());
}

void tay()
{
    writeyreg(readareg());
}

void tya()
{
    writeareg(readyreg());
}
