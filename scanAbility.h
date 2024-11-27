#ifndef SCANABILITY_H
#define SCANABILITY_H

#include "link.h"
#include "player.h"
#include <vector>
#include "data.h"
#include "virus.h"

#include "link.h"
#include "player.h"
#include <vector>

class scanAbility{
  public:
    bool useAbility(Player *player,Player *other, char linkname, Board *board, bool negate) {
      if (negate) {
        std::cout << "your opponent has used negate" << endl;
        return false;
      }
      if (board->find_unit(linkname)) {
        if ((std::find(other->links.begin(), other->links.end(), board->find_unit(linkname))!=other->links.end()) && (std::find(player->links.begin(), player->links.end(), board->find_unit(linkname))==player->links.end())) {
            if (board->find_unit(linkname)->getDownloaded()) {
                std::cout << "this link has already be downloaded!"<< endl;
                return false;
            }
            auto link = board->find_unit(linkname);
            if (board->find_unit(linkname)->getDisplayed()) {
                std::cout << "Bro you are already able to see this link's info!Change one:,P"<< endl;
                return false;
            }
            board->find_unit(linkname)->setDisplayed(true);
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
