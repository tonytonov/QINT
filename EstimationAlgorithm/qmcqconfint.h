#ifndef QMCQCONFINT_H
#define QMCQCONFINT_H

#include <EstimationAlgorithm/meanestimation.h>

class QMCQConfint : public MeanEstimation
{
    QMCQConfint(const QMCQConfint& q);
    QMCQConfint* clone() const;

public:
    virtual void BuildBorder(QVector<double> fvals);
};

#endif // QMCQCONFINT_H
