#ifndef SOBOLSEQUENCERANDOMIZED_H
#define SOBOLSEQUENCERANDOMIZED_H

#include <RInside.h>
#include <NodeSequence/QMCSequence.h>

class SobolSequenceRandomized : public QMCSequence
{
public:
    SobolSequenceRandomized(int dim, int len, double seed, RInside &R);
    SobolSequenceRandomized(const SobolSequenceRandomized &s);
    virtual SobolSequenceRandomized *clone() const;

    double getSeed() const;
    void setSeed(double value);

protected:
    double seed;
private:
    RInside &R;
public:
    virtual void Generate();
};

#endif // SOBOLSEQUENCERANDOMIZED_H
