#define N (0x80) /* Negative flag */
#define V (0x40) /* signed oVerflow flag */
#define U (0x20) /* Unused */
#define B (0x10) /* Break flag (probly not needed ATM) */
#define D (0x08) /* Decimal flag (1 when in BCD mode (???)) */
#define I (0x04) /* Irq flag, dunno if this'll be implemented */
#define Z (0x02) /* Zero flag */
#define C (0x01) /* Carry flag (set on unsigned overflow) */

#define CLC() resetcflag()
#define SEC() setcflag()
#define CLI() resetiflag()
#define SEI() setiflag()
#define CLV() resetcflag()
#define CLD() resetdflag()
#define SED() setdflag()

extern void initstatus(void); /* initialize the register */

/*
 * all below are layed out:
 * set n bit
 * unset n bit
 * retrieve n bit
 * where n is the bit as defined above
 */

extern void setnflag(void); 
extern void resetnflag(void);
extern int readnflag(void);

extern void setvflag(void);
extern void resetvflag(void);
extern int readvflag(void);

extern void setbflag(void);
extern void resetbflag(void);
extern int readbflag(void);

extern void setdflag(void);
extern void resetdflag(void);
extern int readdflag(void);

extern void setiflag(void);
extern void resetiflag(void);
extern int readiflag(void);

extern void setzflag(void);
extern void resetzflag(void);
extern int readzflag(void);

extern void setcflag(void);
extern void resetcflag(void);
extern int readcflag(void);


/* These two functions are different from those above */

extern unsigned char readsreg(void);
extern void writesreg(unsigned char);


extern void setnzflag(unsigned char);
