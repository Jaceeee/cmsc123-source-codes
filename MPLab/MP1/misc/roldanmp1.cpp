#include <stdio.h>

#define MAX 10

int function1(char[]);
int function2(char[]);

int main(){
	//int x;
	//scanf("%i",&x);

	char str[10];

	for(int j=0; j<10; i++){
		scanf("%i",&str[i]);
	}

	if(function1(str)!=-1)
		printf("%i, index %i\n",function1(str),function1(str));
	else
		printf("none\n");

	if(function2(str)!=-1)
		printf("%i, index %i\n",function2(str),function2(str));
	else
		printf("none\n");

	return 0;
}

int function1(char s[]){
//int function1(char s[], int x){
	for(int i = 0; i<MAX; i++){
		if(i == s[i])
			return i;

		if(s[i]>i)
			return -1;
	}

	return -1;
}

//int function2(char s[], int x){
int function2(char s[]){
	int lo = 0, hi = 1, mid;

	while(lo < hi){
		mid = (lo + hi) / 2;

		if(mid == s[mid])
			return mid;
		else if(lo == s[lo])
			return lo;
		else if(hi == s[hi])
			return hi;
		else{
			if(s[mid]>mid)
				hi = mid-1;
			else if(s[mid]<mid)
				lo = mid+1;
		}
	}

	return -1;
}
