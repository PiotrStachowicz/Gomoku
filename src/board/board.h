#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "stdint.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define BOARD_SIZE 5
#define COMPUTER_ID 42
#define HUMAN_ID 1


/* 1D board */
static uint16_t board[BOARD_SIZE * BOARD_SIZE];

/* 
  Overview: Flattens 2D move into 1D 
  Arguments: row - row number, col - column number
  Returns: 1D index for board or -1 on error
*/
uint16_t
flatten (uint16_t row, uint16_t col);

/* 
  Overview: Sets board[row][col] to number x
  Arguments: row - row number, col - column number, x - player ID
  Returns: 0 on success, -1 on error
*/
uint16_t 
set (uint16_t row, uint16_t col, uint16_t x);

/* 
  Overview: Retrieves player ID from board[row][col]
  Arguments: row - row number, col - column number
  Returns: Player ID or -1 on error
*/
uint16_t
get (uint16_t row, uint16_t col);

/* 
  Overview: Erases board[row][col]
  Arguments: row - row number, col - column number
  Returns: Erased player ID or -1 on error
*/
uint16_t
erase (uint16_t row, uint16_t col);

/* 
  Overview: Pretty prints board to the shell
  Arguments: None
  Returns: Nothing
*/
void
show ();

#endif
