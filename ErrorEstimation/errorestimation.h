#ifndef ERRORESTIMATION_H
#define ERRORESTIMATION_H

#include <QVector>

class ErrorEstimation
{
public:
    ErrorEstimation();

private:
    QVector<double> border;

public:
    virtual void LaunchEstimation(QVector<double> fvals)=0;
};

#endif // ERRORESTIMATION_H
