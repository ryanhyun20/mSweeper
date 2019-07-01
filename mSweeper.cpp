#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

static int maxDim = 30;
void setUpGame(string[][maxDim] grid) {
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
            grid[i][j] = std::to_string(stoi(grid[i][j]) + 1);
          }
        }
      }
    }
  }
}

int main()
{
  setUpGame();
  while(true) {
    //print game state
    //wait for stuff
  }
}
