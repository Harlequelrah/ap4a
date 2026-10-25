#include "Sensor.hpp"
#include <cstdlib>

// Compteur partagé permettant d'attribuer un identifiant différent à chaque capteur.
int Sensor::nextId = 0;

// Initialise un capteur générique avec une configuration sûre par défaut.
Sensor::Sensor()
    : id(nextId++),
      type("Unknown"),
      server(nullptr),
      interval(std::chrono::seconds(1)), lastMeasurement(0.0f) {};

// Initialise un capteur concret avec sa configuration fournie par le constructeur.
Sensor::Sensor(const std::string &type, Server *server, std::chrono::seconds interval)
    : id(nextId++),
      type(type),
      server(server),
      interval(interval), lastMeasurement(0.0f) {
      };

// Une copie conserve la configuration mais reçoit un nouvel identifiant.
Sensor::Sensor(const Sensor &other)
    : id(nextId++),
      type(other.type),
      server(other.server),
      interval(other.interval), lastMeasurement(other.lastMeasurement) {};

// Recopie les données configurables ; l'identifiant reste propre à l'objet cible.
Sensor &Sensor::operator=(const Sensor &other)
{
    if (this != &other)
    {
        type = other.type;
        server = other.server;
        interval = other.interval;
        lastMeasurement = other.lastMeasurement;
    }
    return *this;
}

// Le destructeur est virtuel afin de respecter le polymorphisme de Sensor.
Sensor::~Sensor() {};

// L'ordonnanceur utilise cette méthode comme interface commune d'activation.
void Sensor::update()
{
    execute();
};

// Retourne l'identifiant attribué lors de la construction.
int Sensor::getId() const
{
    return id;
}

// Retourne le délai entre deux mesures de ce capteur.
std::chrono::seconds Sensor::getInterval() const
{
    return interval;
}

// Retourne le serveur associé, sans transférer sa propriété.
Server *Sensor::getServer() const
{
    return server;
}

// Transmet la dernière mesure au serveur si le capteur est correctement connecté.
void Sensor::sendMeasurement()
{
    if (server != nullptr)
    {
        server->processMeasurement(getType(), lastMeasurement);
    }
}

// Retourne le type utilisé pour nommer les journaux et analyser les seuils.
const std::string &Sensor::getType() const
{
    return type;
}
