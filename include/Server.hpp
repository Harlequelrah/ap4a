#ifndef SERVER_HPP
#define SERVER_HPP
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include "Measurement.hpp"
class Server
{
public:
    // création normal
    Server();

    // création par copie
    Server(const Server &other);

    // affectation
    Server &operator=(const Server &other);

    // destructeur
    ~Server();

    // méthodes
    void consoleWrite(const std::string &type,
                      const Measurement &value);

    void fileWrite(const std::string &type,
                   const Measurement &value);

    void processMeasurement(const std::string &type,
                            const Measurement &value);

    void analyzeMeasurement(const std::string &type,
                            const Measurement &value);

    friend std::ostream &operator<<(std::ostream &os, const Server &server);

private:
    void logAlert(const std::string &message);
};

#endif
