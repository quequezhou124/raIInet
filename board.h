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
    
    std::unique_ptr<Unit> find_unit (char name) {
        for (auto it = units.begin(); it != units.end(); ++it) {
            if ((*it)->getName() == name) {
                std::unique_ptr<Unit> result = std::move(*it);
                units.erase(it);
                return result;
            }
        }
        return nullptr;
    }

    std::unique_ptr<Unit> getUnit(int row, int col) {
        for (auto it = units.begin(); it != units.end(); ++it) {
            if ((*it)->getRow() == row && (*it)->getCol() == col) {
                std::unique_ptr<Unit> result = std::move(*it);
                units.erase(it);
                return result;
            }
        }
        return nullptr;
    }

    virtual char unitAt(int row, int col) = 0;
    virtual ~Board() = default;
};

#endif
