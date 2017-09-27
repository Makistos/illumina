#define DEBUG 0

/*
define _LEVEL_1_DEBUG_
*/
/*
#define _LEVEL_2_DEBUG_
*/
#ifndef HWRAPPER
#define HWRAPPER
#if DEBUG

void my_free(void *tree);
void* my_alloc(unsigned long size);

/*
#define malloc(x) my_alloc(x)
#define free(x) my_free(x)
*/

#else
/* The DEBUG flag is not defined, change my_alloc:s to malloc:s and
	my_free:s to free:s
*/
#include <alloc.h>

#define my_alloc(x) malloc(x)
#define my_free(x)  free(x)

#endif
#endif /* HWRAPPER */

#ifndef __heap_h__
#define __heap_h__


void heapPush(char* szFile);

#endif /* __heap_h__ */