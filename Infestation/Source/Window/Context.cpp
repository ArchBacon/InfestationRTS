#include "Context.h"
#include <cstdio>
#include <EGL/egl.h>

Context::Context(Window window)
{
    const EGLint configAttributes[] =
    {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_CONFORMANT, EGL_OPENGL_ES3_BIT,
        EGL_NONE,
    };

    const EGLint contextAttributes[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE,
    };

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY)
    {
        printf("EGL ERROR: Could not get display. %i\n", eglGetError());
    }

    EGLint major, minor;
    if (!eglInitialize(display, &major, &minor))
    {
        printf("EGL ERROR: Could not initialize. %i\n", eglGetError());
    }

    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(display, configAttributes, &config, 1, &numConfigs))
    {
        printf("EGL ERROR: Could not choose configuration. %i\n", eglGetError());
    }

    surface = eglCreateWindowSurface(display, config, window, nullptr);
    if (surface == EGL_NO_SURFACE)
    {
        printf("EGL ERROR: Could not create window surface. %i\n", eglGetError());
        switch (eglGetError())
        {
        // Check window and EGLConfig attributes to determine
        // compatibility, or verify that the EGLConfig
        // supports rendering to a window
        case EGL_BAD_MATCH: printf("EGL_BAD_MATCH\n");
            break;

        // Verify that provided EGLConfig is valid
        case EGL_BAD_CONFIG: printf("EGL_BAD_CONFIG\n");
            break;

        // Verify that provided EGLNativeWindow is valid
        case EGL_BAD_NATIVE_WINDOW: printf("EGL_BAD_NATIVE_WINDOW\n");
            break;

        // Not enough resources available; handle and recover
        case EGL_BAD_ALLOC: printf("EGL_BAD_ALLOC\n");
            break;
        }
    }

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttributes);
    if (context == EGL_NO_CONTEXT)
    {
        printf("EGL ERROR: Could not create context. %i\n", eglGetError());
    }

    if (!eglMakeCurrent(display, surface, surface, context))
    {
        printf("EGL ERROR: Could not make context current. %i\n", eglGetError());
    }

    eglSwapInterval(display, 0);
}

Context::~Context()
{
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
}
