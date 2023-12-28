#include <SFE_MicroOLED.h>
#include "SystemIncludes.h"
#include "bitmaps.h"

MicroOLED oled(9);
int DISPLAY_MIDDLE_X = oled.getLCDWidth() / 2;
int DISPLAY_MIDDLE_Y = oled.getLCDHeight() / 2;
int DISPLAY_MIDDLE_Y_HALF = DISPLAY_MIDDLE_Y / 2;
bool TriggerDisplayUpdate;

// Menus
void MenuRunner(); // Driver

void PlayQRMenu();

void PlayContactMenu();

void PlayAboutMenu();

void PlayMainMenu();

void PlayCellMenu();

void PlaySystemMenu();

// Helper functions
void PrintHeader(String title);

void DrawNavigationArrow(int x, int y, bool isLeftArrow);

void DrawCellMenuDividers();

void DisplayBatteryInfo(const String &batteryLabel, float voltage, float temperature, int xOffset);

String FloatToString(float value, int width, int precision);

// ---------------------------- MENUS ---------------------------- //
const int TOTAL_MENUS = 6;
int menuState = 3;

void MenuRunner()
{
    RunButtonHandler();
    if (TriggerDisplayUpdate)
    {
        oled.clear(PAGE);
        switch (menuState)
        {
        case 0:
            PlayQRMenu();
            break;
        case 1:
            PlayContactMenu();
            break;
        case 2:
            PlayAboutMenu();
            break;
        case 3:
            PlayMainMenu();
            break;
        case 4:
            PlayCellMenu();
            break;
        case 5:
            PlaySystemMenu();
            break;
        default:
            PlayMainMenu();
            break;
        }
    }
    TriggerDisplayUpdate = false;
}

void PlayQRMenu()
{
    PrintHeader("");
    oled.drawBitmap(DocumentationQRCode);
    oled.display();
}

void PlayContactMenu()
{
    PrintHeader("Contact");
    oled.setCursor(0, DISPLAY_MIDDLE_Y - 12);
    oled.print("bdatsko\nlwormald \n\n@umich.edu");
    oled.display();
}

void PlayAboutMenu()
{
    PrintHeader("About");
    oled.setCursor(0, DISPLAY_MIDDLE_Y - 12);
    oled.print("Low-noise 5V PSU. 2mV Pk-Pk ripple.");
    oled.display();
}

void PlayMainMenu()
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

void PlayCellMenu()
{
    PrintHeader("Cells");
    DrawCellMenuDividers();
    DisplayBatteryInfo("Batt1", AmortizedB1Voltage, AmortizedB1Temperature, 0);
    DisplayBatteryInfo("Batt2", AmortizedB2Voltage, AmortizedB2Temperature, oled.getLCDWidth() - 29);
    oled.display();
}

void PlaySystemMenu()
{
    PrintHeader("System");
    oled.setCursor(0, DISPLAY_MIDDLE_Y - 10); // Current draw
    oled.print("CRNT:2.1A");
    oled.setCursor(0, DISPLAY_MIDDLE_Y - 2); // Discharge indicator
    oled.print("BAL:1->2");

    // Uptime
    char uptimeStr[6];
    sprintf(uptimeStr, "%02lu:%02lu", hours, minutes);
    oled.setCursor(0, DISPLAY_MIDDLE_Y + 6);
    oled.print("UT:");
    oled.print(uptimeStr);

    oled.display();
}

// ---------------------------- HELPER FUNCTIONS ---------------------------- //
void PrintHeader(String title)
{
    // Draw left arrow if we're not at the first menu
    if (menuState > 0)
    {
        DrawNavigationArrow(2, DISPLAY_MIDDLE_Y_HALF / 2, true);
    }

    // Draw a right arrow if we're not at the last menu
    if (menuState < TOTAL_MENUS - 1)
    {
        DrawNavigationArrow(oled.getLCDWidth() - 2, DISPLAY_MIDDLE_Y_HALF / 2, false);
    }

    int characterWidth = oled.getFontWidth();
    int spacing = 1;
    int titleWidth = characterWidth * title.length() + spacing * (title.length() - 1);
    int titleX = DISPLAY_MIDDLE_X - titleWidth / 2;
    oled.setCursor(titleX, DISPLAY_MIDDLE_Y_HALF / 2 - (oled.getFontHeight() / 2));
    oled.print(title);
    oled.display();
}

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

void DrawCellMenuDividers()
{
    oled.line(oled.getLCDWidth() / 2, DISPLAY_MIDDLE_Y_HALF, oled.getLCDWidth() / 2,
              oled.getLCDHeight());                                                           // Vertical line in the middle
    oled.line(0, DISPLAY_MIDDLE_Y_HALF + 10, oled.getLCDWidth(), DISPLAY_MIDDLE_Y_HALF + 10); // Horizontal line
}

void DisplayBatteryInfo(const String &batteryLabel, float voltage, float temperature, int xOffset)
{
    String voltageStr = FloatToString(voltage, 4, 1) + "V";
    String tempStr = FloatToString(temperature, 4, 1) + "C";

    // Display label
    oled.setCursor(xOffset, DISPLAY_MIDDLE_Y - 12);
    oled.print(batteryLabel);

    // Display voltage
    oled.setCursor(xOffset, DISPLAY_MIDDLE_Y + 2);
    oled.print(voltageStr);

    // Display temperature
    oled.setCursor(xOffset, DISPLAY_MIDDLE_Y + 12);
    oled.print(tempStr);
}

String FloatToString(float value, int width, int precision)
{
    char buffer[10];
    dtostrf(value, width, precision, buffer);
    return String(buffer);
}