#pragma once

#include <X11/Xlib.h>

class Context;

struct XWindowProperties
{
    int x, y;
    int width, height;
    const char* title;
};

class XWindow
{
    XWindowProperties props;
    Context* eglContext;

    Window window = {};
    Display* display = nullptr;

    bool destroyed = false;
    bool windowCreated = false;

public:
    XWindow(): XWindow(640, 480, "Hello Window!") {}
    XWindow(int width, int height, const char* title);
    ~XWindow() = default;

    void Destroy();
    bool IsValid() const;
    void SwapBuffers() const;

    int GetWidth() const { return props.width; }
    int GetHeight() const { return props.height; }

    int GetPositionX() const { return props.x; }
    int GetPositionY() const { return props.y; }

    Window GetNativeWindow() const { return window; }
    Display* GetNativeDisplay() const { return display; }

private:
    bool CreateWindow(int width, int height, const char* title);
    void InitializeImGui();
};
