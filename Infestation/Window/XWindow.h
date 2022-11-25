#pragma once

#include <EGL/egl.h>
#include <X11/Xlib.h>

struct WindowProperties
{
    int x, y;
    unsigned int width, height;
    unsigned int borderWidth;
    unsigned long borderColor, backgroundColor;

    WindowProperties(
        unsigned int width = 200,
        unsigned int height = 150,
        int x = 0,
        int y = 0,
        unsigned int borderWidth = 15,
        unsigned long borderColor = 0x000000,
        unsigned long backgroundColor = 0xffffff
        ) : x(x), y(y)
          , width(width), height(height)
          , borderWidth(borderWidth)
          , borderColor(borderColor)
          , backgroundColor(backgroundColor)
    {
    }
};

class XWindow
{
    Window nativeWindow;
    Display* display;
    int screen;
    WindowProperties properties;

public:
    XWindow(WindowProperties properties = WindowProperties());
    ~XWindow();

    EGLBoolean InitializeEGL();

    // development only
    Display* GetDisplay() const { return display; };

    Window GetNativeWindow() const { return nativeWindow; };

    int GetScreen() const { return screen; };
};
