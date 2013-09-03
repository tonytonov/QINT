#include "integrationscenario.h"

IntegrationScenario::IntegrationScenario()
{

}

IntegrationScenario::IntegrationScenario(const IntegrationScenario &i) :
    seq(i.seq->clone()), fun(i.fun->clone()), alg(i.alg->clone())
{

}

IntegrationScenario::~IntegrationScenario()
{
    delete seq;
    delete fun;
    delete alg;
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

    // passing these values to estimation algorithm
    alg->BuildEstimate(fvals);
    alg->BuildBorder(fvals);

}

NodeSequence *IntegrationScenario::getSeq() const
{
    return seq;
}

void IntegrationScenario::setSeq(NodeSequence *const value)
{
    seq = value;
}

TestFunction *IntegrationScenario::getFun() const
{
    return fun;
}

void IntegrationScenario::setFun(TestFunction *const value)
{
    fun = value;
}

EstimationAlgorithm *IntegrationScenario::getAlg() const
{
    return alg;
}

void IntegrationScenario::setAlg(EstimationAlgorithm *const value)
{
    alg = value;
}

QVector<double> IntegrationScenario::getFvals() const
{
    return fvals;
}

void IntegrationScenario::setFvals(const QVector<double> value)
{
    fvals = value;
}

double IntegrationScenario::getExact() const
{
    return exact;
}

void IntegrationScenario::setExact(const double value)
{
    exact = value;
}
