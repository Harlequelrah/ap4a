
#include "TemperatureSensor.hpp"
#include <cstdlib>
TemperatureSensor::TemperatureSensor(Server *server, std::chrono::seconds interval) : Sensor("Temperature", server, interval) {};

void TemperatureSensor::execute()
{
    // plage entre -25 et 50 dégré
    float value = (std::rand() % 7501) / 100.0f - 25.0f;
    lastMeasurement = value;
    sendMeasurement();
}
