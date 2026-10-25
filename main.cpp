#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Server.hpp"
#include "Sensor.hpp"
#include "TemperatureSensor.hpp"
#include "HumiditySensor.hpp"
#include "SoundSensor.hpp"
#include "LightSensor.hpp"
#include "Scheduler.hpp"
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Server server;
    Scheduler scheduler(std::chrono::seconds(1));
    TemperatureSensor temperature(&server, std::chrono::seconds(2));
    LightSensor light(&server, std::chrono::seconds(1));
    SoundSensor sound(&server, std::chrono::seconds(2));
    HumiditySensor humidity(&server, std::chrono::seconds(5));
    scheduler.addSensor(&temperature);
    scheduler.addSensor(&humidity);
    scheduler.addSensor(&light);
    scheduler.addSensor(&sound);
    while (true)
    {
        scheduler.simulate();
    }

    return 0;
}
