#ifndef LIGHT_SENSOR_HPP
#define LIGHT_SENSOR_HPP

#include "Sensor.hpp"

class LightSensor : public Sensor
{
public:
    // Construit un capteur de lumière avec sa fréquence d'acquisition.
    LightSensor(Server *server, std::chrono::seconds interval);
    // Génère un état lumineux booléen (éteint ou allumé).
    void execute() override;
};

#endif
