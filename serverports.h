#ifndef SERVERPORTS_H
#define SERVERPORTS_H
#include"unit.h"
#include <string>

class Player;
class Serverports: public Unit {
  protected:
    Serverports (int row, int col, int strength, char name = 'S', bool displayed = false, bool doublespeed = false, bool locked = false, bool downloaded = false);
  public:
    int getStrength() override;
    void setStrength(int strength, int row, int col) override;
    bool setrow(int row) override;
    bool setcol(int col) override;
    std::string getType () override {return "S";}
    ~Serverports() = default;
};

#endif
