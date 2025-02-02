#ifndef WALL_H
#define WALL_H
#include"unit.h"

class Wall: public Unit {
    int strength;
  public:
    std::string getType () override { return "W"; }
    Wall (int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked, bool downloaded);
    int getStrength() override;
    void setStrength(int strength, int row, int col) override;
    bool setrow(int row) override;
    bool setcol(int col) override;
    ~Wall() = default;
};

#endif
