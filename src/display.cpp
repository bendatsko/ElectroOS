//
// Created by Ben Datsko on 12/23/23.
//
#include <SFE_MicroOLED.h>
#include <Wire.h>
#include "bitmaps.h"
#include "system.h"
#include "pins.h"
#include "uptime.h"
#include "buttons.h"

const int TOTAL_MENUS = 6;
bool menuStateChanged = false; // default value

enum MenuState
{
    STATE_SYSTEM_MENU,
    STATE_CELL_MENU,
    STATE_MAIN_MENU,
    STATE_ABOUT_MENU,
    STATE_HELP_MENU,
    STATE_QR_MENU,
    STATE_CONTACT_MENU
};
MenuState currentState = STATE_MAIN_MENU;
int menuState = 3;

// Helper functions
void DrawNavigationArrow(int x, int y, bool isLeftArrow)
{
    int lineLength = 3;
    if (isLeftArrow)
    {
        oled.line(x, y, x + lineLength, y - lineLength);
        oled.line(x, y, x + lineLength, y + lineLength);
    }
    else
    {
        oled.line(x, y, x - lineLength, y - lineLength);
        oled.line(x, y, x - lineLength, y + lineLength);
    }
}
void PrintHeader(String title)
{
    // Print title
    int characterWidth = oled.getFontWidth(); // Width of single character
    int spacing = 1;                          // Estimated spacing between characters
    int titleWidth = characterWidth * title.length() + spacing * (title.length() - 1);
    int titleX = DISPLAY_MIDDLE_X - titleWidth / 2;
    oled.setCursor(titleX, DISPLAY_MIDDLE_Y_HALF / 2 - (oled.getFontHeight() / 2));
    oled.print(title);

    // Left arrow
    if (menuState > 0)
    {
        DrawNavigationArrow(2, DISPLAY_MIDDLE_Y_HALF / 2, true); // Left arrow
    }

    // Right arrow
    if (menuState < TOTAL_MENUS - 1)
    {
        DrawNavigationArrow(oled.getLCDWidth() - 2, DISPLAY_MIDDLE_Y_HALF / 2, false); // Right arrow
    }

    oled.display();
}

// Menus (in order of display)
void PlayQRMenu()
{
    if (currentState == STATE_QR_MENU)
    {
        oled.drawBitmap(DocumentationQRCode); // Draw QR code
        oled.display();
    }
}
void PlayContactMenu()
{
    if (currentState == STATE_CONTACT_MENU)
    {
        PrintHeader("Contact");
        oled.setCursor(0, DISPLAY_MIDDLE_Y - 12);
        oled.print("bdatsko\nlwormald \n\n@umich.edu");
        oled.display();
    }
}
void PlayAboutMenu()
{
    if (currentState == STATE_ABOUT_MENU)
    {
        PrintHeader("About");
        oled.setCursor(0, DISPLAY_MIDDLE_Y - 12);
        oled.print("Low-noise PSU 5-8V. 2mV Pk-Pk ripple.");
        oled.display();
    }
}
void PlayMainMenu()
{
    if (currentState == STATE_MAIN_MENU)
    {
        PrintHeader("Home");

        oled.setCursor(0, DISPLAY_MIDDLE_Y - 12);
        oled.print("Output OFF");
        oled.setCursor(0, DISPLAY_MIDDLE_Y - 4);
        oled.print("Charge 87%");
        oled.setCursor(0, DISPLAY_MIDDLE_Y + 12);
        oled.print("*Charging*");

        oled.display();
    }
}
void PlayCellMenu()
{
    if (currentState == STATE_CELL_MENU)
    {
        PrintHeader("Cells");

        oled.line(oled.getLCDWidth() / 2, DISPLAY_MIDDLE_Y_HALF, oled.getLCDWidth() / 2, oled.getLCDHeight());
        oled.line(0, DISPLAY_MIDDLE_Y_HALF + 10, oled.getLCDWidth(), DISPLAY_MIDDLE_Y_HALF + 10);

        char buffer[10]; // Buffer to hold the float converted to string
        // Convert amortizedB1Voltage to a string with 2 decimal places
        dtostrf(amortizedB1Voltage, 4, 2, buffer);
        String b1VoltageStr = String(buffer);

        // Convert amortizedB2Voltage to a string with 2 decimal places
        dtostrf(amortizedB2Voltage, 4, 2, buffer);
        String b2VoltageStr = String(buffer);

        dtostrf(amortizedB1Temperature, 4, 2, buffer);
        String b1TempStr = String(buffer);

        // Convert amortizedB2Voltage to a string with 2 decimal places
        dtostrf(amortizedB2Temperature, 4, 2, buffer);
        String b2TempStr = String(buffer);

        // Battery 1 values
        int Loffset = 0;
        oled.setCursor(Loffset, DISPLAY_MIDDLE_Y - 12);
        oled.print("Batt1");
        oled.setCursor(Loffset, DISPLAY_MIDDLE_Y + 2);
        oled.print(b1VoltageStr); // Print the formatted string
        oled.setCursor(Loffset, DISPLAY_MIDDLE_Y + 12);
        oled.print(b1TempStr);

        // Battery 2 values
        int Roffset = oled.getLCDWidth() - 29;
        oled.setCursor(Roffset, DISPLAY_MIDDLE_Y - 12);
        oled.print("Batt2");
        oled.setCursor(Roffset, DISPLAY_MIDDLE_Y + 2);
        oled.print(b2VoltageStr); // Print the formatted string
        oled.setCursor(Roffset, DISPLAY_MIDDLE_Y + 12);
        oled.print(b2TempStr);

        // Render to screen
        oled.display();
    }
}
void PlaySystemMenu()
{
    if (currentState == STATE_SYSTEM_MENU)
    {
        PrintHeader("System");

        // Current draw
        oled.setCursor(0, DISPLAY_MIDDLE_Y - 10);
        oled.print("CRNT:2.1A");

        // Battery cell (who's bleeding charge into who to balance)
        oled.setCursor(0, DISPLAY_MIDDLE_Y - 2);
        oled.print("BAL:1->2");

        // Uptime
        char uptimeStr[6];
        sprintf(uptimeStr, "%02lu:%02lu", hours, minutes);
        oled.setCursor(0, DISPLAY_MIDDLE_Y + 6);
        oled.print("UT:");
        oled.print(uptimeStr);

        // Render to screen
        oled.display();
    }
}

// Drivers
void InitializeDisplay()
{
    oled.clear(ALL);
    String title = "Electro";

    // Display splash
    oled.clear(PAGE);
    oled.setCursor(DISPLAY_MIDDLE_X - (oled.getFontWidth() * (title.length() / 2)) - 4,
                   DISPLAY_MIDDLE_Y - (oled.getFontHeight() / 2));
    oled.print(title);
    oled.display();
    delay(1000);
    menuStateChanged = true; // Trigger menu update to enter main FSM
}

void RunMenu()
{
    // Start button handler
    RunButtonHandler();

    // Start menu state machine
    if (menuStateChanged)
    {
        // Clear screen
        oled.clear(PAGE);
        // Update screen based on new state
        switch (menuState)
        {
        case 0:
            currentState = STATE_QR_MENU;
            PlayQRMenu();
            break;
        case 1:
            currentState = STATE_CONTACT_MENU;
            PlayContactMenu();
            break;
        case 2:
            currentState = STATE_ABOUT_MENU;
            PlayAboutMenu();
            break;
        case 3:
            currentState = STATE_MAIN_MENU;
            PlayMainMenu();
            break;
        case 4:
            currentState = STATE_CELL_MENU;
            PlayCellMenu();
            break;
        case 5:
            currentState = STATE_SYSTEM_MENU;
            PlaySystemMenu();
            break;
        default:
            currentState = STATE_MAIN_MENU;
            PlayMainMenu();
            break;
        }
    }
    menuStateChanged = false;
}
