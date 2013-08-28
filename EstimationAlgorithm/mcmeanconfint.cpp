#include "mcmeanconfint.h"

MCMeanConfint::MCMeanConfint()
{
    level = 0.95;
    multiplier = 1.64;
}

void MCMeanConfint::BuildBorder(QVector<double> fvals)
{
    // classical MC confidence interval
    border.clear();
    border.reserve(fvals.count());
}
