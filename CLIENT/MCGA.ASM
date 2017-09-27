	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "MCGA.CPP"
	?debug	C E936A3AD1C084D4347412E435050
	?debug	C E94019CA181B433A5C424F524C414E44435C494E434C5544455C53+
	?debug	C 5444494F2E48
	?debug	C E94019CA181B433A5C424F524C414E44435C494E434C5544455C5F+
	?debug	C 444546532E48
	?debug	C E94019CA181C433A5C424F524C414E44435C494E434C5544455C5F+
	?debug	C 4E46494C452E48
	?debug	C E94019CA181B433A5C424F524C414E44435C494E434C5544455C5F+
	?debug	C 4E554C4C2E48
	?debug	C E94019CA1819433A5C424F524C414E44435C494E434C5544455C44+
	?debug	C 4F532E48
	?debug	C E9CD89AC1C06444546532E48
	?debug	C E9E198AD1C064D4347412E48
MCGA_TEXT	segment byte public use16 'CODE'
MCGA_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:MCGA_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_clearlength	label	word
	db	2 dup (?)
_screenseg	label	word
	db	2 dup (?)
_screenofs	label	word
	db	2 dup (?)
_drawareastart	label	word
	db	2 dup (?)
_screenxlimit	label	word
	db	2 dup (?)
_screenylimit	label	word
	db	2 dup (?)
_BSS	ends
MCGA_TEXT	segment byte public use16 'CODE'
	assume	cs:MCGA_TEXT
@initmcga$qv	proc	far
	push	di
	mov	 ax,00013H
	int	 010H
	push	 040H
	pop	 es
	mov	 di,049H
	mov	 al,es:[di]
	cmp	 al,013H
	je	short @1@310
	mov	 al,000H
	pop	di
	ret	
@1@310:
	mov	 dx,003d4H
	mov	 al,011H
	out	 dx,al
	inc	 dx
	in	 al,dx
	and	 al,07fH
	out	 dx,al
	dec	 dx
	mov	 ax,04109H
	out	 dx,ax
	mov	 ax,00014H
	out	 dx,ax
	mov	 ax,0e317H
	out	 dx,ax
	mov	 dx,003c4H
	mov	 ax,00604H
	out	 dx,ax
	mov	 ax,0a000H
	mov	 [DGROUP:_screenseg],ax
	mov	 ax,00000H
	mov	 [DGROUP:_screenofs],ax
	mov	 al,001H
	pop	di
	ret	
@initmcga$qv	endp
	assume	cs:MCGA_TEXT
@closemcga$qv	proc	far
	mov	 ax,00003H
	int	 010H
	ret	
@closemcga$qv	endp
	assume	cs:MCGA_TEXT
@setclearlength$qui	proc	far
	push	bp
	mov	bp,sp
	mov	 ax,[[bp+6]]
	mov	 [DGROUP:_clearlength],ax
	pop	bp
	ret	
@setclearlength$qui	endp
	assume	cs:MCGA_TEXT
@setdrawarea$qiiii	proc	far
	push	bp
	mov	bp,sp
	mov	 ax,[[bp+8]]
	shl	 ax,2
	add	 ax,[[bp+8]]
	shl	 ax,4
	add	 ax,[[bp+6]]
	mov	 [DGROUP:_drawareastart],ax
	mov	 ax,[[bp+10]]
	mov	 [DGROUP:_screenxlimit],ax
	mov	 ax,[[bp+12]]
	mov	 [DGROUP:_screenylimit],ax
	pop	bp
	ret	
@setdrawarea$qiiii	endp
	assume	cs:MCGA_TEXT
@loadlatches$quc	proc	far
	push	bp
	mov	bp,sp
	push	di
	push	 [DGROUP:_screenseg]
	pop	 es
	mov	 di,0ffffH
	mov	 dx,003c4H
	mov	 ax,00f02H
	out	 dx,ax
	mov	 dx,003ceH
	mov	 ax,0ff08H
	out	 dx,ax
	mov	 al,[[bp+6]]
	mov	 es:[di],al
	mov	 al,es:[di]
	mov	 ax,00008H
	out	 dx,ax
	pop	di
	pop	bp
	ret	
@loadlatches$quc	endp
	assume	cs:MCGA_TEXT
@restorenormalmode$qv	proc	far
	mov	 dx,003ceH
	mov	 ax,0ff08H
	out	 dx,ax
	ret	
@restorenormalmode$qv	endp
	assume	cs:MCGA_TEXT
@clearscreen$qv	proc	far
	push	di
	mov	 dx,003c4H
	mov	 ax,00f02H
	out	 dx,ax
	mov	 cx,[DGROUP:_clearlength]
	mov	 ax,[DGROUP:_screenseg]
	mov	 es,ax
	mov	 di,[DGROUP:_screenofs]
	mov	 ax,00000H
	cld	
	rep stosw	
	pop	di
	ret	
@clearscreen$qv	endp
	assume	cs:MCGA_TEXT
@putpixel$qiiuc	proc	far
	push	bp
	mov	bp,sp
	push	di
	mov	 ax,[DGROUP:_screenseg]
	mov	 es,ax
	mov	 dx,003c4H
	mov	 cx,[[bp+6]]
	shl	 cx,6
	shr	 cl,6
	mov	 ax,00102H
	shl	 ah,cl
	out	 dx,ax
	mov	 di,[[bp+8]]
	shl	 di,2
	add	 di,[[bp+8]]
	shl	 di,4
	shr	 cx,8
	add	 di,cx
	add	 di,[DGROUP:_screenofs]
	mov	 al,[[bp+10]]
	mov	 es:[di],al
	pop	di
	pop	bp
	ret	
@putpixel$qiiuc	endp
	assume	cs:MCGA_TEXT
@putpixel$qii	proc	far
	push	bp
	mov	bp,sp
	push	di
	mov	 ax,[DGROUP:_screenseg]
	mov	 es,ax
	mov	 dx,003c4H
	mov	 cx,[[bp+6]]
	shl	 cx,6
	shr	 cl,6
	mov	 ax,00102H
	shl	 ah,cl
	out	 dx,ax
	mov	 di,[[bp+8]]
	shl	 di,2
	add	 di,[[bp+8]]
	shl	 di,4
	shr	 cx,8
	add	 di,cx
	add	 di,[DGROUP:_screenofs]
	mov	 es:[di],al
	pop	di
	pop	bp
	ret	
@putpixel$qii	endp
	assume	cs:MCGA_TEXT
@clippedpixel$qiiuc	proc	far
	push	bp
	mov	bp,sp
	push	di
	mov	 ax,[DGROUP:_screenseg]
	mov	 es,ax
	mov	 dx,003c4H
	mov	 cx,[[bp+6]]
	cmp	 cx,[DGROUP:_screenxlimit]
	jg	short @10@702
	shl	 cx,6
	shr	 cl,6
	mov	 ax,00102H
	shl	 ah,cl
	out	 dx,ax
	mov	 ax,[[bp+8]]
	cmp	 ax,[DGROUP:_screenylimit]
	jg	short @10@702
	mov	 di,ax
	shl	 di,2
	add	 di,ax
	shl	 di,4
	shr	 cx,8
	add	 di,cx
	add	 di,[DGROUP:_screenofs]
	add	 di,[DGROUP:_drawareastart]
	mov	 al,[[bp+10]]
	mov	 es:[di],al
@10@702:
	pop	di
	pop	bp
	ret	
@clippedpixel$qiiuc	endp
	assume	cs:MCGA_TEXT
@drawline$qiiii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,10
	push	si
	push	di
	mov	 ax,[[bp+10]]
	sub	 ax,[[bp+6]]
	mov	 [[bp-2]],ax
	cwd	
	xor	 ax,dx
	shr	 dx,1
	adc	 ax,0
	mov	 [[bp-8]],ax
	mov	 ax,[[bp+12]]
	sub	 ax,[[bp+8]]
	mov	 [[bp-4]],ax
	cwd	
	xor	 ax,dx
	shr	 dx,1
	adc	 ax,0
	mov	 [[bp-10]],ax
	cmp	 ax,[[bp-8]]
	jg	short @11@1094
	neg	 ax
	mov	 di,ax
	shl	 edi,16
	mov	 ax,[[bp-2]]
	cwd	
	neg	 ax
	shl	 ax,1
	adc	 dx,0
	mov	 di,dx
	mov	 si,[[bp-8]]
	mov	 [[bp-6]],si
	shl	 esi,16
	mov	 ax,[[bp-4]]
	cwd	
	neg	 ax
	shl	 ax,1
	adc	 dx,0
	mov	 si,dx
	imul	 si,320
	jmp	short @11@1626
@11@1094:
	mov	 si,ax
	mov	 di,[[bp-8]]
	neg	 di
	shl	 edi,16
	mov	 ax,[[bp-4]]
	cwd	
	neg	 ax
	shl	 ax,1
	adc	 dx,0
	mov	 di,dx
	imul	 di,320
	mov	 [[bp-6]],si
	shl	 esi,16
	mov	 ax,[[bp-2]]
	cwd	
	neg	 ax
	shl	 ax,1
	adc	 dx,0
	mov	 si,dx
@11@1626:
	mov	 ax,[DGROUP:_screenseg]
	mov	 es,ax
	mov	 ax,[[bp+8]]
	movzx	 ecx,ax
	shl	 cx,2
	add	 cx,ax
	shl	 cx,6
	add	 cx,[[bp+6]]
	add	 cx,[DGROUP:_screenofs]
	add	 cx,[DGROUP:_drawareastart]
	mov	 dx,003c4H
	mov	 al,002H
	out	 dx,al
	inc	 dx
	mov	 ax,[[bp-6]]
	inc	 ax
@11@2074:
	dec	 ax
	je	short @11@2578
@11@2130:
	mov	 bl,cl
	and	 cl,dh
	mov	 bh,al
	mov	 al,001H
	shl	 al,cl
	out	 dx,al
	mov	 al,bh
	mov	 bh,ch
	mov	 cl,bl
	shr	 bx,2
	mov	 es:[bx],al
	add	 ecx,edi
	jns	short @11@2074
	add	 ecx,esi
	dec	 ax
	jne	short @11@2130
@11@2578:
	pop	di
	pop	si
	leave	
	ret	
@drawline$qiiii	endp
	assume	cs:MCGA_TEXT
@clippedline$qiiii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,18
	push	si
	push	di
	xor	ax,ax
	mov	word ptr [bp-8],ax
	mov	word ptr [bp-6],ax
	mov	ax,word ptr [bp+8]
	cmp	ax,word ptr DGROUP:_screenylimit
	jle	short @12@86
	or	word ptr [bp-6],1
	jmp	short @12@142
@12@86:
	cmp	word ptr [bp+8],0
	jge	short @12@142
	or	word ptr [bp-6],2
@12@142:
	mov	ax,word ptr [bp+6]
	cmp	ax,word ptr DGROUP:_screenxlimit
	jle	short @12@198
	or	word ptr [bp-6],4
	jmp	short @12@254
@12@198:
	cmp	word ptr [bp+6],0
	jge	short @12@254
	or	word ptr [bp-6],8
@12@254:
	mov	ax,word ptr [bp+12]
	cmp	ax,word ptr DGROUP:_screenylimit
	jle	short @12@310
	or	word ptr [bp-8],1
	jmp	short @12@366
@12@310:
	cmp	word ptr [bp+12],0
	jge	short @12@366
	or	word ptr [bp-8],2
@12@366:
	mov	ax,word ptr [bp+10]
	cmp	ax,word ptr DGROUP:_screenxlimit
	jle	short @12@422
	or	word ptr [bp-8],4
	jmp	short @12@478
@12@422:
	cmp	word ptr [bp+10],0
	jge	short @12@478
	or	word ptr [bp-8],8
@12@478:
	mov	ax,word ptr [bp-8]
	test	word ptr [bp-6],ax
	je short	@@4
	jmp	@12@1318
@@4:
	mov	ax,word ptr [bp-6]
	or	ax,word ptr [bp-8]
	jne	short @12@562
	push	word ptr [bp+12]
	push	word ptr [bp+10]
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	cs
	call	near ptr @drawline$qiiii
	add	sp,8
	pop	di
	pop	si
	leave	
	ret	
@12@562:
	mov	ax,word ptr [bp+10]
	sub	ax,word ptr [bp+6]
	mov	word ptr [bp-2],ax
	mov	ax,word ptr [bp+12]
	sub	ax,word ptr [bp+8]
	mov	word ptr [bp-4],ax
	movsx	eax,word ptr [bp-2]
	mov	dword ptr [bp-14],eax
	movsx	eax,word ptr [bp-4]
	mov	dword ptr [bp-18],eax
@12@618:
	cmp	word ptr [bp-6],0
	jne	short @12@674
	mov	si,word ptr [bp+6]
	mov	ax,word ptr [bp+10]
	mov	word ptr [bp+6],ax
	mov	word ptr [bp+10],si
	mov	di,word ptr [bp+8]
	mov	ax,word ptr [bp+12]
	mov	word ptr [bp+8],ax
	mov	word ptr [bp+12],di
	mov	ax,word ptr [bp-6]
	mov	word ptr [bp-10],ax
	mov	ax,word ptr [bp-8]
	mov	word ptr [bp-6],ax
	mov	ax,word ptr [bp-10]
	mov	word ptr [bp-8],ax
@12@674:
	test	word ptr [bp-6],1
	je	short @12@814
	mov	eax,dword ptr [bp-14]
	mov	dx,word ptr DGROUP:_screenylimit
	sub	dx,word ptr [bp+8]
	movsx	edx,dx
	imul	eax,edx
	cdq	
	idiv	dword ptr [bp-18]
	mov	dx,word ptr [bp+6]
	add	dx,ax
	mov	word ptr [bp+6],dx
	mov	ax,word ptr DGROUP:_screenylimit
	mov	word ptr [bp+8],ax
	mov	word ptr [bp-6],0
	mov	ax,word ptr [bp+6]
	cmp	ax,word ptr DGROUP:_screenxlimit
	jle	short @12@758
	or	word ptr [bp-6],4
	jmp	@12@1234
@12@758:
	cmp	word ptr [bp+6],0
	jl short	@@5
	jmp	@12@1234
@@5:
	or	word ptr [bp-6],8
	jmp	@12@1234
@12@814:
	test	word ptr [bp-6],2
	je	short @12@954
	mov	eax,dword ptr [bp-14]
	mov	dx,word ptr [bp+8]
	neg	dx
	movsx	edx,dx
	imul	eax,edx
	cdq	
	idiv	dword ptr [bp-18]
	mov	dx,word ptr [bp+6]
	add	dx,ax
	mov	word ptr [bp+6],dx
	xor	ax,ax
	mov	word ptr [bp-6],ax
	mov	word ptr [bp+8],ax
	mov	ax,word ptr [bp+6]
	cmp	ax,word ptr DGROUP:_screenxlimit
	jle	short @12@898
	or	word ptr [bp-6],4
	jmp	@12@1234
@12@898:
	cmp	word ptr [bp+6],0
	jl short	@@6
	jmp	@12@1234
@@6:
	or	word ptr [bp-6],8
	jmp	@12@1234
@12@954:
	test	word ptr [bp-6],4
	je	short @12@1094
	mov	eax,dword ptr [bp-18]
	mov	dx,word ptr DGROUP:_screenxlimit
	sub	dx,word ptr [bp+6]
	movsx	edx,dx
	imul	eax,edx
	cdq	
	idiv	dword ptr [bp-14]
	mov	dx,word ptr [bp+8]
	add	dx,ax
	mov	word ptr [bp+8],dx
	mov	ax,word ptr DGROUP:_screenxlimit
	mov	word ptr [bp+6],ax
	mov	word ptr [bp-6],0
	mov	ax,word ptr [bp+8]
	cmp	ax,word ptr DGROUP:_screenylimit
	jle	short @12@1038
	or	word ptr [bp-6],1
	jmp	short @12@1234
@12@1038:
	cmp	word ptr [bp+8],0
	jge	short @12@1234
	or	word ptr [bp-6],2
	jmp	short @12@1234
@12@1094:
	test	word ptr [bp-6],8
	je	short @12@1234
	mov	eax,dword ptr [bp-18]
	mov	dx,word ptr [bp+6]
	neg	dx
	movsx	edx,dx
	imul	eax,edx
	cdq	
	idiv	dword ptr [bp-14]
	mov	dx,word ptr [bp+8]
	add	dx,ax
	mov	word ptr [bp+8],dx
	xor	ax,ax
	mov	word ptr [bp-6],ax
	mov	word ptr [bp+6],ax
	mov	ax,word ptr [bp+8]
	cmp	ax,word ptr DGROUP:_screenylimit
	jle	short @12@1178
	or	word ptr [bp-6],1
	jmp	short @12@1234
@12@1178:
	cmp	word ptr [bp+8],0
	jge	short @12@1234
	or	word ptr [bp-6],2
@12@1234:
	mov	ax,word ptr [bp-8]
	test	word ptr [bp-6],ax
	jne	short @12@1318
	mov	ax,word ptr [bp-6]
	or	ax,word ptr [bp-8]
	je short	@@7
	jmp	@12@618
@@7:
	push	word ptr [bp+12]
	push	word ptr [bp+10]
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	cs
	call	near ptr @drawline$qiiii
	add	sp,8
@12@1318:
	pop	di
	pop	si
	leave	
	ret	
@clippedline$qiiii	endp
	assume	cs:MCGA_TEXT
@setdrawmode$quc	proc	far
	push	bp
	mov	bp,sp
	mov	 dx,003ceH
	mov	 al,005H
	out	 dx,al
	inc	 dx
	in	 al,dx
	and	 al,0f0H
	or	 al,[[bp+6]]
	out	 dx,al
	pop	bp
	ret	
@setdrawmode$quc	endp
	assume	cs:MCGA_TEXT
@setbitmask$quc	proc	far
	push	bp
	mov	bp,sp
	mov	 dx,003ceH
	mov	 al,008H
	mov	 ah,[[bp+6]]
	out	 dx,ax
	pop	bp
	ret	
@setbitmask$quc	endp
	assume	cs:MCGA_TEXT
@setplanes$quc	proc	far
	push	bp
	mov	bp,sp
	mov	 dx,003c4H
	mov	 al,002H
	mov	 ah,[bp+6]
	out	 dx,ax
	pop	bp
	ret	
@setplanes$quc	endp
	assume	cs:MCGA_TEXT
@reset03c0$qv	proc	far
	mov	 dx,003daH
	in	 al,dx
	ret	
@reset03c0$qv	endp
	assume	cs:MCGA_TEXT
@set03c0$qucuc	proc	far
	push	bp
	mov	bp,sp
	mov	 dx,003c0H
	mov	 al,[[bp+6]]
	or	 al,020H
	out	 dx,al
	mov	 al,[[bp+8]]
	out	 dx,al
	pop	bp
	ret	
@set03c0$qucuc	endp
	assume	cs:MCGA_TEXT
@selectcolor$quc	proc	far
	push	bp
	mov	bp,sp
	mov	 dx,003c8H
	mov	 al,[[bp+6]]
	out	 dx,al
	pop	bp
	ret	
@selectcolor$quc	endp
	assume	cs:MCGA_TEXT
@setcolorvalues$qucucuc	proc	far
	push	bp
	mov	bp,sp
	mov	 dx,003c9H
	mov	 al,[[bp+6]]
	out	 dx,al
	mov	 al,[[bp+8]]
	out	 dx,al
	mov	 al,[[bp+10]]
	out	 dx,al
	pop	bp
	ret	
@setcolorvalues$qucucuc	endp
MCGA_TEXT	ends
_BSS	segment word public use16 'BSS'
	db	23360 dup (?)
_BSS	ends
MCGA_TEXT	segment byte public use16 'CODE'
	assume	cs:MCGA_TEXT
@loadgrf$qnxuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	mov	dword ptr [bp-4],large 0A00027B0h
	push	ds
	push	offset DGROUP:s@
	push	dword ptr [bp+6]
	call	far ptr _fopen
	add	sp,8
	mov	word ptr [bp-10],dx
	mov	word ptr [bp-12],ax
	push	dx
	push	ax
	push	large 000020002h
	push	ds
	push	offset DGROUP:b@w+12
	call	far ptr _fread
	add	sp,12
	push	dword ptr [bp-12]
	push	large 000490140h
	push	ds
	push	offset DGROUP:b@w+12
	call	far ptr _fread
	add	sp,12
 	mov	 dx,03c8H
 	mov	 al,0
 	out	 dx,al
	mov	word ptr [bp-6],0
@20@170:
	push	dword ptr [bp-12]
	push	large 000010001h
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	call	far ptr _fread
	add	sp,12
 	mov	 dx,003c9H
 	mov	 ax,[[bp-8]]
 	out	 dx,al
	inc	word ptr [bp-6]
	cmp	word ptr [bp-6],768
	jl	short @20@170
	push	dword ptr [bp-12]
	call	far ptr _fclose
	add	sp,4
	mov	word ptr [bp-6],0
@20@366:
	mov	al,1
	mov	cl,byte ptr [bp-6]
	shl	al,cl
	push	ax
	push	cs
	call	near ptr @setplanes$quc
	add	sp,2
	mov	word ptr [bp-8],0
@20@394:
	mov	bx,word ptr [bp-8]
	shl	bx,2
	add	bx,word ptr [bp-6]
	mov	al,byte ptr DGROUP:b@w+12[bx]
	les	bx,dword ptr [bp-4]
	add	bx,word ptr [bp-8]
	mov	byte ptr es:[bx],al
	inc	word ptr [bp-8]
	cmp	word ptr [bp-8],5840
	jl	short @20@394
	inc	word ptr [bp-6]
	cmp	word ptr [bp-6],4
	jl	short @20@366
	mov	ax,1
	leave	
	ret	
@loadgrf$qnxuc	endp
	?debug	C E9
	?debug	C FA09000000
MCGA_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	'rb'
	db	0
_DATA	ends
MCGA_TEXT	segment byte public use16 'CODE'
MCGA_TEXT	ends
	public	@loadgrf$qnxuc
	public	@setcolorvalues$qucucuc
	public	@selectcolor$quc
	public	@set03c0$qucuc
	public	@reset03c0$qv
	public	@setplanes$quc
	public	@setbitmask$quc
	public	@setdrawmode$quc
	public	@clippedline$qiiii
	public	@drawline$qiiii
	public	@clippedpixel$qiiuc
	public	@putpixel$qii
	public	@putpixel$qiiuc
	public	@clearscreen$qv
	public	@restorenormalmode$qv
	public	@loadlatches$quc
	public	@setdrawarea$qiiii
	public	@setclearlength$qui
	public	@closemcga$qv
	public	@initmcga$qv
	public	_screenylimit
	public	_screenxlimit
	public	_drawareastart
	public	_screenofs
	public	_screenseg
	public	_clearlength
_pokeb	equ	pokeb
_poke	equ	poke
_peekb	equ	peekb
_peek	equ	peek
	extrn	_fread:far
	extrn	_fopen:far
	extrn	_fclose:far
_s@	equ	s@
	end
