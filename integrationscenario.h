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
    IntegrationScenario(NodeSequence *seq, TestFunction *fun, EstimationAlgorithm *est);
    void RunAnalysis();

private:
    NodeSequence* seq;
    TestFunction* fun;
    EstimationAlgorithm* est;
    QVector<double> fvals;
    double exact;
};

#endif // INTEGRATIONSCENARIO_H
