// Example of saving data which includes inheritance,
// coding style A:
//    #define ZZ_INHERIT
//    all base classes have at least one virtual function
// Since this code does not use any virtual function, class ShapeType
// has a dummy virtual function foo() which does nothing.
// ---------------------------------------------------------------------

#define ZZ_INHERIT
#define ZZmain
#include "zzincl.h"

#define TEXT_LEN 64

class TileType {
	ZZ_EXT_TileType
};


class ShapeType {
	ZZ_EXT_ShapeType
public:
	int ShapeKind;
        virtual void foo(){}
};

class RectangleType: public ShapeType {
	ZZ_EXT_RectangleType
};

class CircleType: public ShapeType {
	ZZ_EXT_CircleType
public:
	int Radius;
	int MinRadius;
};


ZZ_HYPER_SINGLE_AGGREGATE(mTileShapes,TileType,ShapeType);
ZZ_HYPER_UTILITIES(util);

void prtCircles(TileType *tile){
	ShapeType* shape; 
	CircleType *cir;

	mTileShapes_iterator itShapes(tile);
        ITERATE(itShapes,shape)
	{
		if(shape->ShapeKind==1){
                        cir=(CircleType*)shape;
                        printf("Circle Radius=%d MinRadius%d\n",
                                         cir->Radius,cir->MinRadius);
                }
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
	    rc->ShapeKind = 0;
	    mTileShapes.add(tile,rc);

	    cir = new CircleType;
	    cir->ShapeKind = 1;
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
