#ifndef VIRUS_H
#define VIRUS_H
#include"link.h"

class Virus: public Link {
    int strength;
  public:
    std::string getType () override { return "V"; }
    Virus (int row, int col, int strength, char name, Player* owner, bool displayed, bool doublespeed, bool locked);
};

#endif
