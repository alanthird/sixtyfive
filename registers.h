typedef union {         /* Interpret a byte in hexadecimal 'digits' as...*/
  unsigned char c[2];   /* ...two separate hexadecimal 'characters' or...*/
  uint16_t w;           /* ...as composite hexadecimal 'character pair'. */
} HEX_PAIR;

#define LOWBYTE 0
#define HIGHBYTE 1

#define PCL (pc.c[LOWBYTE])
#define PCH (pc.c[HIGHBYTE])
#define PC  (pc.w)

/* accumulator */

unsigned char a;

/* x register */

unsigned char x;

/* y register */

unsigned char y;


/* convenient struct access to program counter */
HEX_PAIR pc;

extern unsigned char readareg(void);
extern void writeareg(unsigned char);

extern unsigned char readxreg(void); 
extern void writexreg(unsigned char);

extern unsigned char readyreg(void); 
extern void writeyreg(unsigned char);

extern unsigned char readbreg(void); 

extern uint16_t readpc(void); 
extern void writepc(uint16_t);

extern unsigned char readpch(void); 
extern void writepch(unsigned char);

extern unsigned char readpcl(void); 
extern void writepcl(unsigned char);
extern void incpc(void);

extern void tax(void);
extern void txa(void);
extern void tay(void);
extern void tya(void);
