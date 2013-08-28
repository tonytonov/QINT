#include "mcsequence.h"

MCSequence::MCSequence(int dim, int len) : NodeSequence(dim, len)
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

