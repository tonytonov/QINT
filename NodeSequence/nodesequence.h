#ifndef NODESEQUENCE_H
#define NODESEQUENCE_H

#include <QList>
#include <QVector>

class NodeSequence
{
public:
    NodeSequence(int d, int l);

protected:
    int dim;
    int len;
    QList<QVector<double> > seq;

public:
    virtual void Generate()=0;
    int getDim() const;
    void setDim(int value);
    int getLen() const;
    void setLen(int value);
};

#endif // NODESEQUENCE_H
