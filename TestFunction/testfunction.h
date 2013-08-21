#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

#include <QVector>
#include <QString>

class TestFunction
{
public:
    TestFunction();

private:
    int dim;
    QString label;

public:
    virtual double GetValue(QVector<double> x)=0;
    virtual double GetExactValue()=0;
};

#endif // TESTFUNCTION_H
