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
    
    Unit* find_unit(char name) {
        for (auto& unit : units) {
            if (unit->getName() == name) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Unit* getUnit(int row, int col) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Unit* getAnotherUnit(int row, int col, Unit* link) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col && link != unit) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    virtual char unitAt(int row, int col) = 0;
    virtual ~Board() = default;
};

#endif
