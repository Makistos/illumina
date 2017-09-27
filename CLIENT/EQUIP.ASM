	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "EQUIP.CPP"
	?debug	C E90B649E1C0945515549502E435050
	?debug	C E963639E1C0745515549502E48
EQUIP_TEXT	segment byte public use16 'CODE'
EQUIP_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:EQUIP_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_DATA	segment word public use16 'DATA'
_mousedetected	label	byte
	db	0
_mousetype	label	byte
	db	0
_mouseirqnumber	label	byte
	db	0
	db	1 dup (0)
_mousedriverversion	label	word
	db	0
	db	0
_DATA	ends
EQUIP_TEXT	segment byte public use16 'CODE'
	assume	cs:EQUIP_TEXT
@com1address$qv	proc	far
	push	di
	mov	 ax,040H
	mov	 es,ax
	mov	 di,000H
	mov	 ax,es:[di]
	pop	di
	ret	
@com1address$qv	endp
	assume	cs:EQUIP_TEXT
@com2address$qv	proc	far
	push	di
	mov	 ax,040H
	mov	 es,ax
	mov	 di,002H
	mov	 ax,es:[di]
	pop	di
	ret	
@com2address$qv	endp
	assume	cs:EQUIP_TEXT
@com3address$qv	proc	far
	push	di
	mov	 ax,040H
	mov	 es,ax
	mov	 di,004H
	mov	 ax,es:[di]
	pop	di
	ret	
@com3address$qv	endp
	assume	cs:EQUIP_TEXT
@com4address$qv	proc	far
	push	di
	mov	 ax,040H
	mov	 es,ax
	mov	 di,006H
	mov	 ax,es:[di]
	pop	di
	ret	
@com4address$qv	endp
	assume	cs:EQUIP_TEXT
@detectjoystick$qv	proc	far
	push	di
	mov	 ax,040H
	mov	 es,ax
	mov	 di,011H
	mov	 al,es:[di]
	and	 al,010H
	shr	 al,4
	pop	di
	ret	
@detectjoystick$qv	endp
	assume	cs:EQUIP_TEXT
@getmouseinformation$qv	proc	far
	push	di
	mov	 ax,00000H
	mov	 es,ax
	mov	 [DGROUP:_mousedetected],al
	mov	 di,033H*4
	mov	 ax,es:[di]
	mov	 bx,es:[di+002H]
	or	 ax,bx
	je	short @6@534
	mov	 ax,00000H
	int	 033H
	mov	 [DGROUP:_mousedetected],al
	or	 al,al
	je	short @6@534
	mov	 ax,00024H
	int	 033H
	mov	 [DGROUP:_mousedriverversion],bx
	mov	 [DGROUP:_mousetype],ch
	mov	 [DGROUP:_mouseirqnumber],cl
@6@534:
	pop	di
	ret	
@getmouseinformation$qv	endp
EQUIP_TEXT	ends
_DATA	segment word public use16 'DATA'
	db	0
	db	1
	db	2
	db	2
	db	4
	db	3
	db	2
	db	5
	db	6
	db	2
	db	8
	db	7
	db	8
_DATA	ends
EQUIP_TEXT	segment byte public use16 'CODE'
	assume	cs:EQUIP_TEXT
@detectcard$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,14
	push	si
	push	di
	mov	si,offset DGROUP:d@w+6
	lea	di,word ptr [bp-14]
	push	ss
	pop	es
	mov	cx,6
	rep 	movsw	
	movsb	
	mov	 ax,01a00H
	int	 010H
	cmp	 al,01aH
	jne	short @7@422
	cmp	 bl,00cH
	jg	short @7@366
	mov	 bh,000H
	add	 bx,offset [bp-14]
	mov	 ah,000H
	mov	 al,[bx]
	jmp	short @7@1066
@7@366:
	mov	 ax,2
	jmp	short @7@1066
@7@422:
	mov	 ah,012H
	mov	 bx,010H
	int	 010H
	cmp	 bx,010H
	je	short @7@814
	mov	 ah,012H
	mov	 bl,010H
	int	 010H
	or	 bh,bh
	je	short @7@758
	mov	 ax,3
	jmp	short @7@1066
@7@758:
	mov	 ax,4
	jmp	short @7@1066
@7@814:
	int	 011H
	and	 al,030H
	shr	 al,4
	mov	 ah,0
	or	 al,al
	je	short @7@1066
	cmp	 al,3
	jne	short @7@366
	mov	 ax,1
@7@1066:
	pop	di
	pop	si
	leave	
	ret	
@detectcard$qv	endp
	assume	cs:EQUIP_TEXT
@detectprocessor$qv	proc	far
	pushf	
	mov	 ax,00000H
	push	 ax
	popf	
	pushf	
	pop	 ax
	and	 ax,0f000H
	cmp	 ax,0f000H
	jne	short @8@506
	push	 cx
	mov	 ax,0ffffH
	mov	 cl,33
	shl	 ax,cl
	pop	 cx
	mov	 ax,1
	jne	short @8@1458
	mov	 ax,0
	jmp	short @8@1458
@8@506:
	mov	 ax,007000H
	push	 ax
	popf	
	pushf	
	pop	 ax
	and	 ax,07000H
	mov	 ax,2
	je	short @8@1458
	mov	 eax,cr0
	mov	 ebx,eax
	or	 al,010H
	mov	 cr0,eax
	mov	 eax,cr0
	mov	 cr0,ebx
	test	 al,010H
	mov	 ax,3
	je	short @8@1458
	mov	 ecx,esp
	pushfd	
	pop	 ebx
	and	 esp,not 3
	mov	 eax,ebx
	xor	 eax,040000H
	push	 eax
	popfd	
	pushfd	
	pop	 eax
	push	 ebx
	popfd	
	mov	 esp,ecx
	cmp	 eax,ebx
	mov	 ax,4
	je	short @8@1458
	mov	 ax,5
@8@1458:
 	popf	
	ret	
@detectprocessor$qv	endp
	?debug	C E9
	?debug	C FA00000000
EQUIP_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
EQUIP_TEXT	segment byte public use16 'CODE'
EQUIP_TEXT	ends
	public	@com4address$qv
	public	@com3address$qv
	public	@com2address$qv
	public	@com1address$qv
	public	@getmouseinformation$qv
	public	@detectjoystick$qv
	public	@detectprocessor$qv
	public	@detectcard$qv
	public	_mousedriverversion
	public	_mouseirqnumber
	public	_mousetype
	public	_mousedetected
_s@	equ	s@
	end
