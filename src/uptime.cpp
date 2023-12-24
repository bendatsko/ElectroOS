//
// Created by Ben Datsko on 12/23/23.
//

#include "system.h"

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 30000;
unsigned long hours, minutes;

void RunUpdateUptime()
{
    unsigned long now = millis();
    minutes = now / 60000;
    hours = minutes / 60;
    minutes %= 60;
}