#include"wall.h"
#include"link.h"
Wall::Wall(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked, bool downloaded) : 
    Unit{row, col, strength, name, displayed, doublespeed, locked, downloaded} {}
