#ifndef INCLUDE_WJPEG_H
#define INCLUDE_WJPEG_H

#include <X11/Xlib.h>

void init_wjpeg(int, int);
void destroy_wjpeg();
int write_jpeg(XImage *, const char *);

#endif
