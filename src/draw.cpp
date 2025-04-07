#include "draw.h"
#include "config.h"
#include "GUI_Paint.h"

void Paint_DrawBitMapAt(UBYTE *frameBuffer, const unsigned char *bitmap, int x, int y, int width, int height)
{
    Paint_SelectImage(frameBuffer);

    // Convert coordinates based on rotation
    UWORD Xpoint = x, Ypoint = y;

    switch (Paint.Rotate)
    {
    case 0:
        break;
    case 90:
        Xpoint = Paint.WidthMemory - y - height;
        Ypoint = x;
        break;
    case 180:
        Xpoint = Paint.WidthMemory - x - width;
        Ypoint = Paint.HeightMemory - y - height;
        break;
    case 270:
        Xpoint = y;
        Ypoint = Paint.HeightMemory - x - width;
        break;
    }

    Paint_DrawImage(bitmap, Xpoint, Ypoint, width, height);
}
