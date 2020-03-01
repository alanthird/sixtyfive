extern void allocateram(void);
extern void blockwrite(const void* data, uint16_t offset, int size);
extern void memwrite(unsigned char, uint16_t);
extern unsigned char memread(uint16_t);

extern void lda(uint16_t);
extern void ldx(uint16_t);
extern void ldy(uint16_t);
extern void sta(uint16_t);
extern void stx(uint16_t);
extern void sty(uint16_t);
