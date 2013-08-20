#ifndef NODESEQUENCE_H
#define NODESEQUENCE_H

class NodeSequence
{
public:
    NodeSequence();
    NodeSequence(int d, int l);

private:
    int dim;
    int length;

public:
    void Generate();
};

#endif // NODESEQUENCE_H
