
    if(root == NULL) {
        root = new node(item);
        return root;
    }
    else {
        bool htChk = (root->right != NULL || root->left != NULL) ? false : true;
        if(item >= root->item) {
            root->right = insert(root->right,item);
            
            root->right->parent = root;            
            if(htChk) {
                update(root,root->right);
            }
            if(root->height > 1){
                root = checker(root);                
                cout<<"Root: " << root->item<<endl;
                cout<<"left: " <<root->left->item<<endl;
                cout<<"right: " <<root->right->item<<endl;                
                
                cout<<"Root: " << this->root->item<<endl;
                return root;
            }                
        }
        else if(item < root->item) {
            root->left = insert(root->left,item);            
            root->left->parent = root; 
            if(htChk) {
                update(root,root->left);
            }                       
            if(root->height > 1) {
                root = checker(root);
                return root->parent;
            }
                
        }
    }
    updateBalances(root);    
    return root;