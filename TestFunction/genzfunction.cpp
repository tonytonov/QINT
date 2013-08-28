#include "genzfunction.h"
#include "testpack.h"

GenzFunction::GenzFunction(int index, int dim): TestFunction(dim), genzIndex(index)
{
    label = QString::fromStdString(genz_name(index));
}

GenzFunction::GenzFunction(int index, int dim, double *alpha, double *beta):
    TestFunction(dim), genzIndex(index), alpha(alpha), beta(beta)
{
    label = QString::fromStdString(genz_name(index));
}

double GenzFunction::GetValue(QVector<double> x)
{
    return genz_function(genzIndex, dim, x.data(), alpha, beta);
}

double GenzFunction::GetExactValue()
{
    return genz_integral(genzIndex, dim, alpha, beta);
}
