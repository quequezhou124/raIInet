#ifndef BOARD_H
#define BOARD_H
#include "unit.h"
#include <iostream>
#include <vector>

using namespace std;

class Unit;

class Board {
  public:
    vector<std::unique_ptr<Unit>> units;
    Unit* find_unit (char name) {
        for (auto& unit : units) {
            if (unit->getName() == name) return unit.get();
        }
        return nullptr;
    }
    Unit* getUnit(int row, int col) { 
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col) {
                return unit.get();
            }
        }
        return nullptr; 
    }
    virtual char unitAt(int row, int col) = 0;
    virtual ~Board() = default;
};

#endif
