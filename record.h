#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QString>

/* Record
 *
 * Purpose: this class represents the record for a saved session
 *
 */

class Record
{
public:
    Record(QString, int, int, int, QString);
    ~Record();
    QString toString();

private:
    QString type;
    int group;
    int duration;
    int intensity;
    QString timestamp;
};

#endif // RECORD_H
