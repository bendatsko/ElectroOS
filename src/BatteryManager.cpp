#include <avr/wdt.h>
#include "SystemIncludes.h"
#include <ArduinoQueue.h>

#define READ_INTERVAL 500    // 0.5 seconds between input reads
#define UPDATE_INTERVAL 5000 // 5 seconds between display updates
#define QUEUE_SIZE 20        // For calculating Amortized temperatures and voltages

// Global Variables
ArduinoQueue<float> B1VoltageQueue(QUEUE_SIZE);
ArduinoQueue<float> B1TemperatureQueue(QUEUE_SIZE);
ArduinoQueue<float> B2VoltageQueue(QUEUE_SIZE);
ArduinoQueue<float> B2TemperatureQueue(QUEUE_SIZE);

float AmortizedB1Voltage;
float AmortizedB1Temperature;
float AmortizedB2Voltage;
float AmortizedB2Temperature;

unsigned long lastReadTime = 0;
unsigned long lastPrintTime = 0;

// Function Prototypes
void RunBMS();

void UpdateSensorData();

void UpdateAverages();

float GetTemperature(int thermistorPin);

float AverageQueue(ArduinoQueue<float> &queue);

void PushToQueue(ArduinoQueue<float> &queue, float value);

void RunBMS()
{
    unsigned long currentTime = millis();

    // Get new data from sensors every 0.5 seconds
    if (currentTime - lastReadTime >= READ_INTERVAL)
    {
        lastReadTime = currentTime;
        UpdateSensorData();
    }

    // Average batt temps and voltages spanning previous 5 seconds
    if (currentTime - lastPrintTime >= UPDATE_INTERVAL)
    {
        lastPrintTime = currentTime;
        UpdateAverages();
        if (menuState == 4)
        {
            TriggerDisplayUpdate = true;
        }
    }
}

void UpdateSensorData()
{
    float B1Voltage = 1.04 * (analogRead(B1_VOLTAGE) / 1024.0) * 5.0;
    float TotalVoltage = 2 * (analogRead(B2_VOLTAGE) / 1024.0) * 5.0;
    float B2Voltage = TotalVoltage - B1Voltage;
    PushToQueue(B1VoltageQueue, B1Voltage);
    PushToQueue(B2VoltageQueue, B2Voltage);
    PushToQueue(B1TemperatureQueue, GetTemperature(B1_THERMISTOR));
    PushToQueue(B2TemperatureQueue, GetTemperature(B2_THERMISTOR));
}

void UpdateAverages()
{
    AmortizedB1Voltage = AverageQueue(B1VoltageQueue);
    AmortizedB2Voltage = AverageQueue(B2VoltageQueue);
    AmortizedB1Temperature = AverageQueue(B1TemperatureQueue);
    AmortizedB2Temperature = AverageQueue(B2TemperatureQueue);
}

float GetTemperature(int thermistorPin)
{
    int reading = analogRead(thermistorPin);

    // Steinhart-Hart Equation
    const float R0 = 10000.0;
    const float T0 = 298.15;
    const float B = 3380.0;
    const float Vcc = 5;
    float Vout = (reading * Vcc) / 1024.0;
    float Rt = R0 * (Vcc / Vout - 1.0);
    float temperatureK = (B * T0) / (B + T0 * log(Rt / R0));
    float Celsius = temperatureK - 273.15;
    return Celsius;
}

float AverageQueue(ArduinoQueue<float> &queue)
{
    // Edge case where empty
    if (queue.isEmpty())
    {
        return 0;
    }

    // Calculate the sum of the queue by popping everything
    float sum = 0;
    unsigned int count = queue.itemCount();
    ArduinoQueue<float> tempQueue(QUEUE_SIZE);
    while (!queue.isEmpty())
    {
        float value = queue.dequeue();
        sum += value;
        tempQueue.enqueue(value); // Enqueue to temporary queue
    }

    // Revert the queue back to its initial state
    while (!tempQueue.isEmpty())
    {
        queue.enqueue(tempQueue.dequeue());
    }

    return sum / count; // Return average
}

void PushToQueue(ArduinoQueue<float> &queue, float value)
{
    if (queue.itemCount() >= QUEUE_SIZE)
    {
        queue.dequeue(); // LRU eviction policy if queue is full
    }
    queue.enqueue(value);
}
