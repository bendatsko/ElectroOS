//
// Created by Ben Datsko on 12/23/23.
//

#ifndef SYSTEM_UPTIME_H
#define SYSTEM_UPTIME_H

extern unsigned long hours;
extern unsigned long minutes;
extern unsigned long lastUpdateTime;
extern const unsigned long updateInterval;
void RunUpdateUptime();

#endif // SYSTEM_UPTIME_H
