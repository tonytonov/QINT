#ifndef ESTIMATIONALGORITHM_H
#define ESTIMATIONALGORITHM_H

#include <QVector>

class EstimationAlgorithm
{
public:
    EstimationAlgorithm();

private:
    QVector<double> border;

public:
    virtual void LaunchEstimation(QVector<double> fvals)=0;
};

#endif // ESTIMATIONALGORITHM_H
