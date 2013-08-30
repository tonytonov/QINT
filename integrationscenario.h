#ifndef INTEGRATIONSCENARIO_H
#define INTEGRATIONSCENARIO_H

#include <QVector>

#include <NodeSequence/nodesequence.h>
#include <TestFunction/testfunction.h>
#include <EstimationAlgorithm/estimationalgorithm.h>

class IntegrationScenario
{
public:
    IntegrationScenario();
    IntegrationScenario(IntegrationScenario const& i);
    ~IntegrationScenario();
    void RunAnalysis();

private:
    NodeSequence *seq;
    TestFunction *fun;
    EstimationAlgorithm *alg;
    QVector<double> fvals;
    double exact;

public:
    NodeSequence* getSeq() const;
    void setSeq(NodeSequence *const value);
    TestFunction* getFun() const;
    void setFun(TestFunction *const value);
    EstimationAlgorithm* getAlg() const;
    void setAlg(EstimationAlgorithm *const value);
};

#endif // INTEGRATIONSCENARIO_H
