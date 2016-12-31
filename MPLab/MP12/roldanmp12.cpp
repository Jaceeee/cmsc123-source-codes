#include <stack>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class node{
public:
	string item;
	node *left;
	node *right;
	node *prnt;

	node(){
		left = right = prnt = NULL;
	}

	node(string item) {
		this->item = item;
		left = right = prnt = NULL;
	}    
};

int append_to_stack(stack<int>*,node*);
node* addItem(node*,string);

class Tree{
private:
	node* root;
public:
	Tree(){
		root = NULL;
	}
    Tree(node* root){
        this->root = root;
    }
    void display(node* a);
};

void Tree::display(node* a){
    if(a != NULL){                
        display(a->left);                
        display(a->right);                
        cout<<a->item<<" ";
    }    
}

node* add_item_to_tree(node* r,string x,node* prev){
    r->left = new node(); //initialized this for some reason I don't know yet
    r->right = new node(); //taking these two statements will invalidate the next several
    r->prnt = prev;
    for(int i = x.length()-1; i >= 0; i--){        
        if(x[i] == '+' || x[i] == '-'){            
            r->left = add_item_to_tree(r->left,x.substr(0,i),r);            
            r->right = add_item_to_tree(r->right,x.substr(i+1, x.length() - i),r);            
            r->item = x.substr(i,1);
            return r;
        }
    }
    for(int i = x.length()-1; i >= 0; i--){
        if(x[i] == '*' || x[i] == '/'){
            r->left = add_item_to_tree(r->left,x.substr(0,i),r);
            r->right = add_item_to_tree(r->right,x.substr(i+1,x.length()-i-1),r);               
            r->item = x.substr(i,1);
            return r;
        }
    }
    for(int i = 0; i < x.length(); i++){
        if(x[i] == '^'){
            r->left = add_item_to_tree(r->left,x.substr(0,i),r);
            r->right = add_item_to_tree(r->right,x.substr(i+1,x.length()-i-1),r);               
            r->item = x.substr(i,1);
            return r;
        }
    }
    r->item = x;
    r->left = NULL;
    r->right = NULL;
    r->prnt = prev;
    return r;
}

int append_to_stack(stack<int> *s, node *n){
    if(n->left == NULL && n->right == NULL){        
        return atoi(n->item.c_str());
    }
    else if(n!=NULL){
        int operation, result;
        int a = append_to_stack(s,n->left);        
        int b = append_to_stack(s,n->right);
        s->push(a);
        s->push(b);
        operation = n->item[0];
        b = s->top();
        s->pop();
        a = s->top();
        s->pop();
        if(operation == '+')
            result = a + b;
        else if(operation == '-')
            result = a - b;
        else if(operation == '*')
            result = a * b;
        else if(operation == '/')
            result = a / b;
        else if(operation == '^')
            result = pow(a,b);
        s->push(result);        
        return result;
    }
    return 0;
}

int main() {
    int T;
    string input;

    cin>>T;    
    node* root = new node();
    Tree tree = Tree(root);
    while(T > 0){        
        stack<int> s;
        cin>>input;
        root = add_item_to_tree(root,input,NULL);
        append_to_stack(&s,root);
        cout<<s.top()<<endl;
        T--;
    }
    return 0;
}