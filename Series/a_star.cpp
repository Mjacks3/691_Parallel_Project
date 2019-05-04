 // A C++ Program to implement A* Search Algorithm 
#include<bits/stdc++.h> 

using namespace std; 
  
#define ROW 10
#define COL 10 
  
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

void tracePath(vertex_cell vertexDetails[ROW], int dest) 
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
    return; 
} 
  
void aStarSearch(vector<vector<int> > inputMatrix , int src, int dest) 
{ 
	bool closedList[ROW];
	memset(closedList, false, sizeof (closedList)); 
	vertex_cell vertexDetails[ROW]; 
	
    for (int i=0; i<ROW; i++) 
    { 
		vertexDetails[i].f = FLT_MAX; 
		vertexDetails[i].g = FLT_MAX; 
		vertexDetails[i].h = FLT_MAX; 
		vertexDetails[i].parent = -1; 
    } 
	
	int node;
  
    // Initialising the parameters of the starting node 
    node = src; 
    vertexDetails[src].f = 0.0; 
    vertexDetails[src].g = 0.0; 
    vertexDetails[src].h = 0.0; 
    vertexDetails[src].parent = src; 
  
    /*Create an open list having information as- 
     <f, v> 
     where f = g + h, 
     and v is the vertex */
	 
	priority_queue<Pair, vector<Pair>, greater<Pair> > openListPQ;
  
  
    // Put the starting vertex on the open list and set its 'f' as 0 
    openListPQ.push(make_pair(0.0, src)); 
  
    // We set this boolean value as false as initially 
    // the destination is not reached. 
    bool foundDest = false; 
  
    while (!openListPQ.empty()) 
    { 


		if(openListPQ.size() != 0 ){
			Pair p = openListPQ.top();
			node = p.second;
			openListPQ.pop(); 
		}
		
            closedList[node] = true; 
			
			
       
        //Generating all the  successors of this cell 
		
        // To store the 'g', 'h' and 'f' of the 8 successors 
        double gNew, hNew, fNew; 
		
		for (int adjnode = 0; adjnode<ROW; adjnode++)
		{

			if(closedList[adjnode] == false &&
			   adjnode==dest && inputMatrix[node][adjnode] == 1){
				   
				// Set the Parent of the destination cell 
                vertexDetails[adjnode].parent = node; 
                printf ("The destination cell (Vertex) is found\n"); 
                tracePath (vertexDetails, dest); 
                foundDest = true; 
                return; 
			}
			// If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following
			
            else if (closedList[adjnode] == false && 
                     inputMatrix[node][adjnode] == 1) 
            { 
                gNew = vertexDetails[adjnode].g + 1.0; 
                hNew = calculateHValue (node, ROW, dest); 
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
  
    // When the destination cell is not found and the open 
    // list is empty, then we conclude that we failed to 
    // reach the destiantion cell. This may happen when the 
    // there is no way to destination cell (due to blockages) 
    if (foundDest == false) 
        printf("Failed to find the Destination Cell\n"); 
  
    return; 
} 
  
// Driver program to test above function 
int main() 
{ 
/*
 int adjmatrix[ROW][R OW] = 
    { 
        { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }		
    }; */
std::vector<std::vector<int> > matrix( 10,std::vector<int>(10));	
matrix[0][2] = matrix[0][3] = matrix[1][3] = matrix[2][9] = matrix[3][8] = matrix[9][8] = 1;

  
    // Source is the left-most bottom-most corner 
    int src = 0 ; 
    // Destination is the left-most top-most corner 
	int dest =  8;
  
    aStarSearch(matrix, src, dest); 
  
    return(0); 
}