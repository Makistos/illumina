#include <conio.h>
#include <dos.h>

#define XKOORD 1
#define YKOORD 2

void main(void)
{ int a,b;

	while(getch()!=27)
	{ asm{
			mov bx,0
			mov cx,0
			mov [a],bx
			mov [b],cx
			mov dx,0x0201
			out dx,al
		}
readit:
		asm{
			inc bx
			inc cx
			in al,dx
			test al,0x03
			jz done
			test al,0x01
			jnz noxkoord
			cmp [a],0

			mov [a],bx
		}
noxkoord:
		asm{
			in al,dx
			test al,0x02
			jnz ykoordstillon

			mov bx,0
			out dx,al
		}
noykoord:
		asm{
			inc bx
			in al,dx
			test al,0x02
			jnz noykoord
			mov [b],bx
		}
		cprintf("X: %d Y: %d\n\r",a,b);
	}
}

