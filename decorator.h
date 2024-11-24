#ifndef DECORATOR_H
#define DECORATOR_H

#include "board.h"

class Decorator: public Board {
  protected:
    Board* theBoard;
  public:
    Decorator(Board* board) : theBoard(board) {
        units = board->units;  // Copy the units from the underlying board
    }
    char unitAt(int row, int col) override {
      Unit *unit = theBoard->getUnit(row, col);
      char unitat = unit->getName();
      return unitat;
    }
    
    virtual ~Decorator() { delete theBoard; }
};

#endif
