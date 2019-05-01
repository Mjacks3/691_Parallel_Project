#include <vector>
#include <iostream>
#include <ctime>
#include <malloc.h> 
#include <stdlib.h>
using namespace std;

struct node {
  int info;
  node *next;
};

class Queue {
  private:
  node *front;
  node *rear;
  public:
  Queue();
  ~Queue();
  bool isEmpty();
  void enqueue(int);
  int dequeue();
  void display();
};


void Queue::display(){
  node *p = new node;
  p = front;
  if(front == NULL){
  cout<<"\nNothing to Display\n";
  }else{
  while(p!=NULL){
  cout<<endl<<p->info;
  p = p->next;
  }
  }
}


Queue::Queue() {
  front = NULL;
  rear = NULL;
}


Queue::~Queue() {
  delete front;
}

void Queue::enqueue(int data) {
  node *temp = new node();
  temp->info = data;
  temp->next = NULL;
  if(front == NULL){
  front = temp;
  }else{
  rear->next = temp;
  }
  rear = temp;
}

int Queue::dequeue() {
  node *temp = new node();
  int value;
  if(front == NULL){
  cout<<"\nQueue is Emtpty\n";
  }else{
  temp = front;
  value = temp->info;
  front = front->next;
  delete temp;
  }
  return value;
}

bool Queue::isEmpty() {
  return (front == NULL);
}
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
  Queue Q;
  /** Keeps track of explored vertices */
  
  bool *explored = new bool[n+1];
  for (int i = 1; i <= n; ++i)
  explored[i] = false;

  Q.enqueue(s);
  explored[s] = true; 
  cout << "Breadth first Search starting from vertex ";
  cout << s << " : " << endl;


  while (!Q.isEmpty()) {

  
  int v = Q.dequeue();

  cout << v << " ";
  if(v == g) break;
  
  for (int w = 1; w <= n; ++w)
  if (isConnected(v, w) && !explored[w]) {
  Q.enqueue(w);
  explored[w] = true;
  
  if(v == g) break;
  
  }
  }
  cout << endl;
  delete [] explored;
}

void Graph::print(){
   for (int i = 0; i < mat.size(); i++) { 
        for (int j = 0; j < mat[i].size(); j++) 
			printf(" %d ",mat[i][j] );
		printf(" \n" );
    }
}

int main() {
	
std::vector<std::vector<int> > matrix( 12,std::vector<int>(12));
matrix[1][0] = 1; 
matrix[0][1] = 1;

Graph g(matrix); 

  /** Adds edges to the graph */
  g.addEdge(1, 2); g.addEdge(1, 3);
  g.addEdge(2, 4); g.addEdge(3, 4);
  g.addEdge(3, 6); g.addEdge(4 ,7);
  g.addEdge(5, 6); g.addEdge(5, 7);

   // /*  */
  g.print();
  g.BFS(1, 4);

}