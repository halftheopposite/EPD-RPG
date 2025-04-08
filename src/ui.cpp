#include "ui.h"
#include "config.h"

void UI_Draw()
{
    display.fillRect(0, 0, 4, 4, GxEPD_BLACK);

    // Top
    display.drawLine(UI_TL_X, UI_TL_Y, UI_TR_X, UI_TR_Y, GxEPD_BLACK);
    // Bottom
    display.drawLine(UI_BL_X, UI_BL_Y, UI_BR_X, UI_BR_Y, GxEPD_BLACK);
    // Left
    display.drawLine(UI_TL_X, UI_TL_Y, UI_BL_X, UI_BL_Y, GxEPD_BLACK);
    // Right
    display.drawLine(UI_TR_X, UI_TR_Y, UI_BR_X, UI_BR_Y, GxEPD_BLACK);
}