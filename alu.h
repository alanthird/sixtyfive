extern void setflagvc(HEX_PAIR);
extern void setflagc(HEX_PAIR);

extern void adc(unsigned char);
extern void sbc(unsigned char);
extern unsigned char asl(unsigned char);
extern unsigned char lsr(unsigned char);
extern unsigned char rol(unsigned char);
extern unsigned char ror(unsigned char);
extern void ora(unsigned char);
extern void and(unsigned char);
extern void eor(unsigned char);
extern unsigned char inc(unsigned char);
extern unsigned char dec(unsigned char);

extern void inm(uint16_t);
extern void ina(void);
extern void inx(void);
extern void iny(void);
extern void dem(uint16_t);
extern void dea(void);
extern void dex(void);
extern void dey(void);
