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
        std::cerr << "Error: X11 DISPLAY environment variable not set. Exiting..." << std::endl;
        exit(1);
    } else {
        std::cout << "X11 DISPLAY environment variable: " << value << std::endl;
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

    setupColors();
    drawColors(); // used to test colors
    // // Set up colours
    // XColor xcolour;
    // Colormap cmap;
    // char color_vals[9][10] = {"white", "black", "red", "green", "blue", "yellow", "pink", "orange", "gray"};

    // cmap = DefaultColormap(d, DefaultScreen(d));
    // for (int i = 0; i < 5; ++i) {
    //     XParseColor(d, cmap, color_vals[i], &xcolour);
    //     XAllocColor(d, cmap, &xcolour);
    //     colours[i] = xcolour.pixel;
    // }
}

void Xwindow::setupColors()
{
    const char *color_vals[ColorCount] = {
        "white", "black", "red", "green", "blue",
        "yellow", "cyan", "magenta", "orange", "purple",
        "pink", "gray", "lightblue", "darkgreen", "navy", "gold"};

    Colormap cmap = DefaultColormap(d, s);
    XColor xcolour;

    for (int i = 0; i < ColorCount; ++i)
    {
        if (XAllocNamedColor(d, cmap, color_vals[i], &xcolour, &xcolour) == 0)
        {
            std::cout << "Failed to allocate color: " << color_vals[i] << std::endl;
            colours[i] = WhitePixel(d, s); // Default to white if allocation fails
        }
        else
        {
            colours[i] = xcolour.pixel; // Store allocated color pixel
        }
    }
}

void Xwindow::drawColors()
{
    int boxSize = 100; // Size of each colored box
    for (int i = 0; i < ColorCount; ++i)
    {
        // Calculate the position of each box
        int x = (i % 5) * boxSize; // Adjust layout as needed
        int y = (i / 5) * boxSize;

        // Set the foreground color to the allocated color
        XSetForeground(d, gc, colours[i]);

        // Draw a filled rectangle
        XFillRectangle(d, w, gc, x, y, boxSize, boxSize);
    }
    XFlush(d);
}

// Destructor for Xwindow
Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XDestroyWindow(d, w);
    XCloseDisplay(d);
}

// Draws a rectangle
void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    std::cout << "fillRectangle color:" << colour << "->" << colours[colour] << std::endl;
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XFlush(d);
}

// Draws a line
void Xwindow::drawLine(int x1, int y1, int x2, int y2, int colour) {
    std::cout << "drawLine color:" << colour << "->" << colours[colour] << std::endl;
    XSetForeground(d, gc, colours[colour]);
    XDrawLine(d, w, gc, x1, y1, x2, y2);
    XFlush(d);
}

// Draws a string
void Xwindow::drawString(int x, int y, std::string msg, int colour) {
    std::cout << "drawString color:" << colour << "->" << colours[colour] << std::endl;
    XSetForeground(d, gc, colours[colour]);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XFlush(d);
}

int Xwindow::getWidth() const {
    return width;
}

int Xwindow::getHeight() const {
    return height;
}

void Xwindow::drawRectangle(int x, int y, int width, int height, int thickness, int colour) {
    std::cout << "drawRectangle color:" << colour << "->" << colours[colour] << std::endl;
    XSetForeground(d, gc, colours[colour]);
    for (int i = 0; i < thickness; ++i) {
        XDrawRectangle(d, w, gc, x + i, y + i, width - 2 * i, height - 2 * i);
    }
    XFlush(d);
}
