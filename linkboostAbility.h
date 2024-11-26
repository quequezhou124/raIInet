#ifndef LINKBOOSTABILITY_H
#define LINKBOOSTABILITY_H
#include "link.h"
#include "player.h"
#include <vector>

class enhanceAbility{
  public:
    bool useAbility(Player *player, char linkname, Board *board) {
      if (board->find_unit(linkname)) {
        if (std::find(player->links.begin(), player->links.end(), board->find_unit(linkname))!=player->links.end()) {
          auto link = board->find_unit(linkname);
          board->find_unit(linkname)->opendoublespeed();
          return true;
        }
      }
      return false;
    }
};

#endif
