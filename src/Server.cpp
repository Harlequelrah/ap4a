#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include "Measurement.hpp"
#include "Server.hpp"

std::string getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

Server::Server()
{
    std::filesystem::create_directories("logs");
}

Server::Server(const Server &other)
{
}

Server &Server::operator=(const Server &other)
{
    if (this != &other)
    {
    }
    return *this;
}

Server::~Server()
{
}

void Server::consoleWrite(const std::string &type,
                          const Measurement &value)
{
    std::cout << "[" << getCurrentDateTime() << "] "
              << type << " : "
              << measurementToString(value)
              << std::endl;
}

void Server::fileWrite(const std::string &type,
                       const Measurement &value)
{
    std::string filename = "logs/" + type + ".csv";

    std::filesystem::create_directories("logs");

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

    if (writeHeader)
    {
        fichier << "datetime,type,value\n";
    }

    fichier << getCurrentDateTime() << ','
            << type << ','
            << measurementToString(value) << '\n';
}
std::ostream &operator<<(std::ostream &os, const Server &server)
{
    os << "Serveur";
    return os;
}

void Server::processMeasurement(const std::string &type,
                                const Measurement &value)
{
    consoleWrite(type, value);
    fileWrite(type, value);
    analyzeMeasurement(type, value);
}
void Server::analyzeMeasurement(const std::string &type,
                                const Measurement &value)
{
    if (type == "Temperature")
    {
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
        // Aucune règle d'alerte définie pour le moment.
    }
}

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

    const std::string datetime = getCurrentDateTime();
    const std::string alert = "[" + datetime + "] " + message;

    std::cout << alert << std::endl;
    file << alert << '\n';
}
