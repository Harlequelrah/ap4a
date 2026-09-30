#include "Sensor.hpp"
#include <cstdlib>

int Sensor::nextId = 0;

Sensor::Sensor()
    : id(nextId++),
      type("Unknown"),
      value(0.0),
      server(nullptr),
      interval(std::chrono::seconds(1)) {};

Sensor::Sensor(const std::string &type, Server *server, std::chrono::seconds interval)
    : id(nextId++),
      type(type),
      value(0.0),
      server(server),
      interval(interval) {

      };
Sensor::Sensor(const Sensor &other)
    : id(nextId++),
      type(other.type),
      value(other.value),
      server(other.server),
      interval(interval) {};

Sensor &Sensor::operator=(const Sensor &other)
{
    if (this != &other)
    {
        type = other.type;
        value = other.value;
        server = other.server;
        interval = other.interval;
    }
    return *this;
}

Sensor::~Sensor() {};

void Sensor::update()
{
    execute();
};

void Sensor::execute()
{
    value = std::rand() % 101;
    if (server != nullptr)
    {
        server->consoleWriter(type, value);
    }
};

int Sensor::getId() const
{
    return id;
}

std::chrono::seconds Sensor::getInterval() const
{
    return interval;
};
