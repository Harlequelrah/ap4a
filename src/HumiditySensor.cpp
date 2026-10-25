
#include "HumiditySensor.hpp"
#include <cstdlib>
#include "Measurement.hpp"

// Configure le capteur avec le type attendu par le serveur.
HumiditySensor::HumiditySensor(Server *server, std::chrono::seconds interval) : Sensor("Humidity", server, interval) {};

// Simule un taux d'humidité compris entre 0.00 % et 100.00 %.
void HumiditySensor::execute()
{
    float value = (std::rand() % 10001) / 100.0f;
    lastMeasurement = value;

    sendMeasurement();
}
