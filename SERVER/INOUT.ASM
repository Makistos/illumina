	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "INOUT.C"
	?debug	C E910A12E1D07494E4F55542E43
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5354444C49422E+
	?debug	C 48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F444546532E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C5F4E554C4C2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C434F4E494F2E48
	?debug	C E94019CA1815433A5C42435C494E434C5544455C535444494F2E48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C5F4E46494C452E+
	?debug	C 48
	?debug	C E94019CA1816433A5C42435C494E434C5544455C535452494E472E+
	?debug	C 48
	?debug	C E957B71A1D09535444444546532E48
	?debug	C E9DAA02E1D094F424A454354532E48
	?debug	C E96D932E1D0A4C494E4B4C4953542E48
	?debug	C E9CE9A251D0746494C45532E48
	?debug	C E9E0952E1D06484541502E48
	?debug	C E912952E1D064D4953432E48
	?debug	C E9C89E251D07494E4F55542E48
INOUT_TEXT	segment byte public use16 'CODE'
INOUT_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:INOUT_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
INOUT_TEXT	segment byte public use16 'CODE'
	?debug	C E80107494E4F55542E4310A12E1D
   ;	
   ;	tPlayer *getPlayer(char *szName)
   ;	
	?debug	L 63
	assume	cs:INOUT_TEXT
_getPlayer	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,398
	?debug	C E318000400160800
	?debug	C E606737A4E616D65180A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @1@86
	call	far ptr F_OVERFLOW@
@1@86:
   ;	
   ;	{
   ;	  FILE *fp;
   ;	  tPlayer player;
   ;	  char szBuf[255];
   ;	  fpos_t pos;
   ;	
   ;	  fp=fopen(F_PLAYER,"r");
   ;	
	?debug	L 70
	push	ds
	push	offset DGROUP:s@+11
	push	ds
	push	offset DGROUP:s@
	call	far ptr _fopen
	add	sp,8
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
   ;	
   ;	  if(!fp)
   ;	
	?debug	L 71
	cmp	dword ptr [bp-4],large 0
	jne	short @1@142
   ;	
   ;	  {
   ;	    printf("Unable to open %s\n",F_PLAYER);
   ;	
	?debug	L 73
	push	ds
	push	offset DGROUP:s@+32
	push	ds
	push	offset DGROUP:s@+13
	call	far ptr _printf
	add	sp,8
@1@142:
   ;	
   ;	  }
   ;	
   ;	  rewind(fp);
   ;	
	?debug	L 76
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _rewind
	add	sp,4
	jmp	short @1@254
@1@170:
   ;	
   ;	  while(!feof(fp))
   ;	  {
   ;	    fgetpos(fp,&pos);
   ;	
	?debug	L 79
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fgetpos
	add	sp,8
   ;	
   ;	    fread(szBuf,sizeof(player.szName),1,fp);
   ;	
	?debug	L 80
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	80
	push	ss
	lea	ax,word ptr [bp-398]
	push	ax
	call	far ptr _fread
	add	sp,12
   ;	
   ;	    if (stricmp(szName,szBuf)==0)
   ;	
	?debug	L 81
	push	ss
	lea	ax,word ptr [bp-398]
	push	ax
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _stricmp
	add	sp,8
	or	ax,ax
	jne	short @1@226
   ;	
   ;	    {
   ;	      break;
   ;	
	?debug	L 83
	jmp	short @1@282
@1@226:
   ;	
   ;	    }
   ;	    fseek(fp,sizeof(tPlayer)-sizeof(player.szName),SEEK_SET);
   ;	
	?debug	L 85
	push	0
	push	large 54
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fseek
	add	sp,10
@1@254:
	?debug	L 77
	les	bx,dword ptr [bp-4]
	test	word ptr es:[bx+2],32
	je	short @1@170
@1@282:
   ;	
   ;	  }
   ;	  if (feof(fp))
   ;	
	?debug	L 87
	les	bx,dword ptr [bp-4]
	test	word ptr es:[bx+2],32
	je	short @1@338
   ;	
   ;	  {
   ;	    /* No player data found */
   ;	    fclose(fp);
   ;	
	?debug	L 90
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fclose
	add	sp,4
   ;	
   ;	    return NULL;
   ;	
	?debug	L 91
	xor	dx,dx
	xor	ax,ax
	leave	
	ret	
@1@338:
   ;	
   ;	  }
   ;	
   ;	  /* Read the record from the disk to memory */
   ;	  fsetpos(fp,&pos);
   ;	
	?debug	L 95
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fsetpos
	add	sp,8
   ;	
   ;	  fread(&player,sizeof(player),1,fp);
   ;	
	?debug	L 96
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	134
	push	ss
	lea	ax,word ptr [bp-142]
	push	ax
	call	far ptr _fread
	add	sp,12
   ;	
   ;	
   ;	  fclose(fp);
   ;	
	?debug	L 98
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fclose
	add	sp,4
   ;	
   ;	
   ;	  return &player;
   ;	
	?debug	L 100
	mov	dx,ss
	lea	ax,word ptr [bp-142]
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 101
	leave	
	ret	
	?debug	C E31900FF001A08
	?debug	C E31A0086001E01
	?debug	C E31B0050001A08
	?debug	C E31C000A001A08
	?debug	C E31D000C001A06
	?debug	C E31E0006001A04
	?debug	C E31F000C001A08
	?debug	C E3210014001E0E
	?debug	C E320000400162100
	?debug	C E603706F730602F8FF0005737A427566190272FE+
	?debug	C 0006706C617965721A0272FF000266702002FCFF+
	?debug	C 0006737A4E616D65180A060000
	?debug	E
	?debug	E
_getPlayer	endp
   ;	
   ;	int writePlayer(tPlayer player)
   ;	
	?debug	L 130
	assume	cs:INOUT_TEXT
_writePlayer	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,264
	?debug	C E606706C617965721A0A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @2@86
	call	far ptr F_OVERFLOW@
@2@86:
   ;	
   ;	{
   ;	  FILE *fp;
   ;	  fpos_t pos;
   ;	  char szBuf[255];
   ;	
   ;	  /* Search the record from the file */
   ;	
   ;	  fp=fopen(F_PLAYER,"r+");
   ;	
	?debug	L 138
	push	ds
	push	offset DGROUP:s@+54
	push	ds
	push	offset DGROUP:s@+43
	call	far ptr _fopen
	add	sp,8
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
   ;	
   ;	  if(!fp)
   ;	
	?debug	L 139
	cmp	dword ptr [bp-4],large 0
	jne	short @2@142
   ;	
   ;	  {
   ;	    printf("Unable to open %s\n",F_PLAYER);
   ;	
	?debug	L 141
	push	ds
	push	offset DGROUP:s@+76
	push	ds
	push	offset DGROUP:s@+57
	call	far ptr _printf
	add	sp,8
   ;	
   ;	    abort();
   ;	
	?debug	L 142
	call	far ptr _abort
@2@142:
   ;	
   ;	  }
   ;	
   ;	  rewind(fp);
   ;	
	?debug	L 145
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _rewind
	add	sp,4
	jmp	short @2@254
@2@170:
   ;	
   ;	
   ;	  while(!feof(fp))
   ;	  {
   ;	    fgetpos(fp,&pos);
   ;	
	?debug	L 149
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fgetpos
	add	sp,8
   ;	
   ;	    fread(szBuf,sizeof(player.szName),1,fp);
   ;	
	?debug	L 150
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	80
	push	ss
	lea	ax,word ptr [bp-264]
	push	ax
	call	far ptr _fread
	add	sp,12
   ;	
   ;	    if (stricmp(player.szName,szBuf)==0)
   ;	
	?debug	L 151
	push	ss
	lea	ax,word ptr [bp-264]
	push	ax
	push	ss
	lea	ax,word ptr [bp+6]
	push	ax
	call	far ptr _stricmp
	add	sp,8
	or	ax,ax
	jne	short @2@226
   ;	
   ;	    {
   ;	      break;
   ;	
	?debug	L 153
	jmp	short @2@282
@2@226:
   ;	
   ;	    }
   ;	    fseek(fp,sizeof(tPlayer)-sizeof(player.szName),SEEK_SET);
   ;	
	?debug	L 155
	push	0
	push	large 54
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fseek
	add	sp,10
@2@254:
	?debug	L 147
	les	bx,dword ptr [bp-4]
	test	word ptr es:[bx+2],32
	je	short @2@170
@2@282:
   ;	
   ;	  }
   ;	
   ;	  if (feof(fp))
   ;	
	?debug	L 158
	les	bx,dword ptr [bp-4]
	test	word ptr es:[bx+2],32
	je	short @2@338
   ;	
   ;	  {
   ;	    /* Goto end of file */
   ;	    fseek(fp,0L,SEEK_END);
   ;	
	?debug	L 161
	push	2
	push	large 0
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fseek
	add	sp,10
   ;	
   ;	    fwrite(&player,sizeof(player),1,fp);
   ;	
	?debug	L 162
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	134
	push	ss
	lea	ax,word ptr [bp+6]
	push	ax
	call	far ptr _fwrite
	add	sp,12
   ;	
   ;	    fclose(fp);
   ;	
	?debug	L 163
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fclose
	add	sp,4
   ;	
   ;	    return 0;
   ;	
	?debug	L 164
	xor	ax,ax
	leave	
	ret	
@2@338:
   ;	
   ;	  }
   ;	
   ;	  fsetpos(fp,&pos);
   ;	
	?debug	L 167
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fsetpos
	add	sp,8
   ;	
   ;	  fwrite(&player,sizeof(player),1,fp);
   ;	
	?debug	L 168
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	134
	push	ss
	lea	ax,word ptr [bp+6]
	push	ax
	call	far ptr _fwrite
	add	sp,12
   ;	
   ;	
   ;	  fclose(fp);
   ;	
	?debug	L 170
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fclose
	add	sp,4
   ;	
   ;	  return 0;
   ;	
	?debug	L 171
	xor	ax,ax
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 172
	leave	
	ret	
	?debug	C E32200FF001A08
	?debug	C E605737A4275662202F8FE0003706F730602F8FF+
	?debug	C 000266702002FCFF0006706C617965721A0A0600+
	?debug	C 00
	?debug	E
	?debug	E
_writePlayer	endp
   ;	
   ;	int writeObjects(tLinkedList list)
   ;	
	?debug	L 180
	assume	cs:INOUT_TEXT
_writeObjects	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,108
	?debug	C E3240F744C696E6B65644C69737443656C6C0A00+
	?debug	C 1E18
	?debug	C E325000400160100
	?debug	C E323000400162400
	?debug	C E6046C697374230A060000
	?debug	B
	cmp	word ptr __stklen,sp
	ja	short @3@86
	call	far ptr F_OVERFLOW@
@3@86:
   ;	
   ;	{
   ;	  FILE* fp;
   ;	  tPosition pos;
   ;	  tObject obj;
   ;	
   ;	  fp=fopen(F_OBJECT,"w");
   ;	
	?debug	L 186
	push	ds
	push	offset DGROUP:s@+99
	push	ds
	push	offset DGROUP:s@+87
	call	far ptr _fopen
	add	sp,8
	mov	word ptr [bp-2],dx
	mov	word ptr [bp-4],ax
   ;	
   ;	  if (!fp)
   ;	
	?debug	L 187
	cmp	dword ptr [bp-4],large 0
	jne	short @3@142
   ;	
   ;	  {
   ;	    printf("Unable to open %s\n",F_OBJECT);
   ;	
	?debug	L 189
	push	ds
	push	offset DGROUP:s@+120
	push	ds
	push	offset DGROUP:s@+101
	call	far ptr _printf
	add	sp,8
   ;	
   ;	    return -1;
   ;	
	?debug	L 190
	mov	ax,-1
	leave	
	ret	
@3@142:
   ;	
   ;	  }
   ;	
   ;	  pos=ll_first(list);
   ;	
	?debug	L 193
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	call	far ptr _ll_first
	add	sp,4
	mov	word ptr [bp-6],dx
	mov	word ptr [bp-8],ax
	jmp	short @3@198
@3@170:
   ;	
   ;	
   ;	  while (!ll_last(pos))
   ;	  {
   ;	    ll_element(pos,&obj);
   ;	
	?debug	L 197
	push	ss
	lea	ax,word ptr [bp-108]
	push	ax
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _ll_element
	add	sp,8
   ;	
   ;	    fwrite(&obj.szName,sizeof(obj.szName),1,fp);
   ;	
	?debug	L 198
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	80
	push	ss
	lea	ax,word ptr [bp-108]
	push	ax
	call	far ptr _fwrite
	add	sp,12
   ;	
   ;	    pos=ll_next(pos);
   ;	
	?debug	L 199
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _ll_next
	add	sp,4
	mov	word ptr [bp-6],dx
	mov	word ptr [bp-8],ax
@3@198:
	?debug	L 195
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _ll_last
	add	sp,4
	or	ax,dx
	je	short @3@170
   ;	
   ;	  }
   ;	  /* Write the last one */
   ;	  ll_element(pos,&obj);
   ;	
	?debug	L 202
	push	ss
	lea	ax,word ptr [bp-108]
	push	ax
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	call	far ptr _ll_element
	add	sp,8
   ;	
   ;	  fwrite(&obj.szName,sizeof(obj.szName),1,fp);
   ;	
	?debug	L 203
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	push	1
	push	80
	push	ss
	lea	ax,word ptr [bp-108]
	push	ax
	call	far ptr _fwrite
	add	sp,12
   ;	
   ;	
   ;	  fclose(fp);
   ;	
	?debug	L 205
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _fclose
	add	sp,4
   ;	
   ;	
   ;	  return 0;
   ;	
	?debug	L 207
	xor	ax,ax
	leave	
	ret	
   ;	
   ;	}
   ;	
	?debug	L 208
	leave	
	ret	
	?debug	C E3260064001E1C
	?debug	C E3270050001A08
	?debug	C E328000C001A06
	?debug	C E3290006001A04
	?debug	C E6036F626A260294FF0003706F732302F8FF0002+
	?debug	C 66702002FCFF00046C697374230A060000
	?debug	E
	?debug	E
_writeObjects	endp
	?debug	C E9
	?debug	C FA00000000
INOUT_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	'player.dat'
	db	0
	db	'r'
	db	0
	db	'Unable to open %s'
	db	10
	db	0
	db	'player.dat'
	db	0
	db	'player.dat'
	db	0
	db	'r+'
	db	0
	db	'Unable to open %s'
	db	10
	db	0
	db	'player.dat'
	db	0
	db	'objects.dat'
	db	0
	db	'w'
	db	0
	db	'Unable to open %s'
	db	10
	db	0
	db	'objects.dat'
	db	0
_DATA	ends
INOUT_TEXT	segment byte public use16 'CODE'
INOUT_TEXT	ends
	extrn	F_OVERFLOW@:far
	extrn	__stklen:word
	public	_writeObjects
	public	_writePlayer
	public	_getPlayer
	extrn	_stricmp:far
	extrn	_ll_element:far
	extrn	_ll_next:far
	extrn	_ll_last:far
	extrn	_ll_first:far
	extrn	_rewind:far
	extrn	_printf:far
	extrn	_fwrite:far
	extrn	_fsetpos:far
	extrn	_fseek:far
	extrn	_fread:far
	extrn	_fopen:far
	extrn	_fgetpos:far
	extrn	_fclose:far
	extrn	_abort:far
_s@	equ	s@
	?debug	C EA010C
	?debug	C E32A00000023040500
	?debug	C EB0B465F4F564552464C4F57402A00
	?debug	C EB085F5F73746B6C656E0A00
	?debug	C E32B00000023040400
	?debug	C EC0D5F77726974654F626A656374732B1800
	?debug	C E32C00000023040400
	?debug	C EC0C5F7772697465506C617965722C1800
	?debug	C E32E000400161A00
	?debug	C E32D000000232E0400
	?debug	C EC0A5F676574506C617965722D1800
	?debug	C E32F00000023040400
	?debug	C EB085F73747269636D702F00
	?debug	C E33000000023010400
	?debug	C EB0B5F6C6C5F656C656D656E743000
	?debug	C E33100000023230400
	?debug	C EB085F6C6C5F6E6578743100
	?debug	C E33200000023230400
	?debug	C EB085F6C6C5F6C6173743200
	?debug	C E33300000023230400
	?debug	C EB095F6C6C5F66697273743300
	?debug	C E33400000023010400
	?debug	C EB075F726577696E643400
	?debug	C E33500000023040401
	?debug	C EB075F7072696E74663500
	?debug	C E336000000230A0400
	?debug	C EB075F6677726974653600
	?debug	C E33700000023040400
	?debug	C EB085F66736574706F733700
	?debug	C E33800000023040400
	?debug	C EB065F667365656B3800
	?debug	C E339000000230A0400
	?debug	C EB065F66726561643900
	?debug	C E33A00000023200400
	?debug	C EB065F666F70656E3A00
	?debug	C E33B00000023040400
	?debug	C EB085F66676574706F733B00
	?debug	C E33C00000023040400
	?debug	C EB075F66636C6F73653C00
	?debug	C E33D00000023010400
	?debug	C EB065F61626F72743D00
	?debug	C E60774506C617965721A060007744F626A656374+
	?debug	C 2606000974506F736974696F6E2306000B744C69+
	?debug	C 6E6B65644C697374230600057443656C6C240600+
	?debug	C 0446494C452106000666706F735F740606000777+
	?debug	C 636861725F740806000673697A655F740A06000F+
	?debug	C 744C696E6B65644C69737443656C6C240700
	?debug	C E20006737A4E616D651B000A737A43616C6C7369+
	?debug	C 676E1C000269640400057370656564040003706F+
	?debug	C 731D000768656164696E671E0004736869700400+
	?debug	C 066E4B696C6C730400076E506F696E747304000A+
	?debug	C 737A5361766546696C651F000673746174757304+
	?debug	C 00076372656469747304C086000000
	?debug	C E200056C6576656C040005666C6167730A000266+
	?debug	C 64080004686F6C640800056273697A6504000662+
	?debug	C 756666657218000463757270180006697374656D+
	?debug	C 700A0005746F6B656E04C014000000
	?debug	C E20007656C656D656E7425000C6E456C656D656E+
	?debug	C 7453697A650A00046E65787423C00A000000
	?debug	C E20006737A4E616D652700057370656564040003+
	?debug	C 706F7328000768656164696E6729C064000000
	end
