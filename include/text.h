#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>

/**
 * Draws text in a white box with borders, positioned at the bottom of the screen
 * The text will automatically wrap to fit within the box width
 * 
 * @param text The text to display
 * @param borderWidth Width of the border in pixels (default: 1)
 * @param padding Padding inside the box in pixels (default: 4)
 */
void Text_DrawBox(const char *text, uint8_t borderWidth = 1, uint8_t padding = 4);

#endif
