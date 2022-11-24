#include "XWindow.h"

#include <stdio.h>
#include <stdlib.h>

XWindow::XWindow(WindowProperties properties)
    : properties(properties)
{
    display = XOpenDisplay(nullptr);
    if (display == nullptr)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        properties.x, properties.y,                        // Window Position
        properties.width, properties.height,               // Window Size
        properties.borderWidth,                            // Border width
        properties.borderColor, properties.backgroundColor // Window Colors
    );

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
}

XWindow::~XWindow()
{
    XCloseDisplay(display);
}
