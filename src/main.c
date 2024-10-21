#include "board/board.h"
#include "computer/computer.h"

int 
main(int argc, char* argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Try: ./gomoku <difficulty: 1-4> <turn: 0/1>\n");
  }

  uint16_t difficulty = atoi(argv[1]);
  uint16_t turn = atoi(argv[2]) == 1 ? COMPUTER_ID : HUMAN_ID;

  if (BOARD_SIZE < 1 || BOARD_SIZE > 10)
  {
    fprintf(stderr, "Warning: 1 <= <difficulty> <= 4\n");
  }

  /* Main loop of the game */
  while (1)
  {
    /* Computer's turn */
    if (turn == COMPUTER_ID)
    {
      move best_move;

      while (1)
      {
      
      /* Play according to the difficulty */
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

      /* Something bad happened */
      if (best_move.row == -1 && best_move.col == -1)
      {
        fprintf(stderr, "Unexpected error while searching for computer move!\n");
      }

      /* Success! Make the move and go on! */
      else
      {
        uint16_t status = set(best_move.row, best_move.col, COMPUTER_ID);

        /* Unexpected error */
        if (status == -1)
        {
          fprintf(stderr, "Unexpected error while performing computer move!\n");
        }
        else
        {
          break;
        }
      }
      }

      turn = HUMAN_ID;
    }

    /* Human's turn */
    else
    {

      while (1)
      {
        uint16_t row;
        uint16_t col;

        /* Ask for play */
        do 
        {
          printf("Make move <[row] [col]>: ");

        } while (scanf("%u %u", &row, &col) != 2);

        uint16_t status = set(row, col, HUMAN_ID);

        /* If there was a legal move, go on! */
        if (status != -1)
        {
          break;
        }
      }

      turn = COMPUTER_ID;
    }

    /* Print the board state */
    show();

  }

  return 0;
}
