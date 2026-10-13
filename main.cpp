#include <iostream>
#include "Server.hpp"
#include "Sensor.hpp"
#include "Scheduler.hpp"
#include <thread>
int main()
{
    Server server;
    Scheduler scheduler;

    Sensor sensor1("Temperature", &server, std::chrono::seconds(2));
    Sensor sensor2("Humidity", &server, std::chrono::seconds(5));
    scheduler.addSensor(&sensor1);
    scheduler.addSensor(&sensor2);
    for (int i = 0; i < 11; ++i)
    {
        scheduler.simulate();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    

    return 0;
}
