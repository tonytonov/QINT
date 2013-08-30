#ifndef GENZFUNCTION_H
#define GENZFUNCTION_H

#include <QString>
#include <TestFunction/testfunction.h>

class GenzFunction : public TestFunction
{
public:
    GenzFunction(int index, int dim);
    GenzFunction(const GenzFunction& g);
    virtual GenzFunction* clone() const;

protected:
    int genzIndex;
    QVector<double> alpha;
    QVector<double> beta;

private:
    void fillGenzParams();

public:
    double virtual GetValue(QVector<double> x);
    double virtual GetExactValue();
};

#endif // GENZFUNCTION_H
