#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

/*
#include "heap.h"
*/
/*
#ifdef DEBUG
*/

long count=0;
long fcount=0;
FILE *log=NULL;


#define SIGWORD 0xAA55


#ifdef _LEVEL_2_DEBUG_

void my_free(void *tree)
{
  char *adjptr;
  char *fenceptr;
  unsigned long size;

  fenceptr=adjptr=(char*) tree;
  adjptr-=sizeof(unsigned long ); /* Points to the start of size */
  fenceptr+=*((unsigned long *)adjptr);
  size=*((unsigned long*) adjptr);
  adjptr-=sizeof(long); /* Points to the true beginning of the block */
#ifdef _LOG_
  if (log==NULL) log=fopen("log","a+");
#endif
  if (tree==NULL)
  {
    printf("Trying to free NULL pointer!\n");
    exit(1);
  }
#ifdef _LOG_
  fprintf( log, "%p %9.9ld %9.9ld free %ld\n",adjptr,
           *((long *) adjptr), size, fcount);
  if (*( (unsigned int *) fenceptr) != SIGWORD)
    fprintf( log, "%p %9.9ld %9.9ld damaged object %ld\n", adjptr,
             *((unsigned long *) adjptr), size, fcount);
#else
  if (*( (unsigned int *) fenceptr) != SIGWORD)
    printf( "%p %9.9ld %9.9ld damaged object %ld\n", adjptr,
             *((unsigned long *) adjptr), size, fcount);

#endif

  fcount++;
  free ( (void *) adjptr );

  tree=NULL;
#ifdef _LOG_
  fclose(log);
  log=NULL;
#endif
}
void *my_alloc(unsigned long size)
{
  char *temp;
  char *adjptr;
  unsigned long lsize;

  if (count==0 && access("log",00)==0)
  {
    unlink("log");
  }
#ifdef _LOG_
  if (log==NULL) log=fopen("log","a+");
#endif
  /* Add: size + serial nro + size of the block + signature */

  lsize= size+sizeof(long )+sizeof(unsigned long )+
         sizeof(int);
  temp = (char *) malloc(lsize);
#ifdef _LOG_
  fprintf(log,"%p %9.9ld %9.9ld anew\n", temp, count, size);
#endif
  if (temp==NULL)
  {
    printf("Memory allocation error!\n");
    exit(1);
  }
  adjptr=(char *) temp;
  *( (long *) adjptr) = count++;
  adjptr+=sizeof(unsigned long );
  *( (unsigned long *) adjptr)=size;
  temp =(char *) (adjptr+=sizeof(unsigned long ));
  adjptr+=size;
  *( (int *) adjptr)=SIGWORD;

#ifdef _LOG_
  fclose(log);
  log=NULL;
#endif
  return (void*)temp;
}

#endif

#ifdef _LEVEL_1_DEBUG_
void my_free(void *tree)
{
  char *adjptr;

  adjptr=(char*)tree;
  adjptr-=sizeof(long);
  if(log==NULL) log=fopen("log","a+");
  fprintf(log,"%p %9.9ld free %ld\n",adjptr,*((long *)adjptr),fcount++);
  if (*((long *)adjptr)>100000L)
    count=count+1-1;
  free((void*) adjptr);
  fclose(log);
  log=NULL;
}

void* my_alloc(unsigned long size)
{
  void *temp;
  char *adjptr;
  char szLog[255];

  if (count==0 && access("log",00)==0)
  {
    unlink("log");
  }

  if (log==NULL) log=fopen("log","a+");
  temp=(void*)malloc(size+sizeof(long));
  *((long*)temp)=count;
  sprintf(szLog,"%p %9.9ld anew\n",(void far *)temp,count++);
  fprintf(log,szLog);
  adjptr=(char*) temp;
  adjptr+=sizeof(long);
  fclose(log);
  log=NULL;
  return (void*)adjptr;

}

#endif

/*
#endif
*/

#ifdef _DOS_

/* HeapPush includes functions not supported in Ansi C */

void heapPush(char* szFile)

{
  struct farheapinfo info;
  FILE* fp;
  int res;
  char szState[50];

  fp=fopen(szFile,"w");

  if( farheapcheck() == _HEAPCORRUPT )
  {
    fprintf(fp, "Heap is corrupted.\n" );
    abort();
  }
  else
    fprintf(fp, "Heap is OK.\n\n" );

  farheapfillfree(0);

  res = farheapcheckfree(0);
  if (res < 0)
  switch(res)
  {
    case _HEAPCORRUPT:
      fprintf(fp,"Heap corrupted.\n");
      break;

    case _BADVALUE:
      fprintf(fp,"Bad value in free space.\n");
      break;

    default:
      fprintf(fp,"Unknown error.\n");
      break;
  }

  info.ptr = NULL;
  fprintf(fp, "Address    Size   Status  State\n" );
  fprintf(fp, "-------    ----   ------  -----\n" );
  while( farheapwalk( &info ) == _HEAPOK )
  {
    switch( farheapchecknode( info.ptr ))
    {
      case _HEAPEMPTY:
        sprintf(szState, "No heap." );
      break;

      case _HEAPCORRUPT:
        sprintf(szState, "Heap corrupt." );
      break;

      case _BADNODE:
      {
        sprintf(szState, "Bad node." );
      }
      break;

      case _FREEENTRY:
        sprintf(szState, "Free." );
      break;

      case _USEDENTRY:
        sprintf(szState, "Used.");
      break;

      default:
        sprintf(szState, "Unknown return code.");
      break;
    }

    fprintf(fp," %p  %7lu    %s     %s\n", info.ptr, info.size, info.in_use ?
                 "used" : "free", szState );
  }
  fclose(fp);

  return;
}


#endif