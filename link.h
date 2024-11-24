#ifndef LINK_H
#define LINK_H
#include"unit.h"
#include <string>

class Player;
class Link: public Unit {
  protected:
    Link (int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked);
  public:
    int getStrength() override;
    void setStrength(int strength, int row, int col) override;
    bool setrow(int row) override;
    bool setcol(int col) override;
    virtual std::string getType () = 0;
    virtual ~Link() = default;
};

#endif
