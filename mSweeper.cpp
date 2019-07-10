#include <iostream>
#include <cstdlib>
#include <cstdio>
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
myCursor theCursor;

void initGame(void)
{
  theCursor.x = 0;
  theCursor.y = 0;
  for(int i = 0; i < maxDim; i++) {
    for(int j = 0; j < maxDim; j++) {
      theGrid[i][j].tile_value = "0";
    }
  }
}

void setUpGrid(void)
{
  string placedMines[maxDim];
  int numMines = maxDim;
  int mineNo = 0;
  while(true) {
    //randomly generate seeds
    int x = rand() % 30;
    int y = rand() % 30;
    string potentialMine = std::to_string(x) + ", " + std::to_string(y);
    bool place = true;
    for(int i = 0; i < maxDim/3; i++) {
      if(placedMines[i].compare(potentialMine) == 0) {
        place = false;
      }
    }
    if(place) {
      placedMines[mineNo] = potentialMine;
      mineNo++;
      theGrid[x][y].tile_value = "X";
      for(int i = x - 1; i < x + 2; i++) {
        for(int j = y - 1; j < y + 2; j++) {
          if(i == x && j == y) {
            theGrid[i][j].tile_value = "X";
          } else if(i > -1 && i < maxDim && j > -1 && j < maxDim &&
                    theGrid[i][j].tile_value.compare("X") != 0) {
            theGrid[i][j].tile_value = std::to_string(stoi(theGrid[i][j].tile_value) + 1);
          }
        }
      }
      if(numMines == mineNo) {
        break;
      }
    }
  }
}

void moveCursor(string key)
{
  if(key.compare("k") == 0) {
    if(theCursor.y > 0) {
      theCursor.y--;
    }
  } else if(key.compare("i") == 0) {
    if(theCursor.y < maxDim - 1) {
      theCursor.y++;
    }
  } else if(key.compare("j") == 0) {
    if(theCursor.x > 0) {
      theCursor.x--;
    }
  } else if(key.compare("l") == 0) {
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
  if(std::to_string(flags).compare(theGrid[x][y].tile_value) == 0) {
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
            dig(i, j, depth);
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
  cout << "-+\n";
  for(int i = 0; i < maxDim; i++) {
    cout << "|";
    for(int j = 0; j < maxDim; j++) {
      if(theGrid[i][j].flag) {
        cout << "F" << "|";
      } else if(theGrid[i][j].tile_value.compare("0") != 0) {
        cout << theGrid[i][j].tile_value; << "|";
      } else {
        cout << " " << "|";
      }
    }
    cout << "\n";
    if(i != maxDim - 1) {
      cout << "|";
      for(int j = 0; j < maxDim * 2 - 2; j++) {
        cout << "-";
      }
      cout << "-|" << "\n";
    }
  }
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
      cout << "-";
  }
  cout << "-+" << "\n";
}

void isGameOver(void)
{
  int signals = 0;
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
  cout << "-+\n";
  for(int i = 0; i < maxDim; i++) {
    cout << "|";
    for(int j = 0; j < maxDim; j++) {
      if(theGrid[i][j].tile_value.compare("X") == 0) {
        cout << theGrid[i][j].tile_value << "|";
      } else {
        cout << " " << "|";
      }
    }
    cout << "\n";
    if(i != maxDim - 1) {
      cout << "|";
      for(int j = 0; j < maxDim * 2 - 2; j++) {
        cout << "-";
      }
      cout << "-|" << "\n";
    }
  }
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
      cout << "-";
  }
  cout << "-+" << "\n";
}

int main()
{
  initGame();
  setUpGrid();
  printGrid();
  //game loop
  while(true) {
    string key;
    cout << "Enter an action(f to flag, d to dig, ijkl to move): ";
    cin >> key;
    if(key.compare("i") == 0 || key.compare("j") == 0 || key.compare("k") == 0
        ||key.compare("l") == 0) {
      moveCursor(key);
      printEndGrid();
    } else if(key.compare("d") == 0){
      dig(theCursor.x, theCursor.y, 0);
      printGrid();
    } else if(key.compare("f") == 0) {
      flag(theCursor.x, theCursor.y);
      printGrid();
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
