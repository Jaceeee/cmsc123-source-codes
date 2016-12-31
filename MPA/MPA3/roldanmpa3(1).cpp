//I declare upon my honor that I did this MPA by myself
//11/27/16 with changes to MazeSolver<class T>::solve)()
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <typeinfo>

using namespace std;

string removeNewlines(string,int,int);

enum {
	WALL = '#',
	OPENPATH = '.',
	START = 'o',
	END = '*',
	TRAIL = 'x'
};

template <class T>
class MyStack : public stack<T> {
public:
	T front();
};

template <class T>
T MyStack<T>::front() {
	return stack<T>::top();
}

class Square {
private:
	char item;
	int row, col;
	bool visited;
public:
	Square() {
		row = col = 0;
		visited = false;
		item = 0;
	}
	Square(int row, int col,char item) {
		this->item = item;
		this->row = row;
		this->col = col;
		visited = false;
	}
	bool isPassable() { return (item == WALL) ? false : true; }
	bool isVisited() { return visited; }
	char getItem() { return item; }
	int getRow() { return row; }
	int getCol() { return col; }
	void setVisited(){ visited = (!visited) ? true : false; }
	void setPath();
	void setSquare(int,int,char);
	Square operator=(Square);
};

void Square::setPath() {
	if(isPassable() && item == OPENPATH) {
		item = TRAIL;
	}
}

void Square::setSquare(int row,int col,char item){
	this->row = row;
	this->col = col;
	this->item = item;
}

Square Square::operator=(Square sq) {
	this->row = sq.row;
	this->col = sq.col;
	this->item = sq.item;
}
class Maze {
private:
	int length, width;
	Square **maze;
public:
	Maze(int length, int width, string mazeInFile) {
		this->length = length;
		this->width = width;
		this->maze = new Square*[length];

		for(int i = 0; i < length; i++)
			this->maze[i] = new Square[width];

		for(int i = 0, k = 0; i < length; i++) {
			for(int j = 0; j < width; j++, k++) {				
				this->maze[i][j].setSquare(i, j, mazeInFile[k]);				
			}
		}
		cout<<toString()<<endl;		
	}
	~Maze() {
		for (int i = 0; i < length; i++)
			delete[] maze[i];

		delete[] maze;
	}
	Square getSquare(int,int);
	void setVisited(int,int);
	void setPath(int,int);
	int getLength() { return length; }
	int getWidth() { return width; }
	string toString();
};

Square Maze::getSquare(int x, int y) {
	return maze[x][y];
}

void Maze::setPath(int row, int col) {
	maze[row][col].setPath();
}

void Maze::setVisited(int row, int col) {
	maze[row][col].setVisited();
}

string Maze::toString() {
	string stringMaze = "";
	for(int i = 0; i < length; i++) {
		for(int j = 0; j < width; j++) {
			stringMaze += maze[i][j].getItem();
		}
		stringMaze += '\n';
	}
	return stringMaze;
}

template <class T>
class Agenda {
private:
	T *path;
	bool type; //true for queue, false for stack
public:
	Agenda<T>();
	~Agenda<T>(){ delete path; }
	void add(Square);
	bool remove();
	bool isEmpty();
	Square peek();
	int getSize() { return path->size(); }
};

template <class T>
Agenda<T>::Agenda(){
	path = new T();
	string t1 = typeid(queue<Square>).name();
	string t2 = typeid(MyStack<Square>).name();
	string t3 = typeid(*path).name();
	if(t1.compare(t3) == 0)
		type = true;
	else 
	if(t2.compare(t3) == 0){
		type = false;		
	}
	else
		throw 1;
}

template <class T>
void Agenda<T>::add(Square s) {
	path->push(s);
}

template <class T>
bool Agenda<T>::remove(){
	if(path->empty())
		return false;
	
	path->pop();
	return true;
}

template <class T>
bool Agenda<T>::isEmpty() {
	return path->empty();
}

template <class T>
Square Agenda<T>::peek() {	
	return path->front();
}

template <class T>
class MazeSolver {
private:
	Agenda<T> *agd;
	Maze *maze;
	Square *current;
	stack<Square*> trckr;
	void setInitialSquare();
public:
	MazeSolver(int len, int wid, string maze) {
		try {
			agd = new Agenda<T>();	
		} catch(int err){
			if(err == 1)
				cout << "Invalid ADT used." << endl;
		}
		
		this->maze = new Maze(len, wid, maze);		
		current = new Square();
	}
	~MazeSolver(){
		delete agd;
		delete maze;
		delete current;
	}
	void solve();
	void writeSolution();
};

template <class T>
void MazeSolver<T>::setInitialSquare() {			
	for(int i = 0; i < maze->getLength(); i++) {
		for(int j = 0; j < maze->getWidth(); j++) {			
			if(maze->getSquare(i,j).getItem() == START) {
				current = new Square(maze->getSquare(i,j).getRow(),maze->getSquare(i,j).getCol(),maze->getSquare(i,j).getItem());										
			}				
		}			
	}	
	trckr.push(current);
	maze->setVisited(current->getRow(),current->getCol());	
}

template <class T>
void MazeSolver<T>::solve() {
	setInitialSquare();	
	bool solvable = true;
	if(current != NULL) {			
		while(solvable) {			
			bool mvdFrwd = false;
			int howManyRemoves = 0;	

			// adding to the stack or queue
			Square left = maze->getSquare(current->getRow(), current->getCol() - 1);			
			Square up = maze->getSquare(current->getRow() - 1, current->getCol());
			Square right = maze->getSquare(current->getRow(), current->getCol() + 1);
			Square down = maze->getSquare(current->getRow() + 1, current->getCol());			

			if(left.isPassable() && !left.isVisited()){
				agd->add(left);				
				mvdFrwd = true;
				howManyRemoves++;
			} //(Y, X)?						
			if(up.isPassable() && !up.isVisited()){
				agd->add(up);					
				mvdFrwd = true;
				howManyRemoves++;
			} //(Y, X)?			
			if(right.isPassable() && !right.isVisited()){
				agd->add(right);				
				mvdFrwd = true;
				howManyRemoves++;
			} //(Y, X)?			
			if(down.isPassable() && !down.isVisited()) {
				agd->add(down);				
				mvdFrwd = true;
				howManyRemoves++;
			} //(Y, X)?						
			
			//changing the new current square
			//cout<<"Square: "<<current->getRow()<<" "<<current->getCol()<<endl;

			if(!agd->isEmpty() && mvdFrwd) {				
				current = new Square(agd->peek().getRow(), agd->peek().getCol(),agd->peek().getItem());
				maze->setVisited(current->getRow(),current->getCol());
				
				// cout<<"other passable: ";
				while(howManyRemoves > 0){
					if(!agd->isEmpty()){
						// cout<<agd->peek().getRow()<<" "<<agd->peek().getCol()<<" ";
						agd->remove();
					}
					else
						solvable = false;
					// cout<<"Hey";
					howManyRemoves--;
				}
				// 	cout<<endl<<endl;
				trckr.push(current);
				// cout<<"Here ";				
			}			

			if(current->getItem() == END || current->getItem() == START)
				break;
			if(current->getItem() == START){
				solvable = false;
				break;
			}

			if(!mvdFrwd) {
				if(!trckr.empty()){					
					trckr.pop();
					current->setSquare(trckr.top()->getRow(),trckr.top()->getCol(), trckr.top()->getItem());					
				}
				else{					
					solvable = false;
				}
			}
			
		}				
		while(!trckr.empty()){
			maze->setPath(trckr.top()->getRow(), trckr.top()->getCol());
			trckr.pop();
		}
	}
	else
		cout << "Start square not found." << endl;
	if(solvable)
		cout<<"Solved"<<endl;
	else
		cout<<"!Solved"<<endl;
}

template <class T>
void MazeSolver<T>::writeSolution() {
	ofstream out;	
	out.open("maze.out", ios::app);
	out << maze->toString();
	out << endl;
	out.close();
}

int main(){	
	ifstream file("input.in");	
	
	if(!file.is_open()){
		cout<<"File not found."<<endl;
		return 0;
	}

	int T;
	
	ofstream out;
	out.open("maze.out");
	out.close();

	file>>T;	
	// cin >> T;

	for(; T>0 ; T--){		
		int rows, cols;
		file >> rows >> cols;
		// cin >> rows >> cols;
		string maze = "";
		string buffer;
		for(int i = 0; i< rows; i++){			
			file >> buffer;
			maze += buffer;
		}

		maze = removeNewlines(maze, rows, cols);		
		
		MazeSolver<queue <Square> > msq(rows, cols, maze);
		msq.solve();
		msq.writeSolution();
		MazeSolver<MyStack <Square> > mss(rows, cols, maze);
		mss.solve();
		mss.writeSolution();
		
	}
	file.close();	
	return 0;
}

string removeNewlines(string st, int row, int col){	
	string ans = "";
	for(int i = 0, j = 0; i < row; i++, j += col){
		ans += st.substr(j, col);
	}	
	return ans;	
}