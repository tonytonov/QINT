#include "MCUniformSequence.h"

MCUniformSequence::MCUniformSequence(int dim, int len, double seed, RInside &R) :
    MCSequence(dim, len, seed), R(R)
{
    seq.reserve(len);
    foreach (QVector<double> s, seq)
    {
        s.reserve(dim);
    }
    Generate();
}

MCUniformSequence::MCUniformSequence(const MCUniformSequence &s) :
    MCSequence(s), R(s.R)
{

}

MCUniformSequence *MCUniformSequence::clone() const
{
    return new MCUniformSequence(*this);
}

void MCUniformSequence::Generate()
{
    R["mcu.dim"] = dim;
    R["mcu.seed"] = seed;
    R.parseEvalQ("set.seed(mcu.seed);");

    for (int i = 0; i < len; i++)
    {
        std::vector<double> vec;
        QVector<double> svec;
        R.parseEvalQ("mcu.seq <- runif(mcu.dim);");
        vec = Rcpp::as<std::vector<double> >(R["mcu.seq"]);
        svec = QVector<double>::fromStdVector(vec);
        seq.push_back(svec);
    }
    R.parseEvalQ("set.seed(NULL);");
}
