#ifndef INTEGRATIONSCENARIO_H
#define INTEGRATIONSCENARIO_H

#include <QVector>

#include <NodeSequence/NodeSequence.h>
#include <TestFunction/TestFunction.h>
#include <EstimationAlgorithm/EstimationAlgorithm.h>

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
    QVector<double> getFvals() const;
    void setFvals(QVector<double> const value);
    double getExact() const;
    void setExact(double const value);
};

#endif // INTEGRATIONSCENARIO_H
