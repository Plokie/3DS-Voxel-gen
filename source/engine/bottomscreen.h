#ifndef BOTTOMSCREEN_H
#define BOTTOMSCREEN_H

#include <3ds.h>
#include <citro3d.h>
#include <string.h>

void bottom_drawpixel(int i)
{
    u8* screen;
    screen = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
    char r= 0xff;
    char g= 0x00;
    char b = 0x00;
    int height = 240;
    u32 v = (height-1-i+i*height)*3;
    screen[v] = b;
    screen[v + 1] = g;
    screen[v + 2] = r;
}

void setPixel(u8 *fb, u16 x, u16 y, u8 red, u8 green, u8 blue) {
    fb[3 * (240 - y + (x - 1) * 240)] = blue;
    fb[3 * (240 - y + (x - 1) * 240) + 1] = green;
    fb[3 * (240 - y + (x - 1) * 240) + 2] = red;
}

#endif