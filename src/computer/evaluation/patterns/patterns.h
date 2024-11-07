#ifndef PATTERNS_HEADER
#define PATTERNS_HEADER

#include "stdint.h"
#include "../../../board/board.h"
#define OPEN_FOUR_SCORE 10000
#define CLOSED_FOUR_SCORE 5000
#define OPEN_THREE_SCORE 500
#define CLOSED_THREE_SCORE 100
#define TWO_IN_ROW_SCORE 10

int64_t
open_four(int16_t player);

int64_t
closed_four(int16_t player);

int64_t
open_three(int16_t player);

int64_t
closed_three(int16_t player);

int64_t
two_in_row(int16_t player);

#endif
