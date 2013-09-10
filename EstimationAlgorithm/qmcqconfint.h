#ifndef QMCQCONFINT_H
#define QMCQCONFINT_H

#include <EstimationAlgorithm/meanestimation.h>
#include <NodeSequence/nodesequence.h>
#include <QVector>

class QMCQConfint : public MeanEstimation
{
public:
    QMCQConfint(const NodeSequence *ns, int k, int s);
    QMCQConfint(const QMCQConfint &q);
    QMCQConfint* clone() const;

protected:
    QVector<int> map;
    int kParam;
    int sParam;
    double multiplier;

public:
    virtual void AddBorder(QVector<double> fvals);
    void MapSequence(const NodeSequence *ns, int method = 0);
};

#endif // QMCQCONFINT_H
