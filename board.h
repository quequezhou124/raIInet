#include <iostream>
#include <vector>

using namespace std;

class Unit;

class Board {
    vector<Unit> units;
  public:
    virtual Unit unitAt() = 0;
};
