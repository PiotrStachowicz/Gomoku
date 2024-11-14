#include "board/board.h"
#include "computer/computer.h"
#include "computer/evaluation/eval.h"

int 
main(int argc, char* argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: ./gomoku [difficulty 1-4] [turn 0-1]\n");
    exit(EXIT_FAILURE);
  }

  int16_t difficulty = atoi(argv[1]);
  int16_t turn = atoi(argv[2]) == 1 ? COMPUTER_ID : (atoi(argv[2]) == 0 ? HUMAN_ID : FAIL);

  if (difficulty < 1 || difficulty > 10 || turn == FAIL)
  {
    fprintf(stderr, "Warning, wrong program arguments!\n");
    exit(EXIT_FAILURE);
  }

  predefine_importance_board();

  while (1)
  {
    if (check_win(HUMAN_ID) == HUMAN_ID || check_win(COMPUTER_ID) == COMPUTER_ID || check_win(DRAW) == DRAW)
    {
      fprintf(stdout, "GAME ENDED\n");
      break;
    }

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
      case 3:
        best_move = fork_minimax(0, MAX);
        break;
      case 4:
        best_move = fork_alfa_beta(0, INT64_MIN, INT64_MAX, MAX);
        break;
      }
      */

      best_move = minimax(0, MAX);
      set(best_move.row, best_move.col, COMPUTER_ID);
      turn = HUMAN_ID;
    }
    else
    {

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

    show();
  }

  exit(EXIT_SUCCESS);
}
