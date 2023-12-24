#include <avr/wdt.h>
#include "system.h"
#include "uptime.h"
using namespace std;

// Function: Setup Configuration
void setup()
{
    wdt_enable(WDTO_2S); // Enable watchdog with 2-second timeout for reset-on-fault
    InitializePins();    // Initialize pins
    InitializeDisplay(); // Initialize display
}

// Tasks
void loop()
{
    wdt_reset();       // Reset watchdog timer
    RunUpdateUptime(); // Calculate uptime
    RunBMS();          // Run battery management system
    RunMenu();         // Run menu interface
}