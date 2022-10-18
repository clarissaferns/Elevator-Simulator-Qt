#include "record.h"

Record::Record(QString n, int g, int d, int i, QString dt) :
    type(n), group(g), duration(d), intensity(i), timestamp(dt)
{

}

Record::~Record()
{

}

QString Record::toString()
{
   QString out = "";

   out.append(timestamp);
   out.append("\n");
   out.append("Type: " + type);
   out.append("\n");
   out.append("Group: " + QString::number(group) + " mins\n");
   out.append("Duration: " + QString::number(duration) + " seconds\n");
   out.append("Intensity: " + QString::number(intensity));
   out.append("\n---------");

   return out;
}

