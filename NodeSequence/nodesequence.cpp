#include "nodesequence.h"

NodeSequence::NodeSequence(int d, int l) : dim(d), len(l)
{
}
int NodeSequence::getLen() const
{
    return len;
}

void NodeSequence::setLen(int value)
{
    len = value;
}

int NodeSequence::getDim() const
{
    return dim;
}

void NodeSequence::setDim(int value)
{
    dim = value;
}


