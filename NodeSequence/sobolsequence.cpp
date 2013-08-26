#include "sobolsequence.h"
#include "sobol.h"

SobolSequence::SobolSequence(int d, int l) : QMCSequence(d,l)
{
    seq.reserve(l);
    foreach (QVector<double> s, seq)
    {
        s.reserve(d);
    }
    Generate();
}

void SobolSequence::Generate()
{
    for (int i=0; i<len; i++)
    {
        QVector<double> svec;
        seq.push_back(svec);
        for (int j=0; j<dim; j++)
        {
            double sval = sobol::sample(i,j);
            seq[i].push_back(sval);
        }
    }
}
