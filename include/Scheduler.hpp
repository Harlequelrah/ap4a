#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Sensor.hpp"
#include <vector>
class Scheduler
{
public:
    Scheduler();
    Scheduler(const Scheduler &other);
    Scheduler &operator=(const Scheduler &other);
    ~Scheduler();
    void simulate();
    void addSensor(Sensor* sensor);

private:
    std::vector<Sensor *> sensors;
    std::chrono::seconds elapsedTime;
};

#endif
