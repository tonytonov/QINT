#ifndef GENZFUNCTION_H
#define GENZFUNCTION_H

#include <QString>
#include <TestFunction/testfunction.h>

class GenzFunction : public TestFunction
{
public:
    GenzFunction();

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    int genzIndex;
    QString description;
};

#endif // GENZFUNCTION_H
