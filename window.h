#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
 public:
  Xwindow(int width=500, int height=500); 
  ~Xwindow();  
  // enum {White=0, Black, Red, Green, Blue, Yellow, Pink, Orange, Gray}; 
  enum {
      White = 0,
      Black,
      Red,
      Green,
      Blue,
      Yellow,
      Cyan,
      Magenta,
      Orange,
      Purple,
      Pink,
      Gray,
      LightBlue,
      DarkGreen,
      Navy,
      Gold,
      ColorCount // Total number of colors defined
  };
  const std::string colorNames[ColorCount] = {
      "White",
      "Black",
      "Red",
      "Green",
      "Blue",
      "Yellow",
      "Cyan",
      "Magenta",
      "Orange",
      "Purple",
      "Pink",
      "Gray",
      "LightBlue",
      "DarkGreen",
      "Navy",
      "Gold"};

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour = Black);

  void drawLine(int x1, int y1, int x2, int y2, int colour = Black);
  void drawRectangle(int x, int y, int width, int height, int thickness, int colour = Black);

private:
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[ColorCount];
  void setupColors();
  void drawColors();
  std::string colorToString(int color)
  {
    if (color >= 0 && color < ColorCount)
    {
      return colorNames[color];
    }
    return "UNKNOWN";
  }
};

#endif
