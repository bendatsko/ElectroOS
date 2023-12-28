//
// Created by Ben Datsko on 12/23/23.
//

#ifndef SYSTEM_PINS_H
#define SYSTEM_PINS_H
#include <limits.h>

// Digital Pin Definitions in Ascending Order
const int PIN_RESET = 9; // Implicitly defined for qwiic

const int BUTTON_LEFT = 2;
const int BUTTON_RIGHT = 7;

const int BOOST_CONVERTER_ENABLE = 3; // For boost converter. Low = off, high = on.
const int BISEL = 5;                  // For boost converter.

const int B1_DISCHRG = 14; // May need revision
const int B2_DISCHRG = 15; // May need revision

const int RELAY_ENABLE = 16;
// const int ENABLE_OUTPUT = INFINITY; // In V1 this was left unspecified. Should go to digital.

// Analog Input Pin Definitions in Ascending Order
const int B1_VOLTAGE = 9; // Pin 9 = Digital9 or analog9
const int B2_VOLTAGE = 6; // Pin 4 = Digital4 or analog6

const int B1_THERMISTOR = 7; // Pin 6 = Digital6 or analog7
const int B2_THERMISTOR = 8; // Pin 8 = Digital8 or analog8
const int CURRENT_IN = 10;   // Pin 10 = Digital
#endif                       // SYSTEM_PINS_H
