#ifndef DOWNLOADABILITY_H
#define DOWNLOADABILITY_H
#include "link.h"
#include "player.h"
#include <vector>

class downloadAbility{
  public:
    bool useAbility(Player *player,Player *other, char linkname, Board *board, bool negate) {
      if (negate) {
          std::cout << "your opponent has used negate" << endl;
          return true;
      }
      if (board->find_unit(linkname)) {
        if ((std::find(other->links.begin(), other->links.end(), board->find_unit(linkname))!=other->links.end()) && (std::find(other->links.begin(), other->links.end(), board->find_unit(linkname))==other->links.end())) {
            if (board->find_unit(linkname)->getDownloaded()) {
                std::cout << "this link has already be downloaded!"<< endl;
                return false;
            }
            auto link = board->find_unit(linkname);
            board->find_unit(linkname)->setDownloaded(true);
            if (link->getType()=="D"){
                int newD = player->getdownloadD() + 1;
                player->setdownloadD(newD);
            } else if (link->getType()=="V"){
                int newV = player->getdownloadV() + 1;
                player->setdownloadV(newV);
            }
            return true;
        } else {
            std::cout << "it is not your opponent's link! (it might be your own link :,P)"<< endl;
        }
      } else {
        std::cout << "this link is not on the board!"<< endl;
      }
      return false;
    }
};

#endif
