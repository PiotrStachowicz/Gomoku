#include "board.h"
#include "../sys/sysfun.h"

int16_t board[BOARD_SIZE * BOARD_SIZE];

int16_t
flatten (int16_t row, int16_t col)
{
  int16_t index = row * BOARD_SIZE + col;

  if (index >= BOARD_SIZE * BOARD_SIZE || index < 0)
  {
    fprintf(stderr, "Illegal (row, col) tuple accessed!\n");
    return FAIL;
  }

  return index;
}

int16_t
set (int16_t row, int16_t col, int16_t x)
{
  int16_t index = flatten(row, col);

  if (x == 0 || (index != FAIL && get(row, col) == 0))
  {
    board[index] = x;
    
    return 0;
  }
  else
  {
    return FAIL;
  }
}

int16_t
get (int16_t row, int16_t col)
{
  int16_t index = flatten(row, col);

  if (index != FAIL)
  {
    return board[index];
  }

  return FAIL;
}

int16_t
erase (int16_t row, int16_t col)
{
  int16_t player_id = get(row, col);

  set(row, col, 0); /* This is safe, because set is safe */

  return player_id;
}

int16_t
is_empty(int16_t row, int16_t col) 
{
  if (get(row, col) == 0)
  {
    return 1;
  }

  return 0;
}

void
show ()
{
  sys_clear_terminal();
  
  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    for (int16_t col = 0; col < BOARD_SIZE; ++col)
    {
      int16_t element = get(row, col);

      if (element == HUMAN_ID)
      {
        printf(" O ");
      }
      else if (element == COMPUTER_ID)
      {
        printf(" X ");
      }
      else 
      {
        printf(" . ");
      }

      if (col < BOARD_SIZE - 1) {
        printf("|");
      }
    }
    
    printf("\n");

    if (row < BOARD_SIZE - 1) {
      for (int col = 0; col < BOARD_SIZE; ++col) {
        printf("---");
        if (col < BOARD_SIZE - 1) {
          printf("+");
        }
      }
      printf("\n");
    }
  }
}

int16_t
check_row (int16_t row, int16_t player) 
{
  int16_t counter = 0;

  for (int16_t col = 0; col < BOARD_SIZE; ++col)
  {
    if (get(row, col) == player)
    {
      counter++;

      if (counter == WIN_CONDITION)
      {
        return player;
      }
    }
    else
    {
      counter = 0;
    }
  }

  return FAIL;
}

int16_t
check_col (int16_t col, int16_t player) 
{
  int16_t counter = 0;

  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    if (get(row, col) == player)
    {
      counter++;

      if (counter == WIN_CONDITION)
      {
        return player;
      }
    }
    else
    {
      counter = 0;
    }
  }

  return FAIL;
}

int16_t 
check_diagonal_1(int16_t row, int16_t col, int16_t player)
{
  int16_t counter = 0;
  int16_t start_row = row > col ? row - col : 0;
  int16_t start_col = col > row ? col - row : 0;

  for (; start_row < BOARD_SIZE && start_col < BOARD_SIZE; ++start_row, ++start_col)
  {
    if (get(start_row, start_col) == player)
    {
      counter++;
      if (counter == WIN_CONDITION)
      {
        return player;
      }
    }
    else
    {
      counter = 0;
    }
  }

  return FAIL;
}

int16_t
check_diagonal_2 (int16_t player)
{
  int16_t counter = 0;

  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    int16_t row_copy = row;
    counter = 0;

    for (int16_t col = 0; row_copy >= 0 ; ++col, --row_copy)
    {
      if (get(row_copy, col) == player)
      {
        counter++;
        if (counter == WIN_CONDITION)
        {
          return player;
        }
      }
      else
      {
        counter = 0;
      }
    }
  }
  
  counter = 0;

  for (int16_t col = 1; col < BOARD_SIZE; ++col)
  {
    int16_t col_copy = col;
    counter = 0;
    
    for (int16_t row = BOARD_SIZE - col; row >=0; --row, ++col_copy)
    {
      if (get(row, col_copy) == player)
      {
        counter++;
        if (counter == WIN_CONDITION)
        {
          return player;
        }
      }
      else
      {
        counter = 0;
      }
    }
  }

  return FAIL;
}

int16_t 
check_win (int16_t player)
{
  for (int16_t col = 0; col < BOARD_SIZE; ++col)
  {
    if(check_row(col, player) == player)
    {
      return player;
    }
  }

  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    if (check_col(row, player) == player)
    {
      return player;
    }
  }

  for (int16_t i = 0; i < BOARD_SIZE; ++i)
  {
    if (check_diagonal_1(i, i, player) == player)
    {
      return player;
    }
  }

  if (check_diagonal_2(player) == player)
  {
    return player;
  }

  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    for (int16_t col = 0; col < BOARD_SIZE; ++col)
    {
      if (is_empty(row, col))
      {
        return FAIL;
      }
    }
  }

  return DRAW;
}
