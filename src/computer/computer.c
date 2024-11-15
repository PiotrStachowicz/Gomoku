#include "computer.h"


move 
new_move(int16_t row, int16_t col, int64_t score)
{
  move result;
  result.row = row;
  result.col = col;
  result.value = score;

  return result;
}


move
minimax (int16_t depth, int16_t player)
{
  move best_move = new_move(-1, -1, player == MAX ? INT64_MIN : INT64_MAX);
  int16_t winner = check_win(player == HUMAN_ID ? COMPUTER_ID : HUMAN_ID);

  /* Check for end state */
  if (winner == HUMAN_ID)
  {
    return new_move(-1, -1, INT64_MIN + depth);
  }
  else if (winner == COMPUTER_ID)
  {
    return new_move(-1, -1, INT64_MAX - depth);
  }
  else if (winner == DRAW)
  {
    return new_move(-1, -1, 0);
  }

  /* Calculate score adhoc if limit reached */
  if (depth == RECCURENCE_LIMIT)
  {
    return new_move(-1, -1, evaluate_board());
  }

  /* Check all possible moves */
  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    for (int16_t col = 0; col < BOARD_SIZE; ++col)
    {
      /* Minimizing */
      if (player == MIN && is_empty(row, col))
      {
        set(row, col, HUMAN_ID);

        move rec_move = minimax(depth + 1, MAX);
        
        erase(row, col);

        if (rec_move.value < best_move.value) 
        {
          best_move = new_move(row, col, rec_move.value);
        }
      }
      /* Maximizing */
      else if (player == MAX && is_empty(row, col))
      {
        set(row, col, COMPUTER_ID);

        move rec_move = minimax(depth + 1, MIN);
        
        erase(row, col);


        if (rec_move.value > best_move.value) 
        {
          best_move = new_move(row, col, rec_move.value);
        }
      }
    }
  }
  
  return best_move;
}



