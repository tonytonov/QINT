#ifndef INTGUIPARAMS_H
#define INTGUIPARAMS_H

#include <QObject>

class IntGuiParams : public QObject
{
    Q_OBJECT

public:
    IntGuiParams();

    int getFunctionIndex() const;
    int getFunctionDim() const;
    int getRuleIndex() const;
    int getSeqLength() const;

private:
    int functionIndex;
    int functionDim;
    int ruleIndex;
    int seqLength;

public slots:
    void setFunctionIndex(int);
    void setFunctionDim(int);
    void setRuleIndex(int);
    void setSeqLength(int);
    void setFunctionDim(QString const);
    void setSeqLength(QString const);

};

#endif // INTGUIPARAMS_H
