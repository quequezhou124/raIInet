#include "decorator.h"

class DataDecorator: public Decorator {
    char unitAt(int row, int col) override {
        char temp = theBoard->unitAt(row, col);
        Unit* unit = getUnit(row, col);
        if (unit) {
            return unit->getName();
        }
        return '.';
    }
};
