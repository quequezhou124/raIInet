#include "player.h"
#include "link.h"
#include "serverports.h"
#include <utility>

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
        if (dir == "u") {
            newrow--;
        } else if (dir == "d") {
            newrow++;
        } else if (dir == "l") {
            newcol--;
        } else if (dir == "r") {
            newcol++;
        } else {
            return false;
        }
        Unit * newunit = board->getUnit(newrow, newcol);
        if (( newunit != nullptr
        && std::find(links.begin(), links.end(), newunit) != links.end())
        || (player1 && newrow == 0 && newcol == 3)
        || (player1 && newrow == 0 && newcol == 4)
        || (!player1 && newrow == 7 && newcol == 3)
        || (!player1 && newrow == 7 && newcol == 4)) {return false;}
        if (player1 == true) {
            std::cout << "player1 turn 11111"<< endl;
            if(newrow >= 8) {
                unit->setDownloaded(true);
                if (unit->getType()== "V") {
                    downloadV++;
                } else if(unit->getType()== "D") {
                    downloadD++;
                }
                return true;
            }
        } else {
            std::cout << "player2 turn 2222"<< endl;
            if(newrow < 0) {
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

bool Player::addAbility(int i){
    for(int i = 0; i < 5; i++) {
        if (abilityBag[i] == 0) {
            abilityBag[i] = i;
            return true;
        } else {
            continue;
        }
    }
    std::cout<< "you have already set 5 abilities!";
    return false;
}

void Player::printAbility() {
    for(int i = 0; i < 5; i++) {
        if (abilityBag[i] == 0) {
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
