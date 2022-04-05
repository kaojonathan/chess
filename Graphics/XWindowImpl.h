#include <X11/Xlib.h>
struct XWindowImpl { // XWindowImpl structure
	Display* d; // display
	Window w; // window
	int s;
	GC gc;
	unsigned long colours[10];
};