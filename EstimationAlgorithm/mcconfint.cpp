#include "mcconfint.h"

MCConfint::MCConfint(double level, double multiplier) :
    level(level), multiplier(multiplier)
{

}

MCConfint::MCConfint(const MCConfint &m) :
    MeanEstimation(m), level(m.level), multiplier(m.multiplier)
{

}

MCConfint *MCConfint::clone() const
{
    return new MCConfint(*this);
}

void MCConfint::BuildBorder(QVector<double> fvals)
{
    // classical MC confidence interval
    border.clear();
    border.reserve(fvals.count());
    // TODO
}
