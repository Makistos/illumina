// Def.h - Global defines&some variables


//-- Variables defined in INPUT.CPP ------------------------------------------
extern void interrupt (**vects)(...);

//-- Variables defined in MCGA.CPP -------------------------------------------
extern unsigned clearlength;
extern unsigned screenseg;
extern unsigned screenofs;
extern unsigned drawareastart;
extern int screenxlimit;
extern int screenylimit;

inline int SGN(int i) { return (i<0)?-1:(!!i); }
inline int ABS(int i) { return (i<0)?-i:i; }
inline void EXCHG(int *a,int *b) { int tmp=*a; *a=*b; *b=tmp; }
