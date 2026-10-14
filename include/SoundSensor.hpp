#ifndef SOUND_SENSOR_HPP
#define SOUND_SENSOR_HPP

#include "Sensor.hpp"

class SoundSensor : public Sensor
{
public:
    SoundSensor(Server *server, std::chrono::seconds interval);
    void execute() override;
};

#endif
