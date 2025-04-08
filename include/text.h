#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "config.h"

#define MAX_LINES 10        // Maximum number of lines to support
#define MAX_LINE_LENGTH 100 // Maximum characters per line

/**
 * Structure to hold text bounds information
 */
typedef struct
{
    uint16_t width;  // Width of the text
    uint16_t height; // Height of the text
    int16_t x;       // X offset
    int16_t y;       // Y offset
} TextBounds;

/**
 * Draws text in a white box with borders, positioned at the bottom of the screen.
 * The text will automatically wrap to fit within the box width.
 */
void Text_Draw(const char *text);

#endif
