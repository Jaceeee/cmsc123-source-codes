//MP by Michael Loewe Alivio and Juan Carlos Roldan
#include <iostream>
#include <limits>
#include <list>
#include <string>

using namespace std;

//max size = 2^d, where d = 9
class HTable{
private:
	list<string>* arr;
	int size;
	int max;
	int type;//hash function
	int hash(int);
	unsigned int hash1(string);
	unsigned int hash2(string);
public:
	HTable();
	HTable(int);
	~HTable(){
		delete[] arr;
	}
	
	int insert(string);
	int search(string);
	void display();
};

unsigned int HTable::hash1(string st){
	unsigned int h = 0;
	unsigned int len = st.length();
	for(unsigned int i = 0; i<len; i++){
		h = 31 * h + st[i];
	}
	return h;
}

unsigned int HTable::hash2(string st){
	unsigned int h = 0, high, i = 0;
	while(st[i] != '\0'){
		h = (h << 4) + st[i++];
		if(high = h & 0xF0000000)
			h ^= high >> 24;
		h &= ~high;
	}
	return h;
}

HTable::HTable(){
	size = 0;
	max = 1<<10;
	arr = new list<string>[max];

	type = 1;
}

HTable::HTable(int d){
	size = 0;
	max = 1<<10;
	arr = new list<string>[max];

	type = d;
}

int HTable::hash(int x){
	unsigned int h = ((60147*(unsigned int)x)%(1<<31)) / (1<< 21);
	return h;
}

int HTable::insert(string x){
	int index = (type == 1) ? hash(hash1(x)) : hash(hash2(x));	
    arr[index].push_back(x);
	return arr[index].size();
}

int HTable::search(string x){
	int index = (type == 1) ? hash(hash1(x)) : hash(hash2(x));
	int i = 0;
	list<string>::iterator it;
	it = arr[index].begin();
	while(it != arr[index].end()){
		i++;
		if((*it).compare(x) == 0)
			break;
		it++;
	}
	return i;
}

void HTable::display() {
	for(int i = 0; i<max; i++) {
		for(list<string>::iterator it = arr[i].begin(); it != arr[i].end(); it++)
			cout << (*it) << endl;
	}
	cout << endl;
}

int main(){	
	int T;
	cin >> T;
	for(; T>0; T--){
		HTable h1(1);
		HTable h2(2);
		int inputNumber;
		cin >> inputNumber;
		for(; inputNumber>0; inputNumber--){
			string input;
			cin >> input;

			cout << h1.insert(input)<<" ";			
			h2.insert(input);			
		}

		string searchItem;
		cin>>searchItem;

		cout<<h1.search(searchItem)<<" ";		
		cout<<h2.search(searchItem)<<endl;
	}

	return 0;
}