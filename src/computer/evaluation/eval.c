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
  score += four_pattern(COMPUTER_ID);
  score += three_pattern(COMPUTER_ID);
  score += two_pattern(COMPUTER_ID);

  score -= four_pattern(HUMAN_ID);
  score -= three_pattern(HUMAN_ID);
  score -= two_pattern(HUMAN_ID);

  /* ... */

  return score;
}


int16_t 
manhattanCenterDistance(int16_t location) 
{
  int16_t col = location % BOARD_SIZE;
  int16_t row = location / BOARD_SIZE;

  /* Taxicab distance */
  int16_t distance = abs(col - (BOARD_SIZE / 2)) + abs(row - (BOARD_SIZE / 2));

  return BOARD_SIZE - distance;
}


void
predefine_importance_board()
{
  /* Calculate the manhattan distance to centre for each cell */
  for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    importance_board[i] = manhattanCenterDistance(i);
  }
}
