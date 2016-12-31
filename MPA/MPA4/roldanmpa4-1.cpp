//I declare upon my honor that I did this MPA by myself.
//when performing operations, user has to be at current directory where that operation is supposed to affect
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum {
	TFILE = 1,
	DIRECTORY = 0,
	PLACEHOLDER = -1	
};

string remove_leading_spaces(string);
string tokenize_loc_string(string*);
string up_level_aux(string);
string separator(string*);

class node {
public:
	node* parent;
	node* next_sibling;
	node* prev_sibling;
	node* next_level;
	string address;
	string val;
	string cont;
	int f_type;	   //0 for directory, 1 for TFILE


	node(string name, int type){
		val = name;
		f_type = type;
		parent = next_sibling = next_level = NULL;
		if(type == TFILE){
			cont = "Empty TFILE.";
		}
	}
};

bool check_present(node*, string);

class GeneralTree{
private:
	node* root;
	int tree_size;
	bool remove(node*, string, int);
	node* access(node*, string);
	void gen_display(node*);
	node* set_node_to_level(string*);	
public:
	GeneralTree(){
		root = new node("root",DIRECTORY);
		root->address = "";
		root->next_level = new node("root",PLACEHOLDER);
		root->next_level->parent = root;
	}
	~GeneralTree(){
		node *del, *tmp = root->next_level->next_sibling;
		
		while(tmp != NULL) {
			del = tmp;
			tmp = tmp->next_sibling;
			remove(del, del->val, del->f_type);
		}		
		root->next_level->next_sibling = root->next_level->parent = NULL;
		del = root->next_level;
		root->next_level = NULL;

		delete del;
		delete root;

		cout<<"Destructor successful."<<endl;
	}

	bool insert(string, int);	
	bool remove(string,int);
	node* access(string);
	void gen_display();
	void dir_display(string);
	void check_cont(string);
};

node* GeneralTree::access(string name){
	return access(root, name);
}

bool GeneralTree::remove(string name, int type){
	return remove(root->next_level, name, type);
}

node* GeneralTree::set_node_to_level(string *loc){
	node *trav = root->next_level;
	string a = *(loc), b, c ="";
	tokenize_loc_string(&a);
	
	b = tokenize_loc_string(&a);
	
	while(b.compare(c) != 0) {
		b = b.substr(1, b.size());
		while(trav != NULL){
			if(trav->val.compare(b) == 0){
				trav = trav->next_level;
				break;
			}
			trav = trav->next_sibling;
		}

		if(trav == NULL){
			return NULL;
		}
		b = tokenize_loc_string(&a);
	}

	a = a.substr(1, a.size());
	*(loc) = a;
	return trav;
}

void GeneralTree::gen_display(node* r){	
	r = r->next_level;
	bool isEmpty = true;
	string desc = "";

	desc += "Folder: " + r->val + "\n";	
	desc += "Contents:\n";

	node *tmp = r->next_sibling;
	while(tmp != NULL){
		if(tmp->f_type == TFILE){
			// cout<<tmp->val<<endl;
			desc += tmp->val + "\n";
			isEmpty = false;
		}
		else{
			desc += "<" + tmp->val + ">\n";
			gen_display(tmp);
			isEmpty = false;
		}
		tmp = tmp->next_sibling;
	}

	cout << desc << ((isEmpty) ? "<Empty>\n" : "") << endl;
}

bool GeneralTree::insert(string name, int type) {
	node* trav;
	string a = name;
		
	trav = set_node_to_level(&a); //might cause error in mkdir later, so check

	if(trav == NULL){
		cout << "Failed to insert at requested position." << endl;
		return false;
	}

	while(trav->next_sibling != NULL){
		if(a.compare(trav->next_sibling->val) == -1){
			break;
		}
		else 
		if(a.compare(trav->next_sibling->val) == 0) {
			throw 404;
		}
		else {
			trav = trav->next_sibling;
		}
	}

	node* tmp = new node(a, type);
	if(type == TFILE){
		cout << "Enter contents of file." << endl;
		getline(cin, tmp->cont);
	}

	tmp->next_sibling = trav->next_sibling;

	if(tmp->next_sibling != NULL){
		tmp->next_sibling->prev_sibling = tmp;
	}

	tmp->prev_sibling = trav;
	trav->next_sibling = tmp;

	if(type == DIRECTORY){
		tmp->next_level = new node(tmp->val, PLACEHOLDER);
		tmp->next_level->parent = tmp;
	}

	tmp->parent = tmp->prev_sibling->parent;	
	tmp->address = tmp->parent->address + "/" + tmp->parent->val;
}

bool GeneralTree::remove(node* curr, string name, int type) {
	node *tmp = curr;
	
	string ta = "/";
	tmp = access(ta + name);	

	if(tmp->f_type == PLACEHOLDER){
		tmp = tmp->next_level;
	}

	if(tmp == NULL){
		return false;
	}
	else {
		node* del;
		if(type == TFILE){
			del = tmp;
			node* prev = tmp->prev_sibling;
			node* next = tmp->next_sibling;			
			prev->next_sibling = next;
			if(next != NULL)
				next->prev_sibling = prev;

			tmp->next_sibling = tmp->prev_sibling = tmp->parent = NULL;		
		}
		else if(type == DIRECTORY) {
			del = tmp;
			node* trav = del->next_level->next_sibling;
			node* start = del->next_level;			
			while(trav != NULL){
				del = trav;				
				trav = trav->next_sibling;				
				remove(del,del->val,del->f_type);				
			}													
			del = tmp;
			if(del->prev_sibling != NULL){
				del->prev_sibling->next_sibling = del->next_sibling;
			}
			if(del->next_sibling != NULL){
				del->next_sibling->prev_sibling = del->prev_sibling;
			}			
			node *lower = del->next_level;
			lower->next_sibling = lower->parent = NULL;
			del->next_level = NULL;
			delete lower;
		}		

		del->next_sibling = del->prev_sibling = del->parent = del->next_level = NULL;
		delete del;
	}
	return true;
}

node* GeneralTree::access(node *curr, string name) {
	node *tmp;
	string a = name;

	if(curr == root) {
		tmp = set_node_to_level(&a);		
	} else {
		tmp = curr;
	}	

	while(tmp != NULL) {		
		if(tmp->val.compare(a) == 0) {			
			return tmp;
		}
		else {			
			if(tmp->f_type == DIRECTORY) {				
				node* ret = access(tmp->next_level, a);								
				if(ret != NULL && ret->val.compare(a) == 0) {
					return ret;
				}
			}
		}
		tmp = tmp->next_sibling;
	}
	return NULL;
}

void GeneralTree::gen_display(){
	cout << endl <<"============Displaying Contents============" << endl << endl;
	gen_display(root);
}

void GeneralTree::dir_display(string input){
	node* tmp;
	string a = input;
	tmp = (set_node_to_level(&a))->next_sibling;
	
	cout << endl << "=========Directory (" << a << ") contents=========" << endl;
	if(tmp == NULL){
		cout << "<Empty>" << endl;
	}
	while(tmp != NULL){
		cout << tmp->val << endl;
		tmp = tmp->next_sibling;
	}
}

class Sim {
private:
	GeneralTree tree;
	string curr;
	bool create_dir(string);
	bool delete_dir(string);
	bool change_dir(string);
	bool up_level();
	bool create_file(string);
	bool append_to_file(string);
	bool edit_file(string);
	bool delete_file(string);
	bool rename_file(string);
	bool move_file(string);
	bool copy(string);
	bool display_list(string);
	bool display_content(string);
	bool search_item(string);
	string up_level(string);
public:
	Sim(){		
		curr = "/root";
	}

	void handle(string);
	void run();	
};

void Sim::run(){	
	ifstream file("mp4.in");
	string inp = "";

	if(!file.is_open()) {
		cout << "File not found." << endl;
	}
	else{
		while(getline(file,inp)){
			handle(inp);
		}
		file.close();
	}	

	inp = "";

	while(inp.compare("end") != 0){
		getline(cin, inp);		
		handle(inp);
	}

	tree.gen_display();
}

void Sim::handle(string c_line){		
	ofstream file("mp4.out", ios::app);

	if(c_line.find("mkdir ") != -1 && c_line.find("mkdir ") == 0){
		create_dir(c_line.substr(6, c_line.size() - 1));		
	}
	else
	if(c_line.find("rmdir ") != -1 && c_line.find("rmdir ") == 0){
		delete_dir(c_line.substr(6, c_line.size() - 1));
	}
	else
	if(c_line.find("cd ") != -1 && c_line.find("cd ") == 0){
		change_dir(c_line.substr(3, c_line.size() - 1));
	}
	else
	if(c_line.find("cd..") != -1){
		up_level();
	}	
	else
	if(c_line.find("> ") != -1 && c_line.find("> ") == 0){
		create_file(c_line.substr(2, c_line.size() - 1));
	}
	else
	if(c_line.find(">> ") != -1 && c_line.find(">> ") == 0){
		append_to_file(c_line.substr(3, c_line.size() - 1));
	}
	else
	if(c_line.find("edit ") != -1 && c_line.find("edit ") == 0){
		edit_file(c_line.substr(5, c_line.size() - 1));
	}
	else
	if(c_line.find("rm ") != -1 && c_line.find("rm ") == 0){
		delete_dir(c_line.substr(3, c_line.size() - 1));	
	}
	else
	if(c_line.find("rn ") != -1 && c_line.find("rn ") == 0){
		rename_file(c_line.substr(3, c_line.size() - 1));
	}
	else
	if(c_line.find("mv ") != -1 && c_line.find("mv ") == 0){
		move_file(c_line.substr(3, c_line.size() - 1));
	}
	else
	if(c_line.find("cp ") != -1 && c_line.find("cp ") == 0){
		copy(c_line.substr(3, c_line.size() - 1));
	}
	else
	if(c_line.find("ls ") != -1 && c_line.find("ls ") == 0){
		display_list(c_line.substr(3, c_line.size() - 1));
	}
	else
	if(c_line.find("show ") != -1 && c_line.find("show ") == 0){
		display_content(c_line.substr(5, c_line.size() - 1));
	}
	else
	if(c_line.find("whereis ") != -1 && c_line.find("whereis ") == 0){
		search_item(c_line.substr(8, c_line.size() - 1));
	}
	else{
		cout << "Command not recognized." << endl;
	}
}

bool Sim::create_dir(string input){ //new directory at current only	
	if(input.find("/") == -1){
		input = curr + "/" + input;		
	}	

	tree.insert(input, DIRECTORY);
}//ok

bool Sim::delete_dir(string input){
	if(input.find("/") == -1){ //at current directory only
		input = "/" + input;		
	}

	tree.remove(input, DIRECTORY);
}//ok

bool Sim::change_dir(string input){ //cd
	node *t = tree.access(curr); //at current directory only

	if(check_present(t, input)){		
		curr += "/" + input;
		return true;
	}
	return false;
}

bool Sim::up_level(){ //cd..
	string t = curr;	
	curr = up_level_aux(curr);	
	return (t.compare(curr) == 0) ? false : true;	
}

bool Sim::create_file(string input){ //>
	if(input.find("/") == -1)
		input = curr + "/" + input;	
	tree.insert(input, TFILE);
	return true;
}

bool Sim::append_to_file(string input){ // >>
	node *t = tree.access(input);
	string newInp;
	getline(cin, newInp);
	if(t != NULL)
		t->cont += newInp;
}

bool Sim::edit_file(string input){ //edit
	node *t = tree.access(input);
	string newInp;	
	getline(cin, newInp);	
	if(t != NULL)
		t->cont = newInp;
}

bool Sim::delete_file(string input){ //rm
	string a = input;
	tree.remove(input, TFILE);
}

bool Sim::rename_file(string input){ //rn
	string a = input;
	string b = "/" +separator(&a);
	node* t = tree.access(b);

	if(t != NULL)
		t->val = separator(&a);
}

bool Sim::move_file(string input){ //mv
	string a = input;
	string b = separator(&a);

	tree.remove(b, TFILE);

	b = separator(&a) + b;	
	tree.insert(b, TFILE);
}

bool Sim::copy(string input){ //cp
	string a = input;
	string b = separator(&a);

	node *t = tree.access(b);
	b = separator(&a);
	tree.insert((t->address + b), TFILE);
}

bool Sim::display_list(string input){ //ls
	tree.dir_display(curr);	
}

bool Sim::display_content(string input){ //show
	input  = "/" + input;
	node *t = tree.access(input);	
	if(t != NULL){
		cout << "Contents: " << endl << t->cont << endl;
	}
}

bool Sim::search_item(string input){ //whereis
	input = "/" + input;
	node *t = tree.access(input);
	if(t != NULL){
		cout << t->address << endl;
	}
}

int main(){
	Sim sim;
	sim.run();			
	
	return 0;
}

//auxiliary functions

string remove_leading_spaces(string input){	
	for(int i = 0; i < input.size(); i++){
		if(input[i] != ' '){
			return input.substr(i,input.size() - 1);
		}
	}
}

string tokenize_loc_string(string *input){
	string ret, inp = *(input);
	bool w = false;

	for(int i = 0, lim = inp.size(); i < lim; i++){
		if(inp[i] == '/'){
			for(int j = i + 1; j < lim; j++){
				if(inp[j] == '/'){				
					w = true;
					ret = inp.substr(i,j-i);
					inp = inp.substr(j, inp.size() - j);
					i = lim;
					break;
				}	
			}
			if(!w){
				ret = "";
				return ret;
			}
		}
	}
	*input = inp;	
	return ret;
}

string up_level_aux(string input){
	string a = input;
	int i = a.find_last_of("/");
	string ret = a.substr(0, i);
	if(ret.find("/root") == -1)
		return a;
	return ret;
}

string separator(string *input){
	string a = *(input);
	string b;
	
	int i = a.find(" ");
	b = a.substr(0, i);
	a = a.substr(i + 1, a.size() - i);
	*input = a;
	return b;
}

bool check_present(node *t, string input){
	node *tmp = t;
	while(tmp != NULL){
		if(tmp->val.compare(input) == 0){
			return true;
		}
		tmp = tmp->next_sibling;
	}
	return false;
}