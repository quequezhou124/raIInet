#ifndef BOARD_H
#define BOARD_H
#include "unit.h"
#include <iostream>
#include <vector>

using namespace std;

class Unit;

class Board {
  public:
    vector<Unit*> units;
    Unit* find_unit (char name) {
        for (auto *unit : units) {
            if (unit->getName() == name) return unit;
        }
        return nullptr;
    }
    Unit* getUnit(int row, int col) { 
        for (Unit* unit : units) {
            if (unit->getRow() == row && unit->getCol() == col) {
                return unit;
            }
        }
        return nullptr; 
    }
    virtual char unitAt(int row, int col) = 0;
    virtual ~Board() = default;
};

#endif
