#ifndef HUMIDITY_SENSOR_HPP
#define HUMIDITY_SENSOR_HPP

#include "Sensor.hpp"

class HumiditySensor : public Sensor
{
public:
    HumiditySensor(Server *server, std::chrono::seconds interval);
    void execute() override;
};

#endif
