#include <X11/Xlib.h>

#include "get_target_window.h"

Window target_window(Display *d)
{
    Window w;
    Window parent;
    Window root = None;
    Window *children;
    unsigned int nchildren;
    Status s;

    while(parent != root)
    {
        w = parent;
        s = XQueryTree(d, w, &root, &parent, &children, &nchildren);

        if(s) XFree(children);
    }

    return w;
}
