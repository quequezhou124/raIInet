#include <iostream>
#include <memory>
#include <algorithm>
#include "board.h"
#include "subject.h"
#include "player.h"
#include "textObserver.h"
#include "unit.h"
#include "link.h"
#include "data.h"
#include "virus.h"
#include <vector>

int battle (Link *l1, Link *l2, Player *p1,Player *p2, Board *board) {
    if (l1->getStrength() >= l2->getStrength()) {
        if (dynamic_cast<Data*>(l2)) {
            p1->setdownloadD(p1->getdownloadD()+1);
            std::cout << "You download a data.\n";
            delete l2;
            return 1;
        } else if (dynamic_cast<Virus*>(l2)) {
            p1->setdownloadV(p1->getdownloadV()+1);
            std::cout << "You download a virus.\n";
            delete l2;
            return 2;
        }
    } else {
        if (dynamic_cast<Data*>(l1)) {
            p2->setdownloadD(p2->getdownloadD()+1);
            std::cout << "Your data is downloaded by opponent.\n";
            delete l1;
            return 3;
        } else if (dynamic_cast<Virus*>(l1)) {
            p2->setdownloadV(p2->getdownloadV()+1);
            std::cout << "Your virus is downloaded by opponent.\n";
            delete l1;
            return 4;
        } 
    }
} 