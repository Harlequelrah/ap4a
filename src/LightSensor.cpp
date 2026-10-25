
#include "LightSensor.hpp"
#include <cstdlib>
LightSensor::LightSensor(Server *server, std::chrono::seconds interval) : Sensor("Light", server, interval) {};

void LightSensor::execute()
{
    bool value = std::rand() % 2;
    sendMeasurement(value);
}
