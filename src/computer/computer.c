#include "computer.h"
#include "evaluation/eval.h"

move
minimax (uint16_t depth, uint16_t player)
{
  move best_move = new_move(-1, -1, player == MAX ? 0 : UINT64_MAX);

  if (depth == RECCURENCE_LIMIT)
  {
    uint64_t score = eval(player);

    return new_move(-1, -1, score);
  }

  for (uint16_t row = 0; row < BOARD_SIZE; ++row)
  {
    for (uint16_t col = 0; col < BOARD_SIZE; ++col)
    {
      if (player == MIN)
      {
        set(row, col, HUMAN_ID);

        move rec_move = minimax(depth + 1, MAX);
        
        erase(row, col);

        if (rec_move.value < best_move.value) 
        {
          best_move = new_move(row, col, rec_move.value);
        }
      }
      else
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
}



