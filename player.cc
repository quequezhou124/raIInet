#include "player.h"
#include "link.h"
//constructor
Player::Player(std::vector<std::unique_ptr<Link>> links, bool player1, State state, int downloadD, int downloadV, int abilityNum):
    links{links},
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

bool Player::move(std::unique_ptr<Link>& link, std::string dir) {
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

