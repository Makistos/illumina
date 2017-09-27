	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "SHAPES.CPP"
	?debug	C E94183A21C0A5348415045532E435050
	?debug	C E9CD89AC1C06444546532E48
	?debug	C E98E81A11C085348415045532E48
SHAPES_TEXT	segment byte public use16 'CODE'
SHAPES_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:SHAPES_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
SHAPES_TEXT	segment byte public use16 'CODE'
	assume	cs:SHAPES_TEXT
@triangle$qiiiiii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,42
	push	si
	push	di
	mov	 word ptr [[bp-42]],2
	mov	 ax,[[bp+8]]
	mov	 bx,[[bp+12]]
	mov	 cx,[[bp+16]]
	cmp	 ax,bx
	jle	short @1@310
	xchg	 ax,bx
	mov	 dx,[[bp+6]]
	xchg	 [[bp+10]],dx
	mov	 [[bp+6]],dx
@1@310:
	cmp	 ax,cx
	jle	short @1@478
	xchg	 ax,cx
	mov	 dx,[[bp+6]]
	xchg	 dx,[[bp+14]]
	mov	 [[bp+6]],dx
@1@478:
	cmp	 bx,cx
	jle	short @1@646
	xchg	 bx,cx
	mov	 dx,[[bp+10]]
	xchg	 dx,[[bp+14]]
	mov	 [[bp+10]],dx
@1@646:
	cmp	 ax,[_screenylimit]
	jl	short @1@730
	pop	di
	pop	si
	leave	
	ret	
@1@730:
	or	 cx,cx
	jns	short @1@814
	pop	di
	pop	si
	leave	
	ret	
@1@814:
	cmp	 ax,bx
	jne	short @1@898
	inc	 bx
@1@898:
	mov	 [[bp+8]],ax
	mov	 [[bp+12]],bx
	mov	 [[bp+16]],cx
	dec	 ax
	mov	 [[bp-36]],cx
	sub	 [[bp-36]],ax
	sub	 cx,bx
	inc	 cx
	mov	 [[bp-40]],cx
	sub	 bx,ax
	mov	 [[bp-38]],bx
	mov	 ax,[[bp+6]]
	mov	 bx,[[bp+10]]
	mov	 cx,[[bp+14]]
	mov	 [[bp-30]],cx
	sub	 [[bp-30]],ax
	sub	 cx,bx
	mov	 [[bp-34]],cx
	sub	 bx,ax
	mov	 [[bp-32]],bx
	movsx	eax,word ptr [bp-30]
	shl	eax,16
	movsx	ebx,word ptr [bp-36]
	cdq	
	idiv	ebx
	mov	dword ptr [bp-10],eax
	mov	dword ptr [bp-20],eax
	movsx	eax,word ptr [bp-32]
	shl	eax,16
	movsx	ebx,word ptr [bp-38]
	cdq	
	idiv	ebx
	mov	dword ptr [bp-6],eax
	movsx	eax,word ptr [bp-34]
	shl	eax,16
	movsx	ebx,word ptr [bp-40]
	cdq	
	idiv	ebx
	mov	dword ptr [bp-16],eax
	cmp	word ptr [bp+8],0
	jle	short @1@1514
	movsx	eax,word ptr [bp+6]
	shl	eax,16
	mov	dword ptr [bp-24],eax
	mov	dword ptr [bp-28],eax
	jmp	@1@1626
@1@1514:
	movsx	eax,word ptr [bp-30]
	mov	dx,word ptr [bp+8]
	neg	dx
	movsx	edx,dx
	imul	eax,edx
	movsx	ebx,word ptr [bp-36]
	cdq	
	idiv	ebx
	movsx	edx,word ptr [bp+6]
	add	edx,eax
	shl	edx,16
	mov	dword ptr [bp-24],edx
	cmp	word ptr [bp+12],0
	jle	short @1@1570
	movsx	eax,word ptr [bp-32]
	mov	dx,word ptr [bp+8]
	neg	dx
	movsx	edx,dx
	imul	eax,edx
	movsx	ebx,word ptr [bp-38]
	cdq	
	idiv	ebx
	movsx	edx,word ptr [bp+6]
	add	edx,eax
	shl	edx,16
	mov	dword ptr [bp-28],edx
	jmp	short @1@1598
@1@1570:
	movsx	eax,word ptr [bp-34]
	mov	dx,word ptr [bp+12]
	neg	dx
	movsx	edx,dx
	imul	eax,edx
	movsx	ebx,word ptr [bp-40]
	cdq	
	idiv	ebx
	movsx	edx,word ptr [bp+10]
	add	edx,eax
	shl	edx,16
	mov	dword ptr [bp-28],edx
@1@1598:
	mov	word ptr [bp+8],0
@1@1626:
	mov	 ax,[[bp+12]]
	mov	 bx,[[bp+16]]
	mov	 cx,[_screenylimit]
	cwd	
	not	 dx
	and	 ax,dx
	sub	 ax,cx
	cwd	
	and	 ax,dx
	add	 ax,cx
	xchg	 ax,bx
	sub	 ax,cx
	cwd	
	and	 ax,dx
	add	 ax,cx
	inc	 ax
	sub	 ax,bx
	mov	 [[bp-20]+8],ax
	inc	 bx
	sub	 bx,[[bp+8]]
	mov	 [[bp-10]+8],bx
	mov	 eax,[[bp-10]+0]
	cmp	 eax,[[bp-10]+4]
	jle	short @1@2522
	xchg	 eax,[[bp-10]+4]
	mov	 [[bp-10]+0],eax
	mov	 eax,[[bp-20]+0]
	xchg	 eax,[[bp-20]+4]
	mov	 [[bp-20]+0],eax
	mov	 eax,[[bp-24]]
	xchg	 eax,[[bp-28]]
	mov	 [[bp-24]],eax
@1@2522:
	movzx	 eax,[_screenxlimit]
	shl	 eax,16
	sub	 [[bp-28]],eax
	mov	 dx,003c4H
	mov	 al,002H
	out	 dx,al
	inc	 dx
	mov	 ax,[_screenseg]
	mov	 es,ax
	mov	 si,[[bp+8]]
	shl	 si,2
	add	 si,[[bp+8]]
	shl	 si,4
	add	 si,[_screenofs]
	add	 si,[_drawareastart]
	cld	
@1@2970:
	dec	 [[bp-10]+8]
	je	short @1@4454
@1@3026:
	mov	 di,si
	add	 si,80
	mov	 eax,[[bp-10]+4]
	add	 [[bp-28]],eax
	mov	 cx,[[bp-28]]+002H
	mov	 eax,[[bp-10]+0]
	add	 [[bp-24]],eax
	mov	 bx,[[bp-24]]+002H
	mov	 ax,bx
	sar	 ax,15
	not	 ax
	and	 bx,ax
	mov	 ax,cx
	sar	 ax,15
	and	 cx,ax
	add	 cx,[_screenxlimit]
	cmp	 cx,bx
	jle	short @1@2970
	mov	 ax,0f10fH
	shl	 cx,6
	rol	 cl,2
	rol	 ah,cl
	mov	 cl,bl
	and	 cl,dh
	shl	 al,cl
	shr	 bx,2
	add	 di,bx
	sub	 ch,bl
	je	short @1@4314
	out	 dx,al
	mov	 al,00fH
	mov	 es:[di],al
	inc	 di
	dec	 ch
	je	short @1@4314
	out	 dx,al
	test	 di,1
	je	short @1@4174
	mov	 es:[di],al
	inc	 di
	dec	 ch
@1@4174:
	shr	 cx,9
	rep stosw	
	jnc	short @1@4314
	mov	 es:[di],al
	inc	 di
@1@4314:
	and	 al,ah
	out	 dx,al
	mov	 es:[di],al
	dec	 [[bp-10]+8]
	jne	short @1@3026
@1@4454:
	dec	 [[bp-42]]
	je	short @1@4706
	mov	 ax,[[bp-20]+8]
	mov	 [[bp-10]+8],ax
	mov	 eax,[[bp-20]+0]
	mov	 [[bp-10]+0],eax
	mov	 eax,[[bp-20]+4]
	mov	 [[bp-10]+4],eax
	jmp	@1@2970
@1@4706:
	pop	di
	pop	si
	leave	
	ret	
@triangle$qiiiiii	endp
	assume	cs:SHAPES_TEXT
@circle$qiii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,24
	push	si
	push	di
	mov	 ax,01111H
	mov	 cx,[[bp+6]]
	and	 cx,00003H
	rol	 ax,cl
	mov	 [[bp-24]+0],ah
	mov	 [[bp-24]+1],al
	mov	 ax,01111H
	mov	 cx,[[bp+6]]
	add	 cx,[[bp+10]]
	and	 cx,00003H
	rol	 al,cl
	mov	 [[bp-24]+2],al
	mov	 cx,[[bp+6]]
	sub	 cx,[[bp+10]]
	and	 cx,00003H
	rol	 ah,cl
	mov	 [[bp-24]+3],ah
	xor	 edi,edi
	mov	 di,[[bp+10]]
	mov	 [[bp-4]+0],di
	mov	 [[bp-4]+2],0
	mov	 eax,edi
	mul	 eax
	mov	 ebx,eax
	imul	 eax,4
	mov	 [[bp-16]],eax
	mov	 eax,ebx
	shl	 eax,1
	mov	 ecx,eax
	mul	 edi
	add	 eax,ecx
	sub	 ebx,eax
	mov	 [[bp-12]],ebx
	shl	 ecx,1
	mov	 [[bp-8]],ecx
	mov	 eax,ecx
	imul	 ecx,edi
	add	 ecx,eax
	mov	 [[bp-20]],ecx
	mov	 ax,[_screenseg]
	mov	 es,ax
	mov	 dx,003c4H
	mov	 al,002H
	out	 dx,al
	inc	 dx
	mov	 si,[[bp+8]]
	shl	 si,2
	add	 si,[[bp+8]]
	shl	 si,4
@2@1402:
	mov	 ebx,[[bp-4]]
	shl	 ebx,2
	add	 ebx,[[bp-4]]
	shl	 ebx,4
	mov	 di,si
	sub	 di,bx
	shl	 bx,1
	mov	 eax,[[bp-24]]
	mov	 cx,[[bp+6]]
	add	 cx,[[bp-4]+2]
	shr	 cx,2
	out	 dx,al
	add	 di,cx
	mov	 es:[di],al
	add	 di,bx
	mov	 es:[di],al
	sub	 di,cx
	mov	 cx,[[bp+6]]
	sub	 cx,[[bp-4]+2]
	shr	 cx,2
	mov	 al,ah
	out	 dx,al
	add	 di,cx
	mov	 es:[di],al
	sub	 di,bx
	mov	 es:[di],al
	shr	 eax,16
	shr	 ebx,16
	mov	 di,si
	sub	 di,bx
	shl	 bx,1
	mov	 cx,[[bp+6]]
	add	 cx,[[bp-4]+0]
	shr	 cx,2
	out	 dx,al
	add	 di,cx
	mov	 es:[di],al
	add	 di,bx
	mov	 es:[di],al
	sub	 di,cx
	mov	 cx,[[bp+6]]
	sub	 cx,[[bp-4]+0]
	shr	 cx,2
	mov	 al,ah
	out	 dx,al
	add	 di,cx
	mov	 es:[di],al
	sub	 di,bx
	mov	 es:[di],al
	ror	 byte ptr [[bp-24]+1],1
	rol	 byte ptr [[bp-24]+0],1
	inc	 word ptr [[bp-4]+2]
	mov	 ecx,[[bp-12]]
	mov	 eax,[[bp-8]]
	add	 [[bp-16]],eax
	add	 ecx,[[bp-16]]
	js	short @2@3138
	sub	 ecx,[[bp-20]]
	sub	 [[bp-20]],eax
	dec	 word ptr [[bp-4]+0]
	ror	 byte ptr [[bp-24]+2],1
	rol	 byte ptr [[bp-24]+3],1
@2@3138:
	mov	 [[bp-12]],ecx
	mov	 ax,[[bp-4]+2]
	cmp	 ax,[[bp-4]+0]
	jg	short @2@3278
	jmp	@2@1402
@2@3278:
	pop	di
	pop	si
	leave	
	ret	
@circle$qiii	endp
	assume	cs:SHAPES_TEXT
@filledcircle$qiii	proc	far
	push	bp
	mov	bp,sp
	pop	bp
	ret	
@filledcircle$qiii	endp
	?debug	C E9
	?debug	C FA00000000
SHAPES_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
SHAPES_TEXT	segment byte public use16 'CODE'
SHAPES_TEXT	ends
	public	@filledcircle$qiii
	public	@circle$qiii
	public	@triangle$qiiiiii
	extrn	_screenylimit:word
	extrn	_screenxlimit:word
	extrn	_drawareastart:word
	extrn	_screenofs:word
	extrn	_screenseg:word
_s@	equ	s@
	end
