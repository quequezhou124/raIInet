#ifndef GRAPHICS_OBSERVER_H
#define GRAPHICS_OBSERVER_H
#include "observer.h"
#include "subject.h"
#include "window.h"

class GraphicsObserver : public Observer {
    Subject *subject;
    int top, bottom, left, right;
    Xwindow window;

public:
    GraphicsObserver(Subject *subject, int top, int bottom, int left, int right):
        subject{subject},
        top{top},
        bottom{bottom},
        left{left},
        right{right}, 
        window{(right - left + 1) * 10, (bottom - top + 1) * 10} {
            subject->attach(this);
        }

    void notify() override {
        for (int i = top; i <= bottom; ++i) {
            for (int j = left; j <= right; ++j) {
                char c = subject->getState(i, j);
                int color = Xwindow::White;
                if (c >= 'a' && c <= 'z') {
                    color = Xwindow::Red;
                }
                else if (c >= 'A' && c <= 'Z') {
                    color = Xwindow::Green;
                }
                else if (c >= '0' && c <= '9') {
                    color = Xwindow::Blue;
                }
                else if (c != ' ') {
                    color = Xwindow::Black;
                }
                window.fillRectangle((j - left) * 10, (i - top) * 10, 10, 10, color);
            }
        }
    }

    ~GraphicsObserver() {
        subject->detach(this);
    }
};

#endif
