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
}

Server::Server(const Server &other)
{
}

Server &Server::operator=(const Server &other)
{
    std::cout << "Operateur =" << std::endl;
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
