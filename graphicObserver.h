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

                char state = subject->getState(i, j);
                bool isPlayer1Turn = curplayer->isplayer1turn();

                if (subject->getBoard()->getFirewall(i, j, curplayer)) {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White); 
                    window.drawRectangle(x, y, cellSize, cellSize, borderWidth, Xwindow::Yellow); 
                } else if (subject->getBoard()->getFirewall(i, j, otherplayer)) {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                } else if (state == 'S') {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Blue);
                } else if (state >= 'a' && state <= 'z') {
                    if (isPlayer1Turn || state == 'S') { 
                        window.fillRectangle(x, y, cellSize, cellSize, state <= 'd' ? Xwindow::Green : Xwindow::Red);
                        window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                    } else {
                        window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                    }
                } else if (state >= 'A' && state <= 'Z') {
                    if (!isPlayer1Turn || state == 'S') {
                        window.fillRectangle(x, y, cellSize, cellSize, state <= 'D' ? Xwindow::Pink : Xwindow::Black);
                        window.drawString(x + cellSize / 4, y + cellSize / 2, std::string(1, state), Xwindow::Black);
                    } else {
                        window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                    }
                } else {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                }
            }
        }
    }


    ~GraphicObserver() {
        subject->detach(this);
    }
};

#endif
