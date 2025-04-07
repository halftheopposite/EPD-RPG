#include <Arduino.h>
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "assets/maps.h"
#include "assets/sprites.h"
#include "config.h"
#include "draw.h"
#include "player.h"
#include "tilemap.h"
#include "ui.h"

void setup()
{
  // Initialize the device
  DEV_Module_Init();

  // Initialize the display
  EPD_1IN54_V2_Init();
  EPD_1IN54_V2_Clear();
  DEV_Delay_ms(500);

  // Allocate framebuffer
  UBYTE *frameBuffer;
  UWORD ImageSize = ((EPD_1IN54_V2_WIDTH % 8 == 0) ? (EPD_1IN54_V2_WIDTH / 8) : (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;

  frameBuffer = (UBYTE *)malloc(ImageSize);
  if (frameBuffer == NULL)
  {
    printf("Memory allocation failed\r\n");
    return;
  }

  // Initialize the paint library (270 degrees rotation is needed for this display)
  Paint_NewImage(frameBuffer, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
  Paint_SelectImage(frameBuffer);
  Paint_Clear(WHITE);

  // Draw
  UI_Draw(frameBuffer);
  Tilemap_Draw(frameBuffer, MAP_TEST, GAME_TL_X, GAME_TL_Y);
  Player_Draw(frameBuffer, 2, 2);

  // Send the framebuffer to the display
  EPD_1IN54_V2_Display(frameBuffer);

  // Wait for a while
  // DEV_Delay_ms(5000);

  // Cleanup the display
  EPD_1IN54_V2_Init();
  EPD_1IN54_V2_Clear();

  // Put the device to sleep
  EPD_1IN54_V2_Sleep();

  // Free the framebuffer
  free(frameBuffer);
  frameBuffer = NULL;
}

void loop()
{
  // No need for loop in this demo
}
