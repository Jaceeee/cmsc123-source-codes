/*
 * Output done by Juan Carlos Roldan in collab with Michael Loewe Alivio
 */
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int returnReverse(int); // returns the reverse of the user's input
bool checkPrime(int); // checks if the int argument is a prime or not. returns true if it is, and false otherwise

int main(){
    list<int> l;
    list<int>::iterator it;

    int T; //number of testcases
	int i = 0, input, reversed = 0;

	cin >> T;

    while(T>0){
        cin >> input;
        l.push_back(input);
        T--;
    }

    for(it = l.begin(); it != l.end(); it++){ //iterator goes from the start of the list until the last element and prints whether the item is an emirp or not.
        reversed = returnReverse(*it);
        if(checkPrime(*it) == true && checkPrime(reversed) == true){
            printf("YES\n",*it);
        }
        else{
            printf("NO\n",*it);
        }
    }

	return 0;
}

int returnReverse(int a){
	int tmp = 0;      //starts with a tmp = 0 and uses the modulo operator to take the digits every iteration.
	while(a != 0){
		tmp *= 10;      //multiplies tmp by 10 every time to accomodate the digits
		tmp += a % 10;
		a /= 10;        //decreases the digits by 1 every time
	}

	return tmp;
}

bool checkPrime(int a){
	if(a == 1 || a == 0){
        return false;
	}
	int cp = 2;
	while(cp * cp <= a){
		if(a%cp == 0){
			return false;
		}
		cp++;
	}
	return true;
}
