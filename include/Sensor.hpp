#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "Server.hpp"
#include <string>
#include <chrono>

// classe de base
class Sensor
{
public:
    Sensor();
    Sensor(const std::string &type, Server *server, std::chrono::seconds interval);
    Sensor(const Sensor &other);
    Sensor &operator=(const Sensor &other);
    // virtual ~Sensor();
    virtual ~Sensor();
    virtual void update();
    void execute();
    int getId() const;
    std::chrono::seconds getInterval() const;

private:
    int id;
    std::string type;
    double value;
    Server *server;
    std::chrono::seconds interval;
    static int nextId;
};
#endif
