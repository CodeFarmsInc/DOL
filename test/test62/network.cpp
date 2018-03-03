 
#include "network.h"
 
 int Connection::cnt=0;
 
Station* Place::getStation()
{
	return station.fwd(this);
}
 
 
const char* Station::getName()
{
	Place *from = station.bwd(this);
	return (const char*) pName.fwd(from);
}

Place::Place(char *name, Network *net)
{
	if(placesArr.formed(net)==NULL)
	{
		placesArr.form(net, 20, 5);
	}
	char *n = util.strAlloc(name);
	pName.add(this, n);
	placesArr.push(net, this);
}

Connection::Connection(int dist, char *name)
{
	distance = dist;
	char *n = util.strAlloc(name);
	cName.add(this, n);
	cnt++;
}
const char* Connection::getName()
{
	return (const char*) cName.fwd(this);
}
