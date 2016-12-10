; Assembly code macros.
; Put the INCLUDE directive for this file before the .data and .code sections
; of source files that need the macros.

include \masm32\include\masm32rt.inc

public start

put_ch	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			invoke crt_printf, addr charFmt, byte ptr [EAX]
		else
			invoke crt_printf, addr charFmt, byte ptr FROM
		endif
ENDM
.data
charFmt db '%c', 0

put_i	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			invoke crt_printf, addr intFmt, dword ptr [EAX]
		else
			invoke crt_printf, addr intFmt, dword ptr FROM
		endif
ENDM
.data
intFmt db '%d', 0

put_str	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			invoke crt_printf, addr stringFmt, addr [EAX]
		else
			invoke crt_printf, addr stringFmt, addr FROM
		endif
ENDM
.data
stringFmt db '%s', 0


get_ch	MACRO	 TO:req
            	lea EAX, TO
		invoke crt_scanf, addr charFmt, EAX
ENDM

get_i	MACRO	 TO:req
            	lea EAX, TO
		invoke crt_scanf, addr intFmt, EAX
ENDM

get_str	MACRO	 TO:req
            	lea EAX, TO
		invoke crt_scanf, addr stringFmt, EAX
ENDM

iadd	MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
		else
			lea		EAX,TO
		endif

		add		[EAX],EBX		
ENDM

isub	MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
		else
			lea		EAX,TO
		endif

		sub		[EAX],EBX		
ENDM

ineg	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			neg		dword ptr [EAX]
		else
			neg		dword ptr FROM
		endif
ENDM

imult	MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
		else
			lea		EAX,TO
		endif

		mov		EDX, [EAX]
		imul	EDX, EBX
		mov		dword ptr [EAX], EDX		
ENDM

idivi	MACRO	TO:req, FROM:req
		LOCAL	positive, do_divide
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX, [EAX]
		else
			mov		EBX, FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		ECX
			mov		EAX, [ECX]
		else
			lea		ECX, TO
			mov		EAX, TO
		endif

		;; if EAX contains negative value, EDX<-ffffffffh
		;; if EAX contains positive value, EDX<-00000000h
		cmp		EAX, 0
		jge		positive
		mov		EDX, 0ffffffffh
		jmp		do_divide
positive:
		mov		EDX, 0
do_divide:
		idiv	EBX		;; idiv EAX, EBX in manual
		mov		dword ptr [ECX], EAX		
ENDM

irem	MACRO	TO:req, FROM:req
		LOCAL	positive, do_divide
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		ECX
			mov		EAX, [ECX]
		else
			lea		ECX, TO
			mov		EAX, TO
		endif

		;; if EAX contains negative value, EDX<-ffffffffh
		;; if EAX contains positive value, EDX<-00000000h
		cmp		EAX, 0
		jge		positive
		mov		EDX, 0ffffffffh
		jmp		do_divide
positive:
		mov		EDX, 00000000h
do_divide:
		idiv	EBX			;; idiv EAX, EBX in manual
		mov		dword ptr [ECX], EDX		
ENDM


lnot	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			not		dword ptr [EAX]
		else
			not		dword ptr FROM
		endif
ENDM


land	MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
		else
			lea		EAX,TO
		endif

		and		dword ptr [EAX],EBX		
ENDM

lor		MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
		else
			lea		EAX,TO
		endif

		or		dword ptr [EAX],EBX		
ENDM

lxor		MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX,[EAX]
		else
			mov		EBX,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
		else
			lea		EAX,TO
		endif

		xor		dword ptr [EAX],EBX		
ENDM

rash	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			sar		dword ptr [EAX], 1
		else
			sar		dword ptr FROM, 1
		endif
ENDM

rlsh	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			shr		dword ptr [EAX], 1
		else
			shr		dword ptr FROM, 1
		endif
ENDM

llsh	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			shl		dword ptr [EAX], 1
		else
			shl		dword ptr FROM, 1
		endif
ENDM

rrot	MACRO	 FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			ror		dword ptr [EAX], 1
		else
			ror		dword ptr FROM, 1
		endif
ENDM

compare		MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		EBX, [EAX]
		else
			mov		EBX, dword ptr FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
			mov		EAX, dword ptr [EAX]
		else
			mov		EAX, dword ptr TO
		endif

		cmp			EAX, EBX		
ENDM

compareb		MACRO	TO:req, FROM:req
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		EAX
			mov		BL, byte ptr [EAX]
		else
			mov		BL, byte ptr FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
			mov		AL, byte ptr [EAX]
		else
			mov		AL, byte ptr TO
		endif

		cmp			AL, BL		
ENDM

br		MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			jmp		EAX
		else
			jmp		TO
		endif
ENDM

bez		MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			je		EAX
		else
			je		TO
		endif
ENDM

blz		MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			js		EAX
		else
			js		TO
		endif
ENDM

blez	MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			jle		EAX
		else
			jle		TO
		endif
ENDM

bgz		MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			jg		EAX
		else
			jg		TO
		endif
ENDM

bgez	MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			jge		EAX
		else
			jge		TO
		endif
ENDM

bnz		MACRO	 TO:req
		ifidn		<TO>,<_SAW_M_REF_>
			echo error: illegal use of M() in br instruction
			pop		EAX		;; to undo M() macro push
			jne		EAX
		else
			jne		TO
		endif
ENDM


la		MACRO	TO:req, FROM:req
 		ifidn		<FROM>,<_SAW_M_REF_>
			echo error: illegal use of M() in la instruction
			pop		EAX		;; to undo M() macro push
			mov		EBX, EAX ;; to not further cause errors
		else
			lea		EBX,FROM
		endif
		ifidn		<TO>,<_SAW_M_REF_>
			pop		EAX
			mov		[EAX],EBX
		else
			mov		TO, EBX
		endif
ENDM
 
 move	MACRO	TO:req, FROM:req
		
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		eax
			mov		ebx,[eax]
		else
			mov		ebx,FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		eax
		else
			lea		eax,TO
		endif

		mov		[eax],ebx
ENDM

moveb	MACRO	TO:req, FROM:req
		
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		eax
			mov		bl,[eax]
		else
			mov		bl,byte ptr FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		eax
		else
			lea		eax,TO
		endif

		mov			[eax],bl
ENDM

movezx	MACRO	TO:req, FROM:req
		
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		eax
			movzx	ebx, byte ptr [eax]
		else
			movzx	ebx, byte ptr FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		eax
		else
			lea		eax,TO
		endif

		mov		[eax],ebx
ENDM

movesx	MACRO	TO:req, FROM:req
		
		ifidn		<FROM>,<_SAW_M_REF_>
			pop		eax
			movsx	ebx, byte ptr [eax]
		else
			movsx	ebx, byte ptr FROM
		endif

		ifidn		<TO>,<_SAW_M_REF_>
			pop		eax
		else
			lea		eax,TO
		endif

		mov		[eax],ebx
ENDM


;;
;;----M: load address contained in param and push it on stack.
;;
M		macro	ADDR:req
		mov		eax,ADDR
		push	eax
		exitm	<_SAW_M_REF_>
endm
