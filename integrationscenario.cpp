#include "integrationscenario.h"

IntegrationScenario::IntegrationScenario()
{

}

IntegrationScenario::IntegrationScenario(NodeSequence *seq, TestFunction *fun, EstimationAlgorithm *est) :
    seq(seq), fun(fun), est(est)
{

}

void IntegrationScenario::RunAnalysis()
{
    // getting integrand function values and exact value
    fvals.clear();
    fvals.reserve(seq->getLen());
    foreach (QVector<double> x, seq->getSeq())
    {
        fvals.push_back(fun->GetValue(x));
    }
    exact = fun->GetExactValue();

    // passing these values to an error estimation algorithm
    est->BuildEstimate(fvals);
    est->BuildBorder(fvals);

}
