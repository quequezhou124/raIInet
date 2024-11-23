#include "decorator.h"
#include "virus.h"
class VirusDecorator: public Decorator {
    char unitAt(int row, int col) override {
        char temp = theBoard->unitAt(row, col);
        Unit* unit = getUnit(row, col);
        if (dynamic_cast<Virus*>(unit)) {
            return unit->getName();
        } else {
            return '.';
        }
    }
};
