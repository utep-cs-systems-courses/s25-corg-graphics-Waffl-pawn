	.text
StrLength:
	sub #6, r1
	mov #0, 0(r1)
	mov #0, 2(r1)
	mov #0, 4(r1)

	top:
	add.b r12, r12
	cmp.b #0, 2(r1)
	      JZ end

	add #1, 2(r1)
	add #5, 4(r1)
	JMP top

	end:
	mov 4(r1), r12
	add #1, r12
	add #6, r1
	pop r0
