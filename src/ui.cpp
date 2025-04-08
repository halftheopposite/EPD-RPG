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
    display.drawLine(UI_TL_X, UI_TL_Y, UI_TR_X, UI_TR_Y, GxEPD_BLACK);
    display.drawLine(UI_BL_X, UI_BL_Y, UI_BR_X, UI_BR_Y, GxEPD_BLACK);
    display.drawLine(UI_TL_X, UI_TL_Y, UI_BL_X, UI_BL_Y, GxEPD_BLACK);
    display.drawLine(UI_TR_X, UI_TR_Y, UI_BR_X, UI_BR_Y, GxEPD_BLACK);
}