#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include "Measurement.hpp"
#include "Server.hpp"

// Retourne la date et l'heure locales dans le format utilisé par les journaux.
std::string getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

// Prépare le dossier de sortie dès la création du serveur.
Server::Server()
{
    std::filesystem::create_directories("logs");
}

// Le serveur ne possède pas d'état à recopier.
Server::Server(const Server &other)
{
}

// Le serveur ne possède pas d'état assignable.
Server &Server::operator=(const Server &other)
{
    if (this != &other)
    {
    }
    return *this;
}

// Les fichiers sont fermés automatiquement par leurs flux locaux.
Server::~Server()
{
}

// Affiche une mesure avec son horodatage et sa valeur formatée.
void Server::consoleWrite(const std::string &type,
                          const Measurement &value)
{
    std::cout << "[" << getCurrentDateTime() << "] "
              << type << " : "
              << measurementToString(value)
              << std::endl;
}

// Ajoute une mesure au fichier CSV correspondant à son type.
void Server::fileWrite(const std::string &type,
                       const Measurement &value)
{
    // Chaque capteur écrit dans un fichier distinct : Temperature.csv, etc.
    std::string filename = "logs/" + type + ".csv";

    // Garantit que le dossier existe même après une suppression manuelle.
    std::filesystem::create_directories("logs");

    // L'en-tête est écrit uniquement lors de la création d'un fichier vide.
    bool writeHeader =
        !std::filesystem::exists(filename) ||
        std::filesystem::file_size(filename) == 0;

    std::ofstream fichier(filename, std::ios::app);

    if (!fichier.is_open())
    {
        std::cerr << "Erreur : impossible d'ouvrir "
                  << filename << std::endl;
        return;
    }

    // Le format reste compatible avec un tableur ou un outil d'analyse CSV.
    if (writeHeader)
    {
        fichier << "datetime,type,value\n";
    }

    fichier << getCurrentDateTime() << ','
            << type << ','
            << measurementToString(value) << '\n';
}

// Surcharge d'affichage minimale pour représenter le serveur dans un flux.
std::ostream &operator<<(std::ostream &os, const Server &server)
{
    os << "Serveur";
    return os;
}

// Pipeline central de traitement d'une mesure reçue d'un capteur.
void Server::processMeasurement(const std::string &type,
                                const Measurement &value)
{
    consoleWrite(type, value);
    fileWrite(type, value);
    analyzeMeasurement(type, value);
}

// Vérifie les seuils métiers propres à chaque type de capteur.
void Server::analyzeMeasurement(const std::string &type,
                                const Measurement &value)
{
    if (type == "Temperature")
    {
        // Une température supérieure à 30 °C est considérée comme élevée.
        if (const float *temperature = std::get_if<float>(&value))
        {
            if (*temperature > 30.0f)
            {
                logAlert("Temperature elevee : " +
                         measurementToString(value) + " °C");
            }
        }
    }
    else if (type == "Humidity")
    {
        // Une humidité supérieure à 70 % déclenche une alerte.
        if (const float *humidity = std::get_if<float>(&value))
        {
            if (*humidity > 70.0f)
            {
                logAlert("Humidite elevee : " +
                         measurementToString(value) + " %");
            }
        }
    }
    else if (type == "Sound")
    {
        // Un niveau sonore supérieur à 80 déclenche une alerte.
        if (const int *sound = std::get_if<int>(&value))
        {
            if (*sound > 80)
            {
                logAlert("Niveau sonore eleve : " +
                         measurementToString(value));
            }
        }
    }
    else if (type == "Light")
    {
        // Aucune règle d'alerte n'est définie pour la lumière pour le moment.
    }
}

// Ecrit une alerte dans la console et dans le journal permanent.
void Server::logAlert(const std::string &message)
{
    const std::string filename = "logs/alerts.log";

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Erreur : impossible d'ouvrir "
                  << filename << std::endl;
        return;
    }

    // Le même message horodaté est envoyé aux deux sorties.
    const std::string datetime = getCurrentDateTime();
    const std::string alert = "[" + datetime + "] - Alerte - " + message;

    std::cout << alert << std::endl;
    file << alert << '\n';
}
