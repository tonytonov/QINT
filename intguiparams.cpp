#include "intguiparams.h"
#include <cmath>

IntGuiParams::IntGuiParams()
{

}

void IntGuiParams::setFunctionIndex(int value)
{
    functionIndex = value;
}

int IntGuiParams::getFunctionIndex() const
{
    return functionIndex;
}

void IntGuiParams::setFunctionDim(int value)
{
    functionDim = value;
}

int IntGuiParams::getFunctionDim() const
{
    return functionDim;
}

void IntGuiParams::setRuleIndex(int value)
{
    ruleIndex = value;
}

int IntGuiParams::getRuleIndex() const
{
    return ruleIndex;
}

void IntGuiParams::setSeqLength(int value)
{
    seqLength = value;
}

int IntGuiParams::getSeqLength() const
{
    return seqLength;
}

void IntGuiParams::setFunctionDim(const QString str)
{
    functionDim = str.toInt();
}

void IntGuiParams::setSeqLength(const QString str)
{
    seqLength = str.toInt();
}

int IntGuiParams::getkParam() const
{
    return kParam;
}

int IntGuiParams::getsParam() const
{
    return sParam;
}

void IntGuiParams::setsParam(int value)
{
    sParam = value;
    kParam = pow(2, floor(log2(seqLength)) - sParam);
}

void IntGuiParams::setsParam(const QString str)
{
    sParam = str.toInt();
    kParam = pow(2, floor(log2(seqLength)) - sParam);
}
