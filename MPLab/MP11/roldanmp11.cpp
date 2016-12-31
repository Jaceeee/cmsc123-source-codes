/**
*
* MP Lab by Michael Loewe Alivio and Juan Carlos Roldan
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
class Stack{
private:
    node<T> *top;
    int size;
public:
    Stack(){
        size = 0;
        top = NULL;
    }
    Stack(const Stack&);
    ~Stack();
    void insertFront(T);
    T peek();
    int getSize() { return size; }
    Stack<T> operator=(Stack<T>);
    bool pop();
    void display();    
};

template <class T>
bool Stack<T>::pop() {
    if(size == 0)
        return false;

    node<T> *del;    //same implementation for queue as well; nothing changed
    del = top;
    top = del->next;
    del->next = NULL;
    delete del;
    size--;
    return true;
}

template <class T>
T Stack<T>::peek(){
    if(size != 0)
        return top->data;
    else
        throw 404;
}

template <class T>
Stack<T>::~Stack(){
    while(size > 0){
        pop();
    }
}


template <class T>
Stack<T>::Stack(const Stack& a){
    node<T>* trav = a.top;
    size = 0;

    while(trav != NULL){
        insertFront(trav->data);
        trav = trav->next;
    }
}

template <class T>
void Stack<T>::insertFront(T item){

    node<T> *tmp = new node<T>(item);

    tmp->next = top;
    top = tmp;  
    size++;
}

//display
template <class T>
void Stack<T>::display(){
    if(size > 0){
        node<T> *trav = top;
        while(trav != NULL){
            cout << trav->data << " ";
            trav = trav->next;
        }
    }
    cout << endl;
}

template <class T>
Stack<T> Stack<T>::operator=(Stack<T> l){
    size = 0;
    top = NULL;
    node<T>* trav = l.top;
    while(trav != NULL) {
        insertFront(trav->data);
        trav = trav->next;
    }
}

int main(){
    int T;
    cin >> T;
    Stack<int> l;

    while(T > 0){
        int item;
        int option;
        cin >> option;
        switch (option){
            case 1:
                cin >> item;
                l.insertFront(item);
                l.display();
                break;
            case 2:
                l.pop();
                l.display();
                break;
            case 3:
                try{
                    cout<<l.peek()<<endl;
                }
                catch(int err){
                    if(err == 404){
                        cout<<"stack is empty."<<endl;
                    }
                }
                break;
            default:
                l.display();                
        }
        T--;
    }
    return 0;
}
