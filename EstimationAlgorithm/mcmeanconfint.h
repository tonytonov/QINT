#ifndef MCMEANCONFINT_H
#define MCMEANCONFINT_H

#include <EstimationAlgorithm/meanestimation.h>

class MCMeanConfint : public MeanEstimation
{
public:
    MCMeanConfint();

private:
    double level;
    double multiplier;
    QVector<double> stddev;

public:
    void BuildBorder(QVector<double> fvals);
};

#endif // MCMEANCONFINT_H
