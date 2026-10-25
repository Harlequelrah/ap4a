#include "Scheduler.hpp"
#include <thread>

// Configure un scheduler avec un pas de simulation d'une seconde.
Scheduler::Scheduler() : elapsedTime(std::chrono::seconds(0)), startTime(std::chrono::steady_clock::now()), sleepInterval(std::chrono::seconds(1)) {};

// Configure le pas de simulation demandé par l'appelant.
Scheduler::Scheduler(std::chrono::seconds sleepInterval) : elapsedTime(std::chrono::seconds(0)), startTime(std::chrono::steady_clock::now()), sleepInterval(sleepInterval) {};

// Copie les pointeurs vers les capteurs sans copier les capteurs eux-mêmes.
Scheduler::Scheduler(const Scheduler &other) : sensors(other.sensors), elapsedTime(0), startTime(std::chrono::steady_clock::now()) {};

// Recopie la liste et le pas, puis redémarre la mesure du temps écoulé.
Scheduler &Scheduler::operator=(const Scheduler &other)
{
    if (this != &other)
    {
        sensors = other.sensors;
        startTime = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::seconds(0);
        sleepInterval = other.sleepInterval;
    }
    return *this;
};

// Exécute les capteurs dont l'intervalle divise le temps écoulé.
void Scheduler::simulate()
{
    // Une horloge monotone évite les problèmes liés aux changements de date système.
    auto now = std::chrono::steady_clock::now();
    auto current_second = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    elapsedTime = std::chrono::seconds(current_second);

    for (Sensor *sensor : sensors)
    {
        auto interval = sensor->getInterval();

        // Un intervalle nul ou négatif est ignoré pour éviter une division modulo invalide.
        if (
            interval.count() > 0 &&
            elapsedTime.count() % interval.count() == 0)
        {
            sensor->update();
        }
    }

    // Ralentit la boucle afin de reproduire le passage du temps.
    std::this_thread::sleep_for(sleepInterval);
}

// Ajoute un capteur existant à la liste des capteurs ordonnancés.
void Scheduler::addSensor(Sensor *sensor)
{
    sensors.push_back(sensor);
}

// Le scheduler ne détruit pas les capteurs car il n'en est pas propriétaire.
Scheduler::~Scheduler() {};
