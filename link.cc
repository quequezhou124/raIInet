#include "link.h"

Link::Link(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked) :
    Unit{row, col, strength, name}, displayed{displayed}, doublespeed{doublespeed}, locked{locked} {}

int Link::getStrength() { return strength; }

void Link::setStrength(int strength, int row, int col) { this->strength = strength; }

void Link::setrow(int row) { this->row = row; }

void Link::setcol(int col) { this->col = col; }
