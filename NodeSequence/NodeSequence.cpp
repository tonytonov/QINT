#include "NodeSequence.h"

NodeSequence::NodeSequence(int dim, int len) : dim(dim), len(len)
{

}

NodeSequence::NodeSequence(const NodeSequence &s) :
    dim(s.dim), len(s.len), seq(s.seq)
{

}

QList<QVector<double> > NodeSequence::getSeq() const
{
    return seq;
}

void NodeSequence::setSeq(const QList<QVector<double> > &value)
{
    seq = value;
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


