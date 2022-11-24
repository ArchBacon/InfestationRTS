﻿#pragma once

#include <X11/Xlib.h>

struct WindowProperties
{
    int x, y;
    unsigned int width, height;
    unsigned int borderWidth;
    unsigned long borderColor, backgroundColor;

    WindowProperties(
        int x = 0,
        int y = 0,
        unsigned int width = 200,
        unsigned int height = 150,
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
    Window window;
    Display* display;
    int screen;
    WindowProperties properties;

public:
    XWindow(WindowProperties properties = WindowProperties());
    ~XWindow();

    // development only
    Display* GetDisplay() const { return display; };
    Window& GetWindow() { return window; };
    int& GetScreen() { return screen; };
};
