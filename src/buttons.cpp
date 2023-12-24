//
// Created by Ben Datsko on 12/23/23.
//

#include "system.h"
#include "pins.h"
#include "buttons.h"

bool previousRightState = HIGH;
bool previousLeftState = HIGH;

void RunButtonHandler()
{
    static unsigned long lastDebounceTimeRight = 0;
    static unsigned long lastDebounceTimeLeft = 0;
    static bool rightButtonHandled = false;
    static bool leftButtonHandled = false;
    const unsigned long debounceDelay = 50;       // Debounce time in milliseconds
    const unsigned long holdDelay = 500;          // Delay after a button is held down
    static unsigned long lastButtonPressTime = 0; // New variable to track last press time
    const unsigned long buttonRateLimit = 200;    // Rate limit in milliseconds
    unsigned long currentTime = millis();

    bool currentRightState = digitalRead(BUTTON_RIGHT);
    bool currentLeftState = digitalRead(BUTTON_LEFT);

    // Check if enough time has passed since the last button press
    if (currentTime - lastButtonPressTime < buttonRateLimit)
    {
        return; // Exit if the button is pressed too quickly
    }

    // Right Button
    if (currentRightState != previousRightState)
    {
        lastDebounceTimeRight = millis();
    }
    if ((millis() - lastDebounceTimeRight) > debounceDelay)
    {
        if (currentRightState == LOW && !rightButtonHandled)
        {
            if (menuState < TOTAL_MENUS - 1)
            {
                menuState++;
                menuStateChanged = true;
                rightButtonHandled = true;
                leftButtonHandled = true;
                lastDebounceTimeRight = millis(); // Reset the debounce timer
            }
        }
        else if (currentRightState == HIGH)
        {
            rightButtonHandled = false;
            if (currentLeftState == HIGH)
            {
                leftButtonHandled = false;
            }
        }
    }
    else if (rightButtonHandled && (millis() - lastDebounceTimeRight) < holdDelay)
    {
        // Add a delay after the menu state is changed when the button is held down
        menuStateChanged = false;
    }
    previousRightState = currentRightState;

    // Left Button
    if (!rightButtonHandled && currentLeftState != previousLeftState)
    {
        lastDebounceTimeLeft = millis();
    }
    if (!rightButtonHandled && (millis() - lastDebounceTimeLeft) > debounceDelay)
    {
        if (currentLeftState == LOW && !leftButtonHandled)
        {
            if (menuState > 0)
            {
                menuState--;
                menuStateChanged = true;
                leftButtonHandled = true; // Set the flag
            }
        }
        else if (currentLeftState == HIGH)
        {
            leftButtonHandled = false; // Reset the flag when button released
        }
    }
    previousLeftState = currentLeftState;

    // Update the lastButtonPressTime for any button state change
    if (currentRightState != previousRightState || currentLeftState != previousLeftState)
    {
        lastButtonPressTime = currentTime;
    }
}
