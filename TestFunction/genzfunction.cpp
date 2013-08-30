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

//GenzFunction::GenzFunction(const GenzFunction &gf)
//{
//    this->genzIndex = gf.genzIndex;
//    this->label = gf.label;
//    this->alpha = gf.alpha;
//    this->beta = gf.beta;
//}

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
    switch (genzIndex) {
    case 1:
        for (int i=0; i<dim; i++)
        {
            alpha.push_back(0);
            beta.push_back(1);
        }
        break;
    case 2:
        //TODO
        break;
    case 3:
        //TODO
        break;
    case 4:
        //TODO
        break;
    case 5:
        //TODO
        break;
    case 6:
        //TODO
        break;
    default:
        break;
   }
}
