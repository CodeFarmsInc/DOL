#define msg ZZmsgS
#define getBlock (char *)ZZnewObj
#define letBlock ZZdelObj
#define formPage ZZformPage
#define ioPage ZZioPage
#define closePager ZZclosePager

#ifdef ZZ_ANSI
void *ZZnewObj(ZZint,ZZint);
ZZint ZZdelObj(char *);
#else
void *ZZnewObj();
ZZint ZZdelObj();
#endif
