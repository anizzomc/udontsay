;
; cpuid.asm
;
;  Created on: Apr 19, 2010
;      Author: anizzomc


GLOBAL cpuidTest
GLOBAL _cpuidString
GLOBAL cpuidWordEDX
GLOBAL cpuidExtended
GLOBAL _cpuidLongMode

cpuidWordEDX:
	push ebp
	mov ebp, esp

	push edx

	mov eax, 01h
	cpuid

	mov eax, edx

	pop edx

	mov esp, ebp
	pop ebp

	ret


cpuidExtended:
	push ebp
	mov ebp, esp

	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb NoExentededMode
	mov eax, 1h
	jmp ExitExtended
NoExentededMode:
	mov eax, 0
ExitExtended:
	mov esp, ebp
	pop ebp
	ret


_cpuidLongMode:
	push ebp
	mov ebp, esp

	push edx

	mov eax, 0x80000001    ; Set the A-register to 0x80000001.
    cpuid                  ; CPU identification.
    test edx, 1 << 29      ; Test if the LM-bit, which is the bit 29, is set in the D-register.
    jz NoLongMode
    mov eax, 1h
    jmp ExitLongMode
NoLongMode:
	mov eax, 0
ExitLongMode:
    pop edx
   	mov esp, ebp
   	pop ebp
   	ret

; returns 1 if CPUID is supported, 0 otherwise (ZF is also set accordingly)
cpuidTest:
	push ebp
	mov ebp, esp

	pushfd ; get the full flags register
	pop eax ;
	mov ecx, eax ; save
	xor eax, 0x200000 ; flip
	push eax ; set
	popfd
	pushfd ; and test
	pop eax
	xor eax, ecx ; mask changed bits
	shr eax, 21 ; move bit 21 to bit 0
	and eax, 1 ; and mask others

	mov esp, ebp
	pop ebp
	ret

; returns the array of the machine vendor:
; array[0] = ECX
; array[1] = EDX
; array[2] = EBX
_cpuidString:
	push ebp
	mov ebp, esp

	push ebx
	push ecx
	push edx

	push edi

	mov eax, 0
	cpuid


	mov edi, [ebp+8] ; argumento

	mov [edi], ebx		; arg[0]
	mov [edi + 4], edx 	; arg[1]
	mov [edi + 8], ecx	; arg[2]

	pop edi

	pop edx
	pop ecx
	pop ebx

	mov ebp, esp
	pop ebp
	ret
