#include "unit.h"

Unit::Unit(int row, int col, int strength, char name, bool displayed, bool doublespeed, bool locked) :
    row{row}, col{col}, strength{strength}, name{name}, displayed{displayed}, doublespeed{doublespeed}, locked{locked} {}
