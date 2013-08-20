#ifndef MCSEQUENCE_H
#define MCSEQUENCE_H

#include <NodeSequence/nodesequence.h>

class MCSequence : public NodeSequence
{
public:
    MCSequence();

private:
    double seed;
};

#endif // MCSEQUENCE_H
