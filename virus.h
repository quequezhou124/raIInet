#include"link.h"

class Virus: public Link {
    int strength;
  public:
    Virus (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
};
