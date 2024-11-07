#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "stdint.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define BOARD_SIZE 4
#define COMPUTER_ID 42
#define HUMAN_ID 1
#define FAIL -1
#define WIN_CONDITION 3
#define DRAW -2


extern int16_t board[BOARD_SIZE * BOARD_SIZE];

int16_t
flatten (int16_t row, int16_t col);

int16_t 
set (int16_t row, int16_t col, int16_t x);

int16_t
get (int16_t row, int16_t col);

int16_t
erase (int16_t row, int16_t col);

int16_t
is_empty(int16_t row, int16_t col);

void
show ();

int16_t
check_row (int16_t row, int16_t player);

int16_t
check_col (int16_t col, int16_t player);

int16_t 
check_diagonal_1 (int16_t row, int16_t col, int16_t player);

int16_t
check_diagonal_2 (int16_t player);

int16_t 
check_win (int16_t player);

#endif
