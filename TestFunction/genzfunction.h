#ifndef GENZFUNCTION_H
#define GENZFUNCTION_H

#include <QString>
#include <TestFunction/testfunction.h>

class GenzFunction : public TestFunction
{
public:
    GenzFunction(int index);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    int genzIndex;
    QString description;

public:
    double GetValue(QVector<double> x);
    double GetExactValue();
};

#endif // GENZFUNCTION_H
