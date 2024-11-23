#include "data.h"

Data::Data(int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked) : 
    Link{row, col, strength, name, owner, displayed, doublespeed, locked} {}

int Data::getStrength() { return strength; }

void Data::setStrength(int strength, int row, int col) { this->strength = strength; }
