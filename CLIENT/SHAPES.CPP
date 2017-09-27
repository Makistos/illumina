// Shapes.cpp

#include "defs.h"
#include "shapes.h"

//-- TRIANGLE ----------------------------------------------------------------

void triangle(int x1,int y1,int x2,int y2,int x3,int y3)
{	struct BLOCKDAT {long dx1,dx2; unsigned counter;} block1,block2;
	long xx1,xx2;
	int dx1,dx2,dx3;
	int dy1,dy2,dy3;
	int changed;

	asm{
		mov word ptr [changed],2
		mov ax,[y1]
		mov bx,[y2]
		mov cx,[y3]
		cmp ax,bx
		jng notexchanged1
		xchg ax,bx
		mov dx,[x1]
		xchg [x2],dx
		mov [x1],dx
	}
notexchanged1:
	asm{
		cmp ax,cx
		jng notexchanged2
		xchg ax,cx
		mov dx,[x1]
		xchg dx,[x3]
		mov [x1],dx
	}
notexchanged2:
	asm{
		cmp bx,cx
		jng notexchanged3
		xchg bx,cx
		mov dx,[x2]
		xchg dx,[x3]
		mov [x2],dx
	}
notexchanged3:
	asm{
		cmp ax,[screenylimit]
		jnge continue1
		jmp triangleend
	}
continue1:
	asm{
		or cx,cx
		jns continue2
		jmp triangleend
	}
continue2:
	asm{
		cmp ax,bx
		jnz continue3
		inc bx
	}
continue3:
	asm{
		mov [y1],ax
		mov [y2],bx
		mov [y3],cx
		dec ax
		mov [dy1],cx
		sub [dy1],ax
		sub cx,bx
		inc cx
		mov [dy3],cx
		sub bx,ax
		mov [dy2],bx

		mov ax,[x1]
		mov bx,[x2]
		mov cx,[x3]
		mov [dx1],cx
		sub [dx1],ax
		sub cx,bx
		mov [dx3],cx
		sub bx,ax
		mov [dx2],bx
	}

	block2.dx1=block1.dx1=((long)(dx1)<<16)/(dy1);
	block1.dx2=((long)(dx2)<<16)/(dy2);
	block2.dx2=((long)(dx3)<<16)/(dy3);

	if(y1>0) xx2=xx1=(long)(x1)<<16;
	else
	{ xx1=(long)(x1+dx1*(long)(-y1)/dy1)<<16;
		if(y2>0) xx2=(long)(x1+dx2*(long)(-y1)/dy2)<<16;
				else xx2=(long)(x2+dx3*(long)(-y2)/dy3)<<16;
		y1=0;
	}

	asm{
//	COUNTER1=Y2/0/SCREENYLIMIT-Y1+1;
//	COUNTER2=Y3/SCREENYLIMIT-y2/0/SCREENYLIMIT+1;
		mov ax,[y2]
		mov bx,[y3]
		mov cx,[screenylimit]

		cwd
		not dx
		and ax,dx

		sub ax,cx
		cwd
		and ax,dx
		add ax,cx

		xchg ax,bx
		sub ax,cx
		cwd
		and ax,dx
		add ax,cx

		inc ax
		sub ax,bx
		mov [block2.counter],ax
		inc bx
		sub bx,[y1]
		mov [block1.counter],bx

// DX1>DX2 -> DX1<->DX2, XX1<->XX2
		mov eax,[block1.dx1]
		cmp eax,[block1.dx2]
		jle startdrawing
		xchg eax,[block1.dx2]
		mov [block1.dx1],eax

		mov eax,[block2.dx1]
		xchg eax,[block2.dx2]
		mov [block2.dx1],eax

		mov eax,[xx1]
		xchg eax,[xx2]
		mov [xx1],eax
		}
startdrawing:
	asm{
		movzx eax,[screenxlimit]
		shl eax,16
		sub [xx2],eax

		mov dx,0x03c4
		mov al,0x02
		out dx,al
		inc dx
		mov ax,[screenseg]
		mov es,ax
		mov si,[y1]
		shl si,2
		add si,[y1]
		shl si,4
		add si,[screenofs]
		add si,[drawareastart]
		cld
	}
verticalstart:
	asm{
		dec [block1.counter]
		jz verticalend
	}
verticalloop:
	asm{
		mov di,si
		add si,80

		mov eax,[block1.dx2]
		add [xx2],eax
		mov cx,[xx2]+0x02

		mov eax,[block1.dx1]
		add [xx1],eax
		mov bx,[xx1]+0x02

		mov ax,bx
		sar ax,15
		not ax
		and bx,ax

		mov ax,cx
		sar ax,15
		and cx,ax
		add cx,[screenxlimit]

		cmp cx,bx
		jle verticalstart

		mov ax,0xf10f
		shl cx,6
		rol cl,2
		rol ah,cl
		mov cl,bl
		and cl,dh
		shl al,cl
		shr bx,2
		add di,bx

		sub ch,bl
		jz drawend

		out dx,al
		mov al,0x0f
		mov es:[di],al
		inc di
		dec ch
		jz drawend

		out dx,al
		test di,1
		jz drawloop
		mov es:[di],al
		inc di
		dec ch
	}
drawloop:
	asm{
		shr cx,9
		rep stosw
		jnc drawend
		mov es:[di],al
		inc di
	}
drawend:
	asm{
		and al,ah
		out dx,al
		mov es:[di],al
		dec [block1.counter]
		jnz verticalloop
	}
verticalend:
	asm{
		dec [changed]
		jz triangleend
		mov ax,[block2.counter]
		mov [block1.counter],ax
		mov eax,[block2.dx1]
		mov [block1.dx1],eax
		mov eax,[block2.dx2]
		mov [block1.dx2],eax
		jmp verticalstart
	}
triangleend:
}

//-- CIRCLE ------------------------------------------------------------------

void circle(int x,int y,int radius)
{ struct COMBI { int row,col;} blk;
	long sqr4;
	long d,dxx,dxy;
	struct LONG {char x1,x2,y1,y2;} bits;

	asm{
		mov ax,0x1111
		mov cx,[x]
		and cx,0x0003
		rol ax,cl
		mov [bits.x1],ah
		mov [bits.x2],al

		mov ax,0x1111
		mov cx,[x]
		add cx,[radius]
		and cx,0x0003
		rol al,cl
		mov [bits.y1],al
		mov cx,[x]
		sub cx,[radius]
		and cx,0x0003
		rol ah,cl
		mov [bits.y2],ah

		xor edi,edi
		mov di,[radius]
		mov [blk.row],di
		mov [blk.col],0

		mov eax,edi
		mul eax
		mov ebx,eax
		imul eax,4
		mov [dxx],eax

		mov eax,ebx
		shl eax,1
		mov ecx,eax
		mul edi
		add eax,ecx
		sub ebx,eax
		mov [d],ebx

		shl ecx,1
		mov [sqr4],ecx

		mov eax,ecx
		imul ecx,edi
		add ecx,eax
		mov [dxy],ecx

		mov ax,[screenseg]
		mov es,ax
		mov dx,0x03c4
		mov al,0x02
		out dx,al
		inc dx
		mov si,[y]
		shl si,2
		add si,[y]
		shl si,4
	}
circleloop:
	asm{
		mov ebx,[blk]
		shl ebx,2
		add ebx,[blk]
		shl ebx,4
		mov di,si
		sub di,bx
		shl bx,1


		mov eax,[bits]
		mov cx,[x]
		add cx,[blk.col]
		shr cx,2
		out dx,al
		add di,cx
		mov es:[di],al
		add di,bx
		mov es:[di],al
		sub di,cx

		mov cx,[x]
		sub cx,[blk.col]
		shr cx,2
		mov al,ah
		out dx,al
		add di,cx
		mov es:[di],al
		sub di,bx
		mov es:[di],al

		shr eax,16
		shr ebx,16
		mov di,si
		sub di,bx
		shl bx,1

		mov cx,[x]
		add cx,[blk.row]
		shr cx,2
		out dx,al
		add di,cx
		mov es:[di],al
		add di,bx
		mov es:[di],al
		sub di,cx

		mov cx,[x]
		sub cx,[blk.row]
		shr cx,2
		mov al,ah
		out dx,al
		add di,cx
		mov es:[di],al
		sub di,bx
		mov es:[di],al

		ror byte ptr [bits.x2],1
		rol byte ptr [bits.x1],1
		inc word ptr [blk.col]
		mov ecx,[d]
		mov eax,[sqr4]
		add [dxx],eax
		add ecx,[dxx]
		js isnegative
		sub ecx,[dxy]
		sub [dxy],eax
		dec word ptr [blk.row]
		ror byte ptr [bits.y1],1
		rol byte ptr [bits.y2],1
	}
isnegative:
	asm{
		mov [d],ecx
		mov ax,[blk.col]
		cmp ax,[blk.row]
		jg done
		jmp circleloop
	}
done:
}

void filledcircle(int x,int y,int radius)
{
}










