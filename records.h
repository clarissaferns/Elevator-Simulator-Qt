#ifndef RECORDS_H
#define RECORDS_H

#include <QVector>
#include "record.h"

/* Records
 *
 * Purpose: a collection class to hold pointers to therapy session record objects.
 *
 */

class Records
{
public:
    Records();
    ~Records();
    void pushRecord(Record*);
    void insertRecord(int, Record*);
    Record* getRecord(int);
    int getSize(); // getter
    void clear();

private:
    QVector<Record*> records;

};

#endif // RECORDS_H
