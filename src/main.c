#include "board/board.h"
#include "computer/computer.h"


int 
main(int argc, char* argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Try: ./gomoku <difficulty: 1-4> <turn: 0/1>\n");
    exit(EXIT_FAILURE);
  }

  int16_t difficulty = atoi(argv[1]);
  int16_t turn = atoi(argv[2]) == 1 ? COMPUTER_ID : HUMAN_ID;

  if (difficulty < 1 || difficulty > 10)
  {
    fprintf(stderr, "Warning: 1 <= <difficulty> <= 4\n");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    if (check_win(HUMAN_ID) == HUMAN_ID || check_win(COMPUTER_ID) == COMPUTER_ID)
    {
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

      if (best_move.row == -1 && best_move.col == -1)
      {
        fprintf(stderr, "Unexpected error while searching for computer move!\n");
        exit(EXIT_FAILURE);
      }
      else
      {
        int16_t status = set(best_move.row, best_move.col, COMPUTER_ID);

        if (status == -1)
        {
          fprintf(stderr, "Unexpected error while performing computer move!\n");
          exit(EXIT_FAILURE);
        }
      }

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
          printf("Make move <[row] [col]>: ");

        } while (scanf("%hd %hd", &row, &col) != 2);

        int16_t status = set(row, col, HUMAN_ID);

        if (status != -1)
        {
          break;
        }
      }

      turn = COMPUTER_ID;
    }

    show();
  }

  exit(EXIT_SUCCESS);
}
