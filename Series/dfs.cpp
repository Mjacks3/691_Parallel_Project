#include <iostream>
#include <vector>
#include <ctime>
#include <malloc.h> 
#include <stdlib.h>

using namespace std;
struct node{
    int info;
    struct node *next;
}; 
 
class stack{
    struct node *top;
    public:
        stack();
        void push(int);
        int pop();
        bool isEmpty();
        void display();
}; 
 
stack::stack(){
    top = NULL;
} 
 
void stack::push(int data){
    node *p;
    if((p=(node*)malloc(sizeof(node)))==NULL){
        cout<<"Memory Exhausted";
        exit(0);
    }
    p = new node;
    p->info = data;
    p->next = NULL;
    if(top!=NULL){
        p->next = top;
    }
    top = p;
} 
 
int stack::pop(){
    struct node *temp;
    int value;
    if(top==NULL){
        cout<<"\nThe stack is Empty"<<endl;
    }else{
        temp = top;
        top = top->next;
        value = temp->info;
        delete temp;
    }
    return value;
} 
 
bool stack::isEmpty(){
    return (top == NULL);
} 
 
void stack::display(){
    struct node *p = top;
    if(top==NULL){
        cout<<"\nNothing to Display\n";
    }else{
        cout<<"\nThe contents of Stack\n";
        while(p!=NULL){
            cout<<p->info<<endl;
            p = p->next;
        }
    }
} 
 
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
    stack s;
    bool *visited = new bool[n+1];
    int i;
    for(i = 0; i <= n; i++)
        visited[i] = false;
    s.push(x);
    visited[x] = true;
    if(x == required) return;
    cout << "Depth first Search starting from vertex ";
    cout << x << " : " << endl;
    while(!s.isEmpty()){
        int k = s.pop();
        if(k == required) break;
        cout<<k<<" ";
        for (i = n; i >= 0 ; --i)
            if (isConnected(k, i) && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
    }
    cout<<endl;
    delete [] visited;
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
/*
g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
g.addEdge(2, 5); g.addEdge(2, 6); g.addEdge(4, 7);
g.addEdge(4, 8);
*/
g.print();
//g.DFS(1, 4);

    return 0;
}