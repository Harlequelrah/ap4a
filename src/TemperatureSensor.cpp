
#include "TemperatureSensor.hpp"
#include <cstdlib>
TemperatureSensor::TemperatureSensor(Server *server, std::chrono::seconds interval) : Sensor("Temperature", server, interval) {};

void TemperatureSensor::execute()
{
    float value = std::rand() % 101;
    sendMeasurement(value);
}
