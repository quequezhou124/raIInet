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
    TextObserver(Subject *subject):
        subject{subject} {
            // once created it attach it
            subject->attach(this);
        }
    // print the canvas
    void notify() override {
        std::cout << "Player 1: " << endl;
        std::cout << "Downloaded: " << curplayer->getdownloadD() <<"D, "<< curplayer->getdownload() << "V" <<endl;
        std::cout << "Abilities: " << curplayer->getabilityNum() << endl;
        
        if (curplayer->isplayer1turn()) {
            std::cout << "a: " << getName("a") << " ";
            std::cout << "b: " << getName("b") << " ";
            std::cout << "c: " << getName("c") << " ";
            std::cout << "d: " << getName("d") << " " << endl;
            std::cout << "e: " << getName("e") << " ";
            std::cout << "f: " << getName("f") << " ";
            std::cout << "g: " << getName("g") << " ";
            std::cout << "h: " << getName("h") << " " << endl;
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
        std::cout << "Downloaded: " << otherplayer->getdownloadD() <<"D, "<< otherplayer->getdownload() << "V" <<endl;
        std::cout << "Abilities: " << otherplayer->getabilityNum() << endl;
        

        if (!curplayer->isplayer1turn()) {
            std::cout << "A: " << string getName("A") << " ";
            std::cout << "B: " << string getName("B") << " ";
            std::cout << "C: " << string getName("C") << " ";
            std::cout << "D: " << string getName("D") << " " << endl;
            std::cout << "E: " << string getName("E") << " ";
            std::cout << "F: " << string getName("F") << " ";
            std::cout << "G: " << string getName("G") << " ";
            std::cout << "H: " << string getName("H") << " " << endl;
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
