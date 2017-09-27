/*************************************************************************
 *
 *N Module inout
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This module contains the input and output functions.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen    Aug. 1994                       UNIX V BC++ 3.1
 *E
 *************************************************************************/

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#include "stddefs.h"
#include "objects.h"
#include "files.h"
#include "heap.h"
#include "misc.h"
#include "inout.h"

/*************************************************************************
 *
 *N readPlayer
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function reads and returns a player data structure, using the
 *    name as the key field.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Variables
 *A
 *    <return>    == (tPlayer *) The data. If not found, return NULL.
 *    szName <in> == (char *) Player's name.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External variables
 *X
 *    F_PLAYER    "files.h"
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Aug. 1994                                   ANSI C
 *E
 *************************************************************************/

tPlayer *getPlayer(char *szName)
{
  FILE *fp;
  tPlayer player;
  char szBuf[255];
  fpos_t pos;

  fp=fopen(F_PLAYER,"r");
  if(!fp)
  {
    printf("Unable to open %s\n",F_PLAYER);
  }

  rewind(fp);
  while(!feof(fp))
  {
    fgetpos(fp,&pos);
    fread(szBuf,sizeof(player.szName),1,fp);
    if (stricmp(szName,szBuf)==0)
    {
      break;
    }
    fseek(fp,sizeof(tPlayer)-sizeof(player.szName),SEEK_SET);
  }
  if (feof(fp))
  {
    /* No player data found */
    fclose(fp);
    return NULL;
  }

  /* Read the record from the disk to memory */
  fsetpos(fp,&pos);
  fread(&player,sizeof(player),1,fp);

  fclose(fp);

  return &player;
}

/*************************************************************************
 *
 *N writePlayer
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function writes a player record to the disk. It performs this
 *    by first searching through the save file for a matching name. If
 *    a match is found, then the old record is overwritten. If no match is
 *    found, the new record is written at the end of the file.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Variables
 *A
 *    player <in> == (tPlayer) the record to be written.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Aug. 1994                                   ANSI C
 *E
 *************************************************************************/

int writePlayer(tPlayer player)
{
  FILE *fp;
  fpos_t pos;
  char szBuf[255];

  /* Search the record from the file */

  fp=fopen(F_PLAYER,"r+");
  if(!fp)
  {
    printf("Unable to open %s\n",F_PLAYER);
    abort();
  }

  rewind(fp);

  while(!feof(fp))
  {
    fgetpos(fp,&pos);
    fread(szBuf,sizeof(player.szName),1,fp);
    if (stricmp(player.szName,szBuf)==0)
    {
      break;
    }
    fseek(fp,sizeof(tPlayer)-sizeof(player.szName),SEEK_SET);
  }

  if (feof(fp))
  {
    /* Goto end of file */
    fseek(fp,0L,SEEK_END);
    fwrite(&player,sizeof(player),1,fp);
    fclose(fp);
    return 0;
  }

  fsetpos(fp,&pos);
  fwrite(&player,sizeof(player),1,fp);

  fclose(fp);
  return 0;
}

/*************************************************************************
 *
 *N writeObjects
 *
 *************************************************************************/

int writeObjects(tLinkedList list)
{
  FILE* fp;
  tPosition pos;
  tObject obj;

  fp=fopen(F_OBJECT,"w");
  if (!fp)
  {
    printf("Unable to open %s\n",F_OBJECT);
    return -1;
  }

  pos=ll_first(list);

  while (!ll_last(pos))
  {
    ll_element(pos,&obj);
    fwrite(&obj.szName,sizeof(obj.szName),1,fp);
    pos=ll_next(pos);
  }
  /* Write the last one */
  ll_element(pos,&obj);
  fwrite(&obj.szName,sizeof(obj.szName),1,fp);

  fclose(fp);

  return 0;
}

