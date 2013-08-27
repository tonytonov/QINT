#include "testfunction.h"

TestFunction::TestFunction(): dim(-1), label("Unknown function")
{
}

TestFunction::TestFunction(int dim): dim(dim)
{

}

QString TestFunction::getLabel() const
{
    return label;
}

void TestFunction::setLabel(const QString &value)
{
    label = value;
}

int TestFunction::getDim() const
{
    return dim;
}

void TestFunction::setDim(int value)
{
    dim = value;
}

