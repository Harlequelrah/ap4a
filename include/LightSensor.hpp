#ifndef LIGHT_SENSOR_HPP
#define LIGHT_SENSOR_HPP

#include "Sensor.hpp"

class LightSensor : public Sensor
{
public:
    LightSensor(Server *server, std::chrono::seconds interval);
    void execute() override;
};

#endif
