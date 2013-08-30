#ifndef MCSEQUENCE_H
#define MCSEQUENCE_H

#include <NodeSequence/nodesequence.h>

class MCSequence : public NodeSequence
{
public:
    MCSequence(int dim, int len);
    MCSequence(const MCSequence& s);

    double getSeed() const;
    void setSeed(double value);

private:
    double seed;
};

#endif // MCSEQUENCE_H
