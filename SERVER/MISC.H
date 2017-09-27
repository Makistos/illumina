#ifndef __misc_h__
#define __misc_h__

#ifndef DEBUG
void *my_alloc(unsigned long size);
#endif

void strupr(char *str);

int stricmp(char *s1, char *s2);

#endif