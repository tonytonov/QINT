#include "genzfunction.h"
#include "testpack.h"

GenzFunction::GenzFunction(int index, int dim): TestFunction(dim), genzIndex(index)
{
    label = QString::fromStdString(genz_name(index));
}

double GenzFunction::GetValue(QVector<double> x)
{
    double alpha[1] = {0};
    double beta[1] = {1};
    return genz_function(genzIndex, dim, x.data(), alpha, beta);
}

double GenzFunction::GetExactValue()
{
    return 0;
}
