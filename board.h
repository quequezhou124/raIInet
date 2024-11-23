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
    
    std::unique_ptr<Unit> find_unit(char name) {
        for (auto& unit : units) {
            if (unit->getName() == name) {
                return std::unique_ptr<Unit>(unit.get());  // Create a new unique_ptr from raw pointer
            }
        }
        return nullptr; // Return nullptr if not found
    }

    std::unique_ptr<Unit> getUnit(int row, int col) {
        for (auto& unit : units) {
            if (unit->getRow() == row, unit->getCol() == col) {
                return std::unique_ptr<Unit>(unit.get());  // Create a new unique_ptr from raw pointer
            }
        }
        return nullptr; // Return nullptr if not found
    }

    virtual char unitAt(int row, int col) = 0;
    virtual ~Board() = default;
};

#endif
