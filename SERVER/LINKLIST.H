
/* LINKLIST.H */

#ifndef __LINKLIST_H__

#define __LINKLIST_H__   1

/* Linked list structure */
typedef struct tLinkedListCell
{
   void       	           *element;
   unsigned                nElementSize;
   struct tLinkedListCell  *next;
} tCell, *tLinkedList, *tPosition;

/* Functions: */

tLinkedList ll_init(void);

int ll_empty( tLinkedList list );

tPosition ll_first( tLinkedList list );

#define LL_FIRST(list) (tPosition)list

tPosition ll_last( tLinkedList list );

tPosition ll_next( tPosition position );

#define LL_NEXT(position) position->next

tPosition ll_previous( tPosition position,
			                 tLinkedList list );

int ll_end( tPosition position );

void ll_element( tPosition position,
		             void *element );

void ll_insert( void  *element,
		            unsigned size,
		            tPosition position );

void ll_delete( tPosition position );

void ll_reset( tLinkedList list );

tPosition ll_locate( void *element,
			               tLinkedList list );

void ll_replace( void *element,
		             tPosition position );

#endif
