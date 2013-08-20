#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

#include <QVector>

class TestFunction
{
public:
    TestFunction();

private:
    int dim;

public:
    virtual double GetValue(QVector<double> x)=0;
};

#endif // TESTFUNCTION_H
