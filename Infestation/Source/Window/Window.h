#pragma once

#include <X11/Xlib.h>

class Context;

struct WindowProperties
{
    int x, y;
    int width, height;
    const char* title;
};

class MyWindow
{
    WindowProperties props;
    Context* eglContext;

    Window window = {};
    Display* display = nullptr;

    bool destroyed = false;
    bool windowCreated = false;

public:
    MyWindow(): MyWindow(640, 480, "Hello Window!") {}
    MyWindow(int width, int height, const char* title);
    ~MyWindow() = default;

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
