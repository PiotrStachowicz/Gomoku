#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dumb_Dummy.h"
#define LENGTH 15
struct stan_gry{
    char board[LENGTH][LENGTH];
    int gracz; // 1-X 2-O
    bool koniec;
};
void print_stan_gry(struct stan_gry* stan){
    putchar(' '), putchar(' '), putchar(' ');
    for(int i = 1;i<=LENGTH;i++){
        if(i>=10){
            printf(" %d ",i);
        } else{
            printf("  %d ",i);
        }
    }
    putchar('\n'), putchar(' '), putchar(' '), putchar(' ');
    for(int i = 0;i<LENGTH*4+1;i++){
        printf("\x1b[44m-\x1b[0m");
    }
    putchar('\n');
    for(int y = 0;y<LENGTH;y++){
        if(y>8){
            printf("%d ", y+1);
        }else{
            printf("%d  ", y+1);
        }
        printf("\x1b[44m|\x1b[0m");
        for(int x = 0;x<LENGTH;x++){
            if(stan->board[y][x]!=0){
                printf("\x1b[44m\x1b[92m %c \x1b[0m", stan->board[y][x]);
                printf("\x1b[44m|\x1b[0m");
            } else{
                printf("\x1b[44m   \x1b[0m");
                printf("\x1b[44m|\x1b[0m");
            }
        }
        putchar('\n');putchar(' ');putchar(' ');putchar(' ');
        for(int i = 0;i<LENGTH*4+1;i++){
            printf("\x1b[44m-\x1b[0m");
        }
        putchar('\n');
    }
}
void move(struct stan_gry* state){
    int x, y;
    int cp = 0;
    do{
        printf("Podaj ruch <kolumna> <wiersz>: ");
        if(scanf("%d %d", &x, &y)!=2){
            printf("\x1b[31mBłędne dane, spróbuj ponownie.\x1b[0m\n");
        }else if(x-1>15||y-1>15||y-1<0||x-1<0){
            printf("\x1b[31mTakie pole nie istnieje, spróbuj ponownie.\x1b[0m\n");
        }else if(state->board[y-1][x-1]!=0){
            printf("\x1b[31mPole %d %d jest już zajęte, spróbuj ponownie.\x1b[0m\n",x,y);
        } else{
            cp = 1;
        }
    } while (cp!=1);
    if(state->gracz==1){
        state->board[y-1][x-1] = 'X';
        state->gracz=-1;
    } else{
        state->board[y-1][x-1] = 'O';
        state->gracz=1;
    }
    system("clear");
}
int main(void){
    struct stan_gry stan = {.gracz = 1,.koniec = false};
    while(stan.koniec!=1){
        print_stan_gry(&stan);
        move(&stan);
    }
    return 0;
}
