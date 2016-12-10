; Assembly code macros.
; Put the INCLUDE directive for this file before the .data and .code sections
; of source files that need the macros.

include \masm32\include\masm32rt.inc
EXTERN putchar:NEAR
EXTERN getchar:NEAR

public start

put_ch   MACRO  thechar:REQ
     	push	EAX
     	push	EBX
     	push	ECX
     	push	EDX
     	push	thechar
     	call	putchar
	add 	ESP, 4
	pop	EDX
	pop	ECX
	pop	EBX
	pop	EAX
ENDM


put_i	MACRO	 FROM:req
     	push	EAX
    	push	EBX
     	push	ECX
     	push	EDX
	ifidn		<FROM>,<_SAW_M_REF_>
		pop		EAX
		invoke crt_printf, addr intFmt, dword ptr [EAX]
	else
		invoke crt_printf, addr intFmt, dword ptr FROM
	endif
	pop	EDX
	pop	ECX
	pop	EBX
	pop	EAX
ENDM
.data
intFmt db '%d', 0

put_str	MACRO	 FROM:req
     	push	EAX
    	push	EBX
     	push	ECX
     	push	EDX
	ifidn		<FROM>,<_SAW_M_REF_>
		pop		EAX
		invoke crt_printf, addr stringFmt, addr [EAX]
	else
		invoke crt_printf, addr stringFmt, addr FROM
	endif
	pop	EDX
	pop	ECX
	pop	EBX
	pop	EAX
ENDM
.data
stringFmt db '%s', 0

get_ch   MACRO
 	push	EBX
     	push	ECX
     	push	EDX
     	call   getchar ;; character in EAX
	pop	EDX
	pop	ECX
	pop	EBX
ENDM

get_i	MACRO	 TO:req
     	push	EAX
    	push	EBX
     	push	ECX
     	push	EDX
        lea EAX, TO
	invoke crt_scanf, addr intFmt, EAX
	pop	EDX
	pop	ECX
	pop	EBX
	pop	EAX
ENDM

get_str	MACRO	 TO:req
     	push	EAX
    	push	EBX
     	push	ECX
     	push	EDX
        lea EAX, TO
	invoke crt_scanf, addr stringFmt, EAX
	pop	EDX
	pop	ECX
	pop	EBX
	pop	EAX
ENDM


