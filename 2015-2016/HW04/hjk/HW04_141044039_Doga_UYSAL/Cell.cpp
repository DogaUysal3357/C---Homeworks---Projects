/* 
 * File:   Cell.cpp
 * Author: Doğa
 * 
 * Created on 15 Kasım 2015 Pazar, 22:07
 */

#include "Cell.h"

int Cell::yStatic = 0;
std::string Cell::xStatic = "a";
int Cell::tableCounterX = 0;
int Cell::tableCounterY = 0;

Cell::Cell() {
    setY();
    setX();
    setOwner('.');
    setAlive(false);
}

void Cell::setX() {
    if (xStatic[xStatic.size() - 1] == 'z') {
        for (int i = 0; i <= xStatic.size() - 1; i++) {
            xStatic[i] = 'a';
        }
        xStatic + "a";
    }

    xStatic[xStatic.size() - 1]++;
    x = xStatic;
    tableCounterX++;
    if (tableCounterX == Reversi::getTableX() - 1) {
        setCounterXToZero();
        xStatic = "a";
    }
}

void Cell::setY() {
    y = yStatic;
    tableCounterY++;
    if (tableCounterY == Reversi::getTableY() - 1) {
        setCounterYToZero();
        yStatic++;
    }
}

void Cell::staticsToStart() {
    xStatic = "a";
    yStatic = 0;
}

void Cell::setCounterXToZero() {
    tableCounterX = 0;
}

void Cell::setCounterYToZero() {
    tableCounterY = 0;
}

void Cell::setOwner(char _owner) {
    owner = _owner;
}

void Cell::setAlive(bool _alive) {
    alive = _alive;
}

char Cell::getOwner() const {
    return owner;
}

std::string Cell::getX() const {
    return x;
}

bool Cell::getAlive() const {
    return alive;
}
