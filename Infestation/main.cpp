#include <X11/Xlib.h>
#include <GLES3/gl31.h>
#include <iostream>

#include "Window/XWindow.h"

int main(int argc, char* argv[])
{
    WindowProperties props;
    props.width = 800;
    props.height = 600;

    const auto window = new XWindow(props);
    window->InitializeEGL();

    while (true)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        eglSwapBuffers(window->GetDisplay(), window->GetSurface());
    }

    delete window;

    return 0;
}
