	lda #$32
	sta $2000
	lda #$31
	sta $2001
	lda #$34
	sta $2002
	lda #$33
	sta $2003
	ldx #$00
xloop:	
	ldy #$00
yloop:	
	lda $2000,y
	sbc $2001,y
	bpl noop
	lda $2000,y
	sta $00
	lda $2001,y
	sta $2000,y
	lda $00
	sta $2001,y
noop:	
	iny
	cpy #$04
	bne yloop
	inx
	cpx #$04
	bne xloop
	