#include "virus.h"

Virus::Virus(int row, int col, int strength, char name, Player* owner, bool displayed = false, bool doublespeed = false, bool locked = false) : 
    Link{row, col, strength, name, owner, displayed, doublespeed, locked} {}
