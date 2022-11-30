#include "XWindow.h"

#include <cstdio>

#include "Context.h"

XWindow::XWindow(const int width, const int height, const char* title)
    : props({width, height, title})
{
    windowCreated = CreateWindow(width, height, title);
    eglContext = new Context(GetNativeWindow());
}

void XWindow::Destroy()
{
    destroyed = true;
    XCloseDisplay(display);
}

bool XWindow::IsValid() const
{
    return windowCreated && !destroyed;
}

void XWindow::SwapBuffers() const
{
    eglSwapBuffers(eglContext->GetDisplay(), eglContext->GetSurface());
}

bool XWindow::CreateWindow(int width, int height, const char* title)
{
    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

    display = XOpenDisplay(nullptr);
    if (display == nullptr)
    {
        printf("X11 ERROR: Could not get display. %i\n", eglGetError());
        return false;
    }

    window = XCreateWindow(
        display,
        DefaultRootWindow(display),
        0, 0,                           // window position
        width, height,                  // window height
        2,                              // border width
        CopyFromParent,                 // depth
        CopyFromParent,                 // class
        CopyFromParent,                 // visual
        CopyFromParent,                 // value mask
        &swa                            // attributes
    );

    XMapWindow(display, window);
    XStoreName(display, window, title);

    XEvent xev = {};
    xev.type = ClientMessage;
    xev.xclient.window = window;
    xev.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", 0);
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = 0;

    XSendEvent(display, DefaultRootWindow(display), 0, SubstructureNotifyMask, &xev);

    return true;
}
