#include "eval.h"

int64_t
evaluate_board()
{
  int64_t score = 0;

  /* Position on board */
  

  /* Patterns score */
  score += open_four(COMPUTER_ID) * OPEN_FOUR_SCORE;
  score += closed_four(COMPUTER_ID) * CLOSED_FOUR_SCORE;
  score += open_three(COMPUTER_ID) * OPEN_THREE_SCORE;
  score += closed_three(COMPUTER_ID) * CLOSED_THREE_SCORE;
  score += two_in_row(COMPUTER_ID) * TWO_IN_ROW_SCORE;

  score -= open_four(HUMAN_ID) * OPEN_FOUR_SCORE;
  score -= closed_four(HUMAN_ID) * CLOSED_FOUR_SCORE;
  score -= open_three(HUMAN_ID) * OPEN_THREE_SCORE;
  score -= closed_three(HUMAN_ID) * CLOSED_THREE_SCORE;
  score -= two_in_row(HUMAN_ID) * TWO_IN_ROW_SCORE;

  /* ... */

  return score;
}

