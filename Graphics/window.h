#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class XWindowImpl; // used the pImpl Idiom
class XWindow {
	XWindowImpl* pImpl;

 public:
	 XWindow(int width=500, int height=500);  // Constructor; displays the window.
  ~XWindow();                              // Destructor; destroys the window.
  XWindow(const XWindow&) = delete;
  //XWindow&operator=(const XWindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Draws a line
  void drawLine(int x1, int y1, int x2, int y2);


};

#endif
