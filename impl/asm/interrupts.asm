;
; interrups.asm
;
; Created on: Apr 18, 2010
;      Author: anizzomc
;

GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL int_08_hand
GLOBAL _lidt
GLOBAL haltcpu

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler


EXTERN irqDispatcher
EXTERN int_08

%macro irqHandlerMaster 1
	push ds
	push es
	pusha

	mov eax, %1
	push eax
	call irqDispatcher
	pop eax
	
	
	;signal pic
	mov al, 20h
	out 20h, al

	popa
	pop es
	pop ds
	iret
%endmacro



SECTION .text

_cli:
	cli
	ret


_sti:
	sti
	ret


picMasterMask:
	push ebp
    mov ebp, esp
    mov ax, [ss:ebp+8]
    out	21h,al
    pop ebp
    retn

picSlaveMask:
	push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     ebp
    retn

_lidt:				; Carga el IDTR
    push    ebp
    mov     ebp, esp
    push    ebx
    mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR
	rol	ebx,16
	lidt    [ds: ebx]          ; carga IDTR
    pop     ebx
    pop     ebp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0
	
;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3
	
;Serial Port 1 and 3	
_irq04Handler:
	irqHandlerMaster 4
	
;USB
_irq05Handler:
	irqHandlerMaster 5


int_08_hand:				; Handler de INT 8 ( Timer tick)
    push    ds
    push    es                      ; Se salvan los registros
    pusha                           ; Carga de DS y ES con el valor del selector
    mov     ax, 10h			; a utilizar.
    mov     ds, ax
    mov     es, ax
    call    int_08
    mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa
    pop     es
    pop     ds
    iret

haltcpu:
	cli
	hlt
	ret

