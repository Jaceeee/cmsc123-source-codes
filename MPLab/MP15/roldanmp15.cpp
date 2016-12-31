//We, Loewe Alivio and Jace Roldan swear that we did this MP on our own.
//11/14/2016
#include <iostream>
#include <cmath>

using namespace std;

enum {
    LEFT = 1,
    RIGHT = 2,
    LEFTRIGHT = 3,
    RIGHTLEFT = 4
};

template <class T>
class node{
public:
    T item;
    node *left;
    node *right;
    node *parent;
    int height; //updated during insert
    int balance; //updated during insert

    node() {
        left = right = parent = NULL;
        height = 0;
        balance = 0;
    }

    node(int item) {
        this->item = item;
        left = right = parent = NULL;
        height = 0;
        balance = 0;
    }
};

template <class T>
class AVLTree{
private:
    node<T> *root;
    int size;
    //following functions private access due to the root having private access
    int remove(node<T>*, int);
    void display(node<T>*);
    node<T>* insert(node<T>*,int);
    int search(node<T>*,int);
    //special auxiliary AVL functions
    void rightRotate(node<T>*);
    void leftRotate(node<T>*);
    void rightLeftRotate(node<T>*);
    void leftRightRotate(node<T>*);
    bool updateHeights(node<T>*,bool);
    void updateBalances(node<T>*);
    void update(node<T>*,node<T>*);
    int checkViolation(node<T>*);
    void checker(node<T>*);
public:
    AVLTree() {
        size = 0;
        root = NULL;
    }
    ~AVLTree();
    void insert(int);
    int remove(int);
    void display();
    int search(int);

    int getSize() { return size; }
};

template <class T>
AVLTree<T>::~AVLTree() {
    while(root != NULL)
        remove(root,root->item);
}

template <class T>
void AVLTree<T>::insert(int x) {
    root = insert(root,x);
    size++;    
}

template <class T>
node<T>* AVLTree<T>::insert(node<T>* root,int item) {    
    if(root == NULL)
        return this->root = new node<T>(item);

    node<T>* tmp = this->root;
    while(tmp != NULL) {
        bool htChk = (tmp->right != NULL || tmp->left != NULL) ? false : true;

        if(item < tmp->item){            
            if(tmp->height > 1) {
                checker(tmp);
            }
            if(tmp->left == NULL) {
                tmp->left = new node<T>(item);
                tmp->left->parent = tmp;
                update(tmp,tmp->left);
                break;
            }
            else
                tmp = tmp->left;
        }
 
        else if(item > tmp->item) {
            if(tmp->height > 1) {
                checker(tmp);
            }
            if(tmp->right == NULL) {
                tmp->right = new node<T>(item);
                tmp->right->parent = tmp;
                update(tmp,tmp->right);        
                break;
            }
            else
                tmp = tmp->right;            

        }
    }            

    return this->root;
        
}

template <class T>
void AVLTree<T>::checker(node<T> *root){
    if(checkViolation(root) == LEFT){
        rightRotate(root->left);        
    }
    else if(checkViolation(root) == RIGHT){                
        leftRotate(root->right);
    }
    else if(checkViolation(root) == LEFTRIGHT){
        rightLeftRotate(root->right);
    }
    else if(checkViolation(root) == RIGHTLEFT){
        leftRightRotate(root->left);
    }    
}

template <class T>
void AVLTree<T>::leftRotate(node<T> *n){ //right leaning violation        
    cout<<"Left Rotate!"<<endl;
    node<T>* tmp = n->parent;        

    tmp->right = n->left;
    if(n->left != NULL)
        tmp->right->parent = tmp;

    n->left = tmp;
    tmp->height -= 2;

    n->parent = tmp->parent;

    tmp->parent = n;
    
    if(tmp == this->root){
        this->root = n;
        // if(tmp->height != 0)
        //     tmp->height--;
    }
    else {
        n->parent->right = n;        
    }
    
    // cout<<"Root: "<<root->item<<endl;
    // if(root->right != NULL)
    //     cout<<"Root->right: "<<root->right->item<<endl;
    // if(root->left != NULL)
    //     cout<<"Root->left: "<<root->left->item<<endl;
    // cout<<"n: " <<n->item<<endl;
    // // cout<<"Tmp: "<<tmp->item<<endl;    
    // if(n->parent!=NULL)
    //     cout<<"tmp: "<<tmp->item<<endl;
    
    node<T> *tmp2 = n->parent;
    
    while(tmp2 != NULL){
        tmp2->height--;
        tmp2 = tmp2->parent;
    }

    updateBalances(tmp);
    updateBalances(n);
}

template <class T>
void AVLTree<T>::rightRotate(node<T>* n) { //left leaning violation
    cout<<"Right Rotate!"<<endl;
    node<T> *tmp = n->parent;

    tmp->left = n->right;
    
    if(n->right != NULL)
        tmp->left->parent = tmp;
    
    n->right = tmp;
    n->right->height -= 2;

    n->parent = tmp->parent;    
    tmp->parent = n;

    if(tmp == this->root){        
        this->root = n;
        // tmp->height--;
        // if(tmp->height != 0){
        //     tmp->height--;
        // }
        // cout<<"Root: "<<root->item<<endl;
    }
    else 
        n->parent->left = n;    
    
    n->right->parent = n;

    node<T>* tmp2 = n->parent;

    while(tmp2 != NULL){
        tmp2->height--; 
        tmp2 = tmp2->parent;
    }
    updateBalances(tmp);
    updateBalances(n);
}

template <class T>
void AVLTree<T>::rightLeftRotate(node<T> *n){ //left-right leaning violation
    cout<<"Right-Left Rotate!"<<endl;
    int x;
    x = n->item;//swap
    n->item = n->left->item;
    n->left->item = x;

    node<T> *tmp = n->left; //temp node

    n->right = tmp; //super heavy         

    n->left = NULL;
    leftRotate(n);
}

template <class T>
void AVLTree<T>::leftRightRotate(node<T> *n){ //right-left leaning violation
    cout<<"Left-right Rotate!"<<endl;
    int x;
    x = n->item;
    n->item = n->right->item;
    n->right->item = x;

    node<T> *tmp = n->right;

    n->left = tmp;
    n->right = NULL;

    rightRotate(n);
}

template <class T>
int AVLTree<T>::remove(int x) {
    return remove(this->root,x);
}

template <class T>
int AVLTree<T>::remove(node<T>* root, int x) {
    if(root != NULL) {
        if(root->item == x) {
            node<T> *del = root;
            if(del->left == NULL && del->right == NULL) {
                if(del->parent != NULL) {
                    if(del->parent->right == del) {
                        del->parent->right = NULL;
                    }
                    else if(del->parent->left == del) {
                        del->parent->left = NULL;
                    }
                    del->parent = NULL;
                }
                if(del == this->root) {
                   this->root = NULL;
                }
            }
            else if(del->left != NULL && del->right != NULL) {
                node<T>* tmp2 = del->right;
                while(tmp2->left != NULL) {
                    tmp2 = tmp2->left;
                }
                del->item = tmp2->item;
                del = tmp2;
                return remove(del, tmp2->item);
            }
            else {
                bool drtn = false;
                node<T> *tmp = del->parent;

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
                        del->left->parent = tmp;
                        del->parent = NULL;
                        del->left = NULL;
                    }
                    else if(del->left == NULL) {
                        if(drtn)
                            tmp->right = del->right;
                        else
                            tmp->left = del->right;
                        del->right->parent = tmp;
                        del->parent = NULL;
                        del->right = NULL;
                    }
                }

                else if (tmp == NULL) {
                    if(del->right != NULL) {
                        this->root = del->right;
                        del->right->parent = NULL;
                    }
                    else if(del->left != NULL) {
                        this->root = del->left;
                        del->left->parent = NULL;
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

template <class T>
int AVLTree<T>::search(int x) {
    return search(this->root,x);
}

template <class T>
int AVLTree<T>::search(node<T> *root, int item) {
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

template <class T>
void AVLTree<T>::display() {    
    display(root);
    if(root->left != NULL)
        cout<<"Root->left->height: "<<root->left->height<<endl;
    if(root->right != NULL)
        cout<<"Root->right->height: "<<root->right->height<<endl;
}

template <class T>
void AVLTree<T>::display(node<T>* root) {    
    if(root != NULL) {        
        cout << root->item << " height: " << root->height << " balance: "<< root->balance <<endl;
        display(root->left);        
        display(root->right);
    }
}

template <class T>
bool AVLTree<T>::updateHeights(node<T>*n,bool side) {
    int a = (n->left != NULL) ? n->left->height + 1 : 0;
    int b = (n->right != NULL) ? n->right->height + 1 : 0;
        
    if((side && a >= b) || (!side && a <= b))
        return false;
    else
        return true;
}

template <class T>
void AVLTree<T>::updateBalances(node<T>* n) {
    int left = (n->left == NULL) ? 0 : n->left->height + 1;
    int right = (n->right == NULL) ? 0 : n->right->height + 1;

    if(right > left)
        n->balance = 1;
    else if(left > right)
        n->balance = -1;
    else
        n->balance = 0;
}

template <class T>
void AVLTree<T>::update(node<T>* n, node<T>* tmp2){
    while(n != NULL){
        // if(size == 5){
        //     if(n == root){
        //         cout<<"n: "<<n->item<<endl;
        //         cout<<"n->left->height: "<<n->left->height<<endl<<"n->right->height: "<<n->right->height<<endl;
        //     }
                
        //     cout<<"tmp2: "<<tmp2->item<<endl;
        // }
        bool side;

        if(tmp2 == n->left)
            side = false;
        else if(tmp2 == n->right)
            side = true;
        
        if(updateHeights(n,side))
            n->height++;

        updateBalances(n);                

        if(n->height > 1)
            checker(n);

        tmp2 = n;
        n = n->parent;
    }
}

template <class T>
int AVLTree<T>::checkViolation(node<T>* n){
    int left = (n->left == NULL) ? 0 : n->left->height + 1;
    int right = (n->right == NULL) ? 0 : n->right->height + 1;
    // if(size == 5 && n == root){
    //     cout<<"Hey !!"<<endl;        
    // }
    if(abs(left-right) > 1) {
        // if(n == root && size == 5)
        //     cout<<"went in"<<left<<" "<<right<<endl;
        if(left>right) {
            if(n->left->balance == -1 && n->balance == -1)
                return LEFT;
            else if(n->left->balance == 1 && n->balance == -1)
                return RIGHTLEFT;
        }
        else{
            if(n->right->balance == 1 && n->balance == 1)
                return RIGHT;
            else if(n->right->balance == -1 && n->balance == 1)
                return LEFTRIGHT;
        }
    }
    // if(size == 5 && n == root)
    //     cout<<"Returned 0"<<endl;
    return 0;
}
/*
Input:
    This program has four groups of input. The first is the number of test cases T. Each test case will be composed of Telem AVLTree nodes,
    followed by a sequence of Telem [elem] integers. What follows is the item to be deleteed, deleteElem.
    It displays the number of comparisons made by the search traversal for that deleteElem, and whether that element is found in the AVLTree
    or not.
*/

int main() {
    int T,Telem,elem;
    cin >> T;
    while(T > 0) {
        AVLTree<int> avlTree;
        bool check = false;
        cin >> Telem;
        while(Telem > 0) {
            cin >> elem;
            avlTree.insert(elem);
            Telem--;
        }

        int deleteElem;
        cin >> deleteElem;
        int count = avlTree.remove(deleteElem);
        if(count <= avlTree.getSize())
            cout << count << " DELETED!" << endl;
        else
            cout << count-avlTree.getSize() << " !FOUND" << endl;      
        avlTree.display();
        T--;        
    }
    return 0;
}