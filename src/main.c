#include "board/board.h"
#include "computer/computer.h"
#include "computer/evaluation/eval.h"

int 
main(int argc, char* argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: ./gomoku [difficulty 1-2] [turn 0-1]\n");
    exit(EXIT_FAILURE);
  }

  /* Update game settings */
  int16_t difficulty = atoi(argv[1]);
  int16_t turn = atoi(argv[2]) == 1 ? COMPUTER_ID : (atoi(argv[2]) == 0 ? HUMAN_ID : FAIL);

  if (difficulty < 1 || difficulty > 10 || turn == FAIL)
  {
    fprintf(stderr, "Warning, wrong program arguments!\n");
    exit(EXIT_FAILURE);
  }

  /* Predefine the importance board for state evaluation */
  predefine_importance_board();

  /* Main loop of the game */
  while (1)
  {
    /* Check for end game state */
    if (check_win(HUMAN_ID) == HUMAN_ID || check_win(COMPUTER_ID) == COMPUTER_ID || check_win(DRAW) == DRAW)
    {
      fprintf(stdout, "GAME ENDED\n");
      break;
    }

    /* Computer's turn */
    if (turn == COMPUTER_ID)
    {
      move best_move;

      /*
      switch (difficulty)
      {
      case 1:
        best_move = minimax(0, MAX);
        break;
      case 2:
        best_move = alfa_beta(0, INT64_MIN, INT64_MAX, MAX);
        break;
      }
      */

      best_move = minimax(0, MAX);
      set(best_move.row, best_move.col, COMPUTER_ID);
      turn = HUMAN_ID;
    }

    /* Human's turn */
    else
    {

      /* Wait for good move */
      while (1)
      {
        int16_t row;
        int16_t col;

        do 
        {
          fprintf(stdout, "Make move <[row] [col]>: ");

        } while (scanf("%hd %hd", &row, &col) != 2);

        if (set(row, col, HUMAN_ID) != FAIL)
          break;
      }

      turn = COMPUTER_ID;
    }

    /* Print the board to the terminal */
    show();
  }

  exit(EXIT_SUCCESS);
}
