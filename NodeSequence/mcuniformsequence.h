#ifndef MCUNIFORMSEQUENCE_H
#define MCUNIFORMSEQUENCE_H

#include <RInside.h>
#include <NodeSequence/mcsequence.h>

class MCUniformSequence : public MCSequence
{
public:
    MCUniformSequence(int dim, int len, double seed, RInside &R);
    MCUniformSequence(const MCUniformSequence &s);
    virtual MCUniformSequence *clone() const;

private:
    RInside &R;
public:
    virtual void Generate();
};

#endif // MCUNIFORMSEQUENCE_H
