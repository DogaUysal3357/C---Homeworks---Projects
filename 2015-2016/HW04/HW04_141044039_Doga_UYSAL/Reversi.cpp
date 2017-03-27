/* 
 * File:   ReversiAndClass.cpp
 * Author: Doğa
 * 
 * Created on 10 Kasım 2015 Salı, 12:57
 */

#include "Reversi.h"

Reversi::Reversi() {
    tableSizeX = DEF_SIZE;
    tableSizeY = DEF_SIZE;
    resizeGameCells(tableSizeY);
}

Reversi::Reversi(int _x) {
    tableSizeX = _x;
    tableSizeY = DEF_SIZE;
    resizeGameCells(tableSizeY);
}

Reversi::Reversi(int _x, int _y) {
    tableSizeX = _x;
    tableSizeY = _y;
    resizeGameCells(tableSizeY);
}

int Reversi::getTableX() const {
    return tableSizeX;
}

int Reversi::getTableY() const {
    return tableSizeY;
}

void Reversi::setTableY(int _y) {
    tableSizeY = _y;
}

void Reversi::setTableX(int _x) {
    tableSizeX = _x;  
}

void Reversi::resizeGameCells(int y) {
    gameCells.resize(y);
}

void Reversi::setGameSize() {
    std::cout << "Oynamak istediginiz masa boyutunu giriniz (x, y):";
    std::cin << tableSizeX << tableSizeY;
    resizeGameCells(tableSizeY);
}

bool Reversi::endGame() const {
    bool end = false;

    for (int i = 0; i < getTableY(); i++) {
        if (gameCells[i].size() != tableSizeX);
        else
            end = true;
    }

    return end;
}

void Reversi::playGame() {
    setGameSize();

    while (!endGame()) {






    }
}

void Reversi::printSize() const {
    std::cout << "Width :" << tableSizeX << std::endl;
    std::cout << "Height :" << tableSizeY << std::endl << std::endl;
}




