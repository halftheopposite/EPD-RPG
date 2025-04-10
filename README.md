# EPD-RPG

A retro-style RPG game engine for e-paper displays (EPD) with procedural content generation.

<img src="./images/example.jpeg" alt="EPD-RPG Example" width="400">

## Overview

EPD-RPG is a project that provides a C++ game engine designed for e-paper displays, specifically targeting the Waveshare 1.54" V2 black and white e-paper display (200x200 pixels).

### Key Concepts

- **Procedural Content Generation**: The game generates content procedurally over time, using a combination of existing maps, situations, and narratives.
- **Educational Resource**: This project serves as a learning resource for developers and creators interested in e-paper displays, embedded systems programming, and game development. The code is extensively documented to facilitate learning.

## Hardware Requirements

- ESP32 development board
- Waveshare 1.54" V2 black and white e-paper display (200x200 pixels)
- Connecting wires

### Pin Configuration

| E-Paper Pin | ESP32 Pin |
| ----------- | --------- |
| CS          | 15        |
| DC          | 27        |
| RST         | 26        |
| BUSY        | 25        |
| SCK         | 13        |
| MOSI        | 14        |

## Software Components

The EPD-RPG engine is built using:

- VSCode as the development environment
- PlatformIO for project management and building
- GxEPD2 library for e-paper display control
- Adafruit GFX library for graphics rendering

Key features:

- Tilemap rendering system
- Text display system with automatic wrapping
- UI components
- Game state management
- Procedural content generation
- Low power consumption for long battery life

## Getting Started

1. Clone this repository:
   ```
   git clone https://github.com/halftheopposite/EPD-RPG.git
   cd EPD-RPG
   ```
2. Open the project in PlatformIO (VSCode with PlatformIO extension recommended)
3. Connect your ESP32 to your computer
4. Build and upload the project:
   ```
   pio run -t upload
   ```

**Note:** I've also created a tilemap editor to export maps into bytes array. Check it out [here](https://halftheopposite.github.io/arduino-tilemap-editor/).

## Development

### Adding New Maps

1. Create your maps as C++ arrays in header files
2. Place the files in the `include/assets/` directory
3. Update `include/assets/maps.h` to include your new maps
4. Update `include/assets/sprites.h` to include the sprites used in your maps

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- [GxEPD2 Library](https://github.com/ZinggJM/GxEPD2) by Jean-Marc Zingg
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Waveshare](https://www.waveshare.com/) for their e-paper display modules
