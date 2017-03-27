/* 
 * File:   Cell.h
 * Author: Doğa
 *
 * Created on 15 Kasım 2015 Pazar, 22:07
 */

#ifndef CELL_H
#define	CELL_H

#include "Reversi.h"
#include <string>

class Cell {
public:
    Cell();
    void setX();
    void setY();
    void setOwner(char _owner);
    void setAlive(bool _alive);
    char getOwner() const;
    bool getAlive() const;
    std::string getX() const;
    static void staticsToStart();
private:
    int y;
    std::string x;
    static int yStatic;
    static std::string xStatic;
    static int tableCounterX;
    static int tableCounterY;
    static void setCounterXToZero();
    static void setCounterYToZero();
    char owner;
    bool alive;
};

#endif	/* CELL_H */

