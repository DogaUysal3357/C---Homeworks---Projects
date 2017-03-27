/* 
 * File:   Cell.cpp
 * Author: Doğa
 * 
 * Created on 15 Kasım 2015 Pazar, 22:07
 */

#include "Cell.h"

Cell::Cell() {
    setY(0);
    setX("a");
    setOwner('.');
    setAlive(false);
}

Cell::Cell(int _y, std::string _x, char _owner){
    setY(_y);
    setX(_x);
    setOwner(_owner);
    setAlive(true);    
}
void Cell::setX( std::string _x) {
    x=_x;
}

void Cell::setY(int _y) {
    y=_y;
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

bool Cell::getAlive() const {
    return alive;
}
