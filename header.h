#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define BOARD_LENGHT 15
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
int counter;
int valuable[BOARD_LENGHT][BOARD_LENGHT];
struct stan_gry{
    char board[BOARD_LENGHT][BOARD_LENGHT];
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
        printf("\x1b[92m-\x1b[0m");
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
                printf("\x1b[92m %c |\x1b[0m", stan->board[y][x]);
            } else{
                printf("\x1b[92m   |\x1b[0m");
            }
        }
        printf("\n   ");
        for(int i = 0; i < BOARD_LENGHT * 4 + 1; i++){
            printf("\x1b[92m-");
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
void move(struct stan_gry* state){
    int x, y;
    do {
        printf("Podaj ruch <kolumna> <wiersz>: ");
        if (scanf("%d %d", &x, &y) == 2 && x >= 1 && y >= 1 && x <= BOARD_LENGHT && y <= BOARD_LENGHT && state->board[y-1][x-1] == 0) {
            break;
        }
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
int blockandattack(struct stan_gry* stan) {
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == 'O' && stan->board[y][x + 1] == 'O' && stan->board[y][x + 2] == 'O') {
                if (x > 0 && stan->board[y][x - 1] == 0) {
                    stan->board[y][x - 1] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (x < BOARD_LENGHT - 3 && stan->board[y][x + 3] == 0) {
                    stan->board[y][x + 3] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (stan->board[y][x] == 'O' && stan->board[y + 1][x] == 'O' && stan->board[y + 2][x] == 'O') {
                if (y > 0 && stan->board[y - 1][x] == 0) {
                    stan->board[y - 1][x] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && stan->board[y + 3][x] == 0) {
                    stan->board[y + 3][x] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == 'O' && stan->board[y + 1][x + 1] == 'O' &&
                stan->board[y + 2][x + 2] == 'O') {
                if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0) {
                    stan->board[y - 1][x - 1] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && x < BOARD_LENGHT - 3 && stan->board[y + 3][x + 3] == 0) {
                    stan->board[y + 3][x + 3] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (stan->board[y][x] == 'O' && stan->board[y + 1][x - 1] == 'O' && stan->board[y + 2][x - 2] == 'O') {
                if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == 0) {
                    stan->board[y - 1][x + 1] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && x > 1 && stan->board[y + 3][x - 3] == 0) {
                    stan->board[y + 3][x - 3] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    //Atak
    for (int y = 0; y < BOARD_LENGHT; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == 'X' && stan->board[y][x + 1] == 'X' && stan->board[y][x + 2] == 'X') {
                // Znajdź puste pole obok rzędu O i zagraj tam X
                if (x > 0 && stan->board[y][x - 1] == 0) {
                    stan->board[y][x - 1] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (x < BOARD_LENGHT - 3 && stan->board[y][x + 3] == 0) {
                    stan->board[y][x + 3] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int x = 0; x < BOARD_LENGHT; x++) {
        for (int y = 0; y < BOARD_LENGHT - 2; y++) {
            if (stan->board[y][x] == 'X' && stan->board[y + 1][x] == 'X' && stan->board[y + 2][x] == 'X') {
                if (y > 0 && stan->board[y - 1][x] == 0) {
                    stan->board[y - 1][x] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && stan->board[y + 3][x] == 0) {
                    stan->board[y + 3][x] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 0; x < BOARD_LENGHT - 2; x++) {
            if (stan->board[y][x] == 'X' && stan->board[y + 1][x + 1] == 'X' && stan->board[y + 2][x + 2] == 'X') {
                if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0) {
                    stan->board[y - 1][x - 1] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && x < BOARD_LENGHT - 3 && stan->board[y + 3][x + 3] == 0) {
                    stan->board[y + 3][x + 3] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGHT - 2; y++) {
        for (int x = 2; x < BOARD_LENGHT; x++) {
            if (stan->board[y][x] == 'X' && stan->board[y + 1][x - 1] == 'X' && stan->board[y + 2][x - 2] == 'X') {
                if (y > 0 && x < BOARD_LENGHT - 1 && stan->board[y - 1][x + 1] == 0) {
                    stan->board[y - 1][x + 1] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
                if (y < BOARD_LENGHT - 3 && x > 1 && stan->board[y + 3][x - 3] == 0) {
                    stan->board[y + 3][x - 3] = 'X';
                    stan->gracz = 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}
int minimax(struct stan_gry* state, bool isMaximizingPlayer,int depth, int alpha, int beta) {
    if(depth == 3){
        return 0;
    }
    if(check_winner(state)==-1){
        return 0;
    }
    if (check_winner(state) == 1) {
        return 100-depth;
    }else if(check_winner(state)==2){
        return depth-100;
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
                    if(alpha>beta){
                        return bestScore;
                    }
                } else {
                    bestScore = MIN(score,bestScore);
                    beta = MIN(beta, bestScore);
                    if(alpha>beta){
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
    printf("%d", counter);
}
