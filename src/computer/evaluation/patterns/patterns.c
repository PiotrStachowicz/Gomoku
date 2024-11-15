#include "patterns.h"

int64_t
four_pattern(int16_t player)
{
  int64_t score = 0;
  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
     /* Check whole row for win */
    for (int16_t col = 0; col + 5 < BOARD_SIZE; ++col)
    {
      if (get(row, col) == NOTHING && get(row, col + 1) == player && get(row, col + 2) == player &&
          get(row, col + 3) == player && get(row, col + 4) == player && get(row, col + 5) == NOTHING)
            score += OPEN_FOUR_SCORE;

      if (get(row, col) == player && get(row, col + 1) == player && get(row, col + 2) == NOTHING &&
          get(row, col + 3) == NOTHING && get(row, col + 4) == player && get(row, col + 5) == player)
            score += CLOSED_FOUR_SCORE;
    }
  }

  for (int16_t col = 0; col < BOARD_SIZE; ++col)
  {
    /* Check whole column for win */
    for (int16_t row = 0; row + 5 < BOARD_SIZE; ++row)
    {
      if (get(row, col) == NOTHING && get(row + 1, col) == player && get(row + 2, col) == player &&
          get(row + 3, col) == player && get(row + 4, col) == player && get(row + 5, col) == NOTHING)
            score += OPEN_FOUR_SCORE;
      
      if (get(row, col) == player && get(row + 1, col) == player && get(row + 2, col) == NOTHING &&
          get(row + 3, col) == NOTHING && get(row + 4, col) == player && get(row + 5, col) == player)
            score += CLOSED_FOUR_SCORE;      
    }
  }     

  /* Iterate over all first diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d) 
  {
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1 ;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1;

    for (int16_t i = start_row; i + 5 <= end_row; ++i)
    {
      int16_t j = BOARD_SIZE - (d - i) - 1;

      if (get(i, j) == NOTHING && get(i + 1, j + 1) == player && get(i + 2, j + 2) == player &&
          get(i + 3, j + 3) == player && get(i + 4, j + 4) == player && get(i + 5, j + 5) == NOTHING)
            score += OPEN_FOUR_SCORE;
      
      if (get(i, j) == player && get(i + 1, j + 1) == player && get(i + 2, j + 2) == NOTHING &&
          get(i + 3, j + 3) == NOTHING && get(i + 4, j + 4) == player && get(i + 5, j + 5) == player)
            score += CLOSED_FOUR_SCORE;  
    }
  }

  /* Iterate over all second diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d)
  {
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1; 

    for (int16_t i = start_row; i + 5 <= end_row; ++i)
    {
      int16_t j = d - i;

      if (get(i, j) == NOTHING && get(i + 1, j - 1) == player && get(i + 2, j - 2) == player &&
          get(i + 3, j - 3) == player && get(i + 4, j - 4) == player && get(i + 5, j - 5) == NOTHING)
            score += OPEN_FOUR_SCORE;

      if (get(i, j) == player && get(i + 1, j - 1) == player && get(i + 2, j - 2) == NOTHING &&
          get(i + 3, j - 3) == NOTHING && get(i + 4, j - 4) == player && get(i + 5, j - 5) == player)
            score += CLOSED_FOUR_SCORE;
    }
  }

  return 0;
}


int64_t
three_pattern(int16_t player)
{
  int64_t score = 0;
  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
     /* Check whole row for win */
    for (int16_t col = 0; col + 4 < BOARD_SIZE; ++col)
    {
      if (get(row, col) == NOTHING && get(row, col + 1) == player && get(row, col + 2) == player &&
          get(row, col + 3) == player && get(row, col + 4) == NOTHING)
            score += OPEN_THREE_SCORE;

      if (get(row, col) == player && get(row, col + 1) == player && get(row, col + 2) == NOTHING &&
          get(row, col + 3) == player && get(row, col + 4) == player)
            score += CLOSED_THREE_SCORE;
    }
  }

  for (int16_t col = 0; col < BOARD_SIZE; ++col)
  {
    /* Check whole column for win */
    for (int16_t row = 0; row + 4 < BOARD_SIZE; ++row)
    {
      if (get(row, col) == NOTHING && get(row + 1, col) == player && get(row + 2, col) == player &&
          get(row + 3, col) == player && get(row + 4, col) == NOTHING)
            score += OPEN_THREE_SCORE;
      
      if (get(row, col) == player && get(row + 1, col) == player && get(row + 2, col) == NOTHING &&
          get(row + 3, col) == player && get(row + 4, col) == player)
            score += CLOSED_THREE_SCORE;      
    }
  }     

  /* Iterate over all first diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d) 
  {
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1 ;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1;

    for (int16_t i = start_row; i + 4 <= end_row; ++i)
    {
      int16_t j = BOARD_SIZE - (d - i) - 1;

      if (get(i, j) == NOTHING && get(i + 1, j + 1) == player && get(i + 2, j + 2) == player &&
        get(i + 3, j + 3) == player && get(i + 4, j + 4) == NOTHING)
          score += OPEN_THREE_SCORE;
      
      if (get(i, j) == player && get(i + 1, j + 1) == player && get(i + 2, j + 2) == NOTHING &&
        get(i + 3, j + 3) == player && get(i + 4, j + 4) == player)
          score += CLOSED_THREE_SCORE;  
    }
  }

  /* Iterate over all second diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d)
  {
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1; 

    for (int16_t i = start_row; i + 4 <= end_row; ++i)
    {
      int16_t j = d - i;

      if (get(i, j) == NOTHING && get(i + 1, j - 1) == player && get(i + 2, j - 2) == player &&
          get(i + 3, j - 3) == player && get(i + 4, j - 4) == NOTHING)
            score += OPEN_THREE_SCORE;

      if (get(i, j) == player && get(i + 1, j - 1) == player && get(i + 2, j - 2) == NOTHING &&
          get(i + 3, j - 3) == player && get(i + 4, j - 4) == player)
            score += CLOSED_THREE_SCORE;
    }
  }

  return 0;
}


int64_t
two_pattern(int16_t player)
{
  int64_t score = 0;
  for (int16_t row = 0; row < BOARD_SIZE; ++row)
  {
     /* Check whole row for win */
    for (int16_t col = 0; col + 2 < BOARD_SIZE; ++col)
    {
      if (get(row, col) == player && get(row, col + 1) == player)
          score += TWO_IN_ROW_SCORE;
    }
  }

  for (int16_t col = 0; col < BOARD_SIZE; ++col)
  {
    /* Check whole column for win */
    for (int16_t row = 0; row + 2 < BOARD_SIZE; ++row)
    {
      if (get(row, col) == player && get(row + 1, col) == player)
          score += TWO_IN_ROW_SCORE;     
    }
  }     

  /* Iterate over all first diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d) 
  {
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1 ;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1;

    for (int16_t i = start_row; i + 2 <= end_row; ++i)
    {
      int16_t j = BOARD_SIZE - (d - i) - 1;

      if (get(i, j) == player && get(i + 1, j + 1) == player)
          score += TWO_IN_ROW_SCORE; 
    }
  }

  /* Iterate over all second diagonals and check for win */
  for (int16_t d = 0; d < BOARD_SIZE + BOARD_SIZE - 1; ++d)
  {
    int16_t start_row = d < BOARD_SIZE ? 0 : d - BOARD_SIZE + 1;
    int16_t end_row = d < BOARD_SIZE ? d : BOARD_SIZE - 1; 

    for (int16_t i = start_row; i + 2 <= end_row; ++i)
    {
      int16_t j = d - i;

      if (get(i, j) == player && get(i + 1, j - 1) == player)
            score += TWO_IN_ROW_SCORE;
    }
  }

  return 0;
}
