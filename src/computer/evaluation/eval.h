#ifndef EVAL_HEADER
#define EVAL_HEADER

#include "patterns/patterns.h"
#include "math.h"

extern int16_t importance_board[BOARD_SIZE * BOARD_SIZE];

/* Evaluate adhoc the current state of the board */
int64_t
evaluate_board();

/* Predefines the importance board */
void 
predefine_importance_board();

/* Function that returns taxicab distance from location to the centre */
int16_t 
manhattanCenterDistance(int16_t location);

#endif
