#ifndef DECORATOR_H
#define DECORATOR_H

#include "board.h"

class Decorator: public Board {
  protected:
    Board* theBoard;
  public:
    Decorator(Board* board) : theBoard(board) {}
    char unitAt(int row, int col) override {
        return theBoard->unitAt(row, col);
    }
    virtual ~Decorator() { delete theBoard; }
};

#endif
