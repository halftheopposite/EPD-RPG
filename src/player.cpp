#include "player.h"
#include "GUI_Paint.h"
#include "assets/sprites.h"
#include "config.h"
#include "draw.h"

void Player_Draw(UBYTE *frameBuffer, int tileX, int tileY)
{
    int x = GAME_TL_X + (tileX * TILE_SIZE);
    int y = GAME_TL_Y + (tileY * TILE_SIZE);

    Paint_DrawBitMapAt(frameBuffer, SPRITE_344, x, y, PLAYER_SIZE, PLAYER_SIZE);
}
