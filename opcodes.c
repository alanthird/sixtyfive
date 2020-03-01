#include <stdint.h>
#include "mem.h"
#include "registers.h"
#include "alu.h"
#include "stack.h"
#include "status.h"
#include "branch.h"
#include "compare.h"

uint16_t memaddress(unsigned char low, unsigned char high)
{
  HEX_PAIR alter;

  alter.c[LOWBYTE]=low;
  alter.c[HIGHBYTE]=high;

  return alter.w;
}

void execute()
{
  unsigned char instruction;

  /* this is used to temporarily store addresses that are required for
   * reads AND writes and therefore MUST be stored or worked out twice
   */
  uint16_t ta;

  instruction = memread(readpc());
  incpc();

  switch(instruction)
    {
      /* ADC opcodes */
      /* immediate */
    case 0x69:
      adc(memread(readpc()));
      incpc();
      break;

      /* Zero Page */
    case 0x65:
      adc(memread(memaddress(memread(readpc()), 0x00)));
      incpc();
      break;

      /* Zero Page, X */
    case 0x75:
      adc(memread(memaddress(memread(readpc())+readxreg(), 0x00)));
      incpc();
      break;

      /* absolute */
    case 0x6d:
      adc(memread(memaddress(memread(readpc()),(memread(readpc()+1)))));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0x7d:
      adc(memread(memaddress(memread(readpc()),(memread(readpc()+1)))+readxreg()));
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0x79:
      adc(memread(memaddress(memread(readpc()),(memread(readpc()+1)))+readyreg()));
      incpc();
      incpc();
      break;

      /* indirect x */
    case 0x61:
      adc(memread(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00))));
      incpc();
      break;

      /* indirect y */
    case 0x71:
      adc(memread(memaddress(memread(readpc()), memread(readpc()+1)+readyreg())));
      incpc();
      break;
      /* end ADC opcodes */

      /* SBC opcodes */
      /* immediate */
    case 0xe9:
      sbc(memread(readpc()));
      incpc();
      break;

      /* Zero Page */
    case 0xe5:
      sbc(memread(memaddress(memread(readpc()), 0x00)));
      incpc();
      break;

      /* Zero Page, X */
    case 0xf5:
      sbc(memread(memaddress(memread(readpc())+readxreg(), 0x00)));
      incpc();
      break;

      /* absolute */
    case 0xed:
      sbc(memread(memaddress(memread(readpc()),(memread(readpc()+1)))));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0xfd:
      sbc(memread(memaddress(memread(readpc()),(memread(readpc()+1)))+readxreg()));
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0xf9:
      sbc(memread(memaddress(memread(readpc()),(memread(readpc()+1)))+readyreg()));
      incpc();
      incpc();
      break;

      /* indirect x */
    case 0xe1:
      sbc(memread(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00))));
      incpc();
      break;

      /* indirect y */
    case 0xf1:
      sbc(memread(memaddress(memread(readpc()), memread(readpc()+1)+readyreg())));
      incpc();
      break;
      /* end SBC opcodes */

      /* ASL opcodes */
      /* Immplied */
    case 0x0a:
      writeareg(asl(readareg()));
      break;

      /* Zero Page */
    case 0x06:
      ta=memaddress(memread(readpc()), 0x00);
      memwrite(asl(memread(ta)), ta);
      incpc();
      break;

      /* Zero Page, x */
    case 0x16:
      ta=memaddress(memread(readpc()+readxreg()),0x00);
      memwrite(asl(memread(ta)), ta);
      incpc();
      break;

      /* Absolute */
    case 0x0e:
      ta=memaddress(memread(readpc()), memread(readpc()+1));
      memwrite(asl(memread(ta)), ta);
      incpc();
      incpc();
      break;

      /* Absolute, X */
    case 0x1e:
      ta=memaddress(memread(readpc())+readxreg(), memread(readpc()+1));
      memwrite(asl(memread(ta)), ta);
      incpc();
      incpc();
      break;
      /* end ASL opcodes */

      /* LSR opcodes */
      /* Immplied */
    case 0x4a:
      writeareg(lsr(readareg()));
      break;

      /* Zero Page */
    case 0x46:
      ta=memaddress(memread(readpc()), 0x00);
      memwrite(lsr(memread(ta)), ta);
      incpc();
      break;

      /* Zero Page, x */
    case 0x56:
      ta=memaddress(memread(readpc()+readxreg()),0x00);
      memwrite(lsr(memread(ta)), ta);
      incpc();
      break;

      /* Absolute */
    case 0x4e:
      ta=memaddress(memread(readpc()), memread(readpc()+1));
      memwrite(lsr(memread(ta)), ta);
      incpc();
      incpc();
      break;

      /* Absolute, X */
    case 0x5e:
      ta=memaddress(memread(readpc())+readxreg(), memread(readpc()+1));
      memwrite(lsr(memread(ta)), ta);
      incpc();
      incpc();
      break;
      /* end LSR opcodes */

      /* ROL opcodes */
      /* Immplied */
    case 0x2a:
      writeareg(rol(readareg()));
      break;

      /* Zero Page */
    case 0x26:
      ta=memaddress(memread(readpc()), 0x00);
      memwrite(rol(memread(ta)), ta);
      incpc();
      break;

      /* Zero Page, x */
    case 0x36:
      ta=memaddress(memread(readpc()+readxreg()),0x00);
      memwrite(rol(memread(ta)), ta);
      incpc();
      break;

      /* Absolute */
    case 0x2e:
      ta=memaddress(memread(readpc()), memread(readpc()+1));
      memwrite(rol(memread(ta)), ta);
      incpc();
      incpc();
      break;

      /* Absolute, X */
    case 0x3e:
      ta=memaddress(memread(readpc())+readxreg(), memread(readpc()+1));
      memwrite(rol(memread(ta)), ta);
      incpc();
      incpc();
      break;
      /* end ROL opcodes */

      /* ROR opcodes */
      /* Immplied */
    case 0x6a:
      writeareg(ror(readareg()));
      break;

      /* Zero Page */
    case 0x66:
      ta=memaddress(memread(readpc()), 0x00);
      memwrite(ror(memread(ta)), ta);
      incpc();
      break;

      /* Zero Page, x */
    case 0x76:
      ta=memaddress(memread(readpc()+readxreg()),0x00);
      memwrite(ror(memread(ta)), ta);
      incpc();
      break;

      /* Absolute */
    case 0x6e:
      ta=memaddress(memread(readpc()), memread(readpc()+1));
      memwrite(ror(memread(ta)), ta);
      incpc();
      incpc();
      break;

      /* Absolute, X */
    case 0x7e:
      ta=memaddress(memread(readpc())+readxreg(), memread(readpc()+1));
      memwrite(ror(memread(ta)), ta);
      incpc();
      incpc();
      break;
      /* end ROR opcodes */

      /* INC opcodes */
      /* zero page */
    case 0xe6:
      inm(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0xf6:
      inm(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xee:
      inm(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0xfe:
      inm(memaddress(memread(readpc()), memread(readpc()+1))+readxreg());
      incpc();
      incpc();
      break;
      /* end INC opcodes */

      /* DEC opcodes */
      /* zero page */
    case 0xc6:
      dem(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0xd6:
      dem(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xce:
      dem(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0xde:
      dem(memaddress(memread(readpc()), memread(readpc()+1))+readxreg());
      incpc();
      incpc();
      break;
      /* end DEC opcodes */

      /* register IN? and de? opcodes */
      /* INX */
    case 0xe8:
      inx();
      break;

      /* INY */
    case 0xc8:
      iny();
      break;

      /* DEX */
    case 0xca:
      dex();
      break;

      /* DEY */
    case 0x88:
      dey();
      break;

      /* end register IN? and DE? opcodes */

      /* ORA opcodes */
      /* Immediate */
    case 0x09:
      ora(memread(readpc()));
      incpc();
      break;

      /* Zero Page */
    case 0x05:
      ora(memread(memaddress(memread(readpc()), 0x00)));
      incpc();
      break;

      /* zero page, x */
    case 0x15:
      ora(memread(memaddress(memread(readpc())+readxreg(), 0x00)));
      incpc();
      break;

      /* absolute */
    case 0x0d:
      ora(memread(memaddress(memread(readpc()), memread(readpc()+1))));
      incpc();
      incpc();
      break;

      /* absolute x */
    case 0x1d:
      ora(memread(memaddress(memread(readpc()), memread(readpc()+1))+readxreg()));
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0x19:
      ora(memread(memaddress(memread(readpc()), memread(readpc()+1))+readyreg()));
      incpc();
      incpc();
      break;

      /* indirect, x */
    case 0x01:
      ora(memread(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00))));
      incpc();
      break;

      /* indirect, y */
    case 0x11:
      ora(memread(memaddress(memread(readpc()), memread(readpc()+1)+readyreg())));
      incpc();
      break;            
      /* end ORA opcodes */

      /* AND opcodes */
      /* Immediate */
    case 0x29:
      and(memread(readpc()));
      incpc();
      break;

      /* Zero Page */
    case 0x25:
      and(memread(memaddress(memread(readpc()), 0x00)));
      incpc();
      break;

      /* zero page, x */
    case 0x35:
      and(memread(memaddress(memread(readpc())+readxreg(), 0x00)));
      incpc();
      break;

      /* absolute */
    case 0x2d:
      and(memread(memaddress(memread(readpc()), memread(readpc()+1))));
      incpc();
      incpc();
      break;

      /* absolute x */
    case 0x3d:
      and(memread(memaddress(memread(readpc()), memread(readpc()+1))+readxreg()));
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0x39:
      and(memread(memaddress(memread(readpc()), memread(readpc()+1))+readyreg()));
      incpc();
      incpc();
      break;

      /* indirect, x */
    case 0x21:
      and(memread(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00))));
      incpc();
      break;

      /* indirect, y */
    case 0x31:
      and(memread(memaddress(memread(readpc()), memread(readpc()+1)+readyreg())));
      incpc();
      break;            
      /* end AND opcodes */

      /* EOR opcodes */
      /* Immediate */
    case 0x49:
      eor(memread(readpc()));
      incpc();
      break;

      /* Zero Page */
    case 0x45:
      eor(memread(memaddress(memread(readpc()), 0x00)));
      incpc();
      break;

      /* zero page, x */
    case 0x55:
      eor(memread(memaddress(memread(readpc())+readxreg(), 0x00)));
      incpc();
      break;

      /* absolute */
    case 0x4d:
      eor(memread(memaddress(memread(readpc()), memread(readpc()+1))));
      incpc();
      incpc();
      break;

      /* absolute x */
    case 0x5d:
      eor(memread(memaddress(memread(readpc()), memread(readpc()+1))+readxreg()));
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0x59:
      eor(memread(memaddress(memread(readpc()), memread(readpc()+1))+readyreg()));
      incpc();
      incpc();
      break;

      /* indirect, x */
    case 0x41:
      eor(memread(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00))));
      incpc();
      break;

      /* indirect, y */
    case 0x51:
      eor(memread(memaddress(memread(readpc()), memread(readpc()+1)+readyreg())));
      incpc();
      break;            
      /* end EOR opcodes */


      /* status register opcodes */
      /* CLC */
    case 0x18:
      CLC();
      break;

      /* SEC */
    case 0x38:
      SEC();
      break;

      /* CLI */
    case 0x58:
      CLI();
      break;

      /* SEI */
    case 0x78:
      SEI();
      break;

      /* CLV */
    case 0xb8:
      CLV();
      break;

      /* CLD */
    case 0xd8:
      CLD();
      break;

      /* SED */
    case 0xf8:
      SED();
      break;
      /* end status register opcodes */


      /* BIT opcodes */
      /* zero page */
    case 0x24:
      bit(memread(memaddress(memread(readpc()), 0x00)));
      incpc();
      break;

      /* absolute */
    case 0x2c:
      bit(memread(memaddress(memread(readpc()), memread(readpc()+1))));
      incpc();
      incpc();
      break;
      /* end BIT opcodes */

      /* CMP opcodes */
      /* Immediate */
    case 0xc9:
      cmp(readpc());
      incpc();
      break;

      /* Zero Page */
    case 0xc5:
      cmp(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0xd5:
      cmp(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xcd:
      cmp(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute x */
    case 0xdd:
      cmp(memaddress(memread(readpc()), memread(readpc()+1))+readxreg());
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0xd9:
      cmp(memaddress(memread(readpc()), memread(readpc()+1))+readyreg());
      incpc();
      incpc();
      break;

      /* indirect, x */
    case 0xc1:
      cmp(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00)));
      incpc();
      break;

      /* indirect, y */
    case 0xd1:
      cmp(memaddress(memread(readpc()), memread(readpc()+1)+readyreg()));
      incpc();
      break;            
      /* end CMP opcodes */

      /* CPX opcodes */
      /* immediate */
    case 0xe0:
      cpx(readpc());
      incpc();
      break;

      /* zero page */
    case 0xe4:
      cpx(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xec:
      cpx(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;
      /* end CPX opcodes */

      /* CPY opcodes */
      /* immediate */
    case 0xc0:
      cpy(readpc());
      incpc();
      break;

      /* zero page */
    case 0xc4:
      cpy(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xcc:
      cpy(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;
      /* end CPY opcodes */


      /* branch opcodes */
      /* BPL */
    case 0x10:
      bpl(memread(readpc()));
      incpc();
      break;

      /* BMI */
    case 0x30:
      bmi(memread(readpc()));
      incpc();
      break;

      /* BVC */
    case 0x50:
      bvc(memread(readpc()));
      incpc();
      break;

      /* BVS */
    case 0x70:
      bvs(memread(readpc()));
      incpc();
      break;

      /* BCC */
    case 0x90:
      bcc(memread(readpc()));
      incpc();
      break;

      /* BCS */
    case 0xb0:
      bcs(memread(readpc()));
      incpc();
      break;

      /* BNE */
    case 0xd0:
      bne(memread(readpc()));
      incpc();
      break;

      /* BEQ */
    case 0xf0:
      beq(memread(readpc()));
      incpc();
      break;

      /* JMP */
      /* absolute */
    case 0x4c:
      jmpabs(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* indirect */
    case 0x6c:
      jmpind(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* JSR */
    case 0x20:
      jsr(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* RTS */
    case 0x60:
      rts();
      break;
      /* end branch opcodes */

      /* register opcodes */
      /* TAX */
    case 0xaa:
      tax();
      break;

      /* TXA */
    case 0x8a:
      txa();
      break;

      /* TAY */
    case 0xa8:
      tay();
      break;

      /* TYA */
    case 0x98:
      tya();
      break;
      /* end register opcodes */

      /* stack opcodes */
      /* TXS */
    case 0x9a:
      txs();
      break;

      /* TSX */
    case 0xba:
      tsx();
      break;

      /* PHA */
    case 0x48:
      pha();
      break;

      /* PLA */
    case 0x68:
      pla();
      break;

      /* PHP */
    case 0x08:
      php();
      break;

      /* PLP */
    case 0x28:
      plp();
      break;
      /* end stack opcodes */

      /* memory opcodes */
      /* LDA opcodes */
      /* immediate */
    case 0xa9:
      lda(readpc());
      incpc();
      break;

      /* zero page */
    case 0xa5:
      lda(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0xb5:
      lda(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xad:
      lda(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0xbd:
      lda(memaddress(memread(readpc()), memread(readpc()+1))+readxreg());
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0xb9:
      lda(memaddress(memread(readpc()), memread(readpc()+1))+readyreg());
      incpc();
      incpc();
      break;

      /* indirect, x */
    case 0xa1:
      lda(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00)));
      incpc();
      incpc();
      break;

      /* indirect, y */
    case 0xb1:
      lda(memaddress(memread(readpc()), memread(readpc()+1)+readyreg()));
      incpc();
      incpc();
      break;
      /* end LDA opcodes */

      /* LDX opcodes */
      /* immediate */
    case 0xa2:
      ldx(readpc());
      incpc();
      break;

      /* zero page */
    case 0xa6:
      ldx(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, y */
    case 0xb6:
      ldx(memaddress(memread(readpc())+readyreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xae:
      ldx(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0xbe:
      ldx(memaddress(memread(readpc()), memread(readpc()+1))+readyreg());
      incpc();
      incpc();
      break;
      /* end LDX opcodes */

      /* LDY opcodes */
      /* immediate */
    case 0xa0:
      ldy(readpc());
      incpc();
      break;

      /* zero page */
    case 0xa4:
      ldy(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0xb:
      ldy(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0xac:
      ldy(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0xbc:
      ldy(memaddress(memread(readpc()), memread(readpc()+1))+readxreg());
      incpc();
      incpc();
      break;
      /* end LDX opcodes */

      /* STA opcodes */
      /* zero page */
    case 0x85:
      sta(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0x95:
      sta(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0x8d:
      sta(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;

      /* absolute, x */
    case 0x9d:
      sta(memaddress(memread(readpc()), memread(readpc()+1))+readxreg());
      incpc();
      incpc();
      break;

      /* absolute, y */
    case 0x99:
      sta(memaddress(memread(readpc()), memread(readpc()+1))+readyreg());
      incpc();
      incpc();
      break;

      /* indirect, x */
    case 0x81:
      sta(memaddress(memaddress(memread(readpc()), 0x00), memaddress(memread(readpc()+1), 0x00)));
      incpc();
      incpc();
      break;

      /* indirect, y */
    case 0x91:
      sta(memaddress(memread(readpc()), memread(readpc()+1)+readyreg()));
      incpc();
      incpc();
      break;
      /* end STA opcodes */

      /* LDX opcodes */
      /* zero page */
    case 0x86:
      stx(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, y */
    case 0x96:
      stx(memaddress(memread(readpc())+readyreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0x8e:
      stx(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;
      /* end STX opcodes */

      /* STY opcodes */
      /* zero page */
    case 0x84:
      sty(memaddress(memread(readpc()), 0x00));
      incpc();
      break;

      /* zero page, x */
    case 0x94:
      sty(memaddress(memread(readpc())+readxreg(), 0x00));
      incpc();
      break;

      /* absolute */
    case 0x8c:
      sty(memaddress(memread(readpc()), memread(readpc()+1)));
      incpc();
      incpc();
      break;
      /* end STY opcodes */

      /* NOP just cos it's "official" */
    case 0xea:
      break;

    default:
      break;
    }
}



