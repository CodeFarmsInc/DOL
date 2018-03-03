#ifndef ZZint

#ifdef Windows64
#define ZZlong long long
#define ZZint long long
#define ZZfloat long double
#define ZZsize unsigned long long
#else
#define ZZlong long
#define ZZint int
#define ZZfloat float
#define ZZsize unsigned long 
#endif

ZZint ZZlongToInt(char *,ZZlong);
unsigned ZZlong ZZptrToLong(char *);
char *ZZintToPtr(ZZint);
ZZint ZZptrToInt(const char *);
ZZsize ZZptrToSize(char *);
char *ZZsizeToPtr(ZZsize);

#define ZZ_MAXU ((ZZsize)(-1) - 1)

#endif // ZZint

#ifdef AMDAHL
#define ZZvoidS ZZint
#else
#define ZZvoidS void
#endif
