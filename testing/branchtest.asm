	lda #$00
	ldx #$0f
	stx $01
label:
	adc #$01
	cmp $01
	bne label

	ldy #$ff
	