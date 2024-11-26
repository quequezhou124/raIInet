#include"wall.h"
#include"link.h"
Wall::Wall(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked, bool downloaded) : 
    Unit{row, col, strength, name, displayed, doublespeed, locked, downloaded} {}

int Wall::getStrength() { return strength; }

void Wall::setStrength(int strength, int row, int col) { this->strength = strength; }

bool Wall::setrow(int row) { 
    if (row >= 0 && row <= 7) {
        this->row = row; 
        return true;
    } else {
        return false;
    }
}

bool Wall::setcol(int col) {
    if (col >= 0 && col <= 7) {
        this->col = col;
        return true;
    } else {
        return false;
    }
}
