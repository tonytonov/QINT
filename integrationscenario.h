#ifndef INTEGRATIONSCENARIO_H
#define INTEGRATIONSCENARIO_H

#include <QVector>

#include <NodeSequence/nodesequence.h>
#include <TestFunction/testfunction.h>
#include <ErrorEstimation/errorestimation.h>

class IntegrationScenario
{
public:
    IntegrationScenario();
    IntegrationScenario(NodeSequence *s, TestFunction *f);
    void RunAnalysis();

private:
    NodeSequence* seq;
    TestFunction* fun;
    ErrorEstimation* err;
    QVector<double> fvals;
};

#endif // INTEGRATIONSCENARIO_H
