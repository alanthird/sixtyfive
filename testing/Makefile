tests = $(basename $(wildcard *.asm))
ASM = xa
SF = ../sixtyfive

check: $(tests)

.PHONY $(tests): %: %.65
	$(info Testing: $@)
	$(SF) $*.65

%.65: %.asm
	$(ASM) $< -o $@

clean:
	rm -f *.65
