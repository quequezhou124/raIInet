#ifndef GRAPHIC_OBSERVER_H
#define GRAPHIC_OBSERVER_H

#include "observer.h"
#include "subject.h"
#include "player.h"
#include "link.h"
#include "window.h"
#include <format>

class GraphicObserver : public Observer {
    Subject *subject;
    Player *curplayer;
    Player *otherplayer;
    Xwindow window;

public:
    GraphicObserver(Subject *subject, Player *curplayer, Player *otherplayer)
        : subject{subject}, curplayer{curplayer}, otherplayer{otherplayer},
          window{800, 800} { // 8x8 grid with each cell 100x100 pixels
        subject->attach(this);
    }

    void notify() override {
        const int cellSize = 100;
        const int borderWidth = 3;

        // Clear the entire grid to white
        window.fillRectangle(0, 0, 800, 800, Xwindow::White);

        // Draw grid lines
        for (int i = 0; i <= 8; ++i) {
            window.drawLine(i * cellSize, 0, i * cellSize, 800, Xwindow::Black);
            window.drawLine(0, i * cellSize, 800, i * cellSize, Xwindow::Black);
        }

        // Draw the board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int x = j * cellSize;
                int y = i * cellSize;
                char c = subject->getState(i, j);

                char state = subject->getState(i, j);
                bool isPlayer1Turn = curplayer->isplayer1turn();
                if (subject->getBoard()->getFirewall(i, j, curplayer) && subject->getBoard()->getFirewall(i, j, curplayer)->getName() == 'w' && curplayer->isplayer1turn()) {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White); 
                    window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Orange); 
                } else if (subject->getBoard()->getFirewall(i, j, otherplayer) && subject->getBoard()->getFirewall(i, j, otherplayer)->getName() == 'm' && !curplayer->isplayer1turn()) {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                    window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Orange);
                } else if (state == 'S') {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::LightBlue);
                    window.drawString(j * 100 + 5, i * 100 + 40, std::format("Sever Pot: ({},{})", i, j));
                    window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black);
                } else if (state >= 'a' && state <= 'z') {
                    if(curplayer->isplayer1turn()){
                        if (subject->getBoard()->getUnit(i, j)->getType() == "D"&&subject->getBoard()->getUnit(i, j)->getDownloaded()==false) {
                            window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Green);
                            window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                            window.drawString(j * 100 + 5, i * 100 + 40, std::format("Data {}: ({},{})", c, i, j));
                            window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black);
                        } else if (subject->getBoard()->getUnit(i, j)->getType() == "V"&&subject->getBoard()->getUnit(i, j)->getDownloaded()==false) {
                            window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Red);
                            window.drawString(j * 100 + 5, i * 100 + 40, std::format("Virus {}: ({},{})", c, i, j));
                            window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                            window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black);
                        }
                    } else {
                        window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Gray);
                        window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::White);
                    }
                } else if (state >= 'A' && state <= 'Z') {
                    if(!curplayer->isplayer1turn()){
                        if (subject->getBoard()->getUnit(i, j)->getType() == "D" &&subject->getBoard()->getUnit(i, j)->getDownloaded()==false) {
                                window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Green);
                                window.drawString(j * 100 + 5, i * 100 + 40, std::format("Data {}: ({},{})", c, i, j));
                                window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                                window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black);
                        } else if (subject->getBoard()->getUnit(i, j)->getType() == "V"&&subject->getBoard()->getUnit(i, j)->getDownloaded()==false) {
                                window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Red);
                                window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                                window.drawString(j * 100 + 5, i * 100 + 40, std::format("Virus {}: ({},{})", c, i, j));
                                window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black);
                        }
                    } else {
                        window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Gray);
                        window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                        window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black);
                    }
                } else {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                    window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Black); 
                }
            }
        }
    }


    ~GraphicObserver() {
        subject->detach(this);
    }
};

#endif
