// Another, more complex, test case for virtual function pointers,
// virtual base class pointers, and ASCII saving to disk

// This test cannot be run on SUN, cfront 2.0 generates illegal c-code

#include <stdio.h>
#define ZZmain
#define ZZascii
#define ZZ_NOLEAK
#include "zzincl.h"

ZZ_HYPER_UTILITIES(util);

class MQWRect
{
  ZZ_EXT_MQWRect
public:
  MQWRect() {}
  MQWRect(long iLeft,  long iTop,
          long iRight, long iBottom);
  void Save(const char *fp);
  void Draw();
  long top;
  long left;
  long bottom;
  long right;
};
void MQWRect::Save(const char *fp) { printf("MQWRect::Save() called\n"); ZZ_STORE(MQWRect, fp); }
void MQWRect::Draw() {}
ZZ_FORMAT(MQWRect, "%ld %ld %ld %ld, top, left, bottom, right");

MQWRect::MQWRect(long iLeft, long iTop, long iRight, long iBottom)
{
  top    = iTop;
  left   = iLeft;
  bottom = iBottom;
  right  = iRight;
}

class MQShape
{
  ZZ_EXT_MQShape
  virtual void Save(const char *fp);
  short bIsSelected;
  virtual void Print() {};
};
void MQShape::Save(const char *fp) { ZZ_STORE(MQShape, fp); }
ZZ_FORMAT(MQShape, "%hd, bIsSelected");
ZZ_HYPER_SINGLE_LINK(MQShapeToolLink, MQShape, MQShapeTool);
ZZ_HYPER_DOUBLE_RING(MQShapeList, MQShape);

class MQAbstractRectShape : public MQShape
{
  ZZ_EXT_MQAbstractRectShape
  MQAbstractRectShape() {}
  MQAbstractRectShape(long iLeft, long iTop, long iRight, long iBottom);
  virtual void Save(const char *fp);
  MQWRect MathRect;
};
MQAbstractRectShape::MQAbstractRectShape(long iLeft, long iTop,
                                         long iRight, long iBottom) :
  MathRect(iLeft, iTop, iRight, iBottom) {}
void MQAbstractRectShape::Save(const char *fp) {ZZ_STORE(MQAbstractRectShape, fp);}
ZZ_FORMAT(MQAbstractRectShape, "");

class MQOvalShape : public MQAbstractRectShape
{
  ZZ_EXT_MQOvalShape
  MQOvalShape();
  ~MQOvalShape();
  MQOvalShape(long iLeft, long iTop, long iRight, long iBottom, MQShapeTool *Tool);
  virtual void Save(const char *fp);
  virtual void Print();
};
MQOvalShape::MQOvalShape() {}
MQOvalShape::~MQOvalShape() {}
MQOvalShape::MQOvalShape(long iLeft, long iTop, long iRight, long iBottom, MQShapeTool *Tool)
: MQAbstractRectShape(iLeft, iTop, iRight, iBottom)
{
  MQShapeToolLink.add(this, Tool);
}
void MQOvalShape::Save(const char *fp){ ZZ_STORE(MQOvalShape, fp); }
ZZ_FORMAT(MQOvalShape, "");

class MQCircleShape : public MQOvalShape
{
  ZZ_EXT_MQCircleShape
  virtual void Save(const char *fp);
};
ZZ_FORMAT(MQCircleShape, "");
void MQCircleShape::Save(const char *fp){ ZZ_STORE(MQCircleShape, fp); }

class MQShapeTool
{
  ZZ_EXT_MQShapeTool
  virtual void Save(const char *fp);
  virtual void Print() {};
  int RefCnt;
};
void MQShapeTool::Save(const char *fp) { ZZ_STORE(MQShapeTool, fp); }
ZZ_FORMAT(MQShapeTool, "%d, RefCnt");

class MQPenTool : virtual public MQShapeTool
{
  ZZ_EXT_MQPenTool
  virtual void Save(const char *fp);
  int Pen;
};
void MQPenTool::Save(const char *fp) { ZZ_STORE(MQPenTool, fp);}
ZZ_FORMAT(MQPenTool, "%d, Pen");

class MQBrushTool : virtual public MQShapeTool
{
  ZZ_EXT_MQBrushTool
  virtual void Save(const char *fp);
  int Brush;
};
void MQBrushTool::Save(const char *fp) { ZZ_STORE(MQBrushTool, fp); }
ZZ_FORMAT(MQBrushTool, "%d, Brush");

class MQBackgndTool : virtual public MQShapeTool
{
  ZZ_EXT_MQBackgndTool
  virtual void Save(const char *fp);
  long bgColor;
};
void MQBackgndTool::Save(const char *fp) { ZZ_STORE(MQBackgndTool, fp); }
ZZ_FORMAT(MQBackgndTool, "%ld, bgColor");

class MQSolidTool
  : public MQPenTool, public MQBrushTool, public MQBackgndTool
{
  ZZ_EXT_MQSolidTool
  virtual void Save(const char *fp);
  virtual void Print();
};
void MQSolidTool::Save(const char *fp) { ZZ_STORE(MQSolidTool, fp); }
ZZ_FORMAT(MQSolidTool, "");

class MQPenBkgndTool : public MQPenTool, public MQBackgndTool
{
  ZZ_EXT_MQPenBkgndTool
  virtual void Save(const char *fp);
};
void MQPenBkgndTool::Save(const char *fp) { ZZ_STORE(MQPenBkgndTool, fp); }
ZZ_FORMAT(MQPenBkgndTool, "");

class MQShapeKey
{
  ZZ_EXT_MQShapeKey
  virtual void Save(const char *fp);
};
void MQShapeKey::Save(const char *fp) { ZZ_STORE(MQShapeKey, fp); }
ZZ_FORMAT(MQShapeKey, "");
ZZ_HYPER_SINGLE_LINK(MQShapeLink, MQShapeKey, MQShape);

/**********************************************************************/
MQShape *ShapeListTail = NULL;

void ReadData()
{
  FILE *DataFile = fopen("junk.out", "rb");
  if (DataFile == NULL)
  {
    printf("Error opening file");
    return;
  }
  
  // delete the default tools and shapelist if necessary
  // ADD CODE HERE ?????
  
  //ReadHeader(DataFile);
  char *v[1], *t[1];
  v[0] = NULL;  // this will be overwritten anyway
  util.open((char *)DataFile, 1, v, t);
  fclose(DataFile);
  MQShapeKey *pKey = (MQShapeKey *) v[0];
  ShapeListTail    = MQShapeLink.fwd(pKey);
  MQShapeLink.del( pKey );
  delete pKey;
  //DefaultSolidTool    = (MQSolidTool *)    v[1];
  //DefaultPenBkgndTool = (MQPenBkgndTool *) v[2];
}

void
MQDrawDocSave(char *Object, ZZint TypeID, ZZint /*Size*/, const char *fp)
{
  char *Type = util.type(TypeID);
  
  printf("MQDrawDocSave(): TypeID=%d Type=%s\n", TypeID, Type);  //??? Debug msg
  
  if ( strcmp(Type, "MQShape") == 0 )
    ((MQShape *)Object)->Save(fp);
  else if ( strcmp(Type, "MQOvalShape") == 0 )
    ((MQOvalShape *)Object)->Save(fp);
  else if ( strcmp(Type, "MQShapeTool") == 0 )
    ((MQShapeTool *)Object)->Save(fp);
  else if ( strcmp(Type, "MQSolidTool") == 0 )
    ((MQSolidTool *)Object)->Save(fp);
  else if ( strcmp(Type, "MQPenBkgndTool") == 0 )
    ((MQPenBkgndTool *)Object)->Save(fp);
  else if ( strcmp(Type, "MQShapeKey") == 0 )
    ((MQShapeKey *)Object)->Save(fp);
  else
    printf("MQDrawDocSave(): Unknown TypeID=%d Type=%s\n", TypeID,
            Type);
}

void WriteData()
{
  FILE *DataFile = fopen("junk.out", "wb");
  if (DataFile == NULL)
  {
    printf("Error opening file");
    return;
  }
  
  // WriteHeader(DataFile);
  //ZZ_KEY_SAVE(MQShape,        (char *)DataFile, ShapeListTail);
  //ZZ_KEY_SAVE(MQSolidTool,    (char *)DataFile, DefaultSolidTool);
  //ZZ_KEY_SAVE(MQPenBkgndTool, (char *)DataFile, DefaultPenBkgndTool);
  MQShapeKey *pKey = new MQShapeKey;
  MQShapeLink.add( pKey, ShapeListTail);
  char *v[1], *t[1];
  v[0] = (char *) pKey;
  t[0] = (char*)"MQShapeKey";
  util.swpSet(1, v, t);
  util.swpFun(MQDrawDocSave, (char *)DataFile);
  util.swpFree();
  util.close( (char *)DataFile );
  fclose(DataFile);
  MQShapeLink.del( pKey );
  delete pKey;
}

void MQSolidTool::Print()
{
  printf("Pen     = %d\n",  Pen);
  printf("Brush   = %d\n",  Brush);
  printf("bgColor = %ld\n", bgColor);
  printf("RefCnt  = %d\n",  RefCnt);
}  

void MQOvalShape::Print()
{
  MQShapeToolLink.fwd(this)->Print();
  printf("bIsSelected = %hd\n", bIsSelected);
  printf("MathRect = %ld %ld %ld %ld\n", MathRect.left,
          MathRect.top, MathRect.right, MathRect.bottom);
}  

int main()
{
 util.mode(1,1,0,1);
 MQSolidTool *SldTool = new MQSolidTool;
 SldTool->Pen     = 1;
 SldTool->Brush   = 2;
 SldTool->bgColor = 3;
 SldTool->RefCnt  = 4;
 MQOvalShape *Oval = new MQOvalShape(5L, 6L, 7L, 8L, SldTool);
 Oval->bIsSelected = 9;
 ShapeListTail = MQShapeList.add(ShapeListTail, Oval);
 WriteData();
 ShapeListTail->Print();
 ReadData();
 ShapeListTail->Print();
 return 0;
}

#include "zzfunc.c"
