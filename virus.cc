#include "virus.h"

Virus::Virus(int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked) : 
    Link{row, col, strength, name, owner, displayed, doublespeed, locked} {}