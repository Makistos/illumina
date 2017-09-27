/*************************************************************************
 *
 *N  Module LINKLIST.C
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This module contains functions that make up a singly linked list
 *     data structure.  It is generic in the sense that it can hold any
 *     type of data, including user-defined types and structures.  That
 *     is why you must treat the data element as a void pointer and pass
 *     in its size when inserting into the list.  These routines are
 *     assured of working with "non-pointer" types of data elements.
 *     If you try storing other lists, or structures with pointers hanging
 *     off of them, the results will become unpredictable.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    N/A
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    tLinkedList ll_init();
 *    int ll_empty( tLinkedList list );
 *    tPosition ll_first( tLinkedList list );
 *    tPosition ll_last( tLinkedList list );
 *    tPosition ll_next( tPosition position );
 *    tPosition ll_previous( tPosition position, tLinkedList
 *                  list );
 *    int ll_end( tPosition position );
 *    void ll_element( tPosition position, void *element );
 *    void ll_insert( void *element, unsigned size, tPosition position );
 *    void ll_delete( tPosition position );
 *    void ll_reset( tLinkedList list );
 *    tPosition ll_locate( void *element, tLinkedList list );
 *    void ll_replace( void *element, tPosition position );
 *E
 *************************************************************************/

#include <alloc.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include "stddefs.h"
#include "heap.h"
#include "linklist.h"

/*************************************************************************
 *
 *N  ll_init
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function allocates and initializes a new linked list structure.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    ll_init <output> == (tLinkedList) initialized head of the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
tLinkedList ll_init()
{
   tLinkedList list;

   if ((list = (tLinkedList) my_alloc( sizeof(tCell) ))==NULL) {
      printf("Out of memory in ll_init()\n");
      exit(1);
   }
   list->element = NULL;
   list->nElementSize = 0;
   list->next = NULL;
   return list;
}


/*************************************************************************
 *
 *N  ll_empty
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function TRUE if the list is empty and FALSE if it is not.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    list      <input> == (tLinkedList) linked list being checked.
 *    ll_empty <output> == (int) boolean function result.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
int ll_empty( tLinkedList list )
{
   if (list == NULL) return TRUE;
   if (list->next == NULL)
      return TRUE;
   else
      return FALSE;
}


/*************************************************************************
 *
 *N  ll_first
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function returns the head of the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    list      <input> == (tLinkedList) linked list.
 *    ll_first <output> == (tPosition) head of the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
tPosition ll_first( tLinkedList list )
{
   return ((tPosition) list);
}


/*************************************************************************
 *
 *N  ll_last
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function returns *THE* last position in the list, which is
 *     not useable.  Use ll_previous to get to the las USEABLE link in
 *     the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    list     <input> == (tLinkedList) linked list.
 *    ll_last <output> == (tPosition) tail of the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
tPosition ll_last( tLinkedList list )
{
   tPosition p;

   p = (tPosition) list;
   while (p->next != NULL)
      p = p->next;
   return p;
}


/*************************************************************************
 *
 *N  ll_next
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function returns the next position in the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    position <input> == (tPosition) current position in the list.
 *    ll_next <output> == (tPosition) next position in the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
tPosition ll_next( tPosition position )
{
   return(position->next);
}


/*************************************************************************
 *
 *N  ll_previous
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function returns the previous position in the list.  Note:
 *     This is a singly linked list -> no backward pointer -> this
 *     operation is relatively inefficient.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    position     <input> == (tPosition) current position.
 *    list         <input> == (tLinkedList) linked list.
 *    ll_previous <output> == (tPosition) previous position in the list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
tPosition ll_previous( tPosition    position,
			   tLinkedList list )
{
   tPosition p;

   if (position==list) return(position);
   p = list;
   while (p->next != position)
      p = p->next;
   return(p);
}


/*************************************************************************
 *
 *N  ll_end
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function determines if the given position is at the end of the
 *     list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    position <input> == (tPosition) current position in the list.
 *    ll_end  <output> == (int) TRUE  -- if position is the end of the list.
 *                              FALSE -- if not.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
int ll_end( tPosition position )
{
   if (position == NULL)
      return(TRUE);
   else {
      if (position->next == NULL)
	 return(TRUE);
      else
	 return(FALSE);
   }
}


/*************************************************************************
 *
 *N  ll_element
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function copies the element at position in the list into the
 *     contents of element.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    position <input> == (tPosition) position in the list.
 *    element <output> == (void *) pointer to the element data.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
void ll_element( tPosition position,
		 void         *element )
{
   movmem(position->next->element,element,position->next->nElementSize);
}

/*************************************************************************
 *
 *N  ll_insert
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function inserts a new cell into the list at position that will
 *     contain the data pointed to by element.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    element  <input> == (void *) pointer to the data element to insert.
 *    size     <input> == (unsigned) size of the data element.
 *    position <input> == (tPosition) position to insert the new cell.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
void ll_insert( void      *element,
		            unsigned  size,
		            tPosition position )
{
   tPosition temp;

   if ((temp = (tPosition) my_alloc( sizeof(tCell) )) == NULL) {
      printf("out of memory\n");
      abort();
   }
   temp->next = position->next;
   position->next = temp;
   temp->nElementSize = size;
   if ((temp->element = my_alloc( size ))==NULL) {
      printf("out of memory\n");
      abort();
   }
   movmem(element,temp->element,size);

}


/*************************************************************************
 *
 *N  ll_delete
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function deletes and disposes of a cell from the linked list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    position <input> == (tPosition) position in the list to delete.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
void ll_delete( tPosition position )
{
   tPosition    p;

   if (position != NULL) {  /* Cut the element out of the chain */
      p = position->next;
      position->next = p->next;
      my_free( p->element );
      my_free( p );
   }
}




/*************************************************************************
 *
 *N  ll_reset
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function empties out a linked list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    list <inout> == (tLinkedList) linked list to be emptied.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    void ll_delete( tPosition position );
 *    int ll_empty( tLinkedList list );
 *E
 *************************************************************************/
void ll_reset( tLinkedList list )
{
   while (! ll_empty(list))
      ll_delete(ll_first(list));
   my_free(list);
   list = NULL;
}



/*************************************************************************
 *
 *N  ll_locate
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function locates a position in the list by comparing data.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    element <input> == (void *) pointer to the data element to locate.
 *    list    <input> == (tLinkedList) linked list.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
tPosition ll_locate( void             *element,
			 tLinkedList list )
{
   tPosition p;

   p = list;
   while (p->next != NULL) {
      if ( memcmp(p->next->element,element,p->next->nElementSize) == 0 )
	 return p;
      else
	 p = p->next;
   }
   return NULL;
}


/*************************************************************************
 *
 *N  ll_replace
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Purpose:
 *P
 *     This function replaces an element in the linked list at the given
 *     position.  WARNING:  The new data element must be the same size as
 *     the previous data element or you will get some rather INTERESTING
 *     results.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Parameters:
 *A
 *    element  <input> == (void *) data element to replace existing data.
 *    position <input> == (tPosition) position in the list to replace
 *                        the data.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   History:
 *H
 *    Barry Michaels   Feb. 1990                      DOS Turbo C
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   External Variables:
 *X
 *    None
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *   Functions Called:
 *F
 *    None
 *E
 *************************************************************************/
void ll_replace( void          *element,
		 tPosition position )
{
   movmem(element,position->next->element,position->next->nElementSize);
}



