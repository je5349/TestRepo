#include "os5000s_compass/Demo.h"

Demo::Demo() {
    _demoName = " ";
}

bool Demo::start( double frequency_hz)
{
    //cout << ("Start Demo " +_demoName);

     return this->startTicking<Demo>( *this, &Demo::loop, 1000.0/frequency_hz);

}

bool Demo::stop()
{
    return this->stopTicking();
}

bool Demo::isRunning()
{
    return this->isTicking();
}

std::string Demo::demoName()
{
    return _demoName;
}

Demo::~Demo()
{
    if( isRunning() )
        stop();

    return;
}
