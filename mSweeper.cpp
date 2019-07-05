#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <curses.h>
using namespace std;

struct myTile {
  string tile_value;
  bool hit;
  bool flag;
  bool mystery;
} ;

struct myCursor {
  int x;
  int y;
} ;

const int maxDim = 30;
bool gameOver = false;

myTile theGrid[maxDim][maxDim];
string visGrid[maxDim][maxDim];
myCursor theCursor;

void initGame(void)
{
  theCursor.x = 0;
  theCursor.y = 0;
  for(int i = 0; i < maxDim; i++) {
      for(int j = 0; j < maxDim; j++) {
          visGrid[i][j] = " ";
          theGrid[i][j].tile_value = "0";

      }
  }
}

void setUpGrid(void)
{
  vector<string> placedMines;
  int numMines = maxDim/3;
  while(true) {
    //randomly generate seeds
    int x = rand() % 30;
    int y = rand() % 30;
    string potentialMine = std::to_string(x) + ", " + std::to_string(y);
    bool place = true;
    for(string item: placedMines) {
      if(item.compare(potentialMine) == 0) {
        place = false;
      }
    }
    if(place) {
      placedMines.push_back(potentialMine);
      theGrid[x][y].tile_value = "X";
      for(int i = x - 1; i < x + 2; i++) {
        for(int j = y - 1; j < y + 2; j++) {
          if(i == x && j == y) {
            theGrid[i][j].tile_value = "X";
          } else if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
            theGrid[i][j].tile_value = std::to_string(stoi(theGrid[i][j].tile_value) + 1);
          }
        }
      }
      numMines--;
      if(numMines == 0) {
        break;
      }
    }
  }
}

void moveCursor(int x, int y, int dir)
{
  switch(dir) {
    case 72:
      if(theCursor.y > 0) {
        theCursor.y--;
      }
    case 80:
      if(theCursor.y < maxDim - 1) {
        theCursor.y++;
      }
    case 75:
      if(theCursor.x > 0) {
        theCursor.x--;
      }
    case 77:
      if(theCursor.x < maxDim - 1) {
          theCursor.x++;
      }
  }
}

bool isComplete(int x, int y)
{
  int flags = 0;
  for(int i = x - 1; i < x + 2; i++) {
    for(int j = y - 1; j < y + 2; j++) {
      if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
        if(theGrid[i][j].flag) {
          flags++;
        }
      }
    }
  }
  if(std:to_string(flags).compare(theGrid[x][y].tile_value) == 0) {
      return true;
  }
  return false;
}

void dig(int x, int y, int depth)
{
  if(!theGrid[x][y].flag) {
    if(theGrid[x][y].tile_value.compare("0") == 0) {
      for(int i = x - 1; i < x + 2; i++) {
        for(int j = y - 1; j < y + 2; j++) {
          if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
            dig(x, y, depth);
          }
        }
      }
    } else if(theGrid[x][y].tile_value.compare("X") == 0) {
        //end game
        gameOver = true;
    } else if(!theGrid[x][y].hit) {
      theGrid[x][y].hit = true;
    } else if(isComplete(x, y) && depth == 0){
      for(int i = x - 1; i < x + 2; i++) {
        for(int j = y - 1; j < y + 2; j++) {
          if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
            dig(i, j, 1);
          }
        }
      }
    }
  }
}

void flag(int x, int y)
{
  theGrid[x][y].flag = true;
}

void printGrid(void)
{
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
    cout << "-";
  }
  cout << "+";
  for(int i = 0; i < maxDim; i++) {
    cout << "|";
    for(int j = 0; j < maxDim; j++) {
      cout << visGrid[i][j] << "|";
    }
    cout << "\n";
    cout << "|";
    for(int j = 0; j < maxDim * 2 - 2; j++) {
      cout << "-";
    }
    cout << "|" << "\n";
  }
}

void isGameOver(void)
{
  int signals;
  for(int i = 0; i < maxDim; i++) {
    for(int j = 0; j < maxDim; j++) {
      if(!theGrid[i][j].hit && theGrid[i][j].tile_value.compare("X") != 0) {
        signals++;
      }
    }
  }
  if(signals == 0) {
    gameOver = true;
  }
}

void printEndGrid(void) {
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
    cout << "-";
  }
  cout << "+";
  for(int i = 0; i < maxDim; i++) {
    cout << "|";
    for(int j = 0; j < maxDim; j++) {
      if(theGrid[i][j].tile_value.compare("X") == 0) {
        cout << theGrid[i][j].tile_value << "|";
      } else {
        cout << visGrid[i][j] << "|";
      }
    }
    cout << "\n";
    cout << "|";
    for(int j = 0; j < maxDim * 2 - 2; j++) {
      cout << "-";
    }
    cout << "|" << "\n";
  }
}

int main()
{
  initGame();
  setUpGrid();
  //game loop
  while(true) {
    printGrid();
    char key = getch();
    if(key > 71) {
      moveCursor(theCursor.x, theCursor.y, key);
    } else if(key == 64){
      dig(theCursor.x, theCursor.y, 0);
    } else if(key == 66) {
      flag(theCursor.x, theCursor.y);
    }
    if(!gameOver) {
      isGameOver();
    }
    if(gameOver) {
      printEndGrid();
      break;
    }
  }
  cout << "GAME OVER";
  return 0;
}
