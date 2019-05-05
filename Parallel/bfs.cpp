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
	//cout << "Breadth first Search starting from vertex ";


	while (!Q.empty() and !goal_found) 
	{	

		#pragma omp parallel 
		{
			int v = -1;
			#pragma omp critical
			if(Q.size() != 0 ){
			
			v = Q.front(); 
			//cout << v<< endl;
			Q.pop();

			}
		  
			if (v != -1 )
			{ 
			  
				if(v == g) 
				{goal_found = true;
				printf( "Done ");
				}
			
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
  //cout << endl;
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
	for()
		
    auto t_start = std::chrono::high_resolution_clock::now();

 if (argc != 2)
  {
    printf("Error improper arguments\nUsage: ./matrixreader {filename}");
    exit(1);
  }

  char* filename = argv[1];
  tuple<int, vector<vector<int>>> mytuple = matrixRead(filename);
  vector<vector<int>> adjMatrix = get<1>(mytuple);
 /* for(int i = 0; i < adjMatrix.size(); i++)
  {
    for(int j=0; j<adjMatrix[i].size(); j++)
    {
      printf("%d ", adjMatrix[i][j]);
    }
    printf("\n");
  }
  */
 // printf("Goal nodeID: %d\n", get<0>(mytuple));


Graph g( get<1>(mytuple));


g.BFS(24, get<0>(mytuple));

auto t_end = std::chrono::high_resolution_clock::now();
std::cout << std::fixed << std::setprecision(7) <<". Wall clock time passed: " 
              << std::chrono::duration<double, std::milli>(t_end-t_start).count() <<" ms\n";


//printf("start = %d\nend   = %d\n", start, end);
//cout << "Done in :" <<  (double) start  << " seconds" << endl;


//get<0>(mytuple)

}



/*
std::vector<std::vector<int> > matrix( 16,std::vector<int>(16));
matrix[1][0] = 1; 
matrix[0][1] = 1;

Graph g(matrix); 

  /** Adds edges to the graph
  g.addEdge(1, 2); g.addEdge(1, 3);
  g.addEdge(2, 4); g.addEdge(3, 4);
  g.addEdge(3, 6); g.addEdge(4 ,7);
  g.addEdge(5, 6); g.addEdge(5, 7);
 
  g.print();
  g.BFS(1, 4);
*/
//}

