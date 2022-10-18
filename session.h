#ifndef SESSION_H
#define SESSION_H
#include <QString>

/* Session
 *
 * Purpose: represents a therapy session.
 *
 */

class Session
{
public:
    Session();
    ~Session();
    //getters
    //setters
    QString getName();
    int getGroup();
    float getIntensity();
    int getElapsed();
    void setName(QString);
    void setGroup(int);
    void setIntensity(float);
    void setElapsed(int);
    void setElapsed(int, int);

private:
    //therapy name (decided by GUI arrows)
    //group (time) (decided by GUI arrows)
    //frequency (decided by GUI arrows)
    QString name;
    int group;
    float intensity;
    int elapsed;

};

#endif // SESSION_H
