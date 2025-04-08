#ifndef TILEMAP_H
#define TILEMAP_H

#include "DEV_Config.h" // Needed for UBYTE type

void Tilemap_Draw(UBYTE *frameBuffer, const unsigned int *mapData, int startX, int startY);

#endif
