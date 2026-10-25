#include "Sensor.hpp"
#include <cstdlib>

int Sensor::nextId = 0;

Sensor::Sensor()
    : id(nextId++),
      type("Unknown"),
      server(nullptr),
      interval(std::chrono::seconds(1)), lastMeasurement(0.0f) {};

Sensor::Sensor(const std::string &type, Server *server, std::chrono::seconds interval)
    : id(nextId++),
      type(type),
      server(server),
      interval(interval), lastMeasurement(0.0f) {
      };
Sensor::Sensor(const Sensor &other)
    : id(nextId++),
      type(other.type),
      server(other.server),
      interval(other.interval), lastMeasurement(other.lastMeasurement) {};

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

Sensor::~Sensor() {};

void Sensor::update()
{
    execute();
};

int Sensor::getId() const
{
    return id;
}

std::chrono::seconds Sensor::getInterval() const
{
    return interval;
}

Server *Sensor::getServer() const
{
    return server;
}

void Sensor::sendMeasurement()
{
    if (server != nullptr)
    {
        server->processMeasurement(getType(), lastMeasurement);
    }
}
const std::string &Sensor::getType() const
{
    return type;
}
