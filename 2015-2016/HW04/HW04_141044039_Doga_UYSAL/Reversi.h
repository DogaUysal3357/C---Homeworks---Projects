/* 
 * File:   ReversiAndClass.h
 * Author: Doğa
 *
 * Created on 10 Kasım 2015 Salı, 12:57
 */

#ifndef REVERSI_H
#define	REVERSI_H

#include <vector>
const int DEF_SIZE = 4;

class Cell;

class Reversi {
public:
    Reversi();
    Reversi(int _x);
    Reversi(int _x, int _y);
    int getTableX()const;
    int getTableY()const;
    void printSize() const;
    void playGame();
private:
    void setGameSize();
    void setTableX(int _x);
    void setTableY(int _y);
    bool endGame()const;
    std::vector< std::vector<Cell> > gameCells;
    void resizeGameCells(int x, int y);
    int tableSizeX;
    int tableSizeY;
};






#endif	/* REVERSI_H */

