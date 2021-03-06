#ifndef QMCSEQUENCE_H
#define QMCSEQUENCE_H

#include <NodeSequence/NodeSequence.h>

class QMCSequence : public NodeSequence
{
public:
    QMCSequence(int dim, int len);
    QMCSequence(const QMCSequence &s);
};

#endif // QMCSEQUENCE_H
