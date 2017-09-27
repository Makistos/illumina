	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "MAIN00.CPP"
	?debug	C E9B9A5AD1C0A4D41494E30302E435050
	?debug	C E94019CA181C433A5C424F524C414E44435C494E434C5544455C53+
	?debug	C 54444C49422E48
	?debug	C E94019CA181B433A5C424F524C414E44435C494E434C5544455C5F+
	?debug	C 444546532E48
	?debug	C E94019CA181B433A5C424F524C414E44435C494E434C5544455C5F+
	?debug	C 4E554C4C2E48
	?debug	C E94019CA181B433A5C424F524C414E44435C494E434C5544455C43+
	?debug	C 4F4E494F2E48
	?debug	C E94019CA1819433A5C424F524C414E44435C494E434C5544455C44+
	?debug	C 4F532E48
	?debug	C E9CD89AC1C06444546532E48
	?debug	C E9E198AD1C064D4347412E48
	?debug	C E98E81A11C085348415045532E48
	?debug	C E963639E1C0745515549502E48
	?debug	C E9489FAC1C07494E5055542E48
MAIN00_TEXT	segment byte public use16 'CODE'
MAIN00_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:MAIN00_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
MAIN00_TEXT	segment byte public use16 'CODE'
	assume	cs:MAIN00_TEXT
@clock_start$qn4time	proc	far
	push	bp
	mov	bp,sp
	push	dword ptr [bp+6]
	call	far ptr _gettime
	add	sp,4
	pop	bp
	ret	
@clock_start$qn4time	endp
	assume	cs:MAIN00_TEXT
@clock_stop$qn4time	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	push	ss
	lea	ax,word ptr [bp-4]
	push	ax
	call	far ptr _gettime
	add	sp,4
	les	bx,dword ptr [bp+6]
	movzx	eax,byte ptr es:[bx+1]
	mov	dword ptr [bp-8],eax
	imul	eax,large 60
	mov	dword ptr [bp-8],eax
	movzx	eax,byte ptr es:[bx]
	add	dword ptr [bp-8],eax
	mov	eax,dword ptr [bp-8]
	imul	eax,large 60
	mov	dword ptr [bp-8],eax
	movzx	eax,byte ptr es:[bx+3]
	add	dword ptr [bp-8],eax
	mov	eax,dword ptr [bp-8]
	imul	eax,large 100
	mov	dword ptr [bp-8],eax
	movzx	eax,byte ptr es:[bx+2]
	add	dword ptr [bp-8],eax
	movzx	eax,byte ptr [bp-3]
	mov	dword ptr [bp-12],eax
	imul	eax,large 60
	mov	dword ptr [bp-12],eax
	movzx	eax,byte ptr [bp-4]
	add	dword ptr [bp-12],eax
	mov	eax,dword ptr [bp-12]
	imul	eax,large 60
	mov	dword ptr [bp-12],eax
	movzx	eax,byte ptr [bp-1]
	add	dword ptr [bp-12],eax
	mov	eax,dword ptr [bp-12]
	imul	eax,large 100
	mov	dword ptr [bp-12],eax
	movzx	eax,byte ptr [bp-2]
	add	dword ptr [bp-12],eax
	mov	eax,dword ptr [bp-12]
	sub	eax,dword ptr [bp-8]
	shld	edx,eax,16
	leave	
	ret	
@clock_stop$qn4time	endp
MAIN00_TEXT	ends
_DATA	segment word public use16 'DATA'
_processors	label	byte
	db	56
	db	48
	db	56
	db	54
	db	6 dup (0)
	db	56
	db	48
	db	49
	db	56
	db	54
	db	5 dup (0)
	db	56
	db	48
	db	50
	db	56
	db	54
	db	5 dup (0)
	db	56
	db	48
	db	51
	db	56
	db	54
	db	83
	db	88
	db	3 dup (0)
	db	56
	db	48
	db	51
	db	56
	db	54
	db	68
	db	88
	db	3 dup (0)
	db	56
	db	48
	db	52
	db	56
	db	54
	db	5 dup (0)
_mousenames	label	byte
	db	78
	db	111
	db	110
	db	101
	db	11 dup (0)
	db	83
	db	101
	db	114
	db	105
	db	97
	db	108
	db	32
	db	109
	db	111
	db	117
	db	115
	db	101
	db	3 dup (0)
	db	73
	db	110
	db	80
	db	111
	db	114
	db	116
	db	32
	db	109
	db	111
	db	117
	db	115
	db	101
	db	3 dup (0)
	db	80
	db	83
	db	47
	db	50
	db	32
	db	109
	db	111
	db	117
	db	115
	db	101
	db	5 dup (0)
	db	72
	db	80
	db	32
	db	109
	db	111
	db	117
	db	115
	db	101
	db	7 dup (0)
	db	15 dup (0)
_DATA	ends
MAIN00_TEXT	segment byte public use16 'CODE'
	assume	cs:MAIN00_TEXT
_main	proc	far
	push	bp
	mov	bp,sp
	sub	sp,8
	call	far ptr @initmcga$qv
	mov	ah,0
	or	ax,ax
	jne	short @3@86
	push	ds
	push	offset DGROUP:s@
	call	far ptr _cprintf
	add	sp,4
	mov	ax,seg _exit
	mov	es,ax
@3@86:
	push	8000
	call	far ptr @setclearlength$qui
	add	sp,2
	push	large 000C7013Fh
	push	large 0
	call	far ptr @setdrawarea$qiiii
	add	sp,8
	call	far ptr @clearscreen$qv
	call	far ptr _getch
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	push	cs
	call	near ptr @clock_start$qn4time
	add	sp,4
	mov	dword ptr [bp-4],large 0
	jmp	short @3@170
@3@114:
	call	far ptr _rand
	movsx	eax,ax
	shl	eax,8
	mov	ebx,large 000008000h
	cdq	
	idiv	ebx
	push	ax
	call	far ptr @loadlatches$quc
	add	sp,2
	push	large 000C800A0h
	push	large 000640140h
	push	large 000640000h
	call	far ptr @triangle$qiiiiii
	add	sp,12
	inc	dword ptr [bp-4]
@3@170:
	cmp	dword ptr [bp-4],large 500
	jl	short @3@114
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	push	cs
	call	near ptr @clock_stop$qn4time
	shl	eax,16
	shrd	eax,edx,16
	add	sp,4
	mov	dword ptr [bp-4],eax
	call	far ptr @closemcga$qv
	push	dword ptr [bp-4]
	push	ds
	push	offset DGROUP:s@+40
	call	far ptr _cprintf
	add	sp,8
	call	far ptr _getch
	leave	
	ret	
_main	endp
	?debug	C E9
	?debug	C FA00000000
MAIN00_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	'Error: This program needs MCGA-display.'
	db	0
	db	'%ld'
	db	0
_DATA	ends
MAIN00_TEXT	segment byte public use16 'CODE'
MAIN00_TEXT	ends
	public	_main
	public	_mousenames
	public	_processors
	public	@clock_stop$qn4time
	public	@clock_start$qn4time
	extrn	@triangle$qiiiiii:far
	extrn	@clearscreen$qv:far
	extrn	@loadlatches$quc:far
	extrn	@setdrawarea$qiiii:far
	extrn	@setclearlength$qui:far
	extrn	@closemcga$qv:far
	extrn	@initmcga$qv:far
_pokeb	equ	pokeb
_poke	equ	poke
_peekb	equ	peekb
_peek	equ	peek
	extrn	_gettime:far
	extrn	_cprintf:far
	extrn	_getch:far
	extrn	_rand:far
	extrn	_exit:far
_atoi	equ	atoi
_abs	equ	abs
_s@	equ	s@
	end
