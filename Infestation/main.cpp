#include <X11/Xlib.h>
#include "Window.h"

int main(void)
{
    XEvent event;

    const auto window = new XWindow();

    while (true)
    {
        XNextEvent(window->GetDisplay(), &event);
        if (event.type == Expose)
        {
            
        }

        if (event.type == KeyPress)
            break;
    }

    delete window;
    
    return 0;
}
