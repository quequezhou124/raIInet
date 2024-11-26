#ifndef POLARIZEABILITY_H
#define POLARIZEABILITY_H

#include "link.h"
#include "player.h"
#include <vector>
#include "data.h"
#include "virus.h"

class polarizeAbility{
    public:
    bool useAbility(char linkname, Board *board) {
        Unit *cur = board->find_unit(linkname);
        int row = cur->getRow();
        int col = cur->getCol();
        int strength = cur->getStrength();
        char name = cur->getName();
        bool displayed = cur->getDisplayed();
        bool doublespeed = cur->getDoublespeed();
        bool locked = cur->getLocked();
        bool downloaded = cur->getDownloaded();
        for (auto& unit : board->units) {
            if ((unit->getName() == linkname) && (unit->getDownloaded()== false)) {
                Unit* oldUnit = unit;
                if (unit->getType()== "V") {
                    unit = new Data(row, col, strength, name, displayed, doublespeed, locked, downloaded);  
                } else if (unit->getType()== "D") {
                    unit = new Virus(row, col, strength, name, displayed, doublespeed, locked, downloaded);
                }
                delete oldUnit;
                return true;
            }
        }
        std::cout<<"this link is not on the board or it has been downlownded."<< endl;
        return false;
    }
};

#endif
