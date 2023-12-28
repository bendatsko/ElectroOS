#include "SystemIncludes.h"

bool previousRightState = HIGH;
bool previousLeftState = HIGH;

void HandleRightButton(unsigned long &lastDebounceTime, bool &buttonHandled, unsigned long currentTime,
                       bool currentRightState)
{
    const unsigned long debounceDelay = 20;
    const unsigned long holdDelay = 20;

    if (currentRightState != previousRightState)
    {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (currentRightState == LOW && !buttonHandled)
        {
            if (menuState < TOTAL_MENUS - 1)
            {
                menuState++;
                TriggerDisplayUpdate = true;
                buttonHandled = true;
                lastDebounceTime = millis(); // Reset the debounce timer
            }
        }
        else if (currentRightState == HIGH)
        {
            buttonHandled = false;
        }
    }
    else if (buttonHandled && (millis() - lastDebounceTime) < holdDelay)
    {
        TriggerDisplayUpdate = false;
    }
}

void HandleLeftButton(unsigned long &lastDebounceTime, bool &buttonHandled, unsigned long currentTime, bool currentLeftState,
                      bool rightButtonHandled)
{
    const unsigned long debounceDelay = 20;

    if (!rightButtonHandled && currentLeftState != previousLeftState)
    {
        lastDebounceTime = millis();
    }
    if (!rightButtonHandled && (millis() - lastDebounceTime) > debounceDelay)
    {
        if (currentLeftState == LOW && !buttonHandled)
        {
            if (menuState > 0)
            {
                menuState--;
                TriggerDisplayUpdate = true;
                buttonHandled = true;
            }
        }
        else if (currentLeftState == HIGH)
        {
            buttonHandled = false;
        }
    }
}

void RunButtonHandler()
{
    static unsigned long lastDebounceTimeRight = 0;
    static unsigned long lastDebounceTimeLeft = 0;
    static bool rightButtonHandled = false;
    static bool leftButtonHandled = false;
    static unsigned long lastButtonPressTime = 0; // Declare lastButtonPressTime here
    const unsigned long buttonRateLimit = 20;
    unsigned long currentTime = millis();

    bool currentRightState = digitalRead(BUTTON_RIGHT);
    bool currentLeftState = digitalRead(BUTTON_LEFT);

    // Check if enough time has passed since the last button press
    if (currentTime - lastButtonPressTime < buttonRateLimit)
    {
        return; // Exit if the button is pressed too quickly
    }

    HandleRightButton(lastDebounceTimeRight, rightButtonHandled, currentTime, currentRightState);
    HandleLeftButton(lastDebounceTimeLeft, leftButtonHandled, currentTime, currentLeftState, rightButtonHandled);

    // Update the lastButtonPressTime for any button state change
    if (currentRightState != previousRightState || currentLeftState != previousLeftState)
    {
        lastButtonPressTime = currentTime;
    }

    previousRightState = currentRightState;
    previousLeftState = currentLeftState;
}
