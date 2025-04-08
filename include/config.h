#ifndef CONFIG_H
#define CONFIG_H

#include <GxEPD2_BW.h> // GxEPD2 library for black and white displays

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

// Tile types
#define TILE_EMPTY 0
#define TILE_FULL 1

// Map
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

// UI
#define UI_PADDING_HALF SCREEN_PADDING / 2

#define UI_TL_X UI_PADDING_HALF
#define UI_TL_Y UI_PADDING_HALF

#define UI_TR_X SCREEN_WIDTH - UI_PADDING_HALF
#define UI_TR_Y UI_PADDING_HALF

#define UI_BL_X UI_PADDING_HALF
#define UI_BL_Y SCREEN_HEIGHT - UI_PADDING_HALF - 1

#define UI_BR_X SCREEN_WIDTH - UI_PADDING_HALF
#define UI_BR_Y SCREEN_HEIGHT - UI_PADDING_HALF - 1

// Game
#define GAME_TL_X SCREEN_PADDING
#define GAME_TL_Y SCREEN_PADDING

#define GAME_TR_X SCREEN_WIDTH - SCREEN_PADDING
#define GAME_TR_Y SCREEN_PADDING

#define GAME_BL_X SCREEN_PADDING
#define GAME_BL_Y SCREEN_HEIGHT - SCREEN_PADDING

#define GAME_BR_X SCREEN_WIDTH - SCREEN_PADDING
#define GAME_BR_Y SCREEN_HEIGHT - SCREEN_PADDING

// Player
#define PLAYER_SIZE 16

#endif
