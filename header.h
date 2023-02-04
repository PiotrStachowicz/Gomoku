#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#define BOARD_LENGTH 15
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
extern int counter;
extern int valuable[BOARD_LENGTH][BOARD_LENGTH];
struct stan_gry{
    int board[BOARD_LENGTH][BOARD_LENGTH];
    int gracz;
    int ruch;
    bool koniec;
};
void print_stan_gry(struct stan_gry* stan);
void clear (void);
void move(struct stan_gry* state);
int check_winner(struct stan_gry* state);
int something(int board[BOARD_LENGTH][BOARD_LENGTH], int y, int x);
int _OOOlubOOO_(struct stan_gry* stan, int atak);
int OO_OO(struct stan_gry* stan, int atak);
int O_OOOlubOOO_O(struct stan_gry* stan, int atak);
int _O_OOlubOO_O_(struct stan_gry* stan, int atak);
int _OOO_(struct stan_gry* stan, int atak);
int _O_O_(struct stan_gry* stan, int atak);
int blockandattack(struct stan_gry* stan);
int evaluate(struct stan_gry* stan, int X);
int minimax(struct stan_gry* state, bool isMaximizingPlayer,int depth, int alpha, int beta);
void best_move(struct stan_gry* state);
int update(struct stan_gry* stan);
int patterns(struct stan_gry* stan);
