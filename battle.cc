#include <iostream>
#include <memory>
#include <algorithm>
#include "board.h"
#include "blank.h"
#include "subject.h"
#include "player.h"
#include "textObserver.h"
#include "unit.h"
#include "link.h"
#include "data.h"
#include "virus.h"
#include "decorator.h"
#include "datadecorator.h"
#include "virusdecorator.h"
#include <vector>

bool battle (Link *l1, Link *l2, Player *p1,Player *p2, Board *board) {
    if (l1->getStrength() >= l2->getStrength()) {
        if (dynamic_cast<Data*>(l2)) {
            p1->setdownloadD(p1->getdownloadD()+1);
        } else if (dynamic_cast<Virus*>(l2)) {
            p1->setdownloadV(p1->getdownloadV()+1);
        }

        
    }
} 