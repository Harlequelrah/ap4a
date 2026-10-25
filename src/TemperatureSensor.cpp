
#include "TemperatureSensor.hpp"
#include <cstdlib>

// Le type transmis au serveur est utilisé pour le nom du fichier et les alertes.
TemperatureSensor::TemperatureSensor(Server *server, std::chrono::seconds interval) : Sensor("Temperature", server, interval) {};

// Simule une mesure comprise entre -25.00 °C et 50.00 °C.
void TemperatureSensor::execute()
{
    float value = (std::rand() % 7501) / 100.0f - 25.0f;
    lastMeasurement = value;
    sendMeasurement();
}
