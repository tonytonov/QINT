#ifndef GENZFUNCTION_H
#define GENZFUNCTION_H

#include <QString>
#include <TestFunction/testfunction.h>

class GenzFunction : public TestFunction
{
public:
    GenzFunction(int index, int dim);
    GenzFunction(int index, int dim, double* alpha, double* beta);

protected:
    int genzIndex;
    double* alpha;
    double* beta;

public:
    double GetValue(QVector<double> x);
    double GetExactValue();
};

#endif // GENZFUNCTION_H
