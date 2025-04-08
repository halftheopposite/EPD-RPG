#include "draw.h"
#include "config.h"
#include "GUI_Paint.h"
#include <stdlib.h>

// Function to rotate a 16x16 bitmap 90 degrees counterclockwise
// This will counteract the 270 degree (90 degrees clockwise) rotation of the display
void RotateBitmap90CounterClockwise(const unsigned char *src, unsigned char *dst)
{
    // For a 16x16 1-bit bitmap, we need to rotate each bit
    // This is a specialized function for 16x16 sprites

    // Clear the destination buffer
    for (int i = 0; i < 32; i++) // 16x16 / 8 = 32 bytes
    {
        dst[i] = 0;
    }

    // Process each byte in the source bitmap
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            // Get the bit from the source bitmap
            int srcByte = (y * 16 + x) / 8;
            int srcBit = 7 - ((y * 16 + x) % 8); // MSB first
            bool srcPixel = (src[srcByte] & (1 << srcBit)) != 0;

            // Calculate the position in the destination bitmap
            // For 90 degrees counterclockwise: (x, y) -> (y, 15-x)
            int newX = y;
            int newY = 15 - x;
            int dstByte = (newY * 16 + newX) / 8;
            int dstBit = 7 - ((newY * 16 + newX) % 8); // MSB first

            // Set the bit in the destination bitmap
            if (srcPixel)
            {
                dst[dstByte] |= (1 << dstBit);
            }
        }
    }
}

void Paint_DrawBitMapAt(UBYTE *frameBuffer, const unsigned char *bitmap, int x, int y, int width, int height)
{
    Paint_SelectImage(frameBuffer);

    UWORD Xpoint = x;
    UWORD Ypoint = y;

    Paint_DrawImage(bitmap, Xpoint, Ypoint, width, height);
}
