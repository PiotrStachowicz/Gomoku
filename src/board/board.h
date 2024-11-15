#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "stdint.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define BOARD_SIZE 7
#define COMPUTER_ID 42
#define HUMAN_ID 1
#define SUCCESS 1
#define NOTHING 0 
#define FAIL -1
#define WIN_CONDITION 5
#define DRAW -2

extern int16_t board[BOARD_SIZE * BOARD_SIZE];

/* Flattens 2D (row, col) access into 1D array */
int16_t
flatten (int16_t row, int16_t col);

/* Sets (row, col) cell to x */
int16_t 
set (int16_t row, int16_t col, int16_t x);

/* Returns value in (row, col) cell */
int16_t
get (int16_t row, int16_t col);

/* Sets (row, col) cell to 0 */
int16_t
erase (int16_t row, int16_t col);

/* Returns 1 if (row, col) cell is of value 0 */
int16_t
is_empty(int16_t row, int16_t col);

/* Clears terminal window */
void
sys_clear_terminal();

/* Prints the board for user */
void
show ();

/* Checks for win in row for given player ID */
int16_t
check_row (int16_t row, int16_t player);

/* Checks for win in column for given player ID */
int16_t
check_col (int16_t col, int16_t player);

/* Checks for win in first diagonals for given player ID */
int16_t 
check_diagonal_1 (int16_t player);

/* Checks for win in second diagonals for given player ID */
int16_t
check_diagonal_2 (int16_t player);

/* Check for the win for the given player ID */
int16_t 
check_win (int16_t player);

#endif
