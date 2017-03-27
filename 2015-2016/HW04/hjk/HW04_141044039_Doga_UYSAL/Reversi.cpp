/* 
 * File:   ReversiAndClass.cpp
 * Author: Doğa
 * 
 * Created on 10 Kasım 2015 Salı, 12:57
 */

#include "Reversi.h"
#include "Cell.h"

int Reversi::tableSizeX = DEF_SIZE;
int Reversi::tableSizeY = DEF_SIZE;

Reversi::Reversi() {
    setTableX(DEF_SIZE);
    setTableY(DEF_SIZE);
    resizeGameCells(getTableX(), getTableY());
}

Reversi::Reversi(int _x) {
    setTableX(_x);
    setTableY(DEF_SIZE);
    resizeGameCells(getTableX(), getTableY());
}

Reversi::Reversi(int _x, int _y) {
    setTableX(_x);
    setTableY(_y);
    resizeGameCells(getTableX(), getTableY());
}

int Reversi::getTableX() {
    return tableSizeX;
}

int Reversi::getTableY() {
    return tableSizeY;
}

char Reversi::getChoice() const {
    return choice;
}

int Reversi::getFileNo() const {
    return fileNo;
}

std::string Reversi::getUserX() const {
    return userX;
}

int Reversi::getUserXInt() const {
    return userXInt;
}

int Reversi::getUserY() const {
    return userY;
}

void Reversi::setUserXInt(int _x) {
    userXInt = _x;
}

void Reversi::setTableY(int _y) {
    tableSizeY = _y;
}

void Reversi::setTableX(int _x) {
    tableSizeX = _x;
}

void Reversi::setChoice(char _c) {
    choice = _c;
}

void Reversi::setFileNo() {
    std::cout << " Uzerinde islem yapmak istediginiz oyun numarasini seciniz (1-2-3-4-5) : \n";
    int temp;
    std::cin >> temp;
    fileNo = temp;
}

void Reversi::setUserX() {
    bool flag = true;

    while (flag) {
        std::cout << "Oynayacaginiz X degerini giriniz :";
        std::cin >> userX;
        std::cin.clear();
        std::cin.ignore(80, '\n');

        if (getUserX() != QUIT_PLAY) {
            for (int i = 0; i <= userX.size() - 1; i++) {
                userX[i] = tolower(userX[i]);
            }

            for (int i = 0; i <= userX.size() - 1; i++) {
                if (!(isalpha(userX[i])));
                flag = false;
            }

            int strToInt = 0;
            for (int i = 0; i <= userX.size() - 1; i++) {

                strToInt += ((int) userX[userX.size() - i]-(int) 'a') *(i * DIFF_A_TO_Z);
            }

            setUserXInt(strToInt);

            if (strToInt > getTableX())
                flag = false;

            if (flag == false)
                std::cout << "Gecerli bir X degeri girmediniz." << std::endl;
        }
    }
}

void Reversi::setUserY() {
    bool flag = true;

    while (flag) {
        std::cin >> userY;
        if (userY > getTableY()) {
            std::cout << "Masa disinda bir nokta oynadiniz." << std::endl;
            flag = false;
        }
    }
}

/* Staticleri resetleyip yeni bir vector <vector cell> olusturur. İcini dogru 
 * sekilde doldurduktan sonra ve gameCells'de resize edildikten sonra
 *  gameCells'e kopyalama yapilir. */
void Reversi::resizeGameCells(int x, int y) {

    Cell::staticsToStart();
    std::vector< std::vector<Cell> > temp;

    temp.resize(y);
    for (int i = 0; i < y; i++)
        temp[i].resize(x);

    gameCells.resize(y);
    for (int i = 0; i < y; i++)
        gameCells[i].resize(x);

    gameCells = temp;

    int startX = (getTableX() / 2) + 1;
    int startY = (getTableY() / 2) + 1;
    gameCells[startY - 1][startX - 1].setOwner(PC_SYMB);
    gameCells[startY - 1][startX ].setOwner(USER_SYMB);
    gameCells[startY ][startX ].setOwner(PC_SYMB);
    gameCells[startY ][startX - 1].setOwner(USER_SYMB);
}

/* Kullanicidan input alarak oyun masasini yeniden boyutlandirir */
void Reversi::setGameSize() {
    std::cout << "Oynamak istediginiz masa boyutunu giriniz (x, y):";
    int x, y;
    std::cin >> x >> y;
    setTableX(x);
    setTableY(y);
    resizeGameCells(getTableX(), getTableY());
}

/* 2 tarafinda oynanabilir hamlesi olup olmama durumunu alarak sonuca gore oyunu sonlandirir*/
bool Reversi::endGame(bool userLegal, bool pcLegal) {
    bool end = false;
    int countUser = 0;
    int countPc = 0;

    if (userLegal == false && pcLegal == false)
        end = true;

    if (end == false) {
        std::cout << "Iki tarafinda oynayacak hamlesi kalmamis ve oyun sonlanmistir. " << std::endl;
        countUser = countOwnerScore(USER_SYMB);
        countPc = countOwnerScore(PC_SYMB);

        std::cout << "Sizin aldiginiz tas sayisi : " << countUser << std::endl;
        std::cout << "Bilgisayarin aldigi tas sayisi : " << countPc <<std::endl;
        
        std::cout << "Oyunun kazanani " ;
        if(countUser > countPc)
            std::cout << " Sizsiniz" << std::endl;
        else
            std::cout << "Bilgisayar" << std::endl;
    }

    return end;
}

int Reversi::countOwnerScore(char owner) {

    int x = 0, y = 0;
    int count = 0;
    for (y = 0; y < getTableY(); y++)
        for (x = 0; x < getTableX(); x++) {
            gameCells[y][x].getOwner() == owner;
            count++;
        }

    return count;
}

/* Dosya numarasini alarak o dosyaya masayi kaydeder.*/
void Reversi::saveGame() {

    std::ofstream s_file;
    std::string fileName;


    switch (getFileNo()) {

        case 1:
            fileName = "game_1.txt";
            break;
        case 2:
            fileName = "game_2.txt";
            break;
        case 3:
            fileName = "game_3.txt";
            break;
        case 4:
            fileName = "game_4.txt";
            break;
        case 5:
            fileName = "game_5.txt";
            break;
    }

    s_file.open(fileName.c_str());

    s_file << tableSizeX << ' ' << tableSizeY << std::endl;

    for (int i = 0; i < tableSizeY; i++) {
        for (int k = 0; k < tableSizeX; i++) {
            s_file << gameCells[i][k].getOwner() << ' ';
        }
        s_file << std::endl;
    }
    s_file.close();
}

/*Dosya numarasini alarak o dosyadaki oyunu, guncel oyuna cevirir.*/
void Reversi::loadGame() {

    std::ifstream l_file;
    std::string fileName;

    switch (getFileNo()) {

        case 1:
            fileName = "game_1.txt";
            break;
        case 2:
            fileName = "game_2.txt";
            break;
        case 3:
            fileName = "game_3.txt";
            break;
        case 4:
            fileName = "game_4.txt";
            break;
        case 5:
            fileName = "game_5.txt";
            break;
    }

    l_file.open(fileName.c_str());


    int tempx, tempy;
    l_file >> tempx >> tempy;

    setTableX(tempx);
    setTableY(tempy);

    resizeGameCells(getTableX(), getTableY());

    char temp;

    l_file.get(temp);

    while (!l_file.eof()) {
        for (int i = 0; i < tableSizeY; i++) {
            for (int k = 0; k < tableSizeX; k++) {
                l_file.get(temp);
                gameCells[i][k].setOwner(temp);
                if (temp != '.')
                    gameCells[i][k].setAlive(true);
                l_file.get(temp);
            }
            l_file.get(temp);
        }
    }


    l_file.close();
}

/*Oyunun oynandigi dongulerin oldugu fonksyondur.*/
void Reversi::playGame() {
    bool userCheck = true;
    char temp = 'p';
    bool userLegalMove = true;
    bool pcLegalMove = true;

    while (choice != 'e' || choice != 'E') {

        std::cout << "Yapmak istediginiz islem icin gecerli karakteri giriniz :\n"
                << "S : Oyunu Kaydetmek icin" << std::endl
                << "L : Kayitli oyunu yuklemek icin" << std::endl
                << "P : Oyunu oynamak icin" << std::endl
                << "E : Cikis icin" << std::endl;

        std::cin >> temp;
        setChoice(temp);
        std::cin.clear();
        std::cin.ignore(80, '\n');

        switch (getChoice()) {
            case 's':
            case 'S':
                setFileNo();
                saveGame();
                break;
            case 'l':
            case 'L':
                setFileNo();
                loadGame();
                break;
            case 'p':
            case 'P':
                while (!endGame(userLegalMove, pcLegalMove) || getUserX() != QUIT_PLAY) {
                    while (getUserX() != QUIT_PLAY) {
                        while (!userCheck) {
                            userLegalMove = checkLegalMove(USER_SYMB, PC_SYMB);
                            if (userLegalMove == false)
                                std::cout << "Oynayacak hamleniz bulunmamaktadir" << std::endl;
                            if (userLegalMove == true) {
                                std::cout << "Cikmak icin -1 giriniz. " << std::endl;
                                setUserX();
                                if (getUserX() != QUIT_PLAY) {
                                    setUserY();
                                    userCheck = play(getUserXInt(), getUserY());
                                }
                            }
                            if (getUserX() != QUIT_PLAY) {
                                pcLegalMove = checkLegalMove(PC_SYMB, USER_SYMB);
                                if (pcLegalMove == false)
                                    std::cout << " Pc'nin oynayacak hamlesi bulunmamaktadir" << std::endl;
                                if (pcLegalMove == true)
                                    play();
                            }
                        }
                    }
                }
                break;

            case 'e':
            case 'E': break;

            default:
                std::cout << " Gecerli bir karakter girmediniz..! \n";
                break;
        }

    }

}

/* Gecerli bir hamle olup olmadigini kontrol eden fonksyondur*/
bool Reversi::checkLegalMove(char player, char target) {
    int x = 0, y = 0;
    int cself = 0; // playerSymb bulana sayim yapar
    int cempty = 0; // '.' bulunana kadar sayim yapar
    char targetSymb = target;
    char playerSymb = player;
    int currPts = 0, tempPts = 0; // oynanan hamle ile kac tas alindigini sayan sayac
    bool legalMove = true;

    for (y = 0; y < getTableY(); ++y)
        for (x = 0; x < getTableX(); ++x) {

            //saga kontrol
            if (gameCells[y][x + 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y][x + cself].getOwner() != playerSymb && x + cself < getTableX(); ++cself);
                for (cempty = 1; gameCells[y][x + cempty].getOwner() != EMPTY && x + cempty < getTableX(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sola kontrol
            if (gameCells[y][x - 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y][x - cself].getOwner() != playerSymb && x - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y][x - cempty].getOwner() != EMPTY && x - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //yukari kontrol
            if (gameCells[y - 1][x].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y - cself][x].getOwner() != playerSymb && y - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y - cself][x].getOwner() != '.' && y - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //asagi kontrol
            if (gameCells[y + 1][x].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y + cself][x].getOwner() != playerSymb && y + cself < getTableY(); ++cself);
                for (cempty = 1; gameCells[y + cself][x].getOwner() != EMPTY && y + cempty < getTableY(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sag alt capraza dogru kontrol
            if (gameCells[y + 1][x + 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y + cself][x + cself].getOwner() != playerSymb && y + cself < getTableY() && x + cself < getTableX(); ++cself);
                for (cempty = 1; gameCells[y + cself][x + cself].getOwner() != EMPTY && y + cempty < getTableY() && x + cempty < getTableX(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            // sol ust tarafa dogru kontrol
            if (gameCells[y - 1][x - 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y - cself][x - cself].getOwner() != playerSymb && y - cself >= 0 && x - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y - cself][x - cself].getOwner() != EMPTY && y - cempty >= 0 && x - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sol alt capraza dogru kontrol
            if (gameCells[y + 1][x - 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y + cself][x - cself].getOwner() != playerSymb && y + cself < getTableY() && x - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y + cself][x - cself].getOwner() != EMPTY && y + cempty < getTableY() && x - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sag uste dogru kontrol
            if (gameCells[y - 1][x + 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y - cself][x + cself].getOwner() != playerSymb && y - cself >= 0 && x + cself < getTableX(); ++cself);
                for (cempty = 1; gameCells[y - cself][x + cself].getOwner() != EMPTY && y - cempty >= 0 && x + cempty < getTableX(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            if (tempPts > currPts) {
                currPts = tempPts;
            }
        }

    if (currPts == 0)
        legalMove = false;

    return legalMove;
}

/* Bilgisayarin hamlesinin hesaplanip oynandigi fonksyondur*/
void Reversi::play() {
    int x = 0, y = 0, tempX = 0, tempY = 0;
    int cself = 0; // playerSymb bulana sayim yapar
    int cempty = 0; // '.' bulunana kadar sayim yapar
    char targetSymb = USER_SYMB;
    char playerSymb = PC_SYMB;
    int currPts = 0, tempPts = 0; // oynanan hamle ile kac tas alindigini sayan sayac


    for (y = 0; y < getTableY(); ++y)
        for (x = 0; x < getTableX(); ++x) {

            //saga kontrol
            if (gameCells[y][x + 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y][x + cself].getOwner() != playerSymb && x + cself < getTableX(); ++cself);
                for (cempty = 1; gameCells[y][x + cempty].getOwner() != EMPTY && x + cempty < getTableX(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sola kontrol
            if (gameCells[y][x - 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y][x - cself].getOwner() != playerSymb && x - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y][x - cempty].getOwner() != EMPTY && x - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //yukari kontrol
            if (gameCells[y - 1][x].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y - cself][x].getOwner() != playerSymb && y - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y - cself][x].getOwner() != '.' && y - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //asagi kontrol
            if (gameCells[y + 1][x].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y + cself][x].getOwner() != playerSymb && y + cself < getTableY(); ++cself);
                for (cempty = 1; gameCells[y + cself][x].getOwner() != EMPTY && y + cempty < getTableY(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sag alt capraza dogru kontrol
            if (gameCells[y + 1][x + 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y + cself][x + cself].getOwner() != playerSymb && y + cself < getTableY() && x + cself < getTableX(); ++cself);
                for (cempty = 1; gameCells[y + cself][x + cself].getOwner() != EMPTY && y + cempty < getTableY() && x + cempty < getTableX(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            // sol ust tarafa dogru kontrol
            if (gameCells[y - 1][x - 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y - cself][x - cself].getOwner() != playerSymb && y - cself >= 0 && x - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y - cself][x - cself].getOwner() != EMPTY && y - cempty >= 0 && x - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sol alt capraza dogru kontrol
            if (gameCells[y + 1][x - 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y + cself][x - cself].getOwner() != playerSymb && y + cself < getTableY() && x - cself >= 0; ++cself);
                for (cempty = 1; gameCells[y + cself][x - cself].getOwner() != EMPTY && y + cempty < getTableY() && x - cempty >= 0; ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            //sag uste dogru kontrol
            if (gameCells[y - 1][x + 1].getOwner() == targetSymb) {
                for (cself = 1; gameCells[y - cself][x + cself].getOwner() != playerSymb && y - cself >= 0 && x + cself < getTableX(); ++cself);
                for (cempty = 1; gameCells[y - cself][x + cself].getOwner() != EMPTY && y - cempty >= 0 && x + cempty < getTableX(); ++cempty);

                if (cempty < cself)
                    tempPts += cempty;
            }

            if (tempPts > currPts) {
                currPts = tempPts;
                tempX = x;
                tempY = y;
            }
        }

    if (currPts == 0) {
        std::cout << "Makinanin oynayabilecegi gecerli bir hamle bulunmamaktadir." << std::endl;
    } else {
        changeTable(tempX, tempY, PC_SYMB, USER_SYMB);
    }

    // printTable();
}

/* Oyuncunun hamlesinin alinip, oynadigi hamlenin gecerli olup olmadiginin bakildi,
 * gecerli ise oynandigi fonksyondur */
bool Reversi::play(int userX, int userY) {

    int x = userX, y = userY;
    int cself = 0; // playerSymb bulana sayim yapar
    int cempty = 0; // '.' bulunana kadar sayim yapar
    char targetSymb = PC_SYMB;
    char playerSymb = USER_SYMB;
    int currPts = 0, tempPts = 0; // oynanan hamle ile kac tas alindigini sayan sayac
    bool moveCheck = true;

    //saga kontrol
    if (gameCells[y][x + 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y][x + cself].getOwner() != playerSymb && x + cself < getTableX(); ++cself);
        for (cempty = 1; gameCells[y][x + cempty].getOwner() != EMPTY && x + cempty < getTableX(); ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    //sola kontrol
    if (gameCells[y][x - 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y][x - cself].getOwner() != playerSymb && x - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y][x - cempty].getOwner() != EMPTY && x - cempty >= 0; ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    //yukari kontrol
    if (gameCells[y - 1][x].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y - cself][x].getOwner() != playerSymb && y - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y - cself][x].getOwner() != '.' && y - cempty >= 0; ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    //asagi kontrol
    if (gameCells[y + 1][x].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y + cself][x].getOwner() != playerSymb && y + cself < getTableY(); ++cself);
        for (cempty = 1; gameCells[y + cself][x].getOwner() != EMPTY && y + cempty < getTableY(); ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    //sag alt capraza dogru kontrol
    if (gameCells[y + 1][x + 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y + cself][x + cself].getOwner() != playerSymb && y + cself < getTableY() && x + cself < getTableX(); ++cself);
        for (cempty = 1; gameCells[y + cself][x + cself].getOwner() != EMPTY && y + cempty < getTableY() && x + cempty < getTableX(); ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    // sol ust tarafa dogru kontrol
    if (gameCells[y - 1][x - 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y - cself][x - cself].getOwner() != playerSymb && y - cself >= 0 && x - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y - cself][x - cself].getOwner() != EMPTY && y - cempty >= 0 && x - cempty >= 0; ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    //sol alt capraza dogru kontrol
    if (gameCells[y + 1][x - 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y + cself][x - cself].getOwner() != playerSymb && y + cself < getTableY() && x - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y + cself][x - cself].getOwner() != EMPTY && y + cempty < getTableY() && x - cempty >= 0; ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    //sag uste dogru kontrol
    if (gameCells[y - 1][x + 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y - cself][x + cself].getOwner() != playerSymb && y - cself >= 0 && x + cself < getTableX(); ++cself);
        for (cempty = 1; gameCells[y - cself][x + cself].getOwner() != EMPTY && y - cempty >= 0 && x + cempty < getTableX(); ++cempty);

        if (cempty < cself)
            tempPts += cempty;
    }

    if (tempPts > currPts) {
        currPts = tempPts;
    }


    if (currPts == 0) {
        std::cout << "Gecerli bir hamle oynamadiniz." << std::endl;
        moveCheck = false;
    } else {
        changeTable(userX, userY, USER_SYMB, PC_SYMB);
        // printTable ();
    }

    return moveCheck;
}

/* Oynanan gecerli hamlelere gore masanin degistirildigi func*/
void Reversi::changeTable(int userX, int userY, char owner, char target) {

    int i = 0, k = 0;
    int x = userX, y = userY;
    int cself = 0; // playerSymb bulana sayim yapar
    int cempty = 0; // '.' bulunana kadar sayim yapar
    char targetSymb = target;
    char playerSymb = owner;
    int currPts = 0, tempPts = 0; // oynanan hamle ile kac tas alindigini sayan sayac


    gameCells[y][x].setOwner(owner);

    //saga kontrol
    if (gameCells[y][x + 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y][x + cself].getOwner() != playerSymb && x + cself < getTableX(); ++cself);
        for (cempty = 1; gameCells[y][x + cempty].getOwner() != EMPTY && x + cempty < getTableX(); ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y][x + i].getOwner() == targetSymb; ++i)
                gameCells[y][x + i].setOwner(playerSymb);
        }
    }

    //sola kontrol
    if (gameCells[y][x - 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y][x - cself].getOwner() != playerSymb && x - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y][x - cempty].getOwner() != EMPTY && x - cempty >= 0; ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y][x - i].getOwner() == targetSymb; ++i)
                gameCells[y][x - i].setOwner(playerSymb);
        }
    }

    //yukari kontrol
    if (gameCells[y - 1][x].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y - cself][x].getOwner() != playerSymb && y - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y - cself][x].getOwner() != '.' && y - cempty >= 0; ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y - i][x].getOwner() == targetSymb; ++i)
                gameCells[y - i][x].setOwner(playerSymb);
        }
    }

    //asagi kontrol
    if (gameCells[y + 1][x].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y + cself][x].getOwner() != playerSymb && y + cself < getTableY(); ++cself);
        for (cempty = 1; gameCells[y + cself][x].getOwner() != EMPTY && y + cempty < getTableY(); ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y + i][x].getOwner() == targetSymb; ++i)
                gameCells[y + i][x].setOwner(playerSymb);
        }
    }

    //sag alt capraza dogru kontrol
    if (gameCells[y + 1][x + 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y + cself][x + cself].getOwner() != playerSymb && y + cself < getTableY() && x + cself < getTableX(); ++cself);
        for (cempty = 1; gameCells[y + cself][x + cself].getOwner() != EMPTY && y + cempty < getTableY() && x + cempty < getTableX(); ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y + i][x + i].getOwner() == targetSymb; ++i)
                gameCells[y + i][x + i].setOwner(playerSymb);
        }
    }

    // sol ust tarafa dogru kontrol
    if (gameCells[y - 1][x - 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y - cself][x - cself].getOwner() != playerSymb && y - cself >= 0 && x - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y - cself][x - cself].getOwner() != EMPTY && y - cempty >= 0 && x - cempty >= 0; ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y - i][x - i].getOwner() == targetSymb; ++i)
                gameCells[y - i][x - i].setOwner(playerSymb);
        }
    }

    //sol alt capraza dogru kontrol
    if (gameCells[y + 1][x - 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y + cself][x - cself].getOwner() != playerSymb && y + cself < getTableY() && x - cself >= 0; ++cself);
        for (cempty = 1; gameCells[y + cself][x - cself].getOwner() != EMPTY && y + cempty < getTableY() && x - cempty >= 0; ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y + i][x - i].getOwner() == targetSymb; ++i)
                gameCells[y + i][x - i].setOwner(playerSymb);
        }
    }

    //sag uste dogru kontrol
    if (gameCells[y - 1][x + 1].getOwner() == targetSymb) {
        for (cself = 1; gameCells[y - cself][x + cself].getOwner() != playerSymb && y - cself >= 0 && x + cself < getTableX(); ++cself);
        for (cempty = 1; gameCells[y - cself][x + cself].getOwner() != EMPTY && y - cempty >= 0 && x + cempty < getTableX(); ++cempty);

        if (cempty > cself) {
            for (i = 1; gameCells[y - i][x + i].getOwner() == targetSymb; ++i)
                gameCells[y - i][x + i].setOwner(playerSymb);
        }
    }
}

/* Masayi ekrana basan func*/
void Reversi::printTable() const {

    int x = 0, y = 0;
    int strSpaceCount = 1;
    int strCountCheck = 1;
    int strCountLimit = DIFF_A_TO_Z;
    int intCountCheck;
    int intSpaceCount = 1;
    int intCountLimit = 10;
    int tempInt = getTableY() / intCountLimit;

    for (intCountCheck = 1; tempInt > intCountLimit; intCountCheck++) {
        tempInt /= intCountLimit;
    }

    std::cout << ' ';

    for (y = 0; y < getTableY(); y++) {
        for (x = 0; x < getTableX(); x++) {
            for (int i = 0; i < getTableX(); i++) {
                std::cout << gameCells[y][x].getOwner();
                for (int k = 0; k < strSpaceCount; k++)
                    std::cout << ' ';
                strCountCheck++;
                if (strCountCheck == strCountLimit) {
                    strCountCheck = 1;
                    strCountLimit *= DIFF_A_TO_Z;
                }
            }
        }
        std::cout << std::endl;
        std::cout << y + 1;
        for (int k = 0; k < intSpaceCount; k++)
            std::cout << ' ';
        intCountCheck++;
        if (intCountCheck == intCountLimit) {
            intCountLimit *= 10;
            intSpaceCount--;
        }
    }





}
