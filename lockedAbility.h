#ifndef LOCKEDABILITY_H
#define LOCKEDABILITY_H
#include "link.h"
#include "player.h"
#include <vector>

class lockedAbility{
  public:
    bool useAbility(Player *player,Player *other, char linkname, Board *board, bool negate) {
      if (negate) {
          std::cout << "your opponent has used negate" << endl;
          return true;
      }
      if (board->find_unit(linkname)) {
        if ((std::find(other->links.begin(), other->links.end(), board->find_unit(linkname))!=other->links.end()) && (std::find(player->links.begin(), player->links.end(), board->find_unit(linkname))==player->links.end())) {
            if (board->find_unit(linkname)->getLocked()) {
                std::cout << "this link has already be locked!"<< endl;
                return false;
            }
            auto link = board->find_unit(linkname);
            board->find_unit(linkname)->setLocked(true);
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
