#include <iostream>

using namespace std;

class node{
public:
	int item;
	node *left;
	node *right;
    node *prnt;

	node(){
		left = right = prnt = NULL;
	}

	node(int item) {
		this->item = item;
		left = right = NULL;
	}
};

class Tree{
private:
    node *root;
    int size;
    node* insert(node*,int);
    int search(node*,int);
    void display(node*);
public:
    Tree() { 
        size = 0; 
        root = NULL; 
    }    
    void insert(int);
    int search(int);    
    void display();        
    int getSize() { return size; }    
};

void Tree::insert(int x) {
    root = insertNode(root,x);
    size++;
}

node* Tree::insert(node* root,int item) {
    if(root == NULL) {
        root = new node(item);
        return root;
    } 
    else {
        if(item >= root->item) {
            root->right = insert(root->right,item);
            root->right->prnt = root;
        } 
        else
        if(item < root->item) {
            root->left = insert(root->left,item);
            root->left->prnt = root;
        }
    }
    return root;
}

void Tree::display(node* root){
    if(root != NULL){
        display(root->left);
        cout << root->item << " ";
        display(root->right);
    }
}

void Tree::display() {
    display(root);
}

int Tree::search(int item) {
    return search(this->root,item);
}

int Tree::search(node *root, int item) {
    if(root != NULL){
        if(item == root->item){            
            return 1;
        }
        else if(item > root->item){
            if(root->right == NULL)
                return size + 1;
            else
                return 1 + search(root->right,item);
        }
        else if(item < root->item){
            if(root->left == NULL)
                return size + 1;
            else
                return 1 + searchNode(root->left,item);
        }
    }
    else {
        root = this->root;
        return search(root,item);
    }
    return 0;
}

int main(){
    int T,Telem,elem;
    Tree tree;
    cin >> T;
    while(T > 0){
        
        bool check = false;
        cin >> Telem;
        while(Telem > 0){
            cin >> elem;
            tree.insert(elem);
            Telem--;
        }
        
        int searchelem;
        cin >> searchelem;
        int count = tree.searchNode(searchelem);
        if(count < tree.getSize())
            cout << count << " FOUND" << endl;
        else
            cout << count-tree.getSize() << " !FOUND" << endl;
        T--;
    } 

    return 0;
}