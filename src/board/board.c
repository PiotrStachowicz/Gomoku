#include "board.h"

uint16_t
flatten (uint16_t row, uint16_t col)
{
  uint16_t index = row * BOARD_SIZE + col;

  if (index >= BOARD_SIZE * BOARD_SIZE)
  {
    fprintf(stderr, "Illegal (row, col) tuple accessed!\n");
    return -1;
  }

  return index;
}

uint16_t
set (uint16_t row, uint16_t col, uint16_t x)
{
  uint16_t index = flatten(row, col);

  if (index != -1)
  {
    board[index] = x;
    
    return 0;
  }
  else
  {
    return -1;
  }
}

uint16_t
get (uint16_t row, uint16_t col)
{
  uint16_t index = flatten(row, col);

  if (index != -1)
  {
    return board[index];
  }

  return -1;
}

uint16_t
erase (uint16_t row, uint16_t col)
{
  uint16_t player_id = get(row, col);

  set(row, col, 0); /* This is safe, because set is safe */

  return player_id;
}

void
show ()
{
  for (uint16_t i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    printf(" %u ", board[i]);

    if (i % BOARD_SIZE == BOARD_SIZE - 1)
    {
      printf("\n");
    }
  }
}
