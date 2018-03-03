#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "zzincl.h"

class Network
{
	ZZ_EXT_Network
};

class Place
{
	ZZ_EXT_Place
public:
	Place(){ZZ_INIT(Place);}
	Place(char *name, Network *net);
	Station* getStation();
};

class Station
{
	ZZ_EXT_Station
public:
	const char* getName();
};

class Connection
{
	ZZ_EXT_Connection
private:
	static int cnt;
public:
	bool visited;
	int distance;
	Connection(){ZZ_INIT(Connection);cnt++;}
	Connection(int dist, char *name);
	const char* getName();	
	~Connection(){cnt--;}
	static  int getCount(){return cnt;}
};

ZZ_HYPER_NAME(pName, Place);
ZZ_HYPER_NAME(cName, Connection);
ZZ_HYPER_ARRAY(placesArr, Network, Place);
ZZ_HYPER_DOUBLE_LINK(station, Place, Station);
ZZ_HYPER_PAGER(info, Station);
ZZ_HYPER_SINGLE_TREE(placesTree, Place);
ZZ_HYPER_SINGLE_GRAPH(flights, Station, Connection);
ZZ_HYPER_SINGLE_GRAPH(roads, Station, Connection);
ZZ_HYPER_UTILITIES(util);
#endif //_NETWORK_H_