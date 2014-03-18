#ifndef MEANESTIMATION_H
#define MEANESTIMATION_H

#include <EstimationAlgorithm/EstimationAlgorithm.h>

class MeanEstimation : public EstimationAlgorithm
{
public:
    MeanEstimation();
    MeanEstimation(const MeanEstimation& m);
    virtual void BuildEstimate(QVector<double> fvals);
};

#endif // MEANESTIMATION_H
