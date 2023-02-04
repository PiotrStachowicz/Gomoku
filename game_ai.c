#include "header.h"
int patterns(struct stan_gry* stan){
    if(OO_OO(stan,3)==1) return 1;
    else if(_OOO_(stan,3)==1) return 1;
    else if(_O_O_(stan,3)==1) return 1;
    else if(_O_OOlubOO_O_(stan,3)==1) return 1;
    else if(O_OOOlubOOO_O(stan,3)==1)return 1;
    else if(_OOOlubOOO_(stan,3)==1) return 1;
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
    for(int y = 0; y < BOARD_LENGTH; y++){
        int count = 1;
        for(int x = 0; x < BOARD_LENGTH - 1; x++){
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
    for(int x = 0; x < BOARD_LENGTH; x++){
        int count = 1;
        for(int y = 0; y < BOARD_LENGTH - 1; y++){
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
    for(int y = 0 ; y < BOARD_LENGTH; y++){
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
    for(int x = 0 ; x < BOARD_LENGTH; x++){
        int y = BOARD_LENGTH - 1;
        int kx = x;
        int count = 1;
        while (kx != BOARD_LENGTH - 1){
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
    for(int x = 0 ; x < BOARD_LENGTH; x++){
        int y = BOARD_LENGTH - 1;
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
    for(int x = 0 ; x < BOARD_LENGTH; x++){
        int y = 0;
        int kx = x;
        int count = 1;
        while (kx != BOARD_LENGTH - 1){
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
    if(X == 1 && patterns(stan)==1){
        result += 150;
    }
    return result;
}
int minimax(struct stan_gry* state, bool isMaximizingPlayer,int depth, int alpha, int beta) {
    int k = check_winner(state);
    if (k == 1) {
        return (10000-depth);
    }else if(k==2){
        return -(10000-depth);
    }else if(k==-1){
        return 0;
    }else if(depth == 3){
        if(isMaximizingPlayer==true){
            return evaluate(state,1) - evaluate(state,0);
        } else{
            return -evaluate(state,1) + evaluate(state, 0);
        }
    }
    int bestScore = isMaximizingPlayer ? INT_MIN : INT_MAX;
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH; x++) {
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
    int best_x = 0, best_y = 0;
    int best_score = INT_MIN;
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
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