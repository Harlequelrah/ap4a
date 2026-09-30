#include "Scheduler.hpp"

Scheduler::Scheduler() : elapsedTime(0) {};
Scheduler::Scheduler(const Scheduler &other) {};
Scheduler &Scheduler::operator=(const Scheduler &other)
{
    if (this != &other)
    {
    }
    return *this;
};
void Scheduler::simulate()
{
    elapsedTime += std::chrono::seconds(1);
    for (Sensor *sensor : sensors)
    {
        if (elapsedTime.count() % sensor->getInterval().count())
        {
            sensor->update();
        }
    }
}
void Scheduler::addSensor(Sensor *sensor)
{
    sensors.push_back(sensor);
}
Scheduler::~Scheduler() {};
