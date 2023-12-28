#include <SFE_MicroOLED.h>

#ifndef BATTERY_MANAGEMENT_SYSTEM_H
#define BATTERY_MANAGEMENT_SYSTEM_H

// ---------------------------- INPUT/OUTPUT PINS ----------------------------
// Buttons
#define BUTTON_RIGHT 7
#define BUTTON_LEFT 2
// 5V USB boost converter + relay
#define BOOST_CONVERTER_ENABLE 3
#define BISEL 5 // Do not modify.
#define RELAY_ENABLE 16
// Discharge n-fet gates
#define B1_DISCHARGE_ENABLE 14
#define B2_DISCHARGE_ENABLE 15
// Analog input ports
#define B1_VOLTAGE 9
#define B2_VOLTAGE 6
#define B1_THERMISTOR 7
#define B2_THERMISTOR 8
#define CURRENT_IN 10

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
