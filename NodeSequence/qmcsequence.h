#ifndef QMCSEQUENCE_H
#define QMCSEQUENCE_H

#include <NodeSequence/nodesequence.h>

class QMCSequence : public NodeSequence
{
public:
    QMCSequence(int dim, int len);
};

#endif // QMCSEQUENCE_H
