#include "sobolsequence.h"
#include "sobol.h"

SobolSequence::SobolSequence(int d, int l) : QMCSequence(d,l)
{
    seq.reserve(l);
    foreach (QVector<double> s, seq)
    {
        s.reserve(d);
    }
}

void SobolSequence::Generate()
{
    for (int i=0; i<len; i++)
    {
        for (int j=0; j<dim; j++)
        {
            seq[i].push_back(sobol::sample(i,j));
        }
    }
}
