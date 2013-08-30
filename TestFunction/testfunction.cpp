#include "testfunction.h"

TestFunction::TestFunction(int dim): dim(dim)
{

}

TestFunction::TestFunction(const TestFunction &t) :
    dim(t.dim), label(t.label)
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

