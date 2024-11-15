#ifndef COMPUTER_HEADER
#define COMPUTER_HEADER

#include "../board/board.h"
#include "evaluation/eval.h"
#define RECCURENCE_LIMIT 4
#define MIN HUMAN_ID
#define MAX COMPUTER_ID

typedef struct 
{
  int16_t row;
  int16_t col;
  int64_t value;
} move;

/* Creates new move */
move 
new_move(int16_t row, int16_t col, int64_t score);

/* Minimax algortihm (slow) */
move
minimax(int16_t depth, int16_t player);

/* Alfa beta pruning (faster) */
move
alfa_beta(int16_t depth, int16_t player, int64_t alfa, int64_t beta);

#endif
