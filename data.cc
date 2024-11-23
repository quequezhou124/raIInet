#include "data.h"

Data::Data(int row, int col, int strength, char name, bool displayed = false, bool doublespeed = false, bool locked = false) : 
    Link{row, col, strength, name, displayed, doublespeed, locked} {}
