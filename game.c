// Define the number of rows and columns necessary
#define ROWS 4
#define COLS 4
// Arbitrary buffer size 
#define BUFFER 256
// Include separate file of functions to be used in game.c
#include "ascii_land_funcs.c"

// Include standard libraries
#include <stdio.h>
#include <stdlib.h>

// Begin main
int main(int argc, char *argv[]){

    // Maintain position of player in main
    int player_row = 0, player_col = 0;
    // Initialise board size, proposed move and apples left
    char board_array[ROWS][COLS];
    char *board_string;
    char proposed_move_str[BUFFER];
    char proposed_move;
    int apples_left = 0;



    // If the board string is wrong, the program exits
    if (0 != get_boardstring(argc, argv, board_string))
    {
        return 0;
    }

    // Set board string in main
    board_string = argv[1];

    // The board string satisfies requriements.

    /* Convert stored board string to a GUI board.
    Find the row and column index of player position.*/
    set_board(board_string, board_array, &player_row, &player_col, &apples_left);
    
    // Welcome message
    printf("Welcome to ASCII Land!\n");
    // Display the board
    print_board(board_array);

    // The board is set and the game begins

    /* Game is active: it will continue to be forever, 
    unless it is broken by the player successfully reaching
    the winning conditions */
    while (1)
    {
        // Get input from the player: (hopefully) u, d, l, r
        printf("Enter move (udlr): ");
        // Store move as a string
        scanf(" %s", proposed_move_str);

         // Checks if move is valid: u, d, l, r
        if (0 == parse_move_input(proposed_move_str))
        {
            proposed_move = proposed_move_str[0];
            if(0 == check_move_validity(board_array, player_row, player_col, proposed_move, apples_left))
            {
                /* Update board state (e.g. replace proposed move to blank space with P), 
                update the apple counter, player_ROW, player_COL since player has moved */
                update_board(board_array, &player_row, &player_col, proposed_move, &apples_left);
                // Print the new board
                print_board(board_array);
                
                /* Check if the ultimate winning condition have beeen met
                i.e. checks if "G" is still present */
                if(0 == goal_reached(board_array))  
                {
                    // Congratulate player
                    printf("Goal Reached!\n");
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
        // Input was poor, return back to beginning of while loop
        else    
        {

            continue;
        }
    }

    return 0;
}
