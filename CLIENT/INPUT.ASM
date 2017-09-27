	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "INPUT.CPP"
	?debug	C E943A4AC1C09494E5055542E435050
	?debug	C E9CD89AC1C06444546532E48
	?debug	C E9489FAC1C07494E5055542E48
INPUT_TEXT	segment byte public use16 'CODE'
INPUT_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:INPUT_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_DATA	segment word public use16 'DATA'
_vects	label	dword
	db	0
	db	0
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_jmaxx	label	word
	db	2 dup (?)
_jminx	label	word
	db	2 dup (?)
_jmaxy	label	word
	db	2 dup (?)
_jminy	label	word
	db	2 dup (?)
_jcentx	label	word
	db	2 dup (?)
_jcenty	label	word
	db	2 dup (?)
_jrange	label	word
	db	2 dup (?)
_jactualx	label	word
	db	2 dup (?)
_jactualy	label	word
	db	2 dup (?)
_stick_x	label	word
	db	2 dup (?)
_stick_y	label	word
	db	2 dup (?)
_BSS	ends
INPUT_TEXT	segment byte public use16 'CODE'
	assume	cs:INPUT_TEXT
@stick_range$qi	proc	far
	push	bp
	mov	bp,sp
	mov	ax,word ptr [bp+6]
	inc	ax
	mov	word ptr DGROUP:_jrange,ax
	pop	bp
	ret	
@stick_range$qi	endp
	assume	cs:INPUT_TEXT
@stick_reset$qv	proc	far
	mov	ax,word ptr DGROUP:_jcentx
	add	ax,10
	mov	word ptr DGROUP:_jmaxx,ax
	mov	ax,word ptr DGROUP:_jcentx
	add	ax,-10
	mov	word ptr DGROUP:_jminx,ax
	mov	ax,word ptr DGROUP:_jcenty
	add	ax,10
	mov	word ptr DGROUP:_jmaxy,ax
	mov	ax,word ptr DGROUP:_jcenty
	add	ax,-10
	mov	word ptr DGROUP:_jminy,ax
	ret	
@stick_reset$qv	endp
	assume	cs:INPUT_TEXT
@stick_center$qv	proc	far
	mov	ax,word ptr DGROUP:_jactualx
	mov	word ptr DGROUP:_jcentx,ax
	mov	ax,word ptr DGROUP:_jactualy
	mov	word ptr DGROUP:_jcenty,ax
	ret	
@stick_center$qv	endp
	assume	cs:INPUT_TEXT
@stick_update$qv	proc	far
	mov	 bx,0
	mov	 dx,00201H
	out	 dx,al
@4@86:
	inc	 bx
	in	 al,dx
	test	 al,001H
	jne	short @4@86
	mov	 [DGROUP:_jactualx],bx
	cmp	 bx,[DGROUP:_jmaxx]
	jle	short @4@310
	mov	 [DGROUP:_jmaxx],bx
@4@310:
	cmp	 bx,[DGROUP:_jminx]
	jge	short @4@394
	mov	 [DGROUP:_jminx],bx
@4@394:
	mov	ax,word ptr DGROUP:_jactualx
	cmp	ax,word ptr DGROUP:_jcentx
	jge	short @4@450
	mov	ax,word ptr DGROUP:_jrange
	neg	ax
	mov	dx,word ptr DGROUP:_jcentx
	sub	dx,word ptr DGROUP:_jactualx
	imul	dx
	mov	bx,word ptr DGROUP:_jcentx
	sub	bx,word ptr DGROUP:_jminx
	inc	bx
	cwd	
	idiv	bx
	mov	word ptr DGROUP:_stick_x,ax
	jmp	short @4@478
@4@450:
	mov	dx,word ptr DGROUP:_jactualx
	sub	dx,word ptr DGROUP:_jcentx
	mov	ax,word ptr DGROUP:_jrange
	imul	dx
	mov	bx,word ptr DGROUP:_jmaxx
	sub	bx,word ptr DGROUP:_jcentx
	inc	bx
	cwd	
	idiv	bx
	mov	word ptr DGROUP:_stick_x,ax
@4@478:
 	mov	 dx,00201H
@4@506:
	in	 al,dx
	test	 al,002H
	jne	short @4@506
	mov	 bx,0
	out	 dx,al
@4@646:
	inc	 bx
	in	 al,dx
	test	 al,002H
	jne	short @4@646
	mov	 [DGROUP:_jactualy],bx
	cmp	 bx,[DGROUP:_jmaxy]
	jle	short @4@870
	mov	 [DGROUP:_jmaxy],bx
@4@870:
	cmp	 bx,[DGROUP:_jminy]
	jge	short @4@954
	mov	 [DGROUP:_jminy],bx
@4@954:
	mov	ax,word ptr DGROUP:_jactualy
	cmp	ax,word ptr DGROUP:_jcenty
	jge	short @4@1010
	mov	ax,word ptr DGROUP:_jrange
	neg	ax
	mov	dx,word ptr DGROUP:_jcenty
	sub	dx,word ptr DGROUP:_jactualy
	imul	dx
	mov	bx,word ptr DGROUP:_jcenty
	sub	bx,word ptr DGROUP:_jminy
	inc	bx
	cwd	
	idiv	bx
	mov	word ptr DGROUP:_stick_y,ax
	ret	
@4@1010:
	mov	dx,word ptr DGROUP:_jactualy
	sub	dx,word ptr DGROUP:_jcenty
	mov	ax,word ptr DGROUP:_jrange
	imul	dx
	mov	bx,word ptr DGROUP:_jmaxy
	sub	bx,word ptr DGROUP:_jcenty
	inc	bx
	cwd	
	idiv	bx
	mov	word ptr DGROUP:_stick_y,ax
	ret	
@stick_update$qv	endp
INPUT_TEXT	ends
_DATA	segment word public use16 'DATA'
_ispressed	label	byte
	db	0
	db	127 dup (0)
_DATA	ends
INPUT_TEXT	segment byte public use16 'CODE'
	assume	cs:INPUT_TEXT
@mykey$qve	proc	far
	push	ax
	push	bx
	push	cx
	push	dx
	push	es
	push	ds
	push	si
	push	di
	push	bp
	mov	bp,DGROUP
	mov	ds,bp
	mov	bp,sp
	sub	sp,2
	in	 al,060H
	mov	 [[bp-1]],al
	movsx	 bx,al
	and	 bx,0007fH
	or	 al,al
	setns	 DGROUP:_ispressed[bx]
	in	 al,061H
	or	 al,080H
	out	 061H,al
	and	 al,07fH
	out	 061H,al
	mov	 al,020H
	out	 020H,al
	leave	
	pop	di
	pop	si
	pop	ds
	pop	es
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	iret	
@mykey$qve	endp
	assume	cs:INPUT_TEXT
@myclock$qve	proc	far
	push	ax
	push	bx
	push	cx
	push	dx
	push	es
	push	ds
	push	si
	push	di
	push	bp
	mov	bp,DGROUP
	mov	ds,bp
	mov	 al,060H
	out	 020H,al
	pop	bp
	pop	di
	pop	si
	pop	ds
	pop	es
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	iret	
@myclock$qve	endp
INPUT_TEXT	ends
_BSS	segment word public use16 'BSS'
_oldkey	label	dword
	db	4 dup (?)
_oldclock	label	dword
	db	4 dup (?)
_BSS	ends
INPUT_TEXT	segment byte public use16 'CODE'
	assume	cs:INPUT_TEXT
@kbd_init$qv	proc	far
	les	bx,dword ptr DGROUP:_vects
	mov	eax,dword ptr es:[bx+36]
	mov	dword ptr DGROUP:_oldkey,eax
 	cli	
	les	bx,dword ptr DGROUP:_vects
	mov	word ptr es:[bx+38],seg @mykey$qve
	mov	word ptr es:[bx+36],offset @mykey$qve
 	sti	
	ret	
@kbd_init$qv	endp
	assume	cs:INPUT_TEXT
@kbd_done$qv	proc	far
 	cli	
	les	bx,dword ptr DGROUP:_vects
	mov	eax,dword ptr DGROUP:_oldkey
	mov	dword ptr es:[bx+36],eax
 	sti	
	ret	
@kbd_done$qv	endp
	?debug	C E9
	?debug	C FA00000000
INPUT_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
INPUT_TEXT	segment byte public use16 'CODE'
INPUT_TEXT	ends
	public	_oldclock
	public	_oldkey
	public	@myclock$qve
	public	@mykey$qve
	public	_jactualy
	public	_jactualx
	public	_jrange
	public	_jcenty
	public	_jcentx
	public	_jminy
	public	_jmaxy
	public	_jminx
	public	_jmaxx
	public	@stick_update$qv
	public	@stick_center$qv
	public	@stick_reset$qv
	public	@stick_range$qi
	public	@kbd_done$qv
	public	@kbd_init$qv
	public	_stick_y
	public	_stick_x
	public	_ispressed
	public	_vects
_s@	equ	s@
	end
