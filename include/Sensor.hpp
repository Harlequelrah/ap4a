#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "Server.hpp"
#include <string>
#include <chrono>
#include "Measurement.hpp"

// classe de base
class Sensor
{
public:
    Sensor();
    Sensor(const std::string &type, Server *server, std::chrono::seconds interval);
    Sensor(const Sensor &other);
    Sensor &operator=(const Sensor &other);
    virtual ~Sensor();
    void update();
    Server *getServer() const;
    const std::string &getType() const;
    int getId() const;
    std::chrono::seconds getInterval() const;

private:
    int id;
    std::string type;
    Server *server;
    std::chrono::seconds interval;
    static int nextId;

protected:
    // rend execute purement virtuel et Sensor devient une classe Abstraite
    virtual void execute() = 0;
    void sendMeasurement();
    Measurement lastMeasurement;
};
#endif
