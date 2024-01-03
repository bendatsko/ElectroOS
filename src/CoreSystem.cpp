#include <avr/wdt.h>
#include "SystemIncludes.h"
#include <SFE_MicroOLED.h>

unsigned long hours, minutes; // System time tracking

void InitializeHardware();

void InitializeDisplay();

void setup()
{
    wdt_enable(WDTO_2S);  // Initialize 2 second watchdog timer
    InitializeHardware(); // Definitions in pins.h/pins.cpp
    InitializeDisplay();  // Definitions in display.cpp
}

void loop()
{
    wdt_reset(); // Reset watchdog timer

    // Update runtime
    unsigned long now = millis();
    minutes = now / 60000;
    hours = minutes / 60;
    minutes %= 60;

    RunBMS();
    MenuRunner();

    Serial.println((analogRead(CURRENT_IN) / 1024.0) * 5.0);
}

void InitializeHardware()
{
    // 1. Start connections
    Serial.begin(115200); // Enable serial communication
    Wire.begin();         // Qwiic I2C bus @ 400kHz
    Wire.setClock(400000);

    // 2. Set pinmodes
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BOOST_CONVERTER_ENABLE, OUTPUT);
    pinMode(BOOST_CONVERTER_ISEL, OUTPUT); // Do not modify.
    pinMode(RELAY_ENABLE, OUTPUT);
    pinMode(B1_DISCHARGE_ENABLE, OUTPUT);
    pinMode(B1_DISCHARGE_ENABLE, OUTPUT);
    pinMode(B1_VOLTAGE, INPUT);
    pinMode(B2_VOLTAGE, INPUT);
    pinMode(B1_THERMISTOR, INPUT_PULLUP);
    pinMode(B2_THERMISTOR, INPUT_PULLUP);
    pinMode(CURRENT_IN, INPUT);

    // 3. Set initial state
    digitalWrite(BOOST_CONVERTER_ENABLE, HIGH); // High = on
    digitalWrite(BOOST_CONVERTER_ISEL, HIGH);   // Do not modify.
    digitalWrite(RELAY_ENABLE, LOW);            // Low = Off (use N.O.)
    digitalWrite(B1_DISCHARGE_ENABLE, LOW);     // Low = dont discharge
    digitalWrite(B1_DISCHARGE_ENABLE, LOW);     // Low = dont discharge
}

void InitializeDisplay()
{
    oled.begin(0x3D, Wire); // Connect display
    oled.clear(ALL);
    String title = "Electro"; // Show splash screen
    oled.clear(PAGE);
    oled.setCursor(DISPLAY_MIDDLE_X - (oled.getFontWidth() * (title.length() / 2)) - 4,
                   DISPLAY_MIDDLE_Y - (oled.getFontHeight() / 2));
    oled.print(title);
    oled.display();
    delay(1000);
    TriggerDisplayUpdate = true; // Force re-render
}