# generates an adjacency matrix representative of a randomly generated maze
# takes in two arguments, x and outputFile
# x is the size of one dimension of the desired maze size, thus x=5 indicates a 5x5 size maze

# runs in python 3.6.0 or higher

# 5x5 matrix: each number corresponds to id of cell
# 00 01 02 03 04
# 05 06 07 08 09
# 10 11 12 13 14
# 15 16 17 18 19
# 20 21 22 23 24


# outputFile is the destination of the adjacency matrix

import sys
import random

def main():
  if len(sys.argv) != 3:
    print(f"error, invalid arguments\n");
    print(f"Usage: python maze_generator.py (int) (string)");
    sys.exit();

  print("beginning")
  size = int(sys.argv[1]);
  output = sys.argv[2];
  # generate a blank adjacency matrix
  adjMatrix = [[0 for i in range(size*size)] for j in range(size*size)];
  print("choosing starting node")
  # choose a random cell id to begin generation of the maze
  curr = random.randint(0,size*size-1);
  # initializes visited matrix
  visited = [];
  # initializes frontier and adds first node to frontier
  frontier = [];
  frontier.append(curr);
  print("generating neighbours")
  # while we haven't visited every node
  while len(frontier) != 0:
    curr = frontier.pop(0);
    visited.append(curr);
    # gets the neighbours of current node
    neighbours = getNeighbours(curr, size);
    # randomizes expansion of neighbours
    random.shuffle(neighbours);
    # checks all neighbours of currrent node
    for neighbour in neighbours:
      # makes sure we haven't found node yet
      if neighbour not in frontier and neighbour not in visited:
        frontier.insert(0,neighbour);
        # adds edge in adjacency matrix in both directions
        adjMatrix[curr][neighbour] = 1;
        adjMatrix[neighbour][curr] = 1;

  print("writing to file")
  with open(output, "w+") as file:
    for row in adjMatrix:
      count = 0;
      for col in row:
        file.write(str(col));
        file.write(",");
        count+=1;
        if count == size*size:
          file.write("\n");

def getNeighbours(curr, size):
  neighbours = [];

  # adds north neighbour
  if curr >= size:
    neighbours.append(curr-size);

  # adds west neighbour
  if curr%size > 0:
    neighbours.append(curr-1);

  # adds east neighbour
  if curr%size < size-1:
    neighbours.append(curr+1);

  # adds south neighbour
  if curr<size*size-size:
    neighbours.append(curr+size);

  return neighbours;

if __name__ == '__main__':
  main();