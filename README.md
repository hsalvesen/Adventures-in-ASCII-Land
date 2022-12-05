# Adventures-in-ASCII-Land
A simple, single-player arcade-like video game.

Code for this program is split between two files: game.c hosting main; and ascii_land_funcs.c, hosting functions frequently called.

When called, the program begins and immediately terminates if input arguments are invalid.
With a correct game string, user is welcomed, and the string is decoded. Program GUI (game board) is printed as a 2-D array.

The program then enters an infinite loop where the user is asked for move inputs corresponding to movement coordinates for the array element ‘P’. 
Each loop, the program accesses if the input move is acceptable, then appropriate. The while loop will:

–	re-prompt the user for input if an incorrect movement (not udlr) is entered

–	assess the udlr movement choice (with a faux move) and re-print the board and re-prompt the user if an invalid movement choice is made (to a *, or to G prematurely)

–	update the player coordinates if the faux move is valid by game logic, update the board, check if the user is on an apple, then printing the new board. Prompt the user for another move.

– If P moves to G (only when no apples remain), the board will print a success message and terminate by exiting the while loop.


Flow of the Game:

The state of the game maze/map at the start of the game is specified by the user when they run the executable using a single argument to the program from the terminal, in the following form:

./game <maze_string>

Here, maze_string is a 16-character long string representing the "state" of each grid square, read from the top-left corner along the top row, the followed by the second row, third row and fourth row of the game maze. Each character in the string is actually a number representing the type of grid or grid object that should appear at each location:

0: a blank square

1: a "blocked/obstacle" square ('*')

2: An apple ('A')

3: The player's starting square ('P')

4: The goal square ('G')

For example, running the game with ./game 3120010204000000, would produce the following maze at the start of the game:

******

*P*A *

* * A*

* G  *

*    *

******

If the program is run using an incorrect number of arguments, then the program should quit after displaying the message:
Incorrect number of arguments to run the game.
If the provided string contains any invalid characters (i.e. not in 0 1 2 3 4), then the program should quit after displaying the message:

Invalid Map: invalid character

Valid game maps must contain exactly one player start position and one goal position: if the map does not contain the correct number of player start positions, then the program should quit after displaying the message:

Invalid Map: must have exactly one goal

If the map does not contain the correct number of goal positions, then the program should quit after displaying the message:

Invalid Map: must have exactly one player
