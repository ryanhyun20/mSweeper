# mSweeper
To build, run `make`.
To clean, run `make clean`.

## User Interface
The program interfaces with the user through prompts on the terminal. The
program launches from the command-line using one argument: `$ mSweeper`. The
user can see a rendition of the game state in the form of a grid printed repeatedly as an action is registered by the program. A cursor denoted by a `C`
character shows the current tile upon which an action is to take place. The
user then inputs single keystrokes defined as follows:
```
j to move cursor left
i to move cursor up
k to move cursor down
l to move cursor right
d to dig the tile the cursor is on
f to flag the tile the cursor is on
```
These single keystrokes must be followed by a single press of the `enter` key
to be considered valid.

## Inputs and Outputs
Input: the inputs are the command-line parameters and keystrokes defined in the User Interface section above.
Output: the output is a frequently re-printed grid of the game. There is no
persistent storage of the game state and events.

## Decomposition into Modules
The following are anticipated modules or functions:
*main*, which parses arguments, initializes data structures and modules, and
contains the game loop
*initGame*, which initializes the global structures of the game
*setUpGrid*, which randomly generates mines in the grid structure of the game,
updating tiles adjacent to mines with values of the count of adjacent tiles with mines
*moveCursor*, which moves the global cursor according to an input single-character string in accordance with the definitions established in the User interface
*isComplete*, which returns true when the tile at the input x- and y- coordinates fulfills the following two conditions:
  1. All adjacent tiles with a mine have been flagged, and only those adjacent tiles have been flagged
*dig*, which excavates the tile the cursor is on, ending the game if the tile has a mine, or exposing the number of mines adjacent to the tile; if the tile has no adjacent mines, `dig` is called recursively on the surrounding tiles with further recursion enabled; if the tile has already been dug and is complete as determined by `isComplete`, then call `dig` recursively on each adjacent non-flagged tile without further recursion
*flag*, which places a flag on a non-flagged tile that has not been dug by `dig`; a flagged tile gets a mystery flag; a mystery-flagged tile becomes a normal un-flagged tile
*printGrid*, which prints the game grid, displaying `F` for flagged tiles, `C` for the cursor tile, integers for tiles upon which `dig` was called, `M` for mystery tiles, and blank spaces for other tiles; a count of flags to be planted is also printed
*isGameOver*, which checks if the game should end, using the number of non-mine tiles dug as an indicator; if the number of non-mine tiles dug is equal to the total number of tiles minus the number of mines, the game is over
*printEndGrid*, which prints the grid, revealing all contents and displaying `F` for correctly-placed flags, `D` for misplaced flags, and `X` for un-flagged mine tiles

## Pseudocode for Logic/Algorithmic Flow
1. execute from the command-line as shown in User Interface
2. initialize the grid and global parameters
3. generate the mines and update the necessary tile values
4. while the game is not over
  1. check if the game is over
    1. end the game if so
  2. print the current game state
  3. give a prompt for input
  4. interpret the input
5. print a gameover message

## Dataflow through Modules
1. `main` parses arguments and calls functions to set up, start and finish the game
2. 
