#include "mcsequence.h"

MCSequence::MCSequence(int d, int l) : NodeSequence(d,l)
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

