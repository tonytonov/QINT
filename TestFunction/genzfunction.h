#ifndef GENZFUNCTION_H
#define GENZFUNCTION_H

#include <QString>
#include <TestFunction/testfunction.h>

class GenzFunction : public TestFunction
{
public:
    GenzFunction(int index, int dim);

protected:
    int genzIndex;

public:
    double GetValue(QVector<double> x);
    double GetExactValue();
};

#endif // GENZFUNCTION_H
