#include "QMCQConfint.h"
#include <cmath>
#include <algorithm>

QMCQConfint::QMCQConfint(const NodeSequence *ns, int k, int s, double mult) :
    kParam(k), sParam(s), multiplier(mult)
{
    MapSequence(ns, 1);
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
    border.clear();
    for (int k = 1 ; k <= kParam; k++)
    {
        // ignore k=1, variance estimate is often 0
        if (k == 1) continue;
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
        alphas[map[i]] += fvals[i] / N;
        meanN += fvals[i] / N;
        meanSqN += fvals[i] * fvals[i] / N;
    }
    // sum of squared pairwise differences
    for (int i = 0; i < NSets; i++)
    {
        for (int j = i; j < NSets; j++)
        {
            ssAlpha += (alphas[i] - alphas[j]) * (alphas[i] - alphas[j]);
        }
    }
    // no border prior to N
    double varEstimMC = (meanSqN - meanN * meanN) / N;
    double varEstimQMC = varEstimMC - ssAlpha / N;
    // QMC estimate may be less than 0 due to rounding around zero
    // in that case, ignore estimation as unreliable
    if (varEstimQMC < 0.0) {return;}
    QMap<int, double> qmclim;
    // border is actual until next k or end of range
    int lastPt = std::min(fvals.count() + 1, (k + 1) * NSets);
    for (int i = N; i < lastPt; i++)
    {
        qmclim.insert(i, multiplier * sqrt(varEstimQMC));
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
        // subsets are chosen to be as close to cubic shape as possible
        foreach (QVector<double> v, seq) {
            int index = CubicSubsetIndex(v, sParam);
            map.push_back(index);
        }
        break;
    }
    }
}

int QMCQConfint::CubicSubsetIndex(QVector<double> v, int s)
{
    int d = v.count();
    QVector<int> partTimes;
    partTimes.reserve(d);
    QVector<int> binaryIndex;
    binaryIndex.reserve(d);
    int index = 0;
    auto dv = std::div(s, d);
    int a = dv.quot;
    int b = dv.rem;
    for (int i = 0; i < d; i++)
    {
        (i < b) ? partTimes.push_back(a + 1) : partTimes.push_back(a);
        binaryIndex.push_back(floor(v[i] * pow(2, partTimes[i])));
        index += binaryIndex[i] * pow(2, s - VectorSum(partTimes));
    }
    return index;
}

int QMCQConfint::VectorSum(QVector<int> v)
{
    double sum = 0;
    for (int j = 0; j < v.count(); j++)
    {
        sum += v[j];
    }
    return sum;
}

