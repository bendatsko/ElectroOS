//
// Created by Ben Datsko on 12/23/23.
//
#include "pins.h"
#include "system.h"

void InitializePins()
{
    Serial.begin(115200);   // Enable serial communication
    Wire.begin();           // Enable Qwiic connector I2C bus
    Wire.setClock(400000);  // Set Qwiic I2C to 400kHz
    oled.begin(0x3D, Wire); // Initialize OLED display with Qwiic connector address

    // BMS Pin Configuration
    pinMode(NBAL1, OUTPUT);
    pinMode(NBAL2, OUTPUT);
    pinMode(BOOST_CONVERTER_PIN, OUTPUT);
    pinMode(MOSPIN, OUTPUT);
    pinMode(RELAYFETS, OUTPUT);

    // Button Configuration
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);

    // Set Initial States of Pins
    digitalWrite(NBAL1, LOW);
    digitalWrite(NBAL2, LOW);
    digitalWrite(BOOST_CONVERTER_PIN, LOW);
    digitalWrite(MOSPIN, HIGH);
    digitalWrite(RELAYFETS, HIGH);
}