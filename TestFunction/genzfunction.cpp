#include "genzfunction.h"

GenzFunction::GenzFunction()
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

