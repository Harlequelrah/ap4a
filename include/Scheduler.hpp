#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Sensor.hpp"
#include <vector>
class Scheduler
{
public:
    Scheduler();
    Scheduler(std::chrono::seconds sleepInterval);
    Scheduler(const Scheduler &other);
    Scheduler &operator=(const Scheduler &other);
    ~Scheduler();
    void simulate();
    void addSensor(Sensor *sensor);

private:
    std::vector<Sensor *> sensors;
    std::chrono::seconds elapsedTime;
    std::chrono::seconds sleepInterval;
    std::chrono::steady_clock::time_point startTime;
};

#endif
