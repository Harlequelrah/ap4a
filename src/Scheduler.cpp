#include "Scheduler.hpp"
#include <thread>

Scheduler::Scheduler() : elapsedTime(std::chrono::seconds(0)), startTime(std::chrono::steady_clock::now()), sleepInterval(std::chrono::seconds(1)) {};
Scheduler::Scheduler(std::chrono::seconds sleepInterval) : elapsedTime(std::chrono::seconds(0)), startTime(std::chrono::steady_clock::now()), sleepInterval(sleepInterval) {};
Scheduler::Scheduler(const Scheduler &other) : sensors(other.sensors), elapsedTime(0), startTime(std::chrono::steady_clock::now()) {};
Scheduler &Scheduler::operator=(const Scheduler &other)
{
    if (this != &other)
    {
        sensors = other.sensors;
        startTime = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::seconds(0);
        sleepInterval = other.sleepInterval;
    }
    return *this;
};
void Scheduler::simulate()
{
    auto now = std::chrono::steady_clock::now();
    auto current_second = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
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
    std::this_thread::sleep_for(sleepInterval);
}
void Scheduler::addSensor(Sensor *sensor)
{
    sensors.push_back(sensor);
}
Scheduler::~Scheduler() {};
