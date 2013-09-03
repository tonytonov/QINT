#include "estimationalgorithm.h"

EstimationAlgorithm::EstimationAlgorithm()
{

}

EstimationAlgorithm::EstimationAlgorithm(const EstimationAlgorithm &e) :
    estimate(e.estimate), border(e.border)
{

}

QVector<double> EstimationAlgorithm::getEstimate() const
{
    return estimate;
}

void EstimationAlgorithm::setEstimate(const QVector<double> &value)
{
    estimate = value;
}

QMap<int, double> EstimationAlgorithm::getBorder() const
{
    return border;
}

void EstimationAlgorithm::setBorder(const QMap<int, double> &value)
{
    border = value;
}

