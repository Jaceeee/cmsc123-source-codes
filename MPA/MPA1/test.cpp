#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(){
	char a[] = "Hello World!";
	char *ptr;

	ptr = strtok(a," ");

	while(ptr!=NULL){
		for(int i=0; ptr[i]!='\0'; i++){
            printf("%c",ptr[i]);
		}
		printf("\n");
		ptr = strtok(NULL," ");

	}
	return 0;
}
