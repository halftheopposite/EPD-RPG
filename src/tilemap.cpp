#include "tilemap.h"
#include "GUI_Paint.h"
#include "assets/sprites.h"
#include "config.h"
#include "draw.h"

// Helper function to get the sprite data for a given tile type
const unsigned char *GetSpriteForTileType(unsigned int tileType)
{
    // This avoids switch statement limitations with large values
    if (tileType == 1)
        return SPRITE_1;
    if (tileType == 2)
        return SPRITE_2;
    if (tileType == 3)
        return SPRITE_3;
    if (tileType == 4)
        return SPRITE_4;
    if (tileType == 5)
        return SPRITE_5;
    if (tileType == 6)
        return SPRITE_6;
    if (tileType == 50)
        return SPRITE_50;
    if (tileType == 51)
        return SPRITE_51;
    if (tileType == 53)
        return SPRITE_53;
    if (tileType == 99)
        return SPRITE_99;
    if (tileType == 344)
        return SPRITE_344;
    if (tileType == 505)
        return SPRITE_505;
    if (tileType == 594)
        return SPRITE_594;
    if (tileType == 595)
        return SPRITE_595;
    if (tileType == 596)
        return SPRITE_596;
    if (tileType == 642)
        return SPRITE_642;
    if (tileType == 644)
        return SPRITE_644;
    if (tileType == 645)
        return SPRITE_645;

    return SPRITE_1;
}

void Tilemap_Draw(UBYTE *frameBuffer, const unsigned int *mapData, int startX, int startY)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int tileIndex = y * MAP_WIDTH + x;
            unsigned int tileType = mapData[tileIndex];

            // Calculate the pixel position for this tile
            int pixelX = startX + (x * TILE_SIZE);
            int pixelY = startY + (y * TILE_SIZE);

            // Get the sprite for this tile type
            const unsigned char *sprite = GetSpriteForTileType(tileType);

            // Draw the sprite at the calculated position
            Paint_DrawBitMapAt(frameBuffer, sprite, pixelX, pixelY, SPRITE_WIDTH, SPRITE_HEIGHT);
        }
    }
}