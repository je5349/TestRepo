#ifndef COMPASS_H
#define COMPASS_H

#include "os5000s_compass/SerialPort.h"
#include "os5000s_compass/Demo.h"
#include "os5000s_compass/Mutex.h"
#include "os5000s_compass/Timer.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>

class Compass:protected Demo
{

    Threads::GuardedData<double> heading;
    Threads::GuardedData<double> roll;
    Threads::GuardedData<double> pitch;
    Threads::GuardedData<double> temperature;
    Threads::GuardedData<double> depth;
    Threads::GuardedData<double> magnetic_vector_length;
    Threads::GuardedData<double> Mx;
    Threads::GuardedData<double> My;
    Threads::GuardedData<double> Mz;
    Threads::GuardedData<double> acceleration_vector_length;
    Threads::GuardedData<double> Ax;
    Threads::GuardedData<double> Ay;
    Threads::GuardedData<double> Az;

    SerialPort myPort;
    std::string last_tail;

    bool loop(double timeSinceLast); // this is where we take the measurement and parse it ...

public:
    Compass();

    ~Compass();

    double getHeading();
    double getPitch();
    double getRoll();
    double getTemperature();
    double getDepth();
    double getMagneticVectorLength();
    double getMx();
    double getMy();
    double getMz();
    double getAccelerationVectorLength();
    double getAx();
    double getAy();
    double getAz();


};

#endif
