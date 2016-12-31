//We, Loewe Alivio and Jace Roldan swear that we did this MP on our own.
//11/10/2016
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
    //following functions have private access due to the root having private access
    int remove(node*, int);
    void display(node*);
    node* insert(node*,int);
    int search(node*,int);
public:
    Tree() { 
        size = 0; 
        root = NULL; 
    }
    ~Tree();
    void insert(int);
    int remove(int);
    void display();    
    int search(int);    
    int getSize() { return size; }    
};

Tree::~Tree() {
    while(root != NULL)
        remove(root,root->item);
}

void Tree::insert(int x) {
    root = insert(root,x);
    size++;
}

node* Tree::insert(node* root,int item) {
    if(root == NULL){
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

int Tree::remove(int x) {
    return remove(this->root,x);
}

int Tree::remove(node* root, int x) {
    if(root != NULL) {
        if(root->item == x) {
            node *del = root;
            if(del->left == NULL && del->right == NULL) {
                if(del->prnt != NULL) {
                    if(del->prnt->right == del) {
                        del->prnt->right = NULL;
                    }
                    else if(del->prnt->left == del) {
                        del->prnt->left = NULL;
                    }
                    del->prnt = NULL;
                }
                if(del == this->root) {
                   this->root = NULL;   
                }
            }
            else if(del->left != NULL && del->right != NULL) {
                node* tmp2 = del->right;
                while(tmp2->left != NULL) {
                    tmp2 = tmp2->left;
                }
                del->item = tmp2->item;
                del = tmp2;
                return remove(del, tmp2->item);                        
            }                     
            else {
                bool drtn = false;
                node *tmp = del->prnt;

                if(tmp != NULL) {
                    if(tmp->right == del)
                        drtn = true;            
                    else if(tmp->left == del)
                        drtn = false;      

                    if(del->right == NULL) {
                        if(drtn)
                            tmp->right = del->left;                                        
                        else
                            tmp->left = del->left;                                                                        
                        del->left->prnt = tmp;           
                        del->prnt = NULL;
                        del->left = NULL;
                    }
                    else if(del->left == NULL) {
                        if(drtn)
                            tmp->right = del->right;                                    
                        else
                            tmp->left = del->right;
                        del->right->prnt = tmp;
                        del->prnt = NULL;
                        del->right = NULL;
                    }                    
                }

                else if (tmp == NULL) {
                    if(del->right != NULL) {
                        this->root = del->right;
                        del->right->prnt = NULL;
                    }                        
                    else if(del->left != NULL) {
                        this->root = del->left;
                        del->left->prnt = NULL;                        
                    }
                }                    
            }
                                   
            delete del;            
            del = NULL;
            return 1;
        }
        else if(x < root->item)
            return 1 + remove(root->left,x);    
        else if(x > root->item)
            return 1 + remove(root->right, x);                
    }
    else if(root == NULL)
        return size;
    return 0;
}

int Tree::search(int x) {
    return search(this->root,x);
}

int Tree::search(node *root, int item) {
    if(item == root->item)
        return 1;        
    else if(item > root->item) {
        if(root->right == NULL)
            return size + 1;
        else
            return 1 + search(root->right,item);
    }
    else if(item < root->item) {
        if(root->left == NULL)
            return size + 1;
        else
            return 1 + search(root->left,item);
    }    
    return 0;
}

void Tree::display() {
    display(root);
}

void Tree::display(node* root) {
    if(root != NULL) {
        display(root->left);
        cout << root->item << " ";
        display(root->right);
    }
}

/*
Input:
    This program has four groups of input. The first is the number of test cases T. Each test case will be composed of Telem tree nodes,
    followed by a sequence of Telem [elem] integers. What follows is the item to be deleted, deleteElem.
    It displays the number of comparisons made by the search traversal for that deleteElem, and whether that element is found in the tree
    or not.
*/
    
int main() {
    int T,Telem,elem;    
    cin >> T;
    while(T > 0) {
        Tree tree;
        bool check = false;
        cin >> Telem;
        while(Telem > 0) {
            cin >> elem;
            tree.insert(elem);
            Telem--;
        }
        
        int deleteElem;
        cin >> deleteElem;
        int count = tree.remove(deleteElem);
        if(count <= tree.getSize())
            cout << count << " DELETED" << endl;
        else
            cout << count-tree.getSize() << " !FOUND" << endl;        
        T--;
    }    
    return 0;
}