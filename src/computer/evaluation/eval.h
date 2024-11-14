#ifndef EVAL_HEADER
#define EVAL_HEADER

#include "patterns/patterns.h"
#include "math.h"

extern int16_t importance_board[BOARD_SIZE * BOARD_SIZE];

int64_t
evaluate_board();

void 
predefine_importance_board();

int16_t 
manhattanCenterDistance(int16_t location);

#endif
