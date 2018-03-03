/* ============================================================ */

/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/


/* one character propCode has the key role in handling properties:
 *   - capital charaters specify arrays,
 *   - small case characters specify single property,
 *      'i' 'I' = ZZint,
 *      'f' 'F' = float,
 *      'c' 'C' = char, 
 *      's' 'S' = string,
 */

/* ============================================================ */
#define ZZ_PROP_CS 4

struct ZZaProp {
    ZZint size;     /* number of structures in the array, NOT byte size */
    char *array; /* cast as char*, it can be array of other things */
};

struct ZZproperty {
    char *codeName; /* one character propCode followed by the property name */
    struct ZZproperty *next;        /* ring of all properties on one object */
    union ZZpropType {
	char        cProp[ZZ_PROP_CS];  /* cProp[0] as one character */
	struct ZZaProp *arrayProp;  /* poZZints to the size and the array */
        ZZint iProp; /* ZZinteger value directly stored */
        float fProp; /* float value directly stored */
    }propType;
};

#define ZZpropSIZE(type,size) {\
char *P;\
P=ZZ_STRINGIT(type);\
if(!strcmp(P,"ZZint"))(size)=(ZZint)sizeof(ZZint);\
else if(!strcmp(P,"float"))(size)=(ZZint)sizeof(float);\
else if(!strcmp(P,"char"))(size)=(ZZint)sizeof(char);\
else if(!strcmp(P,"string"))(size)=(ZZint)sizeof(char*);\
else ZZmsgS(13,P);\
}
