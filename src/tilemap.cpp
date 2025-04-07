#include "tilemap.h"
#include "GUI_Paint.h"
#include "assets/sprites.h"
#include "config.h"
#include "draw.h"

void Tilemap_Draw(UBYTE *frameBuffer, const unsigned char *mapData, int startX, int startY)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int tileIndex = y * MAP_WIDTH + x;
            unsigned char tileType = mapData[tileIndex];

            // TODO
        }
    }
}