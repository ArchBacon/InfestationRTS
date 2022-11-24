#include <X11/Xlib.h>
#include "XWindow.h"

int main(void)
{
    XEvent event;

    const XWindow* window = new XWindow();

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
