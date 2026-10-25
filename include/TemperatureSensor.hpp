#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include "Sensor.hpp"

class TemperatureSensor : public Sensor
{
public:
    TemperatureSensor(Server *server, std::chrono::seconds interval);
    void execute() override;
};

#endif
