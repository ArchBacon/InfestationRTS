#pragma once

#include <EGL/egl.h>

class Context
{
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

public:
    Context(Window window);
    ~Context();

    EGLDisplay GetDisplay() const { return display; }

    EGLSurface GetSurface() const { return surface; }

    EGLContext GetContext() const { return context; }
};
