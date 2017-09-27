#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#include "defs.h"
#include "mcga.h"
#include "shapes.h"
#include "equip.h"
#include "input.h"

void clock_start(struct time *starttime)
{ gettime(starttime);
}

long clock_stop(struct time *starttime)
{ struct time stoptime;
	long start,stop;

	gettime(&stoptime);

	start = (long)(starttime->ti_hour);
	start *= 60;
	start += (long)(starttime->ti_min);
	start *= 60;
	start += (long)(starttime->ti_sec);
	start *= 100;
	start += (long)(starttime->ti_hund);

	stop  = (long)(stoptime.ti_hour);
	stop  *= 60;
	stop  += (long)(stoptime.ti_min);
	stop  *= 60;
	stop  += (long)(stoptime.ti_sec);
	stop  *= 100;
	stop  += (long)(stoptime.ti_hund);

	return stop-start;
}

char processors[6][10] = {"8086","80186","80286","80386SX","80386DX","80486"};
char mousenames[6][15] = {"None","Serial mouse","InPort mouse","PS/2 mouse","HP mouse"};

void main(void)
{ long a;
	struct time starttime;
	int x,y;

	/*
	cprintf("Configuration\n\r");
	cprintf("-------------\n\n\r");
	cprintf("COM1 I/O-address: [%4x]\n\r",com1address());
	cprintf("COM2 I/O-address: [%4x]\n\r",com2address());
	cprintf("COM3 I/O-address: [%4x]\n\r",com3address());
	cprintf("COM4 I/O-address: [%4x]\n\r",com4address());
	cprintf("-----------------\n\r");
	getmouseinformation();
	cprintf("Mouse...........: %s\n\r",mousedetected?"Detected":"Not detected");
	cprintf("Mouse type......: %s\n\r",mousenames[mousetype]);
	cprintf("Driver version..: %d\n\r",mousedriverversion);
	cprintf("Mouse IRQ.......: %d\n\r",mouseirqnumber);
	cprintf("Joystick........: %s\n\r",detectjoystick()?"Detected":"Not detected");
	cprintf("-----------------\n\r");
	cprintf("Processor.......: %s\n\r",processors[detectprocessor()]);
	cprintf("Coprocessor.....: \n\r");

	/**/

	//*
	if(!initmcga())
	{ cprintf("Error: This program needs MCGA-display.");
		exit;
	}
	setclearlength(200*40);
	setdrawarea(0,0,319,199);
	clearscreen();
	loadgrf("COCKPIT1.GRF");

	//*
	getch();
//	clock_start(&starttime);
	/**/
	/*
	for(a=0;a<10000;a++)
	{ loadlatches(random(256));
		//drawline(random(320),random(200),random(320),random(200));
		//clippedline(random(320),random(200),random(320),random(200));
		//clippedline(random(1000)-400,random(1000)-400,random(1000)-400,random(1000)-400);
		//clippedline(random(4000)-1600,random(4000)-1600,random(4000)-1600,random(4000)-1600);
		//if(getch()==27) break;
	}
	/**/

	/*
	for(a=0;a<500;a++)
	{	loadlatches(random(256));
		//circle(random(320),random(200),random(50));
		//clearscreen();
		//triangle(0,-200,0,200,640,200);
		//triangle(160,0,0,200,320,200);
		//triangle(random(160),random(100),random(160),random(100),random(160),random(100));
		//triangle(random(320),random(200),random(320),random(200),random(320),random(200));
		//triangle(random(480)-80,random(400)-100,
		//				 random(480)-80,random(400)-100,
		//				 random(480)-80,random(400)-100);
		//triangle(random(1000)-400,random(1000)-400,
		//				 random(1000)-400,random(1000)-400,
		//				 random(1000)-400,random(1000)-400);
		//triangle(random(4000)-1600,random(4000)-1600,
		//				 random(4000)-1600,random(4000)-1600,
		//				 random(4000)-1600,random(4000)-1600);
		//x=random(320);
		//y=random(200);
		//triangle(x,y,x+2,y-2,x-2,y-2);
		//triangle(x,y,x+20,y-20,x-20,y-20);
		//triangle(0,100,320,100,160,200);
		//if(getch()==27) break;
	}
	/**/
	//*
	//a=clock_stop(&starttime);

	//getch();
	closemcga();

	//cprintf("%ld",a);getch();
	/**/

}