@ POC do mapeamento linear de 96 MB (doc-futuro/02-abordagem-a-linear.md).
@ `make ROM_FILLER_MB=N` preenche N MB entre script_data e .rodata, para que
@ todo o .rodata fique acima de 32 MB. ROM_FILLER_MB=0 nao gera nada.
	.section rom_filler, "a"
	.ifdef ROM_FILLER_BYTES
	.if ROM_FILLER_BYTES
	.fill ROM_FILLER_BYTES, 1, 0xFF
	.endif
	.endif
