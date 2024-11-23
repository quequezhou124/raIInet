#include "player.h"
//constructor
Player::Player(std::vector<Link*> links, bool player1=true, State state, int download):
    links{links},
    player1{player1},
    state{state},
    download{download}{}

State Player::getState() const {
    return state;
}
void Player::setState(State newState) {
    state = newState;
}

int Player::getdownloadD(){
    return downloadD;
}
int Player::getdownloadV(){
    return downloadV;
}
void Player::setdownloadD(int newdownloadD) {
    downloadD = newdownloadD;
}
void Player::setdownloadV(int newdownloadV) {
    downloadV = newdownloadV;
}

int getabilityNum() const {
    return abilityNum;
}

void setabilityNum(int newabilityNum){
    abilityNum = newabilityNum;
}

bool isplayer1turn() const {
    return player1;
}

void changeturn(bool isplayer1){
    player1 = isplayer1;
}

bool move(Link * link, string dir) {
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
    link->setrow(newrow);
    link->setcol(newcol);
    return true;
}
