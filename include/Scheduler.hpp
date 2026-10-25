#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Sensor.hpp"
#include <vector>
class Scheduler
{
public:
    // Utilise un pas de simulation d'une seconde.
    Scheduler();
    // Construit un ordonnanceur avec un pas de simulation donné.
    Scheduler(std::chrono::seconds sleepInterval);
    // Copie la liste des capteurs et réinitialise la base de temps.
    Scheduler(const Scheduler &other);
    // Remplace la configuration et réinitialise le chronomètre.
    Scheduler &operator=(const Scheduler &other);
    // Libère les ressources propres à l'ordonnanceur (les capteurs ne lui appartiennent pas).
    ~Scheduler();
    // Exécute les capteurs dont l'intervalle est arrivé à échéance.
    void simulate();
    // Ajoute un capteur à la liste des capteurs ordonnancés.
    void addSensor(Sensor *sensor);

private:
    std::vector<Sensor *> sensors;                         // Capteurs observés.
    std::chrono::seconds elapsedTime;                      // Temps depuis le démarrage.
    std::chrono::seconds sleepInterval;                    // Pause entre deux cycles.
    std::chrono::steady_clock::time_point startTime;       // Origine de la simulation.
};

#endif
