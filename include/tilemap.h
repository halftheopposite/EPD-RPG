#ifndef TILEMAP_H
#define TILEMAP_H

#include <Arduino.h>

void Tilemap_Draw(const unsigned int *mapData, int startX, int startY);
uint8_t const *Tilemap_GetSpriteForTileType(unsigned int tileType);

#endif
