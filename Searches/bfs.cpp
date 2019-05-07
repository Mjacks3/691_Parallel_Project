/* 
Code Originally Adapted and Parallelized from https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/ 
*/
#include <vector>
#include <iostream>
#include <ctime>
#include <malloc.h> 
#include <stdlib.h>
#include <queue>
#include <omp.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <tuple>



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

  return (mat[u][v] == 1);
}




void Graph::BFS(int s, int g) {
	bool goal_found = false;
	std::queue<int> Q;
	/** Keeps track of explored vertices */
	vector<bool> explored(n);
	for (int i = 0; i < n; ++i)explored[i] = false;
	Q.push(s);
	explored[s] = true; 
	cout << "Breadth first Search starting from vertex ";


	while (!Q.empty() and !goal_found) 
	{	
		#pragma omp parallel 
		{
			int v = -1;
			#pragma omp critical
			if(Q.size() != 0 ){
			v = Q.front(); 
			cout << v<< endl;
			Q.pop();}
		  
			if (v != -1 )
			{ 
				if(v == g) 
				{goal_found = true;}
			
				else
				{
					for (int w = 0; w < n; ++w)
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




tuple <int,vector<vector<int>>> matrixRead(string filename)
{

  // opens the file
  ifstream inFile;
  inFile.open(filename);

  int goal;
  // creates a string to hold the line
  // a temp to store the integers of the split line
  // a count to determine vector access
  // a base vector we will be creating the matrix with
  string line;
  string temp;
  int count = 0;
  vector< vector<int> > adjMatrix;

  // while the file can read lines, assign the line to "line"
  while (getline(inFile, line))
  {
	stringstream stream(line);
	if(count != 0)
	{
	   // for each line pushes an empty vector to hold the columns for that row
		adjMatrix.push_back(vector<int>{});
	} 
    // splits the line by whitespace
    while(stream >> temp)
    {
      if(count == 0)
      {
        goal = stoi(temp);
      }
      else
      {
      // adds current value into 2D vector
      adjMatrix[count-1].push_back(stoi(temp));
      }
    }
    count++;
  }
  inFile.close();
  return make_tuple(goal,adjMatrix);

}

int main(int argc, char *argv[])  {

	int src;
	for(int i=0; i< 4 ; i++ )
	{
	if (i==0)
	{src = 0;}
	else if (i==1)
	{src = 29;}
	else if (i==2)
	{src = 860;}
	else 
	{src = 899;}

		double final_time = 0;

		for(int ind=0; ind< 1 ; ind++ )
	{
    auto t_start = std::chrono::high_resolution_clock::now();
	std::clock_t c_start = std::clock();

 if (argc != 2)
  {
    printf("Error improper arguments\nUsage: ./matrixreader {filename}");
    exit(1);
  }

char* filename = argv[1];
tuple<int, vector<vector<int>>> mytuple = matrixRead(filename);
vector<vector<int>> adjMatrix = get<1>(mytuple);

  printf("Goal nodeID: %d\n", get<0>(mytuple));


Graph g( get<1>(mytuple));
g.BFS(src, get<0>(mytuple));
std::clock_t c_end = std::clock();
auto t_end = std::chrono::high_resolution_clock::now();

final_time +=  1000.0 * (c_end-c_start) / CLOCKS_PER_SEC ;

	}

	cout <<final_time/1.0 <<" ms"<<endl;
}
}
