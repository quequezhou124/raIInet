#include "link.h"

const int side = 8;
Link::Link(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked) :
    Unit{row, col, strength, name, displayed, doublespeed, locked} {}

int Link::getStrength() { return strength; }

void Link::setStrength(int strength, int row, int col) { this->strength = strength; }

bool Link::setrow(int row) { 
    if (row >= 0 || row <= 7) {
        this->row = row;
        return true;
    } else {
        return false;
    }
}

bool Link::setcol(int col) {
    if (col >= 0 || col <= 7) {
        this->col = col;
        return true;
    } else {
        return false;
    }
}
