#include "equip.h"

char mousedetected = 0;
char mousetype = 0;
char mouseirqnumber = 0;
int  mousedriverversion = 0;

unsigned com1address(void)
{ asm{
		mov ax,0x40
		mov es,ax
		mov di,0x00
		mov ax,es:[di]
	}
}

unsigned com2address(void)
{ asm{
		mov ax,0x40
		mov es,ax
		mov di,0x02
		mov ax,es:[di]
	}
}

unsigned com3address(void)
{ asm{
		mov ax,0x40
		mov es,ax
		mov di,0x04
		mov ax,es:[di]
	}
}

unsigned com4address(void)
{ asm{
		mov ax,0x40
		mov es,ax
		mov di,0x06
		mov ax,es:[di]
	}
}
char detectjoystick(void)
{ asm{
		mov ax,0x40
		mov es,ax
		mov di,0x11
		mov al,es:[di]
		and al,0x10
		shr al,4
	}
}

void getmouseinformation(void)
{ asm{
		mov ax,0x0000
		mov es,ax
		mov [mousedetected],al
		mov di,0x33*4
		mov ax,es:[di]
		mov bx,es:[di+0x02]
		or ax,bx
		jz done
		mov ax,0x0000
		int 0x33
		mov [mousedetected],al
		or al,al
		jz done
		mov ax,0x0024
		int 0x33
		mov [mousedriverversion],bx
		mov [mousetype],ch
		mov [mouseirqnumber],cl
	}
done:
}

char detectcard(void)
{	char PS2CARDS[13]={0,1,2,2,4,3,2,5,6,2,8,7,8};
	asm{
		mov ax,0x1a00
		int 0x10
		cmp al,0x1a
		jne notPS2

		cmp bl,0x0c
		jg isCGA
		mov bh,0x00
		add bx,offset PS2CARDS
		mov ah,0x00
		mov al,[bx]
		jmp short done
	}
isCGA:
	asm{
		mov ax,CGA
		jmp short done
	}
notPS2:
	asm{
		mov ah,0x12
		mov bx,0x10
		int 0x10
		cmp bx,0x10
		je simpleadapter
		mov ah,0x12
		mov bl,0x10
		int 0x10
		or bh,bh
		jz colorega
		mov ax,EGAMONO
		jmp short done
	}
colorega:
	asm{
		mov ax,EGACOLOR
		jmp short done
	}
simpleadapter:
	asm{
		int 0x11
		and al,0x30
		shr al,4
		mov ah,0
		or al,al
		jz done
		cmp al,3
		jne isCGA
		mov ax,MDA
	}
done:
}


char detectprocessor(void)
{ asm{
		pushf
		mov ax,0x0000
		push ax
		popf
		pushf
		pop ax
		and ax,0xf000
		cmp ax,0xf000
		jne not8086

		push cx
		mov ax,0xffff
		mov cl,33
		shl ax,cl
		pop cx
		mov ax,P80186
		jnz done
		mov ax,P8086
		jmp short done
	}
not8086:
	asm{
		mov ax,0x07000
		push ax
		popf
		pushf
		pop ax
		and ax,0x7000
		mov ax,P80286
		jz done

		mov eax,cr0
		mov ebx,eax
		or al,0x10
		mov cr0,eax
		mov eax,cr0
		mov cr0,ebx
		test al,0x10
		mov ax,P80386SX
		jz done

		mov ecx,esp
		pushfd
		pop ebx
		and esp,not 3
		mov eax,ebx
		xor eax,0x40000
		push eax
		popfd
		pushfd
		pop eax
		push ebx
		popfd
		mov esp,ecx
		cmp eax,ebx
		mov ax,P80386DX
		jz done
		mov ax,P80486
	}
done:
	asm popf
}
