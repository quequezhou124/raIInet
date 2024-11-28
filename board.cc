#include "player.h"
#include "board.h"
#include "serverports.h"
#include "wall.h"
#include <algorithm>

    Unit* Board::find_unit(char name) {
        for (auto& unit : units) {
            if (unit->getName() == name) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Unit* Board::getUnit(int row, int col) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col && !unit->getDownloaded()) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Unit* Board::getAnotherUnit(int row, int col, Unit* link, Player* player) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col && link != unit && !(std::find(player->links.begin(), player->links.end(), unit) == player->links.end())) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }

    char Board::unitAt(int row, int col) {
        Unit* unit = getUnit(row, col);
        if (unit && unit->getType() == "W") return '.';
        if (unit && unit->getType() == "S") return 'S';
        if (unit && !unit->getDownloaded()) {
            return unit->getName();
        } else {
            return '.';  // Or any other character for empty cells
        }
    }

    bool Board::setFirewall (Board *borad, Player *player, int row, int col, bool negate) {
        if (negate) {
            std::cout << "your opponent has used negate" << std::endl; 
            return true;
        } else if (row < 0 || row > 8 || col < 0 || col > 8 || 
                   (getUnit(row, col) && getUnit(row, col)->getType() != "W") || (row == 0 && (col == 3 || col == 4)) ||
                   (row == 7 && (col == 3 || col == 4))) {
            return false;
        } else {
            if (player->isplayer1turn()) {
                Wall * firewall = new Wall {row, col, 0, 'w', false, false, false, false};
                borad->units.push_back(firewall);
                player->walls.push_back(firewall);
            }

            else {
                Wall * firewall = new Wall {row, col, 0, 'm', false, false, false, false};
                borad->units.push_back(firewall);
                player->walls.push_back(firewall);
            }

            return true;
        }
    }

    Unit* Board::getFirewall(int row, int col, Player *player) {
        for (auto& unit : units) {
            if (unit->getRow() == row && unit->getCol() == col && unit->getType() == "W" && std::find(player->walls.begin(), player->walls.end(), unit) != player->walls.end()) {
                return unit;
            }
        }
        return nullptr; // Return nullptr if not found
    }
    