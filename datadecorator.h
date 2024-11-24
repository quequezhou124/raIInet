#ifndef DATA_DECORATOR_H
#define DATA_DECORATOR_H

#include "decorator.h"
#include "data.h"

class DataDecorator: public Decorator {
    char unitAt(int row, int col) override {
        char temp = theBoard->unitAt(row, col);
        Unit* unit = getUnit(row, col);
        if (dynamic_cast<Data*>(unit)) {
            return unit->getName();
        } else {
            return '.';
        }
    }
};

#endif
