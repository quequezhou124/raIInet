#include "player.h"
#include "board.h"

    Unit* Board::find_unit(char name) {
        for (auto& unit : units) {
            if (unit->getName() == name && unit->getDownloaded()==false) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Unit* Board::getUnit(int row, int col) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Unit* Board::getAnotherUnit(int row, int col, Unit* link, Player* player) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col && link != unit && std::find(player->links.begin(), player->links.end(), unit) == player->links.end()) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    char Board::unitAt(int row, int col) {
        Unit* unit = getUnit(row, col);
        if (unit) {
            return unit->getName();
        } else {
            return '.';  // Or any other character for empty cells
        }
    }