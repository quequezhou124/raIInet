#ifndef TEXT_OBSERVER_H
#define TEXT_OBSERVER_H
#include "observer.h"
#include "subject.h"
#include "player.h"
#include "link.h"

class Player;
class Link;

class TextObserver : public Observer {
    Subject *subject;
    Player *curplayer;
    Player *otherplayer;
public:
    // constructor
    TextObserver(Subject *subject, Player *curplayer, Player *otherplayer):
        subject{subject}, curplayer{curplayer}, otherplayer{otherplayer} {
            // once created it attach it
            subject->attach(this);
        }
    // print the canvas
    void notify() override {
        std::cout << "Player 1: " << endl;
        std::cout << "Downloaded: " << curplayer->getdownloadD() <<"D, "<< curplayer->getdownloadV() << "V" <<endl;
        std::cout << "Abilities: " << curplayer->getabilityNum() << endl;
        
        if (curplayer->isplayer1turn()) {
            std::cout << "a: " << subject->getBoard()->find_unit('a')->getType() << subject->getBoard()->find_unit('a')->getStrength() << " ";
            std::cout << "b: " << subject->getBoard()->find_unit('b')->getType() << subject->getBoard()->find_unit('b')->getStrength() << " ";
            std::cout << "c: " << subject->getBoard()->find_unit('c')->getType() << subject->getBoard()->find_unit('c')->getStrength() << " ";
            std::cout << "d: " << subject->getBoard()->find_unit('d')->getType() << subject->getBoard()->find_unit('d')->getStrength() << " " << endl;
            std::cout << "e: " << subject->getBoard()->find_unit('e')->getType() << subject->getBoard()->find_unit('e')->getStrength() << " ";
            std::cout << "f: " << subject->getBoard()->find_unit('f')->getType() << subject->getBoard()->find_unit('f')->getStrength()<< " ";
            std::cout << "g: " << subject->getBoard()->find_unit('g')->getType() << subject->getBoard()->find_unit('g')->getStrength() << " ";
            std::cout << "h: " << subject->getBoard()->find_unit('h')->getType() << subject->getBoard()->find_unit('h')->getStrength() << " " << endl;
        } else {
            std::cout << "a: ? b: ? c: ? d: ?" << endl;
            std::cout << "e: ? f: ? g: ? h: ?" << endl;
        }
        
        for (int i = 0; i < 8; ++i) {
            std::cout << '=' << endl;
        }
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j <= 8; ++j) {
                std::cout << subject->getState(i, j);
            }
            std::cout << endl;
        }
        for (int i = 0; i < 8; ++i) {
            std::cout << '=' << endl;
        }
        std::cout << "Player 2: " << endl;
        std::cout << "Downloaded: " << otherplayer->getdownloadD() <<"D, "<< otherplayer->getdownloadV() << "V" <<endl;
        std::cout << "Abilities: " << otherplayer->getabilityNum() << endl;
        

        if (!curplayer->isplayer1turn()) {
            std::cout << "A: " << subject->getBoard()->find_unit('A')->getType() << subject->getBoard()->find_unit('A')->getStrength() << " ";
            std::cout << "B: " << subject->getBoard()->find_unit('B')->getType() << subject->getBoard()->find_unit('B')->getStrength() << " ";
            std::cout << "C: " << subject->getBoard()->find_unit('C')->getType() << subject->getBoard()->find_unit('C')->getStrength() << " ";
            std::cout << "D: " << subject->getBoard()->find_unit('D')->getType() << subject->getBoard()->find_unit('D')->getStrength() << " " << endl;
            std::cout << "E: " << subject->getBoard()->find_unit('E')->getType() << subject->getBoard()->find_unit('E')->getStrength() << " ";
            std::cout << "F: " << subject->getBoard()->find_unit('F')->getType() << subject->getBoard()->find_unit('F')->getStrength()<< " ";
            std::cout << "G: " << subject->getBoard()->find_unit('H')->getType() << subject->getBoard()->find_unit('G')->getStrength() << " ";
            std::cout << "H: " << subject->getBoard()->find_unit('H')->getType() << subject->getBoard()->find_unit('H')->getStrength() << " " << endl;
        } else {
            std::cout << "A: ? B: ? C: ? D: ?" << endl;
            std::cout << "E: ? F: ? G: ? H: ?" << endl;
        }
    }
    // destructor
    ~TextObserver() {
        subject->detach(this);
    }
};

#endif
