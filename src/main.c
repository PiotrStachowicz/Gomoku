#include "board/board.h"
#include "computer/computer.h"
#include "computer/evaluation/eval.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/ioctl.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "time.h"

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

  if (difficulty < 1 || difficulty > 2 || turn == FAIL)
  {
    fprintf(stderr, "Warning, wrong program arguments!\n");
    exit(EXIT_FAILURE);
  }

  int sv[2]; 

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1)
  {
    perror("socketpair");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if (pid < 0)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  /* Parent: computational backend in C */
  if (pid) 
  {
    close(sv[1]);

    /* Predefine the importance board for state evaluation */
    predefine_importance_board();

    /* Clear pygame trash */
    char trash[1024];
    if (read(sv[0], trash, sizeof(trash)) == -1)
    {
      exit(EXIT_FAILURE);
    }

    /* Main loop of the game */
    while (1)
    {
      move best_move;

      /* Computer's move */
      if (turn == COMPUTER_ID)
      {
         /* Get move from different agents */
        switch (difficulty)
        {
        case 1:
          best_move = minimax(0, MAX);
          break;
        case 2:
          best_move = alfa_beta(0, MAX, INT64_MIN, INT64_MAX);
          break;

        default:
          best_move = minimax(0, MAX);
          break;
        }

        set(best_move.row, best_move.col, COMPUTER_ID);

        int send_buf[2] = {best_move.row, best_move.col};

        /* Send information to GUI */
        if (write(sv[0], send_buf, sizeof(send_buf)) != sizeof(send_buf))
        {
          perror("write");
          exit(EXIT_FAILURE);
        }

        /* Check for end game state */
        if (check_win(HUMAN_ID) == HUMAN_ID || check_win(COMPUTER_ID) == COMPUTER_ID || check_win(DRAW) == DRAW)
        {
          fprintf(stdout, "GAME ENDED\n");
          break;
        }

        turn = HUMAN_ID;
      }
      /* Human's turn */
      else
      {
        /* Wait for valid information from user */
        int get_buf[2];

        if (read(sv[0], get_buf, sizeof(get_buf)) != sizeof(get_buf))
        {
          perror("read");
          exit(EXIT_FAILURE);
        }

        if (set(get_buf[1], get_buf[0], HUMAN_ID) == FAIL)
        {
          exit(EXIT_FAILURE);
        }

        /* Check for end game state */
        if (check_win(HUMAN_ID) == HUMAN_ID || check_win(COMPUTER_ID) == COMPUTER_ID || check_win(DRAW) == DRAW)
        {
          fprintf(stdout, "GAME ENDED\n");
          break;
        }

        turn = COMPUTER_ID;
      }
    }
    /* Sleep for 5 seconds */
    sleep(5);
    close(sv[0]);
    
  }

  /* Child: GUI for user */
  else
  {
    close(sv[0]);

    if (dup2(sv[1], STDIN_FILENO) == -1 || dup2(sv[1], STDOUT_FILENO) == -1)
    {
      perror("dup2");
      exit(EXIT_FAILURE);
    }

    /* Run GUI */
    char board_size_str[4];
    snprintf(board_size_str, sizeof(board_size_str), "%d", BOARD_SIZE);
    char turn_str[4];
    snprintf(turn_str, sizeof(turn_str), "%d", turn);

    char* args[] = {"gui", "../gui/ui.py", board_size_str, turn_str, NULL};

    execlp("python3", args[0], args[1], args[2], args[3], args[4]);
    perror("execlp");
    exit(EXIT_FAILURE);
  }


  exit(EXIT_SUCCESS);
}
