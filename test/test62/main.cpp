 
#define ZZmain
#include "network.h"
const char* getText(Station *s, int start, int num);

void prtPlaces(Place *root, int level)
{
	for(int i=0; i<level; i++)
	{
		printf("--");
	}
	printf("%s\n", pName.fwd(root));
	Station *s = station.fwd(root);
	if(s!=NULL)
	{
		const char * info = getText(s, 1200, 500);
		if(info != NULL)
		{
			printf("INFO:\n");
			printf("%s\n\n", info);
		}
	}
	placesTree_iterator it;
	it.start(root);
	Place *p;
	ITERATE(it, p)
	{
		prtPlaces(p, level+1);
	}
}

void prtRoads(Station *s)
{
	roads_iterator it;
	it.start(s);
	Connection *c;
	Station *sa;
	
	ITERATE(it, c)
	{
		if(c->visited)
		{
			continue;
		}
		c->visited = true;
		sa = it.adj();
		printf("%s - %s (%s): %d\n", s->getName(), sa->getName(), c->getName(), c->distance);
		prtRoads(sa);
	}
}

void prtFlights(Station *s)
{
	flights_iterator it;
	it.start(s);
	Connection *c;
	Station *sa;
	
	ITERATE(it, c)
	{
		if(c->visited)
		{
			continue;
		}
		c->visited = true;
		sa = it.adj();
		printf("%s - %s (%s): %d\n", s->getName(), sa->getName(), c->getName(), c->distance);
		prtFlights(sa);
	}
}

void generateText(Station *s, const char* filename)
{
	FILE *f = fopen(filename, "r");
	static char buf[81];
	int cnt = 0;
	int i,k;
	for(i=0, k=0;; i++, k=k+cnt)
	{
		if(!fgets(buf, 80, f))
		{
			break;
		}
		cnt = strlen(buf);
//printf("??? cnt=%d k=%d\n%s\n",cnt,k,buf);
		info.io(s, k, buf, cnt, 1);
	}
//printf("??? k=%d\n",k);
    
	fclose(f);
        info.flush(s);
}

const char* getText(Station *s, int start, int num)
{
	static char buf[1024];
	memset(buf, 0, sizeof(buf));
	int ret = info.io(s, start, buf, num, 0);
	printf("requested: %d, returned: %d, returned buffer length=%d\n", num, ret, strlen(buf));
	if(ret==-1)
		return NULL;
	return buf;
} 

int main()
{
	Network *net = new Network();
	
	Place *p1 = new Place("USA", net);
	Place *p11 = new Place("Texas", net);
	placesTree.add(p1, p11);
	Place *p111 = new Place("Dallas", net);
	placesTree.add(p11, p111);
	station.add(p111, new Station());
	Place *p112 = new Place("Forth Worth", net);
	placesTree.add(p11, p112);
	station.add(p112, new Station());
		
	Place *p12 = new Place("Alabama", net);
	placesTree.add(p1, p12);
	Place *p121 = new Place("Montgomery", net);
	placesTree.add(p12, p121);
	station.add(p121, new Station());

	info.form(p121->getStation(), "infoMontgomery", 64, 8, 2);
	generateText(p121->getStation(), "info.txt");
	
	
	Place *p122 = new Place("Birmingham", net);
	placesTree.add(p12, p122);
	station.add(p122, new Station());
	
	
	Place *p13 = new Place("Florida", net);
	placesTree.add(p1, p13);
	Place *p131 = new Place("Miami", net);
	placesTree.add(p13, p131);
	station.add(p131, new Station());
	Place *p132 = new Place("Tampa", net);
	placesTree.add(p13, p132);
	station.add(p132, new Station());
	Place *p133 = new Place("Jacksonville", net);
	placesTree.add(p13, p133);
	station.add(p133, new Station());
	
	printf("\n");
	prtPlaces(p1, 0);
	
	Place *p2 = new Place("Canada", net);
	Place *p21 = new Place("Ontario", net);
	placesTree.add(p2, p21);
	Place *p211 = new Place("Ottawa", net);
	placesTree.add(p21, p211);
	station.add(p211, new Station());
	Place *p212 = new Place("North Bay", net);
	placesTree.add(p21, p212);
	station.add(p212, new Station());
	
	Place *p22 = new Place("Quebec", net);
	placesTree.add(p2, p22);
	Place *p221 = new Place("Chicoutimi", net);
	placesTree.add(p22, p221);
	station.add(p221, new Station());
	Place *p222 = new Place("Quebec", net);
	placesTree.add(p22, p222);
	station.add(p222, new Station());
	
	printf("\n");
	prtPlaces(p2, 0);
	
	//roads
	Station *s[2];
	
	s[0]=p112->getStation();s[1]=p111->getStation();
	roads.add(s, new Connection(200, "r112-111"));
	s[0]=p111->getStation();s[1]=p122->getStation();
	roads.add(s, new Connection(1000, "r111-122"));
	s[0]=p122->getStation();s[1]=p121->getStation();
	roads.add(s, new Connection(100, "r122-121"));
	s[0]=p122->getStation();s[1]=p211->getStation();
	roads.add(s, new Connection(2500, "r122-211"));
	s[0]=p211->getStation();s[1]=p212->getStation();
	roads.add(s, new Connection(400, "r211-212"));
	s[0]=p211->getStation();s[1]=p222->getStation();
	roads.add(s, new Connection(500, "r211-222"));
	s[0]=p222->getStation();s[1]=p221->getStation();
	roads.add(s, new Connection(100, "r222-221"));
	s[0]=p221->getStation();s[1]=p133->getStation();
	roads.add(s, new Connection(3500, "r221-133"));
	s[0]=p133->getStation();s[1]=p132->getStation();
	roads.add(s, new Connection(150, "r133-132"));
	s[0]=p132->getStation();s[1]=p131->getStation();
	roads.add(s, new Connection(100, "r132-131"));
	printf("\nROADS:\n");
	prtRoads(p132->getStation());
	
	//flights
	s[0]=p112->getStation();s[1]=p122->getStation();
	flights.add(s, new Connection(800, "f112-122"));
	s[0]=p122->getStation();s[1]=p211->getStation();
	flights.add(s, new Connection(2500, "f122-211"));
	s[0]=p122->getStation();s[1]=p132->getStation();
	flights.add(s, new Connection(2000, "f122-132"));
	s[0]=p211->getStation();s[1]=p132->getStation();
	flights.add(s, new Connection(3000, "f211-132"));
	s[0]=p132->getStation();s[1]=p222->getStation();
	flights.add(s, new Connection(3200, "f132-222"));
	printf("\nFLIGHTS:\n");
	prtFlights(p112->getStation());
	
        info.close(p121->getStation());
	return 0;
} 

#include "zzfunc.c"
