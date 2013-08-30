#include "qmcqconfint.h"

QMCQConfint::QMCQConfint(const QMCQConfint &q) :
    MeanEstimation(q)
{

}

QMCQConfint *QMCQConfint::clone() const
{
    return new QMCQConfint(*this);
}

void QMCQConfint::BuildBorder(QVector<double> fvals)
{

}
