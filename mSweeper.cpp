#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

static int maxDim = 30;

struct tile {
    int x_value;
    int y_value;
    string tile_value;
    bool found;
    bool hit;
}

void initGrid(string[][maxDim] grid) {
  for(int i = 0; i < maxDim; i++) {
      for(int j = 0; j < maxDim; j++) {
          grid[i][j] = "0";
      }
  }
}

void setUpGrid(string[][maxDim] grid) {
  vector<string> placedMines;
  while(true) {
    //randomly generate seeds
    int x = rand() % 30;
    int y = rand() % 30;
    string potentialMine = std::to_string(x) + ", " + std::to_string(y);
    bool place = true;
    for(string item: placedMines) {
      if(item.compare(potentialMine) == 0) {
        place = false;
        break;
      }
    }
    if(place) {
      placedMines.push_back(potentialMine);
      grid[x][y] = "X";
      for(int i = x - 1; i < x + 2; i++ {
        for(int j = y - 1; j < y + 2; j++) {
          if(i == x && j == y) {
            grid[i][j] = "X";
          } else if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
            if(grid[i][j]
            grid[i][j] = std::to_string(stoi(grid[i][j]) + 1);
          }
        }
      }
    }
  }
}

void moveCursor(int x, int y, string dir) {

}

void dig(int x, int y, string act) {
  if(act.compare("f") == 0) {

  }
}

void flag(int x, int y) {

}

int main()
{
  string grid[maxDim][maxDim];
  initGrid(grid);
  setUpGrid(grid);
  //game loop
  while(true) {
    //print game state
    printGrid(grid);
    //wait for stuff
    while()
  }
}
