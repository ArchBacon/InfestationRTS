#include <X11/Xlib.h>
#include "Window/XWindow.h"

int main(int argc, char* argv[])
{
    XEvent event;
    const auto window = new XWindow();
    window->InitializeEGL();

    while (true)
    {
        XNextEvent(window->GetDisplay(), &event);
        if (event.type == Expose)
        {
        }

        if (event.type == KeyPress)
        {
            break;
        }
    }

    delete window;

    return 0;
}
