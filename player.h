#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string.h>

enum class State {
    Winner,
    Loser,
    Undecided
};

class Link;

class Player {
    std::vector<Link*> links;
    bool player1;
    State state;
    int downloadD;
    int downloadV;
    int abilityNum;
   public:
    //constructor
    Player(std::vector<Link*> links, bool player1 = true, State state = State::Undecided, int downloadD = 0, int downloadV = 0, int abilityNum = 0);
    Player();
    // methods
    bool move(Link* link, string dir);
    bool useAbility();
    bool useAbility(int id);
    bool useAbility(int id, char link);
    bool useAbility(int id, int row, int col);
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
