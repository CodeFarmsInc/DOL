/* Test of the hash table used as a fast, index driven ordered collection
 * The input file contains instruction to add and remove random words.
 *    A  wordx     ...    adds wordx
 *    D  wordy     ...    finds wordy and deletes it
 * For simplicity, all words are printed in lower case.
 * The input file has been constructed so that (beside the random operations)
 * adding and deleting at both the head and the tail of the sublists is tested.
 * After all these operations are performed, the program prints the entire
 * collection, which still must be sorted.
 * Author: Jiri Soukup, June 5, 1997
 */
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Root {
    ZZ_EXT_Root 
};

class Word {
    ZZ_EXT_Word
public:
    Word(char *s);
    Word(){ZZ_INIT(Word);}
    ~Word(){ZZ_CHECK(Word);}
};

ZZ_HYPER_HASH(dict,Root,Word);
ZZ_HYPER_NAME(word,Word);
ZZ_HYPER_UTILITIES(util);

Word::Word(char *s){
    char* p=util.strAlloc(s);
    word.add(this,p);
}

// compare the words as for normal hash table or when sorting collections
inline int dict_class::cmp(Word *w1,Word *w2){
    return strcmp( word.fwd(w1), word.fwd(w2) );
}

// hash so that the first character of the word indexes the bucket
inline int dict_class::hash(Word *w,int size){
    char* p=word.fwd(w);
    unsigned char c=(*p); // the first character
    int i=(int)(c-(unsigned char)('a'));
    if(i<0 || i>=size){
        printf("hash() error: word=%s bucket=%d size=%d\n",p,i,size);
        i=0;
    }
    return i;
}

#define BSIZE 80

int main(int argc,char **argv){
    FILE *file1,*file2;
    char buff[BSIZE],name[BSIZE],c;
    unsigned char u,ua,uz;
    int i,num,sz;
    Root *rp;
    Word *wp,*ws,ww;
    dict_iterator it;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");
    if(!file1 || !file2)return 1;
    rp=new Root;

    // create a dictionary with one bucket for each word of the alphabet
    ua='a'; uz='z'; u=uz-ua+1; sz=(int)u;
    dict.form(rp,sz);

    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s",&c,name);
        if(c=='A'){
            wp=new Word(name);
            dict.add(rp,wp);
        }
        else if(c=='D'){
            word.add(&ww,name);
            wp=dict.get(rp,&ww);
            if(!wp)fprintf(file2,"<%s> does not exist, cannot delete\n",name);
            else dict.del(rp,wp);
            (void)word.del(&ww);
        }
        else fprintf(file2,"wrong instruction on the input file=%c\n",c);
    }

    sz=dict.size(rp,&num);
    fprintf(file2,"resulting table: %d buckets, %d words\n",sz,num);

    //test traversal using the bucket iterator
    fprintf(file2,"traversing the table with the bucket iterator\n");
    for(i=0; i<sz; i++){
        ws=dict.slot(rp,i);
        it.start(ws);
        ITERATE(it,wp){ fprintf(file2,"%s\n",word.fwd(wp)); }
    }

    //test traversal using the table iterator
    fprintf(file2,"\ntraversing the table with the global iterator\n");
    it.start(rp); // or: dict_iterator itg; itg.start(rp);
    ITERATE(it,wp){
        fprintf(file2,"%s\n",word.fwd(wp)); 
    }
    return 0;
}
#include "zzfunc.c"






