#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "window.h"
#include <cstdlib>

using namespace std;

// Constructor for Xwindow
Xwindow::Xwindow(int width, int height) : width{width}, height{height} {
    const char* envVar = "DISPLAY";
    const char* value = std::getenv(envVar);
    if (value == nullptr) {
        std::cerr << "Error: DISPLAY environment variable for X11 not set. Exiting..." << std::endl;
        exit(1);
    }
    d = XOpenDisplay(nullptr);
    if (d == nullptr) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d, w, width, height,
                               DefaultDepth(d, DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0, nullptr);
    XFlush(d);
    XFlush(d);

    // Set up colours
    XColor xcolour;
    Colormap cmap;
    char color_vals[5][10] = {"white", "black", "red", "green", "blue"};

    cmap = DefaultColormap(d, DefaultScreen(d));
    for (int i = 0; i < 5; ++i) {
        XParseColor(d, cmap, color_vals[i], &xcolour);
        XAllocColor(d, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }
}

// Destructor for Xwindow
Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XDestroyWindow(d, w);
    XCloseDisplay(d);
}

// Draws a rectangle
void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XFlush(d);
}

// Draws a line
void Xwindow::drawLine(int x1, int y1, int x2, int y2, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XDrawLine(d, w, gc, x1, y1, x2, y2);
    XFlush(d);
}

// Draws a string
void Xwindow::drawString(int x, int y, string msg) {
    XSetForeground(d, gc, colours[Black]);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XFlush(d);
}

int Xwindow::getWidth() const {
    return width;
}

int Xwindow::getHeight() const {
    return height;
}
