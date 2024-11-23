#ifndef UNIT_H
#define UNIT_H
#include"player.h"
#include <iostream>

class Unit {
  protected:
    int row;
    int col;
    int strength;
    char name;
  public:
    Unit(int row, int col, int strength, char name);
    char getName() const { return name; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    virtual int getStrength() = 0;
    virtual std::string getType ();
    virtual void setStrength(int strength, int row, int col) = 0;
    virtual void setrow(int row) = 0;
    virtual void setcol(int col) = 0;
    virtual ~Unit() = default;
};

#endif
