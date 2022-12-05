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

