#ifndef SOUND_SENSOR_HPP
#define SOUND_SENSOR_HPP

#include "Sensor.hpp"

class SoundSensor : public Sensor
{
public:
    // Construit un capteur sonore avec sa fréquence d'acquisition.
    SoundSensor(Server *server, std::chrono::seconds interval);
    // Génère un niveau sonore entier entre 0 et 100.
    void execute() override;
};

#endif
