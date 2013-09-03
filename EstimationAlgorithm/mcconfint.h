#ifndef MCCONFINT_H
#define MCCONFINT_H

#include <EstimationAlgorithm/meanestimation.h>

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
    virtual void BuildBorder(QVector<double> fvals);
};

#endif // MCCONFINT_H
