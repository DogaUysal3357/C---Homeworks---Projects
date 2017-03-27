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
    Cell(int _y, std::string _x, char _owner);
    void setX();
    void setY();
    void setOwner(char _owner);
    void setAlive(bool _alive);
    char getOwner() const;
    bool getAlive() const;

private:
    int y;
    std::string x;
    char owner;
    bool alive;
};

#endif	/* CELL_H */

