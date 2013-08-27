#ifndef SOBOLSEQUENCE_H
#define SOBOLSEQUENCE_H

#include <NodeSequence/qmcsequence.h>

class SobolSequence : public QMCSequence
{
public:
    SobolSequence();
    SobolSequence(int dim, int len);

public:
    void Generate();
};

#endif // SOBOLSEQUENCE_H
