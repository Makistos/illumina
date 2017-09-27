#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "linklist.h"
enum ships { XWING=0,COMANCHE }; 

typedef struct
{
  char szName[50];
  int maxSpeed;
  int maxTurn;

} tShip ;

typedef struct

{
  char szName[80];
  int speed;
  long int pos[3];
  int heading[3];

} tObject ;

typedef struct

{
  char szName[80];
  char szCallsign[10];
  int id;
  int speed;
  long int pos[3];
  int heading[3];
  int ship;
  int nKills;               /* No of kills */
  int nPoints;              /* Points total */
  char szSaveFile[12];      /* Save file */
  int status;               /* 0 = in base, 1 = in flight, 2 = killed */
  int credits;              /* Balance */

} tPlayer;

typedef struct tCoalition
{
  tLinkedList players;
  long int score;
};

#endif