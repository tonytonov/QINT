#ifndef MCCONFINT_H
#define MCCONFINT_H

#include <EstimationAlgorithm/meanestimation.h>

class MCConfint : public MeanEstimation
{
public:
    MCConfint();

private:
    double level;
    double multiplier;
    QVector<double> stddev;

public:
    void BuildBorder(QVector<double> fvals);
};

#endif // MCCONFINT_H
