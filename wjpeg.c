#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#include "wjpeg.h"


static char *buf;

void init_wjpeg(int width, int height)
{
    buf = malloc(sizeof(char) * width * height * 3);
    printf("malloc buf done\n");
}


void destroy_wjpeg()
{
    free(buf);
    printf("free buf done\n");
}


int write_jpeg(XImage *img, const char *filename)
{
    FILE *fp;
    unsigned long pixel;
    int x, y;
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_prt;

    fp = fopen(filename, "wb");
    if (!fp) return 1;

    for(y=0; y<img->height; y++)
    {
        for(x=0; x<img->width; x++)
        {
            pixel = XGetPixel(img, x, y);
            buf[y*img->width*3 + x*3 + 0] = pixel >> 16;
            buf[y*img->width*3 + x*3 + 1] = (pixel & 0x00ff00) >> 8;
            buf[y*img->width*3 + x*3 + 2] = (pixel & 0x0000ff);
        }
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fp);

    cinfo.image_width = img->width;
    cinfo.image_height = img->height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while(cinfo.next_scanline < cinfo.image_height)
    {
        row_prt = (JSAMPROW) &buf[cinfo.next_scanline * 3 * img->width];
        jpeg_write_scanlines(&cinfo, &row_prt, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(fp);
    return 0;
}

