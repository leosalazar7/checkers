// Leo Salazar
// 8/1/2023

#include "checkers.h"

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();
    // call function clearScreen
    clearScreen();
    // call function displayExplicitBoard
//    displayExplicitBoard();
    // call function playGame
    playGame();
    // program executed successfully
    return 0;
}

// welcomeScreen function displays the Checkers logo and rules of the game
void welcomeScreen ()
{
	printf ("\t\t CCCC  HH  HH  EEEEE   CCCC  KK  KK  EEEEE  RRRRR    SSSS   \n");
	printf ("\t\tCC     HH  HH  EE     CC     KK KK   EE     RR RR   SS      \n");
	printf ("\t\tCC     HHHHHH  EEEE   CC     KKK     EEEE   RRRR     SSSS   \n");
	printf ("\t\tCC     HH  HH  EE     CC     KK KK   EE     RR RR       SS  \n");
	printf ("\t\t CCCC  HH  HH  EEEEE   CCCC  KK  KK  EEEEE  RR  RR  SSSSS   \n");
	printf ("\n\n");//
	printf ("CHECKERS GAME RULES\n\n");
    printf("\t 1. The board includes 64 alternating dark and light squares with 8 rows and 8 columns.\n");
    printf("\t 2. Each player places their pieces on the 12 dark squares in the first 3 rows closest to them.\n");
    printf("\t 3. Each of these 3 rows should have a total of 4 checkers.\n");
    printf("\t 4. The player with the black checkers always goes first.\n");
    printf("\t 5. Players can only move 1 checker 1 diagonal space forward during a regular turn.\n");
    printf("\t 6. Checkers must stay on the dark squares.\n");
    printf("\t 7. Jump the opponent's checkers to remove them from the board.\n");
    printf("\t 8. Players alternate turns.\n");
    printf("\t 9. If a player can jump their opponent's checker, the player must jump it.\n");
    printf("\t10. A player must keep capturing their opponent's checkers until no checkers are available to jump.\n");
    printf("\t11. Players king their pieces when their checkers reach the end of their opponent's side.\n");
    printf("\t12. The king can move forward and backward diagonally on the dark squares.\n");
    printf("\t13. Once a player has captured all their opponent's checkers, they have won the game!\n");
}

// function displayExplicitBoard displays a hardcoded version of an Checkers board
void displayExplicitBoard()
{
    printf("|-----------------------------------------------------|\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  1  |     |  W  |     |  W  |     |  W  |     |  W  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  2  |  W  |     |  W  |     |  W  |     |  W  |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  3  |     |  W  |     |  W  |     |  W  |     |  W  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  4  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  5  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  6  |  B  |     |  B  |     |  B  |     |  B  |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  7  |     |  B  |     |  B  |     |  B  |     |  B  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  8  |  B  |     |  B  |     |  B  |     |  B  |     |\n");
    printf("|-----------------------------------------------------|\n");
 }

// function clearScreen clears the screen for display purposes
void clearScreen()
{
    printf("\n\t\t\t\tHit <ENTER> to continue!\n");

	char enter;
	scanf("%c", &enter );

	// send the clear screen command Windows
    system("cls");
    // send the clear screen command for UNIX flavor operating systems
//    system("clear");
}

void playGame()
{
    // declare variable for each player as a struct
    struct Player playerB;
    struct Player playerW;

    // black (B) always goes first
    int currentPlayer = PLAYER_B;
    int loop = ZERO;

    char board[ROW][COL]; // this is really a memory location of board[0][0]

    // create struct for each player
    printf("Player B, please enter your name\n");
    scanf("%s", playerB.playerName);
    playerB.playerNum = PLAYER_B;
    playerB.playChar = 'B';
    playerB.numCheckers = TWELVE;

    printf("Player W, please enter your name\n");
    scanf("%s", playerW.playerName);
    playerW.playerNum = PLAYER_W;
    playerW.playChar = 'W';
    playerW.numCheckers = TWELVE;

    printf("%s and %s, let's play Checkers!\n", playerB.playerName, playerW.playerName);

    // call function initializeBoard
    initializeBoard(board);


    //while(loop<THREE) (i used this to test the end game and winner screen)
    // runs the while loop as long as both players still have checkers to play with
    while(gameOver(playerB, playerW) == FALSE)
    {
        // call function displayBoard
        displayBoard(board);

        // switch players for each move
        if(currentPlayer == PLAYER_B)
        {
            makeMove(&playerB, board);
            currentPlayer = PLAYER_W;
        }
        else if(currentPlayer == PLAYER_W)
        {
            makeMove(&playerW, board);
            currentPlayer = PLAYER_B;
        }

        updateCheckerCount(board, &playerB);
        displayStats(playerB);

        updateCheckerCount(board, &playerW);
        displayStats(playerW);

        //setEndGame(&playerB);

        // displays the winner if one of the players runs out of checkers
        displayWinner(&playerB, &playerW);

        //loop++;
    }
    // call function displayBoard
    displayBoard(board);
    //setEndGame(&playerB);
    displayWinner(&playerB, &playerW);
}

void initializeBoard(char board[ROW][COL])
{
    for(int row = 0; row < ROW; row++)
    {
        for(int col = 0; col < COL; col++)
        {
            // row and column are both even
            if(row % 2 == 0 && col % 2 == 0)
                board[row][col] = SPACE;
            // row and column are both odd
            else if(row % 2 != 0 && col % 2 != 0)
                board[row][col] = SPACE;
            // row and column are not both even or both odd
            else
            {
                if(row < 3)
                {
                    board[row][col] = 'W';
                }
                else if (row > 4)
                {
                    board[row][col] = 'B';
                }
                else
                {
                    board[row][col] = SPACE;
                }
            }
        }
    }
}

void displayBoard(char board[ROW][COL])
{
    printf("|-----------------------------------------------------|\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");

    for(int row = 0; row < ROW; row++)
    {
        printf("|-----------------------------------------------------|\n");
        printf("|  %d  |", (row + 1));

        for(int col = 0; col < COL; col++)
        {
            printf("  %c  |", board[row][col]);
        }

        printf("\n");
    }

    printf("|-----------------------------------------------------|\n");
}

void makeMove(struct Player *player, char board[ROW][COL])
{
    char start[THREE];
    char end[THREE];
    int valid = FALSE;

    // loop until the player enters a valid move
    while(valid == FALSE)
    {
        printf("%s, enter location of checker to move (e.g. B6)\n", player->playerName);
        scanf("%s", start);

        printf("%s, enter new location for the checker (e.g. C5)\n", player->playerName);
        scanf("%s", end);

        printf("%s, wants to move checker %s to square %s\n", player->playerName, start, end);

        int lengthS = (int)strlen(start);
        int lengthE = (int)strlen(end);

        if( (lengthS == TWO) && (lengthE == TWO) &&
            (isValid(start, end, board, player->playChar) == TRUE) )
        {
            valid = TRUE;
            updateBoard(start, end, board);
        }
        else
        {
            valid = FALSE;
            printf("\tInvalid move, try again\n");
        }
    }
}

int isValid(char start[THREE], char end[THREE], char board[ROW][COL], char playerChar)
{
    int valid = FALSE;

    // check if the start square has a valid checker
    valid = hasChecker(start, board, playerChar);

    // if the start square is not the correct checker, return FALSE
    if(valid == FALSE)
        return valid;

    // check if the end square is open
    valid = isOpen(end, board);

    // if the end square is not open, return FALSE
    if(valid == FALSE)
        return valid;

    // Players can move diagonally 1 or two spaces(depending)
    valid = isDiagonal(start, end, playerChar, board);

    // if the move is not diagonal, return FALSE
    if(valid == FALSE)
        return valid;

    return valid;
}

int isOpen(char end[THREE], char board[ROW][COL])
{
    int open = FALSE;

    // get the indexes for the board row and column to check the array
    int rowInt = getMoveRow(end);
    int colInt = getMoveCol(end);

    if( (rowInt != INVALID) && (colInt != INVALID) &&
        (board[rowInt][colInt] == SPACE))
    {
        open = TRUE;
        printf("\tEnd position is open!\n");
    }
    else
        open = FALSE;

    return open;
}

int hasChecker(char start[THREE], char board[ROW][COL], char playerChar)
{
    int checker = FALSE;

    // get the indexes for the board row and column to check the array
    int rowInt = getMoveRow(start);
    int colInt = getMoveCol(start);

    // check if the start square has the correct checker
    if( (rowInt != INVALID) && (colInt != INVALID) &&
        (board[rowInt][colInt] == playerChar))
    {
        checker = TRUE;
        printf("\tThe selected checker is valid!\n");
    }
    else
    {
        checker = FALSE;
    }

    return checker;
}

int getMoveCol(char move[THREE])
{
    // initialize to an invalid value
    int colInt = INVALID;
    // use the array to get the index value for the board array row
    //              0    1    2    3    4    5    6    7
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for(int col = 0; col < COL; col++)
    {
        // convert the first character to upper case
        if(toupper(move[ZERO]) == cols[col])
            colInt = col;
    }

    return colInt;
}

int getMoveRow(char move[THREE])
{
    // initialize to an invalid value
    int rowInt = INVALID;
    // use the array to get the index value for the board array column
    //              0    1    2    3    4    5    6    7
    char rows[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    for(int row = 0; row < ROW; row++)
    {
        // the second character in the move array is the column
        if(move[ONE] == rows[row])
            rowInt = row;
    }

    return rowInt;
}

void displayStats(struct Player player)
{
    printf("Player name:      %s\n", player.playerName);
    printf("Player number:    %d\n", player.playerNum);
    printf("Player character: %c\n", player.playChar);
    printf("Player checkers:  %d\n\n", player.numCheckers);
}

int isDiagonal(char start[THREE], char end[THREE], char playerChar, char board[ROW][COL])
{
    int diagonal = FALSE;

    // start row and col
    int sRow = getMoveRow(start);
    int sCol = getMoveCol(start);

    // end row and col
    int eRow = getMoveRow(end);
    int eCol = getMoveCol(end);

    if(sRow != INVALID && sCol != INVALID &&
       eRow != INVALID && eCol != INVALID )
    {
        // playerB's rows should decrement
        // playerB's cols can increment and decrement
        if(playerChar == 'B')
        {
            // start row should be end row - 1 AND
            // start col should be end col + 1 OR end col - 1
            if((sRow - ONE) == eRow &&
              (sCol == (eCol + ONE) || sCol == (eCol - ONE)))
            {
                diagonal = TRUE;
            }
            // calls ifJump to check if the move jumps over an opposing player's piece
            else if (isJump(sRow, sCol, eRow, eCol, board, playerChar) == TRUE)
            {
                diagonal = TRUE;
            }
            else
            {
                diagonal = FALSE;
            }
        }
        // playerW's rows should increment
        // playerW's cols can increment and decrement
        else if (playerChar == 'W')
        {
            // start row + 1 should equal end row AND
            // start col should be end col + 1 OR end col - 1
            if((sRow + ONE) == eRow && (sCol == (eCol + ONE) || sCol == (eCol - ONE)))
            {
                diagonal = TRUE;
            }
            else if ((sRow + TWO) == eRow && (sCol == (eCol + TWO) || sCol == (eCol - TWO)))
            {
                diagonal = TRUE;
            }
            else
            {
                diagonal = FALSE;
            }
        }
    }

    return diagonal;
}

void updateBoard(char start[THREE], char end[THREE], char board[ROW][COL])
{
    // start row and col
    int sRow = getMoveRow(start);
    int sCol = getMoveCol(start);

    // end row and col
    int eRow = getMoveRow(end);
    int eCol = getMoveCol(end);

    // read the character at the start location
    char playerChar = board[sRow][sCol];

    // update the board at the end location
    board[eRow][eCol] = playerChar;

    // will replace jumped square with a SPACE
    if (isJump(sRow, sCol, eRow, eCol, board, playerChar) == TRUE)
    {
        board[abs((eRow+sRow)/2)][abs((eCol+sCol)/2)] = SPACE;
    }

    // update the start location to a SPACE
    board[sRow][sCol] = SPACE;
}

void updateCheckerCount(char board[ROW][COL], struct Player *player)
{
    int checker = 0;

    for(int row = 0; row < ROW; row++)
        for(int col = 0; col < COL; col++)
            if(board[row][col] == player->playChar)
                checker++;

    player->numCheckers = checker;
}

int isJump(int sRow, int sCol, int eRow, int eCol, char board[ROW][COL], char playerChar)
{
    int jump = FALSE;
    int mRow = abs((eRow+sRow)/2);
    int mCol = abs((eCol+sCol)/2);

    // checks if the player moves the checker piece by 2 rows and 2 columns
    if ((eRow+sRow)%2 == 0 && (eCol+sCol)%2 == 0)
    {
        // checks if the space the player jumped over has its own piece or space
        if ((board[mRow][mCol] != playerChar && board[mRow][mCol] != SPACE))
        {
            jump = TRUE;

            return jump;
        }
    }
    return jump;
}

int gameOver(struct Player playerB, struct Player playerW)
{
    int over = FALSE;
    // if either player runs out of checkers gameOver returns TRUE
    if ((playerB.numCheckers == 0 || playerW.numCheckers == 0))
    {
        over = TRUE;

        return over;
    }
    return over;
}

void displayWinner(struct Player *playerB, struct Player *playerW)
{
    // if playerB runs out of checkers, playerW gets declared the winner
    if (playerB->numCheckers == 0)
    {
        printf("%s has won the game!\n", playerW->playerName);
        displayStats(*playerB);
        displayStats(*playerW);
    }
    // if playerW runs out of checkers, playerB gets declared the winner
    else if (playerW->numCheckers == 0)
    {
        printf("%s has won the game!", playerB->playerName);
        displayStats(*playerB);
        displayStats(*playerW);
    }
}

void setEndGame(struct Player *Player)
{
    // sets the given player's # of checkers to 0
    Player->numCheckers = 0;
}