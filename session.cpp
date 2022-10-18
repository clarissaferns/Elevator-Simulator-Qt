#include "session.h"
#include <QString>

Session::Session()
{
    name = "default";
    group = 0;
    intensity = 2.0; //change to intensity
    elapsed = 0;
}

Session::~Session()
{

}

QString Session::getName()
{
    return this->name;

}

int Session::getGroup()
{
    return this->group;

}

float Session::getIntensity()
{
    return this->intensity;

}

int Session::getElapsed()
{
    return this->elapsed;
}

void Session::setName(QString n)
{
    this->name = n;

}

void Session::setIntensity(float f)
{
    this->intensity = f;

}

void Session::setGroup(int g)
{
    this->group = g;

}

void Session::setElapsed(int e)
{
    this->elapsed = e;
}


// calculate elapsed time in seconds
void Session::setElapsed(int m, int s)
{
    if (s == 0) {
        this->elapsed = (group - m) * 60;
    } else {
        int mins = group - (m + 1);
        int sec = 60 - s;

        this->elapsed = (mins * 60) + sec;
    }
}
