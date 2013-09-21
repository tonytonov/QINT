#include "qmcqconfint.h"
#include <cmath>
#include <algorithm>

QMCQConfint::QMCQConfint(const NodeSequence *ns, int k, int s) :
    kParam(k), sParam(s)
{
    multiplier = 2.58;
    MapSequence(ns);
}

QMCQConfint::QMCQConfint(const QMCQConfint &q) :
    MeanEstimation(q), kParam(q.kParam), sParam(q.sParam), multiplier(q.multiplier)
{

}

QMCQConfint *QMCQConfint::clone() const
{
    return new QMCQConfint(*this);
}

void QMCQConfint::AddBorder(QVector<double> fvals)
{
    for (int k = 1 ; k <= kParam; k++)
    {
        AddBorderStep(k, fvals);
    }
}

void QMCQConfint::AddBorderStep(int k, QVector<double> fvals)
{
    int NSets = pow(2, sParam);
    QVector<double> alphas;
    alphas.reserve(NSets);
    int N = k * NSets;
    double meanN = 0;
    double meanSqN = 0;
    double ssAlpha = 0;

    for (int j = 0; j < NSets; j++)
    {
        alphas.push_back(0);
    }
    // computing mean values for each group and total
    for (int i = 0; i < N; i++)
    {
        alphas[map[i]] += 1.0 / N / k * fvals[i];
        meanN += 1.0 / N * fvals[i];
        meanSqN += 1.0 / N * fvals[i] * fvals[i];
    }
    // sum of squared pairwise differences
    for (int i = 0; i < NSets; i++)
    {
        for (int j = i; j < NSets; j++)
        {
            ssAlpha += pow(alphas[i] - alphas[j], 2);
        }
    }
    // no border prior to N
    double varEstimMC = 1.0 / N * (meanSqN - meanN * meanN);
    double varEstimQMC = varEstimMC - 1.0 / N * ssAlpha;
    // QMC estimate may be less than 0 due to rounding around zero
    // in that case, ignore estimation as unreliable
    if (varEstimQMC < 0.0) {return;}
    QMap<int, double> qmclim;
    // border is actual until next k or end of range
    int lastPt = std::min(fvals.count() + 1, (k + 1) * NSets);
    for (int i = N; i < lastPt; i++)
    {
        qmclim.insert(i, multiplier * sqrt(varEstimQMC) / sqrt(N));
    }
    border.push_back(qmclim);
}

void QMCQConfint::MapSequence(const NodeSequence *ns, int method)
{
    // maps sequence points into groups, which are used later to build upper border
    map.clear();
    map.reserve(ns->getLen());
    QList<QVector<double> > seq = ns->getSeq();
    switch(method)
    {
    case 0:
    {
        // only the first coordinate is used to define subsets
        foreach (QVector<double> v, seq) {
            int index = floor(v[0] * pow(2, sParam));
            map.push_back(index);
        }
        break;
    }
    case 1:
    {
        //TODO
        break;
    }
    }
}
