#ifndef INTEGRATIONSCENARIO_H
#define INTEGRATIONSCENARIO_H

#include <QVector>

#include <nodesequence.h>
#include <testfunction.h>
#include <errorestimation.h>

class IntegrationScenario
{
public:
    IntegrationScenario();
    IntegrationScenario(NodeSequence s, TestFunction f);

private:
    NodeSequence seq;
    TestFunction fun;
    ErrorEstimation err;
    QVector<double> fvals;
};

#endif // INTEGRATIONSCENARIO_H
