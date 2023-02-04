#include "header.h"
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
    for(int i = 0; i < BOARD_LENGTH * 4 + 1; i++){
        if(i%4==0) printf("\x1b[92m+\x1b[0m");
        else printf("\x1b[92m-\x1b[0m");
    }
    putchar('\n');
    for(int y = 0; y < BOARD_LENGTH; y++){
        if(y>8){
            printf("\x1b[96m%d \x1b[0m", y+1);
        }else{
            printf("\x1b[96m%d  \x1b[0m", y+1);
        }
        printf("\x1b[92m|\x1b[0m");
        for(int x = 0; x < BOARD_LENGTH; x++){
            if(stan->board[y][x]!=0){
                if(stan->board[y][x]=='X') printf("\x1b[95m %c\x1b[92m |\x1b[0m", stan->board[y][x]);
                if(stan->board[y][x]=='O') printf("\x1b[93m %c\x1b[92m |\x1b[0m", stan->board[y][x]);
            } else{
                printf("\x1b[92m   |\x1b[0m");
            }
        }
        printf("\n   ");
        for(int i = 0; i < BOARD_LENGTH * 4 + 1; i++){
            if(i%4==0) printf("\x1b[92m+");
            else printf("\x1b[92m-");
        }
        putchar('\n');
    }
    printf("   ");
    for(int i = 1; i <= BOARD_LENGTH; i++){
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
        if (scanf(" %d %d", &x, &y) == 2 && x >= 1 && y >= 1 && x <= BOARD_LENGTH && y <= BOARD_LENGTH && state->board[y - 1][x - 1] == 0){
            break;
        }
        clear();
    } while (true);
    state->board[y-1][x-1] = 'O';
    valuable[y-1][x-1] = 1;
    state->ruch += 1;
    state->gracz = -1;
    if(system("clear")==-1) printf("error\n");
}
int check_winner(struct stan_gry* state){
    for(int y = 0; y < BOARD_LENGTH; y++){
        int count = 1;
        for(int x = 0; x < BOARD_LENGTH - 1; x++){
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
    for(int x = 0; x < BOARD_LENGTH; x++){
        int count = 1;
        for(int y = 0; y < BOARD_LENGTH - 1; y++){
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
    for(int y = 0 ; y < BOARD_LENGTH; y++){
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
    for(int x = 0 ; x < BOARD_LENGTH; x++){
        int y = BOARD_LENGTH - 1;
        int kx = x;
        int count = 1;
        while (kx != BOARD_LENGTH - 1){
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
    for(int x = 0 ; x < BOARD_LENGTH; x++){
        int y = BOARD_LENGTH - 1;
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
    for(int x = 0 ; x < BOARD_LENGTH; x++){
        int y = 0;
        int kx = x;
        int count = 1;
        while (kx != BOARD_LENGTH - 1){
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
    for(int i = 0; i < BOARD_LENGTH; i++){
        for(int j = 0; j < BOARD_LENGTH; j++){
            if(state->board[i][j]!=0){
                draw++;
            }
        }
    }
    if(draw == BOARD_LENGTH * BOARD_LENGTH){
        return -1;
    }//remis
    return 0;
}
int something(int board[BOARD_LENGTH][BOARD_LENGTH], int y, int x){
    if(x>0){
        if(board[y][x-1]!=0){
            return 1;
        }
    }//lewo
    if(x < BOARD_LENGTH - 1){
        if(board[y][x+1]!=0){
            return 1;
        }
    }//prawo
    if(y < BOARD_LENGTH - 1){
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
    if(x < BOARD_LENGTH - 1 && y < BOARD_LENGTH - 1){
        if(board[y+1][x+1]!=0){
            return 1;
        }
    }//prawy dolny
    if(x>0&& y < BOARD_LENGTH - 1){
        if(board[y+1][x-1]!=0){
            return 1;
        }
    }//lewy dolny
    if(x < BOARD_LENGTH - 1 && y > 0){
        if(board[y-1][x+1]!=0){
            return 1;
        }
    }//prawy górny
    return 0;
}
int update(struct stan_gry* stan){
    int k = check_winner(stan);
    if (k == 1) {
        if (system("clear") == -1) printf("error\n");
        stan->koniec = true;
        print_stan_gry(stan);
        printf("\x1b[31m\n"
               "     __     ______  _    _        _      ____   _____ _______ \n"
               "     \\ \\   / / __ \\| |  | |      | |    / __ \\ / ____|__   __|\n"
               "      \\ \\_/ / |  | | |  | |      | |   | |  | | (___    | |   \n"
               "       \\   /| |  | | |  | |      | |   | |  | |\\___ \\   | |   \n"
               "        | | | |__| | |__| |      | |___| |__| |____) |  | |   \n"
               "        |_|  \\____/ \\____/       |______\\____/|_____/   |_|   \n"
               "                                                              \n"
               "                                                              \x1b[0m\n");
        return 0;
    } else if (k == 2) {
        if (system("clear") == -1) printf("error\n");
        stan->koniec = true;
        print_stan_gry(stan);
        printf("\x1b[36m\n"
               "     __     ______  _    _      __          ______  _   _ \n"
               "     \\ \\   / / __ \\| |  | |     \\ \\        / / __ \\| \\ | |\n"
               "      \\ \\_/ / |  | | |  | |      \\ \\  /\\  / / |  | |  \\| |\n"
               "       \\   /| |  | | |  | |       \\ \\/  \\/ /| |  | | . ` |\n"
               "        | | | |__| | |__| |        \\  /\\  / | |__| | |\\  |\n"
               "        |_|  \\____/ \\____/          \\/  \\/   \\____/|_| \\_|\n"
               "                                                          \n"
               "                                                          \x1b[0m\n");
        return 0;
    } else if (k == -1) {
        if (system("clear") == -1) printf("error\n");
        stan->koniec = true;
        print_stan_gry(stan);
        printf("\x1b[35m\n"
               "      _____  _____       __          __\n"
               "     |  __ \\|  __ \\     /\\ \\        / /\n"
               "     | |  | | |__) |   /  \\ \\  /\\  / / \n"
               "     | |  | |  _  /   / /\\ \\ \\/  \\/ /  \n"
               "     | |__| | | \\ \\  / ____ \\  /\\  /   \n"
               "     |_____/|_|  \\_\\/_/    \\_\\/  \\/    \n"
               "                                       \n"
               "                                       \x1b[0m\n");
        return 0;
    } else {
        if (system("clear") == -1) printf("error\n");
        printf("\x1b[95mnodes: %d\x1b[0m", counter);
        counter = 0;
        print_stan_gry(stan);
    }
    return 0;
}