#ifndef NODESEQUENCE_H
#define NODESEQUENCE_H

#include <QList>
#include <QVector>

class NodeSequence
{
public:
    NodeSequence(int dim, int len);

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
    QList<QVector<double> > getSeq() const;
    void setSeq(const QList<QVector<double> > &value);
};

#endif // NODESEQUENCE_H
