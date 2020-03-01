#include <stdint.h>
#include "registers.h"
#include "status.h"

/* status byte */

static unsigned char p;

void initstatus()
{
    p=U;
}

void setnflag()
{
    p |= N;
}

void resetnflag()
{
    p &= ~N;
}

int readnflag()
{
    return ((p & N) != 0);
}


void setvflag()
{       
    p |= V;
}        

/* effectively CLV */
void resetvflag()   
{             
    p &= ~V;
}

int readvflag()
{
    return ((p & V) != 0);
}
 
    
void setbflag()
{       
    p |= B;
}        

void resetbflag()   
{             
    p &= ~B;
}

int readbflag()
{
    return ((p & B) != 0);
}

/* effectively SED */
void setdflag()
{
    p |= D;
}        

/* effectively CLD */
void resetdflag()   
{             
    p &= ~D;
}

int readdflag()
{
    return ((p & D) != 0);
}

/* effectively SEI */
void setiflag()
{
    p |= I;
}        

/* effectively CLI */
void resetiflag()
{             
    p &= ~I;
}

int readiflag()
{
    return ((p & I) != 0);
}


void setzflag()
{
    p |= Z;
}        

void resetzflag()   
{             
    p &= ~Z;
}

int readzflag()
{
    return ((p & Z) != 0);
}


/* effectively SEC */
void setcflag()
{
    p |= C;
}        

/* effectively CLC */
void resetcflag()   
{             
    p &= ~C;
}

int readcflag()
{
    return ((p & C) != 0);
}

unsigned char readsreg()
{
    return p;
}

void writesreg(unsigned char data)
{
    p=data;
}


void setnzflag(unsigned char data)
{
    p=(( p & 0x7f ) | ( data & 0x80 ));
    if (data == 0x00)
        setzflag();
    else
        resetzflag();
}
