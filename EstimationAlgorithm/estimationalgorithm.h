#ifndef ESTIMATIONALGORITHM_H
#define ESTIMATIONALGORITHM_H

#include <QVector>

class EstimationAlgorithm
{
public:
    EstimationAlgorithm();

protected:
    QVector<double> estimate;
    QVector<double> border;

public:
    virtual void BuildEstimate(QVector<double> fvals)=0;
    virtual void BuildBorder(QVector<double> fvals)=0;
};

#endif // ESTIMATIONALGORITHM_H
