#include "mcconfint.h"
#include <math.h>

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
    // cumulative stddev is computed safely (reference to Knuth)
    border.clear();
    double stddev;
    double sqdiff = 0;
    int k = 0;
    foreach (double v, fvals)
    {
        ++k;
        if (k > 1)
        {
            sqdiff = sqdiff + (v - estimate[k-2]) * (v - estimate[k-1]);
            stddev = sqrt(sqdiff / (k - 1));
            border.insert(k, multiplier * stddev / sqrt(k));
        }
    }
}
