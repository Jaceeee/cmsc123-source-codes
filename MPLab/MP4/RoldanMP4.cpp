/*
 *  MP submitted by Juan Carlos Roldan in collaboration with Michael Loewe Alivio
 */
#include <iostream>

#define MAX 20

using namespace std;

class array{
private:
	int items[MAX];
	int size;
public:
	array();
	array(int);
	int getSize();
	int at(int);		
	bool insert(int,int);
	bool remove(int);
	void removeAll();
	int& operator[](int);	
};

array::array(){
	size = 0;
}

array::array(int n){	
	size = MAX;
	for(int i=0; i<size; i++)
		items[i] = n;
}

void array::removeAll(){
	while(size > 0){
		remove(0);
	}
}

bool array::insert(int data, int pos){
	int i;
	if(pos < 0 || pos > size || size == MAX){
		return false;
	}	

	for(i = size; i>pos; i--){
		items[i] = items[i-1];
	}

	items[i] = data;
	size++;
	return true;
}

bool array::remove(int pos){
	int i;
	if(pos < 0 || pos > size || size == 0){
		return false;
	}

	for(i = pos; i<size-1; i++){
		items[i] = items[i+1];
	}

	size--;
	return true;
}

int& array::operator[](int pos){
	return items[pos];
}

int array::getSize(){
	return size;
}
	
int array::at(int i){
	return items[i];
}
bool checkAscending(array);
void removeDuplicates(array*);
void display(array);

int main() {
    array a;
    array &a;
    int T, input;
    cin >> T;
    while(T>0){
    	int i = 0;
    	while(i<10){    		
    		cin >> input;    		
    		a.insert(input,i);    		    		
    		i++;        		
    	}    	 	    	    	       
    	if(checkAscending(a) == true){
    		cout<<"YES"<<endl;
    	} else{
    		cout<<"NO"<<endl;
    	}
        removeDuplicates(&a);
    	display(a);
    	a.removeAll();
    	T--;
    }
    return 0;
}

bool checkAscending(array a){	//try to make these functions independent of each other: checkAscending() and removeDuplicates()	        
    if(a.getSize() == 1){
		return false;
	}    
	int i, j, size = a.getSize(), c = a[0], b;
    bool duplicateCheck = true;
	for(i = 0; i<size-1; i++){
        b = a[i+1];
        if(a[i] > a[i+1]){
            return false;
        }
        if(c != b && duplicateCheck == true){
            duplicateCheck = false;
        }		
	}
 
    if(duplicateCheck){
        return false;
    }
	return true;
}

void removeDuplicates(array *a){
	int i, j;	
	for(i = 0; i<a->getSize()-1; i++){
		for(j = i + 1; j<a->getSize(); j++){
			if(a->at(i) == a->at(j)){				
				a->remove(j);				
				j--;		
			}
		}
	}	
}

void display(array a){
	for(int i = 0; i < a.getSize(); i++){
		cout<<a[i]<<" ";
	}
	cout << endl;
}