#include"player.h"
#include <iostream>

class Unit {
    int row;
    int col;
    int strength;
    char name;
  protected:
    Unit(int row, int col, int strength, char name);
  public:
    char getName() const { return name; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    virtual int getStrength() {};
    virtual void setStrength(int strength, int row, int col) {};
    virtual ~Unit() = default;
};
