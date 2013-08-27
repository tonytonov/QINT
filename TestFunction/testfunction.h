#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

#include <QVector>
#include <QString>

class TestFunction
{
public:
    TestFunction();
    TestFunction(int dim);

protected:
    int dim;
    QString label;

public:
    virtual double GetValue(QVector<double> x)=0;
    virtual double GetExactValue()=0;
    int getDim() const;
    void setDim(int value);
    QString getLabel() const;
    void setLabel(const QString &value);
};

#endif // TESTFUNCTION_H
