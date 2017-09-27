	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "KEYBRD.C"
	?debug	C E9ED922E1D084B45594252442E43
	?debug	C E94019CA1815433A5C42435C494E434C5544455C434F4E494F2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F444546532E48
	?debug	C E957B71A1D09535444444546532E48
	?debug	C E94EBF2E1D084B45594252442E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C434F4E494F2E48
	?debug	C E9E0952E1D06484541502E48
KEYBRD_TEXT	segment byte public use16 'CODE'
KEYBRD_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:KEYBRD_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
KEYBRD_TEXT	segment byte public use16 'CODE'
	?debug	C E801084B45594252442E43ED922E1D
   ;	
   ;	void dummy()
   ;	
	?debug	L 17
	assume	cs:KEYBRD_TEXT
_dummy	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @1@86
	call	far ptr F_OVERFLOW@
@1@86:
   ;	
   ;	{}
   ;	
	?debug	L 18
	pop	bp
	ret	
	?debug	E
	?debug	E
_dummy	endp
	?debug	C E9
	?debug	C FA00000000
KEYBRD_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
KEYBRD_TEXT	segment byte public use16 'CODE'
KEYBRD_TEXT	ends
	extrn	F_OVERFLOW@:far
	extrn	__stklen:word
	public	_dummy
_s@	equ	s@
	?debug	C EA010C
	?debug	C E31800000023040500
	?debug	C EB0B465F4F564552464C4F57401800
	?debug	C EB085F5F73746B6C656E0A00
	?debug	C E31900000023010400
	?debug	C EC065F64756D6D79191800
	end
