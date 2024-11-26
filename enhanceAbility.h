#ifndef ENHANCEABILITY_H
#define ENHANCEABILITY_H
#include "player.h"
#include "link.h"
#include <vector>

class enhanceAbility{
  public:
    bool useAbility(Player *player, char linkname, Board *board, bool negate) {
      if (negate) {
        std::cout << "your opponent has used negate" << endl;
        return false;
      }
      if (board->find_unit(linkname)) {
        if (std::find(player->links.begin(), player->links.end(), board->find_unit(linkname))!=player->links.end()) {
          auto link = board->find_unit(linkname);
          int row = link->getRow();
          int col = link->getCol();
          int newlevel = (link->getStrength())+1;
          board->find_unit(linkname)->setStrength(newlevel, row, col);
          return true;
        }
      }
      return false;
    }
};

#endif
