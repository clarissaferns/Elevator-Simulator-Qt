#include "Device.h"
#include <QTimer>
#include <QDebug>

Device::Device(){
    battery = 100.00;
    sessionState = false;
    timer = new QTimer(this);
}

float Device::getBat() { return battery; }
void Device::setBatLevel(float b) { battery = b; }
void Device::setSessionState(bool state) { sessionState = state; }
bool Device::getState() { return sessionState; }
QTimer* Device::getTimerObj(){return timer;
}

// Returns false when the battery is too low to run a session or continue one
int Device::checkBatLevel()
{
  if (battery <= 0)
  {
    return 0;
  }
  else if (battery > 0 && battery <= 10)
  {
    qDebug() << "Battery level at 10% replace battery";
    return 1;
  }
  else if ( battery> 10 && battery <= 30)
  {
    qDebug() << "Battery level at 30% replace battery soon";
    return 2;
  }
  else
    return 3;
}

/* This function takes in the intenstiy and connection level from the main window
 * and calculated the rate at which the battery should deplete
 */
void Device::batteryDepletion(float intensity, float connectionStr)
{
    float rate = intensity/10;
    float connect = connectionStr/50;
    battery = battery - rate - connect;
    float val = (int(battery * 100 + .5));
    battery = (float)val/100;

}



