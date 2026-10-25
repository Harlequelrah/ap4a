
#include "SoundSensor.hpp"
#include <cstdlib>

// Configure le capteur sonore et son intervalle de mesure.
SoundSensor::SoundSensor(Server *server, std::chrono::seconds interval) : Sensor("Sound", server, interval) {};

// Simule un niveau sonore entier compris entre 0 et 100.
void SoundSensor::execute()
{
    int value = std::rand() % 101;
    lastMeasurement = value;
    sendMeasurement();
}
