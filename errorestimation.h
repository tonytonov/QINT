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
    void LaunchEstimation(QVector<double> fvals);
};

#endif // ERRORESTIMATION_H
