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
        // Clear the window
        window.fillRectangle(0, 0, 800, 800, Xwindow::White);

        // Draw the grid
        for (int i = 0; i <= 8; ++i) {
            window.drawLine(i * 100, 0, i * 100, 800); // Vertical lines
            window.drawLine(0, i * 100, 800, i * 100); // Horizontal lines
        }

        // Draw the board content
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                char c = subject->getState(i, j);
                auto type = subject->getBoard()->find_unit(c) != nullptr ? subject->getBoard()->find_unit(c)->getType() : "";
                auto color = Xwindow::Black; // Default color for unknown

                if (curplayer->isplayer1turn()) {
                    if (c >= 'a' && c <= 'z') {
                        if (type == "D")
                        {
                            window.drawString(j * 100 + 10, i * 100 + 10, std::format("Data {}: {},{}", c, i, j));
                            color = Xwindow::Green; // Data
                        }
                        else if (type == "V")
                        {
                            window.drawString(j * 100 + 10, i * 100 + 10, std::format("Virus {}: {},{}", c, i, j));
                            color = Xwindow::Red; // Virus
                        }
                    } else if (c >= 'A' && c <= 'Z') {
                        color = Xwindow::Black; // Opponent's links remain unknown
                    }
                } else {
                    if (c >= 'A' && c <= 'Z') {
                        if (type == "D")
                        {
                            window.drawString(j * 100 + 10, i * 100 + 10, std::format("Data {}: {},{}", c, i, j));
                            color = Xwindow::Green; // Data
                        }
                        else if (type == "V")
                        {
                            window.drawString(j * 100 + 10, i * 100 + 10, std::format("Virus {}: {},{}", c, i, j));
                            color = Xwindow::Red; // Virus
                        }
                    } else if (c >= 'a' && c <= 'z') {
                        color = Xwindow::Black; // Opponent's links remain unknown
                    }
                }

                // Fill the rectangle representing the link
                window.fillRectangle(j * 100 + 10, i * 100 + 10, 80, 80, color);
                // window.drawString(j * 100 + 10, i * 100 + 10, "hello");
                // window.drawLine(j * 100 + 10, i * 100 + 10, 10, 10, Xwindow::Blue);
            }
        }

        // Draw player info
        window.drawString(10, 810, "Player 1 Downloads: " + 
                          std::to_string(curplayer->getdownloadD()) + "D, " + 
                          std::to_string(curplayer->getdownloadV()) + "V");
        window.drawString(410, 810, "Player 2 Downloads: " + 
                          std::to_string(otherplayer->getdownloadD()) + "D, " + 
                          std::to_string(otherplayer->getdownloadV()) + "V");
    }

    ~GraphicObserver() {
        subject->detach(this);
    }
};

#endif
