#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include "Sensor.hpp"

class TemperatureSensor : public Sensor
{
public:
    // Construit un capteur de température avec sa fréquence d'acquisition.
    TemperatureSensor(Server *server, std::chrono::seconds interval);
    // Génère une température aléatoire comprise dans la plage du projet.
    void execute() override;
};

#endif
