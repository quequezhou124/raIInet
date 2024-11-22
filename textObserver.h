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
        std::cout << "Downloaded: " << curplayer->getdownloadD <<"D, "<< curplayer->getdownloadV << "V" <<endl;
        std::cout << "Abilities: " << curplayer->getabilityNum << endl;
        
        if (curplayer->isplayer1turn()) {
            std::cout << "a: " << string getinfo("a") << " ";
            std::cout << "b: " << string getinfo("b") << " ";
            std::cout << "c: " << string getinfo("c") << " ";
            std::cout << "d: " << string getinfo("d") << " " << endl;
            std::cout << "e: " << string getinfo("e") << " ";
            std::cout << "f: " << string getinfo("f") << " ";
            std::cout << "g: " << string getinfo("g") << " ";
            std::cout << "h: " << string getinfo("h") << " " << endl;
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

        if (!curplayer->isplayer1turn()) {
            std::cout << "A: " << string getinfo("A") << " ";
            std::cout << "B: " << string getinfo("B") << " ";
            std::cout << "C: " << string getinfo("C") << " ";
            std::cout << "D: " << string getinfo("D") << " " << endl;
            std::cout << "E: " << string getinfo("E") << " ";
            std::cout << "F: " << string getinfo("F") << " ";
            std::cout << "G: " << string getinfo("G") << " ";
            std::cout << "H: " << string getinfo("H") << " " << endl;
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
