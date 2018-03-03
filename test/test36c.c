#include <iostream.h>
#define ZZmain
#include "zzincl.h"

// holder of the hash table
class Table {
    ZZ_EXT_Table
};

// represents one name entry
class Token {
    ZZ_EXT_Token
public:
    Token(){}
    Token(char *n);
    ~Token();
};

// encapsulates the hash table
// Note the absence of ZZ_EXT_Dict
class Dict { 
    Table *tab; // hides the hash table
public:
    Dict(int sz);
    ~Dict();
    void addName(char *n);
    char *getName(char *n);
    void delName(char *n);
};
ZZ_HYPER_HASH(hash,Table,Token);
ZZ_HYPER_NAME(name,Token);
ZZ_HYPER_UTILITIES(util);

int hash_class::cmp(Token *b1,Token *b2){
        return strcmp(name.fwd(b1),name.fwd(b2)); }
int hash_class::hash(Token *b,int size)
        { int ZZhashStr(char *,int); return ZZhashStr(name.fwd(b),size); }

Dict::Dict(int sz){tab=new Table; hash.form(tab,sz);}
Dict::~Dict(){hash.free(tab);} 

Token::Token(char *n){char* p=util.strAlloc(n); name.add(this,p);}
Token::~Token(){char* p=name.del(this); if(p)util.strFree(p);}

void Dict::addName(char *n){
    Token* t=new Token(n);
    Token* p=hash.get(tab,t);
    if(!p)hash.add(tab,t); else delete t;
}

char* Dict::getName(char *n){
    static Token t;
    char *p;
    name.add(&t,n);
    Token* tp=hash.get(tab,&t);
    if(tp)p=name.fwd(tp); else p=NULL;
    (void)name.del(&t);
    return p;
}

void Dict::delName(char *n){
    static Token t;
    name.add(&t,n);
    Token* tp=hash.get(tab,&t);
    if(tp)(void)hash.del(tab,tp);
    (void)name.del(&t);
}

int main(void){
    Dict a(100); char *n;

    a.addName("brown"); 
    a.addName("black"); 
    a.addName("brown"); 
    a.addName("brown"); 
    a.delName("brown");
    n=a.getName("black"); if(n)cout<<n<<"\n";
    n=a.getName("brown"); if(n)cout<<n<<"\n";
    return(0);
};
#include "zzfunc.c"

// The program prints only one line: black
