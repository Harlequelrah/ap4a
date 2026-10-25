#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "Server.hpp"
#include <string>
#include <chrono>
#include "Measurement.hpp"

// Classe abstraite commune à tous les capteurs du simulateur.
class Sensor
{
public:
    // Construit un capteur avec des valeurs par défaut.
    Sensor();
    // Construit un capteur configuré avec son type, son serveur et sa fréquence.
    Sensor(const std::string &type, Server *server, std::chrono::seconds interval);
    // Copie la configuration d'un capteur en attribuant un nouvel identifiant.
    Sensor(const Sensor &other);
    // Copie la configuration sans remplacer l'identifiant propre à l'objet.
    Sensor &operator=(const Sensor &other);
    // Le destructeur virtuel permet une destruction correcte via Sensor*.
    virtual ~Sensor();
    // Déclenche une acquisition concrète définie par la sous-classe.
    void update();
    // Retourne le serveur destinataire de la mesure.
    Server *getServer() const;
    // Retourne le nom du type de capteur.
    const std::string &getType() const;
    // Retourne l'identifiant unique du capteur.
    int getId() const;
    // Retourne l'intervalle entre deux acquisitions.
    std::chrono::seconds getInterval() const;

private:
    int id;                                      // Identifiant unique de l'instance.
    std::string type;                            // Type fonctionnel du capteur.
    Server *server;                              // Serveur auquel envoyer les mesures.
    std::chrono::seconds interval;               // Fréquence propre du capteur.
    static int nextId;                           // Compteur utilisé pour les identifiants.

protected:
    // Génère une mesure ; chaque capteur spécialisé fournit son implémentation.
    virtual void execute() = 0;
    // Transmet la dernière mesure au serveur lorsqu'il est disponible.
    void sendMeasurement();
    Measurement lastMeasurement;                 // Dernière valeur générée.
};
#endif
