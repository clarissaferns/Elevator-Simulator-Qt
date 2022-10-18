#ifndef DEVICE_H
#define DEVICE_H
#include <QTimer>
#include <iostream>
using namespace std;

/* Device
 *
 * Purpose: a class in charge of creating a timer and depleting the battery
 *
 */


class Device: public QObject
{
    Q_OBJECT
    public:
        Device();
        float getBat();
        void setBatLevel(float);
        void setSessionState(bool);
        bool getState();
        int checkBatLevel();
        void batteryDepletion(float, float);
        QTimer* getTimerObj();

    private:
        float battery;
        bool sessionState; // true if session is active
        QTimer* timer;
};

#endif // DEVICE_H
