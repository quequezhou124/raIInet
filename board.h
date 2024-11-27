#ifndef BOARD_H
#define BOARD_H
#include "unit.h"
#include <iostream>
#include <vector>

using namespace std;

class Player;

class Board {
  public:
    vector<Unit*> units;

    Board (vector<Unit*> units) : units{units} {}
    Board () : units{} {}
    Unit* find_unit(char name);

    Unit* getUnit(int row, int col);

    Unit* getAnotherUnit(int row, int col, Unit* link, Player* player);

    char unitAt(int row, int col);

    bool setFirewall (Board *borad, Player *player, int row, int col, bool negate);

    ~Board() = default;
};

#endif
