#ifndef ESTIMATIONALGORITHM_H
#define ESTIMATIONALGORITHM_H

#include <QVector>
#include <QMap>

class EstimationAlgorithm
{
public:
    EstimationAlgorithm();
    EstimationAlgorithm(const EstimationAlgorithm& e);
    virtual EstimationAlgorithm* clone() const = 0;

protected:
    QVector<double> estimate;
    QMap<int, double> border;

public:
    virtual void BuildEstimate(QVector<double> fvals)=0;
    //TODO: call by const reference
    virtual void BuildBorder(QVector<double> fvals)=0;
    QVector<double> getEstimate() const;
    void setEstimate(const QVector<double> &value);
    QMap<int, double> getBorder() const;
    void setBorder(const QMap<int, double> &value);
};

#endif // ESTIMATIONALGORITHM_H
