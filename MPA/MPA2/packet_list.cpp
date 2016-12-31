/*
class node{
public:
	Packet packet;
	node* next;
public:
	node(){
		next = NULL;
	}
	node(Packet x){
		packet = x;
		next = NULL;
	}
};

class Poem{
private:
	node* head;
	node* tail;
	int size;
public:
	Poem(){
		head = tail = NULL;
		size = 0;
	}
	~Poem();
	Poem(const Poem&);
	bool insert(Packet,int);
	Packet get(int);	
	int getSize() { return size; }
	Poem operator=(Poem);
	node* getHead() { return head; }
	bool remove(int);
	bool set(Packet,int);
};

Poem::Poem(const Poem &poem){
	node* trav = poem.head;
	head = tail = NULL;
	int i = 0;
	size = 0;

	while(i < poem.size){
		insert(	trav->packet,i);
		trav = trav->next;
		i++;
	}
}

bool Poem::insert(Packet x,int pos){
	if(pos < 0 || pos > size)
		return false;
	else if(size == 0){
		node *tmp =  new node(x);
		head = tail = tmp;
	}
	else{
		node *trav = head, *tmp = new node(x);
						
		if(pos == 0) {
			tmp->next = head;
			head = tmp;						
		}
		else {
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
	}
	size++;
	return true;
}

Poem::~Poem(){
	while(size>0)
		remove(0);
}

Packet Poem::get(int pos){
	if(pos < 0 || pos >= size)
		throw 1;
	int i = 0;
	node *trav = head;
	while(i < pos){
		trav = trav->next;
		i++;
	}
	return trav->packet;
}

Poem Poem::operator=(Poem aPoem){
	node* trav = aPoem.getHead();
	int i = 0;
	size = 0;
	head = tail = NULL;

	while(i < aPoem.getSize()){
		insert(trav->packet,i);
		trav = trav->next;
		i++;
	}
}

bool Poem::remove(int pos){
	if(pos < 0 || pos >= size)
		return false;
	else{
		node *del, *tmp = head;

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

bool Poem::set(Packet item, int pos){
	if(pos < 0 || pos >= size){
		return false;
	}
	else{
		node *trav = head;
		int i = 0;
		while(i < pos){
			i++;
			trav = trav->next;
		}
		trav->packet = item;
		return true;
	}
}*/