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
    //TODO : qconfint core
    border.clear();
    int k = 0;
    foreach (double v, fvals)
    {
        border.insert(k, 0);
    }
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
    }
    }
}
