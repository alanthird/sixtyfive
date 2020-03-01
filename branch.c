#include <stdint.h>
#include "registers.h"
#include "mem.h"
#include "stack.h"
#include "status.h"
#include "branch.h"

void bpl(char data)
{
    if (!(readnflag()))
        writepc(readpc()+data);
}

void bmi(char data)
{
    if (readnflag())
        writepc(readpc()+data);
}

void bvc(char data)
{                          
    if (!(readvflag())) 
        writepc(readpc()+data); 
}                              
 
void bvs(char data)    
{
    if (readvflag())    
        writepc(readpc()+data); 
}

void bcc(char data)
{                          
    if (!(readcflag())) 
        writepc(readpc()+data); 
}                              
 
void bcs(char data)    
{
    if (readcflag())    
        writepc(readpc()+data); 
}

void bne(char data)
{                          
    if (!(readzflag())) 
        writepc(readpc()+data); 
}                              
 
void beq(char data)    
{
    if (readzflag())    
        writepc(readpc()+data); 
}

void jmpabs(uint16_t address)
{
    writepc(address);
}

void jmpind(uint16_t address)
{
    writepc(memread(address));
}

void jsr(uint16_t address)
{
    pushpc();
    writepc(address);
}

void rts()
{
    pullpc();
}
