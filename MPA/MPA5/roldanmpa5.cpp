#include <iostream>

using namespace std;
// adjacency matrix solution for positively weighted graphs
class graph{
private:
	int **adj;
	int n;
public:
	graph();
	~graph();
	bool addedge(int,int);
};

int main(){

	return 0;
}

graph::graph(int s){
	n = s;
	adj = new int*[n];
	for(int i = 0; i<n; i++){
		adj[i] = new int[n];
		for(int j = 0;j<n;j++){
			adj[i][j] = 0;
		}
	}
}

graph::~graph(){
	for(int i = 0; i<n; i++){
		delete[] adj[n];
	}
	delete[] adj;
}

bool graph::addedge(int i, int j, int wt){
	if(i < 0|| i>=n || j<0||j>=n)
		return false	
	else
		adj[i][j] = wt;

	return true;
}

bool graph::removeedge(int i, int j){
	if(i < 0|| i>=n || j<0||j>=n)
		return false	
	else
		adj[i][j] = 0;
	
	return false;
}

bool graph::