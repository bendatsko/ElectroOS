#include <SFE_MicroOLED.h>

#ifndef BATTERY_MANAGEMENT_SYSTEM_H
#define BATTERY_MANAGEMENT_SYSTEM_H

// ---------------------------- INPUT/OUTPUT PINS ----------------------------
// Buttons
#define BUTTON_RIGHT 2
#define BUTTON_LEFT 15
// 5V USB boost converter + relay
#define BOOST_CONVERTER_ENABLE 16
#define BOOST_CONVERTER_ISEL 14 // Do not modify.
#define RELAY_ENABLE 10
// Discharge n-fet gates
#define B1_DISCHARGE_ENABLE 7
#define B2_DISCHARGE_ENABLE 5
#define OUTPUT_ENABLE 1 // 1 = provide output, 0 = no output
// Analog input ports
#define B1_VOLTAGE 9
#define B2_VOLTAGE 6 // This is really D4
#define B1_THERMISTOR 7
#define B2_THERMISTOR 7 // D6 aka A7
#define CURRENT_IN 5 
#define MCU_OFF 0
#define NEOPIXEL 3

// ---------------------------- FUNCTION DECLARATIONS ----------------------------
void RunBMS();

void MenuRunner();

void RunButtonHandler();

// ---------------------------- GLOBAL VARIABLES AND OBJECTS ----------------------------
extern MicroOLED oled;
extern int DISPLAY_MIDDLE_X;               // CoreSystem.cpp
extern int DISPLAY_MIDDLE_Y;               // CoreSystem.cpp
extern int DISPLAY_MIDDLE_Y_HALF;          // CoreSystem.cpp
extern const int TOTAL_MENUS;              // DisplayController.cpp
extern bool TriggerDisplayUpdate;          // DisplayController.cpp
extern int menuState;                      // DisplayController.cpp
extern float AmortizedB1Voltage;           // BatteryManager.cpp
extern float AmortizedB2Voltage;           // BatteryManager.cpp
extern float AmortizedB1Temperature;       // BatteryManager.cpp
extern float AmortizedB2Temperature;       // BatteryManager.cpp
extern unsigned long hours;                // CoreSystem.cpp
extern unsigned long minutes;              // CoreSystem.cpp
extern unsigned long lastUpdateTime;       // CoreSystem.cpp
extern const unsigned long updateInterval; // CoreSystem.cpp

#endif // BATTERY_MANAGEMENT_SYSTEM_H
