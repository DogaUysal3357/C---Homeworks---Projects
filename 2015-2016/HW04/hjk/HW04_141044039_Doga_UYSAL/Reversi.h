/* 
 * File:   ReversiAndClass.h
 * Author: Doğa
 *
 * Created on 10 Kasım 2015 Salı, 12:57
 */

#ifndef REVERSI_H
#define	REVERSI_H

#include <vector>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>

const int DEF_SIZE = 6;
const std::string QUIT_PLAY = "-1";
const char USER_SYMB = 'O';
const char PC_SYMB = 'X';
const char EMPTY = '.';
const int DIFF_A_TO_Z = 26;

class Cell;

class Reversi {
public:
    Reversi();
    Reversi(int _x);
    Reversi(int _x, int _y);
    static int getTableX();
    static int getTableY();
    void printSize() const;
    void playGame();
private:
    void printTable() const;
    void saveGame();
    void loadGame();
    void setGameSize();
    void setTableX(int _x);
    void setTableY(int _y);
    void setChoice(char _c);
    void setUserXInt(int _x);
    char getChoice() const;
    void setFileNo();
    int getFileNo() const;
    bool endGame(bool user, bool pc);
    std::string getUserX() const;
    int getUserY() const;
    int getUserXInt() const;
    void setUserX();
    void setUserY();
    void resizeGameCells(int x, int y);
    void play();
    bool play(int userX, int userY);
    void changeTable(int x, int y, char owner, char target);
    bool checkLegalMove(char player, char taget);
    int countOwnerScore (char x);

    std::vector< std::vector<Cell> > gameCells;
    static int tableSizeX;
    static int tableSizeY;
    int fileNo;
    char choice;
    std::string userX;
    int userXInt;
    int userY;
};






#endif	/* REVERSI_H */

