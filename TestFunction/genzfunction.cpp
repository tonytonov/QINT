#include "genzfunction.h"

GenzFunction::GenzFunction(int index): genzIndex(index)
{

}

QString GenzFunction::getDescription() const
{
    return description;
}

void GenzFunction::setDescription(const QString &value)
{
    description = value;
}

double GenzFunction::GetValue(QVector<double> x)
{
    return 0;
}

double GenzFunction::GetExactValue()
{
    return 0;
}

