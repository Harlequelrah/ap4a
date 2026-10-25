
#include "LightSensor.hpp"
#include <cstdlib>

// Configure le capteur de lumière et son intervalle de mesure.
LightSensor::LightSensor(Server *server, std::chrono::seconds interval) : Sensor("Light", server, interval) {};

// Simule un état de lumière : false (0) ou true (1).
void LightSensor::execute()
{
    bool value = std::rand() % 2;
    lastMeasurement = value;
    sendMeasurement();
}
