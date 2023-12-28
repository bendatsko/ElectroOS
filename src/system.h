//
// Created by Ben Datsko on 12/23/23.
//
#include <SFE_MicroOLED.h>
#include "pins.h"

#ifndef ALLEGROOS_SYSTEM_H
#define ALLEGROOS_SYSTEM_H

// --- I/O pins ---
void InitializePins();

// --- Display/Menu ---
inline MicroOLED oled(PIN_RESET);
void InitializeDisplay();
inline int DISPLAY_MIDDLE_X = oled.getLCDWidth() / 2;
inline int DISPLAY_MIDDLE_Y = oled.getLCDHeight() / 2;
inline int DISPLAY_MIDDLE_Y_HALF = DISPLAY_MIDDLE_Y / 2;
extern const int TOTAL_MENUS;
extern bool menuStateChanged;
extern int menuState;

// BMS
extern float amortizedB1Voltage;
extern float amortizedB2Voltage;

extern float amortizedB1Temperature;
extern float amortizedB2Temperature;

// --- Core Tasks ---
void RunMenu();
void RunBMS();

void PlayMainMenu();

#endif // ALLEGROOS_SYSTEM_H
