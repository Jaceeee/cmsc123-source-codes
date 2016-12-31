//Upon my honor, I declare that I made this MP by myself.
#include <iostream>
#include <stdio.h>

#define SIZE 10

using namespace std;

int solution(int[]);
int solution2(int[]);

int main()
{
    int A[SIZE];
    bool first, second;

    for(int i = 0; i<SIZE; i++)
        scanf("%i",&A[i]);

    if(solution(A)!= -1)
        printf("%i, index %i \n", solution(A), solution(A));
    else
        printf("None\n");
    if(solution2(A)!= -1)
        printf("%i, index %i \n", solution2(A), solution2(A));
    else
        printf("None\n");
    return 0;
}

int solution(int A[]){
    for(int i = 0; i<SIZE; i++){
        if(i == A[i])
            return i;
        if(A[i] > i)
            return -1; //stopper for unnecessary checks
    }
    return -1;
}

int solution2(int A[]){
    int hi = 9, lo = 0, mid;
    while(lo < hi && lo != hi){
        mid = (hi + lo ) / 2;

        if(mid==A[mid]) //checks if the middle element is the one
            return mid; //does not necesarily take the first element that matches indez
        else{   //otherwise, the program lessens the searching area
            if(mid>A[mid])
                hi = mid-1;
            else if(mid<A[mid])
                lo = mid+1;
        }
    }
    return -1;
}
