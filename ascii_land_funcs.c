// Include standard libraries
#include <stdio.h>
#include <string.h>
// Define the number of rows and columns necessary
#define ROWS 4
#define COLS 4
// Define the length of the active playing board
#define BOARDSTRING_LENGTH 16


int parse_command_line(int argc, char *argv[])
{
    // If there are a wrong number of arguments passed through
    if (argc != 2)
    {
        // Print an error message, terminate
        printf("Incorrect number of arguments to run the game\n");
        return -1;
    }

    // Check second argument to be exactly BOARDSTRING_LENTH long
    if (strlen(argv[1]) != BOARDSTRING_LENGTH)
    {
        // Terminate
        return -1;
    }
    return 0;
}


int get_boardstring(int argc, char *argv[], char *board_string)
{

    int g_counter = 0, p_counter = 0, valid_map = 0;

    // Check if command line entry is successful
    if (0 != parse_command_line(argc, argv))
    {
        // Terminate
        return -1;
    }

    // Retrieve board string
    board_string = argv[1];

    // Check adequacy of board string
    for (int i = 0; i < strlen(board_string); i++)
    {
        /* Check each character within the board string 
        Check characters lie between 0 and 4, inclusive */
        if ((board_string[i] > '4') || (board_string[i] < '0'))
        {
            // Invalidate map
            valid_map++;
        }

        // Check there exists 1 goal, total
        if (board_string[i] == '4')
        {
            g_counter++;
        }
        
        // Check there exists exactly 1 player
        if (board_string[i] == '3')
        {
            p_counter++;
        }
    }

    // Valid maps only contain valid characters
    if (valid_map != 0)
    {
        // Print an error message
        printf("Invalid Map: invalid character\n");
        return -1; 
    }
    
    // There must be exactly 1 player
    if (p_counter != 1 && valid_map == 0)
    {
        // Print an error message
        printf("Invalid Map: must have exactly one player\n");
        return -1;
    }

    // There must be exactly 1 goal
    if (g_counter != 1 && valid_map == 0)
    {                   
        printf("Invalid Map: must have exactly one goal\n");
        return -1;
    }

    // If preliminary tests are passed, return 0 (no errors).
    return 0;
}

/* Fill in 2-D board array using the board string. 
Get row and column position of the player, stored in main */
void set_board(char *board_string, char board_array[4][4], int *player_row, int *player_col, int *apples_left){
    // Initialise an index to keep track of board element
    int index = 0;
    // Nested loop to check through each string character
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {   
            
            // Fill in the board
            switch(board_string[index])
            {
                case '0':
                    board_array[i][j] = ' ';
                    break;
                case '1':
                    board_array[i][j] = '*';
                    break;
                case '2':
                    board_array[i][j] = 'A';
                    (*apples_left)++;
                    break;
                case '3':
                    board_array[i][j] = 'P';
                    // Update position coordinates in main when player is found
                    *player_row = i;   
                    *player_col = j;
                    break;
                case '4':
                    board_array[i][j] = 'G';
                    break;
            }
            // Increment index
            index++;
        }
    }
    return;
}

// Function to print the gameboard
void print_board(char board_array[ROWS][COLS]){

    // Nested loop to display a border around the active game board
    for (int i = 0; i < ROWS+2; i++)
    {
        // Print the top and bottom border
        if ((i == 0) || (i == 5))
        {
            printf("******\n");
            continue;
        }
        
        for (int j = 0; j < COLS+2; j++)
        {
            if ((j == 0) || (j == 5))
            {
                // Print the verical borders
                printf("*");
                continue;
            }
            printf("%c", board_array[i-1][j-1]);
        }
        printf("\n");
    }

}

// Check if the input move is valid
int parse_move_input(char *proposed_move_str){

    if(strlen(proposed_move_str) > 1){
        printf("Invalid move!\n");
        return -1;
    }

    // Checks if the user entered a valid input direction
    switch(proposed_move_str[0])
    {
        case 'u':
            return 0;
            break;
        case 'd':
            return 0;
            break;
        case 'l':
            return 0;
            break;
        case 'r':
            return 0;
            break;
        // Otherwise, the move is erronous 
        default:    
            return -1;
    }

    return 0;
}

// Function to check if the move entered is possible, according to the game's logic
int check_move_validity(char board_array[4][4], int player_row, int player_col, char proposed_move, int apples_left){
    // Initialise where the player is currently 
    int proposed_new_row = player_row;
    int proposed_new_col = player_col;
    
    /* Faux move the player's row and column position, according to the proposed move. 
    This won't update variables in main because the passed in by value is only used 
    for checking the move, and not enacting it */
    switch(proposed_move)
    {
        case 'u':
            // up relates to decrementing the row position of the player
            (proposed_new_row)--;
            break;
        case 'd':
            // down relates to incrementing the row position of the player
            (proposed_new_row)++;
            break;
        case 'l':
            // left relates to decrementing the column position of the player
            (proposed_new_col)--;
            break;
        case 'r':
            // right relates to incrementing the column position of the player
            (proposed_new_col)++;
            break;
    }    
    
    // Check the bounds of the array and decides whether the faux move is out of bounds
    // Row lies outside of bounds:
    if ((proposed_new_row < 0) || (proposed_new_row > 3))
    {
        print_board(board_array);
        return -1;
    }
    // Column lies outside of bounds:
    if ((proposed_new_col < 0) || (proposed_new_col > 3))
    {
        print_board(board_array);
        return -1;
    }

    // Checks whether the new move overlaps a '*'
    if (board_array[proposed_new_row][proposed_new_col] == '*')
    {
        print_board(board_array);
        return -1;
    }
    // Checks if a player is attempting to move into the goal before collecting all apples
    if ((board_array[proposed_new_row][proposed_new_col] == 'G') && (apples_left != 0))
    {
        print_board(board_array);
        return -1;
    }

    return 0;
}

/* This function applies the validated move input to the board, 
updating the state of the board and moving the player coordinates accordingly. */
void update_board(char board_array[4][4], int *player_row, int *player_col, char move, int *apples_left){
    
    // First, set current position to ' '
    board_array[*player_row][*player_col] = ' ';

   // Second, convert 'u', 'd', 'l', 'r' into new row and column coordinates
    switch(move)
    {
        case 'u':
        // up relates to decrementing the row position of the player
            (*player_row)--;
            break;
        case 'd':
        // down relates to incrementing the row position of the player
            (*player_row)++;
            break;
        case 'l':
        // left relates to decrementing the column position of the player
            (*player_col)--;
            break;
        case 'r':
        // right relates to incrementing the column position of the player
            (*player_col)++;
            break;
    }

    // Player's position is now updated.

    // Check if new position is an apple, if so decrement apple counter
    if (board_array[*player_row][*player_col] == 'A')
    {
        (*apples_left)--;
        // Print a confirmation message
        printf("Got Apple!\n");
    }

    // Update the board by placing 'P' at the new position
    board_array[*player_row][*player_col] = 'P';

    return;
}

/* Checks if the winning conditions have been met:
If game is over, there will be no more 'G's on the board. */
int goal_reached(char board_array[4][4]){

    // Iterate through the board and check if there is a 'G'
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j ++)
        {
            // If a goal is found, return a fail
            if (board_array[i][j] == 'G')
            {
                return -1;
            }
        }
    }

    // If loops finish and no 'G' was found, game must be concluded; return 0;
    return 0;
}


