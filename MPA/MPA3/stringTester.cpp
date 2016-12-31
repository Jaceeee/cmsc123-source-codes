#include <iostream>
#include <fstream>

using namespace std;

enum{
	WALL = '#',
	OPENPATH = '.',
	START = 'o',
	END = '*',
	TRAIL = 'x'
};

class Square{
private:
	char item;
	int row, col;
	bool visited;
public:
	Square(){
		row = col = 0;
		visited = false;
		item = 0;
	}
	Square(char item, int row, int col) {
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
};

void Square::setPath() {
	if(isPassable() && item == OPENPATH) {
		item = TRAIL;
	}
}

string removeNewlines(string, int, int);
int main() {
	int T;
	ifstream file("maze.in");
	// ofstream out;

	//out.open("maze.out", ios::app);
	file >> T;	
	// cin >> T;

	for(; T>0 ; T--){		
		int rows, cols;
		file >> rows >> cols;
		// cin >> rows >> cols;
		string maze = "";
		string buffer;
		for(int i = 0; i < rows; i++) {			
			file >> buffer;
			cout<<endl<<"Buffer: "<<buffer<<endl;
			maze += buffer;
		}

		maze = removeNewlines(maze, rows, cols);
		cout<<"This is the maze"<<endl<<maze<<endl;
	}
	return 0;
	file.close();

	Square **maze = new Square*[12];

	for(int i = 0; i<12; i++){
		maze[i] = new Square[4];
	}
}

string removeNewlines(string st, int row, int col) {	
	string ans = "";
	for(int i = 0, j = 0; i < row; i++, j += col) {
		ans += st.substr(j, col);
	}
	return ans;	
}