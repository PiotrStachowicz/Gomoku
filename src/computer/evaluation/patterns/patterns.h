#ifndef PATTERNS_HEADER
#define PATTERNS_HEADER

#include "stdint.h"
#include "../../../board/board.h"
#define OPEN_FOUR_SCORE 10000
#define CLOSED_FOUR_SCORE 5000
#define OPEN_THREE_SCORE 500
#define CLOSED_THREE_SCORE 100
#define TWO_IN_ROW_SCORE 10

/* Checks if given player has some four pattern */
int64_t
four_pattern(int16_t player);

/* Checks if given player has open three pattern */
int64_t
three_pattern(int16_t player);

/* Checks if given player has two in row pattern */
int64_t
two_pattern(int16_t player);

#endif
