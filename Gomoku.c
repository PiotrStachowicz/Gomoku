#include "header.h"
int counter;
int valuable[BOARD_LENGTH][BOARD_LENGTH];
int main(void){
    srand(time(0));
    for(int i = 0; i < BOARD_LENGTH; i++){
        for(int j = 0; j < BOARD_LENGTH; j++){
            valuable[i][j] = 0;
        }
    }
    if(system("clear")==-1) printf("error\n");
    struct stan_gry stan = {.koniec = false, .gracz=2, .ruch=1};
    print_stan_gry(&stan);
    while(stan.koniec!=true){
        if(stan.gracz == 2 && stan.ruch == 1){
            int x1,y1;
            x1 = 10 - (rand() % 6);
            y1 =  10 - (rand() % 6);
            stan.board[y1][x1] = 'X';
            valuable[y1][x1] = 1;
            stan.gracz = 1;
            stan.ruch += 1;
        } else if(stan.gracz==1){
            move(&stan);
        }else{
            best_move(&stan);
        }
       update(&stan);
    }
    return 0;
}
