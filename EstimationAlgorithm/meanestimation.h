#ifndef MEANESTIMATION_H
#define MEANESTIMATION_H

#include <EstimationAlgorithm/estimationalgorithm.h>

class MeanEstimation : public EstimationAlgorithm
{
public:
    MeanEstimation();
    MeanEstimation(const MeanEstimation& m);
    virtual void BuildEstimate(QVector<double> fvals);
};

#endif // MEANESTIMATION_H
