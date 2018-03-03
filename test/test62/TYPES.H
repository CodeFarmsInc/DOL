#ifndef ZZint

#ifdef Windows64
#define ZZlong long long
#define ZZint long long
#define ZZfloat long double
#else
#define ZZlong long
#define ZZint int
#define ZZfloat float
#endif

ZZint ZZlongToInt(char *,ZZlong);
unsigned ZZlong ZZptrToLong(char *);
char *ZZintToPtr(ZZint);
ZZint ZZptrToInt(const char *);

#endif // ZZint
