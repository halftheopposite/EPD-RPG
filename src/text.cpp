#include "text.h"
#include "config.h"
#include <Fonts/FreeMonoBold9pt7b.h>
#include <string.h>

void GetTextBounds(const char *text, TextBounds *bounds)
{
    // Variables to store the text bounds
    int16_t x, y;
    uint16_t w, h;

    // Get the text bounds from the display
    display.getTextBounds(text, 0, 0, &x, &y, &w, &h);

    // Store the results in the bounds struct if provided
    if (bounds)
    {
        bounds->width = w;
        bounds->height = h;
        bounds->x = x;
        bounds->y = y;
    }
}

int AddLine(char lines[][MAX_LINE_LENGTH], int lineCount, const char *text, uint16_t lineWidths[], uint16_t *maxLineWidth)
{
    // Check if we've reached the maximum number of lines
    if (lineCount >= MAX_LINES)
        return lineCount;

    // Copy the text to the lines array
    strcpy(lines[lineCount], text);

    // Measure the line width
    TextBounds lineBounds;
    GetTextBounds(text, &lineBounds);
    lineWidths[lineCount] = lineBounds.width;

    // Update max line width if this line is wider
    if (lineWidths[lineCount] > *maxLineWidth)
    {
        *maxLineWidth = lineWidths[lineCount];
    }

    // Return the incremented line count
    return lineCount + 1;
}

int WrapText(const char *text, uint16_t maxWidth, char lines[][MAX_LINE_LENGTH], uint16_t lineWidths[], uint16_t *maxLineWidth)
{
    int lineCount = 0;
    *maxLineWidth = 0;

    // Handle empty or null text
    if (!text || strlen(text) == 0)
    {
        return AddLine(lines, lineCount, "", lineWidths, maxLineWidth);
    }

    // Copy the input text so we can modify it with strtok
    char textCopy[strlen(text) + 1];
    strcpy(textCopy, text);

    // Split the text into words
    char *word = strtok(textCopy, " ");
    char currentLine[MAX_LINE_LENGTH] = "";

    // Process each word
    while (word != NULL && lineCount < MAX_LINES)
    {
        // Create a test line by adding the next word
        char testLine[MAX_LINE_LENGTH];
        if (strlen(currentLine) == 0)
        {
            strcpy(testLine, word); // First word on the line
        }
        else
        {
            sprintf(testLine, "%s %s", currentLine, word); // Add word with space
        }

        // Check if the test line fits within the maximum width
        TextBounds testBounds;
        GetTextBounds(testLine, &testBounds);

        if (testBounds.width <= maxWidth)
        {
            // The word fits, add it to the current line
            strcpy(currentLine, testLine);
        }
        else
        {
            // The word doesn't fit, start a new line
            if (strlen(currentLine) > 0)
            {
                // Save the current line and update line count
                lineCount = AddLine(lines, lineCount, currentLine, lineWidths, maxLineWidth);

                // Start a new line with the current word
                strcpy(currentLine, word);
            }
            else
            {
                // The word is too long for a line, add it anyway (will be clipped)
                lineCount = AddLine(lines, lineCount, word, lineWidths, maxLineWidth);
                currentLine[0] = '\0'; // Reset current line
            }
        }

        // Get the next word
        word = strtok(NULL, " ");

        // If this is the last word, add the current line
        if (word == NULL && strlen(currentLine) > 0 && lineCount < MAX_LINES)
        {
            lineCount = AddLine(lines, lineCount, currentLine, lineWidths, maxLineWidth);
        }
    }

    // If no lines were created (should not happen with our empty text check), create an empty line
    if (lineCount == 0)
    {
        lineCount = AddLine(lines, lineCount, "", lineWidths, maxLineWidth);
    }

    return lineCount;
}

void DrawBox(int startX, int startY, int boxWidth, int boxHeight)
{
    display.fillRect(startX, startY, boxWidth, boxHeight, GxEPD_WHITE);
    display.drawRect(startX, startY, boxWidth, boxHeight, GxEPD_BLACK);
}

void Text_Draw(const char *text)
{
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);

    // Get font metrics for line height calculation using representative characters
    TextBounds metrics;
    GetTextBounds("Aj|", &metrics); // Characters with ascenders, descenders, and full height
    uint16_t lineHeight = metrics.height;
    int16_t baselineY = metrics.y;

    // Arrays to store the wrapped text lines
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    uint16_t lineWidths[MAX_LINES];
    uint16_t maxLineWidth = 0;

    // Wrap the text into lines based on the available width
    int lineCount = WrapText(text, TEXT_BOX_TEXT_MAX_WIDTH, lines, lineWidths, &maxLineWidth);

    // Calculate total text height
    uint16_t textHeight = lineCount * lineHeight;

    // Add spacing between lines (but not after the last line)
    if (lineCount > 1)
    {
        textHeight += (lineCount - 1) * TEXT_BOX_LINE_SPACING;
    }

    // Add equal padding at top and bottom
    uint16_t boxHeight = textHeight + (TEXT_BOX_PADDING * 2);
    uint16_t startY = TEXT_BOX_END_Y - boxHeight;

    // Draw the box
    DrawBox(TEXT_BOX_START_X, startY, TEXT_BOX_WIDTH, boxHeight);

    // Calculate the position of the first line with consistent padding
    int16_t cursorY = startY + TEXT_BOX_PADDING - baselineY;

    // Draw each line of text
    for (int i = 0; i < lineCount; i++)
    {
        // Get the text bounds for proper positioning
        TextBounds lineBounds;
        GetTextBounds(lines[i], &lineBounds);

        // Align the text to the left with padding
        // The negative lineBounds.x accounts for the text bounds offset
        int16_t cursorX = TEXT_BOX_START_X + TEXT_BOX_PADDING - lineBounds.x;

        // Draw this line of text
        display.setCursor(cursorX, cursorY);
        display.print(lines[i]);

        // Move to the next line (add line height and spacing)
        cursorY += lineHeight + TEXT_BOX_LINE_SPACING;
    }
}
