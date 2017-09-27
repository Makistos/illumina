/*

EQUIPMENT CHECKING ROUTINES:

 - detect COM1-COM4 (and their addresses)
 - detect mouse driver
 - detect joystick
 - detect processor

*/

const char
	P8086			= 0,
	P80186		= 1,
	P80286		= 2,
	P80386SX	= 3,
	P80386DX	= 4,
	P80486		= 5,

	NOVIDEO		= 0,
	MDA				= 1,
	CGA				= 2,
	EGAMONO		= 3,
	EGACOLOR	= 4,
	VGAMONO		= 5,
	VGACOLOR	= 6,
	MCGAMONO	= 7,
	MCGACOLOR	= 8,

	NOMOUSE		= 0,
	BUSMOUSE	= 1,
	SERIALMOUSE = 2,
	INPORTMOUSE = 3,
	PS2MOUSE  = 4,
	HPMOUSE = 5;

extern char mousedetected;
extern char mousetype;
extern char mouseirqnumber;
extern int mousedriverversion;

char detectcard(void);
char detectprocessor(void);
char detectjoystick(void);
void getmouseinformation(void);
unsigned com1address(void);
unsigned com2address(void);
unsigned com3address(void);
unsigned com4address(void);

