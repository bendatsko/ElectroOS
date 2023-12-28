//
// Created by Ben Datsko on 12/23/23.
//
#include "pins.h"
#include "system.h"

void InitializePins()
{
    Wire.begin();           // Enable Qwiic connector I2C bus
    Wire.setClock(400000);  // Set Qwiic I2C to 400kHz
    oled.begin(0x3D, Wire); // Initialize OLED display with Qwiic connector address

    // Button Configuration
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);

    // Boost Converter
    pinMode(BOOST_CONVERTER_ENABLE, OUTPUT);
    pinMode(BISEL, OUTPUT);

    pinMode(B1_DISCHRG, OUTPUT);
    // Refactor consider: change to B1_0b_DO_DISCHARGE [1 = ]

    pinMode(B2_DISCHRG, OUTPUT);
    // Refactor consider: change to B1_0b_DO_DISCHARGE [1 = ]

    // Refactor consider: change to B1_0b_ [1 = ]
    pinMode(RELAY_ENABLE, OUTPUT);

    // Analog read
    pinMode(B1_THERMISTOR, INPUT);
    pinMode(B2_THERMISTOR, INPUT);
    pinMode(CURRENT_IN, INPUT);

    // Default configuration
    pinMode(B1_VOLTAGE, INPUT);
    pinMode(B2_VOLTAGE, INPUT);

    // Turn off discharge balancing
    digitalWrite(B1_DISCHRG, LOW); //
    digitalWrite(B2_DISCHRG, LOW);

    // Configure boost converter (and disable)
    digitalWrite(BOOST_CONVERTER_ENABLE, HIGH);
    digitalWrite(BISEL, HIGH); // Do not modify.

    // Turn off the relay
    digitalWrite(RELAY_ENABLE, LOW);
}