char initmcga(void);
void closemcga(void);
void setclearlength(unsigned length);
void setdrawarea(int x,int y,int width,int height); // x=0-79

void loadlatches(char color);
void restorenormalmode(void);

void clearscreen(void);
void putpixel(int x,int y,char color);
void putpixel(int x,int y);
void clippedpixel(int x,int y,char color);
void drawline(int x1,int y1,int x2,int y2);
void clippedline(int x1,int y1,int x2,int y2);

void setdrawmode(char mode);
void setbitmask(char mask);
void setplanes(char planes);

void reset03c0(void);
void set03c0(char index,char data);

void selectcolor(char color);
void setcolorvalues(char r,char g,char b);

int loadgrf(const char *);