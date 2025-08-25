/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // For the abs() function

int main() 
{
    char board[8][8];

    // Set up empty squares
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            board[i][j] = ' ';
        }
    }

    // Set up white pawns
    for (int j = 0; j < 8; j++) {
        board[1][j] = 'P';
    }

    // Set up other white pieces
    board[0][0] = 'R';
    board[0][1] = 'N';
    board[0][2] = 'B';
    board[0][3] = 'Q';
    board[0][4] = 'K';
    board[0][5] = 'B';
    board[0][6] = 'N';
    board[0][7] = 'R';

    // Set up black pawns
    for (int j = 0; j < 8; j++) 
    {
        board[6][j] = 'p';
    }

    // Set up other black pieces
    board[7][0] = 'r';
    board[7][1] = 'n';
    board[7][2] = 'b';
    board[7][3] = 'q';
    board[7][4] = 'k';
    board[7][5] = 'b';
    board[7][6] = 'n';
    board[7][7] = 'r';

    return 0;
}
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // For abs()

// Function to print the board
void print_board(char board[8][8]) 
{
    printf("\n");
    for (int i = 0; i < 8; i++) 
    {
        printf("%d ", 8 - i); // Row numbers (8 to 1)
        for (int j = 0; j < 8; j++) 
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n"); // Column letters
}

// Function to set up the chess board
void setup_board(char board[8][8]) 
{
    // Empty squares
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            board[i][j] = ' ';
        }
    }

    // Black pieces
    board[0][0] = 'r'; board[0][1] = 'n'; board[0][2] = 'b'; board[0][3] = 'q';
    board[0][4] = 'k'; board[0][5] = 'b'; board[0][6] = 'n'; board[0][7] = 'r';
    for (int j = 0; j < 8; j++) board[1][j] = 'p';

    // White pieces
    board[7][0] = 'R'; board[7][1] = 'N'; board[7][2] = 'B'; board[7][3] = 'Q';
    board[7][4] = 'K'; board[7][5] = 'B'; board[7][6] = 'N'; board[7][7] = 'R';
    for (int j = 0; j < 8; j++) board[6][j] = 'P';
}

// Function to check if a rook can move from (row1, col1) to (row2, col2) on the chessboard
// Returns 1 if valid move, 0 if blocked or illegal
int check_rook_path(char board[8][8], int row1, int col1, int row2, int col2) 
{
    // Must move either horizontally or vertically
    if (row1 != row2 && col1 != col2) 
    {
        return 0;
    }

    // Same square move is invalid
    if (row1 == row2 && col1 == col2) 
    {
        return 0;
    }

    // Horizontal move
    if (row1 == row2) 
    {
        if (col1 < col2) 
        {
            // Moving right
            for (int col = col1 + 1; col < col2; col++) 
            {
                if (board[row1][col] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
        else 
        {
            // Moving left
            for (int col = col1 - 1; col > col2; col--) 
            {
                if (board[row1][col] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
    }

    // Vertical move
    if (col1 == col2) 
    {
        if (row1 < row2) 
        {
            // Moving down
            for (int row = row1 + 1; row < row2; row++) 
            {
                if (board[row][col1] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
        else 
        {
            // Moving up
            for (int row = row1 - 1; row > row2; row--) 
            {
                if (board[row][col1] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
    }

    // Check capture rules (cannot capture own piece)
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2])))) 
    {
        return 0;
    }

    return 1; // Valid rook move
}
//Function to check if a king can move from (row1, col1) to (row2, col2) on the chessboard
// Returns 1 if valid move, 0 if blocked or illegal

int check_king_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	int row_diff = abs(row2 - row1);
	int col_diff = abs(col2 - col1);

	// Must move atleast one square, and at most one square in any direction
    if (row_diff <= 1 && col_diff <= 1 && (row1 != row2 || col1 != col2))
    {
        //Check if the destination square is occupied by own piece
        if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2]))))
        {
            return 0; // Cannot capture own piece
		}
		return 1; // Valid king move
    }
	return 0; // Invalid king move
}

// Function to check if a bishop can move from (row1, col1) to (row2, col2) on the chessboard
// Returns 1 if valid move, 0 if blocked or illegal

int check_bishop_path(char board[8][8], int row1, int col1, int row2, int col2)
{
    if (abs(row2 - row1) != abs(col2 - col1))
    {
        return 0; // Must move diagonally
    }
    if (row1 == row2 && col1 == col2)
    {
        return 0; // Same square move is invalid
    }
    // Determine the direction of movement
    int row_step = (row2 > row1) ? 1 : -1;
    int col_step = (col2 > col1) ? 1 : -1;

    //Start checking the path right after the starting square 
    int current_row = row1 + row_step;
    int current_col = col1 + col_step;

    while (current_row != row2 && current_col != col2)
    {
        if (board[current_row][current_col] != ' ')
        {
            return 0; // Blocked by another piece
        }
        current_row = current_row + row_step;
        current_col = current_col + col_step;
    }

	// Check if the destination square is occupied by own piece
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2]))))
    {
        return 0; // Cannot capture own piece
    }
    return 1; // Valid bishop move
}

// Function to check if a knight can move from (row1, col1) to (row2, col2) on the chessboard
int check_knight_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	//Knight moves in a "L" shape i.e. two squares in one direction and one square perpendicular
	//Same square move is invalid
    if (row1 == row2 && col1 == col2) 
    {
        return 0; // Invalid move
	}
	//Knight can move in 8 possible ways
    int valid = (col2 == col1 + 1 && row2 == row1 - 2) ||
                (col2 == col1 + 2 && row2 == row1 - 1) ||
                (col2 == col1 + 2 && row2 == row1 + 1) ||
                (col2 == col1 + 1 && row2 == row1 + 2) ||
                (col2 == col1 - 1 && row2 == row1 + 2) ||
                (col2 == col1 - 2 && row2 == row1 + 1) ||
                (col2 == col1 - 2 && row2 == row1 - 1) ||
                (col2 == col1 - 1 && row2 == row1 - 2);
	if (!valid)
    {
                return 0; // Invalid knight move
	}


	// Check if the destination square is occupied by own piece
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2])))) 
    {
        return 0; // Cannot capture own piece
    }
	return 1; // Valid knight move
}


// Function to check if a queen can move from (row1, col1) to (row2, col2) on the chessboard
int check_queen_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	if (row1 == row2 && col1 == col2) // Same square move is invalid
    {
        return 0; // Invalid move
    }

    // A queen can move like a rook or a bishop
    int valid = check_rook_path(board, row1, col1, row2, col2) || check_bishop_path(board, row1, col1, row2, col2);
    
    if (!valid)
    {
        return 0; // Invalid queen move
	}
    /*
    This is an alternative way to check queen move without using rook and bishop functions
    if ((row1== row2 || col1 ==col2) || (abs(row2 - row1) == abs(col2 - col1)))
    {
    printf("Valid queen move\n");
    }
    else
    {
        printf("Invalid queen move\n");
    }
    */

    // Check if the destination square is occupied by own piece
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2]))))
    {
        return 0; // Cannot capture own piece
    }
    return 1; // Valid queen move
}
// Function to check if a pawn can move from (row1, col1) to (row2, col2) on the chessboard
// Function to check if a pawn move is valid
int check_pawn_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	char piece = board[row1][col1];

	//Same square move is invalid
    if (row1 == row2 && col1 == col2) 
    {
        return 0;
	}
	//White pawn moves upward (row decreases)
    if (piece == 'P')
    {
		//Forward move by 1 (only if the square is empty)
        if (col1 == col2 && row2 == row1 - 1 && board[row2][col2] == ' ')
        {
			return 1; // Valid move
        }

		//Forward move by 2 (only if starting row = 6 and both squares are empty)
        if (col1 == col2 && row1 == 6 && row2 == 4 && board[5][col1] == ' ' && board[4][col1] == ' ')
        {
			return 1; // Valid move
        }

        //Diagonal capture by 1 (enemy must be black piece = lowecase)
        if ((col2 == col1 + 1 || col2 == col1 - 1) && row2 == row1 - 1 && board[row2][col2] != ' ' && islower(board[row2][col2]))
        {
			return 1; // Valid capture
        }
    }

    //Black pawn moves downward (row increases)
    else if (piece == 'p')
    {
        //Forward move by 1 (only if the square is empty)
        if (col1 == col2 && row2 == row1 + 1 && board[row2][col2] == ' ')
        {
            return 1; // Valid move
        }

        //Forward move by 2 (only if starting row = 1 and both squares are empty)
        if (col1 == col2 && row1 == 1 && row2 == 3 && board[2][col1] == ' ' && board[3][col1] == ' ')
        {
            return 1; // Valid move
        }

        //Diagonal capture by 1 (enemy must be white piece = uppercase)
        if ((col2 == col1 + 1 || col2 == col1 - 1) && row2 == row1 + 1 && board[row2][col2] != ' ' && isupper(board[row2][col2]))
        {
            return 1; // Valid capture
        }
    }

	// If none of the valid moves matched, return 0
	return 0; // Invalid pawn move
}

// forward declarations of your functions
void setup_board(char board[8][8]);
void print_board(char board[8][8]);
int check_pawn_path(char board[8][8], int r1, int c1, int r2, int c2);
int check_rook_path(char board[8][8], int r1, int c1, int r2, int c2);
int check_knight_path(char board[8][8], int r1, int c1, int r2, int c2);
int check_bishop_path(char board[8][8], int r1, int c1, int r2, int c2);
int check_queen_path(char board[8][8], int r1, int c1, int r2, int c2);
int check_king_path(char board[8][8], int r1, int c1, int r2, int c2);

/*
int main() {
    char board[8][8];
    setup_board(board);

    while (1) {
        print_board(board);

        int r1, c1, r2, c2;
        printf("Enter your move (from_row from_col to_row to_col): ");
        scanf_s("%d %d %d %d", &r1, &c1, &r2, &c2);

        char piece = board[r1][c1];
        int valid = 0;

        switch (tolower(piece)) {
        case 'p': valid = check_pawn_path(board, r1, c1, r2, c2); break;
        case 'r': valid = check_rook_path(board, r1, c1, r2, c2); break;
        case 'n': valid = check_knight_path(board, r1, c1, r2, c2); break;
        case 'b': valid = check_bishop_path(board, r1, c1, r2, c2); break;
        case 'q': valid = check_queen_path(board, r1, c1, r2, c2); break;
        case 'k': valid = check_king_path(board, r1, c1, r2, c2); break;
        default: printf("No piece at that position!\n"); continue;
        }

        if (valid)
            printf(" Valid move!\n\n");
        else
            printf(" Invalid move!\n\n");
    }

    return 0;
}
*/

