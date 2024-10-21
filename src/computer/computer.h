#ifndef COMPUTER_HEADER
#define COMPUTER_HEADER

#include "evaluation/eval.h"
#include "../board/board.h"
#define RECCURENCE_LIMIT 5
#define MIN 0
#define MAX 1

/* 2D move */
typedef struct 
{
  uint16_t row;
  uint16_t col;
  uint64_t value;

} move;

/*
  Overview: Move constructor
  Arguments: row/col - row/column of move, score - evaluation value
  Returns: Move struct
*/
move 
new_move(uint16_t row, uint16_t col, uint64_t score)
{
  move result;
  result.row = row;
  result.col = col;
  result.value = score;
}

/* 
  Overview: Minimax Algorithm 
  Arguments: depth - current depth of recursion, player - MIN/MAX
  Returns: Best computer move (row, col) or (-1, -1) on error
*/
move
minimax (uint16_t depth, uint16_t player);

/* 
  Overview: Minimax Algorithm with Alfa & Beta Prunning
  Arguments: depth - current depth of recursion, alfa/beta - current constraints, player - MIN/MAX
  Returns: Best computer move (row, col) or (-1, -1) on error
*/
move
alfa_beta (uint16_t depth, uint16_t player, uint64_t alfa, uint64_t beta);

/* 
  Overview: Fork version of Minimax Algorithm 
  Arguments: depth - current depth of recursion, player - MIN/MAX
  Returns: Best computer move (row, col) or (-1, -1) on error
*/
move
fork_minimax (uint16_t depth, uint16_t player);

/* 
  Overview: Fork version of Minimax Algorithm with Alfa & Beta Prunning
  Arguments: depth - current depth of recursion, alfa/beta - current constraints, player - MIN/MAX
  Returns: Best computer move (row, col) or (-1, -1) on error
*/
move
fork_alfa_beta (uint16_t depth, uint16_t player, uint64_t alfa, uint64_t beta);

#endif
