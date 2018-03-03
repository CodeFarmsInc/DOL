
#ifndef ZZ_ANSI
void ZZmsg(),ZZmsgS(),ZZmsgD(),ZZmsgC();
void ZZmsgSS(),ZZmsgDD(),ZZmsgSD();
void ZZmsgSSS(),ZZmsgDDD(),ZZMsgSSD(),ZZmsgSDD();
void ZZmsgSSDD(),ZZmsgSDDD();
void ZZmsgSL();
#endif
#ifdef ZZ_ANSI
void ZZmsg(ZZint i),ZZmsgS(ZZint i,const char *s),ZZmsgD(ZZint i,ZZint k1),
     ZZmsgC(ZZint i,const char *c);
void ZZmsgSS(ZZint i,const char *s1,const char *s2),ZZmsgDD(ZZint i,ZZint k1,ZZint k2),
     ZZmsgSD(ZZint i,const char *s,ZZint k);
void ZZmsgSSS(ZZint i,const char *s1,const char *s2,const char *s3),
     ZZmsgDDD(ZZint i,ZZint k1,ZZint k2,ZZint k3),
     ZZmsgSSD(ZZint i,const char *p1,const char *p2,ZZint k),
     ZZmsgSDD(ZZint i,const char *s,ZZint k1,ZZint k2);
void ZZmsgSSDD(ZZint i,const char *s1,const char *s2,ZZint k1,ZZint k2),
     ZZmsgSDDD(ZZint i,const char *s,ZZint k1,ZZint k2,ZZint k3);
void ZZmsgSL(ZZint i,const char *s,ZZlong l);
#endif
