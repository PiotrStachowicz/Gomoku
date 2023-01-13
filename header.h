#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#define BOARD_LENGHT 15
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
int counter;
int valuable[BOARD_LENGHT][BOARD_LENGHT];
struct stan_gry{
    int board[BOARD_LENGHT][BOARD_LENGHT];
    int gracz;
    int ruch;
    bool koniec;
};
void print_stan_gry(struct stan_gry* stan){
    printf("\n\x1b[92m\n"
           " ________  ________  _____ ______   ________  ___  __    ___  ___     \n"
           "|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\   __  \\|\\  \\|\\  \\ |\\  \\|\\  \\    \n"
           "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\\\\\  \\   \n"
           " \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\\\\\  \\ \\   ___  \\ \\  \\\\\\  \\  \n"
           "  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
           "   \\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
           "    \\|_______|\\|_______|\\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|\n"
           "                                                                      \n");
    printf("   ");
    for(int i = 0; i < BOARD_LENGHT * 4 + 1; i++){
        if(i%4==0) printf("\x1b[92m+\x1b[0m");
        else printf("\x1b[92m-\x1b[0m");
    }
    putchar('\n');
    for(int y = 0; y < BOARD_LENGHT; y++){
        if(y>8){
            printf("\x1b[96m%d \x1b[0m", y+1);
        }else{
            printf("\x1b[96m%d  \x1b[0m", y+1);
        }
        printf("\x1b[92m|\x1b[0m");
        for(int x = 0; x < BOARD_LENGHT; x++){
            if(stan->board[y][x]!=0){
                if(stan->board[y][x]=='X') printf("\x1b[95m %c\x1b[92m |\x1b[0m", stan->board[y][x]);
                if(stan->board[y][x]=='O') printf("\x1b[93m %c\x1b[92m |\x1b[0m", stan->board[y][x]);
            } else{
                printf("\x1b[92m   |\x1b[0m");
            }
        }
        printf("\n   ");
        for(int i = 0; i < BOARD_LENGHT * 4 + 1; i++){
            if(i%4==0) printf("\x1b[92m+");
            else printf("\x1b[92m-");
        }
        putchar('\n');
    }
    printf("   ");
    for(int i = 1; i <= BOARD_LENGHT; i++){
        if(i>9){
            printf("\x1b[96m %d \x1b[0m", i);
        } else{
            printf("\x1b[96m  %d \x1b[0m", i);
        }
    }
    putchar('\n');
}
void clear (void)
{
    while ( getchar() != '\n' );
}
void move(struct stan_gry* state){
    int x, y;
    do {
        printf("\x1b[92mRuch: <kolumna> <wiersz>:\x1b[0m ");
        if (scanf(" %d %d", &x, &y) == 2 && x >= 1 && y >= 1 && x <= BOARD_LENGHT && y <= BOARD_LENGHT && state->board[y-1][x-1] == 0) {
            break;
        }
        clear();
    } while (true);
    state->board[y-1][x-1] = 'O';
    valuable[y-1][x-1] = 1;
    state->ruch += 1;
    state->gracz = -1;
    system("clear");
}
int check_winner(struct stan_gry* state){
    for(int y = 0; y < BOARD_LENGHT; y++){
        int count = 1;
        for(int x = 0; x < BOARD_LENGHT - 1; x++){
            if(state->board[y][x]==state->board[y][x+1] && (state->board[y][x]=='X' || state->board[y][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                if(state->board[y][x]=='X') return 1;
                if(state->board[y][x]=='O') return 2;
            }
        }
    }//wiersze
    for(int x = 0; x < BOARD_LENGHT; x++){
        int count = 1;
        for(int y = 0; y < BOARD_LENGHT - 1; y++){
            if(state->board[y][x]==state->board[y+1][x] && (state->board[y][x]=='X' || state->board[y][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                if(state->board[y][x]=='X') return 1;
                if(state->board[y][x]=='O') return 2;
            }
        }
    }//kolumny
    for(int y = 0 ;y < BOARD_LENGHT;y++){
        int x = 0;
        int ky = y;
        int count = 1;
        while (ky!=0){
            if(state->board[ky][x]==state->board[ky-1][x+1] && (state->board[ky][x]=='X' || state->board[ky][x]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                if(state->board[ky][x]=='X') return 1;
                if(state->board[ky][x]=='O') return 2;
            }
            x++;
            ky--;
        }
    }
    for(int x = 0 ;x < BOARD_LENGHT;x++){
        int y = BOARD_LENGHT-1;
        int kx = x;
        int count = 1;
        while (kx!=BOARD_LENGHT-1){
            if(state->board[y][kx]==state->board[y-1][kx+1] && (state->board[y][kx]=='X' || state->board[y][kx]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                if(state->board[y][kx]=='X') return 1;
                if(state->board[y][kx]=='O') return 2;
            }
            kx++;
            y--;
        }
    }//lewy dolny do prawy górny
    for(int x = 0 ;x < BOARD_LENGHT;x++){
        int y = BOARD_LENGHT-1;
        int kx = x;
        int count = 1;
        while (kx!=0){
            if(state->board[y][kx]==state->board[y-1][kx-1] && (state->board[y][kx]=='X' || state->board[y][kx]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                if(state->board[y][kx]=='X') return 1;
                if(state->board[y][kx]=='O') return 2;
            }
            kx--;
            y--;
        }
    }
    for(int x = 0 ;x < BOARD_LENGHT;x++){
        int y = 0;
        int kx = x;
        int count = 1;
        while (kx!=BOARD_LENGHT-1){
            if(state->board[y][kx]==state->board[y+1][kx+1] && (state->board[y][kx]=='X' || state->board[y][kx]=='O')){
                count++;
            } else{
                count = 1;
            }
            if(count==5){
                if(state->board[y][kx]=='X') return 1;
                if(state->board[y][kx]=='O') return 2;
            }
            kx++;
            y++;
        }
    }//prawy dolny do lewy górny
    int draw = 0;
    for(int i = 0;i<BOARD_LENGHT;i++){
        for(int j = 0;j<BOARD_LENGHT;j++){
            if(state->board[i][j]!=0){
                draw++;
            }
        }
    }
    if(draw == BOARD_LENGHT*BOARD_LENGHT){
        return -1;
    }//remis
    return 0;
}
int something(int board[BOARD_LENGHT][BOARD_LENGHT], int y, int x){
    if(x>0){
        if(board[y][x-1]!=0){
            return 1;
        }
    }//lewo
    if(x<BOARD_LENGHT-1){
        if(board[y][x+1]!=0){
            return 1;
        }
    }//prawo
    if(y<BOARD_LENGHT-1){
        if(board[y+1][x]!=0){
            return 1;
        }
    }//dół
    if(y>0){
        if(board[y-1][x]!=0){
            return 1;
        }
    }//góra
    if(x>0&&y>0){
        if(board[y-1][x-1]!=0){
            return 1;
        }
    }//lewy górny
    if(x<BOARD_LENGHT-1&&y<BOARD_LENGHT-1){
        if(board[y+1][x+1]!=0){
            return 1;
        }
    }//prawy dolny
    if(x>0&&y<BOARD_LENGHT-1){
        if(board[y+1][x-1]!=0){
            return 1;
        }
    }//lewy dolny
    if(x<BOARD_LENGHT-1&&y>0){
        if(board[y-1][x+1]!=0){
            return 1;
        }
    }//prawy górny
    return 0;
}
int _OOOlubOOO_(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y][x + 1] == szukana && stan->board[y][x + 2] == szukana) {
                if (x > 0 && stan->board[y][x - 1] == 0) {
                    stan->board[y][x - 1] = 'X';
                    valuable[y][x-1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
                if (x < BOARD_LENGHT - 3 && stan->board[y][x + 3] == 0) {
                    stan->board[y][x + 3] = 'X';
                    valuable[y][x+1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == szukana) {
                if (y > 0 && stan->board[y - 1][x] == 0) {
                    stan->board[y - 1][x] = 'X';
                    valuable[y-1][x] = 1;
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && stan->board[y + 3][x] == 0) {
                    stan->board[y + 3][x] = 'X';
                    valuable[y+3][x] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == szukana && stan->board[y + 2][x + 2] == szukana) {
                if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0) {
                    stan->board[y - 1][x - 1] = 'X';
                    valuable[y-1][x-1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && x < BOARD_LENGHT - 3 && stan->board[y + 3][x + 3] == 0) {
                    stan->board[y + 3][x + 3] = 'X';
                    valuable[y+3][x+3] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == szukana && stan->board[y + 2][x - 2] == szukana) {
                if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == 0) {
                    stan->board[y - 1][x + 1] = 'X';
                    valuable[y-1][x+1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && x > 1 && stan->board[y + 3][x - 3] == 0) {
                    stan->board[y + 3][x - 3] = 'X';
                    valuable[y+3][x-3] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}
int OO_OO(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana) {
                if (x > 0 && stan->board[y][x - 1] == szukana && stan->board[y][x + 3] == szukana) {
                    stan->board[y][x + 1] = 'X';
                    valuable[y][x+1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x] == 0 && stan->board[y + 2][x] == szukana) {
                if (y > 0 && stan->board[y - 1][x] == szukana && stan->board[y + 3][x] == szukana) {
                    stan->board[y + 1][x] = 'X';
                    valuable[y+1][x] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana) {
                if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == szukana && stan->board[y + 3][x + 3] == szukana) {
                    stan->board[y + 1][x + 1] = 'X';
                    valuable[y+1][x+1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana) {
                if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == szukana && stan->board[y + 3][x - 3] == szukana) {
                    stan->board[y + 1][x - 1] = 'X';
                    valuable[y+1][x-1] = 1;
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}
int O_OOOlubOOO_O(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (x > 0 && stan->board[y][x - 1] == szukana && stan->board[y][x] == 0 && stan->board[y][x + 1] == szukana && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == szukana) {
                stan->board[y][x] = 'X';
                valuable[y][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (y > 0 && stan->board[y - 1][x] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == 0 && stan->board[y + 3][x] == szukana) {
                stan->board[y + 2][x] = 'X';
                valuable[y+2][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == szukana && stan->board[y][x] == 0 && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == szukana) {
                stan->board[y][x] = 'X';
                valuable[y][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == szukana && stan->board[y + 2][x - 2] == 0 && stan->board[y + 3][x - 3] == szukana) {
                stan->board[y + 2][x - 2] = 'X';
                valuable[y+2][x-2] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    return 0;
}
int _O_OOlubOO_O_(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (x > 0 && stan->board[y][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == szukana) {
                stan->board[y][x+1] = 'X';
                valuable[y][x+1] = 1;
                stan->gracz = 1;
                return 1;
            } else if(x > 0 && stan->board[y][x - 1] == szukana && stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == 0){
                stan->board[y][x+1] = 'X';
                valuable[y][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (y > 0 && stan->board[y - 1][x] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x] == 0 && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == szukana) {
                stan->board[y + 1][x] = 'X';
                valuable[y+1][x] = 1;
                stan->gracz = 1;
                return 1;
            } else if(y > 0 && stan->board[y - 1][x] == szukana && stan->board[y][x] == 0 && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == 0){
                stan->board[y + 1][x] = 'X';
                valuable[y+1][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == szukana) {
                stan->board[y+1][x+1] = 'X';
                valuable[y+1][x+1] = 1;
                stan->gracz = 1;
                return 1;
            } else if(y > 0 && x > 0 && stan->board[y - 1][x - 1] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == 0){
                stan->board[y+1][x+1] = 'X';
                valuable[y+1][x+1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == szukana) {
                stan->board[y +1][x - 1] = 'X';
                valuable[y+1][x-1] = 1;
                stan->gracz = 1;
                return 1;
            } else if(y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == 0){
                stan->board[y +1][x - 1] = 'X';
                valuable[y+1][x-1] = 1;
                stan->gracz = 1;
                return 1;
            };
        }
    }
    return 0;
}
int _OOO_(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (x > 0 && stan->board[y][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y][x + 1] == szukana && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == 0) {
                stan->board[y][x-1] = 'X';
                valuable[y][x-1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (y > 0 && stan->board[y - 1][x] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == 0) {
                stan->board[y - 1][x] = 'X';
                valuable[y-1][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == szukana && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == 0) {
                stan->board[y-1][x-1] = 'X';
                valuable[y-1][x-1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == szukana && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == 0) {
                stan->board[y - 1][x + 1] = 'X';
                valuable[y-1][x+1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    return 0;
}
int _O_O_(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (x > 0 && stan->board[y][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == 0) {
                stan->board[y][x+1] = 'X';
                valuable[y][x+1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (y > 0 && stan->board[y - 1][x] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x] == 0 && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == 0) {
                stan->board[y + 1][x] = 'X';
                valuable[y+1][x] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == 0) {
                stan->board[y+1][x+1] = 'X';
                valuable[y+1][x+1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == 0) {
                stan->board[y + 1][x - 1] = 'X';
                valuable[y+1][x-1] = 1;
                stan->gracz = 1;
                return 1;
            }
        }
    }
    return 0;
}
int blockandattack(struct stan_gry* stan) {
    //Obrona
    if(OO_OO(stan,0)==1) return 1;
    if(_OOO_(stan,0)==1) return 1;
    if(_O_O_(stan,0)==1) return 1;
    if(_O_OOlubOO_O_(stan,0)==1) return 1;
    if(O_OOOlubOOO_O(stan,0)==1)return 1;
    if(_OOOlubOOO_(stan,0)==1) return 1;
    //Atak
    if(OO_OO(stan,1)==1) return 1;
    if(_OOO_(stan,1)==1) return 1;
    if(_O_O_(stan,1)==1) return 1;
    if(_O_OOlubOO_O_(stan,1)==1) return 1;
    if(O_OOOlubOOO_O(stan,1)==1)return 1;
    if(_OOOlubOOO_(stan,1)==1) return 1;
    return 0;
}
int evaluate(struct stan_gry* stan, int X){
    int result = 0;
    char szukana;
    if (X == 1) {
        szukana = 'X';
    } else {
        szukana = 'O';
    }
    for(int y = 0;y<BOARD_LENGHT;y++){
        for(int x = 0;x<BOARD_LENGHT;x++){
            if(stan->board[y][x]==szukana)continue;
            if(x>0){
                if(stan->board[y][x-1]==szukana){
                    result++;
                }
            }//lewo
            if(x<BOARD_LENGHT-1){
                if(stan->board[y][x+1]==szukana){
                    result++;
                }
            }//prawo
            if(y<BOARD_LENGHT-1){
                if(stan->board[y+1][x]==szukana){
                    result++;
                }
            }//dół
            if(y>0){
                if(stan->board[y-1][x]==szukana){
                    result++;
                }
            }//góra
            if(x>0&&y>0){
                if(stan->board[y-1][x-1]==szukana){
                    result++;
                }
            }//lewy górny
            if(x<BOARD_LENGHT-1&&y<BOARD_LENGHT-1){
                if(stan->board[y+1][x+1]==szukana){
                    result++;
                }
            }//prawy dolny
            if(x>0&&y<BOARD_LENGHT-1){
                if(stan->board[y+1][x-1]==szukana){
                    result++;
                }
            }//lewy dolny
            if(x<BOARD_LENGHT-1&&y>0){
                if(stan->board[y-1][x+1]==szukana){
                    result++;
                }
            }//prawy górny
        }
    }
    for(int y = 0; y < BOARD_LENGHT; y++){
        int count = 1;
        for(int x = 0; x < BOARD_LENGHT - 1; x++){
            if(stan->board[y][x]==stan->board[y][x+1] && (stan->board[y][x]==szukana)){
                count++;
            } else{
                count = 1;
            }
            if(count>=3){
                result+=count*10;
            }
        }
    }//wiersze
    for(int x = 0; x < BOARD_LENGHT; x++){
        int count = 1;
        for(int y = 0; y < BOARD_LENGHT - 1; y++){
            if(stan->board[y][x]==stan->board[y+1][x] && (stan->board[y][x]==szukana)){
                count++;
            } else{
                count = 1;
            }
            if(count>=3){
                result+=count*10;
            }
        }
    }//kolumny
    for(int y = 0 ;y < BOARD_LENGHT;y++){
        int x = 0;
        int ky = y;
        int count = 1;
        while (ky!=0){
            if(stan->board[ky][x]==stan->board[ky-1][x+1] && (stan->board[y][x]==szukana)){
                count++;
            } else{
                count = 1;
            }
            if(count>=3){
                result+=count*10;
            }
            x++;
            ky--;
        }
    }
    for(int x = 0 ;x < BOARD_LENGHT;x++){
        int y = BOARD_LENGHT-1;
        int kx = x;
        int count = 1;
        while (kx!=BOARD_LENGHT-1){
            if(stan->board[y][kx]==stan->board[y-1][kx+1] && (stan->board[y][x]==szukana)){
                count++;
            } else{
                count = 1;
            }
            if(count>=3){
                result+=count*10;
            }
            kx++;
            y--;
        }
    }//lewy dolny do prawy górny
    for(int x = 0 ;x < BOARD_LENGHT;x++){
        int y = BOARD_LENGHT-1;
        int kx = x;
        int count = 1;
        while (kx!=0){
            if(stan->board[y][kx]==stan->board[y-1][kx-1] && (stan->board[y][x]==szukana)){
                count++;
            } else{
                count = 1;
            }
            if(count>=3){
                result+=count*10;
            }
            kx--;
            y--;
        }
    }
    for(int x = 0 ;x < BOARD_LENGHT;x++){
        int y = 0;
        int kx = x;
        int count = 1;
        while (kx!=BOARD_LENGHT-1){
            if(stan->board[y][kx]==stan->board[y+1][kx+1] && (stan->board[y][x]==szukana)){
                count++;
            } else{
                count = 1;
            }
            if(count>=3){
                result+=count*10;
            }
            kx++;
            y++;
        }
    }//prawy dolny do lewy górny
    return result;
}
int minimax(struct stan_gry* state, bool isMaximizingPlayer,int depth, int alpha, int beta) {
    int k = check_winner(state);
    if (k == 1) {
        return 100000-depth;
    }else if(k==2){
        return depth-100000;
    }else if(k==-1){
        return 0;
    }else if(depth == 3){
        if(isMaximizingPlayer==true){
            return evaluate(state,1)-evaluate(state,0);
        } else{
            return -evaluate(state,1)-evaluate(state,0);
        }
    }
    int bestScore = isMaximizingPlayer ? INT_MIN : INT_MAX;
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT; x++) {
            if (state->board[y][x] == 0 && something(valuable,y,x)==1){
                counter++;
                state->board[y][x] = isMaximizingPlayer ? 'X' : 'O';
                int score = minimax(state, !isMaximizingPlayer, depth + 1, alpha, beta);
                state->board[y][x] = 0;
                if (isMaximizingPlayer) {
                    bestScore = MAX(score,bestScore);
                    alpha = MAX(alpha, bestScore);
                    if(alpha>=beta){
                        return bestScore;
                    }
                } else {
                    bestScore = MIN(score,bestScore);
                    beta = MIN(beta, bestScore);
                    if(alpha>=beta){
                        return bestScore;
                    }
                }
            }
        }
    }
    return bestScore;
}
void best_move(struct stan_gry* state){
    counter = 0;
    state->ruch += 1;
    int best_x, best_y;
    int best_score = INT_MIN;
    for (int i = 0; i < BOARD_LENGHT; i++) {
        for (int j = 0; j < BOARD_LENGHT; j++) {
            if (state->board[i][j] == 0 && something(valuable,i,j)==1) {
                state->board[i][j] = 'X';
                int score = minimax(state, false, 0, INT_MIN, INT_MAX);
                state->board[i][j] = 0;
                if (score > best_score) {
                    best_score = score;
                    best_x = j;
                    best_y = i;
                }
            }
        }
    }
    state->board[best_y][best_x] = 'X';
    valuable[best_y][best_x] = 1;
    state->gracz = 1;
}
