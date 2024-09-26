// Leo Salazar
// 8/1/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// global constants a.k.a. macros
#define NAME 20
#define PLAYER_B 1
#define PLAYER_W 2
#define ZERO 0
#define FOUR 4
#define ROW 8
#define COL 8
#define ONE 1
#define TWO 2
#define THREE 3
#define TWELVE 12
#define SPACE ' '
#define TRUE 1
#define FALSE 0
#define INVALID -1

struct Player
{
    int playerNum;
    char playerName[NAME];
    int numCheckers;
    char playChar;
};

// function prototypes
void welcomeScreen ();
void displayExplicitBoard();
void clearScreen();
void playGame();
void initializeBoard(char board[ROW][COL]);
void displayBoard(char board[ROW][COL]);
void makeMove(struct Player *player, char board[ROW][COL]);
int isValid(char start[THREE], char end[THREE], char board[ROW][COL], char playerChar);
int getMoveRow(char move[THREE]);
int getMoveCol(char move[THREE]);
int isOpen(char end[THREE], char board[ROW][COL]);
void displayStats(struct Player player);
int hasChecker(char start[THREE], char board[ROW][COL], char playerChar);
int isDiagonal(char start[THREE], char end[THREE], char playerChar, char board[ROW][COL]);
void updateBoard(char start[THREE], char end[THREE], char board[ROW][COL]);
void updateCheckerCount(char board[ROW][COL], struct Player *player);
int isJump(int sRow, int sCol, int eRow, int eCol, char board[ROW][COL], char playerChar);
int gameOver(struct Player Player, struct Player Player2);
void setEndGame(struct Player *Player);
void displayWinner(struct Player *playerB, struct Player *playerW);