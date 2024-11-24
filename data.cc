#include "data.h"

Data::Data(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked, bool downloaded) : 
    Link{row, col, strength, name, displayed, doublespeed, locked, downloaded} {}
