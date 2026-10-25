
#include "SoundSensor.hpp"
#include <cstdlib>
SoundSensor::SoundSensor(Server *server, std::chrono::seconds interval) : Sensor("Sound", server, interval) {};

void SoundSensor::execute()
{
    int value = std::rand() % 101;
    sendMeasurement(value);
}
