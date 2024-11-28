#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[5];

 public:
  Xwindow(int width=500, int height=500); 
  ~Xwindow();  
  enum {White=0, Black, Red, Green, Blue, Yellow, Pink}; 

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour = Black);

  void drawLine(int x1, int y1, int x2, int y2, int colour = Black);
  void drawRectangle(int x, int y, int width, int height, int thickness, int colour = Black);


};

#endif
