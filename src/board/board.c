#include "board.h"


int16_t board[BOARD_SIZE * BOARD_SIZE];


int16_t
flatten (int16_t row, int16_t col)
{
  int16_t index = row * BOARD_SIZE + col;

  /* Check for illegal access */
  if (index >= BOARD_SIZE * BOARD_SIZE || index < 0)
  {
    fprintf(stderr, "flatten error\n");
    return FAIL;
  }

  return index;
}


int16_t
set (int16_t row, int16_t col, int16_t x)
{
  int16_t index = flatten(row, col);

  /* Check if we can access this cell */
  if (x == 0 || (index != FAIL && is_empty(row, col)))
  {
    board[index] = x;
    
    return 0;
  }
  else
  {
    fprintf(stderr, "set error\n");
    return FAIL;
  }
}


int16_t
get (int16_t row, int16_t col)
{
  int16_t index = flatten(row, col);

  /* Check for illegal access */
  if (index != FAIL)
  {
    return board[index];
  }

  fprintf(stderr, "get error\n");
  return FAIL;
}


int16_t
erase (int16_t row, int16_t col)
{
  int16_t player_id = get(row, col);

  /* Set cell to nothing */
  set(row, col, NOTHING);

  return player_id;
}


int16_t
is_empty(int16_t row, int16_t col) 
{
  /* Check if cell is empty */
  if (get(row, col) == NOTHING)
  {
    return 1;
  }

  return 0;
}


void
sys_clear_terminal()
{
  /* Write escape sequence into the buffer and force it to kernel's buffer */
  fprintf(stdout, "\033c");
  fflush(stdout);
}


void
show ()
{
  sys_clear_terminal();
  
  /* Iterate over cells and print them to terminal */
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
      else if (element == NOTHING)
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

  /* Check whole row for win */
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

  /* Check whole column for win */
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
check_diagonal_1(int16_t player)
{
  /* Iterate over all diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d)
  {
    int16_t counter = 0;
    int16_t start_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1;
    int16_t end_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1; 
    int16_t col = d < BOARD_SIZE ? BOARD_SIZE - 1 : BOARD_SIZE + (BOARD_SIZE - d - 2);

    for (int16_t i = start_row; i >= end_row; --i, --col)
    {
      if (get(i, col) == player)
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
check_diagonal_2(int16_t player)
{
  /* Iterate over all diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d)
  {
    int16_t counter = 0;
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1; 

    for (int16_t i = start_row; i <= end_row; ++i)
    {
      int16_t j = d - i;

      if (get(i, j) == player)
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
  /* Check all rows for win */
  for (int16_t col = 0; col < BOARD_SIZE; ++col)
  {
    if(check_row(col, player) == player)
    {
      return player;
    }
  }

  /* Check all columns for win */
  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
    if (check_col(row, player) == player)
    {
      return player;
    }
  }

  /* Check fisrt diagonals for win */
  if (check_diagonal_1(player) == player)
  {
    return player;
  }

  /* Check second diagonals for win */
  if (check_diagonal_2(player) == player)
  {
    return player;
  }

  /* Check for draw */
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
