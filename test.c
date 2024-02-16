#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

int main() {
    Display *display;
    Window root;
    XEvent ev;

    display = XOpenDisplay(NULL);
    if (!display) 
    {
        fprintf(stderr, "Unable to open display\n");
        return 1;
    }

    root = DefaultRootWindow(display);

    XSelectInput(display, root, KeyPressMask | PointerMotionMask);
    XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(display, root, True, PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

    while (1) 
    {
        XNextEvent(display, &ev);

        if (ev.type == KeyPress) {
            // Key pressed
            printf("Key pressed\n");
        }
        else if (ev.type == MotionNotify) {
            // Mouse moved
            printf("Mouse moved at x=%d, y=%d\n", ev.xmotion.x_root, ev.xmotion.y_root);
        }
    }
    XCloseDisplay(display);
    return 0;
}
