	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "MISC.C"
	?debug	C E925A12E1D064D4953432E43
	?debug	C E94019CA1815433A5C42435C494E434C5544455C414C4C4F432E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F444546532E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F4E554C4C2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C535444494F2E48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5F4E46494C452E+
	?debug	C 48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5354444C49422E+
	?debug	C 48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C535452494E472E+
	?debug	C 48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C43545950452E48
	?debug	C E9E0952E1D06484541502E48
	?debug	C E912952E1D064D4953432E48
MISC_TEXT	segment byte public use16 'CODE'
MISC_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:MISC_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
MISC_TEXT	segment byte public use16 'CODE'
	?debug	C E801064D4953432E4325A12E1D
   ;	
   ;	void strupr(char *str)
   ;	
	?debug	L 26
	assume	cs:MISC_TEXT
_strupr	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	?debug	C E318000400160800
	?debug	C E603737472180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @1@86
	call	far ptr F_OVERFLOW@
@1@86:
   ;	
   ;	{
   ;	  int i;
   ;	
   ;	  for (i=0;i<strlen(str);i++)
   ;	
	?debug	L 30
	xor	si,si
	jmp	short @1@170
@1@114:
   ;	
   ;	   toupper(str[i]);
   ;	
	?debug	L 31
	les	bx,dword ptr [bp+6]
	add	bx,si
	mov	al,byte ptr es:[bx]
	mov	ah,0
	push	ax
	call	far ptr _toupper
	add	sp,2
	?debug	L 30
	inc	si
@1@170:
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _strlen
	add	sp,4
	cmp	si,ax
	jb	short @1@114
   ;	
   ;	}
   ;	
	?debug	L 32
	pop	si
	pop	bp
	ret	
	?debug	C E601690404060003737472180A060000
	?debug	E
	?debug	E
_strupr	endp
   ;	
   ;	int stricmp(char *s1, char *s2)
   ;	
	?debug	L 34
	assume	cs:MISC_TEXT
_stricmp	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,8
	?debug	C E6027332180A0A0000027331180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @2@86
	call	far ptr F_OVERFLOW@
@2@86:
   ;	
   ;	{
   ;	  char *szTemp1,*szTemp2;
   ;	
   ;	  szTemp1=my_alloc(strlen(s1));
   ;	
	?debug	L 38
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _strlen
	add	sp,4
	movzx	eax,ax
	push	eax
	call	far ptr _my_alloc
	add	sp,4
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
   ;	
   ;	  szTemp2=my_alloc(strlen(s2));
   ;	
	?debug	L 39
	push	word ptr [bp+12]
	push	word ptr [bp+10]
	call	far ptr _strlen
	add	sp,4
	movzx	eax,ax
	push	eax
	call	far ptr _my_alloc
	add	sp,4
	mov	word ptr [bp-6],dx
	mov	word ptr [bp-8],ax
   ;	
   ;	
   ;	  strcpy(szTemp1,s1);
   ;	
	?debug	L 41
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _strcpy
	add	sp,8
   ;	
   ;	  strupr(szTemp1);
   ;	
	?debug	L 42
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	cs
	call	near ptr _strupr
	add	sp,4
   ;	
   ;	  strcpy(szTemp2,s2);
   ;	
	?debug	L 43
	push	word ptr [bp+12]
	push	word ptr [bp+10]
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _strcpy
	add	sp,8
   ;	
   ;	  strupr(szTemp2);
   ;	
	?debug	L 44
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	push	cs
	call	near ptr _strupr
	add	sp,4
   ;	
   ;	
   ;	  return strcmp(szTemp1,szTemp2);
   ;	
	?debug	L 46
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _strcmp
	add	sp,8
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 47
	leave	
	ret	
	?debug	C E607737A54656D70321802F8FF0007737A54656D+
	?debug	C 70311802FCFF00027331180A060000027332180A+
	?debug	C 0A0000
	?debug	E
	?debug	E
_stricmp	endp
	?debug	C E9
	?debug	C FA00000000
MISC_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
MISC_TEXT	segment byte public use16 'CODE'
MISC_TEXT	ends
	extrn	F_OVERFLOW@:far
	extrn	__stklen:word
	public	_stricmp
	public	_strupr
	extrn	_my_alloc:far
	extrn	_toupper:far
	extrn	_strlen:far
	extrn	_strcpy:far
	extrn	_strcmp:far
_s@	equ	s@
	?debug	C EA010C
	?debug	C E31900000023040500
	?debug	C EB0B465F4F564552464C4F57401900
	?debug	C EB085F5F73746B6C656E0A00
	?debug	C E31A00000023040400
	?debug	C EC085F73747269636D701A1800
	?debug	C E31B00000023010400
	?debug	C EC075F7374727570721B1800
	?debug	C E31D000400160100
	?debug	C E31C000000231D0400
	?debug	C EB095F6D795F616C6C6F631C00
	?debug	C E31E00000023040400
	?debug	C EB085F746F75707065721E00
	?debug	C E31F000000230A0400
	?debug	C EB075F7374726C656E1F00
	?debug	C E32000000023180400
	?debug	C EB075F7374726370792000
	?debug	C E32100000023040400
	?debug	C EB075F737472636D702100
	?debug	C E60777636861725F740806000666706F735F7406+
	?debug	C 06000673697A655F740A06000970747264696666+
	?debug	C 5F74060600
	end
