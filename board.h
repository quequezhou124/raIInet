#include "unit.h"
#include <iostream>
#include <vector>

using namespace std;

class Unit;

class Board {
  public:
    vector<Unit*> units;
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
