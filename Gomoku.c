#include "header.h"
int main(void){
    for(int i = 0;i<BOARD_LENGHT;i++){
        for(int j = 0;j<BOARD_LENGHT;j++){
            valuable[i][j] = 0;
        }
    }
    system("clear");
    struct stan_gry stan = {.koniec = false, .gracz=2, .ruch=1};
    print_stan_gry(&stan);
    while(stan.koniec!=true){
        if(stan.gracz == 2 && stan.ruch == 1){
            stan.board[7][7] = 'X';
            valuable[7][7] = 1;
            stan.gracz = 1;
            stan.ruch += 1;
        } else if(stan.gracz==1){
            move(&stan);
        }else{
            struct stan_gry dummy_state = stan;
            best_move(&stan, 1);
            if(check_winner(&stan)==0){
                stan = dummy_state;
                if(blockandattack(&stan)==0){
                    best_move(&stan, 0);
                }
            }
        }
        int k = check_winner(&stan);
        if(k==1){
            system("clear");
            stan.koniec = true;
            print_stan_gry(&stan);
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
        }else if(k==2) {
            system("clear");
            stan.koniec = true;
            print_stan_gry(&stan);
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
        }else if(k==-1){
            system("clear");
            stan.koniec = true;
            print_stan_gry(&stan);
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
        }else{
            system("clear");
            printf("\x1b[95mnodes: %d\x1b[0m", counter);
            counter=0;
            print_stan_gry(&stan);
        }
    }
    return 0;
}
