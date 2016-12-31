#include <iostream>

using namespace std;

class vector{
private:
    int max;
    int *items;
    int size;
    void expand();
public:
    static const int INCREM = 5;
    vector();
	bool insert(int,int);
	bool remove(int);
	void removeAll();
    int& operator[](int);
    int getSize();
    friend ostream& operator<<(ostream&, vector);
};

vector::vector(){
    items = new int[5];
    max = 5;
    size = 0;
}

bool vector::insert(int data, int pos){
	int i;
	if(pos < 0 || pos > size)
        return false;

    if(size == max){
        expand();
    }
	for(i = size; i>pos; i--){
		items[i] = items[i-1];
	}
	items[i] = data;
	size++;
	return true;
}

bool vector::remove(int pos){
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

int& vector::operator[](int pos){
	return items[pos];
}

int vector::getSize(){
	return size;
}

void vector::expand(){
    int *newArr = new int[max + INCREM];
    for(int i = 0; i < size; i++){
        newArr[i] = items[i];
    }
    delete[] items;
    max += INCREM;
    items = new int[max];
    for(int i = 0; i < size; i++){
        items[i] = newArr[i];
    }
    delete[] newArr;
}

void vector::removeAll(){
	while(size > 0){
		remove(0);
	}
}


ostream& operator<<(ostream& out, vector n){
    for(int i = 0; i < n.size; i++)
        out<<n[i]<<" ";
    out<<endl;
	return out;
}

bool checkAscending(vector);
void removeDuplicates(vector&);

int main(){
    vector a;
    vector &pa = a;
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
        removeDuplicates(pa);
        cout<<a;
    	a.removeAll();
    	T--;
    }
    return 0;
}

bool checkAscending(vector a){	//try to make these functions independent of each other: checkAscending() and removeDuplicates()
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

void removeDuplicates(vector &a){
	int i, j;
	for(i = 0; i<a.getSize()-1; i++){
		for(j = i + 1; j<a.getSize(); j++){
			if(a[i] == a[j]){
				a.remove(j);
				j--;
			}
		}
	}
}
