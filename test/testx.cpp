#include <stdio.h>
int main(){
#ifndef FILE
	printf("NOT FILE\n");
#endif
#ifdef FILE
	printf("FILE\n");
#endif

    return 0;
}   
