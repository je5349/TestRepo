#ifndef DEMO_H
#define DEMO_H
#include <string>
#include "os5000s_compass/Timer.h"

class Demo: protected Timing::Timer {
public:
    Demo();
    ~Demo();
    virtual bool start(double frequency_hz = 30);
    virtual bool stop();
    virtual bool isRunning();

    std::string demoName();

protected:
    std::string _demoName;

    virtual bool loop( double timeSinceLast ) = 0;
};

#endif // DEMO_H
