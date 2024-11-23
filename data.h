#ifndef DATA_H
#define DATA_H
#include"link.h"

class Data: public Link {
    int strength;
  public:
    Data (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
};

#endif
