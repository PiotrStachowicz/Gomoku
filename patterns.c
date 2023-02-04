#include "header.h"
int _OOOlubOOO_(struct stan_gry* stan, int atak){
    char szukana;
    if(atak==1){
        szukana='X';
    } else{
        szukana='O';
    }
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y][x + 1] == szukana && stan->board[y][x + 2] == szukana) {
                if (x > 0 && stan->board[y][x - 1] == 0) {
                    if(atak!=3) {
                        stan->board[y][x - 1] = 'X';
                        valuable[y][x - 1] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
                if (x < BOARD_LENGTH - 3 && stan->board[y][x + 3] == 0) {
                    if(atak!=3){
                        stan->board[y][x + 3] = 'X';
                        valuable[y][x+1] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
            }
        }
    }
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_LENGTH - 2; y++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == szukana) {
                if (y > 0 && stan->board[y - 1][x] == 0) {
                    if(atak!=3){
                        stan->board[y - 1][x] = 'X';
                        valuable[y-1][x] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
                if (y < BOARD_LENGTH - 3 && stan->board[y + 3][x] == 0) {
                    if(atak!=3) {
                        stan->board[y + 3][x] = 'X';
                        valuable[y + 3][x] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == szukana && stan->board[y + 2][x + 2] == szukana) {
                if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0) {
                    if(atak!=3) {
                        stan->board[y - 1][x - 1] = 'X';
                        valuable[y - 1][x - 1] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
                if (y < BOARD_LENGTH - 3 && x < BOARD_LENGTH - 3 && stan->board[y + 3][x + 3] == 0) {
                    if(atak!=3) {
                        stan->board[y + 3][x + 3] = 'X';
                        valuable[y + 3][x + 3] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 2; x < BOARD_LENGTH; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == szukana && stan->board[y + 2][x - 2] == szukana) {
                if (y > 0 && x < BOARD_LENGTH - 1 && stan->board[y - 1][x + 1] == 0) {
                    if(atak!=3) {
                        stan->board[y - 1][x + 1] = 'X';
                        valuable[y - 1][x + 1] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
                if (y < BOARD_LENGTH - 3 && x > 1 && stan->board[y + 3][x - 3] == 0) {
                    if(atak!=3) {
                        stan->board[y + 3][x - 3] = 'X';
                        valuable[y + 3][x - 3] = 1;
                        stan->gracz = 1;
                    }
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
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana) {
                if (x > 0 && stan->board[y][x - 1] == szukana && x < BOARD_LENGTH - 3 && stan->board[y][x + 3] == szukana) {
                    if(atak!=3) {
                        stan->board[y][x + 1] = 'X';
                        valuable[y][x + 1] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
            }
        }
    }
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_LENGTH - 2; y++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x] == 0 && stan->board[y + 2][x] == szukana) {
                if (y > 0 && stan->board[y - 1][x] == szukana && y < BOARD_LENGTH - 3 &&  stan->board[y + 3][x] == szukana) {
                    if(atak!=3) {
                        stan->board[y + 1][x] = 'X';
                        valuable[y + 1][x] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana) {
                if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == szukana && x < BOARD_LENGTH - 3 && y < BOARD_LENGTH - 3 &&  stan->board[y + 3][x + 3] == szukana) {
                    if(atak!=3) {
                        stan->board[y + 1][x + 1] = 'X';
                        valuable[y + 1][x + 1] = 1;
                        stan->gracz = 1;
                    }
                    return 1;
                }
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 2; x < BOARD_LENGTH; x++) {
            if (stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana) {
                if (y > 0 && x < BOARD_LENGTH - 1 && stan->board[y - 1][x + 1] == szukana && x > 2 && y < BOARD_LENGTH - 3 && stan->board[y + 3][x - 3] == szukana) {
                    if(atak!=3) {
                        stan->board[y + 1][x - 1] = 'X';
                        valuable[y + 1][x - 1] = 1;
                        stan->gracz = 1;
                    }
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
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (x > 0 && x<BOARD_LENGTH - 3 && stan->board[y][x - 1] == szukana && stan->board[y][x] == 0 && stan->board[y][x + 1] == szukana && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == szukana) {
                if(atak!=3) {
                    stan->board[y][x] = 'X';
                    valuable[y][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_LENGTH - 2; y++) {
            if (y > 0 && y<BOARD_LENGTH-3 && stan->board[y - 1][x] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == 0 && stan->board[y + 3][x] == szukana) {
                if(atak!=3) {
                    stan->board[y + 2][x] = 'X';
                    valuable[y + 2][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (y > 0 && x > 0 && x< BOARD_LENGTH-3 && y<BOARD_LENGTH-3 && stan->board[y - 1][x - 1] == szukana && stan->board[y][x] == 0 && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == szukana) {
                if(atak!=3) {
                    stan->board[y][x] = 'X';
                    valuable[y][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 2; x < BOARD_LENGTH; x++) {
            if (y > 0 && y < BOARD_LENGTH - 3 && x > 2 && x < BOARD_LENGTH - 2 && stan->board[y - 1][x + 1] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == szukana && stan->board[y + 2][x - 2] == 0 && stan->board[y + 3][x - 3] == szukana) {
                if(atak!=3) {
                    stan->board[y + 2][x - 2] = 'X';
                    valuable[y + 2][x - 2] = 1;
                    stan->gracz = 1;
                }
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
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (x > 0 && stan->board[y][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == szukana) {
                if(atak!=3) {
                    stan->board[y][x + 1] = 'X';
                    valuable[y][x + 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            } else if(x > 0 && stan->board[y][x - 1] == szukana && stan->board[y][x] == szukana && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == 0){
                if(atak!=3) {
                    stan->board[y][x + 1] = 'X';
                    valuable[y][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_LENGTH - 2; y++) {
            if (y > 0 && stan->board[y - 1][x] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x] == 0 && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == szukana) {
                if(atak!=3) {
                    stan->board[y + 1][x] = 'X';
                    valuable[y + 1][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            } else if(y > 0 && stan->board[y - 1][x] == szukana && stan->board[y][x] == 0 && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == 0){
                if(atak!=3) {
                    stan->board[y + 1][x] = 'X';
                    valuable[y + 1][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == szukana) {
                if(atak!=3) {
                    stan->board[y + 1][x + 1] = 'X';
                    valuable[y + 1][x + 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            } else if(y > 0 && x > 0 && stan->board[y - 1][x - 1] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == 0){
                if(atak!=3) {
                    stan->board[y + 1][x + 1] = 'X';
                    valuable[y + 1][x + 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 2; x < BOARD_LENGTH; x++) {
            if (y > 0 && x < BOARD_LENGTH - 1 && stan->board[y - 1][x + 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == szukana) {
                if(atak!=3) {
                    stan->board[y + 1][x - 1] = 'X';
                    valuable[y + 1][x - 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            } else if(y > 0 && x < BOARD_LENGTH - 1 && stan->board[y - 1][x + 1] == szukana && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == 0){
                if(atak!=3) {
                    stan->board[y + 1][x - 1] = 'X';
                    valuable[y + 1][x - 1] = 1;
                    stan->gracz = 1;
                }
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
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (x > 0 && x < BOARD_LENGTH - 3 && stan->board[y][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y][x + 1] == szukana && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == 0) {
                if(atak!=3) {
                    stan->board[y][x - 1] = 'X';
                    valuable[y][x - 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_LENGTH - 2; y++) {
            if (y > 0 && y < BOARD_LENGTH - 3 && stan->board[y - 1][x] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x] == szukana && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == 0) {
                if(atak!=3) {
                    stan->board[y - 1][x] = 'X';
                    valuable[y - 1][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == szukana && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == 0) {
                if(atak!=3) {
                    stan->board[y - 1][x - 1] = 'X';
                    valuable[y - 1][x - 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 2; x < BOARD_LENGTH; x++) {
            if (y > 0 && x < BOARD_LENGTH - 1 && stan->board[y - 1][x + 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == szukana && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == 0) {
                if(atak!=3) {
                    stan->board[y - 1][x + 1] = 'X';
                    valuable[y - 1][x + 1] = 1;
                    stan->gracz = 1;
                }
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
    for (int y = 0; y < BOARD_LENGTH; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (x > 0 && stan->board[y][x - 1] == 0 && stan->board[y][x] == szukana && x < BOARD_LENGTH - 3 && stan->board[y][x + 1] == 0 && stan->board[y][x + 2] == szukana && stan->board[y][x + 3] == 0) {
                if(atak!=3) {
                    stan->board[y][x + 1] = 'X';
                    valuable[y][x + 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_LENGTH - 2; y++) {
            if (y > 0 &&  y < BOARD_LENGTH - 3 && stan->board[y - 1][x] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x] == 0 && stan->board[y + 2][x] == szukana && stan->board[y + 3][x] == 0) {
                if(atak!=3) {
                    stan->board[y + 1][x] = 'X';
                    valuable[y + 1][x] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 0; x < BOARD_LENGTH - 2; x++) {
            if (y > 0 && x > 0 && stan->board[y - 1][x - 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x + 1] == 0 && stan->board[y + 2][x + 2] == szukana && stan->board[y + 3][x + 3] == 0) {
                if(atak!=3) {
                    stan->board[y + 1][x + 1] = 'X';
                    valuable[y + 1][x + 1] = 1;
                    stan->gracz = 1;
                }
                return 1;
            }
        }
    }
    for (int y = 0; y < BOARD_LENGTH - 2; y++) {
        for (int x = 2; x < BOARD_LENGTH; x++) {
            if (y > 0 && x < BOARD_LENGTH - 1 && stan->board[y - 1][x + 1] == 0 && stan->board[y][x] == szukana && stan->board[y + 1][x - 1] == 0 && stan->board[y + 2][x - 2] == szukana && stan->board[y + 3][x - 3] == 0) {
                if(atak!=3) {
                    stan->board[y + 1][x - 1] = 'X';
                    valuable[y + 1][x - 1] = 1;
                    stan->gracz = 1;
                }
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
