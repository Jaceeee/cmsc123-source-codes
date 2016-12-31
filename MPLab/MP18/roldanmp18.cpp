//MP by Michael Loewe Alivio and Juan Carlos Roldan
#include <iostream>
#include <limits>

using namespace std;

//max size = 2^d, where d = 9
class HTable{
private:
	int* arr;
	int size;
	int max;
	int hash(int);
public:
	HTable();
	HTable(int);
	~HTable(){
		delete arr;
	}
	
	int insert(int);
	int search(int);
	void display();
};

HTable::HTable(){
	size = 0;
	max = 1<<8;
	arr = new int[max];

	for(int i = 0; i<max; i++){
		arr[i] = numeric_limits<int>::infinity();
	}
}

HTable::HTable(int d){
	size = 0;
	max = 1<<d;
	arr = new int[max];

	for(int i = 0; i<max; i++){
		arr[i] = numeric_limits<int>::infinity();
	}
}

//16 = w, 8 = 9
int HTable::hash(int x){
	return ((60147*x)%(1<<16)) / (1<<7);
}

int HTable::insert(int x){
	int index = hash(x);
	int i = 0;

	while(arr[index] != numeric_limits<int>::infinity()){
		index = (index+1) % max;
		i++;
		if(i == max)
			return i;
	}
    
    arr[index] = x;
	return i;
}

int HTable::search(int x){
	int index = hash(x);
	int i = 0;

	while(arr[index] != x){
		index = (index+1) % max;
		i++;
		if(i == max)
			return 0;
	}
	return i;
}

void HTable::display() {
	for(int i = 0; i<max; i++){
		cout<<arr[i];
	}
	cout << endl;
}

int main(){	
	int T;
	cin >> T;
	for(; T>0; T--){
		HTable h(9);
		int inputNumber;
		cin >> inputNumber;
		for(; inputNumber>0; inputNumber--){
			int input;
			cin >> input;
			cout << h.insert(input)<<" ";
		}
		cout<<endl;
		int searchItem;
		cin>>searchItem;
		cout<<h.search(searchItem)<<endl;
	}

	return 0;
}	