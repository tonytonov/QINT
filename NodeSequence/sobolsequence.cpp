#include "sobolsequence.h"
#include "sobol.h"

SobolSequence::SobolSequence(int dim, int len) : QMCSequence(dim, len)
{
    seq.reserve(len);
    foreach (QVector<double> s, seq)
    {
        s.reserve(dim);
    }
    Generate();
}

SobolSequence::SobolSequence(const SobolSequence &s) :
    QMCSequence(s)
{

}

SobolSequence *SobolSequence::clone() const
{
    return new SobolSequence(*this);
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
