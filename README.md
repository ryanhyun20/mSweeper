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
