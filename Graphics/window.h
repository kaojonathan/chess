#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <memory>

class XWindowImpl; // used the pImpl Idiom
class XWindow
{
  std::unique_ptr<XWindowImpl> pImpl;
public:
  XWindow(int width = 500, int height = 500); // Constructor; displays the window.
  ~XWindow();                                 // Destructor; destroys the window.
  XWindow(const XWindow &) = delete;
  XWindow &operator=(const XWindow &) = delete;
  // Available colours.
  enum
  {
    White = 0,
    Black,
    Red,
    Green,
    Blue,
    Cyan,
    Yellow,
    Magenta,
    Orange,
    Brown
  };
  // fills the graphic window with a rectangle of width and height at pos (x, y) with color colour.
  void fillRectangle(int x, int y, int width, int height, int colour = Black);
  // draws a string of words at pos (x, y)
  void drawString(int x, int y, std::string msg);
  // draws a line from (x1, y1) to (x2, y2)
  void drawLine(int x1, int y1, int x2, int y2);
};

#endif
