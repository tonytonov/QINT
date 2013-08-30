#include "meanestimation.h"

MeanEstimation::MeanEstimation()
{

}

MeanEstimation::MeanEstimation(const MeanEstimation &m) :
    EstimationAlgorithm(m)
{

}

void MeanEstimation::BuildEstimate(QVector<double> fvals)
{
    // integral is estimated as a cumulative average
    // LATEX: \hat{\Theta}_k = \frac1k \sum\limits_{i=1}^k f(x_i)
    estimate.clear();
    estimate.reserve(fvals.count());
    double avg = 0;
    int k = 0;
    foreach (double v, fvals)
    {
        ++k;
        avg = (avg * (k - 1) + v) / k;
        estimate.push_back(avg);
    }
}
