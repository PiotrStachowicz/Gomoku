#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dumb_Dummy.h"
int gracz;
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
        printf("\x1b[0m\n");putchar(' ');putchar(' ');putchar(' ');
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
        if(gracz==1){
            state->board[y-1][x-1] = 'X';
        }else{
            state->board[y-1][x-1] = 'O';
        }
        state->gracz=-1;
    }
    system("clear");
}
void move_bota(struct stan_gry* state){
    int cp = 0;
    int x, y;
    do{
        x_y_bot(state, &x,&y);
        if(x-1<15||y-1<15||y-1>0||x-1>0){
            cp = 1;
        }else if(state->board[y-1][x-1]==0){
            cp=1;
        }
    } while (cp!=1);
    if(state->gracz==-1){
        if(gracz==1){
            state->board[y-1][x-1] = 'O';
        }else{
            state->board[y-1][x-1] = 'X';
        }
        state->gracz=1;
    }
    system("clear");
}
int game_win(struct stan_gry* state){
    for(int y = 0;y<LENGTH;y++){
        int count = 1;
        for(int x = 0;x<LENGTH-1;x++){
            if(state->board[y][x]==state->board[y][x+1] && (state->board[y][x]=='X' || state->board[y][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                return 1;
            }
        }
    }
    for(int x = 0;x<LENGTH;x++){
        int count = 1;
        for(int y = 0;y<LENGTH-1;y++){
            if(state->board[y][x]==state->board[y+1][x] && (state->board[y][x]=='X' || state->board[y][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                return 1;
            }
        }
    }
    for(int y = 0;y<LENGTH;y++){
        int ky = y;
        int count = 1;
        int x = 0;
        while (ky!=0){
            if(state->board[ky][x]==state->board[ky-1][x+1] && (state->board[ky][x]=='X' || state->board[ky][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                return 1;
            }
            ky--;
            x++;
        }
    }
    for(int y = 0;y<LENGTH;y++){
        int ky = y;
        int count = 1;
        int x = LENGTH-1;
        while (ky!=0){
            if(state->board[ky][x]==state->board[ky-1][x-1] && (state->board[ky][x]=='X' || state->board[ky][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                return 1;
            }
            ky--;
            x--;
        }
    }
    return 0;
}
int main(void){
    struct stan_gry stan = {.koniec = false};
    print_stan_gry(&stan);
    char start[3];
    printf("Chciałbyś zacząć? <tak> <nie>: ");
    scanf("%s", start);
    if(start[0]=='t'&&start[1]=='a'&&start[2]=='k'){
        stan.gracz = 1;
        gracz = 1; // Zaczyna gracz i gracz ma (X)
    } else{
        stan.gracz = -1;
        gracz = -1; // Zaczyna bot i gracz  ma (O)
    }
    system("clear");
    while(stan.koniec!=true){
        print_stan_gry(&stan);
        move(&stan);
        move_bota(&stan);
        if(game_win(&stan)){
            stan.koniec = true;
            if(stan.gracz==gracz){
                printf("Wygrałeś z botem!\n");
            } else{
                printf("Przegrałeś z botem!\n");
            }
        }
    }
    print_stan_gry(&stan);
    return 0;
}
