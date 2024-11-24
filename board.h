#ifndef BOARD_H
#define BOARD_H
#include "unit.h"
#include "player.h"
#include <iostream>
#include <vector>

using namespace std;

class Unit;

class Board {
  public:
    vector<Unit*> units;

    Board (vector<Unit*> units) : units{units} {}
    Board () : units{} {}
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

    Unit* getAnotherUnit(int row, int col, Unit* link, Player* player) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col && link != unit && std::find(player->links.begin(), player->links.end(), unit) == player->links.end()) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    char unitAt(int row, int col) {
        Unit* unit = getUnit(row, col);
        if (unit) {
            return unit->getName();
        } else {
            return '.';  // Or any other character for empty cells
        }
    }

    ~Board() = default;
};

#endif
