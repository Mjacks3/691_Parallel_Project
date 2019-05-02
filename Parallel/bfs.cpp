#include <vector>
#include <iostream>
#include <ctime>
#include <malloc.h> 
#include <stdlib.h>
#include <queue>
#include <omp.h>


using namespace std;
/************************************************************
 
Class Graph represents a Graph [V,E] having vertices V and
edges E.
 
************************************************************/
class Graph {
  private:
  int n; 
  vector<vector<int> > mat;
  
  public:
  Graph(vector<vector<int> > inputMatrix);
  ~Graph();
  bool isConnected(int u, int v);
  void addEdge(int u, int v);
  void BFS(int s, int g );
  void print();
};

Graph::Graph(vector<vector<int> > inputMatrix ) {
mat = inputMatrix;	
n = mat.size();
}
 
Graph::~Graph() {} 


bool Graph::isConnected(int u, int v) {
  return (mat[u-1][v-1] == 1);
}


void Graph::addEdge(int u, int v) {
  mat[u-1][v-1] = mat[v-1][u-1] = 1;
}


void Graph::BFS(int s, int g) {
	bool goal_found = false;

	std::queue<int> Q;
	/** Keeps track of explored vertices */
	vector<bool> explored(n+1);

	for (int i = 1; i <= n; ++i)explored[i] = false;

	Q.push(s);


	explored[s] = true; 
	cout << "Breadth first Search starting from vertex ";
	cout << s << " : " << endl;

	while (!Q.empty() and !goal_found) 
	{	
		#pragma omp parallel 
		{
			int v = -1;
			#pragma omp critical
			if(Q.size() != 0 ){v = Q.front(); Q.pop();}
		  
			if (v != -1 )
			{ 
				cout << v << " ";
			  
				if(v == g) goal_found = true;
			
				else
				{
					for (int w = 1; w <= n; ++w)
					{
						if (isConnected(v, w) && !explored[w]) 
						{
							Q.push(w);	  
							explored[w] = true;
							
							if(v == g) goal_found = true;
						}
					}
				}
			}
		}
	}
  cout << endl;
}

void Graph::print(){
   for (int i = 0; i < mat.size(); i++) { 
        for (int j = 0; j < mat[i].size(); j++) 
			printf(" %d ",mat[i][j] );
		printf(" \n" );
    }
}

int main()  {

std::vector<std::vector<int> > matrix( 16,std::vector<int>(16));
matrix[1][0] = 1; 
matrix[0][1] = 1;

Graph g(matrix); 

  /** Adds edges to the graph*/
  g.addEdge(1, 2); g.addEdge(1, 3);
  g.addEdge(2, 4); g.addEdge(3, 4);
  g.addEdge(3, 6); g.addEdge(4 ,7);
  g.addEdge(5, 6); g.addEdge(5, 7);
 
  g.print();
  g.BFS(1, 4);
 
}

