/*************************************************************************
 *
 *N Module INIT
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This module contains all functions needed to initialize the
 *    structures in the game.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Aug. 1994                                   ANSI C
 *E
 *************************************************************************/

#include <stdio.h>
#include <string.h>

#include "stddefs.h"
#include "linklist.h"
#include "objects.h"
#include "misc.h"
#include "files.h"
#include "keybrd.h"
#include "heap.h"
#include "init.h"

/*************************************************************************
 *
 *N initObjects
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This functions reads the object info from the disk.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Variables
 *A
 *    objects <inout> ==  (tLinkdeList*) List of objects.
 *    tmpList         ==  (tLinkedList) Temporary list.
 *    object          ==  (tObject) Temporary object record.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Files
 *F
 *    objinfo.dat   ==  Object info file.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Aug. 1994                                   ANSI C
 *E
 *************************************************************************/
int initObjects(tLinkedList objects)
{
  FILE *fp;
  tLinkedList tmpList;
  tObject object;
  tPosition pos;

  tmpList=ll_init();

  fp=fopen(F_OBJECT,"rb");
  if (!fp)
  {
    printf("\n%s missing!\n",F_OBJECT);
    return -1;
  }

  while (!feof(fp))
  /* read the object info */
  {
    pos=ll_last(tmpList);

    fread(&object,sizeof(object),1,fp);

    ll_insert(&object,sizeof(tObject),pos);
  }

  /* Copy temporary list to the real list */
  pos=ll_first(tmpList);

  while (!ll_end(pos))
  {
    ll_insert(&pos,sizeof(pos),ll_last(objects)); /* Virhe!! */
  }

  fclose(fp);
  ll_reset(tmpList);

  return 0;
}

/*************************************************************************
 *
 *N initPlayers
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This functions reads the player info from the disk.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Variables
 *A
 *    players <inout> ==  (tLinkdeList*) List of players.
 *    tmpList         ==  (tLinkedList) Temporary list.
 *    player          ==  (tPlayer) Temporary player record.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Files
 *F
 *    players.dat   ==  Player info file.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Aug. 1994                                   ANSI C
 *E
 *************************************************************************/
#pragma inline
int initPlayers(tLinkedList players)
{

  FILE *fp;
  tPosition pos,*pos2;
  tLinkedList tmpList;
  tPlayer player;


  fp=fopen(F_PLAYER,"rb");

  if(!fp)
  {
    printf("%s missing!\n",F_PLAYER);
    return -1;
  }
  tmpList=ll_init();

  while(!feof(fp))
  /* read in the player info */
  {
    pos=ll_last(tmpList);

    fread(&player,sizeof(player),1,fp);

    ll_insert(&player,sizeof(player),pos);
  }

  /* Copy temporary list to the real list */
  pos=ll_first(tmpList);

  while (!ll_end(pos))
  {
    ll_insert(&pos,sizeof(pos),ll_last(players)); /* Virhe !! */
  }

  fclose(fp);
  return 0;
}


void editWorld(tLinkedList objects)

{
  tObject tmpObj;

}

int findPlayer( tLinkedList list,
                tPlayer *player, char *szStr)

{
  tPosition pos;

  pos=ll_first(list);

  while(!ll_end(pos))
  {
    /* browse through the list */
    ll_element(pos,player);
    if (stricmp(player->szName,szStr)==0)
    pos=ll_next(pos);
    break;
  }
  if (ll_end(pos))
  {
    /* check last one */
    ll_element(pos,player);
    if(stricmp(player->szName,szStr)!=0)
    {
      return 0;
    }
  }
/*
  pos=ll_previous(list);
*/
  return 1;
}

void editPlayers(tLinkedList players)

{
  tPlayer tmpPlayer;
  tPosition pos;
  char szStr[255];
  char choice;
  boolean bFinished;

  bFinished=FALSE;

  while(!bFinished)
  {


    printf("What do you want to do?\n");
    printf("(A)dd player\n");
    printf("(D)elete player\n");
    printf("(E)dit player\n");
    while (!(choice=GETKEY)) ;
    if (choice==KEY_ESC) bFinished=TRUE;
    pos=ll_first(players);
    switch (choice)
    {
      case KEY_A :
      case KEY_a :
        printf("Name of player:");
        scanf("%s",szStr);
        strcpy(tmpPlayer.szName,szStr);
        printf("What's the callsign? ");
        scanf("%s",tmpPlayer.szCallsign);
        tmpPlayer.id=0;
        tmpPlayer.speed=0;
        tmpPlayer.pos[0]=0;
        tmpPlayer.pos[1]=0;
        tmpPlayer.pos[2]=0;
        tmpPlayer.heading[0]=0;
        tmpPlayer.heading[1]=0;
        tmpPlayer.heading[2]=0;
        tmpPlayer.ship=XWING;
        tmpPlayer.nKills=0;
        tmpPlayer.nPoints=0;
        /* tmpPlayer.sSaveFile= ?? */
        tmpPlayer.status=0;
        printf("Balance:");
        scanf("%d",tmpPlayer.credits);
        ll_insert(&tmpPlayer,sizeof(tPlayer),ll_last(players));
      break;

      case KEY_D :
      case KEY_d :
        printf("Name of player:");
        scanf("%s",szStr);
        strcpy(tmpPlayer.szName,szStr);

        if (!findPlayer(players,&tmpPlayer,szStr))
        {
          printf("No such player!\n");
          continue;
        }
        pos=ll_locate(&tmpPlayer,players);
        ll_delete(pos);
      break;

      case KEY_E :
      case KEY_e :
        printf("Name of player:");
        scanf("%s",szStr);
        strcpy(tmpPlayer.szName,szStr);
        if (!findPlayer(players,&tmpPlayer,szStr))
        {
          printf("Player not found!\n");
          continue;
        }
        pos=ll_locate(&tmpPlayer,players);
        printf("Balance: %d\n",tmpPlayer.credits);
        printf("New balance:?");
        scanf("%d",tmpPlayer.credits);
        ll_replace(&tmpPlayer,pos);
      break;

      default: continue;
    }

  }

}