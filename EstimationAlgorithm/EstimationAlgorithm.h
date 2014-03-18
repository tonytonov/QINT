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
    QList<QMap<int, double> > border;

public:
    virtual void BuildEstimate(QVector<double> fvals)=0;
    //TODO: call by const reference
    virtual void AddBorder(QVector<double> fvals)=0;
    QVector<double> getEstimate() const;
    void setEstimate(const QVector<double> &value);
    QList<QMap<int, double> > getBorder() const;
    void setBorder(const QList<QMap<int, double> > &value);
};

#endif // ESTIMATIONALGORITHM_H
