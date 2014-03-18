#include "MCConfint.h"
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

void MCConfint::AddBorder(QVector<double> fvals)
{
    border.clear();
    for (int k = 1 ; k <= fvals.count(); k++)
    {
        AddBorderStep(k, fvals);
    }
}

void MCConfint::AddBorderStep(int N, QVector<double> fvals)
{
    // classical MC confidence interval
    // cumulative stddev is computed in the same way as for QMC
    QMap<int, double> mclim;
    double meanN = 0;
    double meanSqN = 0;
    for (int i = 0; i < N; i++)
    {
        meanN += fvals[i] / N;
        meanSqN += fvals[i] * fvals[i] / N;
    }
    double varEstimMC = (meanSqN - meanN * meanN) / N;
    if (varEstimMC < 0.0) {return;}
    mclim.insert(N, multiplier * sqrt(varEstimMC));
    border.push_back(mclim);
}
