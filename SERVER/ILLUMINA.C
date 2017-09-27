/*************************************************************************
 *
 *N Main module
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *	Purpose
 *P
 * 		This is the main module for Illumina server.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *	History
 *H
 * 		Marko Poutiainen		Aug. 1994												UNIX V BC++ 3.1
 *E
 *************************************************************************/

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "stddefs.h"
#include "linklist.h"
#include "objects.h"
#include "keybrd.h"
#include "inout.h"
#include "misc.h"
#include "init.h"
#include "heap.h"

void mainMenu(void);

extern unsigned _stklen = 32000U;

char home[255];

void mainMenu()
{
  clrscr();
  printf("*** ILLUMINATI ***\n\n");
  printf("Edit (P)layers\n");
  printf("Edit (W)orld\n");
  printf("ESC - QUIT GAME\n");
}


int main(void)

{
  int key;
  tLinkedList players;
  tLinkedList objects;

  players=ll_init();
  objects=ll_init();

  /* Initialization */
  initObjects(objects);
  initPlayers(players);

  mainMenu();

  /* Game loop */
  while (TRUE)
  /* Infinite loop */
  {
    key=GETKEY;
    if (key!=0) printf("%d",key);
    if (key==KEY_ESC) break;
/*
    if ((key=GETKEY)==KEY_ESC) break;
*/
    switch (key)
    {
      case KEY_P :
      case KEY_p :
        editPlayers(players);
        mainMenu();
      break;

      case KEY_W :
      case KEY_w :
        editWorld(objects);
        mainMenu();
      break;

      default    : ;
    }
  if (0) ;
  }

  ll_reset(players);
  ll_reset(objects);

  return 0;
}
