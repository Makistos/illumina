#include "defs.h"
#include "input.h"

void interrupt (**vects)(...) = 0x00000000l;

//-- Joystick ----------------------------------------------------------------

int jmaxx,jminx,jmaxy,jminy;
int jcentx,jcenty;
int jrange;
int jactualx,jactualy;

int stick_x,stick_y;

void stick_range(int r)
{ jrange=r+1;
}

void stick_reset(void)
{ jmaxx=jcentx+10;
	jminx=jcentx-10;
	jmaxy=jcenty+10;
	jminy=jcenty-10;
}

void stick_center(void)
{ jcentx=jactualx;
	jcenty=jactualy;
}

void stick_update(void)
{ asm{
		mov bx,0
		mov dx,0x0201
		out dx,al
	}
noxkoord:
	asm{
		inc bx
		in al,dx
		test al,0x01
		jnz noxkoord

		mov [jactualx],bx
		cmp bx,[jmaxx]
		jng notgreaterx
		mov [jmaxx],bx
	}
notgreaterx:
	asm{
		cmp bx,[jminx]
		jge calcx
		mov [jminx],bx
	}
calcx:

	if(jactualx<jcentx)
		stick_x=-jrange*(jcentx-jactualx)/(jcentx-jminx+1);
	else
		stick_x=jrange*(jactualx-jcentx)/(jmaxx-jcentx+1);

	asm mov dx,0x0201
ykoordstillon:
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

		mov [jactualy],bx
		cmp bx,[jmaxy]
		jng notgreatery
		mov [jmaxy],bx
	}
notgreatery:
	asm{
		cmp bx,[jminy]
		jge calcy
		mov [jminy],bx
	}
calcy:

	if(jactualy<jcenty)
		stick_y=-jrange*(jcenty-jactualy)/(jcenty-jminy+1);
	else
		stick_y=jrange*(jactualy-jcenty)/(jmaxy-jcenty+1);

done:
}

//-- Mouse -------------------------------------------------------------------



//-- Keyboard ----------------------------------------------------------------

volatile char ispressed[128] = {0};

void interrupt far mykey(...)
{ char key;
	asm{
		in al,0x60
		mov [key],al
		movsx bx,al
		and bx,0x007f
		or al,al
		setns ispressed[bx]
		in al,0x61
		or al,0x80
		out 0x61,al
		and al,0x7f
		out 0x61,al
		mov al,0x20
		out 0x20,al
	}
}

void interrupt far myclock(...)
{ asm{
		mov al,0x60
		out 0x20,al
	}
}

void interrupt (*oldkey)(...);
void interrupt (*oldclock)(...);

void kbd_init(void)
{ oldkey=vects[0x09];
	asm cli
	vects[0x09]=mykey;
	asm sti
}

void kbd_done(void)
{	asm cli
	vects[0x09]=oldkey;
	asm sti
}
