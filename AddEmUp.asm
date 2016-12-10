.486
include \masm32\include\pmacros.inc

.data
num1 dd ?
num2 dd ?
newline	dd	0ah
promptint	db	'Please input an integer: ',0
sumStr		db	'The sum is: ',0

.code
start:
   get_i num1
   get_i num2
   mov EAX, num1
   mov EBX, num2

	push	EDX			;return param
	push	EAX			;first number
	push	EBX			;second number
	call	add_em_up	;sum the two numbers
	pop		EBX			;pop the return param into EBX

	put_str	sumStr
	put_i EBX
	put_ch	0ah
	exit
	
;add_em_up procedure
;	add two values.  This is a dumb procedure, but shows usage of parameter passing/stack
;Return value:  sum of the integers
;Parameters:	two integer parameters, call-by-value
add_em_up:
	push	EBP
	mov	EBP, ESP
	push	EAX

	mov		EAX, [EBP+12]	;get the first parameter
	add		EAX, [EBP+8]	;add in the second parameter
	mov		[EBP+16], EAX	;store into return parameter

	pop		EAX
	mov		ESP, EBP
	pop		EBP
	ret		8
end start
