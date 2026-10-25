#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Server.hpp"
#include "Sensor.hpp"
#include "TemperatureSensor.hpp"
#include "HumiditySensor.hpp"
#include "SoundSensor.hpp"
#include "LightSensor.hpp"
#include "Scheduler.hpp"

// Point d'entrée : construit le système IoT et lance sa simulation continue.
int main()
{
    // Active l'affichage UTF-8 pour les messages accentués dans le terminal Windows.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Le serveur reçoit, affiche, journalise et analyse toutes les mesures.
    Server server;

    // Le scheduler vérifie les capteurs toutes les secondes.
    Scheduler scheduler(std::chrono::seconds(1));

    // Chaque capteur possède une fréquence de mesure indépendante.
    TemperatureSensor temperature(&server, std::chrono::seconds(2));
    LightSensor light(&server, std::chrono::seconds(1));
    SoundSensor sound(&server, std::chrono::seconds(2));
    HumiditySensor humidity(&server, std::chrono::seconds(5));

    // Les pointeurs sont non propriétaires : les capteurs vivent jusqu'à la fin de main.
    scheduler.addSensor(&temperature);
    scheduler.addSensor(&humidity);
    scheduler.addSensor(&light);
    scheduler.addSensor(&sound);

    // La simulation est volontairement continue ; l'arrêt se fait avec Ctrl+C.
    while (true)
    {
        scheduler.simulate();
    }

    return 0;
}
