/**
*
* MP Lab by Michael Loewe Alivio, Juan Carlos Roldan and Jeza Marie Marturillas
*
**/
#include <iostream>

using namespace std;

template <class T>
class node{
public:
	T data;
	node *next;

	node(){ next = NULL; }
	node(T item){
		data = item;
		next = NULL;
	}
};

template <class T>
class Queue{
private:
	node<T> *head, *tail;
	int size;
public:
	Queue(){
		size = 0;
		head = tail = NULL;
	}
	Queue(const Queue&);
    ~Queue();
    void append(T);
	int getSize() { return size; }
	Queue<T> operator=(Queue<T>);
    bool remove();
    void display();
    T lookFront();
    T lookBack();
};

template <class T>
bool Queue<T>::remove() {
    if(size == 0)
        return false;

    node<T> *del;
    del = head;
    head = del->next;
    del->next = NULL;
    delete del;
    size--;
    return true;
}

template <class T>
T Queue<T>::lookFront(){
    if(size != 0)
        return head->data;
    else
        throw 404;
}


template <class T>
T Queue<T>::lookBack(){
    if(size != 0)
        return tail->data;
    else
        throw 404;
}


template <class T>
Queue<T>::~Queue(){
    while(size > 0){
        remove();
    }
}


template <class T>
Queue<T>::Queue(const Queue& a){
	node<T>* trav = a.head;
	size = 0;

	while(trav != NULL){
		append(trav->data);
		trav = trav->next;

	}
}

template <class T>
void Queue<T>::append(T item){

    if(size == 0){
		node<T> *tmp =  new node<T>(item);
		head = tail = tmp;
	}
	else{
		node<T> *tmp = new node<T>(item);

		tail->next = tmp;
        tail = tmp;

	}
	size++;
}

//display
template <class T>
void Queue<T>::display(){
    if(size > 0){
        node<T> *trav = head;
        while(trav != NULL){
            cout << trav->data << " ";
            trav = trav->next;
        }
    }
    cout << endl;
}

template <class T>
Queue<T> Queue<T>::operator=(Queue<T> l){
	size = 0;
	head = tail = NULL;
	node<T>* trav = l.head;
    while(trav != NULL)	{
        append(trav->data);
		trav = trav->next;
	}
}

int main(){
	int T;
	cin >> T;
	Queue<int> l;

	while(T > 0){
        int item;
		int option;
		cin >> option;
		switch (option){
            case 1:
                cin >> item;
                l.append(item);
                l.display();
                break;
            case 2:
                l.remove();
                l.display();
                break;
            case 3:
                try{
                    cout<<l.lookFront()<<endl;

                }
                catch(int err){
                    if(err == 404){
                        cout<<"queue is empty."<<endl;
                    }

                }
                break;
            case 4:
                try{
                    cout<<l.lookBack()<<endl;
                }
                catch(int err){
                    if(err == 404){
                        cout<<"queue is empty."<<endl;
                    }
                }
        }
		T--;
	}
	return 0;
}
