#ifndef zzinclUsed
#define zzinclUsed
#ifdef ZZmain
char *ZZorgcVersion={(char*)"Version 8.5"};
#else
extern char *ZZorgcVersion;
#endif
#include "C:\orgc\lib\environ.h"
#ifndef FILE
#include <stdio.h>
#endif
#include "C:\orgc\zzcomb.h"
#include "C:\orgc\lib\msgs.h"

class ZZZiClass{};
#ifndef ZZmain
extern
#endif

ZZ_LOCAL char *ZZselfArr[1]
#ifdef ZZmain
={
(char*)"ZZendMark"}
#endif
;
#define ZZnID 1

#define ZZ_EXT_Connection \
friend class ZZHcName;\
friend class ZZHflights;\
friend class ZZHroads;\
    Connection *ZZsroads;\
    Connection *ZZsflights;\
    Connection *ZZrroads;\
    Connection *ZZrflights;\
    Station *ZZyroads;\
    Station *ZZyflights;\
    Station *ZZxroads;\
    Station *ZZxflights;\
    char *ZZncName;\
public:\
    void *zzThisIs(ZZint *type){*type=0; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Connection};\
    Connection(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);


#define ZZ_EXT_Station \
friend class ZZHstation;\
friend class ZZHinfo;\
friend class ZZHflights;\
friend class ZZHroads;\
    Connection *ZZeroads;\
    Connection *ZZeflights;\
    char *ZZhinfo;\
    Place *ZZbstation;\
public:\
    void *zzThisIs(ZZint *type){*type=1; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Station};\
    Station(){};\
   ~Station(){ZZ_CHECK(Station);};\
    Station(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);


#define ZZ_EXT_Place \
friend class ZZHpName;\
friend class ZZHplacesArr;\
friend class ZZHstation;\
friend class ZZHplacesTree;\
    Place *ZZsplacesTree;\
    Place *ZZcplacesTree;\
    Place *ZZpplacesTree;\
    Station *ZZfstation;\
    char *ZZnpName;\
public:\
    void *zzThisIs(ZZint *type){*type=2; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Place};\
   ~Place(){ZZ_CHECK(Place);};\
    Place(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);


#define ZZ_EXT_Network \
friend class ZZHplacesArr;\
    ZZarray *ZZaplacesArr;\
public:\
    void *zzThisIs(ZZint *type){*type=3; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Network};\
    Network(){};\
   ~Network(){ZZ_CHECK(Network);};\
    Network(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);

#define ZZIConnection ZZZIConnection()
ZZ_LOCAL int ZZZIConnection(void);
#define ZZJConnection ZZZJConnection()
ZZ_LOCAL int ZZZJConnection(void);
#define ZZIStation ZZZIStation()
ZZ_LOCAL int ZZZIStation(void);
#define ZZJStation ZZZJStation()
ZZ_LOCAL int ZZZJStation(void);
#define ZZIPlace ZZZIPlace()
ZZ_LOCAL int ZZZIPlace(void);
#define ZZJPlace ZZZJPlace()
ZZ_LOCAL int ZZZJPlace(void);
#define ZZINetwork ZZZINetwork()
ZZ_LOCAL int ZZZINetwork(void);
#define ZZJNetwork ZZZJNetwork()
ZZ_LOCAL int ZZZJNetwork(void);
#define ZZIint ZZZIint()
ZZ_LOCAL int ZZZIint(void);
#define ZZIfloat ZZZIfloat()
ZZ_LOCAL int ZZZIfloat(void);
#define ZZIchar ZZZIchar()
ZZ_LOCAL int ZZZIchar(void);
#ifdef ZZmain
ZZ_LOCAL int ZZZIint(void){return(-6);}
ZZ_LOCAL int ZZZIfloat(void){return(-7);}
ZZ_LOCAL int ZZZIchar(void){return(-1);}

#endif
#ifdef ZZmain

ZZ_LOCAL char *ZZptrList[]={
    (char*)"aZZsroads[1",
    (char*)"aZZsflights[1",
    (char*)"aZZrroads[1",
    (char*)"aZZrflights[1",
    (char*)"aZZyroads[1",
    (char*)"aZZyflights[1",
    (char*)"aZZxroads[1",
    (char*)"aZZxflights[1",
    (char*)"aZZncName[1",
    (char*)"aZZeroads[1",
    (char*)"aZZeflights[1",
    (char*)"gZZhinfo[1",
    (char*)"aZZbstation[1",
    (char*)"aZZsplacesTree[1",
    (char*)"aZZcplacesTree[1",
    (char*)"aZZpplacesTree[1",
    (char*)"aZZfstation[1",
    (char*)"aZZnpName[1",
    (char*)"AZZaplacesArr[1"
};

ZZ_LOCAL struct ZZstrLST ZZstrList[5]={
  {(char*)"Connection", 0, 0, 9, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"Station", 0, 0, 4, -1, -1, -1, -1, 9, 0, {0,0}, 0}, 
  {(char*)"Place", 0, 0, 5, -1, -1, -1, -1, 13, 0, {0,0}, 0}, 
  {(char*)"Network", 0, 0, 1, -1, -1, -1, 0, 18, 0, {0,0}, 0}, 
  {(char*)"ZZendMark", -1, -1, -1, -1, -1, -1, -1, 19, 0, {0, 0}, 0}};


ZZ_LOCAL ZZint ZZnxtType[19]={
 0,0,0,0,1,1,1,1,-1,
 0,0,-8,2,
 2,2,2,1,-1,
 -4
};

ZZ_LOCAL struct ZZtypeHier ZZinhList[1]={
 {-1, -1, -1, (char*)"ZZendMark"}
};
#else
extern char *ZZptrList[];
extern struct ZZstrLST ZZstrList[];
extern ZZint ZZnxtType[];
extern struct ZZtypeHier ZZinhList[];
#endif
#define ZZstrNum 4

#define ZZS_Connection {Connection *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[0].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZsroads))-ZZi));\
 ZZstrList[0].size=(int)sizeof(Connection);}

#define ZZS_Station {Station *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[1].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZeroads))-ZZi));\
 ZZstrList[1].size=(int)sizeof(Station);}

#define ZZS_Place {Place *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[2].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZsplacesTree))-ZZi));\
 ZZstrList[2].size=(int)sizeof(Place);}

#define ZZS_Network {Network *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[3].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZaplacesArr))-ZZi));\
 ZZstrList[3].size=(int)sizeof(Network);}
#define roads_class ZZHroads
#define ZZ1roads Station
#define ZZX1roads "Station"
#define ZZW1roads 1
#define ZZ2roads Connection
#define ZZX2roads "Connection"
#define ZZW2roads 0
#define ZZVroads  
#define flights_class ZZHflights
#define ZZ1flights Station
#define ZZX1flights "Station"
#define ZZW1flights 1
#define ZZ2flights Connection
#define ZZX2flights "Connection"
#define ZZW2flights 0
#define ZZVflights  
#define placesTree_class ZZHplacesTree
#define ZZ1placesTree Place
#define ZZX1placesTree "Place"
#define ZZW1placesTree 2
#define ZZVplacesTree  
#define info_class ZZHinfo
#define ZZ1info Station
#define ZZX1info "Station"
#define ZZW1info 1
#define ZZVinfo  
#define station_class ZZHstation
#define ZZ1station Place
#define ZZX1station "Place"
#define ZZW1station 2
#define ZZ2station Station
#define ZZX2station "Station"
#define ZZW2station 1
#define ZZVstation  
#define placesArr_class ZZHplacesArr
#define ZZ1placesArr Network
#define ZZX1placesArr "Network"
#define ZZW1placesArr 3
#define ZZ2placesArr Place
#define ZZX2placesArr "Place"
#define ZZW2placesArr 2
#define ZZVplacesArr  
#define cName_class ZZHcName
#define ZZ1cName Connection
#define ZZX1cName "Connection"
#define ZZW1cName 0
#define ZZVcName  
#define pName_class ZZHpName
#define ZZ1pName Place
#define ZZX1pName "Place"
#define ZZW1pName 2
#define ZZVpName  



#ifdef ZZmain
ZZ_LOCAL int ZZbindASCII={0};
#ifdef SUN
ZZ_LOCAL int ZZnoLeak={0};
#else
ZZ_LOCAL int ZZnoLeak={1};
#endif
ZZ_LOCAL int ZZinhFLG={1};
ZZ_LOCAL int ZZvClassPresent={0};
ZZ_LOCAL ZZint ZZallocPtr={76};
#endif
#ifndef ZZmain
extern int ZZbindASCII;
extern int ZZnoLeak;
extern int ZZinhFLG;
extern int ZZvClassPresent;
extern ZZint ZZallocPtr;
#endif
#ifdef ZZ_ANSI
#ifdef ZZmain
ZZ_LOCAL ZZint ZZioFunction(FILE *fp,ZZint io,ZZint type,char *p){
fp=fp; io=io; type=type; p=p; return(0);}
#endif
#else
#ifdef ZZmain
ZZ_LOCAL ZZint ZZioFunction(fp,(ZZint)io,(ZZint)type,p)
FILE *fp;int io; int type;char *p;{
fp=fp; io=io; type=type; p=p; return(0);}
#endif
#endif
class Connection;
class Station;
class Place;
class Network;
#ifdef ZZmultiProj
/* dummy function to prevent compiler warnings */
#ifdef ZZ_ANSI
static void *ZZnoWarnings(void){
#else
static void *ZZnoWarnings(){
#endif
    void *p;
    p=(void *)ZZstrList; p=(void *)ZZptrList;
    p=(void *)ZZnxtType; p=(void *)ZZinhList;
    return(p);
}
#endif
#endif
