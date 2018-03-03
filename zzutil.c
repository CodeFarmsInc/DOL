/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

#include <stdio.h>
#include "zzintern.h"
#ifdef UNIX
#include "lib/types.h"
#else
#include "lib\types.h"
#endif

/* functions in file zzutil.c */
/* -------------------------------------------------------------- */
#ifdef ZZ_ANSI
int getMaster(char *path,int warn);
int aOrder(char *p1,char *p2);
char *binCmp(char *list,int strSize,int offset,int num,char *word);

#if defined(SUN) || defined(LINUX)
extern "C" 
#endif
int genSortFun(const void *p1,const void *p2);

int setBuckets(char *ptr,int n,int size,int offset);
int buckFun(char *p);
void jsCrypt(char *inpName,char *outName,int type,char *c,int autoFlg,int tab);
FILE *myopen(char *a,const char *b);
void mvFile(char *oldF,char *newF);
void delFile(char *name);
int cmpFiles(char *name1,char *name2);
void cpFile(FILE *inFile,FILE *outFile,char *id);
void plainCopy(char *name,FILE *outFile);
char *ZZgetPath(char *progr,char *name);
void filterOut(FILE *mFile,FILE *outFile);
ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSz);
int ZZbindPtrs(char *obj,int newTp,int newSize,int vUpd,int blast);
ZZvoidS *ZZnewBit(ZZsize size) ;
#ifndef GNU
void *malloc(size_t size);
#endif

#else
int getMaster();
int aOrder();
char *binCmp();
int genSortFun();
int setBuckets();
int buckFun();
void jsCrypt();
FILE *myopen();
void mvFile();
void delFile();
int cmpFiles();
void cpFile();
void plainCopy();
char *ZZgetPath();
void filterOut();
int ZZioFunction();
int ZZbindPtrs();
void *ZZnewBit();
void *malloc();
#endif

/* ZZutil.c -
 * utility functions common to ZZprep and the its documentation package 
 */

/* ---------------------------------------------------------------------- */
/* read file zzmaster with the control table of organizations and functions,
 * set and allocate the main control arrays and their sizes.
 */
#ifdef ZZ_ANSI
int getMaster(char *path,int warn)

#else
int getMaster(path,warn)
char *path;  /* path to the directory where macros and zzmaster are */
int warn;    /* 1=issue warnings, 0=do not */
/* returns: 0=normal, 1=allocation or file problems */
#endif
{
    FILE *ff;
    char *fName,n1[BUFSIZE],n2[BUFSIZE],n3[BUFSIZE],n4[BUFSIZE];
    int i,k,kk,count;
    ZZfunction *fp;

    /* here comes the normal code of getMaster() */
    fName=(char *)malloc(strlen(path)+strlen(MACRO_PATH)+strlen(ZZmaster)+1);
    strcpy(fName,path);
    strcat(fName,MACRO_PATH);
    strcat(fName,ZZmaster);

    /* read the file first to determine the size of each section */
    ff=myopen(fName,"r");
    if(!ff){ZZmsg(4); return(1);} /* problem with internal file in getMaster */
    i=count=nOrg=nHier=nFun=nPtr=nSup=0;
    while(fgets(buff,BUFSIZE,ff)){
	sscanf(buff,"%s",n1);
	if(!strcmp(n1,"ZZorganization"))  {i=0; count=1;}
	else if(!strcmp(n1,"ZZpointer"))  {i=1; count=1;}
	else if(!strcmp(n1,"ZZfunction")) {i=2; count=1;}
	else if(!strcmp(n1,"ZZsupport"))  {i=3; count=1;}
	else if(!strcmp(n1,"ZZhierarchy")){i=4; count=1;}
	else if(!strcmp(n1,"}"))count=0;
	else if(count){
	    switch(i) {
		case 0: nOrg++; break;
		case 1: nPtr++; break;
		case 2: nFun++; break;
		case 3: nSup++; break;
		case 4: nHier++; break;
	    }
	}
    }
    fclose(ff);
    if(nFun<=0){ZZmsg(5); return(6);} /* empty master table */

    /* allocate the global tables */
    ZZorg=(ZZorganization *)malloc((nOrg+1)*sizeof(struct ZZorganization));
    ZZptr=(ZZpointer *)malloc((nPtr+1)*sizeof(struct ZZpointer));
    ZZfun=(ZZfunction *)malloc((nFun+1)*sizeof(struct ZZfunction));
    ZZsup=(ZZsupport *)malloc((nSup+1)*sizeof(struct ZZsupport));
    ZZhier=(ZZhierarchy *)malloc((nHier+1)*sizeof(struct ZZhierarchy));
    if(!ZZorg || !ZZptr || !ZZfun || !ZZsup || !ZZhier){
        ZZmsg(6); /* problem to allocate master tables */
	return(2);
    }

    /* read in the global tables */
    ff=myopen(fName,"r");
    if(!ff){ZZmsg(4); return(1);} /* problem with internal file in getMaster */
    i=k=count=0;
    while(fgets(buff,BUFSIZE,ff)){
	sscanf(buff,"%s",n1);
	if(!strcmp(n1,"ZZorganization"))  {i=0; count=1;}
	else if(!strcmp(n1,"ZZpointer"))  {i=1; count=1;}
	else if(!strcmp(n1,"ZZfunction")) {i=2; count=1;}
	else if(!strcmp(n1,"ZZsupport"))  {i=3; count=1;}
	else if(!strcmp(n1,"ZZhierarchy")){i=4; count=1;}
	else if(!strcmp(n1,"}"))         {k=0; count=0;}
	else if(count){
	    switch(i) {
		case 0: 
		    if(k>=nOrg){
                        ZZmsgSD(0,"nOrg",nOrg); /* internal overflow */
			return(3);
		    }
		    sscanf(buff,"%d %s %d %d %d", &(ZZorg[k].ind),n1,
		    &(ZZorg[k].ptrInd),&(ZZorg[k].top),&(ZZorg[k].nInp));
                    if(warn && k!=ZZorg[k].ind)ZZmsgSD(2,"ZZorganization",k);
		    ZZorg[k].name=(char *)malloc(strlen(n1)+1);
		    if(!(ZZorg[k].name)){
                        ZZmsgS(7,"getMaster"); /* name allocation problem in */
			return(4);
		    }
		    strcpy(ZZorg[k].name,n1);
		    k++;
		    break;
		case 1:
		    if(k>=nPtr){
                        ZZmsgSD(0,"nPtr",nPtr); /* internal overflow */
			return(3);
		    }
		    sscanf(buff,"%d %d %d %d %c %s",&(ZZptr[k].ind),
		            &(ZZptr[k].strToUse),&(ZZptr[k].strToPoint),
		            &(ZZptr[k].aSize),&(ZZptr[k].aType),n1);
                    if(k!=ZZptr[k].ind)ZZmsgSD(2,"ZZpointer",k);
		    ZZptr[k].code=(char *)malloc(strlen(n1)+1);
		    if(!(ZZptr[k].code)){
                        ZZmsgS(7,"getMaster"); /* name allocation problem in */
			return(4);
		    }
		    strcpy(ZZptr[k].code,n1);
		    k++;
		    break;
		case 2:
		    if(k>=nFun){
                        ZZmsgSD(0,"nFun",nFun); /* internal overflow */
			return(3);
		    }
		    sscanf(buff,"%s %s %s %d %d %c",n1,n2,n3,&(ZZfun[k].orgInd),
		    &(ZZfun[k].sup),&(ZZfun[k].create));
		    ZZfun[k].sName=(char *)malloc(strlen(n1)+1);
		    ZZfun[k].name=(char *)malloc(strlen(n2)+1);
		    ZZfun[k].fileName=(char *)malloc(strlen(n3)+1);
		    if(!(ZZfun[k].sName) || !(ZZfun[k].name) 
					 || !(ZZfun[k].fileName)){
                        ZZmsgS(7,"getMaster"); /* name allocation problem in */
			return(4);
		    }
		    strcpy(ZZfun[k].sName,n1);
		    strcpy(ZZfun[k].name,n2);
		    strcpy(ZZfun[k].fileName,n3);
		    k++;
		    break;
		case 3:
		    if(k>=nSup){
                        ZZmsgSD(0,"nSup",nSup); /* internal overflow */
			return(3);
		    }
		    sscanf(buff,"%d %d %s",&(ZZsup[k].ind),&(ZZsup[k].next),n1);
                    if(k!=ZZsup[k].ind)ZZmsgSD(2,"ZZsupport",k);
		    ZZsup[k].fileName=(char *)malloc(strlen(n1)+1);
		    if(!(ZZsup[k].fileName)){
                        ZZmsgS(7,"getMaster"); /* name allocation problem in */
			return(4);
		    }
		    strcpy(ZZsup[k].fileName,n1);
		    k++;
		    break;
                case 4:
                    if(k>=nHier){
                        ZZmsgSD(0,"nHier",nHier); /* internal overflow */
			return(4);
		    }
		    sscanf(buff,"%s %s %s %s",n1,n2,n3,n4);
                    ZZhier[k].parent=ZZhier[k].child=NULL;
                    for(kk=0;kk<nFun;kk++){
                        fp= &(ZZfun[kk]);
                        if(!strcmp(fp->name,n1) || !strcmp(fp->sName,n1))
                                                     ZZhier[k].parent=fp;
                        if(!strcmp(fp->name,n2) || !strcmp(fp->sName,n2))
                                                     ZZhier[k].child=fp;
                    }
                    if(!(ZZhier[k].parent) || !(ZZhier[k].child)){
                        ZZmsgSS(7,n1,n2); /* hierarchy error in zzmaster */
                        return(4);
                    }
                    ZZhier[k].prefix=(char*)malloc(strlen(n3)+1);
                    ZZhier[k].sequence=(char*)malloc(strlen(n4)+1);
                    if(!(ZZhier[k].prefix) || !(ZZhier[k].sequence)){
                        ZZmsg(7); /* problem in allocation of ZZhierarchy */
                        return(4);
                    }
                    strcpy(ZZhier[k].prefix,n3);
                    strcpy(ZZhier[k].sequence,n4);
                    break;
	    }
	}
    }
    fclose(ff);


    /* check internal links between sections */
    for(i=0;i<nOrg;i++){
	if(ZZorg[i].ptrInd<0 || ZZorg[i].ptrInd>=nPtr ||
	   ZZorg[i].top<0    || ZZorg[i].top>=nPtr ||
	   ZZorg[i].ptrInd>ZZorg[i].top){
	     ZZmsg(8); /* master table error - from org. to its pointers */
	     return(5);
	}
    }
    for(i=0;i<nFun;i++){
	if(ZZfun[i].sup< -1 || ZZfun[i].sup>=nSup){
	     ZZmsg(9); /* master table error - from function to its support */
	     return(5);
	}
    }
    for(i=0;i<nSup;i++){
	if(ZZsup[i].next< -1 || ZZsup[i].next>=nSup){
	     ZZmsg(10); /* master table error - next in ZZsupport */
	     return(5);
	}
    }

    /* fill in the end records */
    ZZorg[nOrg].ind= -1;
    ZZptr[nPtr].ind= -1;
    ZZfun[nFun].used='e';
    ZZsup[nSup].ind= -1; ZZsup[nSup].used='e';

    /* initialize some internal fields */
    for(i=0;i<nOrg;i++)ZZorg[i].used=BLANK;
    for(i=0;i<nFun;i++){ZZfun[i].used=BLANK; ZZfun[i].inst=NULL;}
    for(i=0;i<nSup;i++)ZZsup[i].used=BLANK;

    return(0);
}
/* ---------------------------------------------------------------------- */
/* fast determination of the alphabetical order, returns 0 if equal */
#ifdef ZZ_ANSI
int aOrder(char *p1,char *p2)

#else
int aOrder(p1,p2)
char *p1,*p2; /* two strings */
/* returns -1=p1 shorter or alphabetically smaller,
 *          0=equal, 1=p2 shorter or alphabetically smaller */
#endif
{
    for(;(*p1)!=END && (*p2)!=END;p1++,p2++){
	if((*p1)<(*p2))return(-1);
	if((*p1)>(*p2))return(1);
    }
    if((*p1)==(*p2))return(0);
    if((*p2)!=END)return(-1);
    return(1);
}
/* ---------------------------------------------------------------------- */
/* General binary search using names. Can be used for different structures
 * and their members.
 *
 * Preconditions: input list sorted by bucket and then the offset field
 */
#ifdef ZZ_ANSI
char *binCmp(char *list,int strSize,int offset,int num,char *word)

#else
char *binCmp(list,strSize,offset,num,word)
char *list;  /* list of given structures, sorted by the selected member */
int strSize; /* size of the structure in characters */
int offset;  /* number of characters inside the structure to the member */
int num;     /* total number of structures on the list */
char *word;  /* word to search for */
/* returns pointer to the structure found, NULL if not found */
#endif
{
    int i1,i2,k,m,n;
    char **p,*entry;

    /* first find the range of indeces for this bucket */
    m=buckFun(word);
    if(m>0){ /* buckFun() is operational */
        i2=ZZbucket[m];
        i1=ZZbucket[m-1]+1;
        if(i1>i2)return(NULL);
    }
    else { i1=0; i2=num;} /* go just by binary search */

    /* search for the offset-ed members */
    entry=list+offset; 

    n=i1*strSize;
    p=(char**)(entry+n);
    m=aOrder(*p,word);
    if(m>0)return(NULL);
    if(m==0)return(list+n);
    if(i1==i2)return(NULL);

    n=i2*strSize;
    p=(char**)(entry+n);
    m=aOrder(*p,word);
    if(m<0)return(0);
    if(m==0)return(list+n);

    while((k=(i1+i2)/2)>i1){
        n=k*strSize;
        p=(char**)(entry+n);
        m=aOrder(*p,word);
        if(m<0)     i1=k;
	else if(m>0)i2=k;
        else        return(list+n);
    }
    return(NULL);
}
/* ---------------------------------------------------------------------- */
/* General function to support qsort() which works on names
 * inside different structures.
 * Global variable ZZoffset must be set to provide internal offset.
 * Global array ZZbucket improves the speed of access
 */
#ifdef ZZ_ANSI

#ifdef SOLARIS
extern "C" 
#endif
int genSortFun(const void *p1,const void *p2)

#else
int genSortFun(p1,p2)
void *p1,*p2;
#endif
{
    int m,i1,i2;
    char**pp1,**pp2;

    pp1=(char**)((char *)p1+ZZoffset);
    pp2=(char**)((char *)p2+ZZoffset);
    i1=buckFun(*pp1);
    i2=buckFun(*pp2);
    if(i1<i2)return(-1);
    if(i1>i2)return(1);
    m=aOrder(*pp1,*pp2);
    if(m<0)return(-1);
    if(m>0)return(1);
    return(0);
}
/* ---------------------------------------------------------------------- */
/* set the buckets to the index leading into ZZfun();
 * ZZbucket[k] is the highest index i such that the length of ZZfun[i].name
 * is exactly k characters.
 */
#ifdef ZZ_ANSI
int setBuckets(char *ptr,int n,int size,int offset)

#else
int setBuckets(ptr,n,size,offset)
char *ptr;  /* pointer to the beginning of the first structure */
int n;      /* number of structures in the array */
int size;   /* size of one structure in characters */
int offset; /* offset of the name inside the structure */
#endif
{
    int i,k;
    char *p,**s;

    for(i=0;i<ZZ_BUCK;i++)ZZbucket[i]= -1;
    for(i=0,p=ptr+offset;i<n;i++,p+=size){
	s=(char**)p;
	k=buckFun(*s);
	ZZbucket[k]=MAX(ZZbucket[k],i);
    }
    /* some buckets may be empty... */
    for(i=1;i<ZZ_BUCK;i++)ZZbucket[i]=MAX(ZZbucket[i-1],ZZbucket[i]);
    return(0);
}
/* ---------------------------------------------------------------------- */
/* bucket calculation - if you want to disable this function,
 * return always 0 
 */
#ifdef ZZ_ANSI
int buckFun(char *p)

#else
int buckFun(p)
char *p; /* pointer to a name */
#endif
{
    int i;

    i=strlen(p);
    if(i<0)i=0;
    if(i>=ZZ_BUCK)i=ZZ_BUCK-1;
    return(i);
}
/* ---------------------------------------------------------------------- */
/* A dummy program to replace the encrypting algorithm JStCrypt() below */

#define BUFS 512
#define KEYS 80
#define LINE '\n'

/* if the first line of the file starts like this, the autoFlg is on,
 *  and type=='d',the program detects a file that is not encrypted,
 * and simply copies it over without modification */
#define NO_CRYPT "* ========"

#define MOD(A,B) ((A)<0 ? full+(A) : (A)-((A)/(B))*(B))

#ifdef ZZ_ANSI
void jsCrypt(char *inpName,char *outName,int type,char *c,int autoFlg,int tab)

#else
void jsCrypt(inpName,outName,type,c,autoFlg,tab)
char *inpName; /* name of the input file */
char *outName; /* name of the output file */
char type;     /* 'e'=encrypting, 'd'=decrypting */
char *c;       /* encrypting key as a string */
int autoFlg;   /* 1=automatic detection of encrypted files, 0=full control */
int tab;       /* 1 if TAB  and other special characters are also encrypted */
#endif
{
    FILE *inpFile,*outFile;
    char *p;
    static char mybf[BUFS];
    int nc,start,cryptIt;

    if(tab<0 || tab>1){ZZmsgD(3,tab); return;} /* internal error tab=%d */
    if(!c)ZZmsg(11); /* internal error: no crypt key given to jsCrypt */
    outFile=myopen(outName,"w");
    if(!outFile){
        ZZmsgS(0,outName); /* cannot open file */
	return;
    }
    inpFile=myopen(inpName,"r");
    if(!inpFile){
        ZZmsgS(0,inpName); /* cannot open file */
	return;
    }

    for(start=1,cryptIt=1;fgets(mybf,BUFS,inpFile);start=0){
	if(start){
          nc=strlen(NO_CRYPT);
          /* skip the first character - comment makes problem in TURBO C */
	  if(autoFlg && type=='d' && !strncmp(NO_CRYPT,&(mybf[1]),nc))cryptIt=0;
          if(cryptIt){
              ZZmsgS(8,inpName); /* probably error in the format of file */
              ZZmsg(12); /* encrypting algorithm not available in this release*/
          }
	}
	for(p=mybf;(*p)!=LINE;p++){
            fprintf(outFile,"%c",*p);
        }
        fprintf(outFile,"%c",*p);
    }

    fclose(inpFile);
    fclose(outFile);
    return;
}
/* ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
FILE *myopen(char *a,const char *b)

#else
FILE *myopen(a,b)
char *a,*b;
#endif
{
    FILE *fp;

#ifdef DOS
  { char *c;
    /* convert '/' to '\' in all file names */
    for(c=a;(*c)!='\0';c++)if((*c)=='/')*c='\\';
  }
#endif
#ifdef MAC
  { char *c;
    /* convert '/' to ':' in all file names */
    for(c=a;(*c)!='\0';c++)if((*c)=='/')*c=':';
  }
#endif

    fp=fopen(a,b);
    return(fp);
}
/* ----------------------------------------------------------- */
#ifdef ZZ_ANSI
void mvFile(char *oldF,char *newF)

#else
void mvFile(old,new)
char *oldF,*newF; /* old and new name for the file */
#endif
{
#ifdef DOS
    strcpy(buff,"rename ");
#endif
#ifdef UNIX
    strcpy(buff,"mv ");
#endif
#ifdef VMS
    strcpy(buff,"$ rename ");
#endif
    strcat(buff,oldF);
    strcat(buff," ");
    strcat(buff,newF);
#ifdef VMS
    strcat(buff,";*");
#endif
    system(buff);
}
/* ----------------------------------------------------------- */
#ifdef ZZ_ANSI
void delFile(char *name)

#else
void delFile(name)
char *name;
#endif
{
    FILE *fp;

    fp=myopen(name,"r"); /* also converts the name for DOS or MAC */
    if(!fp)return; /* file does not exist */
    fclose(fp);
#ifdef DOS
    strcpy(buff,"del ");
#endif
#ifdef UNIX
    strcpy(buff,"rm -rf ");
#endif
#ifdef VMS
    strcpy(buff,"$ del ");
#endif
    strcat(buff,name);
#ifdef VMS
    strcat(buff,";*");
#endif
    system(buff);
}
/* ----------------------------------------------------------- */
/* compare two ZZlocal files, but disregard leading digits (line numbers) */
#ifdef ZZ_ANSI
int cmpFiles(char *name1,char *name2)

#else
int cmpFiles(name1,name2)
char *name1,*name2; /* file names to compare */
#endif
{
    FILE *f1,*f2;
    char *i1,*i2,*c1,*c2,bufc[BUFSIZE];

    f1=fopen(name1,"r");
    f2=fopen(name2,"r");
    if(!f1 || !f2)return(1); /* missing file does not compare */
    for(i1=i2=(char*)1;i1&&i2;){
        i1=fgets(buff,BUFSIZE,f1);
        i2=fgets(bufc,BUFSIZE,f2);
        if(i1&&i2){
            /* proceed to the first blank in both buffers */
            for(c1=buff; (*c1)!=' '&&(*c1)!=END&&(*c1)!=LINE; c1++)continue;
            for(c2=bufc; (*c2)!=' '&&(*c2)!=END&&(*c2)!=LINE; c2++)continue;
            /* compare the two buffers */
            for(; (*c1)!=END&&(*c1)!=LINE&&(*c2)!=END&&(*c2)!=LINE; c1++,c2++)
                                                      if((*c1)!=(*c2))return(1);
            
        }
    }
    if(i1||i2)return(1);
    return(0);
}
/* ---------------------------------------------------------------------- */
/* Copy one open file into another and, at the same
 * skip the documentation part from the input file.
 * The documentation is always between two comment lines with many ====== .
 * Also, if there is any line with many +++++++, skip it.
 * At the same time replace '$' by the given string (id).
 * If id==NULL, copy only until line ______.
 * If id!=NULL, copy only after line  ______.
 */
#ifdef ZZ_ANSI
void cpFile(FILE *inFile,FILE *outFile,char *id)

#else
void cpFile(inFile,outFile,id)
FILE *inFile,*outFile; /* input and output files */
char *id;              /* NULL means nothing to replace */
#endif
{
    int i,j,k,n,sw1,sw2;
    char *c;

    if(id)sw2=0; else sw2=1;
    while(fgets(buff,BUFSIZE,inFile)){
	/* section to treat the documentation */
	for(i=0;i<=RANGE2 && buff[i]!=END && buff[i]!=LINE;i++)continue;
	sw1=1;
	if(i>RANGE2){
	    /* skip long lines of +++++ */
	    for(k=RANGE1;k<=RANGE2;k++)if(buff[k]!='+')break;
	    if(k>RANGE2)sw1=0;
	    /* is this a long line of ==== ? */
	    for(k=RANGE1;k<=RANGE2;k++)if(buff[k]!='=')break;
	    if(k>RANGE2){
	        sw1=0; /* never print this line */
                if(!id)sw2=1-sw2; /* reverse sw2 */
	    }
	    /* is this a long line of ____ ? */
	    for(k=RANGE1;k<=RANGE2;k++)if(buff[k]!='_')break;
	    if(k>RANGE2){
	        sw1=0; /* never print this line */
                sw2=1-sw2; /* reverse sw2 */
	    }
	}
	if(sw1 && sw2){
            if(id){
                /* replace '$' by the given string (id) */
                for(c=buff,i=k=0;*c!='\0';c++,i++)if(*c=='$')k++;/* count '$' */
                j=strlen(id);
                k=i+k*(j-1);
                if(k>=BUFSIZE){
                    ZZmsgSD(1,buff,BUFSIZE); /* BUFSIZE insuff. to expand */
                }
                for(;i>=0;i--){
                    if(buff[i]=='$'){
                        for(n=j-1;n>=0;n--,k--)buff[k]=id[n]; 
                    }
                    else {buff[k]=buff[i]; k--;}
                }
            }
            fprintf(outFile,"%s",buff);
        }
    }
    return;
}
/* ---------------------------------------------------------------------- */
/* Plain copy of the file with a given name onto the output file */
#ifdef ZZ_ANSI
void plainCopy(char *name,FILE *outFile)

#else
void plainCopy(name,outFile)
char *name;    /* name of the input file */
FILE *outFile; /* input and output files */
#endif
{
    FILE *inFile;

    inFile=myopen(name,"r");
    if(!inFile){ZZmsgS(0,name); return;} /* cannot open file */

    while(fgets(buff,BUFSIZE,inFile)) fprintf(outFile,"%s",buff);
    return;
}
/* -------------------------------------------------------------- */
/* Get path from the program call.
 * Example of use:  ZZpath=ZZgetPath(argv[0],"zzprep");
 * Repeated calls allocate new paths; the old path does NOT get overwritten.
 */
#ifdef ZZ_ANSI
char *ZZgetPath(char *progr,char *name)

#else
char *ZZgetPath(progr,name)
char *progr; /* full program call which contains the path */
char *name;  /* name of the program itself */
#endif
{
    int i,nh;
    char *path;
#ifdef VMS
    int k;
#endif

    i=strlen(progr);
    nh=1+strlen(name); /* 1 for '/' */
#ifdef DOS
#ifdef NT
    i=i-nh; 
#else // NT
    i=i-nh-4; /* has '.exe' at the end */
#endif // NT
#endif // DOS
#ifdef UNIX
    i=i-nh; 
#endif
#ifdef VMS
    /* search from the end for ';' */
    for(k=1;progr[i-k]!=';';k++);
    i=i-nh-k-4;
#endif
    if(i>0){
        path=(char *)malloc(i+1);
        strncpy(path,progr,i);
        path[i]='\0';
    }
    else path=(char*)".";
    return(path);
}
/* ------------------------------------------------------------- */
/* read a macro file, and filter out the documentation */
#ifdef ZZ_ANSI
void filterOut(FILE *mFile,FILE *outFile)

#else
void filterOut(mFile,outFile)
FILE *mFile; /* macro file, already open */
FILE *outFile; /* output file, already open */
#endif
{
    int i,k,sw1,sw2;

    sw1=0;
    while(fgets(buff,BUFSIZE,mFile)){
	for(i=0;i<=RANGE2 && buff[i]!=END && buff[i]!=LINE;i++)continue;
	sw2=1;
	if(i>RANGE2){
	    /* when hitting ++++++ stop printing */
	    for(k=RANGE1;k<=RANGE2;k++)if(buff[k]!='+')break;
	    if(k>RANGE2)return;
	    /* is this a long line of ==== ? */
	    for(k=RANGE1;k<=RANGE2;k++)if(buff[k]!='=')break;
	    if(k>RANGE2){sw1++; sw2=0;}
	}
        if(sw2){
            if(sw1==2){ /* eliminate # and \ characters */
	        for(i=0;buff[i]!=END && buff[i]!=LINE;i++){
                    if(buff[i]=='\\' || buff[i]=='#')buff[i]=' ';
                }
            }
	    if(sw1>0)fprintf(outFile,"%s",buff);
        }
    }
    return;
}
/* --------------------------------------------------------------------------- */
/* dummy ZZioFunction() to make libraries that contain a debugging function
 * compatible with the preprocessor */
#ifdef ZZ_ANSI
ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSz){

#else
ZZint ZZioFunction(fp,mode,type,p)FILE *fp;ZZint mode;ZZint type;char *p; ZZint strSz;{
#endif
    fp=fp; mode=mode; type=type; p=p; return(0);}
/* --------------------------------------------------------------------------- */
/* dummy functions for memory blasting to avoid loading too much from the library */

#ifdef ZZ_ANSI
int ZZbindPtrs(char *obj,int newTp,int newSize,int vUpd,int blast)

#else
int ZZbindPtrs(obj,newTp,newSize,vUpd,blast)
char *obj;   /* new(!!) start of the object */
int newTp;   /* new type */
int newSize; /* size of the new object, may indicate an array */
int vUpd;    /* 1 update virt.pointers, 0 do not update */
int blast;   /* 1 for blasting to bitmap, 0 otherwise */
#endif
{ printf("function ZZbindPtrs should never be called here\n");
  printf("%d %d %d %d %d\n",obj,newTp,newSize,vUpd,blast);
  return(0);
}

#ifdef ZZ_ANSI
ZZvoidS *ZZnewBit(ZZsize size) 

#else
ZZvoidS *ZZnewBit(size) 
ZZsize size;
#endif
{ printf("function ZZnewBit should never be called here, size=%d\n",size);
  return((void*)NULL); }
