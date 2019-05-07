/* 
Code Originally Adapted and Parallelized from hhttps://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <malloc.h> 
#include <stdlib.h>
#include <stack>
#include <chrono>
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
#include <tuple>

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
n = mat.size() - 1;
} 
 
Graph::~Graph() {} 
 
bool Graph::isConnected(int x, int y) {
    return (mat[x][y] == 1);
} 
 
void Graph::addEdge(int x, int y) {
    mat[x][y] = mat[y][x] = 1;
} 
 
void Graph::DFS(int x, int required){
    bool goal_found = false;
    std::stack<int> s;
    vector<bool> visited(n);
   
    for(int i = 0; i < n; i++)visited[i] = false;
	s.push(x);
    visited[x] = true;

	
	
	
  while (!s.empty() and !goal_found) 
	{
		#pragma omp parallel 
		{
			int k = -1;
			#pragma omp critical
			if(s.size() != 0 ){k = s.top(); s.pop();}

		
			if (k != -1 )
			{ 
				cout<<k<<" "<<endl;
				if(k == required ) 
				{goal_found = true;
				}
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
	{src = 4;} 
	else if (i==2)
	{src = 18;}
	else 
	{src = 24;}

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
g.DFS(src, get<0>(mytuple));
auto t_end = std::chrono::high_resolution_clock::now();
std::clock_t c_end = std::clock();

	final_time +=  1000.0 * (c_end-c_start) / CLOCKS_PER_SEC ;
	}
	cout <<final_time/1.0 <<" ms"<<endl;
	
}
}
