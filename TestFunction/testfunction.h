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
    double GetValue(QVector<double> x);
};

#endif // TESTFUNCTION_H
