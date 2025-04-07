#include "ui.h"
#include "GUI_Paint.h"
#include "config.h"

void UI_Draw(UBYTE *frameBuffer)
{
    // Top
    Paint_DrawLine(UI_TL_X, UI_TL_Y, UI_TR_X, UI_TR_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Bottom
    Paint_DrawLine(UI_BL_X, UI_BL_Y, UI_BR_X, UI_BR_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Left
    Paint_DrawLine(UI_TL_X, UI_TL_Y, UI_BL_X, UI_BL_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Right
    Paint_DrawLine(UI_TR_X, UI_TR_Y, UI_BR_X, UI_BR_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}