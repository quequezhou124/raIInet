#include"link.h"

class Data: public Link {
    int strength;
  public:
    Data (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
};