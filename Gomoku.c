#include "header.h"
int main(void){
    system("clear");
    struct stan_gry stan = {.koniec = false, .gracz=1};
    print_stan_gry(&stan);
    while(stan.koniec!=true){
        if(stan.gracz==1){
            move(&stan);
        } else{
            best_move(&stan);
        }
        int k = check_winner(&stan);
        if(k==1){
            system("clear");
            stan.koniec = true;
            printf("PRZEGRAŁEŚ Z BOTEM!");
            print_stan_gry(&stan);
            return 0;
        }else if(k==2) {
            system("clear");
            stan.koniec = true;
            printf("WYGRAŁEŚ Z BOTEM!");
            print_stan_gry(&stan);
            return 0;
        }else if(k==-1){
                system("clear");
                printf("REMIS!");
                stan.koniec = true;
                print_stan_gry(&stan);
                return 0;
        }else{
            system("clear");
            print_stan_gry(&stan);
        }
    }
    return 0;
}
