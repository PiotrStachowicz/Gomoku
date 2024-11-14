#include "eval.h"

int16_t importance_board[BOARD_SIZE * BOARD_SIZE];

int64_t
evaluate_board()
{
  int64_t score = 0;

  /* Position on board */
  for (int16_t i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    if (board[i] == HUMAN_ID)
    {
      score -= importance_board[i];
    }
    else if (board[i] == COMPUTER_ID)
    {
      score += importance_board[i];
    }
  }

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

int16_t 
manhattanCenterDistance(int16_t location) 
{
  int16_t col = location % BOARD_SIZE;
  int16_t row = location / BOARD_SIZE;

  // Taxicab distance
  int16_t distance = abs(col - (BOARD_SIZE / 2)) + abs(row - (BOARD_SIZE / 2));

  return BOARD_SIZE - distance;
}

void
predefine_importance_board()
{
  for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    importance_board[i] = manhattanCenterDistance(i);
  }
}
