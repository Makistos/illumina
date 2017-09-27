	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "LINKLIST.C"
	?debug	C E98A952E1D0A4C494E4B4C4953542E43
	?debug	C E94019CA1815433A5C42435C494E434C5544455C414C4C4F432E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F444546532E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F4E554C4C2E48
	?debug	C E94019CA1813433A5C42435C494E434C5544455C4D454D2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C535444494F2E48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5F4E46494C452E+
	?debug	C 48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5354444C49422E+
	?debug	C 48
	?debug	C E957B71A1D09535444444546532E48
	?debug	C E9E0952E1D06484541502E48
	?debug	C E96D932E1D0A4C494E4B4C4953542E48
LINKLIST_TEXT	segment byte public use16 'CODE'
LINKLIST_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:LINKLIST_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
LINKLIST_TEXT	segment byte public use16 'CODE'
	?debug	C E8010A4C494E4B4C4953542E438A952E1D
   ;	
   ;	tLinkedList ll_init()
   ;	
	?debug	L 100
	assume	cs:LINKLIST_TEXT
_ll_init	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @1@86
	call	far ptr F_OVERFLOW@
@1@86:
   ;	
   ;	{
   ;	   tLinkedList list;
   ;	
   ;	   if ((list = (tLinkedList) my_alloc( sizeof(tCell) ))==NULL) {
   ;	
	?debug	L 104
	push	large 10
	call	far ptr _my_alloc
	add	sp,4
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
	or	ax,dx
	jne	short @1@142
   ;	
   ;	      printf("Out of memory in ll_init()\n");
   ;	
	?debug	L 105
	push	ds
	push	offset DGROUP:s@
	call	far ptr _printf
	add	sp,4
   ;	
   ;	      exit(1);
   ;	
	?debug	L 106
	push	1
	call	far ptr _exit
	add	sp,2
@1@142:
   ;	
   ;	   }
   ;	   list->element = NULL;
   ;	
	?debug	L 108
	les	bx,dword ptr [bp-4]
	mov	dword ptr es:[bx],large 0
   ;	
   ;	   list->nElementSize = 0;
   ;	
	?debug	L 109
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+4],0
   ;	
   ;	   list->next = NULL;
   ;	
	?debug	L 110
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+8],0
	mov	word ptr es:[bx+6],0
   ;	
   ;	   return list;
   ;	
	?debug	L 111
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 112
	leave	
	ret	
	?debug	C E3190F744C696E6B65644C69737443656C6C0A00+
	?debug	C 1E01
	?debug	C E31A000400160100
	?debug	C E318000400161900
	?debug	C E6046C6973741802FCFF00
	?debug	E
	?debug	E
_ll_init	endp
   ;	
   ;	int ll_empty( tLinkedList list )
   ;	
	?debug	L 151
	assume	cs:LINKLIST_TEXT
_ll_empty	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E6046C697374180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @2@86
	call	far ptr F_OVERFLOW@
@2@86:
   ;	
   ;	{
   ;	   if (list == NULL) return TRUE;
   ;	
	?debug	L 153
	cmp	dword ptr [bp+6],large 0
	jne	short @2@142
	mov	ax,1
	pop	bp
	ret	
@2@142:
   ;	
   ;	   if (list->next == NULL)
   ;	
	?debug	L 154
	les	bx,dword ptr [bp+6]
	mov	ax,word ptr es:[bx+6]
	or	ax,word ptr es:[bx+8]
	jne	short @2@226
   ;	
   ;	      return TRUE;
   ;	
	?debug	L 155
	mov	ax,1
	pop	bp
	ret	
	jmp	short @2@254
@2@226:
   ;	
   ;	   else
   ;	      return FALSE;
   ;	
	?debug	L 157
	xor	ax,ax
	pop	bp
	ret	
@2@254:
   ;	
   ;	}
   ;	
	?debug	L 158
	pop	bp
	ret	
	?debug	C E6046C697374180A060000
	?debug	E
	?debug	E
_ll_empty	endp
   ;	
   ;	tPosition ll_first( tLinkedList list )
   ;	
	?debug	L 197
	assume	cs:LINKLIST_TEXT
_ll_first	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E6046C697374180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @3@86
	call	far ptr F_OVERFLOW@
@3@86:
   ;	
   ;	{
   ;	   return ((tPosition) list);
   ;	
	?debug	L 199
	mov	dx,word ptr [bp+8]
	mov	ax,word ptr [bp+6]
	pop	bp
	ret	
   ;	
   ;	}
   ;	
	?debug	L 200
	pop	bp
	ret	
	?debug	C E6046C697374180A060000
	?debug	E
	?debug	E
_ll_first	endp
   ;	
   ;	tPosition ll_last( tLinkedList list )
   ;	
	?debug	L 241
	assume	cs:LINKLIST_TEXT
_ll_last	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	?debug	C E6046C697374180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @4@86
	call	far ptr F_OVERFLOW@
@4@86:
   ;	
   ;	{
   ;	   tPosition p;
   ;	
   ;	   p = (tPosition) list;
   ;	
	?debug	L 245
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-4],eax
	jmp	short @4@142
@4@114:
   ;	
   ;	   while (p->next != NULL)
   ;	      p = p->next;
   ;	
	?debug	L 247
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
@4@142:
	?debug	L 246
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+6]
	or	ax,word ptr es:[bx+8]
	jne	short @4@114
   ;	
   ;	   return p;
   ;	
	?debug	L 248
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 249
	leave	
	ret	
	?debug	C E601701802FCFF00046C697374180A060000
	?debug	E
	?debug	E
_ll_last	endp
   ;	
   ;	tPosition ll_next( tPosition position )
   ;	
	?debug	L 288
	assume	cs:LINKLIST_TEXT
_ll_next	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E608706F736974696F6E180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @5@86
	call	far ptr F_OVERFLOW@
@5@86:
   ;	
   ;	{
   ;	   return(position->next);
   ;	
	?debug	L 290
	les	bx,dword ptr [bp+6]
	mov	dx,word ptr es:[bx+8]
	mov	ax,word ptr es:[bx+6]
	pop	bp
	ret	
   ;	
   ;	}
   ;	
	?debug	L 291
	pop	bp
	ret	
	?debug	C E608706F736974696F6E180A060000
	?debug	E
	?debug	E
_ll_next	endp
   ;	
   ;	tPosition ll_previous( tPosition    position,
   ;	
	?debug	L 333
	assume	cs:LINKLIST_TEXT
_ll_previous	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	?debug	C E6046C697374180A0A000008706F736974696F6E+
	?debug	C 180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @6@86
	call	far ptr F_OVERFLOW@
@6@86:
   ;	
   ;				   tLinkedList list )
   ;	{
   ;	   tPosition p;
   ;	
   ;	   if (position==list) return(position);
   ;	
	?debug	L 338
	mov	eax,dword ptr [bp+6]
	cmp	eax,dword ptr [bp+10]
	jne	short @6@142
	mov	dx,word ptr [bp+8]
	mov	ax,word ptr [bp+6]
	leave	
	ret	
@6@142:
   ;	
   ;	   p = list;
   ;	
	?debug	L 339
	mov	eax,dword ptr [bp+10]
	mov	dword ptr [bp-4],eax
	jmp	short @6@198
@6@170:
   ;	
   ;	   while (p->next != position)
   ;	      p = p->next;
   ;	
	?debug	L 341
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
@6@198:
	?debug	L 340
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	cmp	ax,word ptr [bp+8]
	jne	short @6@170
	cmp	dx,word ptr [bp+6]
	jne	short @6@170
   ;	
   ;	   return(p);
   ;	
	?debug	L 342
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 343
	leave	
	ret	
	?debug	C E601701802FCFF0008706F736974696F6E180A06+
	?debug	C 0000046C697374180A0A0000
	?debug	E
	?debug	E
_ll_previous	endp
   ;	
   ;	int ll_end( tPosition position )
   ;	
	?debug	L 384
	assume	cs:LINKLIST_TEXT
_ll_end	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E608706F736974696F6E180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @7@86
	call	far ptr F_OVERFLOW@
@7@86:
   ;	
   ;	{
   ;	   if (position == NULL)
   ;	
	?debug	L 386
	cmp	dword ptr [bp+6],large 0
	jne	short @7@170
   ;	
   ;	      return(TRUE);
   ;	
	?debug	L 387
	mov	ax,1
	pop	bp
	ret	
	jmp	short @7@282
@7@170:
   ;	
   ;	   else {
   ;	      if (position->next == NULL)
   ;	
	?debug	L 389
	les	bx,dword ptr [bp+6]
	mov	ax,word ptr es:[bx+6]
	or	ax,word ptr es:[bx+8]
	jne	short @7@254
   ;	
   ;		 return(TRUE);
   ;	
	?debug	L 390
	mov	ax,1
	pop	bp
	ret	
	jmp	short @7@282
@7@254:
   ;	
   ;	      else
   ;		 return(FALSE);
   ;	
	?debug	L 392
	xor	ax,ax
	pop	bp
	ret	
@7@282:
   ;	
   ;	   }
   ;	}
   ;	
	?debug	L 394
	pop	bp
	ret	
	?debug	C E608706F736974696F6E180A060000
	?debug	E
	?debug	E
_ll_end	endp
   ;	
   ;	void ll_element( tPosition position,
   ;	
	?debug	L 434
	assume	cs:LINKLIST_TEXT
_ll_element	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E607656C656D656E741A0A0A000008706F736974+
	?debug	C 696F6E180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @8@86
	call	far ptr F_OVERFLOW@
@8@86:
   ;	
   ;			 void         *element )
   ;	{
   ;	   movmem(position->next->element,element,position->next->nElementSize);
   ;	
	?debug	L 437
	les	bx,dword ptr [bp+6]
	les	bx,dword ptr es:[bx+6]
	push	word ptr es:[bx+4]
	push	word ptr [bp+12]
	push	word ptr [bp+10]
	les	bx,dword ptr [bp+6]
	les	bx,dword ptr es:[bx+6]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	call	far ptr _movmem
	add	sp,10
   ;	
   ;	}
   ;	
	?debug	L 438
	pop	bp
	ret	
	?debug	C E608706F736974696F6E180A06000007656C656D+
	?debug	C 656E741A0A0A0000
	?debug	E
	?debug	E
_ll_element	endp
   ;	
   ;	void ll_insert( void      *element,
   ;	
	?debug	L 478
	assume	cs:LINKLIST_TEXT
_ll_insert	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	?debug	C E608706F736974696F6E180A0C00000473697A65+
	?debug	C 0A0A0A000007656C656D656E741A0A060000
	mov	si,word ptr [bp+10]
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @9@86
	call	far ptr F_OVERFLOW@
@9@86:
   ;	
   ;			            unsigned  size,
   ;			            tPosition position )
   ;	{
   ;	   tPosition temp;
   ;	
   ;	   if ((temp = (tPosition) my_alloc( sizeof(tCell) )) == NULL) {
   ;	
	?debug	L 484
	push	large 10
	call	far ptr _my_alloc
	add	sp,4
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
	or	ax,dx
	jne	short @9@142
   ;	
   ;	      printf("out of memory\n");
   ;	
	?debug	L 485
	push	ds
	push	offset DGROUP:s@+28
	call	far ptr _printf
	add	sp,4
   ;	
   ;	      abort();
   ;	
	?debug	L 486
	call	far ptr _abort
@9@142:
   ;	
   ;	   }
   ;	   temp->next = position->next;
   ;	
	?debug	L 488
	les	bx,dword ptr [bp+12]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+8],ax
	mov	word ptr es:[bx+6],dx
   ;	
   ;	   position->next = temp;
   ;	
	?debug	L 489
	les	bx,dword ptr [bp+12]
	mov	ax,word ptr [bp-2]
	mov	dx,word ptr [bp-4]
	mov	word ptr es:[bx+8],ax
	mov	word ptr es:[bx+6],dx
   ;	
   ;	   temp->nElementSize = size;
   ;	
	?debug	L 490
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+4],si
   ;	
   ;	   if ((temp->element = my_alloc( size ))==NULL) {
   ;	
	?debug	L 491
	movzx	eax,si
	push	eax
	call	far ptr _my_alloc
	add	sp,4
	les	bx,dword ptr [bp-4]
	mov	word ptr es:[bx+2],dx
	mov	word ptr es:[bx],ax
	or	ax,dx
	jne	short @9@198
   ;	
   ;	      printf("out of memory\n");
   ;	
	?debug	L 492
	push	ds
	push	offset DGROUP:s@+43
	call	far ptr _printf
	add	sp,4
   ;	
   ;	      abort();
   ;	
	?debug	L 493
	call	far ptr _abort
@9@198:
   ;	
   ;	   }
   ;	   movmem(element,temp->element,size);
   ;	
	?debug	L 495
	push	si
	les	bx,dword ptr [bp-4]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _movmem
	add	sp,10
   ;	
   ;	
   ;	}
   ;	
	?debug	L 497
	pop	si
	leave	
	ret	
	?debug	C E60474656D701802FCFF0007656C656D656E741A+
	?debug	C 0A0600000473697A650A0C060008706F73697469+
	?debug	C 6F6E180A0C0000
	?debug	E
	?debug	E
_ll_insert	endp
   ;	
   ;	void ll_delete( tPosition position )
   ;	
	?debug	L 535
	assume	cs:LINKLIST_TEXT
_ll_delete	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	?debug	C E608706F736974696F6E180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @10@86
	call	far ptr F_OVERFLOW@
@10@86:
   ;	
   ;	{
   ;	   tPosition    p;
   ;	
   ;	   if (position != NULL) {  /* Cut the element out of the chain */
   ;	
	?debug	L 539
	cmp	dword ptr [bp+6],large 0
	je	short @10@142
   ;	
   ;	      p = position->next;
   ;	
	?debug	L 540
	les	bx,dword ptr [bp+6]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
   ;	
   ;	      position->next = p->next;
   ;	
	?debug	L 541
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	les	bx,dword ptr [bp+6]
	mov	word ptr es:[bx+8],ax
	mov	word ptr es:[bx+6],dx
   ;	
   ;	      my_free( p->element );
   ;	
	?debug	L 542
	les	bx,dword ptr [bp-4]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	call	far ptr _my_free
	add	sp,4
   ;	
   ;	      my_free( p );
   ;	
	?debug	L 543
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _my_free
	add	sp,4
@10@142:
   ;	
   ;	   }
   ;	}
   ;	
	?debug	L 545
	leave	
	ret	
	?debug	C E601701802FCFF0008706F736974696F6E180A06+
	?debug	C 0000
	?debug	E
	?debug	E
_ll_delete	endp
   ;	
   ;	void ll_reset( tLinkedList list )
   ;	
	?debug	L 586
	assume	cs:LINKLIST_TEXT
_ll_reset	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E6046C697374180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @11@86
	call	far ptr F_OVERFLOW@
@11@86:
	jmp	short @11@142
@11@114:
   ;	
   ;	{
   ;	   while (! ll_empty(list))
   ;	      ll_delete(ll_first(list));
   ;	
	?debug	L 589
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	cs
	call	near ptr _ll_first
	add	sp,4
	push	dx
	push	ax
	push	cs
	call	near ptr _ll_delete
	add	sp,4
@11@142:
	?debug	L 588
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	cs
	call	near ptr _ll_empty
	add	sp,4
	or	ax,ax
	je	short @11@114
   ;	
   ;	   my_free(list);
   ;	
	?debug	L 590
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _my_free
	add	sp,4
   ;	
   ;	   list = NULL;
   ;	
	?debug	L 591
	mov	dword ptr [bp+6],large 0
   ;	
   ;	}
   ;	
	?debug	L 592
	pop	bp
	ret	
	?debug	C E6046C697374180A060000
	?debug	E
	?debug	E
_ll_reset	endp
   ;	
   ;	tPosition ll_locate( void             *element,
   ;	
	?debug	L 632
	assume	cs:LINKLIST_TEXT
_ll_locate	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,4
	?debug	C E6046C697374180A0A000007656C656D656E741A+
	?debug	C 0A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @12@86
	call	far ptr F_OVERFLOW@
@12@86:
   ;	
   ;				 tLinkedList list )
   ;	{
   ;	   tPosition p;
   ;	
   ;	   p = list;
   ;	
	?debug	L 637
	mov	eax,dword ptr [bp+10]
	mov	dword ptr [bp-4],eax
	jmp	short @12@226
@12@114:
   ;	
   ;	   while (p->next != NULL) {
   ;	      if ( memcmp(p->next->element,element,p->next->nElementSize) == 0 )
   ;	
	?debug	L 639
	les	bx,dword ptr [bp-4]
	les	bx,dword ptr es:[bx+6]
	push	word ptr es:[bx+4]
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	les	bx,dword ptr [bp-4]
	les	bx,dword ptr es:[bx+6]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	call	far ptr _memcmp
	add	sp,10
	or	ax,ax
	jne	short @12@198
   ;	
   ;		 return p;
   ;	
	?debug	L 640
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	leave	
	ret	
	jmp	short @12@226
@12@198:
   ;	
   ;	      else
   ;		 p = p->next;
   ;	
	?debug	L 642
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+8]
	mov	dx,word ptr es:[bx+6]
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
@12@226:
	?debug	L 638
	les	bx,dword ptr [bp-4]
	mov	ax,word ptr es:[bx+6]
	or	ax,word ptr es:[bx+8]
	jne	short @12@114
   ;	
   ;	   }
   ;	   return NULL;
   ;	
	?debug	L 644
	xor	dx,dx
	xor	ax,ax
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 645
	leave	
	ret	
	?debug	C E601701802FCFF0007656C656D656E741A0A0600+
	?debug	C 00046C697374180A0A0000
	?debug	E
	?debug	E
_ll_locate	endp
   ;	
   ;	void ll_replace( void          *element,
   ;	
	?debug	L 688
	assume	cs:LINKLIST_TEXT
_ll_replace	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	C E608706F736974696F6E180A0A000007656C656D+
	?debug	C 656E741A0A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @13@86
	call	far ptr F_OVERFLOW@
@13@86:
   ;	
   ;			 tPosition position )
   ;	{
   ;	   movmem(element,position->next->element,position->next->nElementSize);
   ;	
	?debug	L 691
	les	bx,dword ptr [bp+10]
	les	bx,dword ptr es:[bx+6]
	push	word ptr es:[bx+4]
	les	bx,dword ptr [bp+10]
	les	bx,dword ptr es:[bx+6]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _movmem
	add	sp,10
   ;	
   ;	}
   ;	
	?debug	L 692
	pop	bp
	ret	
	?debug	C E607656C656D656E741A0A06000008706F736974+
	?debug	C 696F6E180A0A0000
	?debug	E
	?debug	E
_ll_replace	endp
	?debug	C E9
	?debug	C FA00000000
LINKLIST_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	'Out of memory in ll_init()'
	db	10
	db	0
	db	'out of memory'
	db	10
	db	0
	db	'out of memory'
	db	10
	db	0
_DATA	ends
LINKLIST_TEXT	segment byte public use16 'CODE'
LINKLIST_TEXT	ends
	extrn	F_OVERFLOW@:far
	extrn	__stklen:word
	public	_ll_replace
	public	_ll_locate
	public	_ll_reset
	public	_ll_delete
	public	_ll_insert
	public	_ll_element
	public	_ll_end
	public	_ll_previous
	public	_ll_next
	public	_ll_last
	public	_ll_first
	public	_ll_empty
	public	_ll_init
	extrn	_my_alloc:far
	extrn	_my_free:far
	extrn	_exit:far
	extrn	_abort:far
	extrn	_printf:far
	extrn	_movmem:far
	extrn	_memcmp:far
_s@	equ	s@
	?debug	C EA010C
	?debug	C E31B00000023040500
	?debug	C EB0B465F4F564552464C4F57401B00
	?debug	C EB085F5F73746B6C656E0A00
	?debug	C E31C00000023010400
	?debug	C EC0B5F6C6C5F7265706C6163651C1800
	?debug	C E31D00000023180400
	?debug	C EC0A5F6C6C5F6C6F636174651D1800
	?debug	C E31E00000023010400
	?debug	C EC095F6C6C5F72657365741E1800
	?debug	C E31F00000023010400
	?debug	C EC0A5F6C6C5F64656C6574651F1800
	?debug	C E32000000023010400
	?debug	C EC0A5F6C6C5F696E73657274201800
	?debug	C E32100000023010400
	?debug	C EC0B5F6C6C5F656C656D656E74211800
	?debug	C E32200000023040400
	?debug	C EC075F6C6C5F656E64221800
	?debug	C E32300000023180400
	?debug	C EC0C5F6C6C5F70726576696F7573231800
	?debug	C E32400000023180400
	?debug	C EC085F6C6C5F6E657874241800
	?debug	C E32500000023180400
	?debug	C EC085F6C6C5F6C617374251800
	?debug	C E32600000023180400
	?debug	C EC095F6C6C5F6669727374261800
	?debug	C E32700000023040400
	?debug	C EC095F6C6C5F656D707479271800
	?debug	C E32800000023180400
	?debug	C EC085F6C6C5F696E6974281800
	?debug	C E329000000231A0400
	?debug	C EB095F6D795F616C6C6F632900
	?debug	C E32A00000023010400
	?debug	C EB085F6D795F667265652A00
	?debug	C E32B00000023010400
	?debug	C EB055F657869742B00
	?debug	C E32C00000023010400
	?debug	C EB065F61626F72742C00
	?debug	C E32D00000023040401
	?debug	C EB075F7072696E74662D00
	?debug	C E32E00000023010400
	?debug	C EB075F6D6F766D656D2E00
	?debug	C E32F00000023040400
	?debug	C EB075F6D656D636D702F00
	?debug	C E60974506F736974696F6E1806000B744C696E6B+
	?debug	C 65644C697374180600057443656C6C1906000777+
	?debug	C 636861725F740806000666706F735F7406060006+
	?debug	C 73697A655F740A060009707472646966665F7406+
	?debug	C 06000F744C696E6B65644C69737443656C6C1907+
	?debug	C 00
	?debug	C E20007656C656D656E741A000C6E456C656D656E+
	?debug	C 7453697A650A00046E65787418C00A000000
	end
