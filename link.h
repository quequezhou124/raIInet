#include"unit.h"

class Link: public Unit {
    int strength;
    Player* owner;
    bool displayed;
    bool doublespeed;
    bool locked;
  protected:
    Link (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
  public:
    int getStrength() override {};
    void setStrength(int strength, int row, int col) override {};
    void setrow(int row) override {};
    void setcol(int col) override {};
    virtual ~Link() = default;
};
