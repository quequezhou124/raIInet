#include"link.h"

class Virus: public Link {
    int strength;
    Virus (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
  public:
    int getStrength() override {};
    void setStrength(int strength, int row, int col) override {};
};
