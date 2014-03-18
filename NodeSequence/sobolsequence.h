#ifndef SOBOLSEQUENCE_H
#define SOBOLSEQUENCE_H

#include <NodeSequence/QMCSequence.h>

class SobolSequence : public QMCSequence
{
public:
    SobolSequence(int dim, int len);
    SobolSequence(const SobolSequence& s);
    virtual SobolSequence* clone() const;

public:
    virtual void Generate();
};

#endif // SOBOLSEQUENCE_H
