/*************************************************************************
 *
 *N Module DATABASE
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This is a database server for Unix. The database is made of fixed-
 *    size records. The index for this file is kept in memory. The key
 *    to a table is of type long. The index holds the keys and positions
 *    of each record in the database file.
 *
 *    This server also includes pretty good ways of handling exceptions,
 *    like missing files etc.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Compatibility
 *C
 *    This module should be ANSI C compatible.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994
 *E
 *************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <io.h>
#include <time.h>

#include "heap.h"
#include "btree.h"
#include "db.h"

/* Function prototypes */
int openIndex(char *szIdxName, bnode *root);
long getPos(long num, bnode *first);
void *getInfo(char *szDbName, long pos,long size);
long putInfo(char *szDbName, void* info, long pos, long size);
int addToIndex(long num, long pos, bnode *curr);

/*************************************************************************
 *
 *N openIndex
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function reads the index file from the disk.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out>   == (int) 0 if successfull. -1 if no index file. 1 if
 *                       index empty.
 *    szIdxName <in> == (char *) Name of the index file.
 *    first <inout>  == (iNode *) First node in index list.
 *    curr <inout>   == (iNode *) Current (last) node in index list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    my_alloc      HEAP.H
 *    btree_insert  BTREE.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/

int openIndex(char *szIdxName, bnode *root)
{
  FILE* fp;
  long key,data;

  fp=fopen(szIdxName,"r");
  if (!fp)
  {
    printf("No index file! (%s)\n",szIdxName);
    return -1;
  }

  rewind(fp);

  if (feof(fp))
  {
    printf("Index file empty! (%s)\n",szIdxName);
    return -2;
  }

  /* Read the first record */

  fread(&key,sizeof(long),1,fp);
  fread(&data,sizeof(long),1,fp);

  btree_insert(root,&data,key);

  while(!feof(fp))
  {

   fread(&key,sizeof(long),1,fp);
	 fread(&data,sizeof(long),1,fp);
   btree_insert(root,&data,key);
  }

  fclose(fp);
  return 0;
}

/*************************************************************************
 *
 *N flushIndex
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function writes the index to a file.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out>   == (int) 0, if operation successfull,
 *                            -1 if couldn't open file for writing.
 *    szIdxName <in> == (char *) file name.
 *    first <in>     == (iNode *) first node in index list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    btree_next  BTREE.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/
int flushIndex(char *szIdxName,bnode *root)
{

  FILE *fp;
  bnode *tmp;
  long num;

  fp=fopen(szIdxName,"w");

  if (!fp)
  {
    printf("Can't open index file %s for writing!\n",szIdxName);
    return -1;
  }

  tmp=root;
  while (tmp!=NULL)
  {
    fwrite(&(tmp->key),sizeof(long),1,fp);
    fwrite(&(tmp->data),sizeof(long),1,fp);
    tmp=(bnode*)btree_next(tmp);
  }

  fclose(fp);

  return 0;
}

/*************************************************************************
 *
 *N closeIndex
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function closes the index structure. It writes the index to
 *    disk and frees all allocated memory.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out>   == (int)
 *    szIdxName <in> == (char *) Index file name.
 *    first <in>     == (iNode *) First node in index list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    my_free     HEAP.H
 *    btree_nuke  BTREE.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/
int closeIndex(char *szIdxName, bnode *root)
{
  int retval;

  retval=flushIndex(szIdxName,root);

  btree_nuke(root);

  return retval;
}

/*************************************************************************
 *
 *N getPos
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function searches through the index to find the position for
 *    the database record.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out> == (long) Record's position in database file. If no
 *                           match, returns -1.
 *    num <in>     == (long) key.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    btree_search BTREE.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/

long getPos(long num, bnode *root)
{
  long pos;

  btree_search(root,&pos,num);

  if (pos==NULL)
    pos=-1;

  return pos;
}

/*************************************************************************
 *
 *N getInfo
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    Searches the info from the database file with fseek. It also
 *    allocates memory for the info, so it must be freed when no longer
 *    needed.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *P
 *    return <out>  == (void *) the record.
 *    szDbName <in> == (char *) name of the database file.
 *    pos <in>      == (long) record's position in the db file.
 *    size <in>     == (long) size of the record to be read.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    my_alloc  HEAP.H
 *    my_free   HEAP.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/
void *getInfo(char *szDbName, long pos, long size)
{
  FILE *fp;
  void *tmp;
  int len;

  tmp=(void*)my_alloc(size);

  fp=fopen(szDbName,"r");

  if (!fp)
  {
    printf("Can't open database file %s for reading!\n",szDbName);
    my_free(tmp);
    return NULL;
  }

  /* Search the right record */
  fseek(fp,pos,0);

  len=fread(&tmp,size,1,fp);

  if (len!=size)
  {
    printf("Error reading data from %s!\n",szDbName);
    my_free(tmp);
    fclose(fp);
    return NULL;
  }

  fclose(fp);

  return tmp;
}

/*************************************************************************
 *
 *N putInfo
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function writes the record to the database file. The record is
 *    written in place pos or if it's -1, into the end of the file.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *P
 *    return <out>  == (long) position of the record in the file.
 *    szDbName <in> == (char *) name of the database.
 *    info <in>     == (void *) info to be written.
 *    size <in>     == (long) size of record.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/

long putInfo(char *szDbName, void* info,long pos, long size)
{
  FILE *fp;
  int len;
  fpos_t fpos;

  fp=fopen(szDbName,"r");

  if (!fp)
  {
	 printf("Can't open database file %s for writing!\n",szDbName);
	 return -1;
  }

  /* Go to end of file */

  if (pos==-1)
	 fseek(fp,0,2);

  else fseek(fp,pos,0);

  fgetpos(fp,&fpos);

  len=fwrite(&info,size,1,fp);

  if (len!=size)
  {
	 printf("Error writing data to %s!\n",szDbName);
	 fclose(fp);
	 return -2;
  }

  fclose(fp);

  return fpos;
}

/*************************************************************************
 *
 *N createIndex
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function creates a new index if the old one has been destroyed.
 *    It does this by reading the database file.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    szDbname  == (char *) Database file name.
 *    szIdxName == (char *) Index file name.
 *    recSize   == (int) Size of each record.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    btree_init()    HEAP.H
 *    btree_insert()  HEAP.H
 *    btree_nuke()    HEAP.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Oct 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/
void createIndex(char *szDbName,char *szIdxName,int recSize)
{
  FILE *fp;
  bnode *root;
  long key;
  long pos;

  fp=fopen(szDbName,"r");

  root=btree_init(); /* Init tree */

  rewind(fp);

  while(!feof)
  {
    fread(&key,sizeof(long),1,fp); /* Read key */
    pos=fgetpos(fp,&pos); /* Get position */
    fseek(fp,recSize-sizeof(long),1); /* Go forward to start of next block */
    btree_insert(root,&pos,key); /* Insert this into the index tree */
  }

  fclose(fp);

  flushIndex(szIdxName,root); /* Write index to disk */

  btree_nuke(root); /* Delete tree */
}

/*************************************************************************
 *
 *N addToIndex
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This function adds an index entry to the index structure. It
 *    allocates memory to it, so it must be freed when no longer needed.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out> == See btree_insert.
 *    num          == (long) key.
 *    pos          == (long) Record's position.
 *    curr         == (bnode *) Current node in index structure.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    btree_insert BTREE.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Oct 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/
int addToIndex(long num, long pos, bnode *node)
{
  int retval;

  retval=btree_insert(node, &pos, num);

  return retval;
}

void restoreBackup(char *szTempFile, char *szDbName)
{



}

/*************************************************************************
 *
 *N main
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This is the main function for the database server. This function
 *    initializes the necessary data structures and handles possible
 *    exceptions (files missing etc). After that it starts reading
 *    the socket waiting for commands.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *P
 *    1st parameter == Database name
 *    2nd parameter == Index name
 *    3rd parameter == Size of a record
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    btree_init  BTREE.H
 *    btree_nuke  BTREE.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Oct 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/
void main(int argc, char argv[])
{
	long plNum,pos,size;
	void *data;
  int cmd;
  int done;
  int res,key;
  bnode *root;
  time_t indexTimer;
  char szIdxName[20];
  char szDbName[20];
  char szTemp[80];

  if (argc<3)
  {
    strcpy(szIdxName,"illuidx");
    strcpy(szDbName,"illudb");
  }
  else
  {
    *szDbName=argv[1];
    *szIdxName=argv[2];
    if ((size=atoi(&argv[3]))==0)
    {
      printf("Invalid record size %s. Bailing out.\n",argv[3]);
      abort();
    }
  }

  root=btree_init();  /* Init tree */
	res=openIndex(szIdxName,root); /* Open index */

  done=0;

  /* The following checks for missing files. */

  if (res!=0)
  {
    /* Index is missing */
    if (access(szDbName,00)!=0) /* Check for database file */
    {
      /* The database is missing */

      strcpy(szTemp,szDbName);
      strcat(szTemp,".bak");

      /* The backup file's name is database_name.bak */

      if (access(szTemp,00)==0) /* Check for backup file */
      {
        printf("No database! Restore backup?\n");
        key=getch();
        if (key=='y' || key=='Y')
          restoreBackup(szTemp,szDbName);

      }
      else
      {
        /* Backup is missing */
        printf("No index, database or backup! Continue?\n");
        key=getch();
        if (key=='n' || key=='N')
          done=1;
      }
    }
    /* Database exists, but no index... */
    printf("No index. Creating new index from database...\n");
    createIndex(szDbName,szIdxName,size);
    res=openIndex(szIdxName,root);
    if (res!=0)
    {
      printf("Creation failed. Bailing out.\n");
      abort();
    }
  }

  if (access(szDbName,00)!=0)
  {
    /* The database is missing */

    strcpy(szTemp,szDbName);
    strcat(szTemp,".bak");

    /* The backup file's name is database_name.bak */

    if (access(szTemp,00)==0)
    {
      printf("No database! Restore backup?\n");
      key=getch();
      if (key=='y' || key=='Y')
        restoreBackup(szTemp,szDbName);

    }
    else
    {
      /* Backup is missing */
      printf("No index, database or backup! Continue?\n");
      key=getch();
      if (key=='n' || key=='N')
        done=1;
    }
  }

  indexTimer=time(NULL); /* Get starting time */

  /* Main loop. Should be easy to understand. */

	while (!done)
	{
    if (time(NULL)-indexTimer > 300)
    {
      /* Save index every 5 minutes */
      flushIndex(szIdxName,root);  /* Save index to disk */
      indexTimer=time(NULL); /* Get new time */
    }

	  /* Read socket */

	  switch (cmd)
	  {
	    case GETDATA :
        /* Request for info */
		    pos=getPos(plNum,root);
		    data=getInfo(szDbName,pos,size);
        /* Send data to socket */
		    free(data);
		  break;

	    case PUTDATA :
        /* Request to write data */
        pos=putInfo(szDbName,data,pos,size);
        /* Send acknowledgement */
      break;

      case FINISH :
        /* Request to quit server */
        done=1;
      break;

      default : /* Wait */ ;
	  }
	}

	closeIndex(szIdxName,root);

  btree_nuke(root);

}