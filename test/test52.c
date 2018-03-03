// C.L.Liu discovered a special bug which happened only in C++ and
// for the BINARY saving mode. When a base class had property or
// an array assigned to it, when saving the derived class the property
// orarray was not written out to the disk file, and then util.open()
// stopped with binding errors. This problem was corrected by
// a rather extensive change in bind.cc. <Jiri Soukup, June 26/1997>
// ---------------------------------------------------------------
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class dbObj {
    ZZ_EXT_dbObj
public:
};

class dbLogObj : public dbObj {
    ZZ_EXT_dbLogObj
    public:
	int getNumProperty();
	int addProperty(char *propName, int value);
	int addProperty(char *propName, float value);
	int addProperty(char *propName, char *value);
	int deleteProperty(char *propertyName);
	int getProperty(char *propertyName, int &intValue);
	int getProperty(char *propertyName, float &floatValue);
	int getProperty(char *propertyName, char *&stringValue);
};

class dbLib : public dbLogObj {
    ZZ_EXT_dbLib
public:
    int numCells;
};

ZZ_HYPER_UTILITIES(util);
ZZ_HYPER_PROPERTY(dbLogObj);

int dbLogObj::getNumProperty() {
    int count = 0;
    char *val, *name, *tp;
    int size;

    dbLogObj_propIterator pIter(this);
    for (;;) {
	val = pIter.next (&name, &tp, &size);
	if (val == NULL)
	    break;
	count++;
    }
    return( count );
}
 
int dbLogObj::addProperty(char *propName, int value) {
    this->setProp ("int", propName, &value, 1);
    return( 1 );
}

int dbLogObj::addProperty(char *propName, float value) {
    this->setProp ("float", propName, &value, 1);
    return( 1 );
}

int dbLogObj::addProperty(char *propName, char *value) {
    this->setProp ("string", propName, &value, 1);
    return( 1 );
}

int dbLogObj::deleteProperty(char *propertyName) {
    this->delProp (propertyName);
    return( 1 );
}

int dbLogObj::getProperty(char *propertyName, int &intValue) {
    char *val, *name, *tp;
    int size;
    tp = this->getProp (propertyName, &tp, &size);
    if (size == 0)
	return (0);
    intValue = *((int *) tp);
    return(1);
}

int dbLogObj::getProperty(char *propertyName, float &floatValue) {
    char *val, *name, *tp;
    int size;
    tp = this->getProp (propertyName, &tp, &size);
    if (size == 0)
	return (0);
    floatValue = *((float *) tp);
    return(1);
}

int dbLogObj::getProperty(char *propertyName, char *&stringValue) {
    char *val, *name, *tp;
    int size;
    tp = this->getProp (propertyName, &tp, &size);
    if (size == 0)
	return (0);
    stringValue = *((char **)tp);
    return(1);
}

void createDB() // added 'void'
{
    char *v[1], *t[1];
    dbLib *libId;
    int intValue;
    float floatValue;
    char *stringValue;

    libId = new dbLib;
    libId->numCells = 100;
    libId->addProperty ("Prop_1", 1234);
    libId->addProperty ("Prop_2", (float) 1234.5678);
    libId->addProperty ("Prop_3", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    printf ("Num of prop %d\n", libId->getNumProperty ());

    libId->getProperty ("Prop_1", intValue);
    printf ("Prop_1 %d\n", intValue);

    libId->getProperty ("Prop_2", floatValue);
    printf ("Prop_2 %f\n", floatValue);

    libId->getProperty ("Prop_3", stringValue);
    printf ("Prop_3 %s\n", stringValue);

    libId->deleteProperty ("Prop_1"); 
    printf ("Num of prop %d\n", libId->getNumProperty ());

    v[0] = (char*) libId;
    t[0] = "dbLib";
    util.save ("DB.file", 1, v, t);
    util.clear (1, v, t);

    v[0] = t[0] = (char *) NULL;
}

readDB()
{
    char *v[1], *t[1];
    dbLib *libId;
    int intValue;
    float floatValue;
    char *stringValue;

    util.open ("DB.file", 1, v, t);
    libId = (dbLib *) v[0];
    printf ("number of cell %d\n", libId->numCells);
    printf ("Num of prop %d\n", libId->getNumProperty ());

    libId->getProperty ("Prop_2", floatValue);
    printf ("Prop_2 %f\n", floatValue);

    libId->getProperty ("Prop_3", stringValue);
    printf ("Prop_3 %s\n", stringValue);

    return (0);
}

int main(int argc, char **argv) // added 'int' which is the C++ default
{
    if (argc < 2)
	exit (1);
    if (strcmp (argv[1], "write") == 0)
	createDB ();
    else if (strcmp (argv[1], "read") == 0)
	readDB ();
    return (0); // replaced 'exit' by 'return'
}

#include "zzfunc.c"
