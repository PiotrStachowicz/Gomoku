#include <stdio.h>
#define LENGTH 15
struct stan_gry{
    char board[LENGTH][LENGTH];
    int gracz;
    bool koniec;
};
void x_y_bot(struct stan_gry* state, int *x, int *y){
    *x = rand() % LENGTH;
    *y = rand() % LENGTH;
}
