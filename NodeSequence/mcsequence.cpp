#include "MCSequence.h"

MCSequence::MCSequence(int dim, int len, double seed) :
    NodeSequence(dim, len), seed(seed)
{

}

MCSequence::MCSequence(const MCSequence &s) :
    NodeSequence(s), seed(s.seed)
{

}

double MCSequence::getSeed() const
{
    return seed;
}

void MCSequence::setSeed(double value)
{
    seed = value;
}

