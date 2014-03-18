#include "GenzFunction.h"
#include "testpack.h"

GenzFunction::GenzFunction(int index, int dim): TestFunction(dim), genzIndex(index)
{
    label = QString::fromStdString(genz_name(index));
    fillGenzParams(index);
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

void GenzFunction::fillGenzParams(int index)
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
//    switch(index)
//    {
//    case 1:
//    {
//        alpha = normalizeGenzParams(alpha, 110 / sqrt(dim*dim*dim));
//        break;
//    }
//    case 2:
//    {
//        alpha = normalizeGenzParams(alpha, 600 / dim*dim);
//        break;
//    }
//    case 3:
//    {
//        alpha = normalizeGenzParams(alpha, 600 / dim*dim);
//        break;
//    }
//    case 4:
//    {
//        alpha = normalizeGenzParams(alpha, 100 / dim);
//        break;
//    }
//    case 5:
//    {
//        alpha = normalizeGenzParams(alpha, 150 / dim*dim);
//        break;
//    }
//    case 6:
//    {
//        alpha = normalizeGenzParams(alpha, 100 / dim*dim);
//        break;
//    }
//    }
}

QVector<double> GenzFunction::normalizeGenzParams(QVector<double> alpha, double norm_value)
{
    double norm = 0;
    QVector<double> alpha_norm;
    alpha_norm.reserve(dim);
    for (int i=0; i<dim; i++)
    {
        norm += abs(alpha[i]);
    }
    for (int i=0; i<dim; i++)
    {
        alpha_norm.push_back(alpha[i] / norm * norm_value);
    }
    return alpha_norm;
}
