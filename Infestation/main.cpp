#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    XEvent event;
    
    Display* display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 100, 100, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    while (1)
    {
        XNextEvent(display, &event);
        if (event.type == Expose)
        {
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);

            const char* msg = "Hello, World!";
            XDrawString(display, window, DefaultGC(display, screen), 10, 50, msg, strlen(msg));
        }
        if (event.type == KeyPress)
            break;
    }

    XCloseDisplay(display);
    return 0;
}
