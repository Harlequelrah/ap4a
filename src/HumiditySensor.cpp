
#include "HumiditySensor.hpp"
#include <cstdlib>
#include "Measurement.hpp"
HumiditySensor::HumiditySensor(Server *server, std::chrono::seconds interval) : Sensor("Humidity", server, interval) {};

void HumiditySensor::execute()
{
    float value = std::rand() % 101;

    sendMeasurement(value);
}
