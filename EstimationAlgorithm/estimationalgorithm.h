#ifndef ESTIMATIONALGORITHM_H
#define ESTIMATIONALGORITHM_H

#include <QVector>

class EstimationAlgorithm
{
public:
    EstimationAlgorithm();
    EstimationAlgorithm(const EstimationAlgorithm& e);
    virtual EstimationAlgorithm* clone() const = 0;

protected:
    QVector<double> estimate;
    QVector<double> border;

public:
    virtual void BuildEstimate(QVector<double> fvals)=0;
    virtual void BuildBorder(QVector<double> fvals)=0;
};

#endif // ESTIMATIONALGORITHM_H
