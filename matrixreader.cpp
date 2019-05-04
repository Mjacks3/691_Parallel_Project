// Peter Gottleib
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

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
    // for each line pushes an empty vector to hold the columns for that row
    adjMatrix.push_back(vector<int>{});
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

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("Error improper arguments\nUsage: ./matrixreader {filename}");
    exit(1);
  }

  char* filename = argv[1];
  tuple<int, vector<vector<int>>> mytuple = matrixRead(filename);
  vector<vector<int>> adjMatrix = get<1>(mytuple);
  for(int i = 0; i < adjMatrix.size(); i++)
  {
    for(int j=0; j<adjMatrix[i].size(); j++)
    {
      printf("%d ", adjMatrix[i][j]);
    }
    printf("\n");
  }
  printf("Goal nodeID: %d\n", get<0>(mytuple));
}