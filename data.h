#ifndef DATA_H
#define DATA_H
#include"link.h"

class Data: public Link {
    int strength;
  public:
    std::string getType () override { return "D"; }
    Data (int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked, bool downloaded);
};

#endif
