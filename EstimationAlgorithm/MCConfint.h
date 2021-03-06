#ifndef MCCONFINT_H
#define MCCONFINT_H

#include <EstimationAlgorithm/MeanEstimation.h>

class MCConfint : public MeanEstimation
{
public:
    MCConfint(double level, double multiplier);
    MCConfint(const MCConfint& c);
    virtual MCConfint* clone() const;

private:
    double level;
    double multiplier;

public:
    virtual void AddBorder(QVector<double> fvals);
    void AddBorderStep(int N, QVector<double> fvals);
};

#endif // MCCONFINT_H
