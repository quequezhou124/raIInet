#ifndef UNIT_H
#define UNIT_H
#include <iostream>

class Unit {
  protected:
    int row;
    int col;
    int strength;
    char name;
    bool displayed;
    bool doublespeed;
    bool locked;
  public:
    Unit(int row, int col, int strength, char name, bool displayed = false, bool doublespeed = false, bool locked = false);
    char getName() const { return name; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    virtual int getStrength() = 0;
    virtual std::string getType () = 0;
    virtual void setStrength(int strength, int row, int col) = 0;
    virtual void setrow(int row) = 0;
    virtual void setcol(int col) = 0;
    virtual ~Unit() = default;
};

#endif
