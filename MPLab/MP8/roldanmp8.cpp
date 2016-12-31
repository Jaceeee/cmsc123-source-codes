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
	~List();
	bool insert(T,int);
	T get(int);	
	int getSize() { return size; }
	List<T> operator=(List<T>);
	node<T>* getHead() { return head; }
	bool remove(int);
	bool set(T,int);
};

template <class T>
List<T>::List(const List& a){	
	tail = head = NULL;
	node<T>* trav = a.head;	
	int i = 0;
	size = 0;

	while(i < a.size){
		insert(trav->data,i);
		trav = trav->next;
		i++;
	}	
}

template <class T>
List<T>::~List(){
	while(size > 0){
		remove(0);
	}
}

template <class T>
bool List<T>::set(T item, int pos){
	if(pos < 0 || pos >= size){
		return false;
	}
	else{
		node<T> *trav = head;
		int i = 0;
		while(i < pos){
			i++;
			trav = trav->next;
		}
		trav->data = item;
		return true;
	}
}

template <class T>
bool List<T>::remove(int pos){
	if(pos < 0 || pos >= size)
		return false;
	else{
		node<T> *del, *tmp = head;

		if(pos == 0){
			del = head;
			head = del->next;			
		}
		else{
			int i = 0;

			while(i < pos - 1){
				tmp = tmp->next;
				i++;
			}

			del = tmp->next;
			tmp->next = del->next;			
		}

		if(pos == size - 1){
			tail = tmp;
		}

		del->next = NULL;
		delete del;
		size--;
	}	
	return false;
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
	if(pos < 0 || pos >= size)
		throw 404;
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
	if(l.getSize() > 0){
		node<T> *trav = l.getHead();
		while(trav!=NULL){
			cout << trav->data << " ";
			trav = trav->next;
		}		
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
        int option, pos, item;
        cin >> option;
        switch(option){
            case 1:                
                cin >> pos >> item;        
                l.insert(item,pos);
                display(l);
                break;
            case 2:                
                cin >> pos;
                l.remove(pos);
                display(l);
                break;
            case 3:
                cin >> pos;
                try{
                    cout << l.get(pos) << endl;
                }
                catch(int err){
                    if(err ==  404)
                        cout << "POSITION OUT OF BOUNDS" << endl;                    
                }
                break;
        }        		
		T--;
	}
	l.set(0,1)

	display(l);
	return 0;
}   