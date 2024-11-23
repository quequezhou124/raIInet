#include"link.h"

class Data: public Link {
    int strength;
  public:
    Data (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
    int getStrength() override {};
    void setStrength(int strength, int row, int col) override {};
};
