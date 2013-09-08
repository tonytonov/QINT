#include "qmcqconfint.h"
#include <cmath>

QMCQConfint::QMCQConfint(const NodeSequence *ns)
{
    //temporary fixing params
    sParam = log2(ns->getLen());
    kParam = 1;
    MapSequence(ns);
}

QMCQConfint::QMCQConfint(const QMCQConfint &q) :
    MeanEstimation(q)
{

}

QMCQConfint *QMCQConfint::clone() const
{
    return new QMCQConfint(*this);
}

void QMCQConfint::BuildBorder(QVector<double> fvals)
{
    border.clear();
    int NSets = pow(2, sParam);
    QVector<double> alphas;
    alphas.reserve(NSets);
    int N = kParam * NSets;
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
        alphas[map[i]] += 1.0 / N / kParam * fvals[i];
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
    border.insert(N, 1.0 / N * (meanSqN - meanN * meanN - ssAlpha));
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
        foreach (QVector<double> v, seq) {
            int index = (int) floor(v[0] * pow(2, sParam));
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
