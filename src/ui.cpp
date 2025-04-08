#include "ui.h"
#include "config.h"

void UI_Draw()
{
    // Corners
    display.fillRect(1, 1, 3, 3, GxEPD_BLACK);
    display.fillRect(1, SCREEN_HEIGHT - 4, 3, 3, GxEPD_BLACK);
    display.fillRect(SCREEN_WIDTH - 4, 1, 3, 3, GxEPD_BLACK);
    display.fillRect(SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4, 3, 3, GxEPD_BLACK);

    // Borders
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GxEPD_BLACK);
    display.drawRect(2, 2, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4, GxEPD_BLACK);
}