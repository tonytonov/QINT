#ifndef MCSEQUENCE_H
#define MCSEQUENCE_H

#include <NodeSequence/NodeSequence.h>

class MCSequence : public NodeSequence
{
public:
    MCSequence(int dim, int len, double seed);
    MCSequence(const MCSequence& s);

    double getSeed() const;
    void setSeed(double value);

protected:
    double seed;
};

#endif // MCSEQUENCE_H
