#ifndef NODESEQUENCE_H
#define NODESEQUENCE_H

#include <QList>
#include <QVector>

class NodeSequence
{
public:
    NodeSequence();
    NodeSequence(int d, int l);

private:
    int dim;
    int len;
    QList<QVector<double> > seq;

public:
    virtual void Generate()=0;
};

#endif // NODESEQUENCE_H
