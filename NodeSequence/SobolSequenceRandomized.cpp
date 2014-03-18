#include "SobolSequenceRandomized.h"
#include "sobol.h"

SobolSequenceRandomized::SobolSequenceRandomized(int dim, int len, double seed, RInside &R) :
    QMCSequence(dim, len), seed(seed), R(R)
{
    seq.reserve(len);
    foreach (QVector<double> s, seq)
    {
        s.reserve(dim);
    }
    Generate();
}

SobolSequenceRandomized::SobolSequenceRandomized(const SobolSequenceRandomized &s) :
    QMCSequence(s), seed(s.seed), R(s.R)
{

}

SobolSequenceRandomized *SobolSequenceRandomized::clone() const
{
    return new SobolSequenceRandomized(*this);
}

void SobolSequenceRandomized::Generate()
{
    R["ssr_seed"] = seed;
    R["ssr_dim"] = dim;
    R.parseEvalQ("set.seed(ssr_seed);");
    R.parseEvalQ("rand_vec <- runif(ssr_dim);");
    std::vector<double> vecShift;
    QVector<double> svecShift;
    vecShift = Rcpp::as<std::vector<double> >(R["rand_vec"]);
    svecShift = QVector<double>::fromStdVector(vecShift);
    R.parseEvalQ("set.seed(NULL);");

    for (int i = 0; i < len; i++)
    {
        QVector<double> svec;
        seq.push_back(svec);
        for (int j = 0; j < dim; j++)
        {
            double sval = sobol::sample(i, j) + svecShift[j];
            if (sval >= 1) sval--;
            seq[i].push_back(sval);
        }
    }
}


double SobolSequenceRandomized::getSeed() const
{
    return seed;
}

void SobolSequenceRandomized::setSeed(double value)
{
    seed = value;
}
