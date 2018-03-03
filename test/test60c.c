// Example of saving data which includes inheritance,
// coding style C:
//    #define ZZ_INHERIT
//    do not use member describing the type, but use virtual function
//       to get the desired effect.
// This style results in best performance and smallest data footprint.
// Note that virtual functions needed for style A are naturally in place.
// After all, why would you use inheritance if you do not use virtual functions.
//    Data footprint for this example (with MS Windows and VC++):
//       Style A: 1,238 bytes
//       Style B: 1,246 bytes
//       Style C: 1,158 bytes (member ShapeKind is not used)
// ---------------------------------------------------------------------

#define ZZmain
#include "zzincl.h"

#define TEXT_LEN 64

class TileType {
	ZZ_EXT_TileType
};


class ShapeType {
	ZZ_EXT_ShapeType
public:
        virtual void prt(){}
};

class RectangleType: public ShapeType {
	ZZ_EXT_RectangleType
};

class CircleType: public ShapeType {
	ZZ_EXT_CircleType
public:
	int Radius;
	int MinRadius;
        void prt(){
            printf("Circle Radius=%d MinRadius%d\n",Radius,MinRadius);
        }
};


ZZ_HYPER_SINGLE_AGGREGATE(mTileShapes,TileType,ShapeType);
ZZ_HYPER_UTILITIES(util);

void prtCircles(TileType *tile){
	ShapeType* shape; 

	mTileShapes_iterator itShapes(tile);
        ITERATE(itShapes,shape)
	{
            shape->prt();
        }
        printf("\n");
}

int main(int argc, char* argv[])
{
   
	//
	// create type definitions
	//
	char sFile[] = "tile.odb";
	CircleType *cir;
	RectangleType *rc;
        int i;
     
	TileType* tile = new TileType;

        for(i=0; i<10; i++){ // add 10 rectangles and 10 circles
	    rc = new RectangleType;
	    mTileShapes.add(tile,rc);

	    cir = new CircleType;
	    cir->Radius = 5+i;
	    cir->MinRadius = 4+i;
	    mTileShapes.add(tile,cir);
        }

        prtCircles(tile);

	char *v[1], *t[1];
	v[0] = (char*)tile; t[0] = (char*)"TileType";
	util.save(sFile,1,v,t);
        v[0]=NULL; // prevent picking the old data

	// read
	util.open(sFile,1,v,t);
	tile = (TileType*)v[0];

        prtCircles(tile);
        return 0;
}

#include "zzfunc.c"
