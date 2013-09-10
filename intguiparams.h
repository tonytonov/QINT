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
    int getkParam() const;
    int getsParam() const;

private:
    int functionIndex;
    int functionDim;
    int ruleIndex;
    int seqLength;
    int kParam;
    int sParam;

public slots:
    void setFunctionIndex(int);
    void setFunctionDim(int);
    void setFunctionDim(QString const);
    void setRuleIndex(int);
    void setSeqLength(int);
    void setSeqLength(QString const);
    void setsParam(int);
    void setsParam(const QString);

signals:
    void kParamChanged(QString);
    void sParamChanged(QString);
};

#endif // INTGUIPARAMS_H
