GLOBAL _in
GLOBAL _out

_in:
	push ebp
	mov ebp, esp

	push dx
	
	xor eax, eax

	mov word dx, [ss:ebp+8]; puerto
	in al, dx

	pop dx

	mov esp, ebp
	pop ebp
	ret
_out:
	push ebp
	mov ebp, esp

	push dx
	push ax

	mov word ax, [ss:ebp+12] ; dato
	mov word dx, [ss:ebp+8]; puerto

	out dx, al

	pop ax
	pop dx


	mov esp, ebp
	pop ebp
	ret
