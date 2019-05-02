 #include <iostream>
#include <vector>
#include <ctime>
#include <malloc.h> 
#include <stdlib.h>
#include <stack>

using namespace std;

class Graph {
    private:
        int n;
		vector<vector<int> > mat;
		
    public:
        Graph(vector<vector<int> > inputMatrix  );
        ~Graph();
        bool isConnected(int, int);
        void addEdge(int x, int y);
        void DFS(int , int);
		void print();
}; 
 
Graph::Graph(vector<vector<int> > inputMatrix ) {
mat = inputMatrix;	
n = mat.size();
} 
 
Graph::~Graph() {} 
 
bool Graph::isConnected(int x, int y) {
    return (mat[x-1][y-1] == 1);
} 
 
void Graph::addEdge(int x, int y) {
    mat[x-1][y-1] = mat[y-1][x-1] = 1;
} 
 
void Graph::DFS(int x, int required){
    bool goal_found = false;
    std::stack<int> s;
   
   vector<bool> visited(n+1);
   
    for(int i = 0; i <= n; i++)visited[i] = false;
    
	s.push(x);
	
    visited[x] = true;
    cout << "Depth first Search starting from vertex ";
    cout << x << " : " << endl;
	
	
	
  while (!s.empty() and !goal_found) 
	{
		#pragma omp parallel 
		{
			int k = -1;
			#pragma omp critical
			if(s.size() != 0 ){k = s.top(); s.pop();}

		
			if (k != -1 )
			{ 
				cout<<k<<" ";
				if(k == required ) goal_found = true;
				else
				{
					for (int i = n; i >= 0 ; --i)
					{
						if (isConnected(k, i) && !visited[i])
						{
							s.push(i);
							visited[i] = true;
							
							if(k == required) goal_found = true;
						}
					}
				}
			}
		}
	}
    cout<<endl;
} 
 
 
void Graph::print(){
   for (int i = 0; i < mat.size(); i++) { 
        for (int j = 0; j < mat[i].size(); j++) 
			printf(" %d ",mat[i][j] );
		printf(" \n" );
    }
}

 
int main(){

std::vector<std::vector<int> > matrix( 8,std::vector<int>(8));

matrix[1][0] = 1; 
matrix[0][1] = 1;

Graph g(matrix); 

g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
g.addEdge(2, 5); g.addEdge(2, 6); g.addEdge(4, 7);
g.addEdge(4, 8);

g.print();
g.DFS(1, 4);

    return 0;
}