#include "player.h"
#include "link.h"
#include "serverports.h"
#include <utility>
#include <algorithm>

//constructor
Player::Player(std::vector<Link*> links, bool player1, State state, int downloadD, int downloadV, int abilityNum)
    : links{links},
      player1{player1},
      state{state},
      downloadD{downloadD},
      downloadV{downloadV},
      abilityNum{abilityNum} {}

Player::Player():
    links{}, player1{true}, state{State::Undecided}, downloadD{0}, downloadV{0}, abilityNum{0} {}

State Player::getState() const {
    return state;
}
void Player::setState(State newState) {
    state = newState;
}

bool Player::deleteAbility(int k) {
    bool found = false;
    for(int i = 0; i < 4; i++) {
        if (abilityBag[i] == k && found == false) {
            found = true;
            abilityBag[i] = abilityBag[i+1];
        } else if (found == true) {
            abilityBag[i] = abilityBag[i+1];
        }
    }
    if (found) {
        abilityBag[4] = 0;
        abilityNum--;
        return true;
    } else {
        if (abilityBag[4]==k) {
            abilityBag[4] = 0;
            abilityNum--;
            return true;
        } else {
            std::cout << "You don't have that ability card haha!" << endl;
            return false;
        }
    }

}

int Player::getdownloadD() const {
    return downloadD;
}
int Player::getdownloadV() const {
    return downloadV;
}
void Player::setdownloadD(int newdownloadD) {
    downloadD = newdownloadD;
}
void Player::setdownloadV(int newdownloadV) {
    downloadV = newdownloadV;
}

int Player::getabilityNum() const {
    return abilityNum;
}

void Player::setabilityNum(int newabilityNum){
    abilityNum = newabilityNum;
}

bool Player::isplayer1turn() const {
    return player1;
}

void Player::changeturn(bool isplayer1){
    player1 = isplayer1;
}

bool Player::move(Board * board, Unit * unit, const std::string& dir) {
    if (auto link = dynamic_cast<Link*>(unit)){
        int newrow = link->getRow();
        int newcol = link->getCol();
        int speed = 1;
        if (unit->getDoublespeed()) speed = 2;
        if (dir == "u") {
            newrow -= speed;
        } else if (dir == "d") {
            newrow += speed;
        } else if (dir == "l") {
            newcol -= speed;
        } else if (dir == "r") {
            newcol += speed;
        } else {
            return false;
        }
        Unit * newunit = board->getUnit(newrow, newcol);
        if (( newunit != nullptr
        && std::find(links.begin(), links.end(), newunit) != links.end())
        || (player1 && newrow == 0 && newcol == 3)
        || (player1 && newrow == 0 && newcol == 4)
        || (!player1 && newrow == 7 && newcol == 3)
        || (!player1 && newrow == 7 && newcol == 4)
        || (unit->getLocked() && ((!player1 && newrow == 0 && newcol == 3)
        || (!player1 && newrow == 0 && newcol == 4)))
        || (unit->getLocked() && ((player1 && newrow == 7 && newcol == 3)
        || (player1 && newrow == 7 && newcol == 4)))) {return false;}
        if (player1 == true) {
            if(newrow >= 8) {
                if (unit->getLocked()) return false;
                unit->setDownloaded(true);
                if (unit->getType()== "V") {
                    downloadV++;
                } else if(unit->getType()== "D") {
                    downloadD++;
                }
                return true;
            }
        } else {
            if(newrow < 0) {
                if (unit->getLocked()) return false;
                unit->setDownloaded(true);
                if (unit->getType()== "V") {
                    downloadV++;
                } else if(unit->getType()== "D") {
                    downloadD++;
                }
                return true;
            }
        }
        return link->setrow(newrow) && link->setcol(newcol);

    } else {
        return false;
    }
}

bool Player::addAbility(int k){
    for(int i = 0; i < 5; i++) {
        if (abilityBag[i] == 0) {
            abilityBag[i] = k;
            return true;
        }
    }
    std::cout<< "you have already set 5 abilities!";
    return false;
}

void Player::printAbility() {
    std::cout << abilityBag[4] << std::endl;
    for(int i = 0; i < 5; i++) {
        if (abilityBag[i] == 0) {
            std::cout << endl;
            return;
        } else {
             std::cout<< abilityBag[i]<< " ";
        }
    }
    std::cout << endl;
}

bool Player::findAbility(int k){
    for(int i = 0; i < 5; i++) {
        if (abilityBag[i] == k) {
            return true;
        }
    }
    return false;
}
