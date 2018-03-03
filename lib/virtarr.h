/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

/* Some systems, for example PC DOS or MS WINDOWS, limit the size
 * of arrays you can use within your program. This is caused by two
 * reasons:
 * (1) Integers by which you index arrays are only 2B ZZlong.
 * (2) The size of any object (or array of objects) cannot exceed
 *     one page (64kB).
 *
 * This is quite aggravating when working under MS WINDOWS:
 * virtual memory is essentially unlimited, but arrays can have only
 * a relatively small size. Virtual array solves
 * this problem by using an array of arrays, where each array is
 * of sufficiently small size. From the user's poZZint of view, the
 * access is transparent and similar to using an ordinary array:
 *     ZZlong i;      ... index ZZlong now, not ZZint
 *     objType *p;  ... objects accessed via poZZinter
 *     virtArr a;  ... used instead of objType s[]
 *  
 *     a[i]=... or   ...=a[i], just like s[i]=... or ...=s[i]
 *
 * Implementation which would be type independent would be more
 * complex (templates etc). Here is a simple version which replaces
 * an array of poZZinters.
 * 
 * The decision, whether to use a single array or the array of arrays
 * is made within this class, depending on the size of the array
 * requested, and can be detected in the following way:
 *   arr!=0, mul==0  ... single array
 *   arr==0, mul!=0  ... multiple array
 *   arr==0, mul==0  ... no array yet
 *
 * Use #define SEPARATE for a separate debugging
 *
 * Author: Jiri Soukup, Apr.20/94
 */

typedef void*   vPtr;
typedef void**  vvPtr;

class ZZvirtArr {
    ZZlong nTot;  /* total number of objects in the array */
    unsigned ZZint nObj;  /* max.number of objects in one true array */
    void **arr; /* true array representation */
    void ***mul; /* multiple array representation */
    static unsigned ZZint oSize; /* size of one object, in Bytes */
    static unsigned ZZint maxSize; /* max size of one array */
public:
    ZZvirtArr(){arr=NULL; mul=NULL; nTot=0; nObj=maxSize/oSize;};
    ~ZZvirtArr(){clean();};     
    void clean(void);
    ZZlong size(void){return(nTot);}
    vPtr& operator[](const ZZlong i); // hides implementation
    void reset(const ZZlong size); // resets to a new size
};

typedef struct ZZbindTBL*   tPtr;

class ZZvirtBindArr : public ZZvirtArr {
public:
    ZZvirtBindArr():ZZvirtArr(){};
    ~ZZvirtBindArr(){clean();}
    ZZlong size(void){return ZZvirtArr::size();}
    tPtr& operator[](const ZZlong i){return *((tPtr*)(&((*((ZZvirtArr*)this))[i])));}
    void reset(const ZZlong size){this->ZZvirtArr::reset(size);}
};

