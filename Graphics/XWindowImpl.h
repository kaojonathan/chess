#include <X11/Xlib.h>
struct XWindowImpl {
	Display* d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];
};