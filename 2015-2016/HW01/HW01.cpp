/* 
 * File:   main.cpp
 * Author: Doða
 *
 * Created on 05 Ekim 2015 Pazartesi, 23:04
 */


#include <iostream>
#include <ctype.h>

using namespace std;

const int MAXTABLESIZE = 20;

typedef struct {
    int x;
    int y;
    int valueMove;
    char playerSymb;
    char targetSymb;
} move_t;

void updateAndPrintTable(char table[MAXTABLESIZE][MAXTABLESIZE], int tableSize, move_t player);
int checkMove(char table[MAXTABLESIZE][MAXTABLESIZE], int tableSize, move_t *player);

int main() {
    int tableSize = 0;
    move_t comp_t = {0, 0, 0, 'X', 'O'};
    move_t user_t = {0, 0, -2, 'O', 'X'};
    char table[MAXTABLESIZE][MAXTABLESIZE];
    int gameStatus = 1;
    int validMove = 0;
    int userY;
    char userX; //temp char for x
    int endUser = 0, endComp = 0;
    int validPoint;

    cout << "Oyunu kaca kaclik tahtada oynamak istersiniz ? Cift sayilarda secim yapiniz " << endl;
    cin >> tableSize;

    while (tableSize % 2 != 0 && tableSize > MAXTABLESIZE && tableSize != 0) {
        cout << "Gecerli tahta boyutu girmediniz. Tekrar deneyiniz " << endl;
        cin >> tableSize;
    }

    cout << "Secilen tahta boyutu : " << tableSize << endl << endl;

    updateAndPrintTable(table, tableSize, user_t);

    cout << endl << endl;

    while (gameStatus == 1) {

        //user_t.movePts=1;
        validMove = checkMove(table, tableSize, &user_t);

        if (validMove == 2) {
            cout << "Oynayacaginiz bir hamle bulunmamaktadir." << endl << endl;
            validMove = 0;
            endUser = 1;
        } else {
            //user_t.movePts=0;
            while (validMove == 0) {

                validPoint = 0;
                while (validPoint == 0) {
                    validPoint = 1;
                    cout << "Oynayacaginiz noktayý giriniz :";
                    cin >> userY >> userX;

                    if (cin.fail() || userY < 1 || userY > tableSize)
                        validPoint = 0;
                    userX = tolower(userX);
                    if (userX > 't' || userX < 'a')
                        validPoint = 0;

                    if (validPoint == 0)
                        cout << "Gecerli bir nokta girmediniz, girdinizi kontrol ederek tekrar giriniz" << endl << endl;
                    else {
                        user_t.x = (int) userX - (int) 'a';
                    }

                }
                validMove = checkMove(table, tableSize, &user_t);
                if (validMove == 0)
                    cout << "Hamle yapilabilecek bir nokta girmediniz, tekrardan deneyiniz" << endl << endl;

            }
        }

        if (validMove != 2)
            updateAndPrintTable(table, tableSize, user_t);

        validMove = checkMove(table, tableSize, &comp_t);
        if (validMove == 0) {
            cout << "PC'nin oynayacak hamlesi bulunmamaktadir. Sira sizde :" << endl << endl;
            endComp = 1;

        } else
            updateAndPrintTable(table, tableSize, comp_t);

        if (endUser == 1 && endComp == 1)
            gameStatus = 0;
        else {
            endUser = 0;
            endComp = 0;
        }
    }

    int x = 0, y = 0;
    int userCount = 0, compCount = 0;
    for (y = 0; y < tableSize; y++)
        for (x = 0; x < tableSize; x++) {
            if (table[y][x] == 'O')
                ++userCount;
            if (table[y][x] == 'X')
                ++compCount;
        }

    cout << "Score Talbe :" << endl << "Siz : " << userCount << "Bilgisayar : " << compCount << endl << endl;
    cout << "Kazanan : ";
    if (userCount > compCount)
        cout << "Siz";
    else
        cout << "Bilgisayar";

    return 0;
}

void updateAndPrintTable(char table[MAXTABLESIZE][MAXTABLESIZE], int tableSize, move_t updateTarget) {
    int i = 0, k = 0;
    int startPoint = tableSize / 2;
    char playerSymb = updateTarget.playerSymb;
    char targetSymb = updateTarget.targetSymb;
    int x = updateTarget.x;
    int y = updateTarget.y;
    int cself; // counts until playerSymb found 
    int cempty; // counts until '.' found	


    if (updateTarget.valueMove == -2) {
        /*char horChar = 'a'; //Starting char to print horizantal
        &(*table)=' '; */
        for (i = 0; i < tableSize; ++i)
            for (k = 0; k < tableSize; ++k)
                table[i][k] = '.';

        table[startPoint][startPoint] = 'X';
        table[startPoint][startPoint + 1] = 'O';
        table[startPoint + 1][startPoint + 1] = 'X';
        table[startPoint + 1][startPoint] = 'O';

        updateTarget.valueMove = -1;
    }
        //Oyuncu veya makinanin uygun olan hamlesine gore, tahta uzerinde olan degisiklikler yapilir
    else {

        //saga kontrol
        if (table[y][x + 1] == targetSymb) {

            for (cself = 1; table[y][x + cself] != playerSymb && x + cself < tableSize; ++cself);
            for (cempty = 1; table[y][x + cempty] != '.' && x + cempty < tableSize; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y][x + i] != '.'; ++i)
                    table[y][x + i] = playerSymb;
                table[y][x + i] = playerSymb;
            }
        }
        //sola kontrol
        if (table[y][x - 1] == targetSymb) {
            for (cself = 1; table[y][x - cself] != playerSymb && x - cself > 0; ++cself);
            for (cempty = 1; table[y][x - cempty] != '.' && x - cempty > 0; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y][x - i] != '.'; ++i)
                    table[y][x - i] = playerSymb;
                table[y][x - i] = playerSymb;
            }
        }

        //yukari kontrol
        if (table[y - 1][x] == targetSymb) {
            for (cself = 1; table[y - cself][x] != playerSymb && y - cself > 0; ++cself);
            for (cempty = 1; table[y - cself][x] != '.' && y - cempty > 0; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y - i][x] != '.'; ++i)
                    table[y - i][x] = playerSymb;
                table[y - i][x] = playerSymb;
            }
        }

        //asagi kontrol
        if (table[y + 1][x] == targetSymb) {
            for (cself = 1; table[y + cself][x] != playerSymb && y + cself < tableSize; ++cself);
            for (cempty = 1; table[y + cself][x] != '.' && y + cempty < tableSize; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y + i][x] != '.'; ++i)
                    table[y + i][x] = playerSymb;
                table[y + i][x] = playerSymb;
            }
        }

        //sag alt capraza dogru kontrol
        if (table[y + 1][x + 1] == targetSymb) {
            for (cself = 1; table[y + cself][x + cself] != playerSymb && y + cself < tableSize && x + cself < tableSize; ++cself);
            for (cempty = 1; table[y + cself][x + cself] != '.' && y + cempty < tableSize && x + cempty < tableSize; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y + i][x + i] != '.'; ++i)
                    table[y + i][x + i] = playerSymb;
                table[y + i][x + i] = playerSymb;
            }
        }

        // sol ust tarafa dogru kontrol
        if (table[y - 1][x - 1] == targetSymb) {
            for (cself = 1; table[y - cself][x - cself] != playerSymb && y - cself > 0 && x - cself > 0; ++cself);
            for (cempty = 1; table[y - cself][x - cself] != '.' && y - cempty > 0 && x - cempty > 0; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y - i][x - i] != '.'; ++i)
                    table[y - i][x - i] = playerSymb;
                table[y - i][x - i] = playerSymb;
            }
        }

        //sol alt capraza dogru kontrol
        if (table[y + 1][x - 1] == targetSymb) {
            for (cself = 1; table[y + cself][x - cself] != playerSymb && y + cself < tableSize && x - cself > 0; ++cself);
            for (cempty = 1; table[y + cself][x - cself] != '.' && y + cempty < tableSize && x - cempty > 0; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y + i][x - i] != '.'; ++i)
                    table[y + i][x - i] = playerSymb;
                table[y + i][x - i] = playerSymb;
            }
        }

        //sag uste dogru kontrol
        if (table[y - 1][x + 1] == targetSymb) {
            for (cself = 1; table[y - cself][x + cself] != playerSymb && y - cself > 0 && x + cself < tableSize; ++cself);
            for (cempty = 1; table[y - cself][x + cself] != '.' && y - cempty > 0 && x + cempty < tableSize; ++cempty);

            if (cempty < cself) {
                for (i = 1; table[y - i][x + i] != '.'; ++i)
                    table[y - i][x + i] = playerSymb;
                table[y - i][x + i] = playerSymb;
            }
        }
    }


    char horChar = 'a';
    int vertNumb = 1;
    cout << "  ";
    for (i = 0; i < tableSize; ++i) {
        cout << horChar;
        ++horChar;
    }
    cout << endl;
    for (i = 0; i < tableSize; ++i) {
        if (vertNumb < 10)
            cout << vertNumb << ' ';
        else
            cout << vertNumb;

        cout << table[i] << endl;
        ++vertNumb;
    }
}

int checkMove(char table[MAXTABLESIZE][MAXTABLESIZE], int tableSize, move_t *player) {
    int currPts = 0;
    int validPlayerMove = 0;
    //player.movePts=0;
    int cself = 0; // counter for how many steps taken over player.targetMove
    int cempty = 0; // counter for how steps taken 'till reaching '.' 
    int x = 0, y = 0, tempX = 0, tempY = 0;
    char targetSymb = player->targetSymb;
    char playerSymb = player->playerSymb;

    //general check for valid move
    for (y = 0; y < tableSize; ++y)
        for (x = 0; x < tableSize; ++x) {
            //saga kontrol
            if (table[y][x + 1] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y][x + cself] != playerSymb && x + cself < tableSize; ++cself);
                for (cempty = 1; table[y][x + cempty] != '.' && x + cempty < tableSize; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            //sola kontrol
            if (table[y][x - 1] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y][x - cself] != playerSymb && x - cself > 0; ++cself);
                for (cempty = 1; table[y][x - cempty] != '.' && x - cempty > 0; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            //yukari kontrol
            if (table[y - 1][x] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y - cself][x] != playerSymb && y - cself > 0; ++cself);
                for (cempty = 1; table[y - cself][x] != '.' && y - cempty > 0; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            //asagi kontrol
            if (table[y + 1][x] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y + cself][x] != playerSymb && y + cself < tableSize; ++cself);
                for (cempty = 1; table[y + cself][x] != '.' && y + cempty < tableSize; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            //sag alt capraza dogru kontrol
            if (table[y + 1][x + 1] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y + cself][x + cself] != playerSymb && y + cself < tableSize && x + cself < tableSize; ++cself);
                for (cempty = 1; table[y + cself][x + cself] != '.' && y + cempty < tableSize && x + cempty < tableSize; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            // sol ust tarafa dogru kontrol
            if (table[y - 1][x - 1] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y - cself][x - cself] != playerSymb && y - cself > 0 && x - cself > 0; ++cself);
                for (cempty = 1; table[y - cself][x - cself] != '.' && y - cempty > 0 && x - cempty > 0; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            //sol alt capraza dogru kontrol
            if (table[y + 1][x - 1] == targetSymb) {
                cself = 0; // counts until playerSymb found 
                cempty = 0; // counts until '.' found
                for (cself = 1; table[y + cself][x - cself] != playerSymb && y + cself < tableSize && x - cself > 0; ++cself);
                for (cempty = 1; table[y + cself][x - cself] != '.' && y + cempty < tableSize && x - cempty > 0; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            //sag uste dogru kontrol
            if (table[y - 1][x + 1] == targetSymb) {
                cself = 0;
                cempty = 0;
                for (cself = 1; table[y - cself][x + cself] != playerSymb && y - cself > 0 && x + cself < tableSize; ++cself);
                for (cempty = 1; table[y - cself][x + cself] != '.' && y - cempty > 0 && x + cempty < tableSize; ++cempty);

                if (cempty < cself)
                    currPts += cempty;
            }

            if (currPts > player->valueMove) {
                if (player->playerSymb == 'X') {
                    player->valueMove = currPts;
                    player->x = x;
                    player->y = y;
                }
            }
        }

    if (currPts == 0 && player->playerSymb == 'O') {
        validPlayerMove = 2;
    }

    if (player->playerSymb == 'O' && validPlayerMove != 2 && player->valueMove != 0) {

        currPts = 0;

        //saga kontrol
        if (table[player->y][player->x + 1] == player->targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y][player->x + cself] != playerSymb && player->x + cself < tableSize; ++cself);
            for (cempty = 1; table[player->y][player->x + cempty] != '.' && player->x + cempty < tableSize; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        //sola kontrol
        if (table[player->y][player->x - 1] == targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y][player->x - cself] != playerSymb && player->x - cself > 0; ++cself);
            for (cempty = 1; table[player->y][player->x - cempty] != '.' && player->x - cempty > 0; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        //yukari kontrol
        if (table[player->y - 1][player->x] == targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y - cself][player->x] != playerSymb && player->y - cself > 0; ++cself);
            for (cempty = 1; table[player->y - cself][player->x] != '.' && player->y - cempty > 0; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        //asagi kontrol
        if (table[player->y + 1][player->x] == targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y + cself][player->x] != playerSymb && player->y + cself < tableSize; ++cself);
            for (cempty = 1; table[player->y + cself][player->x] != '.' && player->y + cempty < tableSize; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        //sag alt capraza dogru kontrol
        if (table[player->y + 1][player->x + 1] == targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y + cself][player->x + cself] != playerSymb && player->y + cself < tableSize && player->x + cself < tableSize; ++cself);
            for (cempty = 1; table[player->y + cself][player->x + cself] != '.' && player->y + cempty < tableSize && player->x + cempty < tableSize; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        // sol ust tarafa dogru kontrol
        if (table[player->y - 1][player->x - 1] == targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y - cself][player->x - cself] != playerSymb && player->y - cself > 0 && player->x - cself > 0; ++cself);
            for (cempty = 1; table[player->y - cself][player->x - cself] != '.' && player->y - cempty > 0 && player->x - cempty > 0; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        //sol alt capraza dogru kontrol
        if (table[player->y + 1][player->x - 1] == targetSymb) {
            cself = 0; // counts until playerSymb found 
            cempty = 0; // counts until '.' found
            for (cself = 1; table[player->y + cself][player->x - cself] != playerSymb && player->y + cself < tableSize && player->x - cself > 0; ++cself);
            for (cempty = 1; table[player->y + cself][player->x - cself] != '.' && player->y + cempty < tableSize && player->x - cempty > 0; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        //sag uste dogru kontrol
        if (table[player->y - 1][player->x + 1] == targetSymb) {
            cself = 0;
            cempty = 0;
            for (cself = 1; table[player->y - cself][player->x + cself] != playerSymb && player->y - cself > 0 && player->x + cself < tableSize; ++cself);
            for (cempty = 1; table[player->y - cself][player->x + cself] != '.' && player->y - cempty > 0 && player->x + cempty < tableSize; ++cempty);

            if (cempty < cself)
                currPts += cempty;
        }

        player->valueMove = currPts;

    }

    if (currPts != 0) {
        validPlayerMove = 1;
    }

    return validPlayerMove;
}