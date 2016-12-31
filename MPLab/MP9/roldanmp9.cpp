#include <iostream>

using namespace std;

template <class T>
class node{
public:
	T data;
	node *next, *prev;
	node(){		
		prev = next = NULL;
	}
	node(T item){
		data = item;
		prev = next = NULL;
	}
};

template <class T>
class List{
public:
struct iterator{    
    node<T>* pointer;
    iterator& operator++(int){pointer = pointer->next; return (*this);}
    iterator& operator--(int){pointer = pointer->prev; return (*this);}
    T operator*(){return pointer->data;}
    bool operator!=(const iterator& it){return pointer!=it.pointer;}
};
private:
	node<T> *head, *tail;
	int size;
	iterator iter;
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
	iterator begin(){iter.pointer = head; return iter;}
    iterator end(){iter.pointer = tail->next; return iter;}
};

void display(List<int> l){
	if(l.getSize() > 0){
		List<int>::iterator it;	
		for(it = l.begin(); it != l.end(); it++)
			cout << *it << " ";			
	}
	cout << endl;
}

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
		node<T> *trav;
		int i;
		if(pos > size/2){
			i = size - 1;			
			trav = tail;	
			while(i > pos){
				i--;
				trav = trav->prev;
			}			
		}
		else {
			trav = head;
			i = 0;
			while(i < pos){
				i++;
				trav = trav->next;
			}
			
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
			head = del->next; // del HEAD --- new head
			if(head != NULL)
				head->prev = NULL;
		}
		else{
			int i = 0;

			while(i < pos - 1){
				tmp = tmp->next;
				i++;
			}

			del = tmp->next;
			node<T> *tmp2 = del->next;
			
			tmp->next = tmp2; // tmp --- del ---- del->next (tmp2)

			if(pos == size - 1)
				tail = tmp;			
			else
				tmp2->prev = tmp;
		}
		del->prev = NULL;
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
			head->prev = tmp;
			head = tmp;					
		}
		else if(pos == size){
			tail->next = tmp;
			tmp->prev = tail;
			tail = tmp;
		}
		else{
			int i = 0;
			while(i < pos - 1){
				trav = trav->next;
				i++;
			}
			
			node<T> *tmp2 = trav->next; //trav->next->prev = tmp;

			tmp->next = tmp2;
			tmp2->prev = tmp;
			tmp->prev = trav;
			trav->next = tmp;			//trav -- node to be inserted tmp <-- trav->next (tmp2)	
		}						
	}
	size++;
	return true;
}

template <class T>
T List<T>::get(int pos){	
	if(pos < 0 || pos >= size)
		throw 404;
	else{
		node<T> *trav;
		int i;
		if(pos < size/2){			
			i = 0;
			trav = head;
			while(i < pos){
				trav = trav->next;
				i++;
			}
		}
		else{
			i = size - 1;
			trav = tail;
			while(i > pos){
				trav = trav->prev;
				i--;
			}	
		}
		return trav->data;		
	}		
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
            case 4:
            	cin >> pos >> item;
            	l.set(item,pos);
            	display(l);
            	break;
        }        		
		T--;
	}	
	
	return 0;
}   