#include "records.h"
#include <iostream>
Records::Records()
{

}

Records::~Records()
{
    for (int i = 0; i < records.size(); ++i)
    {
        delete records.at(i);
    }
}

// add a record to the back of the records vector
void Records::pushRecord(Record* r)
{
    records.push_back(r);
}

// add a record at index i
void Records::insertRecord(int i, Record* r)
{
    records.insert(i, r);
}

// get a record at index i
Record* Records::getRecord(int i)
{
    return records.at(i);
}

// get the number of records
int Records::getSize()
{
    return records.size();
}

// clear and delete all records
void Records::clear()
{
    while (records.size())
    {
        // free memory and remove Record one by one
        delete records.at(0);
        records.pop_front();
    }
}

