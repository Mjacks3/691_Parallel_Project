/*Code Originally Adapted and Parallelized  from https://www.geeksforgeeks.org/a-search-algorithm/   */

using namespace std; 
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
#include <chrono>
#include<bits/stdc++.h> 
#include <omp.h>
 
// Creating a shortcut for int, int pair type 
typedef pair<float, int> Pair; 
  
// A structure to hold the neccesary parameters 
struct vertex_cell 
{ 
    int parent;     // Vertex of its parent
    double f, g, h;     // f = g + h 
}; 
  
// A Utility Function to calculate the 'h' heuristics. 
double calculateHValue(int v, int size, int dest) 
{ 
	int dest_row = dest / size;
	int dest_col =  dest % size;
	
	int my_row = v / size;
	int my_col =  v % size;
	
    // Return using the distance formula : Manhattan Distance 
    return ((double) abs(my_row-dest_row) + abs(my_col +dest_col) ); 
} 
  
// A Utility Function to trace the path from the source to destination 
void tracePath( vector<vertex_cell> vertexDetails, int dest) 
{ 
    printf ("\nThe Path is "); 
	int vertex = dest; 
    stack<int> Path;
	
    while (!(vertexDetails[vertex].parent == vertex)) 
    { 
        Path.push (vertex); 
        int temp_vertex = vertexDetails[vertex].parent;  
        vertex = temp_vertex; 
    } 
  
    Path.push (vertex); 
    while (!Path.empty()) 
    { 
		int p = Path.top(); 
        Path.pop(); 
        printf("-> (%d) ",p); 
    } 
	cout << endl;
    return; 
} 
  
void aStarSearch(vector<vector<int> > inputMatrix , int src, int dest) 
{ 
	vector<bool> closedList(inputMatrix.size());
	vector<vertex_cell> vertexDetails(inputMatrix.size()); 
	omp_lock_t writelock;
    omp_init_lock(&writelock);
	
    for (int i=0; i<inputMatrix.size(); i++) 
    { 
		vertexDetails[i].f = FLT_MAX; 
		vertexDetails[i].g = FLT_MAX; 
		vertexDetails[i].h = FLT_MAX; 
		vertexDetails[i].parent = -1; 
		closedList[i] = false;
    } 

    vertexDetails[src].f = 0.0; 
    vertexDetails[src].g = 0.0; 
    vertexDetails[src].h = 0.0; 
    vertexDetails[src].parent = src; 
  
    /*Create an open list having information as- 
     <f, v> where f = g + h, and v is the vertex */
	 
	priority_queue<Pair, vector<Pair>, greater<Pair> > openListPQ;
	
    // Put the starting vertex on the open list and set its 'f' as 0 
    openListPQ.push(make_pair(0.0, src)); 
  
    // We set this boolean value as false as initially the destination is not reached. 
    bool foundDest = false; 
  
    while (!openListPQ.empty() && !foundDest) 
    { 
		#pragma omp parallel 
		{
		
		int node = -1;
		omp_set_lock(&writelock);

		if(!openListPQ.empty() )
		{ 
			Pair p = openListPQ.top();
			node = p.second; 
			openListPQ.pop();
		    closedList[node] = true; 
		}
        
		omp_unset_lock(&writelock);
			
			
        //Generating all the successors of this cell  
        double gNew, hNew, fNew; 

		if (node != -1 ){
		for (int adjnode = 0; adjnode<inputMatrix.size(); adjnode++)
		{
			if(closedList[adjnode] == false &&
			   adjnode==dest && inputMatrix[node][adjnode] == 1  ){
				  
				// Set the Parent of the destination cell 
                vertexDetails[adjnode].parent = node;  
                tracePath (vertexDetails, dest); 
			}
			
			// If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following
			
            else if (closedList[adjnode] == false && 
                     inputMatrix[node][adjnode] == 1 ) 
            { 
                gNew = vertexDetails[adjnode].g + 1.0; 
                hNew = calculateHValue (node, inputMatrix.size(), dest); 
                fNew = gNew + hNew; 
  
                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (vertexDetails[adjnode].f == FLT_MAX || 
                        vertexDetails[adjnode].f > fNew) 
                { 

                    openListPQ.push( make_pair(fNew,adjnode)); 
  
                    // Update the details of this cell 
                    vertexDetails[adjnode].f = fNew; 
                    vertexDetails[adjnode].g = gNew; 
                    vertexDetails[adjnode].h = hNew; 
                    vertexDetails[adjnode].parent = node; 
                }
            }
		}	
		}
	}	
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
	{src = 879;}
	else 
	{src = 899;}

	double final_time = 0;

	for(int ind=0; ind<1 ; ind++ )
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
  
	aStarSearch(get<1>(mytuple), src, get<0>(mytuple)); 
	auto t_end = std::chrono::high_resolution_clock::now();
	std::clock_t c_end = std::clock();
	final_time +=  1000.0 * (c_end-c_start) / CLOCKS_PER_SEC ;
		
	}
	cout <<final_time/1.0 <<" ms"<<endl;
	
	}
}
