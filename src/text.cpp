#include "text.h"
#include "config.h"
#include <Fonts/FreeMonoBold9pt7b.h>
#include <string.h>

void Text_DrawBox(const char *text, uint8_t borderWidth, uint8_t padding)
{
    // Set font for text rendering
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);

    // Set maximum width for the text content (constrained by game area and padding)
    uint16_t maxTextWidth = GAME_END_X - GAME_START_X - (SCREEN_PADDING * 2);

    // Get font metrics for line height calculation
    int16_t dummy_x, dummy_y;
    uint16_t dummy_w, line_height;
    display.getTextBounds("Ay", 0, 0, &dummy_x, &dummy_y, &dummy_w, &line_height);

    // Parse the text to determine how many lines we need and the width of each line
    const int MAX_LINES = 10;        // Maximum number of lines to support
    const int MAX_LINE_LENGTH = 100; // Maximum characters per line
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int lineCount = 0;
    int lineWidths[MAX_LINES];
    int maxLineWidth = 0;

    // Copy the input text so we can modify it
    char textCopy[strlen(text) + 1];
    strcpy(textCopy, text);

    // Split the text into words
    char *word = strtok(textCopy, " ");
    char currentLine[MAX_LINE_LENGTH] = "";

    while (word != NULL && lineCount < MAX_LINES)
    {
        // Create a test line by adding the next word
        char testLine[MAX_LINE_LENGTH];
        if (strlen(currentLine) == 0)
        {
            strcpy(testLine, word);
        }
        else
        {
            sprintf(testLine, "%s %s", currentLine, word);
        }

        // Check if the test line fits within the maximum width
        int16_t test_x, test_y;
        uint16_t test_w, test_h;
        display.getTextBounds(testLine, 0, 0, &test_x, &test_y, &test_w, &test_h);

        if (test_w <= maxTextWidth)
        {
            // The word fits, add it to the current line
            strcpy(currentLine, testLine);
        }
        else
        {
            // The word doesn't fit, start a new line
            if (strlen(currentLine) > 0)
            {
                // Save the current line
                strcpy(lines[lineCount], currentLine);
                int16_t tbx, tby;
                uint16_t tbw, tbh;
                display.getTextBounds(currentLine, 0, 0, &tbx, &tby, &tbw, &tbh);
                lineWidths[lineCount] = tbw;
                if (lineWidths[lineCount] > maxLineWidth)
                {
                    maxLineWidth = lineWidths[lineCount];
                }
                lineCount++;

                // Start a new line with the current word
                strcpy(currentLine, word);
            }
            else
            {
                // The word is too long for a line, we need to truncate it
                // For simplicity, just use the word as is and let it be clipped
                strcpy(lines[lineCount], word);
                int16_t tbx, tby;
                uint16_t tbw, tbh;
                display.getTextBounds(word, 0, 0, &tbx, &tby, &tbw, &tbh);
                lineWidths[lineCount] = tbw;
                if (lineWidths[lineCount] > maxLineWidth)
                {
                    maxLineWidth = lineWidths[lineCount];
                }
                lineCount++;
                currentLine[0] = '\0'; // Reset current line
            }
        }

        // Get the next word
        word = strtok(NULL, " ");

        // If this is the last word, add the current line
        if (word == NULL && strlen(currentLine) > 0 && lineCount < MAX_LINES)
        {
            strcpy(lines[lineCount], currentLine);
            int16_t tbx, tby;
            uint16_t tbw, tbh;
            display.getTextBounds(currentLine, 0, 0, &tbx, &tby, &tbw, &tbh);
            lineWidths[lineCount] = tbw;
            if (lineWidths[lineCount] > maxLineWidth)
            {
                maxLineWidth = lineWidths[lineCount];
            }
            lineCount++;
        }
    }

    // If no lines were created (empty text), create at least one empty line
    if (lineCount == 0)
    {
        strcpy(lines[0], "");
        lineWidths[0] = 0;
        lineCount = 1;
    }

    // Always use the maximum width for the box
    uint16_t boxWidth = GAME_END_X - GAME_START_X;
    uint16_t boxHeight = (lineCount * (line_height + 4)) + (padding * 2); // Add some extra space between lines

    // Position the box at GAME_START_X
    uint16_t boxX = GAME_START_X;

    // Calculate the Y position based on the tilemap position
    // This positions the text box below the tilemap
    uint16_t boxY = GAME_START_Y + (MAP_HEIGHT * TILE_SIZE) + SCREEN_PADDING;

    // Make sure the box doesn't go off-screen
    if (boxY + boxHeight > SCREEN_HEIGHT - SCREEN_PADDING)
    {
        boxY = SCREEN_HEIGHT - boxHeight - SCREEN_PADDING;
    }

    // Draw the box with border
    display.fillRect(boxX, boxY, boxWidth, boxHeight, GxEPD_WHITE); // White background

    // Draw border around the box
    for (uint8_t i = 0; i < borderWidth; i++)
    {
        display.drawRect(boxX + i, boxY + i, boxWidth - (i * 2), boxHeight - (i * 2), GxEPD_BLACK);
    }

    // Draw the text line by line
    int16_t cursorY = boxY + padding - dummy_y; // Initial Y position

    for (int i = 0; i < lineCount; i++)
    {
        // Calculate the X position for this line (center each line)
        int16_t cursorX;

        // Get the width of this line
        int16_t tx, ty;
        uint16_t tw, th;
        display.getTextBounds(lines[i], 0, 0, &tx, &ty, &tw, &th);

        // Align the text to the left with padding
        cursorX = boxX + padding - tx;

        // Draw this line of text
        display.setCursor(cursorX, cursorY);
        display.print(lines[i]);

        // Move to the next line
        cursorY += line_height + 4; // Add some extra space between lines
    }
}
