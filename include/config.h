#ifndef CONFIG_H
#define CONFIG_H

#include <GxEPD2_BW.h>

// Define pins for the e-paper display
#define EPD_CS 15
#define EPD_DC 27
#define EPD_RST 26
#define EPD_BUSY 25
#define EPD_SCK 13  // Match the Waveshare library pin
#define EPD_MOSI 14 // Match the Waveshare library pin

// Forward declaration of the display class
extern GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display;

// Screen dimensions for 1.54" e-paper display
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200
#define SCREEN_PADDING 4

// Tile
#define TILE_SIZE 16

// Map
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

// Game
#define GAME_START_X SCREEN_PADDING
#define GAME_START_Y SCREEN_PADDING
#define GAME_END_X (SCREEN_WIDTH - SCREEN_PADDING)
#define GAME_END_Y (SCREEN_HEIGHT - SCREEN_PADDING)

// Text
#define TEXT_BOX_START_X (GAME_START_X + TEXT_BOX_MARGIN)
#define TEXT_BOX_END_X (GAME_END_X - TEXT_BOX_MARGIN)
#define TEXT_BOX_END_Y (GAME_END_Y - TEXT_BOX_MARGIN)
#define TEXT_BOX_WIDTH (TEXT_BOX_END_X - TEXT_BOX_START_X)
#define TEXT_BOX_MARGIN 2
#define TEXT_BOX_PADDING 8
#define TEXT_BOX_LINE_SPACING 2
#define TEXT_BOX_TEXT_MAX_WIDTH (TEXT_BOX_WIDTH - (TEXT_BOX_PADDING * 2))

#endif
