#include "ui.h"
#include "config.h"

void UI_Draw()
{
    // Corners
    int size = 3;
    int cornerX1 = 1;
    int cornerY1 = 1;
    int cornerX2 = SCREEN_WIDTH - SCREEN_PADDING;
    int cornerY2 = SCREEN_HEIGHT - SCREEN_PADDING;

    display.fillRect(cornerX1, cornerY1, size, size, GxEPD_BLACK);
    display.fillRect(cornerX1, cornerY2, size, size, GxEPD_BLACK);
    display.fillRect(cornerX2, cornerY1, size, size, GxEPD_BLACK);
    display.fillRect(cornerX2, cornerY2, size, size, GxEPD_BLACK);

    // Borders
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GxEPD_BLACK);                                                                     // Outer border
    display.drawRect(SCREEN_PADDING / 2, SCREEN_PADDING / 2, SCREEN_WIDTH - SCREEN_PADDING, SCREEN_HEIGHT - SCREEN_PADDING, GxEPD_BLACK); // Inner border
}