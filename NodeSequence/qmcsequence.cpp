#include "qmcsequence.h"

QMCSequence::QMCSequence(int dim, int len) : NodeSequence(dim, len)
{

}

QMCSequence::QMCSequence(const QMCSequence &s):
    NodeSequence(s)
{

}
