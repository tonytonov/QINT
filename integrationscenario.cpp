#include "integrationscenario.h"

IntegrationScenario::IntegrationScenario()
{
}

IntegrationScenario::IntegrationScenario(NodeSequence *s, TestFunction *f) : seq(s), fun(f)
{
}

void IntegrationScenario::RunAnalysis()
{
    // getting integrand function values
    fvals.clear();
    fvals.reserve(seq->getLen());
    foreach (QVector<double> x, seq->getSeq())
    {
        fvals.push_back(fun->GetValue(x));
    }
    exact = fun->GetExactValue();
    // passing these values to an error estimation algorithm

}
