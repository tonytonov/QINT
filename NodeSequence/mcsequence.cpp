#include "mcsequence.h"

MCSequence::MCSequence(int dim, int len) : NodeSequence(dim, len)
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

