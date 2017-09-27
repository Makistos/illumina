#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "heap.h"
#include "misc.h"

#ifndef DEBUG
void *my_alloc( unsigned long size )
{
  void  *p;
  p = malloc( size );
  if (!p)
  {
    printf("Out of memory  %lu  %lu\n",size,farcoreleft());
    exit(1);
  }
  return p;
}
#endif

/* Following string functions are missing in ANSI C... */

void strupr(char *str)
{
  int i;

  for (i=0;i<strlen(str);i++)
   toupper(str[i]);
}

int stricmp(char *s1, char *s2)
{
  char *szTemp1,*szTemp2;

  szTemp1=(char *)my_alloc(strlen(s1));
  szTemp2=(char *)my_alloc(strlen(s2));

  strcpy(szTemp1,s1);
  strupr(szTemp1);
  strcpy(szTemp2,s2);
  strupr(szTemp2);

  return strcmp(szTemp1,szTemp2);
}
