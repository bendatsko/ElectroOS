//
// Created by Ben Datsko on 12/23/23.
//

#include <avr/wdt.h>
#include "system.h"
#include "uptime.h"
#include <ArduinoQueue.h>

#define QUEUE_SIZE 20
#define READ_INTERVAL 500    // 500 milliseconds (0.5 seconds) between readings
#define PRINT_INTERVAL 10000 // 10000 milliseconds (10 seconds) between prints

ArduinoQueue<float> b1VoltageQueue(QUEUE_SIZE);
ArduinoQueue<float> b2VoltageQueue(QUEUE_SIZE);

unsigned long lastReadTime = 0;
unsigned long lastPrintTime = 0;

float amortizedB1Voltage;
float amortizedB2Voltage;

ArduinoQueue<float> b1TemperatureQueue(QUEUE_SIZE);
ArduinoQueue<float> b2TemperatureQueue(QUEUE_SIZE);

float amortizedB1Temperature;
float amortizedB2Temperature;

void updateQueue(ArduinoQueue<float> &queue, float voltage)
{
    if (queue.itemCount() >= QUEUE_SIZE)
    {
        queue.dequeue(); // Remove oldest element if the queue is full
    }
    queue.enqueue(voltage);
}

float calculateAverage(ArduinoQueue<float> &queue)
{
    float sum = 0;
    unsigned int count = queue.itemCount();
    ArduinoQueue<float> tempQueue(QUEUE_SIZE);

    while (!queue.isEmpty())
    {
        float value = queue.dequeue();
        sum += value;
        tempQueue.enqueue(value); // Enqueue to temporary queue
    }

    // Restore the original queue state
    while (!tempQueue.isEmpty())
    {
        queue.enqueue(tempQueue.dequeue());
    }

    return count > 0 ? sum / count : 0;
}

float convertToTemperature(int reading)
{
    // Constants for the NCU18XH103F60RB thermistor
    const float R0 = 10000.0; // Resistance at 25 degrees C (10kΩ)
    const float T0 = 298.15;  // 25 degrees C in Kelvin
    const float B = 3380.0;   // B constant
    const float Vcc = 4.859;  // Supply Voltage (TODO: Once LDO works change to ~5.0V)

    // Calculate the resistance of the thermistor
    float Vout = (reading * Vcc) / 1024.0;
    float Rt = R0 * (Vcc / Vout - 1.0);

    // Calculate the temperature in Kelvin
    float temperatureK = (B * T0) / (B + T0 * log(Rt / R0));

    // Convert Kelvin to Celsius
    float temperatureC = temperatureK - 273.15;

    return temperatureC;
}

float readTemperature(int thermistorPin)
{
    int reading = analogRead(thermistorPin);
    // Convert the reading to temperature (example implementation)
    // This is highly dependent on your specific thermistor and circuit configuration
    float temperature = convertToTemperature(reading);
    return temperature;
}

void RunBMS()
{
    unsigned long currentTime = millis();

    // Read and update queue every 0.5 seconds
    if (currentTime - lastReadTime >= READ_INTERVAL)
    {
        lastReadTime = currentTime;

        float CorrectionFactor = 1.0336497;

        float b1Voltage = CorrectionFactor * (analogRead(9) / 1024.0) * 5.0;
        float totalVoltage = 2 * (analogRead(6) / 1024.0) * 5.0;
        float b2Voltage = totalVoltage - b1Voltage;

        float b1Temperature = readTemperature(B1_THERMISTOR);
        float b2Temperature = readTemperature(B2_THERMISTOR);

        updateQueue(b1VoltageQueue, b1Voltage);
        updateQueue(b2VoltageQueue, b2Voltage);
        updateQueue(b1TemperatureQueue, b1Temperature);
        updateQueue(b2TemperatureQueue, b2Temperature);
    }

    // Update every 10 seconds
    if (currentTime - lastPrintTime >= PRINT_INTERVAL)
    {
        lastPrintTime = currentTime;

        amortizedB1Voltage = calculateAverage(b1VoltageQueue);
        amortizedB2Voltage = calculateAverage(b2VoltageQueue);
        amortizedB1Temperature = calculateAverage(b1TemperatureQueue);
        amortizedB2Temperature = calculateAverage(b2TemperatureQueue);

        if (menuState == 4)
        {
            menuStateChanged = true;
        }
    }
}
