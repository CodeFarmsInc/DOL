#define ZZ_INHERIT
#define ZZascii

class Header {
    ZZ_EXT_Header
public:
    void save(char *file){ZZ_STORE(Header,file);};
    Header(){ZZ_INIT(Header);};
    ~Header();
};
ZZ_FORMAT(Header,"");
    
class Shape {
    ZZ_EXT_Shape
public:
    virtual void prt(void){};
    Shape(){ZZ_INIT(Shape);};
    ~Shape(){ZZ_CHECK(Shape);};
};
ZZ_FORMAT(Shape,"");
ZZ_HYPER_UTILITIES(util);
    
class Square : public Shape{ 
public:
    int x;
    ZZ_EXT_Square
    void prt(void){printf("Square %d\n",x);};
    void set(int a){x=a;};
    Square(){ZZ_INIT(Square);};
    ~Square(){ZZ_CHECK(Square);};
};
ZZ_FORMAT(Square,"%d,x");
ZZ_HYPER_ARRAY(sqrs,Header,Square);

class Rectangle : public Shape{
    int x,y;
    ZZ_EXT_Rectangle
public:
    void prt(void){printf("Rectangle %dx%d\n",x,y);};
    void set(int a,int b){x=a; y=b;};
    Rectangle(){ZZ_INIT(Rectangle);};
    ~Rectangle(){ZZ_CHECK(Rectangle);};
};
ZZ_FORMAT(Rectangle,"%d %d,x,y");
ZZ_HYPER_ARRAY(recs,Header,Rectangle);

#define BF 80
#ifdef ZZmain
char buff[BF];
#else
extern char *buff;
#endif
