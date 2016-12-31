//MP jointly performed by Loewe Alivio and Jace Roldan
#include <iostream>

using namespace std;

class Heap{
private:
	int *elem; //dynamically allocated at construction of heap instance
	int size;
public:
	Heap() {
		elem = new int[5];
		size = 0;
	}
	Heap(int size) {
		elem = new int[size*2];
		this->size = 0;
	}
	Heap(const Heap&);
	~Heap(){ delete elem; }
	void insert(int);
	bool remove();
	void display();
	int getSize() {return size;}
};

Heap::Heap(const Heap &h){ //copy constructor
	size = h.size;
	elem = new int[size];
	for(int i = 0; i<h.size; i++)
		elem[i] = h.elem[i];
}

void Heap::display(){
	int i = 1;
	while(i <= size){
		cout<<elem[i]<<" ";
		i++;
	}
	cout<<endl;
}

bool Heap::remove(){
	if(size == 0)
		return false;
	else{
		int i = 1, compChildren;	
		elem[1] = elem[size];
		bool direction = false;

		while(i*2 < size) {		
			if(elem[i * 2] < elem[(i * 2) + 1]){ //compares the children
				compChildren = elem[i*2];
				direction = false;
			}
			else {
				compChildren = elem[(i * 2) + 1];
				direction = true;
			}		
			if(compChildren < elem[size]) { //compares that to the last element 
				elem[i] = compChildren;
			}
			else{
				break;
			}
			
			i = (!direction) ? i * 2 : (i * 2) + 1; //determines which next two children to compare
		}
		elem[i] = elem[size];
		size--;		
	}
	return true;
}

void Heap::insert(int x){
	if(size == 0){
		elem[1] = x;
	}
	else{
		elem[size+1] = x;
		int i = size + 1;				
		while(x < elem[i/2] && i != 1) {
			elem[i] = elem[i/2];
			i/=2;
		}
		elem[i] = x;
	}
	size++;
}

int main(){	
	int T;
	cin>>T;
	for(; T>0; T--){
		int numberOfItems;
		cin>>numberOfItems;
		Heap heap(numberOfItems);
		for(; numberOfItems > 0; numberOfItems-- ){
			int elem;
			cin >> elem;				
			heap.insert(elem);
			
		}	
		int dltTimes;				
		cin >> dltTimes;
		for(;dltTimes > 0; dltTimes--){
			heap.remove();
			heap.display();
		}
	}
	
	return 0;
}
