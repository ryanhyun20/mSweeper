/*
* mSweeper: This file contains the source code for a simple, printing-based
* implementation of the classic game, Minesweeper.
*
* Gameplay: To play, the user inputs keystrokes defined in the game, pressing
* the enter key for each char string. The grid printed by the program is updated
* and printed to show a change in the game state. The i, j, k, and l keys
* correspond to up, left, down, and right movement respectively. The f and d
* keys correspond to flagging and digging tiles on the grid.
*
* Ryan Hyun, July 2019
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
using namespace std;

// struct to hold information regarding the squares in the game grid
struct myTile {
  // number of mines adjacent or mine character
  string tile_value;
  // tells if the tile has been dug
  bool hit;
  // has the tile been flagged
  bool flag;
  // mystery state for second flagging
  bool mystery;
} ;

// struct to hold cursor information
struct myCursor {
  int x;
  int y;
} ;

// maximum dimensions of the grid
const int maxDim = 20;
const int numFlags = maxDim * maxDim/10;
int flagsLeft = numFlags;
// tells whether the game is over
bool gameOver = false;

// game grid
myTile theGrid[maxDim][maxDim];

// cursor for player use
myCursor theCursor;

// initializes the game, setting all relevant values to 0
void initGame(void)
{
  theCursor.x = 0;
  theCursor.y = 0;
  for(int i = 0; i < maxDim; i++) {
    for(int j = 0; j < maxDim; j++) {
      theGrid[j][i].tile_value = "0";
    }
  }
}

// generates randomly placed mines and inputs values into the grid
void setUpGrid(void)
{
  string placedMines[numFlags];
  int numMines = numFlags;
  int mineNo = 0;
  // random seed
  srand(time(NULL));
  while(true) {
    //randomly generate x and y
    int x = rand() % maxDim;
    int y = rand() % maxDim;
    // construct a string for checking existence of a mine
    string potentialMine = std::to_string(x) + ", " + std::to_string(y);
    bool place = true;
    for(int i = 0; i < numFlags; i++) {
      // if the randomly selected coordinates already have a mine, do not place
      // the mine since it would be a duplicate
      if(placedMines[i].compare(potentialMine) == 0) {
        place = false;
      }
    }
    if(place) {
      // place the mine in the grid
      placedMines[mineNo] = potentialMine;
      mineNo++;
      theGrid[x][y].tile_value = "X";
      // for the adjacent tiles, update increment their tile values by one
      // since there is a new mine
      for(int i = y - 1; i < y + 2; i++) {
        for(int j = x - 1; j < x + 2; j++) {
          if(i == y && j == x) {
            theGrid[j][i].tile_value = "X";
          } else if(i > -1 && i < maxDim && j > -1 && j < maxDim &&
                    theGrid[j][i].tile_value.compare("X") != 0) {
            theGrid[j][i].tile_value = std::to_string(stoi(theGrid[j][i].tile_value) + 1);
          }
        }
      }
      // stop when enough mines have been placed
      if(mineNo >= numMines) {
        break;
      }
    }
  }
}

/* moves the cursor according to input from the user
 * assumptions: key is a valid string
 */
void moveCursor(string key)
{
  if(key.compare("k") == 0) {
    // down
    if(theCursor.y < maxDim - 1) {
      theCursor.y++;
    }
  } else if(key.compare("i") == 0) {
    // up
    if(theCursor.y > 0) {
      theCursor.y--;
    }
  } else if(key.compare("j") == 0) {
    // left
    if(theCursor.x > 0) {
      theCursor.x--;
    }
  } else if(key.compare("l") == 0) {
    // right
    if(theCursor.x < maxDim - 1) {
        theCursor.x++;
    }
  }
}

/* checks if the number of flags adjacent to the tile at (x, y) is equal to its
 * tile value
 * assumptions: x and y are valid integers
 */
bool isComplete(int x, int y)
{
  int flags = 0;
  for(int i = y - 1; i < y + 2; i++) {
    for(int j = x - 1; j < x + 2; j++) {
      if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
        if(theGrid[j][i].flag) {
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

/* dig a tile, revealing whether it has a mine
 * assumptions: x, y are valid integers and further is true or false
 */
void dig(int x, int y, bool further)
{
  // do not dig flagged tiles
  if(!theGrid[x][y].flag) {
    if(theGrid[x][y].tile_value.compare("X") == 0) {
      // mine hit, so end the game
      gameOver = true;
    } else if(!theGrid[x][y].hit) {
      // tile has been hit
      theGrid[x][y].hit = true;
      if(theGrid[x][y].mystery) {
        theGrid[x][y].mystery = false;
      }
      // dig adjacent tiles and tiles adjacent to those tiles if no mines are
      // adjacent to the current tile
      if(theGrid[x][y].tile_value.compare("0") == 0) {
        for(int i = y - 1; i < y + 2; i++) {
          for(int j = x - 1; j < x + 2; j++) {
            if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
              dig(j, i, true);
            }
          }
        }
      }
    } else if(theGrid[x][y].hit) {
      if(isComplete(x, y) && further){
        for(int i = y - 1; i < y + 2; i++) {
          for(int j = x - 1; j < x + 2; j++) {
            if(i > -1 && i < maxDim && j > -1 && j < maxDim) {
              // dig only the adjacent tiles if the current tile is complete
              dig(j, i, false);
            }
          }
        }
      }
    }
  }
}

/* flag tiles that could have bombs, make flagged tiles mystery tiles, or make
 * or make mystery tiles normal, non-flagged tiles
 * assumptions: x and y are valid integers
 */
void flag(int x, int y)
{
  // flag non-hit tiles in the pattern flag to mystery to non-flag
  if(!theGrid[x][y].hit) {
    if(theGrid[x][y].flag) {
      theGrid[x][y].flag = false;
      flagsLeft++;
      theGrid[x][y].mystery = true;
    } else if(theGrid[x][y].mystery) {
      theGrid[x][y].mystery = false;
    } else if(!theGrid[x][y].flag) {
      theGrid[x][y].flag = true;
      flagsLeft--;
    }
  }
}

// print the grid
void printGrid(void)
{
  // the grid format is as such: plus symbols at each corner, spaces for
  // non-hit tiles, and tile values for hit tiles
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
    cout << "-";
  }
  cout << "-+\n";
  for(int i = 0; i < maxDim; i++) {
    cout << "|";
    for(int j = 0; j < maxDim; j++) {
      if(theCursor.y == i && theCursor.x == j) {
        // tile the cursor is on
        cout << "C" << "|";
      } else if(theGrid[j][i].flag) {
        // flagged tile
        cout << "F" << "|";
      } else if(theGrid[j][i].mystery) {
        // mystery tile
        cout << "M" << "|";
      } else if(theGrid[j][i].hit) {
        // hit tile
        cout << theGrid[j][i].tile_value << "|";
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
  // bottom row
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
      cout << "-";
  }
  cout << "-+" << "\n";
  // indicate how many flags left to set
  cout << "Flags left: " << std::to_string(flagsLeft) << "/" <<
          std::to_string(numFlags) << "\n";
}

// checks the game state to see if the game should end
void isGameOver(void)
{
  int signals = 0;
  for(int i = 0; i < maxDim; i++) {
    for(int j = 0; j < maxDim; j++) {
      if(!theGrid[j][i].hit && theGrid[j][i].tile_value.compare("X") != 0) {
        signals++;
      }
    }
  }
  if(signals == 0) {
    gameOver = true;
  }
}

// prints the game grid with tile values revealed, showing misplaced flags
void printEndGrid(void) {
  cout << "+";
  for(int i = 0; i < maxDim * 2 - 2; i++) {
    cout << "-";
  }
  cout << "-+\n";
  for(int i = 0; i < maxDim; i++) {
    cout << "|";
    for(int j = 0; j < maxDim; j++) {
      if(theGrid[j][i].flag) {
        if (theGrid[j][i].tile_value.compare("X") == 0) {
          // correctly placed flag
          cout << "F|";
        } else {
          // misplaced flag
          cout << "D|";
        }
      } else {
        cout << theGrid[j][i].tile_value << "|";
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
  // bottom row
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
  //game loop
  while(true) {
    // check for game over status
    if(!gameOver) {
      isGameOver();
    }
    if(gameOver) {
      printEndGrid();
      break;
    }
    printGrid();
    string key;
    // take input and interpret it
    cout << "Enter an action(f to flag, d to dig, ijkl to move): ";
    cin >> key;
    if(key.compare("i") == 0 || key.compare("j") == 0 || key.compare("k") == 0
        ||key.compare("l") == 0) {
      moveCursor(key);
    } else if(key.compare("d") == 0){
      dig(theCursor.x, theCursor.y, true);
    } else if(key.compare("f") == 0) {
      flag(theCursor.x, theCursor.y);
    } else {
      // error handling for non-specified inputs
      cout << "Error: invalid key input\n";
    }
  }
  // game is finished
  cout << "GAME OVER\n";
  // exit with status 0
  return 0;
}
