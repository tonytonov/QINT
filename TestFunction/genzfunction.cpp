#include "genzfunction.h"
#include "testpack.h"

GenzFunction::GenzFunction(int index, int dim): TestFunction(dim), genzIndex(index)
{
    label = QString::fromStdString(genz_name(index));
    fillGenzParams();
}

GenzFunction::GenzFunction(const GenzFunction &g) :
    TestFunction(g), genzIndex(g.genzIndex), alpha(g.alpha), beta(g.beta)
{

}

GenzFunction *GenzFunction::clone() const
{
    return new GenzFunction(*this);
}

double GenzFunction::GetValue(QVector<double> x)
{
    return genz_function(genzIndex, dim, x.data(), alpha.data(), beta.data());
}

double GenzFunction::GetExactValue()
{
    return genz_integral(genzIndex, dim, alpha.data(), beta.data());
}

void GenzFunction::fillGenzParams()
{
    alpha.clear();
    beta.clear();
    alpha.reserve(dim);
    beta.reserve(dim);
    for (int i=0; i<dim; i++)
    {
        alpha.push_back(1);
        beta.push_back(1);
    }
}
