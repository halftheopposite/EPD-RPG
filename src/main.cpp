#include <Arduino.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "assets/maps.h"
#include "config.h"
#include "text.h"
#include "tilemap.h"
#include "ui.h"

// Create the display instance - using GxEPD2_154_D67 for 1.54" b/w display (200x200)
// This is for the Waveshare 1.54" V2 black and white e-paper display
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

void setup()
{
  Serial.begin(115200);

  // Initialize SPI with custom pins
  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);

  // Initialize the display
  display.init();

  // Clear the display with white background
  display.setFullWindow();
  display.firstPage();
  display.setRotation(3);
  do
  {
    display.fillScreen(GxEPD_WHITE);

    UI_Draw();
    Tilemap_Draw(MAP_HOME_1, GAME_START_X, GAME_START_Y);
    Text_Draw("Hey there, welcome to this e-ink autonomous RPG adventure!");
  } while (display.nextPage());

  // Put the display to sleep to save power
  display.hibernate();
}

void loop()
{
}
