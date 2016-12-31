#include <iostream>

using namespace std;

template <class T>
class node{
public:
	T data;
	node* next;
	node(){		
		next = NULL;
	}
	node(T item){
		data = item;
		next = NULL;
	}
};

template <class T>
class List{
private:
	node<T> *head, *tail;
	int size;
public:
	List(){
		size = 0;
		head = tail = NULL;
	}
	List(const List&);
	bool insert(T,int);
	T get(int);	
	int getSize() { return size; }
	List<T> operator=(List<T>);
	node<T>* getHead() { return head; }
};

template <class T>
List<T>::List(const List& a){	
	node<T>* trav = a.getHead();
	int i = 0;
	size = 0;

	while(i < a.size){
		insert(trav->data,i);
		trav = trav->next;
		i++;
	}
}

template <class T>
bool List<T>::insert(T item, int pos){
	if(pos < 0 || pos > size)
		return false;
	else if(size == 0){
		node<T> *tmp =  new node<T>(item);
		head = tail = tmp;
	}
	else{		
		node<T> *trav = head, *tmp = new node<T>(item);
					
		if(pos == 0){
			tmp->next = head;
			head = tmp;
			size++;
			return true;
		}

		int i = 0;
		while(i < pos - 1){
			trav = trav->next;
			i++;
		}
		tmp->next = trav->next;
		trav->next = tmp;

		if(pos == size){
			tail = tmp;
		}
				
	}
	size++;
	return true;
}

template <class T>
T List<T>::get(int pos){	
	int i = 0;
	node<T> *trav = head;
	while(i < pos){
		trav = trav->next;
		i++;
	}
	return trav->data;
}

template <class T>
void display(List<T> l){
	node<T> *trav = l.getHead();
	while(trav!=NULL){
		cout << trav->data << " ";
		trav = trav->next;
	}
	cout << endl;
}

template <class T>
List<T> List<T>::operator=(List<T> l){
	size = 0;
	head = tail = NULL;

	node<T>* trav = l.head;
	
	int i = 0;
	while(trav != NULL)	{
		insert(trav->data,i);
		trav = trav->next;
		i++;
	}	
}

int main(){
	int T;    
	cin >> T;    
	List<int> l;
	
	while(T > 0){
		int item, pos;       
		cin >> pos >> item;        
		l.insert(item,pos);		
		display(l);
		T--;
	}

	List<int> a = l;	
	display(a);
	return 0;
}