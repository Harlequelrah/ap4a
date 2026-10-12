#include "Scheduler.hpp"

Scheduler::Scheduler() : elapsedTime(std::chrono::seconds(0)), startTime(std::chrono::steady_clock::now()), lastProcessedSecond(0) {};
Scheduler::Scheduler(const Scheduler &other) : sensors(other.sensors), elapsedTime(0), startTime(std::chrono::steady_clock::now()) {};
Scheduler &Scheduler::operator=(const Scheduler &other)
{
    if (this != &other)
    {
        sensors = other.sensors;
        startTime = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::seconds(0);
        lastProcessedSecond = 0;
    }
    return *this;
};
void Scheduler::simulate()
{
    auto now = std::chrono::steady_clock::now();
    auto current_second = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    while (lastProcessedSecond < current_second)
    {
        ++lastProcessedSecond;
        elapsedTime = std::chrono::seconds(current_second);
        for (Sensor *sensor : sensors)
        {
            auto interval = sensor->getInterval();
            if (
                interval.count() > 0 &&
                elapsedTime.count() % interval.count() == 0)
            {
                sensor->update();
            }
        }
    }
}
void Scheduler::addSensor(Sensor *sensor)
{
    sensors.push_back(sensor);
}
Scheduler::~Scheduler() {};
