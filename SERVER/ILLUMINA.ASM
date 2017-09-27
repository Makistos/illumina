	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "ILLUMINA.C"
	?debug	C E960BF2E1D0A494C4C554D494E412E43
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5354444C49422E+
	?debug	C 48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F444546532E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F4E554C4C2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C434F4E494F2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C535444494F2E48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5F4E46494C452E+
	?debug	C 48
	?debug	C E957B71A1D09535444444546532E48
	?debug	C E96D932E1D0A4C494E4B4C4953542E48
	?debug	C E9DAA02E1D094F424A454354532E48
	?debug	C E96D932E1D0A4C494E4B4C4953542E48
	?debug	C E94EBF2E1D084B45594252442E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C434F4E494F2E48
	?debug	C E9C89E251D07494E4F55542E48
	?debug	C E912952E1D064D4953432E48
	?debug	C E999962E1D06494E49542E48
	?debug	C E9E0952E1D06484541502E48
ILLUMINA_TEXT	segment byte public use16 'CODE'
ILLUMINA_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:ILLUMINA_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_DATA	segment word public use16 'DATA'
__stklen	label	word
	db	0
	db	125
_DATA	ends
ILLUMINA_TEXT	segment byte public use16 'CODE'
	?debug	C E8010A494C4C554D494E412E4360BF2E1D
   ;	
   ;	void mainMenu()
   ;	
	?debug	L 38
	assume	cs:ILLUMINA_TEXT
_mainMenu	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	B
	cmp	word ptr DGROUP:__stklen,sp
	ja	short @1@86
	call	far ptr F_OVERFLOW@
@1@86:
   ;	
   ;	{
   ;	  clrscr();
   ;	
	?debug	L 40
	call	far ptr _clrscr
   ;	
   ;	  printf("*** ILLUMINATI ***\n\n");
   ;	
	?debug	L 41
	push	ds
	push	offset DGROUP:s@
	call	far ptr _printf
	add	sp,4
   ;	
   ;	  printf("Edit (P)layers\n");
   ;	
	?debug	L 42
	push	ds
	push	offset DGROUP:s@+21
	call	far ptr _printf
	add	sp,4
   ;	
   ;	  printf("Edit (W)orld\n");
   ;	
	?debug	L 43
	push	ds
	push	offset DGROUP:s@+37
	call	far ptr _printf
	add	sp,4
   ;	
   ;	  printf("ESC - QUIT GAME\n");
   ;	
	?debug	L 44
	push	ds
	push	offset DGROUP:s@+51
	call	far ptr _printf
	add	sp,4
   ;	
   ;	}
   ;	
	?debug	L 45
	pop	bp
	ret	
	?debug	E
	?debug	E
_mainMenu	endp
   ;	
   ;	int main(void)
   ;	
	?debug	L 48
	assume	cs:ILLUMINA_TEXT
_main	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,8
	push	si
	?debug	B
	cmp	word ptr DGROUP:__stklen,sp
	ja	short @2@86
	call	far ptr F_OVERFLOW@
@2@86:
   ;	
   ;	
   ;	{
   ;	  int key;
   ;	  tLinkedList players;
   ;	  tLinkedList objects;
   ;	
   ;	  players=ll_init();
   ;	
	?debug	L 55
	call	far ptr _ll_init
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
   ;	
   ;	  objects=ll_init();
   ;	
	?debug	L 56
	call	far ptr _ll_init
	mov	word ptr [bp-6],dx
	mov	word ptr [bp-8],ax
   ;	
   ;	
   ;	  /* Initialization */
   ;	  initObjects(objects);
   ;	
	?debug	L 59
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _initObjects
	add	sp,4
   ;	
   ;	  initPlayers(players);
   ;	
	?debug	L 60
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _initPlayers
	add	sp,4
   ;	
   ;	
   ;	  mainMenu();
   ;	
	?debug	L 62
	push	cs
	call	near ptr _mainMenu
@2@114:
   ;	
   ;	
   ;	  /* Game loop */
   ;	  while (TRUE)
   ;	  /* Infinite loop */
   ;	  {
   ;	    key=GETKEY;
   ;	
	?debug	L 68
	call	far ptr _kbhit
	or	ax,ax
	je	short @2@170
	call	far ptr _getch
	jmp	short @2@198
@2@170:
	xor	ax,ax
@2@198:
	mov	si,ax
   ;	
   ;	    if (key!=0) printf("%d",key);
   ;	
	?debug	L 69
	or	si,si
	je	short @2@254
	push	si
	push	ds
	push	offset DGROUP:s@+68
	call	far ptr _printf
	add	sp,6
@2@254:
   ;	
   ;	    if (key==KEY_ESC) break;
   ;	
	?debug	L 70
	cmp	si,27
	jne	short @2@310
	jmp	short @2@646
@2@310:
   ;	
   ;	/*
   ;	    if ((key=GETKEY)==KEY_ESC) break;
   ;	*/
   ;	    switch (key)
   ;	
	?debug	L 74
	mov	ax,si
	cmp	ax,112
	je	short @2@534
	jg	short @2@478
	cmp	ax,80
	je	short @2@534
	cmp	ax,87
	je	short @2@562
	jmp	short @2@590
@2@478:
	cmp	ax,119
	je	short @2@562
	jmp	short @2@590
@2@534:
   ;	
   ;	    {
   ;	      case KEY_P :
   ;	      case KEY_p :
   ;	        editPlayers(players);
   ;	
	?debug	L 78
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _editPlayers
	add	sp,4
   ;	
   ;	        mainMenu();
   ;	
	?debug	L 79
	push	cs
	call	near ptr _mainMenu
   ;	
   ;	      break;
   ;	
	?debug	L 80
	jmp	short @2@590
@2@562:
   ;	
   ;	
   ;	      case KEY_W :
   ;	      case KEY_w :
   ;	        editWorld(objects);
   ;	
	?debug	L 84
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _editWorld
	add	sp,4
   ;	
   ;	        mainMenu();
   ;	
	?debug	L 85
	push	cs
	call	near ptr _mainMenu
   ;	
   ;	      break;
   ;	
	?debug	L 86
	jmp	short @2@590
@2@590:
   ;	
   ;	
   ;	      default    : ;
   ;	    }
   ;	  if (0) ;
   ;	
	?debug	L 90
	jmp	short @2@618
@2@618:
	jmp	short @2@114
@2@646:
   ;	
   ;	  }
   ;	
   ;	  ll_reset(players);
   ;	
	?debug	L 93
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _ll_reset
	add	sp,4
   ;	
   ;	  ll_reset(objects);
   ;	
	?debug	L 94
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _ll_reset
	add	sp,4
   ;	
   ;	
   ;	  return 0;
   ;	
	?debug	L 96
	xor	ax,ax
	pop	si
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 97
	pop	si
	leave	
	ret	
	?debug	C E3190F744C696E6B65644C69737443656C6C0A00+
	?debug	C 1E01
	?debug	C E31A000400160100
	?debug	C E318000400161900
	?debug	C E6076F626A656374731802F8FF0007706C617965+
	?debug	C 72731802FCFF00036B657904040600
	?debug	E
	?debug	E
_main	endp
ILLUMINA_TEXT	ends
_BSS	segment word public use16 'BSS'
_home	label	byte
	db	255 dup (?)
	?debug	C E9
	?debug	C FA00000000
_BSS	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	'*** ILLUMINATI ***'
	db	10
	db	10
	db	0
	db	'Edit (P)layers'
	db	10
	db	0
	db	'Edit (W)orld'
	db	10
	db	0
	db	'ESC - QUIT GAME'
	db	10
	db	0
	db	'%d'
	db	0
_DATA	ends
ILLUMINA_TEXT	segment byte public use16 'CODE'
ILLUMINA_TEXT	ends
	public	_main
	extrn	F_OVERFLOW@:far
	public	_home
	public	__stklen
	public	_mainMenu
	extrn	_editPlayers:far
	extrn	_editWorld:far
	extrn	_initPlayers:far
	extrn	_initObjects:far
	extrn	_ll_reset:far
	extrn	_ll_init:far
	extrn	_printf:far
	extrn	_kbhit:far
	extrn	_getch:far
	extrn	_clrscr:far
_s@	equ	s@
	?debug	C EA010C
	?debug	C E31B00000023040400
	?debug	C EC055F6D61696E1B1800
	?debug	C E31C00000023040500
	?debug	C EB0B465F4F564552464C4F57401C00
	?debug	C E31D00FF001A08
	?debug	C EC055F686F6D651D0000
	?debug	C EC085F5F73746B6C656E0A0000
	?debug	C E31E00000023010400
	?debug	C EC095F6D61696E4D656E751E1800
	?debug	C E31F00000023010400
	?debug	C EB0C5F65646974506C61796572731F00
	?debug	C E32000000023010400
	?debug	C EB0A5F65646974576F726C642000
	?debug	C E32100000023040400
	?debug	C EB0C5F696E6974506C61796572732100
	?debug	C E32200000023040400
	?debug	C EB0C5F696E69744F626A656374732200
	?debug	C E32300000023010400
	?debug	C EB095F6C6C5F72657365742300
	?debug	C E32400000023180400
	?debug	C EB085F6C6C5F696E69742400
	?debug	C E32500000023040401
	?debug	C EB075F7072696E74662500
	?debug	C E32600000023040400
	?debug	C EB065F6B626869742600
	?debug	C E32700000023040400
	?debug	C EB065F67657463682700
	?debug	C E32800000023010400
	?debug	C EB075F636C727363722800
	?debug	C E60974506F736974696F6E1806000B744C696E6B+
	?debug	C 65644C697374180600057443656C6C1906000666+
	?debug	C 706F735F740606000777636861725F7408060006+
	?debug	C 73697A655F740A06000F744C696E6B65644C6973+
	?debug	C 7443656C6C190700
	?debug	C E20007656C656D656E741A000C6E456C656D656E+
	?debug	C 7453697A650A00046E65787418C00A000000
	end
