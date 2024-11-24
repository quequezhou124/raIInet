#include "serverports.h"

Serverports::Serverports(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked, bool downloaded) :
    Unit{row, col, strength, name, displayed, doublespeed, locked, downloaded} {}

int Serverports::getStrength() { return strength; }

void Serverports::setStrength(int strength, int row, int col) { this->strength = strength; }

bool Serverports::setrow(int row) { 
    if (row == 0) {
        this->row = row;
        return true; 
    } else if (row == 7) {
        this->row = row;
        return true; 
    } else {
        return false;
    }
}

bool Serverports::setcol(int col) {
    if (col == 3) {
        this->col = col;
        return true; 
    } else if (col == 4) {
        this->col = col;
        return true; 
    } else {
        return false;
    }
}
