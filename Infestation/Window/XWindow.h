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
        unsigned int width = 800,
        unsigned int height = 600,
        int x = 0,
        int y = 0,
        unsigned int borderWidth = 1,
        unsigned long borderColor = 0x000000,
        unsigned long backgroundColor = 0x00ff00
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
    EGLSurface surface;
    Window nativeWindow;
    Display* display;
    EGLDisplay eglDisplay;
    int screen;
    WindowProperties properties;

public:
    XWindow(WindowProperties properties = WindowProperties());
    ~XWindow();

    EGLBoolean InitializeEGL();

    // development only
#ifdef _DEBUG
    EGLDisplay GetDisplay() const { return eglDisplay; }

    Window GetNativeWindow() const { return nativeWindow; }

    int GetScreen() const { return screen; }

    EGLSurface GetSurface() const { return surface; }
#endif // _DEBUG
};
