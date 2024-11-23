#ifndef VIRUS_DECORATOR_H
#define VIRUS_DECORATOR_H
#include "decorator.h"
#include "virus.h"
class VirusDecorator: public Decorator {
    char unitAt(int row, int col) override {
        char temp = theBoard->unitAt(row, col);
        std::unique_ptr<Unit> unit = getUnit(row, col);
        if (dynamic_cast<Virus*>(unit.get())) {
            return unit->getName();
        } else {
            return '.';
        }
    }
};

#endif
