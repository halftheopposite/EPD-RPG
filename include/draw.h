#ifndef DRAW_H
#define DRAW_H

#include "DEV_Config.h" // Needed for UBYTE type

void Paint_DrawBitMapAt(UBYTE *frameBuffer, const unsigned char *bitmap, int x, int y, int width, int height);

#endif
