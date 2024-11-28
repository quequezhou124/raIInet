#ifndef PLAYER_H
#define PLAYER_H
#include "link.h"
#include "board.h"
#include "wall.h"
#include <vector>
#include <string>

class Link;
class Board;

enum class State {
    Winner,
    Loser,
    Undecided
};


class Player {
    bool player1;
    State state;
    int downloadD;
    int downloadV;
    int abilityNum;
    int abilityBag[5] = {0};

   public:
    std::vector<Link*> links;
    std::vector<Wall*> walls;
    //constructor
    Player(std::vector<Link*> links, bool player1 = true, State state = State::Undecided, int downloadD = 0, int downloadV = 0, int abilityNum = 0);
    Player();
    // methods
    bool findAbility(int k);
    bool addAbility(int k);
    bool move(Board * borad, Unit * unit, const std::string& dir);
    void printAbility();
    bool deleteAbility(int k);
    State getState() const;
    void setState(State newState);
    int getdownloadD() const;
    int getdownloadV() const;
    void setdownloadD(int newdownloadD);
    void setdownloadV(int newdownloadV);
    int getabilityNum() const;
    void setabilityNum(int newabilityNum);
    bool isplayer1turn() const;
    void changeturn(bool isplayer1);
};

#endif
