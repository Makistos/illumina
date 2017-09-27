#include <stdio.h>
#include <dos.h>

#include "defs.h"
#include "mcga.h"

unsigned clearlength;
unsigned screenseg;
unsigned screenofs;
unsigned drawareastart;
int screenxlimit;
int screenylimit;

//-- General functions -------------------------------------------------------

char initmcga(void)
{ asm {
		mov ax,0x0013
		int 0x10
		push 0x40
		pop es
		mov di,0x49
		mov al,es:[di]
		cmp al,0x13
		je modevalidated
		mov al,0x00
		jmp done
	}
modevalidated:
	asm{
		mov dx,0x03d4
		mov al,0x11
		out dx,al
		inc dx
		in al,dx
		and al,0x7f
		out dx,al
		dec dx

		mov ax,0x4109
		out dx,ax
		mov ax,0x0014
		out dx,ax
		mov ax,0xe317
		out dx,ax

		mov dx,0x03c4
		mov ax,0x0604
		out dx,ax

		mov ax,0xa000
		mov [screenseg],ax
		mov ax,0x0000
		mov [screenofs],ax
		mov al,0x01
	}
done:
}

void closemcga(void)
{ asm {
		mov ax,0x0003
		int 0x10
	}
}

void setclearlength(unsigned length)
{ asm {
		mov ax,[length]
		mov [clearlength],ax
	}
}

void setdrawarea(int x,int y,int width,int height)
{ asm {
		mov ax,[y]
		shl ax,2
		add ax,[y]
		shl ax,4
		add ax,[x]
		mov [drawareastart],ax

		mov ax,[width]
		mov [screenxlimit],ax
		mov ax,[height]
		mov [screenylimit],ax
	}
}

void loadlatches(char color)
{ asm{
		push [screenseg]
		pop es

		mov di,0xffff

		mov dx,0x03c4
		mov ax,0x0f02
		out dx,ax

		mov dx,0x03ce
		mov ax,0xff08
		out dx,ax

		mov al,[color]
		mov es:[di],al
		mov al,es:[di]

		mov ax,0x0008
		out dx,ax
	}
}

void restorenormalmode(void)
{ asm{
		mov dx,0x03ce
		mov ax,0xff08
		out dx,ax
	}
}

//-- Drawing functions -------------------------------------------------------

void clearscreen(void)
{ asm {
		mov dx,0x03c4
		mov ax,0x0f02
		out dx,ax

		mov cx,[clearlength]
		mov ax,[screenseg]
		mov es,ax
		mov di,[screenofs]
		mov ax,0x0000
		cld

		rep stosw
	}
}

void putpixel(int x,int y,char color)
{ asm {
		mov ax,[screenseg]
		mov es,ax

		mov dx,0x03c4
		mov cx,[x]
		shl cx,6
		shr cl,6
		mov ax,0x0102
		shl ah,cl
		out dx,ax

		mov di,[y]
		shl di,2
		add di,[y]
		shl di,4
		shr cx,8
		add di,cx
		add di,[screenofs]

		mov al,[color]
		mov es:[di],al
	}
}

void putpixel(int x,int y)
{ asm {
		mov ax,[screenseg]
		mov es,ax

		mov dx,0x03c4
		mov cx,[x]
		shl cx,6
		shr cl,6
		mov ax,0x0102
		shl ah,cl
		out dx,ax

		mov di,[y]
		shl di,2
		add di,[y]
		shl di,4
		shr cx,8
		add di,cx
		add di,[screenofs]

		mov es:[di],al
	}
}

void clippedpixel(int x,int y,char color)
{ asm {
		mov ax,[screenseg]
		mov es,ax

		mov dx,0x03c4
		mov cx,[x]
		cmp cx,[screenxlimit]
		jg notinscreen

		shl cx,6
		shr cl,6
		mov ax,0x0102
		shl ah,cl
		out dx,ax

		mov ax,[y]
		cmp ax,[screenylimit]
		jg notinscreen

		mov di,ax
		shl di,2
		add di,ax
		shl di,4
		shr cx,8
		add di,cx
		add di,[screenofs]
		add di,[drawareastart]

		mov al,[color]
		mov es:[di],al
	}
notinscreen:
}

void drawline(int x1,int y1,int x2,int y2)
{ int ccx,ccy,cc;
	int acx,acy;

	asm{
		mov ax,[x2]
		sub ax,[x1]
		mov [ccx],ax
		cwd
		xor ax,dx
		shr dx,1
		adc ax,0

		mov [acx],ax
		mov ax,[y2]
		sub ax,[y1]
		mov [ccy],ax
		cwd
		xor ax,dx
		shr dx,1
		adc ax,0

		mov [acy],ax
		cmp ax,[acx]
		jg dygreater

		neg ax
		mov di,ax
		shl edi,16
		mov ax,[ccx]
		cwd
		neg ax
		shl ax,1
		adc dx,0
		mov di,dx
		mov si,[acx]
		mov [cc],si
		shl esi,16
		mov ax,[ccy]
		cwd
		neg ax
		shl ax,1
		adc dx,0
		mov si,dx
		imul si,320
		jmp startdraw
	}
dygreater:
	asm{
		mov si,ax
		mov di,[acx]
		neg di
		shl edi,16
		mov ax,[ccy]
		cwd
		neg ax
		shl ax,1
		adc dx,0
		mov di,dx
		imul di,320
		mov [cc],si
		shl esi,16
		mov ax,[ccx]
		cwd
		neg ax
		shl ax,1
		adc dx,0
		mov si,dx
	}
startdraw:
	asm{
		mov ax,[screenseg]
		mov es,ax
		mov ax,[y1]
		movzx ecx,ax
		shl cx,2
		add cx,ax
		shl cx,6
		add cx,[x1]
		add cx,[screenofs]
		add cx,[drawareastart]
		mov dx,0x03c4
		mov al,0x02
		out dx,al
		inc dx
		mov ax,[cc]
		inc ax
	}
startline:
	asm{
		dec ax
		jz endline
	}
lineloop:
	asm{
		mov bl,cl
		and cl,dh
		mov bh,al
		mov al,0x01
		shl al,cl
		out dx,al
		mov al,bh
		mov bh,ch
		mov cl,bl
		shr bx,2
		mov es:[bx],al

		add ecx,edi
		jns startline
		add ecx,esi

		dec ax
		jnz lineloop
	}
endline:
}

void clippedline(int x1,int y1,int x2,int y2)
{ int dx,dy;
	int outcode1,outcode2;

	outcode1=outcode2=0;
	if(y1>screenylimit) outcode1|=1; else if(y1<0) outcode1|=2;
	if(x1>screenxlimit) outcode1|=4; else if(x1<0) outcode1|=8;
	if(y2>screenylimit) outcode2|=1; else if(y2<0) outcode2|=2;
	if(x2>screenxlimit) outcode2|=4; else if(x2<0) outcode2|=8;

	if (outcode1&outcode2) return;
	if (!(outcode1|outcode2))	{ drawline(x1,y1,x2,y2); return; }

	dx=x2-x1;
	dy=y2-y1;

	while(1)
	{	if(!outcode1)
		{ EXCHG(&x1,&x2);
			EXCHG(&y1,&y2);
			EXCHG(&outcode1,&outcode2);
		}

		if(outcode1&1)
		{ x1+=(dx*(long)(screenylimit-y1))/dy;
			y1=screenylimit;
			outcode1=0;
			if(x1>screenxlimit) outcode1|=4; else if(x1<0) outcode1|=8;
		}
		else if(outcode1&2)
		{ x1+=(dx*(long)(-y1))/dy;
			y1=outcode1=0;
			if(x1>screenxlimit) outcode1|=4; else if(x1<0) outcode1|=8;
		}
		else if(outcode1&4)
		{ y1+=(dy*(long)(screenxlimit-x1))/dx;
			x1=screenxlimit;
			outcode1=0;
			if(y1>screenylimit) outcode1|=1; else if(y1<0) outcode1|=2;
		}
		else if(outcode1&8)
		{ y1+=(dy*(long)(-x1))/dx;
			x1=outcode1=0;
			if(y1>screenylimit) outcode1|=1; else if(y1<0) outcode1|=2;
		}

		if (outcode1&outcode2) return;
		if (!(outcode1|outcode2))	{ drawline(x1,y1,x2,y2); return; }
	}
}

//-- Special register manipulation -------------------------------------------

void setdrawmode(char mode)
{ asm{
		mov dx,0x03ce
		mov al,0x05
		out dx,al
		inc dx
		in al,dx
		and al,0xf0
		or al,[mode]
		out dx,al
	}
}

void setbitmask(char mask)
{ asm{
		mov dx,0x03ce
		mov al,0x08
		mov ah,[mask]
		out dx,ax
	}
}

void setplanes(char planes)
{ asm{
		mov dx,0x03c4
		mov al,0x02
		mov ah,planes
		out dx,ax
	}
}

//-- Register 0x03c0 manipulation --------------------------------------------

void reset03c0(void)
{ asm{
		mov dx,0x03da
		in al,dx
	}
}

void set03c0(char index,char data)
{ asm{
		mov dx,0x03c0
		mov al,[index]
		or al,0x20
		out dx,al
		mov al,[data]
		out dx,al
	}
}

//-- Color manipulation ------------------------------------------------------

void selectcolor(char color)
{ asm{
		mov dx,0x03c8
		mov al,[color]
		out dx,al
	}
}

void setcolorvalues(char r,char g,char b)
{ asm{
		mov dx,0x03c9
		mov al,[r]
		out dx,al
		mov al,[g]
		out dx,al
		mov al,[b]
		out dx,al
	}
}


//-- Bitmap manipulation -----------------------------------------------------


int loadgrf(const char *filename)
{	static char bitmap[320*73];
	char *screen = (char *)(MK_FP(0xa000,10160));
	int i,j;

	FILE *file=fopen(filename,"rb");
	fread(bitmap,2,2,file);
	fread(bitmap,320,73,file);
	asm mov dx,0x3c8
	asm mov al,0
	asm out dx,al
	for(i=0;i<3*256;i++)
	{ fread(&j,1,1,file);
		asm mov dx,0x03c9
		asm mov ax,[j]
		asm out dx,al
	}
	fclose(file);


	for(i=0;i<4;i++)
	{ setplanes(1<<i);
		for(j=0;j<80*73;j++) screen[j]=bitmap[j*4+i];
	}
	return 1;
}
