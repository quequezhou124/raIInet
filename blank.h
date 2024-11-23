#ifndef BLANK_H
#define BLANK_H
#include "board.h"

class Blank: public Board {
    char unitAt(int col, int row) { return '.'; }
    ~Blank() = default;
};

#endif
