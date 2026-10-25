#ifndef HUMIDITY_SENSOR_HPP
#define HUMIDITY_SENSOR_HPP

#include "Sensor.hpp"

class HumiditySensor : public Sensor
{
public:
    // Construit un capteur d'humidité avec sa fréquence d'acquisition.
    HumiditySensor(Server *server, std::chrono::seconds interval);
    // Génère un taux d'humidité aléatoire entre 0 et 100 %.
    void execute() override;
};

#endif
