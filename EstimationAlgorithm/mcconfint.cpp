#include "mcconfint.h"

MCConfint::MCConfint()
{
    level = 0.95;
    multiplier = 1.64;
}

void MCConfint::BuildBorder(QVector<double> fvals)
{
    // classical MC confidence interval
    border.clear();
    border.reserve(fvals.count());
}
