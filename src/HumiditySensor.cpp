
#include "HumiditySensor.hpp"
#include <cstdlib>
#include "Measurement.hpp"
HumiditySensor::HumiditySensor(Server *server, std::chrono::seconds interval) : Sensor("Humidity", server, interval) {};

void HumiditySensor::execute()
{
    float value = (std::rand() % 10001) / 100.0f;
    lastMeasurement = value;

    sendMeasurement();
}
