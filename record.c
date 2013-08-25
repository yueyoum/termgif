#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/select.h>

#include "get_target_window.h"
#include "wjpeg.h"


int main(int argc, char *argv[])
{
    Display *d = XOpenDisplay(NULL);
    if (d==NULL) {
        fprintf(stderr, "can not connect x server!\n");
        exit(2);
    }
    Window active;
    int revert;
    XWindowAttributes attr;

    XGetInputFocus(d, &active, &revert);
    /* active = current_window(d); */
    active = target_window(d);
    XGetWindowAttributes(d, active, &attr);

    int width = attr.width;
    int height = attr.height;
    printf("%d, %d, %d, %d\n", attr.x, attr.y, width, height);


    struct timeval delay;
    delay.tv_sec = 0;
    int i;
    char name[12] = {'\0'};
    XImage *image = XGetImage(d, active, 0, 0, width, height, AllPlanes, ZPixmap);
    init_wjpeg(image->width, image->height);

    for(i = 0; i<20; i++)
    {
        sprintf(name, "test_%02d.jpg", i);
        printf("%s\n", name);
        fflush(stdout);
        image = XGetImage(d, active, 0, 0, width, height, AllPlanes, ZPixmap);
        write_jpeg(image, name);
        delay.tv_usec = 500 * 1000;
        select(0, NULL, NULL, NULL, &delay);
    }

    destroy_wjpeg();
    XCloseDisplay(d);
    return(0);
}
