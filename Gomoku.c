#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LENGTH 15
struct stan_gry{
    char board[LENGTH][LENGTH];
    int gracz;
    bool koniec;
};
int main(void){
    struct stan_gry stan = {.gracz = 1,.koniec = false};
    return 0;
}
